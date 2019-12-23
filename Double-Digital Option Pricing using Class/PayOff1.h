#ifndef PAYOFF_H
#define PAYOFF_H
class PayOff
{
public:
	enum OptionType { call, put, double_digital };
	//Add double_digital to the Option Type
	PayOff(double Strike_, double Strike_2, OptionType TheOptionsType_);
	//Add another Strike_2 to the method Payoff
	double operator()(double Spot) const;
private:
	double Strike,Strike2;			
	//For PUT & CALL option, Strike is the strike price.
	//For double digital option, Strike and Strike2 are the upper and lower strike prices.
	OptionType TheOptionsType;
};
#endif
