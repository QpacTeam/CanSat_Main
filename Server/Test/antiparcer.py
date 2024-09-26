import serial
import time


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

def antiparcer_data(be):

    try:
        time = substring(be, 9, 15)
    except : time = 0

    time = "%02d:%02d:%02d" % (time//10000, time%10000//100, time%100)
    latitude = substring(be,15, 23)
    latitude = latitude // 1000000 + (latitude % 1000000) / 10000 / 60
    longitude = substring(be, 23, 32)
    longitude = longitude // 1000000 + (longitude % 1000000) / 10000 / 60
    sat = substring(be, 32, 34)
    hdop = substring(be, 34, 37) / 100
    altitude = substring(be, 37, 42) / 10
    geo = substring(be, 42, 46) / 10

    sign = substring(be, 46, 47)
    temp = substring(be, 47, 51) / 100
    if sign == 1: temp *= -1

    pres = substring(be,51, 59) / 100

    if 1:
        print(be, end="")
        print(time)
        print(latitude)
        print(longitude)
        print(sat)
        print(hdop)
        print(altitude)
        print(geo)
        print(temp)
        print(pres)
        print("")

    with open('radio.txt', 'a') as file:
        file.write(f"time: {time}\nlatitude: {latitude}\nlongitude: {longitude}\nsatellites used: {sat}\nhdop: {hdop}\naltitude: {altitude}\ngeoid separation: {geo}\ntemperature: {temp}\npressure: {pres}\n")

    return [latitude, altitude, longitude, sat, hdop, altitude, geo, temp, pres]

# if __name__ == "__main__":
#     init()
#     while True:
#         get_data()