#include <windows.h> 
#include <iostream> 

/*--------DOCUMENT PATH GETTING------*/

#include <shlobj.h> 
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

/*--------DOCUMENT PATH GETTING------*/

using namespace std;

#pragma comment(lib, "shell32.lib")  //? for document path finding 


void convertStringtoArray(string arg,char* argcopy) //meaning itself defining
{
  int i;
  for(i=0;i<arg.length();i++)
  {
   *(argcopy+i) = arg[i];
  }
  *(argcopy+i)='\0';
}

string convertArrayTostring(char* arg) //meaning itself defining
{
  string re(arg);
  return re;
}


int dirExists(const char *path) //checking function if directory exists or not 
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

int main()
{   
    CHAR pathDocument[MAX_PATH]; //string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathDocument);  //getting documents path
    
    string ApplicationPath,command;  //backup variable for root path

    if (result == S_OK)  //check if  documents path is successfully stored in pathdocuments
    { 
        ////cout<< "Path found: "<<pathDocument<< "\n";

        string AMS_Path=pathDocument; // take original documents path into string

        AMS_Path =  AMS_Path + "\\{JSN-1008-JSK-22-10-2021}"; //making AMS folder path
        ApplicationPath = AMS_Path; //backup for getting ROOT-OF-AMS  path


        int check = dirExists(AMS_Path.c_str()); // check will have 1=exists 0=not_exists

        if(!check) //if directory not exists then create it
        {  
            command = "mkdir " +  AMS_Path; //making commad which will pass in cmd
            ////cout<<"commad 1 for creating directory "<<command<<endl;
            system(command.c_str()); // creating AMS directory by CMD
           ////cout<<endl<<"\nDirectory Created \n";

            command = "mkdir " + ApplicationPath + "\\LOG-INFO"; //making commad which will pass in cmd

            system(command.c_str()); // creating LOG_INFO directory by CMD

            command = "mkdir " + ApplicationPath + "\\USER-INFO"; //making commad which will pass in cmd
            system(command.c_str()); // creating USER_INFO directory by CMD

            command = "mkdir " + ApplicationPath + "\\OTHER"; //making commad which will pass in cmd
            system(command.c_str()); // creating OTHER directory by CMD

            command = "mkdir " + ApplicationPath + "\\LOG-INFO\\APPLOG"; //making commad which will pass in cmd
            system(command.c_str()); // creating APPLOG directory by CMD
            
            command = "cd. > " + ApplicationPath + "\\LOG-INFO\\APPLOG\\logs.txt"; //making commad which will pass in cmd


            system(command.c_str()); // creating  file logs.txt  by CMD


            command = "cd. > " + ApplicationPath + "\\USER-INFO\\userdetails.txt"; //making commad which will pass in cmd
            system(command.c_str()); // creating  file userdetails.txt  by CMD

            command = "cd. > " + ApplicationPath + "\\OTHER\\semesterRecord.txt"; //making commad which will pass in cmd
           //// cout<<endl<<command<<endl;
            system(command.c_str()); // creating  file semesterRecord.txt  by CMD
           
            command = "cd. > " + ApplicationPath + "\\LOG-INFO\\logincredentials.txt"; //making commad which will pass in cmd
            ////cout<<command<<endl;
            system(command.c_str()); // creating  file userdetails.txt  by CMD


        }
        else 
        {
          cout<<endl<<"\nDirectory Already Exist\n";
        }

    }
    else
    {
        cout << "Error Path Not found: " << result << "\n";
    }

    
   
    return 0; 
}
