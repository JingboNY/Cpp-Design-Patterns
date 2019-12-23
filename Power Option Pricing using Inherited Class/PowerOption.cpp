#include <PowerOption.h>
#include <math.h>
#include <minmax.h>
PayOffPowerOptionCall ::PayOffPowerOptionCall(double Strike_, double power_)
	:	Strike(Strike_),  power(power_)
{
}


PayOffPowerOptionPut::PayOffPowerOptionPut(double Strike_, double power_)
	: Strike(Strike_), power(power_)
{
}

double PayOffPowerOptionCall::operator()(double spot) const
{
	return max(pow(spot,power) - Strike, 0.0);
}

double PayOffPowerOptionPut::operator()(double spot) const
{
	return max(Strike - pow(spot, power), 0.0);
}