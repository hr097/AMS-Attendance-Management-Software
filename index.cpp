#include<iostream>     // * c++ code style use
#include<stdio.h>     //* for c style code use 
#include<stdlib.h>   // * standard library like dynamic memory allocation and exit macros and other.. 
#include<conio.h>   // *  console input output
#include<windows.h> // * windows console related functions handle
#include<unistd.h> // * for sleep function
#include<iomanip> // * for manipulator
#include<cwchar>  //*for console font purpose 
#include<string.h> //*  string related functions access
#include<stdbool.h> // * boolean operation
#include<math.h> //* math operations
#include<fstream> //* file handling functions access
#include<string> //* string library function access
#include<regex>  //* for email validation access
#include<algorithm>//* transform functions access

//--------FOR-DOCUMENT PATH GETTING------/

#include <shlobj.h> 
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

#pragma comment(lib, "shell32.lib")  //? for document path finding 

//--------FOR-DOCUMENT PATH GETTING------/

#ifndef _WIN32_WINNT  //*if that macro not exist then condtional compila6ion would be done and those files will be included
  #define _WIN32_WINNT 0x0601
  #include<wincon.h>
  #include<string>

  //#endif  // user 1 

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

#endif // user 2


using namespace std; //? standard namespace for  resolving naming coflicts

/*******************APP-CONTROL_CLASS********************************/



class APP //*GRAND PARENT CLASS
{

  public:

  static int MODULE_CHOICE; //*module selector static variable
  
  APP(){ }

  void SetColor(int ForgC) //?for setting individual text color
  {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;//We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
  }
  
  void setCursorPos(int x, int y=0) //?IMPORTANT : ->relative position is set
  {
    
    //*vertical lines space 
  
    while(x>0)
    {
      cout<<endl;  
      x--;
    }
    while(y!=0) //*horizontal cursor space by 1 charecter
    {
      printf(" ");
      y--;
    }
    
  }
  
  void ShowConsoleCursor(bool showFlag) //? for hiding the cursor just  set showFlag = false(bool value)
  {
      HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  
      CONSOLE_CURSOR_INFO     cursorInfo;
  
      GetConsoleCursorInfo(out, &cursorInfo);
      cursorInfo.bVisible = showFlag; // set the cursor visibility
      SetConsoleCursorInfo(out, &cursorInfo);
  }

  void scrClr(float i=0.0) //?for clearing screen afer some time
  {
    //*by default set to zero with default arguements
    sleep(i); // * going in sleep mode
    system("cls"); // * clear screen
  }

  void buildVerticalWall(int briks) //? for making vertical side
  { cout<<"*";
    while(briks>0){cout<<"-";briks--;} 
    cout<<"*";
  }
  
  void buildHorizontalWall(int endBrick,string data) //? for making horizontal side
  { 
    cout<<"|";
    int run=1;
    int line_start = int(endBrick / 6);
  
    while(run<endBrick)
    {
      
      if(run == line_start)
      {
        cout<<data;
        run+=(data.length()-1);
        cout<<" ";
      }
      else
      {
      cout<<" ";
      }
  
     run++;
    } 
    cout<<"|";
  }

  void debug(int do_what=0) //?for debugging purposes at last we will delete it 0=pause 1=pause & print
  {
    #include<conio.h> // * console input output library
    if(!do_what)
    getch();
    else
    cout<<endl<<"DEBUGING"<<endl;
  } 

  void startApp() //? for startup of home screen
  {
    if(MODULE_CHOICE==0) //* only 1 time initiaization function need to be called after 1 time just we need ro refresh home screen so is/else here
    {
      initApp();
      MODULE_CHOICE = HomeScreen();
    }
    else
    {
      MODULE_CHOICE = HomeScreen();
    }
    
  }
 


~APP() {}

private:
  
  void initApp() //?setting up first time APP screen by making console in full screen
  {

        // get handle to the console window
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        // retrieve screen buffer info
        CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
        GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

        // current window size
        short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
        short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

        // current screen buffer size
        short scrBufferWidth = scrBufferInfo.dwSize.X;
        short scrBufferHeight = scrBufferInfo.dwSize.Y;        

        // to remove the scrollbar, make sure the window height matches the screen buffer height
        COORD newSize;
        newSize.X = scrBufferWidth;
        newSize.Y = winHeight;

        // set the new screen buffer dimensions
        SetConsoleScreenBufferSize(hOut, newSize);

        ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

        setConsoleSize();

        system("color F0"); //set white background and text black
  
  }

  int HomeScreen() //*ask choice at Home screen of APP
  { 
       int line;

       gotoHomeScreen:
    
       setCursorPos(1);
       cout<< setw(55) <<" || ATTENDANCE MANAGEMENT SYSTEM ||"<<endl; //TITLE OF APP

       bool match = false;
       string operationChoice;
    
       setCursorPos(2,15);
    
       buildVerticalWall(43);
    
       line=0; //* re used variable
    
       while(line<11)
       {
           setCursorPos(1,15);
           if(line==1)
           buildHorizontalWall(43,"1) NEW SETUP FOR SEMESTER");
           else if(line==3)
           buildHorizontalWall(43,"2) TAKE ATTENDANCE ");
           else if(line==5)
           buildHorizontalWall(43,"3) CUSTOMIZED ATTENDANCE REPORT ");
           else if(line==7)
           buildHorizontalWall(43,"4) SEARCH & UPDATE DETAILS ");
           else if(line==9)
           buildHorizontalWall(43,"5) EXIT ");
           else 
           buildHorizontalWall(43," ");
           line++;
       }
    
       setCursorPos(1,15);
       buildVerticalWall(43);
    

      askChoice(2,30,operationChoice);
    
       if(!cin)
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
    
       ConvertChoiceToINT = validateString(operationChoice,5);
    
       if(!ConvertChoiceToINT)
       { 
           goto gotoHomeScreen;
       }
    
       return(ConvertChoiceToINT);
  }

 int GetDesktopResolution() //? for getting particular device size screen 
 { 
     int size=22; //specified intial size for small screen
     RECT desktop; // Get a handle to the desktop window
     const HWND hDesktop = GetDesktopWindow(); // Get the size of screen to the variable desktop
     GetWindowRect(hDesktop, &desktop); 
     // The top left corner will have coordinates (0,0) 
     // and the bottom right corner will have coordinates 
     // (horizontal, vertical) 
     
     int horizontal = desktop.right;  // horizontal
     int vertical = desktop.bottom;   // vertical
     
     //-RM(remove at last) printf("h : %d v : %d ",horizontal,vertical);
 
     if(horizontal<=600){size=30;} // ?setting up console inside size according to device size and resolution
     else if(horizontal<=800){size=33;}
     else if(horizontal<=1000){size=35;}
     else if(horizontal<=1400){size=38;}
     else if(horizontal <=1900){size=42;}
     else if(horizontal <=2500){size=45;}
     else if(horizontal <=3200){size=50;}
     else if(horizontal <=4000){size=55;}
     else if(horizontal <=4800){size=58;}
   
     return(size);
  } 

  void setConsoleSize() //? for setting console size
  { 
        CONSOLE_FONT_INFOEX cfi; //structure variable
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 0;                   // Width of each character in the font
        cfi.dwFontSize.Y = GetDesktopResolution();                  // Height getting
        cfi.FontFamily = FF_DONTCARE; // font family doesn't matter
        cfi.FontWeight = FW_NORMAL;   //font normally bold
        std::wcscpy(cfi.FaceName, L"JetBrains Mono Bold"); // Choose your font BY SETTING FONT FACE
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); //pass reference of that structure to OUTPUT HANDLE 
  }

  protected:

  virtual void SetNoObj()=0; //*for disable object creation of APP
  int ConvertChoiceToINT; //*variable for converting string input to integer
  void askChoice(int h,int v,string &input)
  {
    setCursorPos(h,v);
    ShowConsoleCursor(true);
    cout<<"CHOICE : ";
    fflush(stdin);
    getline(cin,input);
    ShowConsoleCursor(false);
  }
  void InvalidInputErr() //! heavy error
  {
    scrClr(0.5);
    ShowConsoleCursor(false);
    setCursorPos(8,26);
    SetColor(4);
    cout<<"INVALID CHOICE ENTERTED !"<<endl;
    setCursorPos(1,20);
    cout<<"PLEASE RE-ENTER YOUR CHOICE CORRECTLY !"<<endl;
    ShowConsoleCursor(false);
    scrClr(1);
    SetColor(0);
  }
  void InvalidInputErr(string err_msg,int color,int pos) //? overloaded version //?medium level error 
  {
    scrClr();
    setCursorPos(9,pos);
    SetColor(color);
    ShowConsoleCursor(false);
    cout<<err_msg<<endl; //error on sem semester creation
    scrClr(2);
    SetColor(0);
  }
  
  int validateString(string input,int Bnd) //* string input validate as integer
  {

      int flag=0,tem=1;
      string i;  //!viraj talaviya look at it can we save it ?? by direct calling like that ... if(to_string(tem) == input) please check that
      for(tem=1;tem<=Bnd;tem++)
      {
          i = to_string(tem);
          if(i == input)
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
  
  int validateString(string input) //?overloaded version of validating string input of yes/no
  {
    if(input == "YES" || input == "yes" || input == "Yes")
    {
      return 1; //yes
    }
    else if(input == "NO" || input == "no" || input == "No")
    {
      return 0; //no
    }
    else
    {
      return -1; // error
    }
  }

};

//---------STATIC DEFINATIONS  OF APP-----------//
 int APP::MODULE_CHOICE=0; //? MODULE CHOICE WILL BE ACT LIKE GLOBALLY
//---------------------------------------------//

/****************************APP-CLASS-END***************************/

/****************************MODULE-START*****************************************/
class MODULE_GENERAL : public APP  //TODO: ALL MD TEAM PLEASE CONTRIBUTE YOUR FUNCTIONS HERE AND INHERIT THIS CLASS TO YOURS
{

  // ? this are general function class which can be used by all 4 module developers
  // *email functionalities also be included here since all 2 modules are using it
  // ? you have to make functions very generalized so other MD developers can use it
  // ?use can you OOP concepts here function overloading and other...concepts like template

  private:

  public:

  MODULE_GENERAL()
  {

  }
  ~MODULE_GENERAL()
  {

  }
  
  protected:

  virtual void SetNoObj()=0; //*for disable object creation of APP
 
  //********** MAIN *************/ 

  string AMS_Path;
  string command;
  string SemPath;
  string tempStorage;
 
 /******************************/

//********** FACULTY *************/ 

  string FacultyName;
  string FacultyEmail;
  string course_name;
  string sem;
  string subject_name;
  string numberOfstudents;

/********************************/
  
//********** STUDENT *************/   

  string student_name;
  string student_email;
  string RoLLNo;
 
/*******************************/

  void AppPath(string &path) //?Getting Project path for each module Variable used Ams_Path for storing path
  {
    CHAR pathDocument[MAX_PATH]; //string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathDocument);  //getting documents path
   
    if (result == S_OK)  //check if  documents path is successfully stored in pathdocuments
    { 
    path = pathDocument; // take original documents path into string
    path =  path + "\\AMS"; //making AMS folder path
    }
    else
    {
        cout << "ERROR PATH NOT FOUND : " << result << "\n"; //*error
    }
  } 

  void getDataFromFile(string path,string &FcName,int lineNo) //?getData file given path form given line as string
  {
   ifstream read(path.c_str(),ios::in);

   if(!read.is_open())
   {
     cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<<endl; 
   }
   else
   {
     int FileLine=1;
     while(FileLine<=lineNo)
     {
       getline(read,FcName);
       FileLine++;
     }
   }
   read.close();
  }

  void writeDataToFile(string path,string &FcName) //?write string data to particular path file
  {
    ofstream write(path.c_str(),ios::app);

    if(!write.is_open())
    {
      cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<<endl;
    }
    else
    {
      write<<FcName<<endl;
    }
    write.close();
  }

  string convertIntToString(int &in) //?meaning itself defining
  {
  string str = to_string(in);
  return str;
  }

  string convertArrayTostring(char* arg) //?meaning itself defining
  {
  string re(arg);
  return re;
  }

  void replaceWithHyphen(string &str) //?file-folderName not allowed special symbols so hyphen conversion
  {   
      int i=0,j=0;
      string list = "#%&{}\\/*>< $!:\'\"@+`|="; //*need to be checked as thease are restricated symbols
      
      for(i=0;i<=list.length();i++)
      {
         for(j=0;j<=str.length();j++)
         {
             if(str[j]==list[i])
             {
                 str[j]='-';
             }
         }
      }
   
   transform(str.begin(), str.end(), str.begin(), ::toupper); //*convert to uppercase
  }

  bool EmptyInput(string &input)  //?checking if input is empty(hint : enter key)
  {
   if(input.empty())
   {
     return true; //if emty then returns  true
   }
   else
   {
     return false; // if not then returns false
   }
  }

  bool validateEmail(string email) //?checking for email validation (for space or any other special character which is not supported in email)
  {
       const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
       return regex_match(email,pattern);
  }

  int dirExists(const char *path) //?checking if directory exists or not 1=EXIST 0=NOT EXIST
  {
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
  }

};

class SET_WRITE_DB: public MODULE_GENERAL 
{
  
  //!=============================DATA-MEMBERS================================//

  /********************************* MODULE_1 *********************************/
  
  private:

  public:

  protected:
    void SetNoObj()
    {
      //? by empty defination of pure virtual function here we are restricating creation of parent class
      //?and grand parent object
    } 

  /*****************************************************************************/

  /********************************* MODULE_2 *********************************/
   private:
   public:
   protected:
  /*****************************************************************************/
  
  //!=============================DATA-MEMBERS-END================================// 
  

  //?=============================MEMBERS-FUNCTIONS===================================//
  
  public:
  SET_WRITE_DB() 
  {
    AppPath(AMS_Path); //* for each module you will get project folder (database)path like that
  }
  /********************************* MODULE_1 *********************************/

  private:
  
  int createSemester() //? return 1=semester created successfully & return 0=not created
  { 
    
    tempStorage=course_name;
    replaceWithHyphen(tempStorage); //hyphen convert
    
    SemPath = AMS_Path + "\\" + tempStorage + "-SEM-" + sem ; //making semesterpath with coursename
  
    tempStorage=subject_name;
    replaceWithHyphen(tempStorage); //hyphen convert

    SemPath = SemPath + "-" + tempStorage  ; //proper subject folder create

    if(!dirExists(SemPath.c_str())) //if directory not exists then create it
        {  
            command = "mkdir " +  SemPath;                //making commad which will pass in cmd
            
            system(command.c_str());      // creating  directory by CMD
             
            /*********************  FOLDERS *******************/
            
             command = "mkdir " + SemPath + "\\DAILY-RECORD" ; // making COMMAND FOR DAILY_RECORD folder
            
             system(command.c_str()); // creating DAILY_RECORD directory by CMD
             
             command = "mkdir " + SemPath + "\\FAC-STUD-DETAILS" ; // making COMMAND FOR FAC&STUD_DETAILS folder
            
             system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD
             
             command = "mkdir " + SemPath + "\\MONTHLY-REPORTS" ; // making COMMAND FOR MONTHLY_REPORTS folder
           
             system(command.c_str()); // creating MONTHLY_REPORTS directory by CMD

             /**************************************************/
             
             /*******************  FILES *********************/
             
              command = "cd. > " + SemPath + "\\DAILY-RECORD\\records.txt"; // RECORDS.TXT file
              system(command.c_str()); 
               
              command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\faculty"+"-sem-"+ sem +".txt"; // faculty_details.TXT file
              system(command.c_str());  
               
              command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\student"+"-sem-"+ sem +".txt"; // student_details.TXT file
              system(command.c_str()); 
              
              tempStorage=course_name; //re used tempStorage
              replaceWithHyphen(tempStorage);

              command = course_name +"|"+sem+"|"+ subject_name +"|"+ tempStorage +"-SEM-" + sem + "-";
             
              
              tempStorage=subject_name; //re used tempStorage
              replaceWithHyphen(tempStorage);
               
              command = command + tempStorage ; 
               
              tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt";   //* it will keep record of each semester that is created like all data of faculty | folderName
                                                                      //! module development 2 you will need that okay for listing out folders
              writeDataToFile(tempStorage,command); //*writting data to file
              return 1; //al above code works then returns 1 = successfully
              /***********************************************/
        }
        else  //if that semester already exist
        {
          InvalidInputErr("SEMSTER WITH THAT SUBJECT ALREADY EXIST !",2,19); //*overloadedversion called
          return 0;//returns 0=failed as we are trying to create that same folder again
        }

  }

  /************   FACULTY DETAILS CONFIRMATION AND MODIFICATION   ****************************/

  int confirmation() //basic confirmation message for user
  {
    int line; 
    
    reConfirm:
    scrClr(0.5);
    setCursorPos(4,15);
    cout<<"FACULTY NAME "<< right << setw(9) <<": "<<FacultyName;
    setCursorPos(1,15);
    cout<<"FACULTY E-MAIL "<< right << setw(7) <<": "<<FacultyEmail;
    setCursorPos(2,15);
    cout<<"COURSE NAME "<< right << setw(10) <<": "<<course_name;
    setCursorPos(1,15);
    cout<<"SEMESTER "<< right << setw(13) <<": "<<sem;
    setCursorPos(1,15);
    cout<<"SUBJECT "<< right << setw(14) <<": "<<subject_name;
    setCursorPos(1,15);
    cout<<"NUMBER OF STUDENTS "<< right << setw(3) <<": "<<numberOfstudents;
      
  
    setCursorPos(2,15);
  
    buildVerticalWall(43);
    line=0;
    while(line<3)
    {
      setCursorPos(1,15);
      if(line==1)
      {
        buildHorizontalWall(43,"Confirm these details (yes/no) ");     
    
      }
      else 
      {
        buildHorizontalWall(43," ");
    
      }
    
      line++;
    }
    setCursorPos(1,15);
    buildVerticalWall(43);
  
    setCursorPos(2,30);
  
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin,tempStorage); //*re-used tempStorage for storage
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage);
    
    if(ConvertChoiceToINT == -1) //validate input
    {
      InvalidInputErr(); //error message
      goto reConfirm;
    }

   return(ConvertChoiceToINT); //returns basic confirmation value yes=1 / no=0 
  }

  int InfoModification() //? MODIFICATIONS OF FACULTY DETAILS
  { 
       
       int line;
       reInputOfmodchoice:
        
       line=0;
       setCursorPos(1);
       cout<< setw(62) <<" => WHICH INFORMATION DO YOU WANT TO MODIFY ? "<<endl; 

       setCursorPos(1,25);
    
       buildVerticalWall(27);
    
       while(line<13)
        {
            setCursorPos(1,25);
            if(line==0)
            buildHorizontalWall(27,"1) FACULTY NAME ");
            else if(line==2)
            buildHorizontalWall(27,"2) FACULTY E-MAIL ");
            else if(line==4)
            buildHorizontalWall(27,"3) COURSE NAME ");
            else if(line==6)
            buildHorizontalWall(27,"4) SEMESTER ");
            else if(line==8)
            buildHorizontalWall(27,"5) SUBJECT ");
            else if(line==10)
            buildHorizontalWall(27,"6) NUMBER OF STUDENTS ");
            else if(line==12)
            buildHorizontalWall(27,"7) NO CHANGE ");
            else 
            buildHorizontalWall(27," ");
            line++;
        }
    
      setCursorPos(1,25);
      buildVerticalWall(27);
    
      askChoice(2,32,tempStorage);
    
       if(!cin)
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
       ConvertChoiceToINT = validateString(tempStorage,7); //validate input

       if(ConvertChoiceToINT==0) //if wrong input
       { 
           goto reInputOfmodchoice; //re take choice of modification
       }
       else 
       {
       return(ConvertChoiceToINT); //returns number option of modification
       }
  }

  //***************************************************************************/


  //********** STUDENT DETAILS CONFIRMATION AND MODIFICATION **********/

  int studConfirmation() //?basic confirmation message for user
  {
    int line; 

    reConfirm:

    setCursorPos(5,15);
    cout<<"STUDENT ROLL NO "<< right << setw(4) <<": " <<RoLLNo;
    setCursorPos(1,15);
    cout<<"STUDENT NAME "<< right << setw(7) <<": " <<student_name;
    setCursorPos(1,15);
    cout<<"STUDENT E-MAIL "<< right << setw(5) <<": " <<student_email;
    
    setCursorPos(2,15);
    buildVerticalWall(43);

    line=0;
    while(line<3)
    {
      setCursorPos(1,15);
      if(line==1)
      {
        buildHorizontalWall(43,"Confirm these details (yes/no) ");     
      }
      else 
      {
        buildHorizontalWall(43," ");
    
      }
    
      line++;
    }
    setCursorPos(1,15);
    buildVerticalWall(43);
  
    setCursorPos(2,30);
  
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin,tempStorage); //*re-used tempStorage for storage
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage);
    
    if(ConvertChoiceToINT == -1) //validate input
    {
      InvalidInputErr(); //error message
      goto reConfirm;
    }

   return(ConvertChoiceToINT); //returns basic confirmation value yes=1 / no=0 
  }

  int InfoStudModification() //? MODIFICATIONS OF STUDENTS DETAILS
  { 
       
       int line;
       reInputOfmod:
        
       line=0;
       setCursorPos(3);
       cout<< setw(62) <<" => WHICH INFORMATION DO YOU WANT TO MODIFY ? "<<endl; 

    
       setCursorPos(2,25);
    
       buildVerticalWall(23);
    
       while(line<7)
        {
            setCursorPos(1,25);
            if(line==1)
            buildHorizontalWall(23,"1) STUDENT NAME ");
            else if(line==3)
            buildHorizontalWall(23,"2) STUDENT E-MAIL ");
            else if(line==5)
            buildHorizontalWall(23,"3) NO CHANGE");
            else 
            buildHorizontalWall(23," ");
            line++;
        }
    
       setCursorPos(1,25);
       buildVerticalWall(23);

       askChoice(3,32,tempStorage); 
    
       if(!cin)
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
       ConvertChoiceToINT = validateString(tempStorage,3); //validate input

       if(ConvertChoiceToINT==0) //if wrong input
       { 
           goto reInputOfmod; //re take choice of modification
       }
       else 
       {
       return(ConvertChoiceToINT); //returns number option of modification
       }
  }

  //************************************************************************/

   void UpdateName(string &input) //?Faculty & student name update input
   { 
      reinput:
      scrClr(0.5);
      setCursorPos(9,20);
      cout<<"ENTER NAME : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,input);
      ShowConsoleCursor(false);
      if(EmptyInput(input))
      {
        InvalidInputErr(); // input error
        goto reinput;
      }
  }
  void UpdateEmail(string &input)  //?Faculty-student email address update & input
  {   reinputOfEmail:
      scrClr(0.5);
      setCursorPos(9,16);
      cout<<"ENTER E-MAIL : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,input);
      ShowConsoleCursor(false);
      if(EmptyInput(input))
      {
        InvalidInputErr(); // input error
        goto reinputOfEmail;
      }
      else if(!validateEmail(input))//email validation
      {
        InvalidInputErr("INVALID E-MAIL ADDRESS !",4,26);
        goto reinputOfEmail;
      }
      scrClr(0.5); //screen stops for reading
  
  }
  void EnterCourseName() //?course name input
  {   
      reinputOfcourseName:
      scrClr(0.5);
      setCursorPos(9,26); //set Cursor Position
      cout<<"ENTER COURSE NAME : ";
      fflush(stdin);
      ShowConsoleCursor(true); // show cursor for taking input
      getline(cin,course_name);   //input
      ShowConsoleCursor(false);   // hide cursor for flickring cursor
      if(EmptyInput(course_name))  // if empty input like enter key so we have set error for that
      {
        InvalidInputErr(); //error on wrong input
        goto reinputOfcourseName;
      }
      scrClr(0.5);
  }
  void EnterSem()  //?input of semester
  {   
      reinputOfsem:
      scrClr(0.5); //clear screen
      fflush(stdin);
      setCursorPos(9,26);
      cout<<"ENTER SEMESTER : ";
      fflush(stdin);
      ShowConsoleCursor(true);   // show cursor for taking input
      getline(cin,sem);       //input
      ShowConsoleCursor(false); // hide cursor for flickring cursor
      
      if(!validateString(sem,10)) //validate sem input
      {goto reinputOfsem;}

  }
  void EnterSubject() //?input subject 
  {
      reinput:
      scrClr(0.5);
      setCursorPos(9,26);
      cout<<"ENTER SUBJECT : ";
      ShowConsoleCursor(true);  // show cursor for taking input
      fflush(stdin);
      getline(cin,subject_name);    //input
      ShowConsoleCursor(false);    // hide cursor for flickring cursor
      if(EmptyInput(subject_name)) // if empty input like enter key so we have set error for that
      {
        InvalidInputErr();  //error on wrong input
        goto reinput;
      }

  }


  void rollNo(int RollNo)  //?show Roll Number
  {   
      scrClr(0.5); //clear screen
      ShowConsoleCursor(false); // hide cursor to stop flickring cursor
      setCursorPos(9,27);
      cout<<" ROLL NO. : "<<RollNo;
      scrClr(1); // user can read no.
  }

  void askNumberOfStudents() //?askig number of students in semeter
  { 
    reAskNumStud:
    scrClr(0.5);
    setCursorPos(7,23);
    cout << " HOW MANY STUDENTS DO YOU HAVE ? ";
    setCursorPos(4,27);
    cout<<"NUMBER OF STUDENT : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin,numberOfstudents);   
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(numberOfstudents,5000);
    if(ConvertChoiceToINT == 0)
    { 
        goto reAskNumStud;
      
    }

  }

  public:

  void askFacDetails() //?asking faculty details
  { 

    reAskFacDet: //re asking  details of faculty

    EnterCourseName(); //course name input 
    EnterSem(); //sem input 
    EnterSubject();  //subject input 
    askNumberOfStudents(); //number of students
    
    command = AMS_Path + "\\USER-INFO\\userdetails.txt"; // making path for getting data from file
   
    getDataFromFile(command,FacultyName,1); //taking data of from file
    getDataFromFile(command,FacultyEmail,2);//taking data of from file
    

    confirmAgain: //final confirmation 

    if(confirmation()) // basic confirmation dialog if yes then semester folder create
    {   
        
        if(createSemester()) //semester confirmation
        {
       
        command = SemPath + "\\FAC-STUD-DETAILS\\faculty"+"-sem-"+ sem +".txt"; //path making for writting into file
        
        writeDataToFile(command,FacultyName); //writting faculty data to files
        writeDataToFile(command,FacultyEmail);
        writeDataToFile(command,course_name);
        writeDataToFile(command,sem);
        writeDataToFile(command,subject_name);
        writeDataToFile(command,numberOfstudents);

        }
        else
        {
          goto reAskFacDet; //*reasking faculty details as semester already exists
        }
    }
    else
    { 
      scrClr(0.5); //clear screen so flickring won't happen 

      switch(InfoModification()) //which details do you want to update that function returns
      {
        case 1:{UpdateName(FacultyName);break;} // each function called according to requirement 
        case 2:{UpdateEmail(FacultyEmail);break;}     
        case 3:{EnterCourseName();break;}
        case 4:{EnterSem();break;}
        case 5:{EnterSubject();break;}
        case 6:{askNumberOfStudents();break;}
        case 7:{scrClr(0.5);break;}
      }
      goto confirmAgain; //ask user to final confirmation
    }
    
  }

  void askStudDetails() //? asking students details
  {
      int ROLLNO=0;
      while(ROLLNO<stoi(numberOfstudents))
      {
           ROLLNO++;

           rollNo(ROLLNO);  // for take input of roll no
           UpdateName(student_name); //for take input of student name
           UpdateEmail(student_email); //for taking input of email
     
           confirmAgain: //final confirmation 
           RoLLNo= convertIntToString(ROLLNO);
           if(studConfirmation()) // basic confirmation dialog if yes then semester folder create
           {  
               command = SemPath + "\\FAC-STUD-DETAILS\\student"+"-sem-"+ sem +".txt";  //path making for writting into file
               RoLLNo = convertIntToString(ROLLNO); //rollNo Int to string
               tempStorage = RoLLNo + "|" + student_name + "|" + student_email; // folder name
               writeDataToFile(command,tempStorage); //writting data to files
           }
           else
           { 
                scrClr(0.5); //clear screen so flickring won't happen 

                switch(InfoStudModification()) //which details do you want to update that function returns
                {
                  case 1:{UpdateName(student_name);break;}     
                  case 2:{UpdateEmail(student_email);break;}
                  case 3:{scrClr(0.5);break;}
                }
                goto confirmAgain; //ask user to final confirmation
           }

      }
   
  }
  

   protected:

  /****************************************************************************/

  /********************************* MODULE_2 *********************************/
   private:
   public:
   protected:
  /****************************************************************************/
   public:

  ~SET_WRITE_DB() //TODO:DESTRUCTOR
  {

  }
  //?=============================MEMBERS-FUNCTIONS===================================//
};


/****************************MODULE-END************************************/

int main()
{
    //*jay swaminrayan
    //*jay ganeshay namh
    //*jay kashtbhanjan dev
    bool loop=true;
    
    SET_WRITE_DB SW;

 
    while(loop)
    {
          SW.startApp(); // the App
          SW.scrClr();  //clear screen
          SW.setCursorPos(2,10); //set cursor position
      
            switch(APP::MODULE_CHOICE)
            {
              case 1:{
                         SW.askFacDetails();
                         SW.askStudDetails();
                         break;
                     }
              case 2:{
                       break;
                     }
              case 3:{
                       break;
                     }
              case 4:{
                       break;
                     }
              case 5:{
                       loop=false; // exit Application
                       break;
                     }
              default:{cout<<endl<<"ERROR: APPLICATION CRASHED!!!"<<endl;exit(1);break;}
            }
    
        SW.scrClr();       //clear screen
    }

    return 0;
}

