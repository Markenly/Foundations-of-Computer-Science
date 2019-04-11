/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "call_class.h"

using namespace std;


int main()
{
	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";

	call_class MyClass;

	cout << "Finish TEST1: testing the default constructor\n\n\n\n";

	cout << "Test2: Testing add, double_size, process, and is_full() \n";

	MyClass.add();

	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, search, and is_empty\n";

	MyClass - "5617278899" - "9546321555" - "1234567890";

	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";

	cout << MyClass << endl;

	cout << "Finish TEST4\n\n\n\n";

	cout << "The destructor will be called automatically\n";

	cout << "TEST1: Testing the Default Constructor, is_full and double_size\n";

	call_class YourClass = MyClass;

	cout << "Finish TEST1: testing the default constructor\n\n\n\n";

	cout << "Test2: Testing add, double_size, process, and is_full() \n";

	YourClass.add();

	cout << "Finish TEST2\n\n\n\n";

	cout << "Test3: Testing operator-, search, and is_empty\n";

	YourClass - "5617278899" - "9546321555" - "1234567890";

	cout << "Finish TEST3\n\n\n\n";

	cout << "Test4: Testing operator<<\n\n";

	cout << YourClass << endl;

	cout << "Finish TEST4\n\n\n\n";

	cout << "The destructor will be called automatically\n";


	return 0;
}