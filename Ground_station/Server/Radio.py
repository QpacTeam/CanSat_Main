import serial
import time
from time import strftime, gmtime
from Variables import RADIO_CTL_SLEEP_TIME, SAVE_FILE_LOCATION, DEFAULT_SAVE_NAME, USE_TIME_SIGNO


ser = serial.Serial("/dev/ttyUSB0", 112500)


def Radio_Write(message: str = '\r\n', wait_after_write: float = RADIO_CTL_SLEEP_TIME):
    ser.write(message.encode('utf-8'))
    time.sleep(wait_after_write)


def Radio_Init():
    global File_Name

    if USE_TIME_SIGNO:
        T = f"{strftime('%Y_%b_%d_%H_%M_%S',gmtime(time.time()))}"
        File_Name = f"{SAVE_FILE_LOCATION}/{T}"
        with open(File_Name, "w") as File:
            File.write("BEGIN\n")
    else:
        File_Name = f"{SAVE_FILE_LOCATION}/{DEFAULT_SAVE_NAME}"
        with open(File_Name, "w") as File:
            File.write("BEGIN\n")

    Radio_Write()   # Sends bullshit
    Radio_Write('sys reset\r\n')    # Sys reset
    Radio_Write('radio rx 0\r\n', 0)    # Start receiving


def Radio_Run():
    msg = ser.readline().decode("utf-8")
    with open(File_Name, "a") as file:
        text: str = f"{strftime('%H:%M:%S',gmtime(time.time()))}.{'%03d' % int(time.time()%1*1000//1)} > {msg}"
        file.write(text)
        file.close()
    return msg


if __name__ == "__main__":
    Radio_Init()
    while 1:
        Radio_Run()
