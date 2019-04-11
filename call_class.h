#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef CALL_CLASS_H
#define CALL_CLASS_H

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
	call_class(const call_class &);
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in list; otherwise return -1
	void add(); //adds the informaation for a call record to call_DB
	call_class & operator-(const string key); //removes an item from the list
	void double_size();
	void process();
	friend ostream & operator<<(ostream & out_to_file, call_class & Org); //prints all the elements in the 
																		  //list to the screen and to the file "stats7_output.txt".
private:
	int count;
	int size;
	call_record *call_DB;
};

#endif