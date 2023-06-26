import matplotlib.pyplot as plt
import sys

# read in the data
with open(sys.argv[1], "r") as f:
    data = f.read()

data = data.split('\n')
celestial_bodies = int(data[0])
timesteps = int(float(data[1]))
labels = data[2]
names = data[3:3+celestial_bodies]
offset = 3 + celestial_bodies

minVals = [ float(x) for x in data[-2].split(' ') ]
maxVals = [ float(x) for x in data[-1].split(' ') ]

show_labels = False

if labels == "true":
    show_labels = True

# create the 3d graph
fig = plt.figure(figsize=(6,6))
ax = fig.add_subplot(111, projection='3d')

# start the animation
for i in range(timesteps):
    try:
        for j in range(celestial_bodies):
            pos = data[i*celestial_bodies+j+offset].split(' ') # add 3 to j because first 3 values are number of bodies and timesteps
            pos = [ float(x) for x in pos]
            ax.plot(pos[0], pos[1], pos[2], marker='o', markersize=(10 if j == 0 else 6))
            if show_labels:
                ax.text(pos[0], pos[1], pos[2], names[j])

        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        ax.set_xlim([minVals[0], maxVals[0]])
        ax.set_ylim([minVals[1], maxVals[1]])

        if minVals[2] != maxVals[2]:
            ax.set_zlim([minVals[2], maxVals[2]])


        plt.pause(0.00001)
        ax.clear()
    except KeyboardInterrupt:
        exit(0)
