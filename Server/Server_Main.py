import Utility
import time

# Ha valamelyik function elé odaírod, ezt, akkor le tudod mérni annak a lefutási idejét.
#
# @Utility.timer
# def func()
#    pass

# Így sokkal átláthatóbb, és hatékonyabb lesz a kód, sőt még a pycharm is visít, ha valamit elgyeszel
Main_Over: bool = False
MAIN_FREQUENCY: float = 1000

def Init():
    pass

def Main():
    Init()      # << Setting everything to default
    Main_del_Time: float = 0
    Main_act_Time: float = time.time()

    while 1:
        if Main_del_Time >= MAIN_FREQUENCY:
            pass


            # Main code


            Main_act_Time = time.time()
        if Main_Over:
            break

        Main_del_Time = time.time() - Main_act_Time
        time.sleep(0.002)   # << Hogy ne hajtsuk túl a CPU-t
    return

if __name__ == "__main__":
    Main()