#ifndef STATISTICSG_H
#define STATISTICSG_H

#include <vector>

class StatisticsGatherer
{

public:

	StatisticsGatherer();
	virtual void DumpOneResultMean(double result);
	virtual void DumpOneResultVariance(double result);
	virtual void DumpOneResultSkewness(double result);
	virtual void DumpOneResultKurtosis(double result);
	virtual void GetResultsSoFar();
	virtual void GetResults();
	virtual double VAR(double risk);
	virtual StatisticsGatherer* clone() const;

private:
	double Results[4];
	double Sample[1000];
	double RunningSumMean;
	double RunningSumVariance;
	double RunningSumSkewness;
	double RunningSumKurtosis;
	unsigned long PathsDone;

};

#endif