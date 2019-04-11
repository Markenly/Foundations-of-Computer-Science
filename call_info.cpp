/****************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
****************************************************/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void Input(string &cell_num, int &relays, int &call_len);

void Output(const string cell_num, const int relays, const int call_len, \
	const double &net_cost, const double &call_tax, \
	const double &total_cost);

void Process(const int relays, const int call_len, double &net_cost, \
	double &call_tax, double &total_cost);


int main()
{
	string cell_num;
	int relays;
	int call_len;
	double net_cost;
	double call_tax;
	double total_cost;
	char loop;

	do
	{
		Input(cell_num, relays, call_len);
		
		Process(relays, call_len, net_cost, call_tax, total_cost);
		
		Output(cell_num, relays, call_len, net_cost, call_tax, total_cost);
		
		cout << "=======================================" << endl;
	
		cout << "Run another calculation? (y, n): ";
		
		cin.ignore() >> loop;

	} while (loop == 'y' || loop == 'Y');

	return 0;
}


void Input(string &cell_num, int &relays, int &call_len)
{

	cout << "Enter your cell phone number: ";
	
	cin.ignore() >> cell_num;
	
	cout << "Enter the number of relays: ";
	
	cin.ignore() >> relays;
	
	cout << "Enter the length of the call in minutes: ";
	
	cin.ignore() >> call_len;

	return;
}


void Output(const string cell_num, const int relays, const int call_len, \
	const double &net_cost, const double &call_tax, \
	const double &total_cost)
{

	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);

	cout << "=======================================" << endl;
	
	cout << setw(30) << left << "Cell Phone" << cell_num << left << endl;

	cout << setw(30) << left << "Number of relay stations" << relays << left\
		<< endl;
	
	cout << setw(30) << left << "Minutes Used" << call_len << left << endl;
	
	cout << setw(30) << left << "Net Cost" << net_cost << left << endl;
	
	cout << setw(30) << left << "Call Tax" << call_tax << left << endl;
	
	cout << setw(30) << left << "Total Cost of Call" << total_cost << left\
		<< endl;

	return;
}


void Process(const int relays, const int call_len, double &net_cost, \
	double &call_tax, double &total_cost)
{
	net_cost = relays / 50.0 * 0.40 * call_len;

	float tax_rate;
	
	cout << "Relays = " << relays << endl;
	
	if (relays >= 1 && relays <= 5)
	{
		tax_rate = 0.01;
	}
	else if (relays >= 6 && relays <= 11)
	{
		tax_rate = 0.03;
	}
	else if (relays >= 12 && relays <= 20)
	{
		tax_rate = 0.05;
	}
	else if (relays >= 21 && relays <= 50)
	{
		tax_rate = 0.08;
	}
	else if (relays > 50)
	{
		tax_rate = 0.12;
	}
	else
	{
		cerr << "Unexpected number of relays entered" << endl;
	}
	cout << "Tax rate = " << tax_rate << endl;


	call_tax = net_cost * tax_rate;


	total_cost = net_cost + call_tax;

	return;
}