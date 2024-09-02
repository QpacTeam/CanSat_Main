import socket as soc

HOST = '192.168.0.104'

PORT = 9896

socket = soc.socket(soc.AF_INET, soc.SOCK_STREAM)
socket.connect((HOST, PORT))

socket.send("Hello World!".encode('utf-8'))
print(socket.recv(1024))
