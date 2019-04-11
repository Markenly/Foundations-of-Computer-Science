/****************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
****************************************************/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class call_record
{
public:
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};

void Input(ifstream & in, call_record & customer_record);

void Output(const call_record & customer_record);

void Process(const call_record & customer_record);

void Input(ifstream & in, call_record & customer_record)
{
	in >> customer_record.cell_number;
	in >> customer_record.relays;
	in >> customer_record.call_length;
}

void Output(const call_record & customer_record)
{
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);

	cout << customer_record.cell_number << "  \t";
	cout << customer_record.relays << "   \t";
	cout << customer_record.call_length << "  \t";
	cout << customer_record.net_cost << "  \t";
	cout << customer_record.tax_rate << "  \t";
	cout << customer_record.call_tax << "  \t";
	cout << " " << customer_record.total_cost << endl;
}

void Process(call_record & customer_record)
{
	customer_record.net_cost = (customer_record.relays / (50.0 / 0.40))*customer_record.call_length;

	if (customer_record.relays >= 0 && customer_record.relays <= 5)
	{
		customer_record.tax_rate = 0.01;
	}
	else if (customer_record.relays >= 6 && customer_record.relays <= 11)
	{
		customer_record.tax_rate = 0.03;
	}
	else if (customer_record.relays >= 12 && customer_record.relays <= 20)
	{
		customer_record.tax_rate = 0.05;
	}
	else if (customer_record.relays >= 21 && customer_record.relays <= 50)
	{
		customer_record.tax_rate = 0.08;
	}
	else 
	{
		customer_record.tax_rate = 0.12;
	}
	customer_record.call_tax = (customer_record.net_cost*customer_record.tax_rate);

	customer_record.total_cost = customer_record.net_cost + customer_record.call_tax;
}

int main()
{
	call_record customer_record;

	ifstream in;

	in.open("call_data.txt");

	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
	}
	else
	{
		while (!in.eof())
		{
			Input(in, customer_record);

			Process(customer_record);

			Output(customer_record);
		}
	}

	in.close();

	return 0;
}
