import time
import subprocess
import Server_Run as Server
# import Utility              # < debug tool
from icecream import ic  # < debug tool


def init() -> bool:
    from Server_Variables import COMMAND_INTERFACE, DEFAULT_STATE, STATE_FILE_LOCATION, RECORDING_FILE_LOCATION, \
        DEFAULT_RECORDING

    Server.Radio_Init()

    try:
        with open(STATE_FILE_LOCATION, "w") as File:  # < make the promt file if it isn't exist
            ic(File)
            File.write(str(DEFAULT_STATE))  # < Set the default state

        with open(RECORDING_FILE_LOCATION, "w") as File:  # < make the recording_state file if it isn't exist
            ic(File)
            File.write(str(DEFAULT_RECORDING))  # < Set the default recording

        ic(subprocess.Popen(COMMAND_INTERFACE, shell=True))  # < Starting the command interface
        return True
    except:
        print("File unreachable (somehow...)")  # < Nearly impossible statement
        return False


def loop() -> None:
    from Server_Variables import FREQUENCY, CONTROL_SLEEP, STATE_FILE_LOCATION, DEFAULT_STATE

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
                case 1:  # < Runs the server
                    Server.run()

                case 2:  # < Idle
                    pass

                case 66:  # < Reset the server
                    init()
                    try:
                        with open(STATE_FILE_LOCATION, "w") as File:
                            File.write(str(DEFAULT_STATE))
                    except:
                        pass

                case 0:  # < Exit the process
                    break

                case _:
                    pass

        time.sleep(CONTROL_SLEEP)  # < loop sleep for optimization


if __name__ == "__main__":  # << Starting sequence
    if init():
        loop()
