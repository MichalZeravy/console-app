#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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
		int t = 1;
		for (int i = 0; i < length() - 1; i++)
			if (at(i) == '\n')
			{
				t++;
			}
		return t;
	}
};