package inet.node.fsr;

import inet.node.inet.AdhocHost;
import inet.routing.fsr.Fsr;

module FsrRouter extends AdhocHost {
    parameters:
        @display("bgb=800,600");
    submodules:
        fsr: Fsr {
            @display("p=825,226");
        }
    connections allowunconnected:
        fsr.socketOut --> at.in++;
        fsr.socketIn  <-- at.out++;
}