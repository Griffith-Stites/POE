import serial
import numpy as np

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

def getPolar(data):
    """Determine the polar coordinate from one point of data
    distance: distance from the laser
    pan: pan angle
    tilt: tilt angle
    returns: polar coordinate"""
    result = data.split(',') # split by comma into list
    rho = analogToDistance(float(result[0]))
    phi = float(result[1])

    return (rho, phi) # only returning 2d, will need spherical

def polarToCart(rho, phi):
    x = rho * np.cos(phi)
    y = rho * np.sin(phi)
    return(x, y)

def acquireData(serialPort):
    """Acquire data from the arduino"""
    dataList = [] # list of the raw analogRead, data1, data2
    running = True
    while running:
        data = checkData(serialPort)
        # print(data)
        if (data == "finished"): # stop code from arduino
            running = False # stop the loop
        elif (data != "none"): # if there is a data point
            dataList.append(data)
    return dataList

def saveData(dataList):
    """Convert the data to coordinates and save"""
    points = []
    for d in dataList:
        rho, phi = getPolar(d)
        points.append(polarToCart(rho, phi))

    # Need to save data to a file than analyze

serialPort = setupSerial()
dataList = acquireData(serialPort)
savaData(dataList)
