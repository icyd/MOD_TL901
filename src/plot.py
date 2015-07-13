import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import Cursor

# from serial import Serial, PARITY_EVEN


# try:
#     serial = Serial('/dev/ttyUSB0', 19200, timeout=2, parity=PARITY_EVEN)
# except:
#     print('Port can not be open!')
#     exit()

class PlotData:
    def __init__(self, N):
        self.count = 0
        self.x = np.array([i for i in range(N)])
        self.y = np.zeros(N)
        self.y2 = np.zeros(N)
        self.step = 0

    def incCount(self):
        self.count = self.count + 1

    def updData(self, d, ax):
        self.incCount()
        if(self.count < len(self.x)):
            self.y = np.delete(self.y, self.count)
            self.y2 = np.delete(self.y2, self.count)
            self.y = np.insert(self.y, self.count, d)
            self.y2 = np.insert(self.y2, self.count, self.step)
        else:
            self.x = np.delete(self.x, 0)
            self.x = np.append(self.x, self.count)
            self.y = np.delete(self.y, 0)
            self.y = np.append(self.y, d)
            self.y2 = np.delete(self.y2, 0)
            self.y2 = np.append(self.y2, self.step)
            ax.set_xlim(self.count - 900, self.count)


fig, ax1 = plt.subplots()
data = PlotData(900)
line1, = ax1.plot([], [], 'k-', label='Input')
ax2 = ax1.twinx()
line2, = ax2.plot([], [], 'b-', label='Temp')
ax1.set_title('Sensor data')
ax1.set_xlabel('t (seg)')
ax1.set_ylabel('Input (%)')
ax2.set_ylabel('Temp (ºC)')
ax2.set_ylim(0, 170)
ax1.set_ylim(0, 30)
ax1.set_xlim(0, 900)
lines = [line1, line2]
ax1.legend(lines, [l.get_label() for l in lines], loc=0, ncol=2)


def keypress(event):
    if(event.key == 'z'):
        data.step = 5
        line2.set_color('green')
    elif(event.key == 'x'):
        data.step = 10
        line2.set_color('orange')
    elif(event.key == 'c'):
        data.step = 15
        line2.set_color('red')
    else:
        data.step = 0
        line2.set_color('blue')
    ax1.legend(lines, [l.get_label() for l in lines], loc=0, ncol=2)

fig.canvas.mpl_connect('key_press_event', keypress)
cursor = Cursor(ax2, useblit=True, color='purple', linewidth=2)
ax1.grid(True)


def animate(num):
    # buff = serial.read()
    # data.updData(buff, ax1)
    data.updData((num/900*160), ax1)
    line2.set_data(data.x, data.y)
    line1.set_data(data.x, data.y2)
    return line1, line2,

anim = animation.FuncAnimation(fig, animate, frames=900,
                               interval=20, blit=False)
plt.show()
