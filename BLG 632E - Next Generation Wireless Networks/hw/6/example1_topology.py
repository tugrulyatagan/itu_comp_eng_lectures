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
 
#class POXcontroller1( Controller):
#   def start(self):
#       self.pox='%s/pox/pox.py' %os.environ['HOME']
#       self.cmd(self.pox, "lab7_controller > /tmp/lab7_controller &")
#   def stop(self):
#       self.cmd('kill %' +self.pox)
 
#controllers = { 'poxcontroller': POXcontroller1}
 
class MyTopo(Topo):
    "Single switch connected to n hosts."
    def __init__(self):
        Topo.__init__(self)
        s1=self.addSwitch('s1')
        s2=self.addSwitch('s2')
        s3=self.addSwitch('s3')
        s4=self.addSwitch('s4')
        s5=self.addSwitch('s5') 
        h1=self.addHost('h1',mac='00:00:00:00:00:01',ip='10.0.0.1/8')
        h2=self.addHost('h2',mac='00:00:00:00:00:02',ip='10.0.0.2/8')

         
        self.addLink(h1, s1, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True)
        self.addLink(s1, s2, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True) 
        self.addLink(s1, s3, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True) 
        self.addLink(s1, s4, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True) 
        self.addLink(s2, s5, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True) 
        self.addLink(s3, s5, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True)  
        self.addLink(s4, s5, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True) 
        self.addLink(s5, h2, bw=1, delay='10ms', loss=0, max_queue_size=1000, use_htb=True)  

def perfTest():
    "Create network and run simple performance test"
    topo = MyTopo()
    #net = Mininet(topo=topo, host=CPULimitedHost, link=TCLink, controller=POXcontroller1)
    net = Mininet(topo=topo, host=CPULimitedHost, link=TCLink, controller=partial(RemoteController, ip='127.0.0.1', port=6633))
    net.start()
    print "Dumping host connections"
    dumpNodeConnections(net.hosts)
    h1,h2=net.get('h1','h2')
    CLI(net)
    net.stop()
 
if __name__ == '__main__':
    setLogLevel('info')
    perfTest()
