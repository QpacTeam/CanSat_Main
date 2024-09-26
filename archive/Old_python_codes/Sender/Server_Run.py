import time
import serial
import socket as soc
from Server_Variables import STATE_FILE_LOCATION, RADIO_SLEEP, DEFAULT_RADIO_PORT, RADIO_PORT_FILE_LOCATION, SERIAL_FILE
from icecream import ic

# SER = serial.Serial(SERIAL_FILE, 112500)
# ic(SER)

HOST = soc.gethostbyname(soc.gethostname())
server = soc.socket(soc.AF_INET, soc.SOCK_STREAM)

RADIO_PORT: int = DEFAULT_RADIO_PORT
for i in range(1000):
    try:
        server.bind((HOST, RADIO_PORT))
    except:
        RADIO_PORT -= 1

with open(RADIO_PORT_FILE_LOCATION, "w") as File:
    File.write(str(RADIO_PORT))


def Get_Operation_Mode() -> int:
    try:
        with open(STATE_FILE_LOCATION, "r") as File:
            data = File.readline()
            return int(data)
    except:
        return 999


def Radio_Write(data='\r\n') -> None:
    # msg = str(data).encode('utf-8')     # < Translate for the LoRa
    # SER.write(msg)
    # time.sleep(RADIO_SLEEP)
    pass


def Radio_Init() -> None:

    Radio_Write('\r\n')
    Radio_Write('sys reset\r\n')
    Radio_Write('radio rx 0\r\n')

    # for i in range(9):      # What the fuck is this thing?
    #     msg = SER.readline()
    #     msg = msg.decode('utf-8')
    #     print(msg, end='')


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
