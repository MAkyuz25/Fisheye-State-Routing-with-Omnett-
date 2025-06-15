// Fsr.ned
package inet.routing.fsr;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.INetNode;

network FsrNetwork {
    parameters:
        @display("bgb=800,600");
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters: @display("p=100,100");
        }
        node[*]: INetNode {
            parameters:
                @display("p=200+100*index,300");
                routingProtocols = "Fsr";
        }
}
