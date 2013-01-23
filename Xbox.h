#ifndef XBOX_H
#define XBOX_H

class Xbox
{
private:
	Joystick controller;
public:
		Xbox(int port) : controller(port) {}

		enum kButton {A = 1, B, X, Y, L, R, BACK, START, L_STICK, R_STICK};
		enum kAxis {L_STICK_H = 1, L_STICK_V, TRIGGERS, R_STICK_H, R_STICK_V, DPAD_H, DPAD_V};
			
		bool isButtonPressed(kButton button)
		{
			return controller.GetRawButton(button);
		}

		float getAxis(kAxis axis)
		{
			if(axis == L_STICK_V || axis == R_STICK_V || axis == DPAD_V)
				return -controller.GetRawButton(axis);
			else
				return controller.GetRawButton(axis);
		}

		~Xbox()
		{

		}
};

#endif
