#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    // int i,j,total;
    vector<string> buffer;
    fstream fin("sample.txt",ios::in);
    // char data[15][50], newdata[50];

    string line;
    // fin.open; //*in -->reading mode
    if(!fin.is_open())
    {
        cout<<" FILE NOT OPENED !";
    }
    else
    {
        getline(fin,line); // For read the input from file
        while(!fin.eof())
        {
             getline(fin,line);
             buffer.push_back(line);
             
        }  
    }
    
    cout<<endl<<"bufferdata"<<endl;

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
        cout << *i<<endl;

    sort(buffer.begin(), buffer.end());  // Sort the data of File

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
        cout << *i<<endl;
     return 0;
}

//* COURSE, COURSELIST, --> BUCKETS [string] -->SEM --> SUBJECT
