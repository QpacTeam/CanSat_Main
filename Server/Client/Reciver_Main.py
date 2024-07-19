import time


def init() -> None:     # << Set
    pass


def loop():
    from Reciver_Variables import Main_State
    package_counter: int = 0
    while 1:

        # TODO receiving packages continuously

        # TODO draw data

        match Main_State:
            case 1:
                pass
            case 2:
                pass
            case 3:
                pass
            case 4:
                pass
            case 66:
                init()
                pass
            case 0:
                print("exit_code:0")  # << Exit the process
                break
            case _:
                pass


if __name__ == "__main__":  # << Starting sequence
    init()
    loop()
