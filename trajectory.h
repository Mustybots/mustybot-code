#define DRAG BALL_DRAG
#define vAngle SHOOTER_ANGLE
#define zPos ROBOT_HEIGHT - HOOP_HEIGHT

float csc(float angle)
{
	return 1 / sin(angle);
}

float sec(float angle)
{
	return 1 / cos(angle);
}

float cot(float angle)
{
	return 1 / tan(angle);
}

float lambertW(float w)
{
	float root = - 1 / E + 0.001;
	for(int i=0; i<10000; i++)
	{
		root = root - (((root) / (root + 1)) - (w / (pow(E, root) * (root + 1))));
	}
	return root;
}

float getV_0(float hDistance)
{
	float time = 1 / (G * DRAG) * sin(vAngle) * (G * csc(vAngle) + G * csc(vAngle) * lambertW(- pow(E, ((hDistance * tan(vAngle) * DRAG * DRAG) / G) - (zPos * DRAG / G) - 1) + DRAG * DRAG * hDistance * (-sec(vAngle)) + DRAG * zPos * csc(vAngle)));
	return - hDistance * DRAG / (cos(vAngle) * (1 - pow(E, - DRAG * time)));
}
