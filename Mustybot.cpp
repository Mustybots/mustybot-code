#include "MustyLib.h"

class Mustybot: public SimpleRobot
{
	//Declare Objects
	RobotDrive drive;
	Xbox xbox;
	DigitalIOButton dumperSwitch;
	Gyro gyro;

public:
	Mustybot(void) :
		//constucts the objects (in the same order), perameters are the port their PWM cable is connected to unless specified
				drive(1, 2), //both wheels

		//controllers - perameter is the number joystick on the list in the driver station
				xbox(1),

		//Digital Inputs - The first perameter is the module number (in our case it will probably always be 1). The devices are pluged into the Digital IO side of the digital sidecar.
				dumperSwitch(1),

		//Analog Inputs - PWM Cables attach to the Analog Breakout Board on top of Module 1 or 5
				gyro(1)
	{
		drive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
		drive.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	}

	void Autonomous(void)
	{
		while (IsEnabled() && IsAutonomous())
		{
		}
	}

	void OperatorControl()
	{
		float xJoy, yJoy, gyroVal, angle = 0, turn = 0, angleDiff, turnPower;
		gyro.Reset();
		gyro.SetSensitivity(9.7);
		while (IsEnabled() && IsOperatorControl()) // loop as long as the robot is running
		{
			yJoy = xbox.getAxis(Xbox::L_STICK_V);
			xJoy = xbox.getAxis(Xbox::R_STICK_H);			
			gyroVal = gyro.GetAngle()/0.242*360;
			turn = 0.15;
			angle = angle - xJoy * xJoy * xJoy * turn;
			angleDiff = mod(angle - gyroVal, 360);
			turnPower = - mod(angleDiff / 180.0 + 1.0, 2) + 1.0;
			SmartDashboard::PutString("Joy1", vectorToString(xJoy, yJoy));
			SmartDashboard::PutNumber("Heading", mod(gyroVal, 360));
			SmartDashboard::PutNumber("Turn Power", turnPower);
			SmartDashboard::PutBoolean("Switch is ON:", dumperSwitch.Get());
			
			if (!xbox.isButtonPressed(Xbox::R))
			{
				drive.ArcadeDrive(yJoy * yJoy * yJoy, turnPower * fabs(turnPower), false);				
			}
		}
	}
};

START_ROBOT_CLASS(Mustybot);
