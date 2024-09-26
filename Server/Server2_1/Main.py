import sys, lora_accept, threading, time, socket
from icecream import ic

PORT = 9004
HOST = socket.gethostbyname(socket.gethostname())

print(HOST)

SERVER = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
SERVER.bind((HOST, PORT))

lora_accept.init()



class Comp(object):
    def __init__(self, comm):
        self.comm = comm

    def send(self, ms):
        try:
            self.comm.send(ms.encode("utf-8"))
            return self.comm.recv(1024).decode("utf-8")
        except: sys.exit(0)


def send(comp, i):
    print("hurray", comp)
    while 1:
        alma = comp.send(str(i))
        if alma != None: print(alma)
        time.sleep(0.5)
        print("most")

SERVER.listen(5)

for i in range(5):
    communication_socket, address = SERVER.accept()
    c = Comp(communication_socket)
    t = threading.Thread(target= send, args=(c, i,))
    t.start()


