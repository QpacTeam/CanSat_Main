# === LOOP CONTROL ===
# Main loop run per second. It should be little to read serial signal effectively! (def: 1/600)
FREQUENCY: float = 0.00167
# The CPU sleep on every turn. It should be way smaller than the FREQUENCY! (def: 1/600)
CONTROL_SLEEP: float = 0.000167

# === DEFAULT SETTINGS ===
# Starting the command interface:
COMMAND_INTERFACE: str = "python3 Sender/Usr_input_promt.py 1"
# State-holder file:
STATE_FILE_LOCATION: str = "Sender/Data/promt.txt"
# Recording file:
RECORDING_FILE_LOCATION: str = "Sender/Data/recording_state.txt"
# The beginning state of the system:
DEFAULT_STATE: int = 2
# Recording state at the beginning:
DEFAULT_RECORDING: int = 0
# The text that prints default in the commandline:
DEFAULT_CLI_TEXT: str = "startup"

# === RADIO SETTINGS ===
# Time to sleep, between signals (def: 0.2)
RADIO_SLEEP: float = 0.2
# The port where the server gets hosted:
DEFAULT_RADIO_PORT: int = 9999
# radio_port.txt file location:
RADIO_PORT_FILE_LOCATION: str = "Sender/Data/radio_port.txt"
# Port where the LoRa located:
SERIAL_FILE: str = "/dev/ttyS0"

# === CML HELP ===
CML_HELP = '''
    start           starting sending packages
    idle            stops the process and waiting for new command (Default)
    stop or exit    exits the program
    help            bring upp this text
'''

CML_ENCODE: dict = {
    0: "stop",
    1: "run",
    2: "idle",
    66: "restarted"
}
