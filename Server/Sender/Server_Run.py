from Server_Variables import STATE_FILE


def Get_Operation_Mode() -> int:
    try:
        with open(STATE_FILE, "r") as File:
            data = File.readline()
            return int(data)
    except:
        return 999



def run():
    # TODO make the package sending code
    pass