import socket as soc

HOST = soc.gethostbyname(soc.gethostname())

with open('number.txt', 'r') as fuck:
    num: str = fuck.read().strip()
    PORT = int(num)

with open('number.txt', 'w') as fuck:
    fuck.write(str(PORT - 1))

server = soc.socket(soc.AF_INET, soc.SOCK_STREAM)
server.bind((HOST, PORT))

server.listen(5)
communication_socket, address = server.accept()

num: int = 0

while 1:
    if num > 9:
        try:
            communication_socket.send("vege".encode('utf-8'))

            alma = communication_socket.recv(1024).decode('utf-8')
            print(alma)

            communication_socket.close()
            break
        except OSError:
            break

    try:
        communication_socket.send((str(num)).encode('utf-8'))
    except OSError: break
    num += 1

    alma = communication_socket.recv(1024).decode('utf-8')
    print(alma)

    # time.sleep(0.1)
