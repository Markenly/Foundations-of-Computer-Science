/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;


void Input(ifstream& dataIn, string filename);

void process(string phoneNos[], int relays[], int mins[], int count);

void Output(ofstream& dataOut, string phone_no, int relay, int mins, double tax_rate,

	double net_cost, double call_tax, double total_cost);

int main()
{

	// defines an input stream for the data file
	ifstream dataIn;

	string filename;

	// Getting the file name entered by the user
	cout << "Enter the filename :";
	cin >> filename;

	Input(dataIn, filename);

	cout << ":: Data Written to Outputfile ::" << endl;

	return 0;
}


/* This function read the data from the file and populate those valuies into an array
*/
void Input(ifstream& dataIn, string filename)
{
	// Opening the input file
	dataIn.open(filename.c_str());

	int count = 0, i = 0;

	string phoneNo;

	int relay, min;

	// checking whether the file name is valid or not
	if (dataIn.fail())
	{
		cout << "** File Not Found **";

		exit(1);
	}
	else
	{
		// this loop will count the number of records in the file
		while (dataIn >> phoneNo >> relay >> min)
		{
			count++;
		}
		dataIn.close();


		// Creating array dynamically
		string* phoneNos = new string[count];

		int* relays = new int[count];

		int* mins = new int[count];

		dataIn.open(filename.c_str());


		// Reading the data from the file
		while (dataIn >> phoneNo >> relay >> min)
		{
			phoneNos[i] = phoneNo;

			relays[i] = relay;

			mins[i] = min;

			i++;
		}

		dataIn.close();

		// calling the function
		process(phoneNos, relays, mins, count);
	}
}

// This function will do calculations
void process(string phoneNos[], int relays[], int mins[], int count)
{

	double net_cost, call_tax, total_cost, tax_rate;

	// Defines an output stream for the data file
	ofstream dataOut;

	dataOut << std::setprecision(2) << std::fixed;

	// creating and Opening the output file
	dataOut.open("weekly_call_info.txt");


	for (int i = 0; i < count; i++)
	{
		if (relays[i] >= 0 && relays[i] <= 5)
		{
			tax_rate = 0.01;
		}
		else if (relays[i] >= 6 && relays[i] <= 11)
		{
			tax_rate = 0.03;
		}
		else if (relays[i] >= 12 && relays[i] <= 20)
		{
			tax_rate = 0.05;
		}
		else if (relays[i] >= 21 && relays[i] <= 50)
		{
			tax_rate = 0.08;
		}
		else if (relays[i] > 50)
		{
			tax_rate = 0.12;
		}

		// performing calculations
		net_cost = (relays[i] / 50.0) * 0.40 * mins[i];

		call_tax = net_cost * tax_rate;

		total_cost = net_cost + call_tax;

		// calling the function
		Output(dataOut, phoneNos[i], relays[i], mins[i], tax_rate, net_cost, call_tax, total_cost);
	}
	dataOut.close();
}

// This function will write the data to the output file
void Output(ofstream& dataOut, string phone_no, int relay, int mins, double tax_rate,
	double net_cost, double call_tax, double total_cost)
{

	dataOut << phone_no << "\t" << relay << "\t" << mins << "\t" << net_cost << "\t" << tax_rate
		<< "\t" << call_tax << "\t" << total_cost << endl;
}