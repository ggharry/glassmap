#Basic imports
from ctypes import *
import sys
import math
#Phidget specific imports
from Phidgets.Phidget import Phidget
from Phidgets.PhidgetException import PhidgetErrorCodes, PhidgetException
from Phidgets.Events.Events import SpatialDataEventArgs, AttachEventArgs, DetachEventArgs, ErrorEventArgs
from Phidgets.Devices.Spatial import Spatial, SpatialEventData, TimeSpan

#Create an accelerometer object
try:
    spatial = Spatial()
except RuntimeError as e:
    print("Runtime Exception: %s" % e.details)
    print("Exiting....")
    exit(1)

#Information Display Function
def DisplayDeviceInfo():
    print("|------------|----------------------------------|--------------|------------|")
    print("|- Attached -|-              Type              -|- Serial No. -|-  Version -|")
    print("|------------|----------------------------------|--------------|------------|")
    print("|- %8s -|- %30s -|- %10d -|- %8d -|" % (spatial.isAttached(), spatial.getDeviceName(), spatial.getSerialNum(), spatial.getDeviceVersion()))
    print("|------------|----------------------------------|--------------|------------|")
    print("Number of Acceleration Axes: %i" % (spatial.getAccelerationAxisCount()))
    print("Number of Gyro Axes: %i" % (spatial.getGyroAxisCount()))
    print("Number of Compass Axes: %i" % (spatial.getCompassAxisCount()))

#Event Handler Callback Functions
def SpatialAttached(e):
    attached = e.device
    print("Spatial %i Attached!" % (attached.getSerialNum()))

def SpatialDetached(e):
    detached = e.device
    print("Spatial %i Detached!" % (detached.getSerialNum()))

def SpatialError(e):
    try:
        source = e.device
        print("Spatial %i: Phidget Error %i: %s" % (source.getSerialNum(), e.eCode, e.description))
    except PhidgetException as e:
        print("Phidget Exception %i: %s" % (e.code, e.details))

def SpatialData(e):
    source = e.device
    # print("Spatial %i: Amount of data %i" % (source.getSerialNum(), len(e.spatialData)))
    for index, spatialData in enumerate(e.spatialData):

    	if len(spatialData.MagneticField) > 0 and len(spatialData.Acceleration) > 0:
	    	gravity = [spatialData.Acceleration[0], spatialData.Acceleration[1], spatialData.Acceleration[2]]
	    	magField = [spatialData.MagneticField[0], spatialData.MagneticField[1], spatialData.MagneticField[2]]

			# Roll Angle - about axis 0
			# tan(roll angle) = gy/gz
			# Use Atan2 so we have an output os (-180 - 180) degrees
	    	rollAngle = math.atan2(gravity[1],gravity[2])
	    	
			# Pitch Angle - about axis 1
			# tan(pitch angle) = -gx / (gy * sin(roll angle) * gz * cos(roll angle))
			# Pitch angle range is (-90 - 90) degrees
	    	pitchAngle = math.atan(-gravity[0] / ((gravity[1] * math.sin(rollAngle)) + (gravity[2] * math.cos(rollAngle))))

			# Yaw Angle - about axis 2
			# Use Atan2 to get our range in (-180 - 180)
			# Yaw angle == 0 degrees when axis 0 is pointing at magnetic north
	    	yawAngle = math.atan2((magField[2] * math.sin(rollAngle))- (magField[1] * math.cos(rollAngle)),(magField[0] * math.cos(pitchAngle))+ (magField[1] * math.sin(pitchAngle) * math.sin(rollAngle)) + (magField[2] * math.sin(pitchAngle) * math.cos(rollAngle)))
	    	
	    	angle = [rollAngle*180/math.pi, pitchAngle*180/math.pi, yawAngle*180/math.pi]

	    	print angle
    # print("------------------------------------------")

#Main Program Code
try:
    spatial.setOnAttachHandler(SpatialAttached)
    spatial.setOnDetachHandler(SpatialDetached)
    spatial.setOnErrorhandler(SpatialError)
    spatial.setOnSpatialDataHandler(SpatialData)
except PhidgetException as e:
    print("Phidget Exception %i: %s" % (e.code, e.details))
    print("Exiting....")
    exit(1)

print("Opening phidget object....")

try:
    spatial.openPhidget()
except PhidgetException as e:
    print("Phidget Exception %i: %s" % (e.code, e.details))
    print("Exiting....")
    exit(1)

print("Waiting for attach....")

try:
    spatial.waitForAttach(10000)
except PhidgetException as e:
    print("Phidget Exception %i: %s" % (e.code, e.details))
    try:
        spatial.closePhidget()
    except PhidgetException as e:
        print("Phidget Exception %i: %s" % (e.code, e.details))
        print("Exiting....")
        exit(1)
    print("Exiting....")
    exit(1)
else:
    spatial.setDataRate(4)
    # DisplayDeviceInfo()

print("Press Enter to quit....")

chr = sys.stdin.read(1)

print("Closing...")

try:
    spatial.closePhidget()
except PhidgetException as e:
    print("Phidget Exception %i: %s" % (e.code, e.details))
    print("Exiting....")
    exit(1)

print("Done.")
exit(0)