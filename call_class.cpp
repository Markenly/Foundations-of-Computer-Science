#include <iostream>
#include <string>
#include <fstream>
#include "call_class.h"

using namespace std;


call_class::call_class()
{
	count = 0;
	size = 5;
	call_DB = new call_record[size];

	ifstream in;

	in.open("callstats_data.txt");

	while (!in.eof())
	{
		if (is_full())
		{
			double_size();
		}

		in >> call_DB[count].firstname;
		in >> call_DB[count].lastname;
		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;

		count++;
	}

	process();

	in.close();
}

call_class::call_class(const call_class & Org)
{
	cout << "Copy constructor has been called\n";
	size = Org.size;
	count = Org.count;

	call_DB = new call_record[size];

	for (int i = 0; i < count; i++)
	{
		call_DB[i].firstname = Org.call_DB[i].firstname;
		call_DB[i].lastname = Org.call_DB[i].lastname;
		call_DB[i].cell_number = Org.call_DB[i].cell_number;
		call_DB[i].relays = Org.call_DB[i].relays;
		call_DB[i].call_length = Org.call_DB[i].call_length;
		call_DB[i].net_cost = Org.call_DB[i].net_cost;
		call_DB[i].tax_rate = Org.call_DB[i].tax_rate;
		call_DB[i].call_tax = Org.call_DB[i].call_tax;
		call_DB[i].total_cost = Org.call_DB[i].total_cost;
	}
}


bool call_class::is_empty()
{
	if (count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool call_class::is_full()
{
	if (count == size)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int call_class::search(const string key)
{
	for (int i = 0; i < count; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			return i;
		}
	}
	return -1;
}


void call_class::add()
{
	if (is_full()) //checks to see if array is full
	{
		double_size(); //if full, doubles capacity
	}

	int i = count;

	//adds new information to array, read into the end of the array.
	cout << "Please enter the first name." << endl;
	cin >> call_DB[i].firstname;
	cout << "Please enter the last name." << endl;
	cin >> call_DB[i].lastname;
	cout << "Please enter the cell phone number." << endl;
	cin >> call_DB[i].cell_number;
	cout << "Please enter the number of relays." << endl;
	cin >> call_DB[i].relays;
	cout << "Please enter the number of minutes." << endl;
	cin >> call_DB[i].call_length;

	count++;
	if (is_full())
	{
		double_size();
	}

	//calls process to complete array entry to include call_tax,tax_rate,total_cost, and net_cost.
	process();
}


call_class & call_class::operator-(const string key)
{
	if (!is_empty()) //checks to see if the array is empty. If it is, the function ends.
	{
		if (search(key) != -1) //if the value returned by search is greater than -1, runs code
		{
			do //runs loop to search for all instances of key and remove entries
			{
				//starting from the array member containing the key, re-assigns all array members following
				//to member -1, essentially deleting the array class entry containing the key.
				for (int x = search(key); x < count; x++)
				{
					int y = x + 1; //assigns int y the incremented x value

					call_DB[x].firstname = call_DB[y].firstname;
					call_DB[x].lastname = call_DB[y].lastname;
					call_DB[x].cell_number = call_DB[y].cell_number;
					call_DB[x].relays = call_DB[y].relays;
					call_DB[x].call_length = call_DB[y].call_length;
					call_DB[x].net_cost = call_DB[y].net_cost;
					call_DB[x].tax_rate = call_DB[y].tax_rate;
					call_DB[x].call_tax = call_DB[y].call_tax;
					call_DB[x].total_cost = call_DB[y].total_cost;
				}
				count--; //de-increments count each time loop is run

			} while (search(key) != -1); //runs loop again if Search still does not return a -1 value.
		}
	}
	return *this;
}


void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


void call_class::process()
{
	//runs the loop through the end of the number of file entries (count).
	for (int i = 0; i < count; i++)
	{
		//calculates the net cost of the call based on the number of relays and the call length. 
		//stores results in appropriate array subscript variable.
		call_DB[i].net_cost = (call_DB[i].relays / (50.0 / 0.40))*call_DB[i].call_length;

		//determines tax rate based on the number of relays.
		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else //>50
		{
			call_DB[i].tax_rate = 0.12;
		}

		//calculates the call tax. stores it in the appropriate array subscript viariable
		call_DB[i].call_tax = (call_DB[i].net_cost*call_DB[i].tax_rate);

		//calculates the total cost of the call. stores it in the appropriate array subscript variable
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}


ostream & operator<<(ostream & out, call_class & Org)
{
	//sets decimal places to show to the hundreths place.
	out.setf(ios::showpoint);
	out.precision(2);
	out.setf(ios::fixed);

	//loop runs through the end of the call record and prints each element to the screen.
	for (int i = 0; i < Org.count; i++)
	{
		out << Org.call_DB[i].firstname << " ";
		out << Org.call_DB[i].lastname << " \t";
		out << Org.call_DB[i].cell_number << "  \t";
		out << Org.call_DB[i].relays << "   \t";
		out << Org.call_DB[i].call_length << "  \t";
		out << Org.call_DB[i].net_cost << "  \t";
		out << Org.call_DB[i].tax_rate << "  \t";
		out << Org.call_DB[i].call_tax << "  \t";
		out << " " << Org.call_DB[i].total_cost << endl;
	}

	//Put code to OPEN and CLOSE an ofstream and print to the file "stats7_output.txt".
	ofstream myfile;

	myfile.open("stats7_output.txt"); //opens file

	myfile.setf(ios::showpoint);
	myfile.precision(2);
	myfile.setf(ios::fixed);

	for (int i = 0; i < Org.count; i++)
	{
		myfile << Org.call_DB[i].firstname << " ";
		myfile << Org.call_DB[i].lastname << " \t";
		myfile << Org.call_DB[i].cell_number << "  \t";
		myfile << Org.call_DB[i].relays << "   \t";
		myfile << Org.call_DB[i].call_length << "  \t";
		myfile << Org.call_DB[i].net_cost << "  \t";
		myfile << Org.call_DB[i].tax_rate << "  \t";
		myfile << Org.call_DB[i].call_tax << "  \t";
		myfile << " " << Org.call_DB[i].total_cost << endl;
	}

	myfile.close(); //closes file.


	return out;  //must have this statement
}


call_class::~call_class()
{
	cout << "Inside destructor." << endl;
	delete[]call_DB;
}