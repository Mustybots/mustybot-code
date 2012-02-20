#include "WPILib.h"
#include "math.h"
class RobotDemo : public SimpleRobot
{
	Joystick stick;
	Jaguar FL,FR,BL,BR;
public:
	RobotDemo(void):
		stick(1, 3, 12),
		FL(3),
		FR(5),
		BL(4),
		BR(6)
	{
	}

#include "mecanumDrive.h"

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
			if (yJoy != 0)
				angleJoy = 90 - yJoy / fabs(yJoy) * acos(xJoy / magJoy);
			else
				if (yJoy >= 0)
					angleJoy = 90;
				else
					angleJoy = - 90;
			if (angleJoy > 180)
				angleJoy -= 360;
			
			mecanumDrive(magJoy, angleJoy, twistJoy); 
			
			
			
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
