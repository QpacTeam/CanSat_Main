import serial
import time

TEST: bool = True

SER = serial.Serial("/dev/ttyUSB0", 112500)

def init() -> None:
    data = '\r\n'.encode('utf-8') #fordítás a lora nyelvére
    SER.write(data)
    time.sleep(0.2)
    data = 'sys reset\r\n'.encode('utf-8') #sys reset
    SER.write(data)
    time.sleep(0.2)
    data = 'radio rx 0\r\n'.encode('utf-8') #start receiving
    SER.write(data)

    x = 0
    while x != 9:
        msg = SER.readline()
        msg = msg.decode('utf-8')
        print(msg, end='')
        x += 1

def substring(msg_imp, a, b) -> int:
    sub: str = ""
    for i in range(a, b):
        try:
            sub += msg_imp[i]
        except : pass
    try:
        return int(sub)
    except :
        print("HIBA------------------------------------------------------HIBA")
        return 0

def get_data() -> list:
    msg: str = SER.readline().decode("UTF-8")

    try:
        time = substring(msg, 10, 16)
    except : time = 0

    time = "%02d:%02d:%02d" % (time//10000, time%10000//100, time%100)
    latitude = substring(msg,16, 24)
    latitude = latitude // 1000000 + (latitude % 1000000) / 10000 / 60
    longitude = substring(msg, 24, 33)
    longitude = longitude // 1000000 + (longitude % 1000000) / 10000 / 60
    sat = substring(msg, 33, 35)
    hdop = substring(msg, 35, 38) / 100
    altitude = substring(msg, 38, 43) / 10
    geo = substring(msg, 43, 47) / 10

    if TEST:
        print(msg, end="")
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
    while 1:
        get_data()