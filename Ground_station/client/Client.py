import socket as soc, antiparcer, icecream as ic

HOST = '172.21.13.220'

PORT = 9090

socket = soc.socket(soc.AF_INET, soc.SOCK_STREAM)
socket.connect((HOST, PORT))

while 1:
    alma = socket.recv(1024).decode("utf-8")
    socket.send("szam1".encode('utf-8'))
    print(antiparcer.antiparcer_data(alma))


