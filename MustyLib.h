#include "WPILib.h"
#include <math.h>
#include <sstream>
#include "Xbox.h"
#include "NetworkTables/NetworkTable.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef E
#define	E  2.71828182845904523536
#endif

#ifndef VECTORTOSTRING
#define VECTORTOSTRING
string vectorToString(double xAxis, double yAxis)
{
	stringstream ss(stringstream::in | stringstream::out);
	ss << xAxis << ";" << yAxis;
	return ss.str();
}
#endif

#ifndef MODULUS
#define MODULUS
float mod(float num, float base)
{
	while(num < 0)
	{
		num += base;
	}
	while(num >= base)
	{
		num -= base;
	}
	return num;
}
#endif

#ifndef SIGN
#define SIGN
float sgn(float num)
{
	if(num >= 0)
		return 1.0;
	else
		return -1.0;
}
#endif
