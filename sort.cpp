#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    vector<string> buffer;
    fstream fin("sample.txt",ios::in);

    string line;
    if(!fin.is_open())
    {
        cout<<" FILE IS NOT OPENED !";
    }
    else
    {
        getline(fin,line);
        while(!fin.eof())
        {
             getline(fin,line);
             buffer.push_back(line);      //pushback function :- inbuilt vector function
        }  
    }
    
    cout<<endl<<"bufferdata"<<endl;

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
        cout << *i<<endl;

    sort(buffer.begin(), buffer.end());

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
        cout << *i<<endl;
     return 0;
}
