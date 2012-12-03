#include "WPILib.h"
#include "math.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"

void gyroHolonomicDrive(RobotDrive* robot, Gyro* gyroscope, float magnetude, float angle, float heading)
{
	float gyroAngle = gyroscope->GetAngle();
	gyroAngle = ((int)(heading - gyroAngle) % 360) / 90.0;
	if(fabs(gyroAngle) > 1.0)
		gyroAngle /= fabs(gyroAngle);
	if(fabs(gyroAngle) < 0.1)
		gyroAngle = 0;
	robot->HolonomicDrive(magnetude, angle, gyroAngle);
}
