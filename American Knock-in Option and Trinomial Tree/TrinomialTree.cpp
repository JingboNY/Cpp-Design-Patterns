//
//  TrinomialTree.cpp
//
//  Created by JB on 5/16/18.
//  Copyright © 2018 JB. All rights reserved.
//

#include "TrinomialTree.h"
#include "Arrays.h"
#include <cmath>

// the basic math functions should be in namespace std but aren't in VCPP6
#if !defined(_MSC_VER)
using namespace std;
#endif

SimpleTrinomialTree::SimpleTrinomialTree(double Spot_,
                                         const Parameters& r_,
                                         const Parameters& d_,
                                         double Volatility_,
                                         unsigned long Steps_,
                                         double Time_)
: Spot(Spot_),
r(r_),
d(d_),
Volatility(Volatility_),
Steps(Steps_),
Time(Time_),
Discounts(Steps)
{
    TreeBuilt=false;
}

void SimpleTrinomialTree::BuildTree()
{
    TreeBuilt = true;
    TheTree.resize(Steps+1);
    
    double InitialLogSpot = log(Spot);
    
    for (unsigned long i=0; i <=Steps; i++)
    {
        //size of trinomial tree
        TheTree[i].resize(i*2+1);
        
        double thisTime = (i*Time)/Steps;
        
        double movedLogSpot =
        InitialLogSpot+ r.Integral(0.0, thisTime)
        - d.Integral(0.0, thisTime);
        
        movedLogSpot -= 0.5*Volatility*Volatility*thisTime;
        
        double sd = Volatility*sqrt(Time/Steps);
        
        //loop j=j+1 to set each node's stock price
        for (long j = -static_cast<long>(i), k=0; j <= static_cast<long>(i); j=j+1,k++)
            TheTree[i][k].first = exp(movedLogSpot+ j*sd);
    }
    
    for (unsigned long l=0; l <Steps; l++)
    {
        Discounts[l] = exp(- r.Integral(l*Time/Steps,(l+1)*Time/Steps));
    }
}

double SimpleTrinomialTree::GetThePrice(const TreeProduct& TheProduct)
{
    if (!TreeBuilt)
        BuildTree();
    
    if (TheProduct.GetFinalTime() != Time)
        throw("mismatched product in SimpleBinomialTree");
    
    //change size of loop at maturity when initialize option price
    for (long j = -static_cast<long>(Steps), k=0; j <=static_cast<long>( Steps); j=j+1,k++)
        TheTree[Steps][k].second = TheProduct.FinalPayOff(TheTree[Steps][k].first);
    
    // trinomial tree's parameters pu,pm,pd
    double pu = ((exp(r.Integral(0.0, Time/Steps)*0.5) - exp(-Volatility*sqrt(0.5*Time/Steps)))/
                 (exp(Volatility*sqrt(0.5*Time/Steps)) - exp(-Volatility*sqrt(0.5*Time/Steps)))) * ((exp(r.Integral(0.0, Time/Steps)*0.5) - exp(-Volatility*sqrt(0.5*Time/Steps)))/(exp(Volatility*sqrt(0.5*Time/Steps)) - exp(-Volatility*sqrt(0.5*Time/Steps))));
    double pd = ((exp(Volatility*sqrt(0.5*Time/Steps)) - exp(r.Integral(0.0, Time/Steps)*0.5)) / (exp(Volatility*sqrt(0.5*Time/Steps)) - exp(-Volatility*sqrt(0.5*Time/Steps)))) * ((exp(Volatility*sqrt(0.5*Time/Steps)) - exp(r.Integral(0.0, Time/Steps)*0.5)) / (exp(Volatility*sqrt(0.5*Time/Steps)) - exp(-Volatility*sqrt(0.5*Time/Steps))));
    double pm = 1.0 - pu - pd;
    
    
    for (unsigned long i=1; i <= Steps; i++)
    {
        unsigned long index = Steps-i;
        double ThisTime = index*Time/Steps;
        
        //loop j=j+1 to set each node's option price
        for (long j = -static_cast<long>(index), k=0; j <= static_cast<long>(index); j=j+1,k++)
        {
            double Spot = TheTree[index][k].first;
            //use next three nodes to get the last node
            double futureDiscountedValue =
            Discounts[index]*(pu*TheTree[index+1][k+2].second + pm*TheTree[index+1][k+1].second+pd*TheTree[index+1][k].second);
            TheTree[index][k].second = TheProduct.PreFinalValue(Spot,ThisTime,futureDiscountedValue);
        }
        
    }
    return TheTree[0][0].second;
}
