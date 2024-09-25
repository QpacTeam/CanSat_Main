import socket as soc

HOST = '172.21.13.220'

PORT = 9004

socket = soc.socket(soc.AF_INET, soc.SOCK_STREAM)
socket.connect((HOST, PORT))

while 1:
    alma = socket.recv(1024).decode("utf-8")
    print(alma)
    socket.send(f"{alma}".encode('utf-8'))

