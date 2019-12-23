#include<SimpleMC2.h>
#include<PowerOption.h>
#include<iostream>
using namespace std;

int main()
{

	double Expiry;
	double Strike; 
	double Spot; 
	double Vol; 
	double r; 
	double power;
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter strike\n";
	cin >> Strike;

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\npower\n";
	cin >> power;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

	PayOffPowerOptionCall PayOffCall(Strike, power);
	PayOffPowerOptionPut PayOffPut(Strike, power);

	double result1 = SimpleMonteCarlo2(PayOffCall,
                                      Expiry,
                                      Spot, 
                                      Vol,
                                      r,
                                      NumberOfPaths);
	
	double result2 = SimpleMonteCarlo2(PayOffPut,
		Expiry,
		Spot,
		Vol,
		r,
		NumberOfPaths);

	cout <<"\nthe call price is " << result1 << "\n";
	cout << "\nthe put price is " << result2 << "\n";
    double tmp;
    cin >> tmp;

	return 0;

}

