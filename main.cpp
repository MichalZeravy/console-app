// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include "Counter.h"

using namespace std;

int main(int argc, char *argv[])
{
	int n;
	string str, str1, str2, line;

	if (argc == 1)
		cout << "Nebol zadany ziaden parameter";
	if (argc == 2)
	{
		if ("-c" == (string)argv[argc - 1])
		{
			getline(cin, str);
			cout <<"Pocet znakov je: "<< spocitaj<_char>(str) << endl;
			
		}

		if ("-w" == (string)argv[argc - 1])
		{
			getline(cin, str);
		
			cout <<"Pocet slov je: "<< spocitaj<_word>(str) << endl;
		}
	
		if ("-l" == (string)argv[argc - 1])
		{
			
			int s = 0;
			while (getline(cin, line)) 
			{
				s++;
				if (line == "^")
					break;

				str+= '\n' + line;
			}
			cout << "Pocet riadkov je:" << spocitaj<_line>(str) <<endl;
		}
			
	}
	
	if (argc == 3)
	{
		fstream subor((string)argv[argc - 1]);
		while (!subor.eof())
		{
			getline(subor, str1);
			str2 = str2 + '\n' + str1;
		}

		if ("-c" == (string)argv[argc - 2])
		{
			cout << "Pocet znakov je: " << spocitaj<_char>(str2) << endl;
		}

		if ("-w" == (string)argv[argc - 2])
		{
			cout << "Pocet slov je: " << spocitaj<_word>(str2)-1 << endl;
		}

		if ("-l" == (string)argv[argc - 2])
		{
			cout << "Pocet riadkov je:" << spocitaj<_line>(str2) << endl;
		}

	}
	system("pause");
	
	return 0;
}
