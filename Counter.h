#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int counterznak(string str)
{
	return str.length();
}

int counterword(string str)
{
	int n, s = 0;
	n = str.length();
	for (int i = 0; i < n - 1; i++)
		if (isspace(str[i]))
			s++;
	if (s == 0 && isalpha(str[0]))
		s = 1;
	return s;
}

int counterline(string str)
{
	int s = 0;
	for (int i = 0; i < str.length() - 1; i++)
		if (isspace(str[i]))
			s++;
	
	return s;
}