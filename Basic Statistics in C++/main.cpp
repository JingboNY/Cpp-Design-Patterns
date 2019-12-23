#include <iostream>
#include <Random1.h>
#include <StatisticG.h>

using namespace std;

int main()
{
	double sample[50],risk;
	int i,temp;
	for (i = 0; i < 50; i++)
	{
		sample[i] = GetOneGaussianByBoxMuller();
	}
	StatisticsGatherer Gatherer;
	for (i = 0; i < 50; i++)
	{
		Gatherer.DumpOneResultMean(sample[i]);
	}
	Gatherer.GetResultsSoFar();
	for (i = 0; i < 50; i++)
	{
		Gatherer.DumpOneResultVariance(sample[i]);
		Gatherer.DumpOneResultSkewness(sample[i]);
		Gatherer.DumpOneResultKurtosis(sample[i]);
	}
	Gatherer.GetResultsSoFar();
	Gatherer.GetResults();
	cout << "Risk is?" << endl;
	cin >> risk;
	cout << "Value at risk "<< risk << "is " << Gatherer.VAR(risk);
	cin >> temp;
}