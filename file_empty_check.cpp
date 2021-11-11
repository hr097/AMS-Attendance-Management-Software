#include<iostream>
#include<fstream>

using namespace std;
 

int main()
{
	ifstream read("test.txt",ios::in);

	if(!read) return 0;

	bool isEmpty = read.peek() == EOF;
	
	cout << boolalpha << "test is empty = " << isEmpty<<endl;

	return 0;
}