#!/usr/bin/python

'''
BLG632E - Next Generation Wireless Networks 
Homework Assignment #5
Tugrul Yatagan 504161551
'''

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.util import irange,dumpNodeConnections
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel

class CustomTopo(Topo):
    "Simple Data Center Topology"
    
    "linkopts - (1:core, 2:aggregation, 3: edge) parameters"
    "fanout - number of child switch per parent switch"
    def __init__(self, linkopts1, linkopts2, linkopts3, fanout=2, **opts):
        # Initialize topology and default options
        Topo.__init__(self, **opts)

        core = self.addSwitch('core_ty1')

        for a in range(fanout):
            aggr = self.addSwitch('access_ty%s' % (a + 1))
            self.addLink(aggr, core, **linkopts1)

            for e in range(fanout):
                edge = self.addSwitch('edge_ty%s' % ((a * fanout + e) + 1))
                self.addLink(edge, aggr, **linkopts2)
        
                for h in range(fanout):
                    host = self.addHost('host_ty%s' % (((a * fanout + e) * fanout + h) + 1))
                    self.addLink(host, edge, **linkopts3)


def simpleTest():
    print "a. Setting link parameters"
    "--- core to aggregation switches"
    linkopts1 = {'bw':50, 'delay':'5ms'}
    "--- aggregation to edge switches"
    linkopts2 = {'bw':30, 'delay':'10ms'}
    "--- edge switches to hosts"
    linkopts3 = {'bw':10, 'delay':'15ms'}

    print "b. Creating Custom Topology"
    topo = CustomTopo(linkopts1, linkopts2, linkopts3, fanout=2)
    
    print "c. Firing up Mininet"
    net = Mininet(topo=topo, host=CPULimitedHost, link=TCLink)
    net.start()

    print "Dumping host connections"
    dumpNodeConnections(net.hosts)

    print "d. Starting Test"
    net.pingAll()
    
    print "e. Stopping Mininet"
    net.stop()

if __name__ == '__main__':
    # Tell mininet to print useful information
    setLogLevel('info')
    simpleTest()
