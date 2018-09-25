// app.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	int n, it;
	string str;
	if (argc == 1)
		cout << "Nebol zadany ziaden parameter";
	if (argc == 2)
	{
		if ("-c" == (string)argv[argc - 1])
		{
			getline(cin, str);
			n = str.length();
			cout << n << endl;
			//std::istream s(std::string(argv[1]));
			//std::istream_iterator<char> it = s->begin();
		}

		if ("-w" == (string)argv[argc - 1])
		{
			getline(cin, str);
			cout << str;
			int s;
			n = str.length();
			for (int i = 0; i < n; i++)
				if (isspace(str[i]))
					s++;
			cout << s;


		}
		//funkcnost plus nastudovat ako nacitavat viacej riadkov 
		if ("-l" == (string)argv[argc - 1])
		{
			getline(cin, str);
			cout << "-l";
		}
			
	}
	system("pause");
	
	return 0;
}
