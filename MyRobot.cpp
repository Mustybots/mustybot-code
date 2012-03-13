#include "WPILib.h"
#include "math.h"

#define PI 3.1415926535897932384626433832795
#define E 2.71828182845904523536028747
#define G 9.80665
#define BALL_DRAG 0.5
#define SHOOTER_ANGLE PI / 180.0 * 45.0 //45 degrees
#define ROBOT_HEIGHT 2.0
#define HOOP_HEIGHT 8.0

class Mustybot : public SimpleRobot
{
	Joystick stick;
	Jaguar FL,FR,BL,BR;
	Victor LazySusan,LShooter,RShooter,ConvBelt;
	Relay LManip,RManip;
public:
	Mustybot(void):
		stick(1, 3, 12),
		FL(3),
		FR(5),
		BL(4),
		BR(6),
		LazySusan(7),
		LShooter(1),
		RShooter(2),
		ConvBelt(8),
		LManip(1,Relay::kBothDirections),
		RManip(2,Relay::kBothDirections)
	{
	}

#include "mustyLib.h"

	void Autonomous(void)
	{
	}
	void OperatorControl(void)
	{
		DriverStationLCD *output = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			float xJoy = - stick.GetRawAxis(1);
			float yJoy = - stick.GetRawAxis(2);
			float twistJoy = stick.GetRawAxis(3);
			
			xJoy = xJoy * fabs(xJoy) * fabs(xJoy);			
			yJoy = yJoy * fabs(yJoy) * fabs(yJoy);
			twistJoy = twistJoy * fabs(twistJoy) * fabs(twistJoy);
			
			float magJoy = sqrt(xJoy * xJoy + yJoy * yJoy);
			
			float angleJoy;
			if (yJoy != 0.0)
				angleJoy = PI / 2.0 - yJoy / fabs(yJoy) * acos(xJoy / magJoy);
			else
				if (yJoy >= 0.0)
					angleJoy = PI / 2.0;
				else
					angleJoy = - PI / 2.0;
			if (angleJoy > PI)
				angleJoy -= 2.0 * PI;
			
			LazySusan.Set(xJoy);
			
			mecanumDrive(magJoy, angleJoy, twistJoy); 
			
			//getV_0(distance_to_the_bottom_of_the_hoop);
						
			output->Printf(DriverStationLCD::kMain_Line6, 9, "%7.1f", xJoy);
			output->Printf(DriverStationLCD::kUser_Line2, 9, "%7.1f", yJoy);
			output->Printf(DriverStationLCD::kUser_Line3, 9, "%7.1f", twistJoy);
			output->Printf(DriverStationLCD::kUser_Line4, 9, "%7.1f", magJoy);
			output->Printf(DriverStationLCD::kUser_Line5, 9, "%7.1f", angleJoy);
			output->Printf(DriverStationLCD::kUser_Line1, 1, "Axis 1");
			output->Printf(DriverStationLCD::kUser_Line2, 1, "Axis 2");
			output->Printf(DriverStationLCD::kUser_Line3, 1, "Axis 3");
			output->Printf(DriverStationLCD::kUser_Line4, 1, "Magnitude");
			output->Printf(DriverStationLCD::kUser_Line5, 1, "Angle");
			output->UpdateLCD();
			
			
		}
	}
};

START_ROBOT_CLASS(Mustybot);
