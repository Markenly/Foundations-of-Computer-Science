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
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	call_class & operator-(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator<<(ostream & out_to_file, call_class & Org); //prints all the elements in the
																		  //list to the screen.

private:
	int count;
	int size;
	call_record *call_DB;
};


call_class::call_class()
{
	call_DB = new call_record[5];

	size = 5;

	count = 0;
}


bool call_class::is_empty()
{
	return count == 0;
}


bool call_class::is_full()
{
	return count == size;
}


int call_class::search(const string key)
{
	for (int i = 0; i < count; ++i)
	{
		// check if cell_number matches to what we are looking for
		if (call_DB[i].cell_number == key)
		{
			return i; // we found the name
		}
	}
	return -1;
}


void call_class::add()
{
	ifstream fin; // read the input from file

	fin.open("call_stats.txt");

	if (is_full())double_size();

	while (fin >> call_DB[count].firstname >> call_DB[count].lastname >>
		call_DB[count].cell_number >> call_DB[count].relays >> call_DB[count].call_length)count++;
}


call_class & call_class::operator-(const string key)
{
	// remove the key and shift right elements to left
	int index = search(key);

	if (index != -1)
	{
		for (int i = index; i < count - 1; ++i)
		{
			call_DB[i] = call_DB[i + 1];
		}
	}
	count--;
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

}


ostream & operator<<(ostream & out, call_class & Org)
{
	for (int i = 0; i<Org.count; i++)
	{
		out << Org.call_DB[i].firstname << " " << Org.call_DB[i].lastname
			<< " " << Org.call_DB[i].relays << " " << Org.call_DB[i].cell_number
			<< " " << Org.call_DB[i].call_length << endl;
	}

	return out;
}


call_class::~call_class()
{
	delete[]call_DB;
}


int main()
{
	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";

	call_class MyClass;

	cout << MyClass.is_full() << MyClass.is_empty() << endl;

	cout << "Finish TEST1: testing the default constructor\n\n\n\n";

	cout << "Test2: Testing add, double_size, process, and is_full() \n";

	MyClass.add();

	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, serach, and is_empty\n";

	MyClass = MyClass - "5617278899";

	MyClass = MyClass - "9546321555";

	MyClass = MyClass - "1234567890";

	cout << "key 1234567890 is present at this index " << MyClass.search("1234567890") << endl;

	cout << "key 9546321555 is present at this index " << MyClass.search("9546321555") << endl;

	cout << "key 5617278899 is present at this index " << MyClass.search("5617278899") << endl;;
	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";

	cout << MyClass << endl;

	// writing into file
	ofstream fout;

	fout.open("stats7_output.txt");

	fout << MyClass << endl;

	cout << "Fist TEST4\n\n\n\n";
	cout << "The destructor will be called automatically\n";

	return 0;
}