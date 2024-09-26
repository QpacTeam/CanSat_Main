import serial, time

ser = serial.Serial("/dev/ttyUSB0", 112500)

def init():
    data = '\r\n'.encode('utf-8') #fordítás a lora nyelvére
    ser.write(data)
    time.sleep(0.5)
    data = 'sys reset\r\n'.encode('utf-8') #sys reset
    ser.write(data)
    time.sleep(0.5)
    data = 'radio rx 0\r\n'.encode('utf-8') #start receiving
    ser.write(data)

    x = 0
    while x != 6:
        be = ser.readline()
        be = be.decode('utf-8')
        print(be, end='')
        x += 1

def get_data():
    be = ser.readline().decode("utf-8")
    with open("data.txt", "a") as file:
        file.write(be)
    return be


if __name__ == "__main__":
    init()
    while True:
        get_data()