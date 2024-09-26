import socket as soc, antiparcer

HOST = '172.21.13.220'

PORT = 9090

socket = soc.socket(soc.AF_INET, soc.SOCK_STREAM)
socket.connect((HOST, PORT))

while 1:
    alma = socket.recv(1024).decode("utf-8")
    print(antiparcer.antiparcer_data(alma))
    socket.send("szam3".encode('utf-8'))

