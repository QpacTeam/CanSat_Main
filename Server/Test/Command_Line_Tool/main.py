import subprocess
import time
from icecream import ic     # < debug tool

COMMAND: str = "python3 Command_promt.py 1"
STATE_LIST: list[int] = [1, 2]

def init():

    ic(subprocess.Popen(COMMAND, shell=True))

    try:
        with open("promt.txt", "r") as File:
            ic(File)
            data = int(File.readline())

        if data not in STATE_LIST:
            with open("promt.txt", "w") as File:
                ic(File)
                File.write(str(2))
    except:
        with open("promt.txt", "w") as File:
            File.write(str(2))


def get_mode() -> int:
    try:
        with open("promt.txt", "r") as File:
            data = File.readline()
            return int(data)
    except:
        return 999


def loop():
    while 1:
        mode: int = get_mode()
        match mode:
            case 0:  # < break
                break
            case 1:  # < RUN
                ...
            case 2:  # < Idle
                ...
            case _:
                pass
        time.sleep(0.1)


if __name__ == "__main__":  # << Starting sequence
    init()
    time.sleep(0.5)
    loop()
