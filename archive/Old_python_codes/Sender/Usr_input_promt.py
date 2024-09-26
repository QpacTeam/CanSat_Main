import time
from Server_Variables import CONTROL_SLEEP, DEFAULT_CLI_TEXT, CML_ENCODE, CML_HELP, STATE_FILE_LOCATION


def write_command(cmd) -> int:

    for i in range(1000):   # < Try 1000 times to avoid things like "Oh no! I can't write"
        try:
            with open(STATE_FILE_LOCATION, "w") as File:
                File.write(str(cmd))
            return 1
        except:
            time.sleep(CONTROL_SLEEP)
    print("Can not write command")
    return 0


def Command_Line_feadback(cmd) -> str:
    return CML_ENCODE[cmd]


def loop():
    CML_text: str = DEFAULT_CLI_TEXT

    while 1:
        print(f"[SERVER:{CML_text}]: ", end="")
        usr_cmd: str = input().lower()

        match usr_cmd:
            case "start":
                write_command(1)
                CML_text = Command_Line_feadback(1)

            case "idle":
                write_command(2)
                CML_text = Command_Line_feadback(2)

            case "stop":
                write_command(0)
                CML_text = Command_Line_feadback(0)
            case "exit":
                write_command(0)
                CML_text = Command_Line_feadback(0)

            case "help":
                print(CML_HELP)

            case "saving":
                ...  # TODO

            case _:
                print("invalid param")
                pass

        time.sleep(CONTROL_SLEEP)


if __name__ == "__main__":
    '''
    Interestingly this code is working!
    Seams the <subprocess.Popen> doesn't care about this starting statement at all...
    Do not thach this pleas!
    '''

    loop()
