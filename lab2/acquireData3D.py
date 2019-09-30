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

def acquireData(serialPort):
    """Acquire data from the arduino"""
    dataList = [] # list of the raw analogRead, data1, data2
    running = True
    while running:
        data = checkData(serialPort)
        print(data)
        if (data == "finished"): # stop code from arduino
            running = False # stop the loop
        elif (data != "none"): # if there is a data point
            dataList.append(data)
    return dataList

def saveData(dataList):
    """Save the raw data to a file"""
    f = open('lab2/dataRaw', 'wb') # create file
    pickle.dump(dataList, f)
    # Need to save data to a file than analyze

serialPort = setupSerial()

wait = True
while wait:
    data = checkData(serialPort)
    if (data == "start"):
        wait = False

dataList = acquireData(serialPort)
saveData(dataList)
