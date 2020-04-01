import socket
import time as t

HOST =  '127.0.0.1'  #'138.68.107.119'  # The server's hostname or IP address
PORT = 60003     # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    while True:
        try:
            #s.sendall(b'Hello, world')
            t.sleep(2)
        except:
            s.close() #executes when ctrl+C is pressed
            break