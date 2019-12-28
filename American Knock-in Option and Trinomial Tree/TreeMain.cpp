//
//
//                      TreeMain.cpp
//
//
//      
/*
requires
    Arrays.cpp
    BinomialTree.cpp
    BlackScholesFormulas.cpp
    Normals.cpp
    Parameters.cpp
    PayOff3.cpp
    PayOffBridge.cpp
    PayOffForward.cpp
    TreeAmerican.cpp
    TreeEuropean.cpp
    TreeMain.cpp
    TreeProducts.cpp
  */
#include "BinomialTree.h"
#include "TrinomialTree.h"
#include "BinomialTree_Barrier.h"
#include "TreeAmerican.h"
#include "TreeEuropean.h"
#include "BlackScholesFormulas.h"
#include "PayOffForward.h"
#include <iostream>
#include <cmath>
using namespace std;
int main()
{

//    double Expiry = 1;
//    double Strike = 100;
//    double Spot = 100;
//    double Vol = 0.3;
//    double r = 0.04;
//    double d = 0.01;
//    unsigned long Steps = 100;
//    double Bar = 80;
    double Expiry ;
    double Strike ;
    double Spot ;
    double Vol ;
    double r ;
    double d ;
    unsigned long Steps ;
    double Bar ;

    cout << "\nEnter expiry\n";
    cin >> Expiry;

    cout << "\nStrike\n";
    cin >> Strike;

    cout << "\nEnter spot\n";
    cin >> Spot;

    cout << "\nEnter vol\n";
    cin >> Vol;

    cout << "\nr\n";
    cin >> r;

    cout << "\nd\n";
    cin >> d;

    cout << "\nNumber of steps\n";
    cin >> Steps;
    
    cout << "\nBarrier\n";
    cin >> Bar;

    PayOffCall thePayOff(Strike);

    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    TreeEuropean europeanOption(Expiry,thePayOff);
    TreeAmerican americanOption(Expiry,thePayOff);

//    SimpleTrinomialTree theTree1(Spot,rParam,dParam,Vol,Steps,Expiry);
//    double euroPrice1 = theTree1.GetThePrice(europeanOption);
//    double americanPrice1 = theTree1.GetThePrice(americanOption);
//    cout << "euro price " << euroPrice1 << " amer price " << americanPrice1 << "\n";
//
//    SimpleBinomialTree theTree(Spot,rParam,dParam,Vol,Steps,Expiry);
//    double euroPrice = theTree.GetThePrice(europeanOption);
//    double americanPrice = theTree.GetThePrice(americanOption);
//    cout<<"\nPrice in trinomial tree:\n";
//    cout << "euro price " << euroPrice << " amer price " << americanPrice << "\n";
    
    SimpleBinomialTree_Barrier theTree3(Spot,rParam,dParam,Vol,Steps,Expiry,Bar);
    cout << "\nFor barrier option:\n " ;
    double euroPrice3 = theTree3.GetThePrice(europeanOption);
    double americanPrice3 = theTree3.GetThePrice(americanOption);
    cout << "euro price " << euroPrice3 << " amer price " << americanPrice3 << "\n";
//
//    double BSPrice = BlackScholesCall(Spot,Strike,r,d,Vol,Expiry);
//    cout << "BS formula euro price " << BSPrice << "\n";
//
//    PayOffForward forwardPayOff(Strike);
//    TreeEuropean forward(Expiry,forwardPayOff);
//
//    double forwardPrice = theTree.GetThePrice(forward);
//    cout << "forward price by tree " << forwardPrice << "\n";
//
//    double actualForwardPrice = exp(-r*Expiry)*(Spot*exp((r-d)*Expiry)-Strike);
//    cout << "forward price " << actualForwardPrice << "\n";
//
//    Steps++; // now redo the trees with one more step
//    SimpleBinomialTree theNewTree(Spot,rParam,dParam,Vol,Steps,Expiry);
//
//    double euroNewPrice = theNewTree.GetThePrice(europeanOption);
//    double americanNewPrice = theNewTree.GetThePrice(americanOption);
//
//    cout << "euro new price " << euroNewPrice << " amer new price " << americanNewPrice << "\n";
//
//    double forwardNewPrice = theNewTree.GetThePrice(forward);
//
//    cout << "forward price by new tree " << forwardNewPrice << "\n";
//
//    double averageEuro = 0.5*(euroPrice + euroNewPrice);
//    double averageAmer = 0.5*(americanPrice + americanNewPrice);
//    double averageForward = 0.5*(forwardPrice + forwardNewPrice);
//
//    cout << "euro av price " << averageEuro << " amer av price " << averageAmer << "\n";
//    cout << "av forward " << averageForward << "\n";
//
//    double tmp;
//    cin >> tmp;

	return 0;
}

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

