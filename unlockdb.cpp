#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#include <direct.h>
#include <shlobj.h>

using namespace std;

class dataBase
{
    private:

    string tempStorage,command;

    void writeDataToFile(string path, string write_data) //?write string data to given path file at latest line
    {
        ofstream write(path.c_str(), ios::app); //file opened in append mode 
    
        if (!write.is_open())//if file is not opened 
        { 
          cout << "something went wrong...";
          exit(1);
        }
        else
        {
          write << write_data << endl; // write data
        }
         write.close();//file closed
    }

    string getDataBasePath()
    {
      string AMS_Path;

      CHAR pathDocument[MAX_PATH];   // string to store path
      HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL,SHGFP_TYPE_CURRENT,pathDocument); // getting documents path
  
      if (result == S_OK) // check if documents path is successfully stored in pathdocuments
      {
        AMS_Path = pathDocument;       // take original documents path into string
        AMS_Path = AMS_Path + "\\{JSN-1008-JSK-22-10-2021}"; // making AMS folder path
      }
      else
      { 
        cout <<endl << "something went wrong....";
        exit(1);
      }

      return(AMS_Path);
    }

    public:

    void unLockDataBase()
    {   
        string path = getDataBasePath();
        tempStorage = path;
        path = path + "\\mn-cs-gxv-jsnfe-1008-jsn-db-lock.ini";
        
        command = "del ";
        command =  command + path;
        system(command.c_str());
        
        command.clear();
        command = "attrib -h -s " + tempStorage;
        WinExec(command.c_str(),0);
    }

    dataBase()
    {

    }
    ~dataBase()
    {
   
    }

    protected:

};

int main()
{   
    dataBase D;
    D.unLockDataBase();
    return(0);
}
