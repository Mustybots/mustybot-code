#define DRAG BALL_DRAG
#define vAngle SHOOTER_ANGLE
#define zPos HOOP_HEIGHT - ROBOT_HEIGHT

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
	float root = - 0.35;
	for(int i=0; 100>i; i++)
	{
		root = (root) / (root + 1) - w / (pow(E, root) * (root + 1)) + root;
	}
	return root;
}

float getV_0(float hDistance)
{
	float time = 1 / (G * DRAG) * sin(vAngle) * (G * csc(vAngle) + G * csc(vAngle) * lambertW(- pow(E, ((hDistance * tan(vAngle) * DRAG * DRAG) / G) - (zPos * DRAG / G) - 1) + DRAG * DRAG * hDistance * (-sec(vAngle)) + DRAG * zPos * csc(vAngle)));
	return - hDistance * DRAG / (cos(vAngle) * (1 - pow(E, - DRAG * time)));
}
