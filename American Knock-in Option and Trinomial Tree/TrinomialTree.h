//
//  TrinomialTree.hpp
//
//  Created by JB on 5/16/18.
//  Copyright © 2018 JB. All rights reserved.
//

#ifndef TrinomialTree_hpp
#define TrinomialTree_hpp


#pragma warning( disable : 4786 )


#include "TreeProducts.h"
#include <vector>
#include "Parameters.h"
#include "Arrays.h"


class SimpleTrinomialTree
{
    
public:
    SimpleTrinomialTree(double Spot_,
                        const Parameters& r_,
                        const Parameters& d_,
                        double Volatility_,
                        unsigned long Steps,
                        double Time);
    
    
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
    
    std::vector<std::vector<std::pair<double, double> > > TheTree;
    MJArray Discounts;
};




#endif /* TrinomialTree_h */
