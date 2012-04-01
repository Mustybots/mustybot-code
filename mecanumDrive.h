float Limit(float num)
{
	if (num > 1.0)
	{
		return 1.0;
	}
	if (num < -1.0)
	{
		return -1.0;
	}
	return num;
}

void Normalize(double *wheelSpeeds)
{
	double maxMagnitude = fabs(wheelSpeeds[0]);
	INT32 i;
	for (i=1; i<4; i++)
	{
		double temp = fabs(wheelSpeeds[i]);
		if (maxMagnitude < temp) maxMagnitude = temp;
	}
	if (maxMagnitude > 1.0)
	{
		for (i=0; i<4; i++)
		{
			wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
		}
	}
}

void mecanumDrive(float magnitude, float direction, float rotation)
{
    magnitude = Limit(magnitude) * sqrt(2.0);
    double dirInRad = (direction + acos(-1) / 4);
    double cosD = cos(dirInRad);
    double sinD = sin(dirInRad);
    double wheelSpeeds[4];
    wheelSpeeds[0] = sinD * magnitude + rotation;
    wheelSpeeds[1] = cosD * magnitude - rotation;
    wheelSpeeds[2] = cosD * magnitude + rotation;
    wheelSpeeds[3] = sinD * magnitude - rotation;

    Normalize(wheelSpeeds);
    
    FL.Set(- wheelSpeeds[0]);
    FR.Set(wheelSpeeds[1]);
    //FR.Set((1.5 * wheelSpeeds[1] > 1.0) and 1.0 or 1.5 * wheelSpeeds[1]);
    BL.Set(- wheelSpeeds[2]);
    BR.Set(wheelSpeeds[3]);
}
