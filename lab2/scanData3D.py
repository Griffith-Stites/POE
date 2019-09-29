import serial
import numpy as np
import pickle

def setupSerial(arduinoComPort = "/dev/ttyACM0", baudRate = 9600):
    """Open the serial port"""
    return serial.Serial(arduinoComPort, baudRate, timeout=1)

def checkData(serialPort):
    """Check the data on the serial port
    serialPort: Serial port to check
    returns: data from the serial port"""
    lineOfData = serialPort.readline().decode()
    if len(lineOfData) > 0:
        return lineOfData.rstrip() # return without any whitespace
    else:
        return "none"

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

def acquireData(serialPort):
    """Acquire data from the arduino"""
    dataList = [] # list of the raw analogRead, data1, data2
    running = True
    while running:
        data = checkData(serialPort)
        # print(data)
        print(data)
        if (data == "finished"): # stop code from arduino
            running = False # stop the loop
        elif (data != "none"): # if there is a data point
            dataList.append(data)
    return dataList

def saveData(dataList):
    """Convert the data to coordinates and save to a file"""
    points = []
    for d in dataList:
        sphere = getSpherical(d)
        points.append(sphericalToCart(sphere))
    f = open('lab2/data.txt', 'wb') # create file
    pickle.dump(points, f)
    # Need to save data to a file than analyze

serialPort = setupSerial()

wait = True
while wait:
    data = checkData(serialPort)
    if (data == "start"):
        wait = False

dataList = acquireData(serialPort)
saveData(dataList)
