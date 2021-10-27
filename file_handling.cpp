#include<stdio.h> //* C file
#include<iostream> //* C++ file 
#include<fstream> //* file handling functions access
#include<string.h> //* string read by getline()


using namespace std;


ifstream* readDataFromFile(string path)
{
    
 ifstream *read = new ifstream;

 read->open(path.c_str(),ios::in);
 if(!read->is_open())
 {
    cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<<endl; 
 }
 else
 {  
    return (read);
 }
 
}
int main()
{
   string DATA,testPath = "C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\USER_INFO\\userdetails.txt"; 
   ifstream *FILE_READ = readDataFromFile(testPath);

   getline(*(FILE_READ),DATA);

   cout<<endl<<DATA<<endl;

    return 0;
}
