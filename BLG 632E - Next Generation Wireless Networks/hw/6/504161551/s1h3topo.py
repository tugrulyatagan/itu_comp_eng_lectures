#!/usr/bin/python
 
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.node import Controller 
from mininet.cli import CLI
from functools import partial
from mininet.node import RemoteController
import os

 
class MyTopo(Topo):
    "Single switch connected to n hosts."
    def __init__(self):
        Topo.__init__(self)
        s1=self.addSwitch('s1') 
        h1=self.addHost('h1',mac='00:00:00:00:00:01',ip='10.0.0.1/8')
        h2=self.addHost('h2',mac='00:00:00:00:00:02',ip='10.0.0.2/8')
        h3=self.addHost('h3',mac='00:00:00:00:00:03',ip='10.0.0.3/8')

         
        self.addLink(h1, s1, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True)
        self.addLink(h2, s1, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True)
        self.addLink(h3, s1, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True)
        

def perfTest():
    "Create network and run simple performance test"
    topo = MyTopo()
    net = Mininet(topo=topo, host=CPULimitedHost, link=TCLink)
    net.start()
    print "Dumping host connections"
    dumpNodeConnections(net.hosts)
    h1,h2,h3=net.get('h1','h2','h3')
    CLI(net)
    net.stop()
 
if __name__ == '__main__':
    setLogLevel('info')
    perfTest()
