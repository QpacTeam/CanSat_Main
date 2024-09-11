import serial
import time
x = 0
be = ''
print('start')
ser = serial.Serial("COM9", 112500)
file = open('radio_1.txt', 'a')

data = '\r\n'
data = data.encode('utf-8') #fordítás a lora nyelvére
ser.write(data)
time.sleep(0.2)
data = 'sys reset\r\n' #lora újra indítása
data = data.encode('utf-8')
ser.write(data)
time.sleep(0.2)
data = 'radio rx 0\r\n' #vételre elindítani a lorát
data = data.encode('utf-8')
ser.write(data)

while x != 9:
    be = ser.readline()
    be = be.decode('utf-8')
    print(be, end='')
    x += 1


with open('radio.txt', 'w') as file:
    while True:
        be = ser.read()
        if be != '' or be != '\n':
            be = be.decode('utf-8') #üzenet str formátumba alakítása
            print(be, end='') #kiírás a konzolra nem szükséges
            if be != '' or be != '\n':
                file.write(be)