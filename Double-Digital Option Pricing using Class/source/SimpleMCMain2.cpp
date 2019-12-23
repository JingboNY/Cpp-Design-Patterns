#include<SimpleMC.h>
#include<iostream>
using namespace std;

int main()
{

	double Expiry;
	double Strike,Strike2; //Add a variable Strike 2 for double digital option
	double Spot; 
	double Vol; 
	double r; 
	unsigned long NumberOfPaths;

	cout << "\nEnter expiry\n";
	cin >> Expiry;

	cout << "\nEnter strike\n";
	cin >> Strike;

	cout << "\nEnter the second strike for double digital option\n";
	cin >> Strike2;
	//Input the second strike for double digital option

	cout << "\nEnter spot\n";
	cin >> Spot;

	cout << "\nEnter vol\n";
	cin >> Vol;

	cout << "\nr\n";
	cin >> r;

	cout << "\nNumber of paths\n";
	cin >> NumberOfPaths;

    PayOff callPayOff(Strike,0, PayOff::call);
    PayOff putPayOff(Strike,0, PayOff::put);
	PayOff dbPayOff(Strike, Strike2, PayOff::double_digital);

	double resultCall = SimpleMonteCarlo2(callPayOff,
                                          Expiry,                                           
							              Spot, 
							              Vol, 
							              r, 
						                  NumberOfPaths);
	
    double resultPut = SimpleMonteCarlo2(putPayOff,
                                         Expiry,                                           
							             Spot, 
							             Vol, 
							             r, 
						                 NumberOfPaths);

	double resultDB = SimpleMonteCarlo2(dbPayOff,
										Expiry,
										Spot,
										Vol,
										r,
										NumberOfPaths);
	cout <<"the prices are\n" << resultCall << "  for the call,\n" << resultPut << " for the put,\n" << resultDB << " for the double digital\n";

    double tmp;
    cin >> tmp;

	return 0;

}
