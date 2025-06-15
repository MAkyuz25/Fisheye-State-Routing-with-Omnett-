import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import glob
import os
from io import StringIO
import csv

# ------------------ CONFIGURATION ------------------
packet_size_bytes = 1000  # payload size in bytes
sim_duration = 15.0       # simulation duration in seconds
"""    "numhosts": {
        "filepath" : "num_hosts_all.csv",
        "xlabel" : "Number of Hosts", ## Or network size
        'sim_duration': sim_duration,
    },
    """
hosts_dir = ""
cases_dict = {
    "exp": {
        "filepath" : "results_sendInterval/sendInterval_all.csv",
        "xlabel" : "Send Interval (exponential)", ## Or network size
        'sim_duration': sim_duration,
    }
}

plot_dict = {
    'Throughput':{
        'ylabel': "Average Throughput (bps)"
    },
    'Packet Delivery Ratio':{
        'ylabel': "Packet Delivery Ratio"
    },
    'End-to-End Delay': {
        'ylabel' : 'Mean End-to-End Delay (s)'
    },
    'Control‐Bit Overhead': {
        'ylabel' : 'Control Bits / Data Bits Delivered'
    },
    'Control-to-Data Overhead': {
        'ylabel' : 'DataBitsTransmitted/ DataBitsDelivered'
    },
}

# ---------------------------------------------------

# --------------------- HELPERS ---------------------

def get_df_dict(filepath,variable):
    # Find all matching CSVs
    # Extract number of hosts from filename
    fname = os.path.basename(filepath)

    # Load the CSV
    df_all = pd.read_csv(
        filepath,
        names=["run", variable, "repetition", "module", "name", "value"],
        usecols=range(6),
        skiprows=1,  # <--- SKIP the header row
        engine='python',
        on_bad_lines='skip'
    )

    # Convert value column to numeric (force errors to NaN, then drop them)
    df_all['value'] = pd.to_numeric(df_all['value'], errors='coerce')
    df_all = df_all.dropna(subset=['value'])  # drop rows where conversion failed

    # Show a few example rows
    #print(f"First few rows from {fname}:")
    #print(df_all.head())
    grouped_dfs = {key: group for key, group in df_all.groupby(variable)}
    return grouped_dfs



def get_histogram_df(casename):
    hist_name = "endToEndDelay:histogram"
    # Step 1: Load raw file and isolate the histogram section
    with open(cases_dict[casename]["filepath"], "r", encoding="utf-8") as f:
        lines = f.readlines()

    # Step 2: Find the start of the histogram section
    start_index = None
    for i, line in enumerate(lines):
        if line.strip() == "**** HISTOGRAMS ****":
            start_index = i + 1
            break
    if start_index is None:
        raise ValueError("Could not find '**** HISTOGRAMS ****' marker.")

    # Step 3: Read header and filter lines with valid number of columns
    header = lines[start_index].strip()
    expected_columns = len(header.split(","))

    header = lines[start_index].strip().split(",")[:13]  # only first 13 columns
    data_lines = []
    for i in range(start_index + 1, len(lines)):
        line = lines[i]
        if hist_name in line and "binedges" in line:
            # only take first 13 columns
            trimmed = ",".join(line.strip().split(",")[:13])
            data_lines.append(trimmed)

    df = pd.DataFrame([line.split(",") for line in data_lines], columns=header)
    
    # Step 6: Ensure correct types
    df["mean"] = pd.to_numeric(df["mean"], errors="coerce")
    df[casename] = pd.to_numeric(df[casename], errors="coerce")

    # Drop rows with NaN values in important columns
    df = df.dropna(subset=["mean", casename])

    # Step 7: Group by numhosts and compute mean + 95% CI
    grouped_dfs = {key: group for key, group in df.groupby(casename)}
    return grouped_dfs



def get_rows(rowName):
    return df[df["name"] == rowName].groupby("repetition")["value"].sum()
    
def get_mean_ci(tps, lists,N):
    if tps.empty:
        print(f"  → no valid data for N={N}")
        return lists

    # Compute mean & 95% CI
    mean_val = tps.mean()
    std_val  = tps.std(ddof=1)
    n_runs   = len(tps)
    ci95     = 1.96 * std_val / np.sqrt(n_runs)

    # Store
    variable_list, mean_tps, ci95_tps = lists
    variable_list.append(int(N))
    mean_tps.append(mean_val)
    ci95_tps.append(ci95)
    return variable_list, mean_tps, ci95_tps

# ---------------------------------------------------

def throughput_func(lists, df,N):
    # Filter for the received-packet counts
    counts = get_rows("packetReceived:count")

    # Compute throughput per repetition (bps)
    tps = counts * packet_size_bytes * 8 / sim_duration
    return get_mean_ci(tps,lists,N)


def packetDeliver_func(lists,df,N):
        # pick out the “:count” rows
    sent_counts = get_rows("packetSent:count")
    recv_counts = get_rows("packetReceived:count")

    # align repetitions and compute per-run PDR
    common_reps = sent_counts.index.intersection(recv_counts.index)
    sent_counts = sent_counts.loc[common_reps]
    recv_counts = recv_counts.loc[common_reps]
    pdr = (recv_counts / sent_counts.replace({0: np.nan})).dropna()

    return get_mean_ci(pdr,lists,N)


def controlRatio_func(lists,df,N):
    # filter & sum per repetition
    ctl_vals = get_rows("controlBytesSent")
    inc_vals = get_rows("incomingPacketLengths:sum")

    # align repetitions
    reps = ctl_vals.index.intersection(inc_vals.index)
    ctl_vals = ctl_vals.loc[reps]
    inc_vals = inc_vals.loc[reps]

    # compute overhead per run
    overhead = (ctl_vals / inc_vals.replace({0: np.nan})).dropna()
    return get_mean_ci(overhead,lists,N)
    

def dataRatio_func(lists,df,N):
    # filter & sum per repetition
    ctl_vals = get_rows("packetSent:sum(packetBytes)")
    inc_vals = get_rows("packetReceived:sum(packetBytes)")

    # align repetitions
    reps = ctl_vals.index.intersection(inc_vals.index)
    ctl_vals = ctl_vals.loc[reps]
    inc_vals = inc_vals.loc[reps]

    # compute overhead per run
    overhead = (ctl_vals / inc_vals.replace({0: np.nan})).dropna()
    return get_mean_ci(overhead,lists,N)




def endToEnd_func(lists, df, N):
    hist_name = "endToEndDelay:histogram"
    values = df["mean"].values
    m = np.mean(values)
    s = np.std(values, ddof=1)
    ci = 1.96 * s / np.sqrt(len(values))

    variable_list, mean_tps, ci95_tps = lists
    variable_list.append(N)
    mean_tps.append(m)
    ci95_tps.append(ci)
    return variable_list, mean_tps, ci95_tps


def plot_func(variable_name, lists, df,N):
    if variable_name == "Throughput":
        results_list = throughput_func(lists, df,N)
    elif variable_name == "End-to-End Delay":
        results_list = endToEnd_func(lists,df, N)
    elif variable_name == "Packet Delivery Ratio":
        results_list = packetDeliver_func(lists, df,N)
    elif variable_name == "Control‐Bit Overhead":
        results_list = controlRatio_func(lists, df,N)
    elif variable_name == "Control-to-Data Overhead":
        results_list = dataRatio_func(lists, df,N)

    return results_list


if __name__ == "__main__":
    for curr_case, curr_case_dict in cases_dict.items():
        grouped_dfs = get_df_dict(curr_case_dict["filepath"], curr_case )
        histogram_dfs = get_histogram_df(curr_case)

        for curr_plot, curr_plot_dict in plot_dict.items():
            lists = [[],[],[]]
            print(curr_case)
            if curr_plot == "End-to-End Delay":
                for N, df in histogram_dfs.items():
                    lists = plot_func(curr_plot,lists,df,N)
            else:
                for N, df in grouped_dfs.items():
                    lists = plot_func(curr_plot,lists,df,N)
            variable_list, mean_tps, ci95_tps = lists

            # Sort by case variable
            sorted_idx = np.argsort(variable_list)
            variable_list = np.array(variable_list)[sorted_idx]
            mean_tps    = np.array(mean_tps)[sorted_idx]
            ci95_tps    = np.array(ci95_tps)[sorted_idx]

            # Set up plot
            sns.set(style="whitegrid")
            plt.figure(figsize=(8, 5))

            # Plot with error bars
            plt.errorbar(
                variable_list,
                mean_tps,
                yerr=ci95_tps,
                fmt='o-',
                capsize=5,
                label=curr_plot
            )

            plt.xlabel(curr_case_dict["xlabel"])
            plt.ylabel(curr_plot_dict["ylabel"])
            plt.title(f"{curr_plot_dict['ylabel']} vs {curr_case_dict['xlabel']}")
            plt.fill_between(
                variable_list,
                mean_tps - ci95_tps ,
                mean_tps + ci95_tps ,
                alpha=0.2
            )
            plt.tight_layout()
            plt.savefig(f"images/{curr_case}_{curr_plot}.png", dpi=300, bbox_inches="tight")
            plt.close()
