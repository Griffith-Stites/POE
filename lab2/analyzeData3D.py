import serial
import numpy as np
import pickle

def analogToDistance(analog):
    """Convert an analog reading from the IR
    distance sensor to inches
    analog: Analog reading
    returns: distance in inches"""
    return 5805.99102955023*(analog**-1.03380467328515)

def getSpherical(data):
    """Determine the polar coordinate from one point of data
    data: one line of data with distance, pan, and tilt
    returns: spherical coordinate as tuple"""
    result = data.split(',') # split by comma into list
    radius = analogToDistance(float(result[0]))
    pan = np.radians(int(result[1])) # pan angle in rads
    tilt = np.radians(int(result[2])) # tilt angle in rads
    return (radius, pan, tilt)

def sphericalToCart(polar):
    """Convert spherical coordinates to cartesion coordinates.
    polar: tuple with radius, pan, tilt angle in radians
    returns: cartesion coordinate as tuple"""
    radius, pan, tilt = polar
    x = radius * np.sin(tilt) * np.cos(pan)
    y = radius * np.sin(tilt) * np.sin(pan)
    z = radius * np.cos(tilt)
    return(x, y, z)

def saveData(data):
    """Convert the data to coordinates and save to a file"""
    points = []
    for d in data:
        sphere = getSpherical(d)
        a = sphericalToCart(sphere)
        points.append(a)
        print(a)
    f = open('lab2/data.txt', 'wb') # create file
    pickle.dump(points, f)
    # Need to save data to a file than analyze

data = []
with open('lab2/dataRaw', 'rb') as openfile:
    while True:
        try:
            data.append(pickle.load(openfile))
        except EOFError:
            break
data = data[0]
saveData(data)

# Plot known coordinates, data input

# print(getSpherical("422, 20, 20"))
# print(sphericalToCart(getSpherical("422, 20, 20")))
