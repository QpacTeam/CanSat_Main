# === LOOP CONTROL ===
# Main loop run per second. It should be little to read serial signal effectively! (def: 1/600)
FREQUENCY: float = 0.00167
# The CPU sleep on every turn. It should be way smaller than the FREQUENCY! (def: 1/600)
CONTROL_SLEEP: float = 0.000167

# === DEFAULT SETTINGS ===
# Starting the command interface:
COMMAND_INTERFACE: str = "python3 Sender/Usr_input_promt.py 1"
# State-holder file:
STATE_FILE: str = "Sender/promt.txt"
# Recording file:
RECORDING_FILE: str = "Sender/recording_state.txt"
# The beginning state of the system:
DEFAULT_STATE: int = 2
# Recording state at the beginning:
DEFAULT_RECORDING: int = 0
# The text that prints default in the commandline:
DEFAULT_CLI_TEXT: str = "startup"

# === RADIO SETTINGS ===
# time to sleep, between signals (def: 0.2)
RADIO_SLEEP: float = 0.2

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
