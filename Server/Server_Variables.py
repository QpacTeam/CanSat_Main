# Main loop run per second
FREQUENCY: float = 1 / 60

# The CPU sleep on every turn. It should be way smaller than the FREQUENCY!
CONTROL_SLEEP: float = 1 / 600

# The beginning state of the system. Should be 1
Main_State: int = 1
