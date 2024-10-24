from icecream import ic
import socket as soc
import time
from time import strftime, gmtime
# import graph
import antiparcer
from Variables import USE_TIME_SIGNO, SAVE_FILE_LOCATION, DEFAULT_SAVE_NAME, DEFAULT_PORT, CTL_SLEEP


HOST: str = '192.168.0.33'
PORT: int = DEFAULT_PORT
socket = soc.socket(soc.AF_INET, soc.SOCK_STREAM)

socket.connect((HOST, PORT))

# temp_alt = graph.Function(2, [[0, 1500], [-10, 40]])          # The fuck dude?!
act_data_list = []
graphs_list = []


# === INIT ===
if USE_TIME_SIGNO:
    T = f"{strftime('%Y_%b_%d_%H_%M_%S', gmtime(time.time()))}"
    File_Name = f"{SAVE_FILE_LOCATION}/{T}"
    with open(File_Name, "w") as File:
        File.write("BEGIN\n")
else:
    File_Name = f"{SAVE_FILE_LOCATION}/{DEFAULT_SAVE_NAME}"
    with open(File_Name, "w") as File:
        File.write("BEGIN\n")

save_time = time.time()


# === ADDING FUNCTIONS === TODO make the graphs
#graphs_list.append(graph.Function(3, [9, 1, 1]))


# === MAIN LOOP ===
while 1:
    line = socket.recv(1024).decode("utf-8")
    socket.send("device1".encode('utf-8'))
    # line = "radio_rx 03170100000000000000000000000000000000279309727156"
    act_data_list = antiparcer.antiparcer_data(line, File_Name)
    passed_time: float = time.time() - save_time

    act_data_list.append(passed_time)

    ic(graphs_list)

    for figure in graphs_list:
        ab: list = figure.attributes

        if figure.dimension == 3:
            figure.update([act_data_list[ab[0]], act_data_list[ab[1]], act_data_list[ab[2]]])

        if figure.dimension == 2:
            figure.update([act_data_list[ab[0]], act_data_list[ab[1]]])

        figure.draw()

    time.sleep(CTL_SLEEP)       # < For performance

graph.End()
