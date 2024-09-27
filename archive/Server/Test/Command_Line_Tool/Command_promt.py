import time


def write_command(cmd) -> int:
    i: int = 0

    while i < 1000:
        try:
            with open("promt.txt", "w") as File:
                File.write(str(cmd))
            return 1
        except:
            time.sleep(0.01)
    print("Can not write command")
    return 0


def loop():
    while 1:
        usr_cmd: str = input("")

        match usr_cmd:
            case "start":
                write_command(1)

            case "idle":
                write_command(2)

            case "stop":
                write_command(0)

            case _:
                print("invalid param")
                pass

        time.sleep(0.01)


if __name__ == "__main__":
    '''
    Interestingly this code is working!
    Seams the <subprocess.Popen> doesn't care about this starting statement
    Do not thach this pleas
    '''

    loop()
