from Server_Variables import STATE_FILE, CONTROL_SLEEP
import serial as SER


def Get_Operation_Mode() -> int:
    try:
        with open(STATE_FILE, "r") as File:
            data = File.readline()
            return int(data)
    except:
        return 999


def Radio_Write(data = '\r\n') -> None:
    msg: str = str(data).encode('utf-8') #fordítás a lora nyelvére
    SER.write(msg)
    time.sleep(CONTROLL_SLEEP)
    

def Radio_Init() -> None:
    Radio_Write('\r\n')
    Radio_Write('sys reset\r\n')
    Radio_Write('radio rx 0\r\n')

def run():
    # TODO make the package sending code
    pass