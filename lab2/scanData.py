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
    # return 5805.99102955023*(analog**-1.03380467328515)
    return 2213662.429886*(analog**-2.0598068054896)
    
def getPolar(data):
    """Determine the polar coordinate from one point of data
    distance: distance from the laser
    pan: pan angle in degrees
    tilt: tilt angle in degrees
    returns: polar coordinate"""
    result = data.split(',') # split by comma into list
    radius = analogToDistance(float(result[0]))
    pan = int(result[1])
    print (radius, pan)
    return (radius, pan) # only returning 2d, will need spherical

def polarToCart(radius, pan):
    x = radius * np.cos(np.radians(pan))
    y = radius * np.sin(np.radians(pan))
    return(x, y)

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
        radius, pan = getPolar(d)
        points.append(polarToCart(radius, pan))
    f = open('lab2/data.txt', 'wb') # create file
    pickle.dump(points, f)
    # Need to save data to a file than analyze

    file = open('raw.txt', 'w')
    file.write(str(dataList))
    file.close()

serialPort = setupSerial()

wait = True
while wait:
    data = checkData(serialPort)
    if (data == "start"):
        wait = False

dataList = acquireData(serialPort)
saveData(dataList)
