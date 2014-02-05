#include <phidget21.h>

// Definitions
#define sampleFreq	62.5f		// sample frequency in Hz
#define betaDef		0.0001f		// 2 * proportional gain

//---------------------------------------------------------------------------------------------------
// Variable definitions
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;	// quaternion of sensor frame relative to auxiliary frame
volatile float beta = betaDef;								// 2 * proportional gain (Kp)

//---------------------------------------------------------------------------------------------------
// Function declarations
float invSqrt(float x);
void getEuler(float * angles);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);

int CCONV AttachHandler(CPhidgetHandle spatial, void *userptr);
int CCONV DetachHandler(CPhidgetHandle spatial, void *userptr);
int CCONV ErrorHandler(CPhidgetHandle spatial, void *userptr, int ErrorCode, const char *unknown);
int CCONV SpatialDataHandler(CPhidgetSpatialHandle spatial, void *userptr, CPhidgetSpatial_SpatialEventDataHandle *data, int count);
int display_properties(CPhidgetHandle phid);
int spatial_simple();

