import socket

HOST = socket.gethostbyname(socket.gethostname())

PORT = 7777

a = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
a.bind((HOST, PORT))

while 1:
    ...





