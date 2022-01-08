#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#include <vector>

using namespace std;



  void getDataFromFile(string path, string &input, int lineNo) //?get Data of given path file line in string
  {
    ifstream get(path.c_str(), ios::in); // file opened in reading mode

    if (!get.is_open()) // if file is not opened
    {
      //scrClr();
      //setCursorPos(9, 28);
      cout << "DATA BASE-ERROR : 404 ";
      //scrClr(2);
      exit(1);
    }
    else // if file is opened
    {
      int FileLine = 1;          // start from first line
      while (FileLine <= lineNo) // whille fileline is <= lineno then
      {
        getline(get, input); // get data
        FileLine++;          // increment the fileline
      }
    }
    get.close(); // file closed
  }

  short int readDataFromCSV(string filePath,unsigned int max_row,vector<string> &data)
  {

    string t_str,t2_str;
    unsigned int count = 0;
    while(count < max_row)
    {   
        count++;
        t_str.clear();
        t2_str.clear();
        getDataFromFile(filePath,t_str,count+1);
        std::replace( t_str.begin(), t_str.end(), ',', '|'); // replace all 'x' to 'y'
        t2_str = to_string(count) ;
        t2_str += "|"+ t_str;
        data.push_back(t2_str);
        
    }

    //error validation coding should be done 
    //and acccording to that error code should be given here
    // 1 is reserved for successful csv reading 

   return(1);
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + replaceStr.size());
    }
}

int main(int args, char * argv[])
{

/**** writing to excel file ****/
/* ofstream MyExcelFile;
 MyExcelFile.open("F:\\test.csv");

MyExcelFile << "First Name, Last Name, Middle Initial" << endl;
MyExcelFile << "Drashti, Dhola, I." << endl;
MyExcelFile << "Dhaval, Dhola, I." << endl;
cout << "file created";
MyExcelFile.close();
*/

/**** reading from excel file *****/

string filePath,file_name,file_path_bckp;
cout<<"enter file path : ";
cin>>filePath;

file_path_bckp = filePath;

file_name = filePath.substr(filePath.find_last_of("\\")+1); 

findAndReplaceAll(file_path_bckp,".xlsx",".csv");
// 
// cout<<" path : "<<file_path_bckp<<endl;

rename(filePath.c_str(),file_path_bckp.c_str());

ifstream is(file_path_bckp,ios::in);
string line;

// while (getline(is, line))
// {
    // const char *begin = line.c_str();
    // cout << line << endl;   // row wise reading
// 
    //strip beyond first comma
    // if (const char *end = strchr(begin, ','))
    // {    
// 
        // const char *mid = end - begin ;
// 
        // string column1(begin, mid);
        // cout << column1 << endl;  // column wise reading
// 
        // string column2((mid+1),end);
        // cout << column2 << endl;  // column wise reading
// 
// 
    // }
// }
// 
// is.close();
vector<string> data;
readDataFromCSV(file_path_bckp,5,data);

for(auto i=data.begin(); i!=data.end();i++) 
{
  cout << endl << (*i);
}

return 0;
}