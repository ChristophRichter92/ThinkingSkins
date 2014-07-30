import serial
import time

port = serial.Serial("/dev/ttyUSB9", 9600)
port.write("on()\n")
port.write("present()\n")
time.sleep(17)
port.write("changeColor(255,0,0)\n")
port.write("present()\n")
time.sleep(17)
port.write("changeColor(0,255,0)\n")
port.write("present()\n")
time.sleep(17)
port.write("changeColor(0,0,255)\n")
port.write("present()\n")
time.sleep(17)
port.write("off()\n")
port.close()
