# Tugrul Yatagan 504161551
import socket

server_address = ('localhost', 5444)

try:
    message = 'Tugrul'
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    source_address = ('localhost', 5566)
    print 'sending "%s" over %s' % (message, source_address)
    sock.bind(source_address)
    sent = sock.sendto(message, server_address)
    sock.close()

    message = 'Yatagan'
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    source_address = ('localhost', 5567)
    print 'sending "%s" over %s' % (message, source_address)
    sock.bind(source_address)
    sent = sock.sendto(message, server_address)

finally:
    print 'closing socket'
    sock.close()
