import socket
import time as t
import sys
   

ip = sys.argv[1]
port = int(sys.argv[2])

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((ip, port))
    while True:
        s.sendall(b'Hello, world')
        t.sleep(2)
