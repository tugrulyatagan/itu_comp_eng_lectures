# Tugrul Yatagan 504161551
import socket

# Create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
server_address = ('localhost', 5444)
print 'starting up on %s port %s' % server_address
sock.bind(server_address)

while True:
    print 'waiting to receive message'
    data, address = sock.recvfrom(4096)
    print 'received %s bytes from host: %s  port: %s' % (len(data), address[0], address[1])
    print data
