//
//  BinomialTree_BarrierOption.hpp
//
//  Created by JB on 5/16/18.
//  Copyright © 2018 JB. All rights reserved.
//

#ifndef BinomialTree_BarrierOption_hpp
#define BinomialTree_BarrierOption_hpp

#pragma warning( disable : 4786 )


#include "TreeProducts.h"
#include <vector>
#include "Parameters.h"
#include "Arrays.h"


class SimpleBinomialTree_Barrier
{
    
public:
    SimpleBinomialTree_Barrier
    (
                       double Spot_,
                       const Parameters& r_,
                       const Parameters& d_,
                       double Volatility_,
                       unsigned long Steps,
                       double Time,
                       double Barrier_//Barrier parameter
    );
    
    double GetThePrice(const TreeProduct& TheProduct);
    
protected:
    
    void BuildTree();
    
private:
    
    double Spot;
    Parameters r;
    Parameters d;
    double Volatility;
    unsigned long Steps;
    double Time;
    bool TreeBuilt;
    double Barrier;
    
    std::vector<std::vector<std::pair<double, double> > > TheTree;
    MJArray Discounts;
};



#endif /* BinomialTree_BarrierOption_hpp */
