import Utility
import time


def init() -> None:
    pass


def loop() -> None:
    from Variables import FREQUENCY, CONTROL_SLEEP, Main_State
    import Server_Run as server

    act_time: float
    sleep_time: float
    pas_time: float = time.time()

    while 1:
        # Loop-control
        act_time = time.time()
        dif_time = act_time - pas_time

        if not dif_time < FREQUENCY:
            pas_time = act_time + (dif_time - FREQUENCY)

            # Main state machine
            match Main_State:
                case 1:
                    # Starts the server
                    server.run()
                    pass
                case 0:
                    print("exit_code:0")
                    break

        time.sleep(CONTROL_SLEEP)  # < loop sleep to optimize


if __name__ == "__main__":
    init()
    loop()
