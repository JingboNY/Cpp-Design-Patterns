#ifndef POWEROPTION_H
#define POWEROPTION_H

#include <Payoff2.h>

class PayOffPowerOptionCall : public PayOff
{
public:

	PayOffPowerOptionCall(double Strike_, double power_);
	virtual double operator()(double Spot) const;
	virtual ~PayOffPowerOptionCall() {}

private:

	double Strike;
	double power;

};


class PayOffPowerOptionPut : public PayOff
{
public:

	PayOffPowerOptionPut(double Strike_, double power_);
	virtual double operator()(double Spot) const;
	virtual ~PayOffPowerOptionPut() {}

private:

	double Strike;
	double power;

};
#endif