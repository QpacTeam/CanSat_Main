import serial
import time


ser = serial.Serial("/dev/ttyUSB0", 112500)

def init():
    data = '\r\n'.encode('utf-8') #fordítás a lora nyelvére
    ser.write(data)
    time.sleep(0.2)
    data = 'sys reset\r\n'.encode('utf-8') #sys reset
    ser.write(data)
    time.sleep(0.2)
    data = 'radio rx 0\r\n'.encode('utf-8') #start receiving
    ser.write(data)

    x = 0
    while x != 9:
        be = ser.readline()
        be = be.decode('utf-8')
        print(be, end='')
        x += 1

def substring(be, a, b):
    sub = ""
    for i in range(a, b):
        try:
            sub += be[i]
        except : pass
    try:
        return int(sub)
    except :
        print("HIBA------------------------------------------------------HIBA")
        return 0

def get_data():
    be = ser.readline().decode("UTF-8")

    try:
        time = substring(be, 10, 16)
    except : time = 0

    time = "%02d:%02d:%02d" % (time//10000, time%10000//100, time%100)
    latitude = substring(be,16, 24)
    latitude = latitude // 1000000 + (latitude % 1000000) / 10000 / 60
    longitude = substring(be, 24, 33)
    longitude = longitude // 1000000 + (longitude % 1000000) / 10000 / 60
    sat = substring(be, 33, 35)
    hdop = substring(be, 35, 38) / 100
    altitude = substring(be, 38, 43) / 10
    geo = substring(be, 43, 47) / 10

    if 1:
        print(be, end="")
        print(time)
        print(latitude)
        print(longitude)
        print(sat)
        print(hdop)
        print(altitude)
        print(geo)
        print("")

    with open('radio.txt', 'a') as file:
        file.write(f"time: {time}\nlatitude: {latitude}\nlongitude: {longitude}\nsatellites used: {sat}\nhdop: {hdop}\naltitude: {altitude}\ngeoid separation: {geo}\n")

    return [latitude, altitude, longitude]

if __name__ == "__main__":
    init()
    while True:
        get_data()