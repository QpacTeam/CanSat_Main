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
        except:
            comps.remove(self.comm)
            return "error"



# def send(comp):
#     print("hurray", comp)
#     while 1:
#         alma = comp.send(str(i))
#         if alma != None: print(alma)
#         time.sleep(0.5)
#         print("most")

SERVER.listen(5)

def get_connection():
    comm, address = SERVER.accept()
    c = Comp(comm)
    comps.append(c)

comps = []

for i in range(10):
    t = threading.Thread(target= get_connection)
    t.start()

while 1:
    be = lora_accept.get_data()
    i = 0
    while i < len(comps):
        respond = i.send(be)
        if respond == "error":
            i -= 1


