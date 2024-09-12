import serial
import time

x = 0
be = ''
print('start')
SERIAL = serial.Serial(port="COM9", baudrate=112500)

data = '\r\n'.encode('utf-8')
# data = data.encode('utf-8') #fordítás a lora nyelvére
SERIAL.write(data)
time.sleep(0.2)
data = 'sys reset\r\n'.encode('utf-8') #lora újra indítása
SERIAL.write(data)
time.sleep(0.2)
data = 'radio rx 0\r\n'.encode('utf-8') #vételre elindítani a lorát
SERIAL.write(data)

while x != 9:
    be = SERIAL.readline()
    be = be.decode('utf-8')
    print(be, end='')
    x += 1

with open('radio.txt', 'w') as file:
    while True:
        be = SERIAL.read()
        if be != '' or be != '\n':
            be = be.decode('utf-8') #üzenet str formátumba alakítása
            print(be, end='') #kiírás a konzolra nem szükséges
            if be != '' or be != '\n':
                file.write(be)