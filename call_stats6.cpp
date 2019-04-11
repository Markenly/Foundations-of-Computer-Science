/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

#include <iostream>
#include <string>
#include <fstream>

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


class call_class
{
public:
	call_class();
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty() const; //inline implementation
	bool is_full() const;//inline implementation
	int search(const string key) const;//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	void remove(const string key); //removes an item from the list
	void double_size();
	void process();
	void print() const; //prints all the elements in the list to the screen
private:
	int count;
	int size;
	call_record *call_DB;
};



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


bool call_class::is_empty() const
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


bool call_class::is_full() const
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


int call_class::search(const string key) const
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


	//calls process to complete array entry to include call_tax,tax_rate,total_cost, and net_cost.
	process();
}


void call_class::remove(const string key)
{
	if (is_empty()) //checks to see if the array is empty. If it is, the function ends.
	{
		return;
	}
	else //if array is not empty, runs code
	{
		int i = search(key); //assigns value returned by Search function to int i.


		if (i != -1) //if the value returned by Search is greater than -1, runs code
		{
			do //runs loop to search for all instances of key and remove entries
			{
				int i = search(key); //assigns value returned by Search function to int i every time loop runs


									 //starting from the array member containing the key, re-assigns all array members following
									 //to member -1, essentially deleting the array class entry containing the key.
				for (int x = i; x < count; x++)
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




void call_class::print() const
{
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);


	for (int i = 0; i<count; i++)
	{
		cout << call_DB[i].firstname << "  " << call_DB[i].lastname
			<< "  " << call_DB[i].relays << "  " << call_DB[i].cell_number
			<< "  " << call_DB[i].call_length << " " << call_DB[i].net_cost << " "
			<< call_DB[i].tax_rate << " " << call_DB[i].call_tax << " "
			<< call_DB[i].total_cost << endl;
	}
}


call_class::~call_class()
{
	cout << "Inside destructor." << endl;
	delete[]call_DB;
}




//driver to test the functionality of your class.
int main()
{
	call_class MyClass;

	MyClass.print();




	return 0;
}