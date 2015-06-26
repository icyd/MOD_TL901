from serial import Serial, PARITY_EVEN
import numpy
import matplotlib.pyplot as plt
from drawnow import *

temp=[]
cnt = 0
plt.ion()
serial = Serial('/dev/ttyUSB0',19200,timeout=10,parity=PARITY_EVEN)

def makeFig():
    plt.ylim(25,200)
    plt.title('Temperatura sensor')
    plt.grid(True)
    plt.ylabel('Temp C')
    plt.plot(temp, 'ro-', label='Grados Celcius')
    plt.legend(loc='upper left')

while True:
    while (serial.inWaiting()==0):
        pass
    buff = serial.read()
    temp.append(int.from_bytes(buff,'big'))
    drawnow(makeFig)
    plt.pause(0.000001)
    cnt=cnt+1
    if(cnt>100):
        temp.pop(0)

