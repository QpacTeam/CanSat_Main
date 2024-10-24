import Radio
import threading
import socket
from Variables import DEFAULT_PORT, STATUS_PRINT_FREQ, DEVICES_TO_LISTEN

Cycle: int = STATUS_PRINT_FREQ
PORT: int = DEFAULT_PORT
Devices = []

HOST = socket.gethostbyname(socket.gethostname())
SERVER = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

while 1:
    try:
        SERVER.bind((HOST, PORT))
        break
    except:
        PORT -= 1
    if PORT == (DEFAULT_PORT - 100):
        print("Can not open port")
        while 1:
            pass

print("=== SERVER START ===")
print(f"host: {HOST}")
print(f"port: {PORT}")
print("")

Radio.Radio_Init()


class Comp(object):
    def __init__(self, comm):
        self.comm = comm

    def send(self, ms):
        try:
            self.comm.send(ms.encode("utf-8"))
            return self.comm.recv(1024).decode("utf-8")
        except:
            return "error"

SERVER.listen(DEVICES_TO_LISTEN)

def get_connection():
    comm, address = SERVER.accept()
    c = Comp(comm)
    Devices.append(c)
    print(f" >>> DEVICE {len(Devices)} CONNECTED")


for i in range(DEVICES_TO_LISTEN):
    thread = threading.Thread(target= get_connection)    # < Creating threads
    thread.start()

# === MAIN LOOP ===
while 1:
    msg = Radio.Radio_Run()
    i = 0

    while i < len(Devices):
        respond = Devices[i].send(msg)

        if respond == "error":
            Devices.pop(i)
            print(" >>> ONE DEVICE LEFT")
            i -= 1

        if Cycle >= STATUS_PRINT_FREQ:
            print(f" devices available: {len(Devices)}")
            Cycle = 0

        i += 1
    Cycle += 1
