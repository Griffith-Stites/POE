import serial

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

def parseData(data):
    """Parse one point of data
    data: One data point, raw from the arduino
    returns: x, y, z coordinate"""
    result = data.split(',') # split by comma into list
    return getCoord(result[0], result[1], result[2])

def getCoord(distance, angle1, angle2):
    """Determine the coordinate
    distance: distance from the laser
    angle1: angle on axis 1
    angle2: angle on axis 2

    returns: x, y, z coordinate"""
    return (distance, angle1, angle2)


serialPort = setupSerial()
# main loop to read data from the Arduino, then display it
dataList = [] # list of the raw analogRead, data1, data2
running = True
while running:
    data = checkData(serialPort)
    print(data)
    if (data == "finished"): # stop code from arduino
        running = False # stop the loop
    elif (data != "none"): # if there is a data point
        dataList.append(data)

points = [] #
for d in dataList:
    parseData(d)

# ask for a line of data from the serial port, the ".decode()" converts the
# data from an "array of bytes", to a string
lineOfData = serialPort.readline().decode()
# check if data was received
