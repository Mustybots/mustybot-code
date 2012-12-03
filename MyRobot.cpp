#include "MustyLib.h"

#define PI 3.14159265358979323846
#define E 2.718281828459045235360

#define XBOX_A xbox.GetRawButton(1)
#define XBOX_B xbox.GetRawButton(2)
#define XBOX_X xbox.GetRawButton(3)
#define XBOX_Y xbox.GetRawButton(4)

#define XBOX_L_BUMPER xbox.GetRawButton(5)
#define XBOX_R_BUMPER xbox.GetRawButton(6)
#define XBOX_TRIGGERS xbox.GetRawAxis(3)

#define XBOX_BACK xbox.GetRawButton(7)
#define XBOX_START xbox.GetRawButton(8)

#define XBOX_L_STICK_H xbox.GetRawAxis(1)
#define XBOX_L_STICK_V xbox.GetRawAxis(2)
#define XBOX_L_STICK_BUTTON xbox.GetRawButton(9)

#define XBOX_R_STICK_H xbox.GetRawAxis(4)
#define XBOX_R_STICK_V xbox.GetRawAxis(5)
#define XBOX_R_STICK_BUTTON xbox.GetRawButton(10)

#define XBOX_DPAD_H xbox.GetRawAxis(6)

#define X_ACCELERATION accelerometer.GetAcceleration(ADXL345_SPI::kAxis_X)
#define Y_ACCELERATION accelerometer.GetAcceleration(ADXL345_SPI::kAxis_Y)
#define Z_ACCELERATION accelerometer.GetAcceleration(ADXL345_SPI::kAxis_Z)

#define ROTATION_COEFFICENT 1.0


class Mustybot : public SimpleRobot
{
	//Declare Objects
	RobotDrive robot;
	Victor topShooter, bottomShooter, lazySuzan, conveyer;
	Joystick xbox;
	ADXL345_SPI accelerometer;
	Gyro gyroscope;
	SmartDashboard* dash;
public:
	
	Mustybot(void):
		//constucts the objects (in the same order), perameters are the port their PWM cable is connected to unless specified
		robot(3, 5, 4, 6), //all 4 wheels
		topShooter(1),
		bottomShooter(2),
		lazySuzan(7),
		conveyer(10),
		
		//Joysticks - perameter is the number joystick on the list in the driver station
		xbox(1),
		
		//Digital Inputs - The first perameter is the module number (in our case it will probably always be 1). The devices are pluged into the Digital IO side of the digital sidecar.
		accelerometer(1, 1, 2, 3, 4, ADXL345_SPI::kRange_2G), //uses the spi protocol. If using two three-pronged pwm cables, plugs in sideways so the first one plugs into the GND, 5V, and digital IO port 1 and the second one plugs into the signal pin of igital IO ports 2, 3, and 4
	
		//Analog Inputs - PWM Cables attach to the Analog Breakout Board on top of Module 1 or 5
		gyroscope(2, 1)	
	{
		dash = SmartDashboard::GetInstance(); //allows feedback throgh the driver station to the driver station
		robot.SetExpiration(0.1);
		robot.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
		robot.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
		gyroscope.Reset();
	}
	void Autonomous(void)
	{
	}
	void OperatorControl(void)
	{
		robot.SetSafetyEnabled(true);
		
		//variable declarations
		float acceleration, xDir, yDir, rotate, shootSpeed, suzanSpeed, driveMag, driveAng, convSpeed, heading = 0;
		
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			acceleration = X_ACCELERATION;
			
			xDir = XBOX_L_STICK_H;
			yDir = XBOX_L_STICK_V;
			rotate = - XBOX_R_STICK_H;
			shootSpeed = - XBOX_TRIGGERS;
			suzanSpeed = XBOX_DPAD_H;
			
			if(rotate < 0.15 && rotate > -0.15)
				rotate = 0;
			
			if(yDir == 0.0)
			{
				driveMag = fabs(xDir);
				driveAng = ((fabs(xDir) / xDir) + 1.0) * 90.0;
			}
			else
			{
				driveMag = sqrt(xDir * xDir + yDir * yDir); //using some trig to convert to polar coodinates
				driveAng = fabs(yDir) / yDir * acos(xDir / driveMag) * 180.0 / PI;
			}
			
			driveMag = driveMag * driveMag * driveMag; //cubes the magnetude so the controller is less sensitivein the middle but still reaches its full potential
			
			if(XBOX_A)//conveyer goes forward
				convSpeed = 1.0;
			else
			{
				if(XBOX_B) //*theoretically* makes the conveyer belt go in reverse when the B button is pressed
					convSpeed = - 1.0;
				else
					convSpeed = 0.0;
			}
			
			
			if(XBOX_L_BUMPER) //if the left bumper button is pressed, stop everything until the button is released
			{
				gyroscope.Reset();
				heading = 0;
				xDir = 0.0;
				yDir = 0.0;
				rotate = 0.0;
				shootSpeed = 0.0;
				suzanSpeed = 0.0;
				convSpeed = 0.0;
				driveMag = 0.0;
				driveAng = 0.0;
			}
			
			heading += ROTATION_COEFFICENT * rotate;
			
			//sets the speeds on the Victors and Jaguars (wheels)
			gyroHolonomicDrive(&robot, &gyroscope, driveMag, driveAng, heading);
			topShooter.Set(0.5 * shootSpeed);
			bottomShooter.Set(0.5 * shootSpeed);
			lazySuzan.Set(suzanSpeed);
			conveyer.Set(convSpeed);
			
			dash->PutString("Xbox Controller", "");
			dash->PutDouble("Left Joystick", xDir);
		}
	}
};

START_ROBOT_CLASS(Mustybot);
