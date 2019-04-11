/*************************************************
Name: Markenly Alusma
Z#: Z23236012
Course: Foundations of Computer Science (COP3014)
Professor: Dr. Lofton Bullard
**************************************************/

#include<iostream>

#include<stdlib.h>

#include<string.h>

#include<fstream>

using namespace std;


void reading_file(ifstream& myfile);

int main()
{

	ifstream myfile;

	//Call to reading_file function
	reading_file(myfile);

	return 0;
}


void reading_file(ifstream& myfile)

{
	string input;

	//Read the text file
	myfile.open("mytext.dat");

	//reads the data of the file by opening it
	if (myfile.is_open())

	{
		//reading lines of the file
		while (getline(myfile, input))
		{

			int count[26] = { 0 }, i, wordCount = 0;

			//checking cases

			for (i = 0; i < input.size(); i++)
			{
				if (((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) && (input[i + 1]
					== '.' || input[i + 1] == ',' || input[i + 1] == ' ')) wordCount++;

				if (input[i] >= 'a' && input[i] <= 'z') count[input[i] - 'a']++;

				if (input[i] >= 'A' && input[i] <= 'Z') count[input[i] - 'A']++;
			}

			//number of words

			char x = input[input.size() - 1];

			if (x != '.' && x != 'z' && x != ' ')

				wordCount++;

			cout << endl << wordCount << " words" << endl;

			for (i = 0; i < 26; i++)
			{
				if (count[i] > 0) cout << count[i] << " " << (char)('a' + i) << endl;
			}
		}


		myfile.close();

	}

	else cout << "file unable to open";

}