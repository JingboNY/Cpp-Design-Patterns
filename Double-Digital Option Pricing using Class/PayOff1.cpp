#include <PayOff1.h>
#include <MinMax.h>
#include <math.h>
PayOff::PayOff(double Strike_, double Strike_2, OptionType TheOptionsType_)
	:
	Strike(Strike_), Strike2(Strike_2), TheOptionsType(TheOptionsType_)
	//Add another Strike_2 to the method Payoff
{
}
double PayOff::operator()(double spot) const
{
	switch (TheOptionsType)
	{
	case call:
		return max(spot - Strike, 0.0);
	case put:
		return max(Strike - spot, 0.0);
	case double_digital:
	{
		double avgStirke = (Strike + Strike2) / 2;
		double halfgap = fabs(Strike - avgStirke);
		if (spot<(avgStirke - halfgap) || spot>(avgStirke + halfgap))
			return 0;
		else return 1;
	}
		//Add the payoff calculation for double digital option
	default:
		throw("unknown option type found.");
	}
}