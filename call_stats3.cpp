/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

# include <string>
# include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

struct call_record {
	string phoneNumber;
	int relayStations;
	int lengthOfTheCall;
};

double netCostOfTheCall;
double taxRate;
double callTax;
double totalCostOfTheCall;
static int count = 0;
ofstream outFile;

void Input(ifstream&, struct call_record *call);

void output(call_record *call, int record, double netCostOfTheCall, double tax_rate, double callTax, double totalCostOfTheCall);

void Input(ifstream& fin, call_record *call)
{
	string temp;

	int i = 0;

	while (fin >> call[i].phoneNumber >> call[i].relayStations >> call[i].lengthOfTheCall)
	{
		cout << call[i].phoneNumber << " " << call[i].relayStations << " " << call[i].lengthOfTheCall << endl;
		i++;
		count = i;
	}
}

void process(call_record *call)
{
	int i = 0;
	int tax_rate = 0;

	cout << "in Process count value:" << count << endl;

	while (i<count)
	{
		//net cost of a call: net_cost
		netCostOfTheCall = (call[i].relayStations / 50 * 0.40 * call[i].lengthOfTheCall);

		netCostOfTheCall = floor(netCostOfTheCall * 100 + 0.5) / 100;

		cout << netCostOfTheCall << ":";

		//tax on the call: call_tax
		if (call[i].relayStations >= 0 || call[i].relayStations <= 5) tax_rate = 1;

		if (call[i].relayStations >= 6 || call[i].relayStations <= 11) tax_rate = 3;

		if (call[i].relayStations >= 12 || call[i].relayStations <= 20) tax_rate = 5;

		if (call[i].relayStations >= 21 || call[i].relayStations <= 50) tax_rate = 8;

		if (call[i].relayStations >50) tax_rate = 12;

		callTax = netCostOfTheCall * tax_rate / 100;

		callTax = floor(callTax * 100 + 0.5) / 100;

		cout << callTax << ":";

		//total cost of the call: total_cost
		totalCostOfTheCall = netCostOfTheCall + callTax;

		cout << totalCostOfTheCall << endl;

		output(call, i, netCostOfTheCall, tax_rate, callTax, totalCostOfTheCall);
		i++;
	}
}

void output(call_record *call, int record, double netCostOfTheCall, double tax_rate, double callTax, double totalCostOfTheCall)
{
	outFile << call[record].phoneNumber << "\t\t" << call[record].relayStations << "\t\t" << call[record].lengthOfTheCall << "\t\t"
		<< netCostOfTheCall << "\t\t" << tax_rate << "\t\t" << callTax << "\t\t" << totalCostOfTheCall << "\n";
}

int main()
{
	call_record cr[200];

	ifstream inFile;

	inFile.open("call_data.txt");

	outFile.open("weekly_call_info.txt");

	if (!inFile) {
		cout << "Error opening call_data.txt" << endl;
		return 1;
	}

	Input(inFile, cr);

	process(cr);

	inFile.close();

	outFile.close();
}