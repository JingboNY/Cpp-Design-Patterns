#include"StatisticG.h"
#include<cmath>
#include <iostream>
using namespace std;

StatisticsGatherer::StatisticsGatherer()
	:
	RunningSumMean(0.0), RunningSumVariance(0.0), RunningSumSkewness(0.0), RunningSumKurtosis(0.0), PathsDone(0UL)
{

}

void StatisticsGatherer::DumpOneResultMean(double result)
{
	Sample[PathsDone] = result;
	PathsDone++;
	RunningSumMean += result;
}

void StatisticsGatherer::DumpOneResultVariance(double result)
{
	result = result * result - Results[0] * Results[0];
	RunningSumVariance += result;
}

void StatisticsGatherer::DumpOneResultSkewness(double result)
{
	result = result * result*result - Results[0] * Results[0] * Results[0];
	RunningSumSkewness += result;
}

void StatisticsGatherer::DumpOneResultKurtosis(double result)
{
	result = result*result*result*result - Results[0] * Results[0] * Results[0] * Results[0];
	RunningSumKurtosis += result;
}
void StatisticsGatherer::GetResultsSoFar()
{

	Results[0] = RunningSumMean / PathsDone;
	Results[1] = RunningSumVariance / PathsDone;
	Results[2] = RunningSumSkewness / PathsDone;
	Results[3] = RunningSumKurtosis / PathsDone;

}

void StatisticsGatherer::GetResults()
{
	cout << "Mean is " << Results[0] << endl;
	cout << "Variance is " << Results[1] << endl;
	cout << "Skewness is " << Results[2] << endl;
	cout << "Kurtosis is " << Results[3] << endl;
}

double StatisticsGatherer::VAR(double risk)
{
	double temp;
	int i;
	for (i = (PathsDone-1); i >=0; i--)
	{
		for (int j = 0; j <i;j++)
		{
			if (Sample[j] < Sample[j + 1])
			{
				temp = Sample[j];
				Sample[j] = Sample[j + 1];
				Sample[j + 1] = temp;
			}
		}
	}
	double r = 0;

	for ( i = 0; r < risk; i++)
	{
		r = r + 1 / double(PathsDone);
	}
	return Sample[i];
}
StatisticsGatherer* StatisticsGatherer::clone() const
{
	return new StatisticsGatherer(*this);
}