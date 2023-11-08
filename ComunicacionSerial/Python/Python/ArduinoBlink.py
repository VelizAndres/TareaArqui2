import pyfirmata
import time
# COM6 = Puerto donde se conecta el arduino
board = pyfirmata.Arduino('COM3') 

while True:
    board.digital[13].write(1)
    time.sleep(4)
    board.digital[13].write(0)
    time.sleep(4)
    