import serial
import time

imp = ''

SERIAL = serial.Serial(port="/dev/ttyACM0", baudrate=9600)

while 1:
