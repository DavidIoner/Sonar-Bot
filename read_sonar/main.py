import json
import re

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import serial

ser = serial.Serial('COM3', 9600)
if ser:
    print('conectado a porta COM')

matplotlib.use('TkAgg')

# Set title and background
fig = plt.figure("Radar Scanner", facecolor='black')
dpi = 180
fig.set_dpi(dpi)  # Set resolution of figure
win = fig.canvas.manager.window # figure window
screen_res = win.wm_maxsize() # used for window formatting later
# Add polar plot radar
ax = fig.add_subplot(111, polar=True, facecolor='#288526')

# Position of the radar
ax.set_position([-0.05, -0.05, 1.1, 1.05])

# Radar form
ax.set_ylim([0.0, 100])  # Default radar radius set to 100 cm
ax.set_xlim([0.0, np.pi])  # Create semi circle

# Display 7 angles for 0 to 180 degrees
ax.set_thetagrids(np.linspace(0.0, 180.0, 7))

# Styling
ax.tick_params(axis='both', colors='w')  # Set text colour
ax.grid(which='major', color='#75d950', linestyle='-', alpha=0.5)  # Set grid colour
points, = ax.plot([], linestyle='', marker='.', markerfacecolor='#f1fff1', markeredgecolor='w', markersize=8.0)  # Set points style
line, = ax.plot([], color='#79f07b', linewidth=3.0)  # Set radar line style

# Variables
angles = np.arange(0, 181, 1)  # 0 to 180 degrees
theta = angles * (np.pi / 180.0)  # Angle to radians
distances = np.ones((len(angles),))  # Initial distances

fig.set_size_inches(0.96*(screen_res[0]/dpi),0.96*(screen_res[1]/dpi))
plot_res = fig.get_window_extent().bounds # window extent for centering
win.wm_geometry('+{0:1.0f}+{1:1.0f}'.\
                format((screen_res[0]/2.0)-(plot_res[2]/2.0),
                       (screen_res[1]/2.0)-(plot_res[3]/2.0))) # centering plot

fig.canvas.toolbar.pack_forget()  # Remove unused tools

fig.canvas.draw()  # Draw canvas

axbackground = fig.canvas.copy_from_bbox(ax.bbox)  # Background
fig.show()  # Display figure
angle = 0
distance = 0
while True:

    line = ser.readline().decode("utf-8")
    if line:
        match = re.search(r'\{.*\}', str(line))
        if match:
            json_recebido = match.group()
            dados_json = json.loads(json_recebido)
            angle = dados_json['angulo']
            distance = dados_json['distancia']
            print(angle, distance)

            distances[int(angle)] = distance

            points.set_data(theta, distances)  # Points
            fig.canvas.restore_region(axbackground)  # Redraw background
            ax.draw_artist(points)  # Add points

            line.set_data(np.repeat((angle * (np.pi / 180.0)), 2),  # Draw line from 0 to 180 degrees
                        np.linspace(0.0, 100, 2))  # Draw line for 100 cm distance
            ax.draw_artist(line)  # Draw radar line

            fig.canvas.blit(ax.bbox)  # Re-plot data
            fig.canvas.flush_events()  # Flush GUI events

    
