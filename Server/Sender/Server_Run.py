import time
import serial
from Server_Variables import STATE_FILE, RADIO_SLEEP

SER = serial.Serial("/dev/ttyUSB0", 112500)

def Get_Operation_Mode() -> int:
    try:
        with open(STATE_FILE, "r") as File:
            data = File.readline()
            return int(data)
    except:
        return 999


def Radio_Write(data='\r\n') -> None:
    msg = str(data).encode('utf-8')     # < Translate for the LoRa
    SER.write(msg)
    time.sleep(RADIO_SLEEP)
    

def Radio_Init() -> None:

    Radio_Write('\r\n')
    Radio_Write('sys reset\r\n')
    Radio_Write('radio rx 0\r\n')

    for i in range(9):      # What the fuck is this thing?
        msg = SER.readline()
        msg = msg.decode('utf-8')
        print(msg, end='')


def Radio_Get_Serial():
    ...


def Radio_Send():
    ...


def Radio_Save():
    ...


def run() -> None:
    Radio_Get_Serial()
    Radio_Send()
    Radio_Save()
    return
