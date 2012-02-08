#include "WPILib.h"
#include "math.h"
/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick

public:
	RobotDemo(void):
		myRobot(3, 4, 5, 6),	// these must be initialized in the same order
		stick(1, 3, 12)		// as they are declared above.
	{
		myRobot.SetInvertedMotor(myRobot.kFrontLeftMotor, true);
		myRobot.SetInvertedMotor(myRobot.kRearLeftMotor, true);
		myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		myRobot.SetSafetyEnabled(true);
		DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
		while (IsOperatorControl())
		{
			float xJoy = stick.GetRawAxis(1);
			float yJoy = - stick.GetRawAxis(2);
			float twistJoy = stick.GetRawAxis(3);
			xJoy = xJoy * fabs(xJoy);			
			yJoy = yJoy * fabs(yJoy);			
			float magJoy = sqrt(xJoy * xJoy + yJoy * yJoy);
			float angleJoy;
			if (yJoy != 0)
				angleJoy = 90 - (yJoy / fabs(yJoy)) * (acos(xJoy / magJoy) * 180 / acos(-1));
			else
				if (yJoy >= 0)
					angleJoy = 90;
				else
					angleJoy = - 90;
			if (angleJoy > 180)
				angleJoy -= 360;
			if (magJoy > 1.0)
				magJoy = 1.0;
			dsLCD->Printf(DriverStationLCD::kMain_Line6, 9, "%7.1f", xJoy);
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 9, "%7.1f", yJoy);
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 9, "%7.1f", twistJoy);
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 9, "%7.1f", magJoy);
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 9, "%7.1f", angleJoy);
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Axis 1");
			dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Axis 2");
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Axis 3");
			dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Magnitude");
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Angle");
			dsLCD->UpdateLCD();
			 
			myRobot.HolonomicDrive(magJoy, angleJoy, twistJoy);
			Wait(0.001);				// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

