import socket
import sys
import ipaddress



ip = sys.argv[1]
port = int(sys.argv[2])


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((ip, port))
    s.listen()
    conn, addr = s.accept()
    print('Connected by', addr)
    while True:
        data = conn.recv(1024)
        if not data:
            break
        print(data)