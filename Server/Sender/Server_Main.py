import time
import subprocess
import Utility              # < debug tool
from icecream import ic     # < debug tool


def init() -> bool:     # << Set
    from Server_Variables import COMMAND_INTERFACE, DEFAULT_STATE, STATE_FILE

    try:
        with open(STATE_FILE, "w") as File:
            ic(File)
            File.write(str(DEFAULT_STATE))

        ic(subprocess.Popen(COMMAND_INTERFACE, shell=True))  # < Starting the command interface
        return True
    except:
        print("File unreachable (somehow...)")
        return False


def loop() -> None:
    from Server_Variables import FREQUENCY, CONTROL_SLEEP
    import Server_Run as Server

    act_time: float
    sleep_time: float
    pas_time: float = time.time()

    while 1:
        # Loop-control
        act_time = time.time()
        dif_time = act_time - pas_time

        if not dif_time < FREQUENCY:
            pas_time = act_time + (dif_time - FREQUENCY)

            state: int = Server.Get_Operation_Mode()

            # Main state machine
            match state:
                case 1:
                    Server.run()    # < Runs the server

                case 2: # << Idle
                    pass

                case 66:
                    init()      # < Reset the server

                case 0:         # < Exit the process
                    break

                case _:
                    pass

        time.sleep(CONTROL_SLEEP)  # << loop sleep to optimize


if __name__ == "__main__":  # << Starting sequence
    if init():
        loop()
