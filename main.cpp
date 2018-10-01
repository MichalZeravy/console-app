// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	int n,it;
	string str, line;
	if (argc == 1)
		cout << "Nebol zadany ziaden parameter";
	if (argc == 2)
	{
		if ("-c" == (string)argv[argc - 1])
		{
			getline(cin, str);
			n = str.length();
			cout <<"Pocet znakov je: "<< n << endl;
			//std::istream s(std::string(argv[1]));
			//std::istream_iterator<char> it = s->begin();
		}

		if ("-w" == (string)argv[argc - 1])
		{
			int s=0;
			getline(cin, str);
			n = str.length();
			for (int i = 0; i < n-1; i++)
				if (isspace(str[i]))
					s++;
			if (s == 0 && isalpha(str[0]))
				s = 1;

			cout <<"Pocet slov je: "<< s;


		}
		//funkcnost plus nastudovat ako nacitavat viacej riadkov 
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
