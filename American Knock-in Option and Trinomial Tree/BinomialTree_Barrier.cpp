//
//  BinomialTree_Barrier.cpp
//
//  Created by JB on 5/16/18.
//  Copyright © 2018 JB. All rights reserved.
//

#include "BinomialTree_Barrier.h"
#include "Arrays.h"
#include <cmath>
#include <iostream>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

SimpleBinomialTree_Barrier::SimpleBinomialTree_Barrier(double Spot_,
                                       const Parameters& r_,
                                       const Parameters& d_,
                                       double Volatility_,
                                       unsigned long Steps_,
                                       double Time_,
                                       double Barrier_)
: Spot(Spot_),
r(r_),
d(d_),
Volatility(Volatility_),
Steps(Steps_),
Time(Time_),
Discounts(Steps),
Barrier(Barrier_)
{
    TreeBuilt=false;
}

void SimpleBinomialTree_Barrier::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);
    
    for (unsigned long i=0; i <=Steps; i++)
    {
        
        TheTree[i].resize(i+1);
        
        double thisTime = (i*Time)/Steps;
        
        double movedLogSpot =
        InitialLogSpot+ r.Integral(0.0, thisTime)
        - d.Integral(0.0, thisTime);
        
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;
        
        double sd = Volatility*sqrt(Time/Steps);
        
        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+2,k++)
            TheTree[i][k].first = exp(movedLogSpot+ j*sd);
    }
    
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double SimpleBinomialTree_Barrier::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();
    
    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");
    
    //when initialize the option price at maturity to decide whether the option is valuable
    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+2,k++)
         {
             
             TheTree[Steps][k].second =
             (TheTree[Steps][k].first <= Barrier )?
             TheProduct.FinalPayOff(TheTree[Steps][k].first):
             0.0;
         }

    
    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = index*Time/Steps;
        
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+2,k++)
        {
            double Spot = TheTree[index][k].first;
            double futureDiscountedValue =
            0.5*Discounts[index]*(TheTree[index+1][k].second+TheTree[index+1][k+1].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }
    
    return TheTree[0][0].second;
}
