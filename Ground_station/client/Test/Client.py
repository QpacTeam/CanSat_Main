import socket as soc, antiparcer, icecream as ic, graph

HOST = '172.21.13.220'

PORT = 9090

socket = soc.socket(soc.AF_INET, soc.SOCK_STREAM)
socket.connect((HOST, PORT))

temp_alt = graph.Function(2, [[0, 1500], [-10, 40]])

datalist = []
while 1:
    line = socket.recv(1024).decode("utf-8")
    socket.send("szam1".encode('utf-8'))
    datalist = antiparcer.antiparcer_data(line)
