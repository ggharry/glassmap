#include "compass.h"

int READ_COMPASS_INTERVAL = 200;

//callback that will run if the Spatial is attached to the computer
int CCONV AttachHandler(CPhidgetHandle spatial, void *userptr)
{
	int serialNo;
	CPhidget_getSerialNumber(spatial, &serialNo);
	printf("Spatial %10d attached!", serialNo);

	return 0;
}

//callback that will run if the Spatial is detached from the computer
int CCONV DetachHandler(CPhidgetHandle spatial, void *userptr)
{
	int serialNo;
	CPhidget_getSerialNumber(spatial, &serialNo);
	printf("Spatial %10d detached! \n", serialNo);

	return 0;
}

//callback that will run if the Spatial generates an error
int CCONV ErrorHandler(CPhidgetHandle spatial, void *userptr, int ErrorCode, const char *unknown)
{
	printf("Error handled. %d - %s \n", ErrorCode, unknown);
	return 0;
}

int CCONV SpatialDataHandler(CPhidgetSpatialHandle spatial, void *userptr, CPhidgetSpatial_SpatialEventDataHandle *data, int count)
{	

	int i;
	printf("Number of Data Packets in this event: %d\n", count);
	for(i = 0; i < count; i++)
	{
		double gravity[] = {
		data[i]->acceleration[0],
		data[i]->acceleration[1],
		data[i]->acceleration[2]
		};

		double magField[] = {
		data[i]->magneticField[0], 
		data[i]->magneticField[1], 
		data[i]->magneticField[2]};

		double rollAngle = atan2(gravity[1], gravity[2]);

		double pitchAngle = atan(-gravity[0] / ((gravity[1] * sin(rollAngle)) + (gravity[2] * cos(rollAngle))));

		double yawAngle = atan2(
		   (magField[2] * sin(rollAngle))- (magField[1] * cos(rollAngle)),
		   (magField[0] * cos(pitchAngle)) + (magField[1] * sin(pitchAngle) * sin(rollAngle)) + (magField[2] * sin(pitchAngle) * cos(rollAngle))
			);

		double angles[] = {rollAngle*180/M_PI, pitchAngle*180/M_PI, yawAngle*180/M_PI};

		if (angles[2] < 0){
			angles[2] = 360-(angles[2] * -1);
		}

		printf("Roll: %6f, Pitch: %6f, Yaw: %6f", angles[0], angles[1], angles[2]);
		
		// Set the global variable
		_angle = angles[2];
		
	}

	

	printf("---------------------------------------------\n");

	return 0;
}

//Display the properties of the attached phidget to the screen.  
//We will be displaying the name, serial number, version of the attached device, the number of accelerometer, gyro, and compass Axes, and the current data rate
// of the attached Spatial.
int display_properties(CPhidgetHandle phid)
{
	int serialNo, version;
	const char* ptr;
	int numAccelAxes, numGyroAxes, numCompassAxes, dataRateMax, dataRateMin;

	CPhidget_getDeviceType(phid, &ptr);
	CPhidget_getSerialNumber(phid, &serialNo);
	CPhidget_getDeviceVersion(phid, &version);
	CPhidgetSpatial_getAccelerationAxisCount((CPhidgetSpatialHandle)phid, &numAccelAxes);
	CPhidgetSpatial_getGyroAxisCount((CPhidgetSpatialHandle)phid, &numGyroAxes);
	CPhidgetSpatial_getCompassAxisCount((CPhidgetSpatialHandle)phid, &numCompassAxes);
	CPhidgetSpatial_getDataRateMax((CPhidgetSpatialHandle)phid, &dataRateMax);
	CPhidgetSpatial_getDataRateMin((CPhidgetSpatialHandle)phid, &dataRateMin);

	

	printf("%s\n", ptr);
	printf("Serial Number: %10d\nVersion: %8d\n", serialNo, version);
	printf("Number of Accel Axes: %i\n", numAccelAxes);
	printf("Number of Gyro Axes: %i\n", numGyroAxes);
	printf("Number of Compass Axes: %i\n", numCompassAxes);
	printf("datarate> Max: %d  Min: %d\n", dataRateMax, dataRateMin);

	return 0;
}

int spatial_simple()
{
	int result;
	const char *err;

	//Declare a spatial handle
	CPhidgetSpatialHandle spatial = 0;

	//create the spatial object
	CPhidgetSpatial_create(&spatial);

	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)spatial, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)spatial, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)spatial, ErrorHandler, NULL);

	//Registers a callback that will run according to the set data rate that will return the spatial data changes
	//Requires the handle for the Spatial, the callback handler function that will be called, 
	//and an arbitrary pointer that will be supplied to the callback function (may be NULL)
	CPhidgetSpatial_set_OnSpatialData_Handler(spatial, SpatialDataHandler, NULL);

	//open the spatial object for device connections
	CPhidget_open((CPhidgetHandle)spatial, -1);

	//get the program to wait for a spatial device to be attached
	printf("Waiting for spatial to be attached.... \n");
	if((result = CPhidget_waitForAttachment((CPhidgetHandle)spatial, 10000)))
	{
		CPhidget_getErrorDescription(result, &err);
		printf("Problem waiting for attachment: %s\n", err);
		return 0;
	}

	//Display the properties of the attached spatial device
	display_properties((CPhidgetHandle)spatial);

	//read spatial event data
	printf("Reading.....\n");
	
	//Set the data rate for the spatial events
	CPhidgetSpatial_setDataRate(spatial, READ_COMPASS_INTERVAL);

	return 0;
}



