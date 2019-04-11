/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

#include <iostream>
#include <cmath>
using namespace std;

void Compute(int a, int b, int c, double &area, double &semiperimeter);

int main()
{
	int a, b, c;
	double area, semiperimeter;

	//declare variable for while loop
	int continueAgain = 1;


	while (continueAgain == 1)
	{
		cout << "Enter the three sides of the triangle: ";
		cin >> a >> b >> c;

		//call Compute
		Compute(a, b, c, area, semiperimeter);

		cout << "The area of given triangle is: " << area << ", and its perimeter is: " << semiperimeter << endl;
		cout << "Do you want to continue? 1. Continue. 0. No.: ";
		cin >> continueAgain;
	}

	return 0;
}

void Compute(int a, int b, int c, double &area, double &semiperimeter)
{
	double s = (a + b + c) / 2.0;
	area = sqrt(s * (s - a) * (s - b) * (s - c));
	semiperimeter = s * 2;
}