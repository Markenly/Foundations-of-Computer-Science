/***********************************************
Name: Markenly Alusma 
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
*************************************************/


#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{

	double net_cost, call_tax, total_cost, tax_rate;
	string cell_num;
	int relays, call_length;


	cout << "Enter the cell phone number :";
	cin >> cell_num;


	cout << "Enter the number of relay stations :";
	cin >> relays;


	cout << "Enter minutes used :";
	cin >> call_length;


	net_cost = (relays / 50.0)*0.40*call_length;



	if (relays >= 1 && relays <= 5)
		tax_rate = 0.01;
	else if (relays >= 6 && relays <= 11)
		tax_rate = 0.03;
	else if (relays >= 12 && relays <= 20)
		tax_rate = 0.05;
	else if (relays >= 21 && relays <= 50)
		tax_rate = 0.08;
	else if (relays>50)
		tax_rate = 0.12;



	call_tax = (net_cost*tax_rate) / 100;


	total_cost = net_cost + call_tax;
	total_cost /= 100;


	std::cout << std::setprecision(2) << std::fixed;


	cout << "Cell Phone " << cell_num << endl;
	cout << "Number of Relay Stations " << relays << endl;
	cout << "Minutes Used " << call_length << endl;
	cout << "Net Cost " << net_cost << endl;
	cout << "Call Tax " << call_tax << endl;
	cout << "Total Cost of Call " << floor(total_cost + 0.5) * 100 << endl;

	return 0;
}