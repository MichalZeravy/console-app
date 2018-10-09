#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int counterznak(string str)
{
	int p;
	p= str.length();
	for (int i = 0; i <= p; i++)
		if (isspace(str[i]))
			p--;
	return p;
}

int counterword(string str)
{
	int n, s = 0;
	n = str.length();
	for (int i = 0; i < n ; i++)
		if (isspace(str[i]))
			s++;
	if (isalpha(str[n-1]))
		s++;
	if (s == 0 && isalpha(str[0]))
		s = 1;
	return s;
}

int counterline(string str)
{
	int s = 0;
	for (int i = 0; i < str.length() - 1; i++)
		if (str[i] == '\n')
		{
			s++;
		}	
	
	return s;
}


template<typename T>
size_t spocitaj(string str) {
	T obj(str);
	return obj.spocitaj();
}


struct _char:public string
{
	_char(string str) :string{ str }
	{};
	size_t spocitaj()
	{
		int p;
		p = length();
		for (int i = 0; i <= p; i++)
			if (isspace(at(i)))
				p--;
		return p;
	}
	
};

struct _word:public string
{
	_word(string str) :string{ str }
	{};
	size_t spocitaj()
	{
		int n, t = 0;
		n = length();
		for (int i = 0; i < n; i++)
			if (isspace(at(i)))
				t++;
		if (isalpha(at(n - 1)))
			t++;
		if (t == 0 && isalpha(at(0)))
			t = 1;
		return t;
	}
};

struct _line:public string
{
	_line(string str) :string{ str }
	{};
	size_t spocitaj()
	{
		int t = 0;
		for (int i = 0; i < length() - 1; i++)
			if (at(i) == '\n')
			{
				t++;
			}
		return t;
	}
};