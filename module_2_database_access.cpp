#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdio.h>

using namespace std;

int main()
{
    // int i,j,total;
    vector<string> buffer;
    fstream fin("sample.txt",ios::in);
    // char data[15][50], newdata[50];

    string line,course_name,sem,subject,command;
    // fin.open; //*in -->reading mode
    if(!fin.is_open())
    {
        cout<<" FILE NOT OPENED !";
    }
    else
    {
        getline(fin,line);
        
        while(!fin.eof())
        {    
            buffer.push_back(line);
            getline(fin,line);
        }  
    }
    
    cout<<endl<<"bufferdata"<<endl;

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
        cout << *i<<endl;

    sort(buffer.begin(), buffer.end());
    string displayData[buffer.size()][3];

    //cout<<buffer.size()<<endl;
    //  for (auto i = buffer.begin(); i != buffer.end(); ++i)  
        //  cout << *i<<endl;
        // 

    command = course_name + "-" + sem + "-" + subject;
    cout<< endl << command;
    
    int j=0;

    for (auto i = buffer.begin(); i != buffer.end(); ++i,++j)
    {
        string data = (*i);
        //cout<<endl<<"data : "<<data<<endl;
        int found_pos = data.find("|");
        
        displayData[j][0] = data.substr(0,(found_pos));
        int temp_pos = (found_pos+1);
        
        // |1|
        // AMS|10|AMS_S

        found_pos = data.find("|",temp_pos);
        displayData[j][1] = data.substr(temp_pos,(found_pos-temp_pos));
        temp_pos = (found_pos+1);

        found_pos = data.find("|", temp_pos);
        displayData[j][2] = data.substr(temp_pos,(found_pos-temp_pos));
        temp_pos = (found_pos+1);

        //found_pos = data.find("|", temp_pos);
        displayData[j][3] = data.substr(temp_pos);

        cout<<endl<<displayData[j][0]<<"\t"<<displayData[j][1]<<"\t"<<displayData[j][2]<<"\t"<<displayData[j][3];   

    }
    


     return 0;
}