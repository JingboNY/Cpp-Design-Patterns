#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

double GetOneGaussianByBoxMuller()
{
	double result;
	double x;
	double y;
	double sizeSquared;
	do
	{
		x = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0*rand() / static_cast<double>(RAND_MAX) - 1;
		sizeSquared = x * x + y * y;
	} while
		(sizeSquared >= 1.0);
	result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);
	return result;
}

double Price_digital(double Expiry,
	double Strike_high,
	double Strike_low,
	double Spot,
	double Vol,
	double r,
	unsigned long NumberOfPaths)
{
	double variance = Vol * Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;
	double movedSpot = Spot * exp(r*Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot * exp(rootVariance*thisGaussian);
		double thisPayoff = 1;
		if (thisSpot > Strike_high || thisSpot < Strike_low)
			thisPayoff = 0;
		runningSum += thisPayoff;
	}
	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;
}

int main()
{
	double Expiry;
	double Strike_high;
	double Strike_low;
	double Spot;
	double Vol;
	double r;
	unsigned long NumberOfPaths;
	cout << "\nEnter expiry\n";
	cin >> Expiry;
	cout << "\nEnter upper strike\n";
	cin >> Strike_high;
	cout << "\nEnter lower strike\n";
	cin >> Strike_low;
	cout << "\nEnter spot\n";
	cin >> Spot;
	cout << "\nEnter vol\n";
	cin >> Vol;
	cout << "\nr\n";
	cin >> r;
	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;
	double result = Price_digital(Expiry,
		Strike_high,
		Strike_low,
		Spot,
		Vol,
		r,
		NumberOfPaths);
	cout << "the price is " << result << "\n";
	double tmp;
	cin >> tmp;
	return 0;
}