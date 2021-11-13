#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include<vector>
#include<stdlib.h>
#include<algorithm>
#define TN 10
using namespace std;

void InvalidInputErr() //*invalid input error function
{
  cout<<"INVALID CHOICE ENTERTED !"<<endl;
  cout<<"PLEASE RE-ENTER YOUR CHOICE CORRECTLY !"<<endl;
}

int validateString(string input,int Bnd,int start) //* string input validate as integer
{
    int flag=0,tem=1;
    if(start==0)
    start++;      
    for(tem=start;tem<=Bnd;tem++)
    {
        
        if(to_string(tem) == input) //convert tem int to string to check input valid condition
        {
          flag = 1; 
          break;
        }
    }
  
    if(flag==0)  //*IF flag=0 means input is invalid 
    {
      InvalidInputErr(); //*error msg
      return 0;
    }
    else
    {
      return tem; //*returns converted string.to_int(INt)
    }
}

string date()
{
    string date;
    time_t tmNow;
    tmNow = time(NULL);
    struct tm t = *localtime(&tmNow);
    date = to_string(t.tm_mday) + "-" + to_string(t.tm_mon + 1) + "-" + to_string(t.tm_year + 1900);
    return date;
}

string lastline()
{
    ifstream fin;
     string lastLine;  
    fin.open("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\BSCIT-SEM-2-C\\DAILY-RECORD\\records.txt");
    if(fin.is_open()) {
        fin.seekg(-1,ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            fin.get(ch);                            // Get current byte's data

            if((int)fin.tellg() <= 1) {             // If the data was at or before the 0th byte
                fin.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if(ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                fin.seekg(-2,ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }  
        getline(fin,lastLine);                      // Read the current line
        //cout << "Result: " << lastLine << '\n';     // Display it
        fin.close();

       
    }
 return lastLine;
}

void lastlineDlt()
{
    string line; 
    vector<string> lines;
    std::ifstream inputStream("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\BSCIT-SEM-2-C\\DAILY-RECORD\\records.txt");
    
    while (getline(inputStream,line)) {
        lines.push_back(line);
    }
    inputStream.close();
    
    std::fstream outputStream("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\BSCIT-SEM-2-C\\DAILY-RECORD\\records.txt", ios::out | ios::trunc);
    if (outputStream.is_open())
    {
        for (int i=0; i < lines.size()-1; i++)
        {
            outputStream << lines[i] << "\n";
        }
        outputStream.close();
    }
}

int ValidateAttendance(string input)
{
    for(int i=0;i<input.length();i++)
    {
        input[i] = toupper(input[i]);
    }
    if(input == "P" || input == "A")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int i,tem,ConvertChoiceToINT;
    vector<string> buffer;
    string data,MCH,ACH,choice;
    
    fstream fout("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\BSCIT-SEM-2-C\\DAILY-RECORD\\records.txt", ios::app | ios::in);

    if (!fout.is_open())
    {
        cout << "your file is not open";
    }
    else
    {
        i = lastline().find("|");
        data = lastline().substr(0,i-1);
        if(data != date())
        {
            cout<<"\n\t\tYou have already taken attendance for today\n";
        }
        else
        {
            fout<<"\n"+date() + " | ";
            for(i = 1;i<= TN ;i++)
            {    
                fout<<"P";
            }
            fout.close();
            fout.open("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\BSCIT-SEM-2-C\\DAILY-RECORD\\records.txt",ios::app);
            i = lastline().find("|");
            data = lastline();

            while(1)
            {
                cout << "Enter Absent Roll No : " <<endl;
                getline(cin,MCH);
                ConvertChoiceToINT = validateString(MCH,TN,1);
                if(ConvertChoiceToINT)
                {
                    data.replace((i+1+ConvertChoiceToINT),1,"A");
                    //cout << data << endl;
                    lastlineDlt();
                    cout << " Do you want to continue  ?" <<endl;
                    getline(cin,choice);
                    if(choice == "no")
                    {
                        break;
                    }
                }
            }
            fout<<data;
            fout.close();
            
            data = lastline();
            i = data.find("|");
            data = lastline().substr(i+2,data.length());
            cout << "Present List"<<endl;

            for(i=0;i<data.length();i++)
            {
               if(data[i] == 'P')
               {
                   cout << i+1 << " ";
               }
            }
            cout << "\nAbsent List"<<endl;
            for(i=0;i<data.length();i++)
            {
               if(data[i] == 'A')
               {
                   cout << i+1 << " ";
               }
            }

            while(1)
            {
                cout<<"\n\nPress 1 for Submit\n";
                cout<<"\nPress 2 for Modification\n\n";
                cout<<"Enter your Choice = ";
                getline(cin,MCH);
                
                switch(validateString(MCH,2,1))
                {
                    case 1:{
                        fout.close();
                        cout<<"\n\nDone\n\n";
                        exit(1);
                        break;
                    }
                    case 2:{
                        fout.close();
                        reAskRollNo:
                        cout<<"\n\nEnter Roll Number for Modification = ";
                        getline(cin,MCH);
                        ConvertChoiceToINT = validateString(MCH,TN,1);
                        if(ConvertChoiceToINT)
                        {
                            reAskAtd:
                            cout<<"\n\nEnter Attendance For roll no "<<MCH << " :";
                            getline(cin,ACH);
                            if(ValidateAttendance(ACH))
                            {
                                fout.open("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\BSCIT-SEM-2-C\\DAILY-RECORD\\records.txt",ios::app);
                                data = lastline().find("|");
                                data = lastline();
                                data.replace((i+1+ConvertChoiceToINT),1,ACH);
                                lastlineDlt();
                                fout<<data;
                                fout.close();
                            }  
                            else  
                            goto reAskAtd;
                       }
                       else
                       goto reAskRollNo;
                    }

                }
            }
            
        }
        

    }
    return 0;
}