#include <windows.h> 
#include <iostream> 

#include <string>//*for string conversion functions

//--------DOCUMENT PATH GETTING------/

#include <shlobj.h> 
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

//--------DOCUMENT PATH GETTING------/

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

string convertIntToString(int &in)
{
 string str = to_string(in);
 return str;
}

string convertArrayTostring(char* arg) //meaning itself defining
{
  string re(arg);
  return re;
}

int dirExists(const char *path) //checking function if directory exists or not 1=EXIST 0=NOT EXIST
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
    
    string AMS_Path,SemCreatePath,command;  //backup variable for root path

    if (result == S_OK)  //check if  documents path is successfully stored in pathdocuments
    { 
        ////cout<< "Path found: "<<pathDocument<< "\n";

        AMS_Path = pathDocument; // take original documents path into string
        AMS_Path =  AMS_Path + "\\AMS"; //making AMS folder path
        
        /*TEMP AREA VARIABLE*/
       
        string courseName="BscIT";
        int sem=2;
        /***/
    
        
        SemCreatePath = AMS_Path + "\\" + courseName +"" + "SEM" +""+ convertIntToString(sem); //backup for getting ROOT-OF-AMS  path
        
        //cout<<endl<<SemCreatePath<<endl;

        if(!dirExists(SemCreatePath.c_str())) //if directory not exists then create it
        {  
            command = "mkdir " +  SemCreatePath;                //making commad which will pass in cmd
            ////cout<<"commad 1 for creating directory "<<command<<endl;
            system(command.c_str());      // creating  directory by CMD
             
            /*********************  FOLDERS *******************/
            
             command = "mkdir " + SemCreatePath + "\\DAILY_RECORD" ; // making COMMAND FOR DAILY_RECORD folder
             ////cout<<"commad 1 for creating directory "<<command<<endl;
             system(command.c_str()); // creating DAILY_RECORD directory by CMD
             
             command = "mkdir " + SemCreatePath + "\\FAC-STUD_DETAILS" ; // making COMMAND FOR FAC&STUD_DETAILS folder
             ////cout<<"commad 1 for creating directory "<<command<<endl;
             system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD
             
             command = "mkdir " + SemCreatePath + "\\MONTHLY_RECORDS" ; // making COMMAND FOR MONTHLY_RECORDS folder
           ////  cout<<"commad 1 for creating directory "<<command<<endl;
             system(command.c_str()); // creating MONTHLY_RECORDS directory by CMD

             /**************************************************/
             
             /*******************  FILES *********************/
             
              command = "cd. > " + SemCreatePath + "\\DAILY_RECORD\\records.txt"; // RECORDS.TXT file
              system(command.c_str()); 
               
              command = "cd. > " + SemCreatePath + "\\FAC-STUD_DETAILS\\faculty"+"_sem_"+ convertIntToString(sem)+".txt"; // faculty_details.TXT file
              system(command.c_str());  
               
              command = "cd. > " + SemCreatePath + "\\FAC-STUD_DETAILS\\student"+"_sem_"+ convertIntToString(sem)+".txt"; // student_details.TXT file
              system(command.c_str()); 

              /***********************************************/
        }
        else 
        {
          ////cout<<endl<<"\nDirectory Already Exist\n";
        }
    }
    else
    {
        cout << "Error Path Not found: " << result << "\n";
    }
    return 0; 
}