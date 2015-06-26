from serial import Serial, PARITY_EVEN
import numpy
import matplotlib.pyplot as plt
from drawnow import *

temp=[]
temp_filter=[]
cnt = 0
plt.ion()
serial = Serial('/dev/ttyUSB0',19200,timeout=10,parity=PARITY_EVEN)

def makeFig():
    plt.ylim(25,60)
    plt.title('Temperatura sensor')
    plt.grid(True)
    plt.ylabel('Temp C')
    plt.plot(temp, 'ro-', label='Grados Celcius')
    plt.legend(loc='upper left')
    plt2=plt.twinx()
    plt.ylim(25,60)
    plt2.plot(temp_filter, 'b^-', label='Filtered')
    plt2.set_ylabel('Filtered')
    plt2.ticklabel_format(useOffset=False)
    plt2.legend(loc='upper right')

while True:
    while (serial.inWaiting()==0):
        pass
    buff = serial.read(size=2)
    buff_1 = buff[0]
    buff_2 = buff[1]
    #temp.append(int.from_bytes(buff_1,'big'))
    #temp_filter.append(int.from_bytes(buff_2,'big'))
    temp.append(buff_1)
    temp_filter.append(buff_2)
    drawnow(makeFig)
    plt.pause(0.000001)
    cnt=cnt+1
    if(cnt>100):
        temp.pop(0)
        temp_filter.pop(0)

