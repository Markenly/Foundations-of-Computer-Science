#include <iostream>

#include <string>

#include <fstream>

using namespace std;

struct order_record {

string cell_number;

string item_number;

double quantity;

double price;

int processing_plant;

double tax_rate;

double order_tax;

double net_cost;

double total_cost;

};

void input(ifstream &, order_record &);

void output(const order_record &);

void process(order_record &);


void input(ifstream &in, order_record &p_record)
{

in >> p_record.cell_number;

in >> p_record.item_number >> p_record.quantity >> p_record.price >>

p_record.processing_plant;

}


void output(const order_record &p_record)
{

//the magic formula.

cout.setf(ios::showpoint);

cout.precision(2);

cout.setf(ios::fixed);


cout << p_record.cell_number << "\t";


cout << p_record.item_number << "\t" << p_record.quantity << "\t"

<< p_record.price << "\t" << p_record.processing_plant << "\t"

<< p_record.tax_rate << "\t" << p_record.order_tax << "\t"

<< p_record.net_cost << "\t" << p_record.total_cost << endl;

}


void process(order_record &p_record)
{

if (0 <= p_record.processing_plant && p_record.processing_plant <= 50)

p_record.tax_rate = 6;

else if (51 <= p_record.processing_plant && p_record.processing_plant <= 110)

p_record.tax_rate = 7;

else if (111 <= p_record.processing_plant && p_record.processing_plant <= 200)

p_record.tax_rate = 8;

else if (201 <= p_record.processing_plant && p_record.processing_plant <= 500)

p_record.tax_rate = 9;

else if (p_record.processing_plant > 500)

p_record.tax_rate = 11;

p_record.order_tax =

p_record.quantity * p_record.price * (p_record.tax_rate / 100.0);

p_record.net_cost = p_record.quantity * p_record.price;

p_record.total_cost = p_record.net_cost + p_record.order_tax;

}


int main()
{

order_record customer_record;

ifstream in; // declaring an input file stream

in.open("purchase_data.txt");

if (in.fail()) 
{
  cout << "Input file did not open correctly" << endl;
} 
else 
{
  while (!in.eof()) 
{

input(in, customer_record);

process(customer_record);

output(customer_record);

}

}

in.close();

return 0;

}
