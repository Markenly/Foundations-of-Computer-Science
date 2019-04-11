/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};


void Initialize(call_record *& call_DB, int & count, int & size);

bool Is_empty(const int count); //inline implementation

bool Is_full(const int count, int size);//inline implementation

int Search(const call_record *call_DB, const int count, const string key);//returns location if item in listl; otherwise return -1

void Add(call_record * &call_DB, int & count, int & size, const string key); //adds item inorder to the list

void Remove(call_record *call_DB, int & count, const string key); //removes an item from the list

void Double_size(call_record * &call_DB, int & count, int & size);

void Process(call_record *call_DB, const int & count);

void Print(const call_record *call_DB, int & count); //prints all the elements in the list to the screen

void Destroy_call_DB(call_record * &call_DB); //de-allocates all memory allocate to call_DB by operator new.


int main() {
	int size = 5;

	int count = 0;

	call_record *call_DB = new call_record[size];

	string key;

	Initialize(call_DB, count, size);

	Is_empty(count); //inline implementation

	Is_full(count, size);//inline implementation

	Search(call_DB, count, key);//returns location if item in listl; otherwise return -1

	Add(call_DB, count, size, key); //adds item inorder to the list

	Remove(call_DB, count, key); //removes an item from the list

	Double_size(call_DB, count, size);

	Process(call_DB, count);

	Print(call_DB, count); //prints all the elements in the list to the screen

	Destroy_call_DB(call_DB); //de-allocates all memory allocate to call_DB by operator new.

	return 0;
}


/*
Precondition: The varialbes firstname, lastname, cell_num, relays, and call_length have not been initialized
Postcondition: The variables have been initialized by data file.
Decription: Reads the data file of call information (firstname, lastname, cell number, relays and call length) into the dynamic array of call record,
call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
*/

void Initialize(call_record * & call_DB, int & count, int & size)
{
	ifstream in; //input file stream object declaration

	in.open("callstats_data.txt"); //bind the file "call_data.txt" to the input

	count = 0;

	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}

	while (!in.eof())
	{
		if (Is_full(count, size))
		{
			Double_size(call_DB, count, size);
		}

		in >> call_DB[count].firstname;

		in >> call_DB[count].lastname;

		in >> call_DB[count].cell_number;

		in >> call_DB[count].relays;

		in >> call_DB[count].call_length;
		count++;
	}
	in.close();
}
/*
Precondition: Checks to see if call_DB is empty
Postcondition: call_DB status verifeid.
Decription: returns true if call_DB is empty
*/

inline bool Is_empty(const int count)
{
	if (count == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}



/*
Precondition: Checks to see if call_DB is full
Postcondition: call_DB status verifeid.
Decription: returns true if call_DB is full
*/

inline bool Is_full(const int count, int size)
{
	if (count == size)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}
/*
Precondition: Checks to see if there is a call_DB
Postcondition: call_DB status verifeid.
Decription: locates key in call_DB if it is there; otherwise -1 is returned
*/

int Search(const call_record *call_DB, const int count, const string key)
{
	for (int i = 0; i < count; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			return i;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

/*
Precondition: Checks memory of call_DB
Postcondition: Increase call_DB size if full.
Decription: add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
*/

void Add(call_record * &call_DB, int & count, int & size, const string key)
{
	int index = count;

	if (Is_full(count, size))
	{
		Double_size(call_DB, count, size);

		call_DB[index].cell_number = key;

		std::cout << "Enter First Name" << '\n';

		std::cin >> call_DB[index].firstname;

		std::cout << "Enter Last Name" << '\n';

		std::cin >> call_DB[index].lastname;

		std::cout << "Enter number of Relays" << '\n';

		std::cin >> call_DB[index].relays;

		std::cout << "Enter Call Length" << '\n';

		std::cin >> call_DB[index].call_length;
		count++;
	}
	return;
}

/*
Precondition: Checks location of call_DB
Postcondition: call_DB is removed if exists.
Decription: remove key from call_DB if it is there.
*/

void Remove(call_record *call_DB, int & count, const string key)
{
	if (Is_empty(count) == 0)
	{
		return;
	}
	int location = Search(call_DB, count, key);

	if (location == -1)
	{
		std::cout << "Location" << location << '\n';
		return;
	}
	else if (location != -1)
	{
		for (int j = location; j < count - 1; j++)
		{
			call_DB[j] = call_DB[j + 1];
		}
		count = count - 1;
	}
}

/*
Precondition: Checks capacity of call_DB
Postcondition: capacity doubled.
Decription: doubles the size (capacity) of call_DB
*/

void Double_size(call_record * &call_DB, int & count, int & size)
{
	size *= 2;

	call_record * temp = new call_record[size];

	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}

	std::cout << "Size: " << size << '\n';

	delete[] call_DB;

	call_DB = temp;

	return;
}

/*
Precondition: The variables have been initialized by the data file.
Postcondition: Conditional statements initialize relay variables.
Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
*/

void Process(call_record *call_DB, const int & count)
{

	for (int i = 0; i < count; i++)
	{
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		call_DB[i].call_tax = call_DB[i].net_cost * call_DB[i].tax_rate;

		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;


		if (call_DB[i].relays <= 0 && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (call_DB[i].relays <= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (call_DB[i].relays <= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (call_DB[i].relays <= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else
		{
			call_DB[i].tax_rate = 0.12;
		}
	}
	return;
}

/*
Name: Print
Precondition: The variables have been initialized and calculated
Postcondition: Results are displayed.
Decription: prints every field of every call_record in call_DB formatted to the screen.
*/

void Print(const call_record *call_DB, int & count)
{
	ofstream out;

	out.open("weekly5_call_info.txt");
	out.setf(ios::showpoint);
	out.precision(2);
	out.setf(ios::fixed);

	if (out.fail())
	{
		cout << "Output file did not open correctly" << endl;
		exit(1);
	}

	//loop to print the output to file
	for (int i = 0; i < count; i++) {
		out << "First Name " << call_DB[i].firstname << "  " << endl;

		out << "Last Name " << call_DB[i].lastname << "  " << endl;

		out << "Cell Phone " << call_DB[i].cell_number << "  " << endl;

		out << "Number of Relay Stations " << call_DB[i].relays << "   " << endl;

		out << "Minutes Used " << call_DB[i].call_length << endl;

		out << "Net Cost " << call_DB[i].net_cost << endl;

		out << "Tax Rate " << call_DB[i].tax_rate << endl;

		out << "Call Tax " << call_DB[i].call_tax << endl;

		out << "Total Cost of Call " << call_DB[i].total_cost << endl << endl;
	}
	out.close();

	return;
}

/*
Name: Destroy_call_DB
Precondition: Checks to see if call_DB exists
Postcondition: Deletes call_DB.
Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
is exited.
*/


void Destroy_call_DB(call_record * &call_DB)
{
	delete[] call_DB;

	return;
}