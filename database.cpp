#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>

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
    void lockDataBase(string &path) 
    {  

        tempStorage = path;
        path = path + "\\Desktop.ini";

        writeDataToFile(path,"[.shellClassInfo]\n");
        writeDataToFile(path,"CLSID = {63E23168-BFF7-4E87-A246-EF024425E4EC}\n");
        
        command = "attrib +h +s " + tempStorage;
        WinExec(command.c_str(),0);

    }  
    void unlockDataBase(string &path)
    {
        tempStorage = path;
        path = path + "\\Desktop.ini";
        
        command = "del ";
        command =  command + path;
        system(command.c_str());
        
        command.clear();
        command = "attrib -h -s " + tempStorage;
        WinExec(command.c_str(),0);
        
    }

    public:

    dataBase(string &status,string &path)
    {
      if(status=="unlock")
      {
          unlockDataBase(path);
      }
      else if(status=="lock")
      {
          lockDataBase(path);
      }
    }
    ~dataBase()
    {
   
    }

    protected:

};

int main(int argc, char* argv[])
{
    if(argc==1)
    {
      cout<<"No Arguments Provided "<<endl;
      exit(1);
    }
    else
    {  
       string status(argv[1]),path(argv[2]);
       if(status=="lock"||status=="unlock") 
       {
          dataBase D(status,path);
       }
       else
       {
         cout<<"First Parameter is Incorrect "<<endl;exit(1);
       }
    }
   
    return(0);
}
