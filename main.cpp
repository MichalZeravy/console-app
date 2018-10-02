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
	int n,it;
	string str, line;
	FILE* subor;
	if (argc == 1)
		cout << "Nebol zadany ziaden parameter";
	if (argc == 2)
	{
		if ("-c" == (string)argv[argc - 1])
		{
			getline(cin, str);
			cout <<"Pocet znakov je: "<< counterznak(str) << endl;
			//std::istream s(std::string(argv[1]));
			//std::istream_iterator<char> it = s->begin();
		}

		if ("-w" == (string)argv[argc - 1])
		{
			getline(cin, str);
		
			cout <<"Pocet slov je: "<< counterword(str);
		}
	
		if ("-l" == (string)argv[argc - 1])
		{
			
			int s = 0;
			while (getline(cin, line)) 
			{
				s++;
				if (line == "^")
					break;

				str+= " " + line;
			}
			cout << "Pocet riadkov je:" << s <<endl;
		}
			
	}
	system("pause");
	
	return 0;
}
