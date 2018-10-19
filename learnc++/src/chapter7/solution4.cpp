#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;

string str[21];
int numofstr = 0;

bool isnum(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}
int stoi( string &s){
   if(s.size()== 0) return 0; 
    int temp = (int)(s[0]-'0');;
    for (int i = 1; i < s.length(); i++)
    {
        temp = temp*10+(int)(s[i]-'0');
        
    }
    return temp;
}
int find()
{
	char s;
	int n;
	cin >> s >> n;
	return str[n].find(s);
}

int rfind()
{
	char s;
	int n;
	cin >> s >> n;
	return str[n].rfind(s);
}

int get_int()
{
	string str;
	cin >> str;
	if (isnum(str))
	{
		return stoi(str);
	}
	else
	{
		if (str == "find")
		{
			return find();
		}
		else if (str == "rfind")
		{
			return rfind();
		}
	}
	return 0;
}



string copy()
{
	int n, x, l;
	n = get_int();
	x = get_int();
	l = get_int();
	return str[n].substr(x, l);
}

string add();

string get_str()
{
	string str;
	cin >> str;
	if (str == "copy")
	{
		return copy();
	}
	else if (str == "add")
	{
		return add();
	}
	else
	{
		return str;
	}
}

string add()
{
	string s1 = get_str();
	string s2 = get_str();
    char temp[10]; 
	if (isnum(s1) && isnum(s2) && stoi(s1) >= 0 && stoi(s1) <= 99999 && stoi(s2) >= 0 && stoi(s2) <= 99999)
	{

        snprintf(temp, sizeof(temp), "%d", stoi(s1) + stoi(s2));
		return temp; 
	}
	else
	{
		return s1 + s2;
	}
}



void insert()
{
	string s = get_str();
	int n = get_int();
	int x = get_int();
	str[n].insert(x, s);
}

void reset()
{
	string s = get_str();
	int n = get_int();
	str[n] = s;
}

void print()
{
	int n = get_int();
	cout << str[n] << endl;
}

void printall()
{
	for (int i = 1; i <= numofstr; i++)
	{
		cout << str[i] << endl;
	}
}

int main()
{
	cin >> numofstr;
	for (int i = 1; i <= numofstr; i++)
	{
		cin >> str[i];
	}
	while (true)
	{
		string operation;
		cin >> operation;
		if (operation == "insert")
		{
			insert();
		}
		else if (operation == "reset")
		{
			reset();
		}
		else if (operation == "print")
		{
			print();
		}
		else if (operation == "printall")
		{
			printall();
		}
		else if (operation == "over")
		{
			break;
		}
	}
	return 0;

}
