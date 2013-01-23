#include "MustyLib.h"

class Mustybot : public SimpleRobot
{
	//Declare Objects
	RobotDrive drive;
	Xbox xbox;
	SmartDashboard* dash;
public:
	
	Mustybot(void):
		//constucts the objects (in the same order), perameters are the port their PWM cable is connected to unless specified
		drive(1, 2), //both wheels
		
		//controllers - perameter is the number joystick on the list in the driver station
		xbox(1)
		
		//Digital Inputs - The first perameter is the module number (in our case it will probably always be 1). The devices are pluged into the Digital IO side of the digital sidecar.
	
		//Analog Inputs - PWM Cables attach to the Analog Breakout Board on top of Module 1 or 5
	
	{
		dash = SmartDashboard::GetInstance(); //allows feedback throgh the driver station to the driver station
	}
	
	void Autonomous(void)
	{
		
	}
	
	void OperatorControl()
	{
		while (IsEnabled() && IsOperatorControl()) // loop "forever"
		{
			drive.ArcadeDrive(xbox.getAxis(Xbox::L_STICK_V), xbox.getAxis(Xbox::L_STICK_H), false);
		}
	}
};

START_ROBOT_CLASS(Mustybot);
