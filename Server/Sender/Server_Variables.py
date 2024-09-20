# === LOOP CONTROL ===
# Main loop run per second
FREQUENCY: float = 1 / 60
# The CPU sleep on every turn. It should be way smaller than the FREQUENCY!
CONTROL_SLEEP: float = 1 / 600

# === DEFAULT SETTINGS ===
# Starting the command interface
COMMAND_INTERFACE: str = "python3 Sender/Usr_input_promt.py 1"
# State-holder file
STATE_FILE: str = "Sender/promt.txt"
# The beginning state of the system. Should be 1
DEFAULT_STATE: int = 2
# The text that prints default in the commandline:
DEFAULT_CLI_TEXT: str = "startup"

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
