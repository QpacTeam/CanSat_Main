import serial
import time

x = 0
be = ''
print('start')
ser = serial.Serial("/dev/ttyUSB0", 112500)

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

def substring(be, a, b):
    sub = ""
    for i in range(a, b):
        sub += be[i]
    try:
        return int(sub)
    except :
        print("HIBA------------------------------------------------------HIBA")
        return 0

with open('radio.txt', 'w') as file:
    while True:
        be = ser.readline().decode("UTF-8")

        try:
            time = substring(be, 10, 16)
        except : time = 0
        time = "%02d:%02d:%02d" % (time//10000, time%10000//100, time%100)

        latitude = substring(be,16, 24) / 10000

        longitude = substring(be, 24, 33) / 10000

        sat = substring(be, 33, 35)

        hdop = substring(be, 35, 38) / 100

        altitude = substring(be, 38, 43) / 10

        geo = substring(be, 43, 47) / 10

        print(be, end="")
        print(time)
        print(latitude)
        print(longitude)
        print(sat)
        print(hdop)
        print(altitude)
        print(geo)
        print("")

        file.write(f"time: {time}\nlatitude: {latitude}\nlongitude: {longitude}\nsatellites used: {sat}\nhdop: {hdop}\naltitude: {altitude}\ngeoid separation: {geo}\n")

        # if be != '' or be != '\n':
        #     be = be.decode('utf-8') #üzenet str formátumba alakítása
        #     print(be, end='') #kiírás a konzolra nem szükséges
        #     if be != '' or be != '\n':
        #         file.write(be)