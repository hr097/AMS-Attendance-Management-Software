#include<iostream>     // * c++ code style use
#include<stdio.h>     //* for c style code use 
#include<stdlib.h>   // * standard library like dynamic memory allocation and exit macros and other.. 
#include<conio.h>   // *  console input output
#include<windows.h> // * windows console related functions handle
#include<unistd.h> // * for sleep function
#include<iomanip> // * for manipulator
#include<cwchar>  //*for console font purpose 
#include<string.h> //* C style string related functions access
#include<stdbool.h> // * boolean operation
#include<math.h> //* math operations
#include<fstream> //* file handling functions access
#include<string> //* C++ STL( string library) function access
#include<regex>  //* for email validation
#include<algorithm> //* for transform function access
#include<ctime> //* for getting current date and time 
#include<sstream> //* for conversion to string
#include<vector> //*STL DYNAMIC ARRAY used
#include<tuple>    //* for using tuples (group of element key->value type)

//--------FOR-DOCUMENT PATH GETTING------/

#include <shlobj.h> 
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

#pragma comment(lib, "shell32.lib")  //* for document path finding 

//--------FOR-DOCUMENT PATH GETTING-------------/

#ifndef _WIN32_WINNT  //*if that macro not exist then condtional compila6ion would be done and those files will be included
  #define _WIN32_WINNT 0x0601
  #include<wincon.h>
  #include<string>

  //#endif  // user 1  DRASHTI

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

#endif // user 2 HARSHIL


using namespace std; //* standard namespace for  resolving naming coflicts

/*******************APP-MAIN-CLASS********************************/



class APP //*GRAND PARENT CLASS
{

  public:

  static int MODULE_CHOICE; //*module selector 
  
  APP()
  { 
     //*******************GET-CURRENT-DATE**************************//

     string temp; //temp variable for storage
     time_t tmNow; // structure variable
     tmNow = time(NULL); //set to initial zero=NULL
     struct tm t = *localtime(&tmNow);   //pre defined function
        
     stringstream ss; //string stream class object
     ss<<t.tm_mday;   // pass day
     temp = ss.str(); // it returns as string
     CUR_DATE = temp;  // save to input parameter

     ss.str(""); //flush string stream class so new input can be taken

     ss<<(t.tm_mon+1); //pass months
     temp = ss.str();  //returns month
     CUR_DATE = CUR_DATE + "/";    //add slash  for formet dd/mm/yy
     CUR_DATE = CUR_DATE + temp;   //concate to input para
        
     ss.str(""); 
     ss<<(t.tm_year+1900); //pass year
     temp = ss.str();  //returns year
     CUR_DATE = CUR_DATE + "/";    //add slash
     CUR_DATE = CUR_DATE + temp;  //concate to input para
        
     ss.str("");   //flush string stream class so new input can be taken

    //*******************CURRENT-DATE**********************************//

    //*******************GET-CURRENT-TIME******************************//
            
            int meridiem_Flag=0; //0=AM 1=PM
            if(t.tm_hour>12) // if hours is greter than 12 then convert into 12 hour formet
            {
                t.tm_hour=(t.tm_hour-12);
                meridiem_Flag=1;    //Flag set to show AM-PM
            } 

            ss<<t.tm_hour; // pass Hours
            temp = ss.str(); // it returns as string
            CUR_TIME = temp; 

            if(stoi(CUR_TIME)<10) // if hours is between 1 to 9 the like 09 ,01 ...put zero before digit
            {
                CUR_TIME = "0" + CUR_TIME;
            }
            ss.str("");
            ss<<(t.tm_min);
            temp = ss.str();
            if(stoi(temp)<10) //convert to int for cheking condition
            {
                temp = "0" + temp;
            }
            CUR_TIME = CUR_TIME + ":";
            CUR_TIME = CUR_TIME + temp;

            ss.str("");

            CUR_TIME+=(meridiem_Flag==0)?" AM":" PM"; //AM and PM
    //*******************CURRENT-TIME*********************************//
  }

  void SetColor(int ForgC) //?for setting individual text color
  {
    WORD wColor; //color specifier
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // create windows handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;//We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor); // set console text color
    }
  }
  
  void setCursorPos(int x, int y=0) //* cursor position set up IMPORTANT: relative postion is set
  {
    
    //vertical lines space 
  
    while(x>0)
    {
      cout<<endl;  
      x--;
    }

    //horizontal cursor space by 1 charecter
    while(y!=0) 
    {
      printf(" ");
      y--;
    }
    
  }
  
  void ShowConsoleCursor(bool showFlag) //? hidinf or showing cursor
  {
      HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // set handle
  
      CONSOLE_CURSOR_INFO     cursorInfo; 
  
      GetConsoleCursorInfo(out, &cursorInfo);
      cursorInfo.bVisible = showFlag; // set the cursor visibility
      SetConsoleCursorInfo(out, &cursorInfo);
  }

  void scrClr(float i=0.0) //?for clearing screen afer some time
  {
    //by default set to zero with default arguements
    sleep(i); //  going in sleep mode for particular time
    system("cls"); //  clear  the screen
  }

  void buildVerticalWall(int briks) //? for making vertical side
  { cout<<"*";
    while(briks>0){cout<<"-";briks--;} 
    cout<<"*";
  }
  
  void buildHorizontalWall(int endBrick,string tempStorage) //? for making horizontal side
  { 
    cout<<"|";
    int run=1;
    while(run<endBrick)
    {
      
      if(run == (endBrick / 6)) 
      {
        cout<<tempStorage;
        run+=(tempStorage.length()-1);
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

  // void debug(int do_what=0) //?for debugging purposes at last we will delete it 0=pause 1=pause & print
  // { //!will remove this at last @viraj note down
  //   #include<conio.h> // * console input output library
  //   if(!do_what)
  //   getch();
  //   else
  //   cout<<endl<<"DEBUGING"<<endl;
  // } 

  void startApp() //? start Application
  {
    if(MODULE_CHOICE==0) //* only 1 time initiaization function need to be called after 1 time just we need ro refresh home screen so is/else here
    {
      initApp(); // init screen first time by opening console in full screen
      MODULE_CHOICE = HomeScreen(); // home screen will tell which module is selected
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

  int HomeScreen() //*ask Module choice at Home screen of APP
  { 
       int line;

       gotoHomeScreen:
      
       Date(1,15); //current date print
       Time(0,16); //current time print

       setCursorPos(2);
       cout<< setw(55) <<" || ATTENDANCE MANAGEMENT SYSTEM ||"<<endl; //TITLE OF APP

       string operationChoice; 
    
       setCursorPos(1,15);
    
       buildVerticalWall(43);
    
       line=0; 
    
       while(line<11) // build UI-Box screen
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
    
       if(!cin) //new line(enter key input ignoring) // not necessary bcz we have set it invalid input error
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
    
       ConvertChoiceToINT = validateString(operationChoice,5,1); // validate and convert choice into integer
    
       if(!ConvertChoiceToINT) // if wrong input then repeat process untill correct input
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
     
    
     //*setting up console inside size according to device size and resolution
     if(horizontal<=600){size=30;} 
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

  void setConsoleSize() //? for setting up console size
  { 
        CONSOLE_FONT_INFOEX cfi; //structure variable
        cfi.cbSize = sizeof(cfi); //total bytes of cfi
        cfi.nFont = 0;
        cfi.dwFontSize.X = 0;                   // Width of each character in the font
        cfi.dwFontSize.Y = GetDesktopResolution();                  // Height getting
        cfi.FontFamily = FF_DONTCARE; // font family doesn't matter
        cfi.FontWeight = FW_NORMAL;   //font normally bold
        std::wcscpy(cfi.FaceName, L"JetBrains Mono Bold"); // Choose your font BY SETTING FONT FACE
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); //pass reference of that structure to OUTPUT HANDLE 
  }


  protected:

  string CUR_DATE,CUR_TIME;//*CURRENT DATE TIME FOR APPLICATION
  int ConvertChoiceToINT; 

  void askChoice(int h,int v,string &input) //?general choice taking function
  {
    setCursorPos(h,v); // set cursor position
    ShowConsoleCursor(true); // show the cursor
    cout<<"CHOICE : ";
    fflush(stdin); //flushing standard input buffer
    getline(cin,input); //taking white space string input
    ShowConsoleCursor(false); // hide the cursor
  }

  int YesNoInput(string inputAsk,string &in)
  {
     int line;
     setCursorPos(2,17);
     buildVerticalWall(43);
     line=0;
     while(line<3)
     {
       setCursorPos(1,17);
       if(line==1)
       {
         buildHorizontalWall(43,inputAsk);     //message BOX-UI
         
       }
       else 
       {
         buildHorizontalWall(43," ");
         
       }
         
       line++;
     }
     setCursorPos(1,17);
     buildVerticalWall(43);
     setCursorPos(2,30);
     fflush(stdin);
     ShowConsoleCursor(true);
     cout << "Type : ";
     getline(cin,in);
     ShowConsoleCursor(false);
     line = validateString(in); //validate input // line re used as return value storage
    
     return (line);
    
  }

  void InvalidInputErr() //? invalid input error function
  {
    scrClr(0.5);
    ShowConsoleCursor(false);
    setCursorPos(8,26);
    SetColor(4); //set color for text individual
    cout<<"INVALID CHOICE ENTERTED !"<<endl;
    setCursorPos(1,20);
    cout<<"PLEASE RE-ENTER YOUR CHOICE CORRECTLY !"<<endl;
    ShowConsoleCursor(false);
    scrClr(1);
    SetColor(0); // back to normal color
  }
  void InvalidInputErr(string err_msg,int color,int pos) //? overloaded version //?medium level error 
  {
    scrClr();
    setCursorPos(9,pos);//set cursor position
    SetColor(color);//setting text color
    ShowConsoleCursor(false); 
    cout<<err_msg<<endl; //error msg
    scrClr(2); // screen stops so user can read message 
    SetColor(0);
  }

  void MSG(string msg,string msg2,int color,int color2,int pos) // work succed message print
  {
    scrClr();
    setCursorPos(9,pos);
    SetColor(color);
    ShowConsoleCursor(false);
    cout<<msg; //mess 1 st 
    SetColor(color2);
    cout<<msg2; //mess 2  nd
    scrClr(2); 
    SetColor(0);
  }

  int validateString(string input,int Bnd,int start) //? string input validate as integer
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
        return tem; //*returns converted string.to_int(INT)
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

  void Date(int v,int h) //? current Date print function
  {
    setCursorPos(v,h);
    cout<<"DATE : ";
    SetColor(2);
    cout<<CUR_DATE;
    SetColor(0);
  }

  void Time(int v,int h) //? current Time print function
  {
    setCursorPos(v,h);
    cout<<"TIME : ";
    SetColor(2);
    cout<<CUR_TIME;
    SetColor(0);
  }

};

//---------STATIC DEFINATIONS-OF-APP---------------//

 int APP::MODULE_CHOICE=0; //? MODULE CHOICE WILL BE ACT LIKE GLOBALLY

//-------------------------------------------------//

/****************************APP-CLASS-END****************************************/

/****************************MODULE-START*****************************************/
class MODULE_GENERAL : public APP  
{
  //TODO: ALL Module development TEAM PLEASE CONTRIBUTE YOUR FUNCTIONS HERE AND INHERIT THIS CLASS TO YOURS
  // ? this are general function class which can be used by all 4 module developers
  // *email functionalities also be included here since all 2 modules are using it
  // ? you have to make functions very generalized so other MD developers can use it
  // ?use can you OOP concepts here function overloading and other...concepts like template

  private:

  public:

  MODULE_GENERAL()
  {
      AppPath(); // //* AMS DATABASE PATH WILL BE FIND OUT HERE IN ANY SYSTEM
  }

  ~MODULE_GENERAL()
  {

  }
  
  protected:

  virtual void SetNoObj()=0; //*WE MAKE THIS CLASS AS PURE VIRTUAL SO NO OBJECT OF THIS CLASS WILL BE CREATED IN MAIN()
 
  //********** MAIN MODULE_GENERAL *************/ 

  string AMS_Path;
  string command;
  string SemPath;
  string tempStorage;
 
 /********************************************/

//********** FACULTY *************/ 

  string FacultyName;
  string FacultyEmail;
  string course_name;
  string sem;
  string subject_name;

/********************************/
  
//********** STUDENT *************/   

  string student_name;
  string student_email;
  string RoLLNo;
  string numberOfstudents; 
 
/*******************************/
 
  void AppPath() //?Getting Project path for each module Variable used AMS_Path for storing path
  {
    CHAR pathDocument[MAX_PATH]; //string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathDocument);  //getting documents path
   
    if (result == S_OK)  //check if  documents path is successfully stored in pathdocuments
    { 
    AMS_Path= pathDocument; // take original documents path into string
    AMS_Path =  AMS_Path + "\\AMS"; //making AMS folder path
    }
    else
    {
        cout << "ERROR PATH NOT FOUND : " << result << "\n"; //*error
    }
  } 

  void getDataFromFile(string path,string &FcName,int lineNo) //?get Data of given path file line by line in string
  {
   ifstream read(path.c_str(),ios::in);

   if(!read.is_open())
   {
     cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<<endl; 
   }
   else
   {
     int FileLine=1; // start from first line
     while(FileLine<=lineNo)
     {
       getline(read,FcName); // read and get data
       FileLine++;
     }
   }
   read.close();
  }

  void writeDataToFile(string path,string &FcName) //?write string data to given path file
  {
    ofstream write(path.c_str(),ios::app);

    if(!write.is_open())
    {
      cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<<endl;
    }
    else
    {
      write<<FcName<<endl; //write data
    }
    write.close();
  }

  string convertIntToString(int &in) //?meaning itself defining
  {
    string str = to_string(in); 
    return str;
  }
   

  // string convertArrayTostring(char* arg) //?meaning itself defining
  // {
    // string re(arg);
    // return re;
  // }

  void replaceWithHyphen(string &str) //? in given string special symbols should be replaced by hyphen and string will be convert into UPPERCASE
  {   
      int i=0,j=0;
      string list = "#%&{}\\/*>< $!:\'\"@+`|="; //need to be checked as thease are restricated symbols
      
      for(i=0;i<=list.length();i++)
      {
         for(j=0;j<=str.length();j++)
         {
             if(str[j]==list[i])
             {
                 str[j]='-'; //replace with hyphen symbol
             }
         }
      }
   
   transform(str.begin(), str.end(), str.begin(), ::toupper); //convert to uppercase
  }

  bool EmptyInput(string &input)  //?checking if input is empty (e.g. : enter key)
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

  bool validateEmail(string email) //?checking for email validation 
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

class MODULE_1: public MODULE_GENERAL //?module 1 class
{
  
  //*=============================DATA-MEMBERS================================//

  
  private:


  public:


  protected:
  
  //*=============================DATA-MEMBERS-END================================// 
  

  //*=============================MEMBERS-FUNCTIONS===================================//
  

  private:
  
  int createSemester() //? return 1=semester created successfully & return 0=not created
  { 
    
    tempStorage=course_name;
    replaceWithHyphen(tempStorage); 
    
    SemPath = AMS_Path + "\\" + tempStorage + "-SEM-" + sem ; //making semesterpath with coursename
  
    tempStorage=subject_name;
    replaceWithHyphen(tempStorage); 

    SemPath = SemPath + "-" + tempStorage  ; //proper subject folder create

    if(!dirExists(SemPath.c_str())) //if directory not exists then create it
        {  
            command = "mkdir " +  SemPath;                //making commad which will pass in cmd
            
            system(command.c_str());      // creating  directory by CMD
             
            //*********************  FOLDERS ***********************************************/
            
             command = "mkdir " + SemPath + "\\DAILY-RECORD" ; // making COMMAND FOR DAILY_RECORD folder
            
             system(command.c_str()); // creating DAILY_RECORD directory by CMD
             
             command = "mkdir " + SemPath + "\\FAC-STUD-DETAILS" ; // making COMMAND FOR FAC&STUD_DETAILS folder
            
             system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD
             
             command = "mkdir " + SemPath + "\\MONTHLY-REPORTS" ; // making COMMAND FOR MONTHLY_REPORTS folder
           
             system(command.c_str()); // creating MONTHLY_REPORTS directory by CMD

             /**********************************************************************************/
             
             //*******************  FILES ******************************************************/
             
              command = "cd. > " + SemPath + "\\DAILY-RECORD\\records.txt"; // RECORDS.TXT file
              system(command.c_str()); 
               
              command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\faculty"+"-sem-"+ sem +".txt"; // faculty_details.TXT file
              system(command.c_str());  
               
              command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\student"+"-sem-"+ sem +".txt"; // student_details.TXT file
              system(command.c_str()); 
              
              tempStorage=course_name; //re used tempStorage
              replaceWithHyphen(tempStorage);

              command = course_name +"|"+sem+"|"+ subject_name +"|"+ tempStorage +"-SEM-" + sem + "-";
              
              transform(command.begin(), command.end(), command.begin(), ::toupper); //convert to uppercase

              tempStorage=subject_name; //re used tempStorage
              replaceWithHyphen(tempStorage);
               
              command = command + tempStorage ; //command for making path for writting data to file 
               
              tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt";   //* it will keep record of each semester that is created like all data of faculty | folderName
                                                                      
              writeDataToFile(tempStorage,command); //*writting data to file
              return 1; //all above code works then returns 1 = successfully
              /***********************************************/
        }
        else  //if that semester already exist
        {
          InvalidInputErr("SEMSTER WITH THAT SUBJECT ALREADY EXIST !",2,19); //overloadedversion called
          return 0;//returns 0=failed as we are trying to create that same folder again
        }

  }

  //----------------FACULTY DETAILS CONFIRMATION AND MODIFICATION---------------------/

  int confirmation() //?basic confirmation message for user
  {
    int line; 
    
    reConfirm:

    //cofirmation BOX-UI
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
      
  
    //message BOX-UI

    ConvertChoiceToINT = YesNoInput("Confirm these details (yes/no) ",tempStorage);  //taking input yes/no

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
    
       while(line<13) // BOX-UI OF modification information
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
    
      askChoice(2,32,tempStorage); //ask choice
    
       if(!cin)
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
       ConvertChoiceToINT = validateString(tempStorage,7,1); //validate input

       if(ConvertChoiceToINT==0) //if wrong input
       { 
           goto reInputOfmodchoice; //repear the process until correct input
       }
       else 
       {
       return(ConvertChoiceToINT); //return the number option of modification
       }
  }

  /***************************************************************************/


  //********** STUDENT DETAILS CONFIRMATION AND MODIFICATION **********/

  int studConfirmation() //?basic confirmation message for user
  {
    int line; 
 
    reConfirm:
    scrClr(0.5);
    //BOX-UI FOR STUDENT INFO CONFIRM
    setCursorPos(5,15);
    cout<<"STUDENT ROLL NO "<< right << setw(4) <<": " <<RoLLNo;
    setCursorPos(1,15);
    cout<<"STUDENT NAME "<< right << setw(7) <<": " <<student_name;
    setCursorPos(1,15);
    cout<<"STUDENT E-MAIL "<< right << setw(5) <<": " <<student_email;
    
    ConvertChoiceToINT = YesNoInput("Confirm these details (yes/no) ",tempStorage);  //taking input yes/no
    
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
      
      //BOX-UI FOR MODIFICATION INFORMATION OF STUDENTS
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
       ConvertChoiceToINT = validateString(tempStorage,3,1); //validate input

       if(ConvertChoiceToINT==0) //if wrong input
       { 
           goto reInputOfmod; //re take choice of modification
       }
       else 
       {
       return(ConvertChoiceToINT); //returns number option of modification
       }
  }

  /************************************************************************/

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

  void UpdateEmail(string &input)  //?Faculty & student email address update & input
  {   reinputOfEmail:
      scrClr(0.5);
      setCursorPos(9,16);
      cout<<"ENTER E-MAIL : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,input);
      ShowConsoleCursor(false);
      if(EmptyInput(input)) //EmptyInput VALIDATION
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
      setCursorPos(9,26); 
      cout<<"ENTER COURSE NAME : ";
      fflush(stdin);
      ShowConsoleCursor(true); 
      getline(cin,course_name);   
      ShowConsoleCursor(false);  
      if(EmptyInput(course_name))  
      {
        InvalidInputErr(); 
        goto reinputOfcourseName;
      }
      scrClr(0.5);
  }

  void EnterSem()  //?input of semester
  {   
      reinputOfsem:
      scrClr(0.5); 
      fflush(stdin);
      setCursorPos(9,26);
      cout<<"ENTER SEMESTER : ";
      fflush(stdin);
      ShowConsoleCursor(true);  
      getline(cin,sem);       
      ShowConsoleCursor(false); 
      
      if(!validateString(sem,10,1)) //validate sem input
      {goto reinputOfsem;}

  }
  void EnterSubject() //?input subject 
  {
      reinput:
      scrClr(0.5);
      setCursorPos(9,26);
      cout<<"ENTER SUBJECT : ";
      ShowConsoleCursor(true);  
      fflush(stdin);
      getline(cin,subject_name);    
      ShowConsoleCursor(false);   
      if(EmptyInput(subject_name)) 
      {
        InvalidInputErr();  
        goto reinput;
      }

  }


  void rollNo(int RollNo)  //?show Roll Number
  {   
      scrClr(0.5); //clear screen
      ShowConsoleCursor(false); // hide cursor to stop flickring cursor
      setCursorPos(9,27);
      cout<<" ROLL NO. : "<<RollNo;
      scrClr(1); // user can read no. FOR 1 SECOND
  }

  void askNumberOfStudents() //?asking number of students 
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
    ConvertChoiceToINT = validateString(numberOfstudents,5000,1);
    if(ConvertChoiceToINT == 0)
    { 
        goto reAskNumStud;
    }

  }

  public:

  MODULE_1() 
  {
    
  }
  ~MODULE_1() 
  {
    
  }

  void askFacDetails() //?asking faculty details
  { 
   
    reAskFacDet: //re asking  details of faculty

    EnterCourseName(); //course name input 
    EnterSem(); //sem input 
    EnterSubject();  //subject input 

    if(!createSemester()) //semester confirmation
    {
     goto reAskFacDet; //reasking faculty details as semester already exists
    }

    askNumberOfStudents(); //number of students INPUT
    
    command = AMS_Path + "\\USER-INFO\\userdetails.txt"; // making path for getting data from file
   
    getDataFromFile(command,FacultyName,1); //taking faculty name of from file
    getDataFromFile(command,FacultyEmail,2);//taking  faculty email  of from file
    

    confirmAgain: //final confirmation 

    if(confirmation()) // basic confirmation dialog if yes then semester folder create
    {   
        command = SemPath + "\\FAC-STUD-DETAILS\\faculty"+"-sem-"+ sem +".txt"; //path making for writting into file
        
        //writting faculty data to files

        writeDataToFile(command,FacultyName); 
        writeDataToFile(command,FacultyEmail);
        writeDataToFile(command,course_name);
        writeDataToFile(command,sem);
        writeDataToFile(command,subject_name);
        writeDataToFile(command,numberOfstudents);

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
      while(ROLLNO<stoi(numberOfstudents)) // functions for taking student data input roll no wise
      {
           ROLLNO++;

           rollNo(ROLLNO);  // for take input of roll no
           UpdateName(student_name); //for take input of student name
           UpdateEmail(student_email); //for taking input of email
     
           confirmAgain: //final confirmation 
           RoLLNo= convertIntToString(ROLLNO);
           if(studConfirmation()) // basic confirmation dialog if yes then semester folder create
           {  
               command = SemPath + "\\FAC-STUD-DETAILS\\student"+"-sem-"+ sem +".txt";  //path making for writing into file
               RoLLNo = convertIntToString(ROLLNO); //rollNo Int to string
               tempStorage = RoLLNo + "|" + student_name + "|" + student_email; // folder name
               writeDataToFile(command,tempStorage); //writing data to files
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
  
  void SetUpSucceed() //module 1 successfully worked
  {
    tempStorage = course_name + " SEM " + sem + " " +subject_name;
    MSG("SET UP SUCCESSFUL OF ",tempStorage,2,0,20);
  }
  
  protected:

  void SetNoObj()
  {
    //* by empty defination of pure virtual function here we are restricating creation of parent class
  } 
  //*==============================MEMBERS-FUNCTIONS===================================//
};

class MODULE_2:public MODULE_GENERAL //?module 2 class
{

//******************************** DATA-MEMBERS **********************************/
 private:

 vector<string> buffer,LIST; //vector buffer for file handling data receiver
 vector<tuple<string,string,string,string>> DATA; // search-access vector-tuple
 
 public:
 
 protected:

//*********************************************************************************/

//******************************** MEMBER-FUNCTIONS *********************************/
 private:
 
 int checkDuplicateRecord(vector<string> vec,string search) //?for cheking if duplicate records found in vector_storage
 {
     vector<string>::iterator it; //iterator
 
     it = find(vec.begin(), vec.end(),search); // finding elemnt in vector
 
  if (it != vec.end())
 	{
       return 0; // if found then return 0
 	}
 	else
     {
       return 1; // if not found then return 1
     }
 }

 void DisplayList_Input(string &put,int select=0) //? display the list and take appropriate input of corse/sem/subject
 { 
   int listFlag = 1,chFlag=0,countFlag=0,temp_flag=1;
   auto i = LIST.begin(); 
   
    (LIST.size()>6)?setCursorPos(0,10):setCursorPos(1,20); // set box-view for list >5 and less than 5
    buildVerticalWall(35);
    setCursorPos(1,20);
    buildHorizontalWall(35," ");
        
    while(i != LIST.end())  // dynamic list loop for sem course subject input choice
    {
        
		    displayAgain:
        chFlag=0;
        setCursorPos(1,20);
        if(select==0)
        buildHorizontalWall(35,to_string(5*countFlag+listFlag) + ") " + (*i)); 
        else
        buildHorizontalWall(35,to_string(5*countFlag+listFlag) + ") " + "Sem-" + (*i)); 
        setCursorPos(1,20);
        buildHorizontalWall(35," "); 
        listFlag++;
        i++;
        
        if(listFlag > 5 && i !=LIST.end())
        {
         
            chFlag=1;
            countFlag++;
            setCursorPos(1,20);
            buildHorizontalWall(35,"TYPE '+' FOR EXTENDED LIST");
            setCursorPos(1,20);
            buildHorizontalWall(35," "); 
            setCursorPos(1,20);
            buildVerticalWall(35);
            askChoice(2,34,tempStorage);
            scrClr(0.5);
            if(tempStorage=="+")
            {
                setCursorPos(2,20);
                buildVerticalWall(35);
                listFlag = 1;
                chFlag=0;
                setCursorPos(1,20);
                buildHorizontalWall(35," "); 
                goto displayAgain;
            }
			      else
			      {    
                ConvertChoiceToINT = validateString(tempStorage,countFlag*5,(countFlag-1)*5); 
                if(ConvertChoiceToINT == 0)
                { 
                    while(temp_flag != (listFlag))
                    {
                      i--;
                      temp_flag++;
                    }
                    temp_flag = 1;
                    countFlag--;
                    listFlag = 1;
                    setCursorPos(2,20);
                    buildVerticalWall(35);
                    chFlag=0;
                    setCursorPos(1,20);
                    buildHorizontalWall(35," "); 
                    goto displayAgain;
                }
                else
                {
                  break;
                }
			      }
        }
    }
    if(chFlag==0)
    {
        setCursorPos(1,20);
        buildVerticalWall(35);
        askChoice(2,30,tempStorage);

        if(tempStorage == "+")
        {
          InvalidInputErr();
          while(temp_flag != (listFlag))
          {
            i--;
            temp_flag++;
          }
          temp_flag = 1;
          listFlag = 1;
          setCursorPos(2,20);
          buildVerticalWall(35);
          setCursorPos(1,20);
          buildHorizontalWall(35," "); 
          goto displayAgain;
        }
		    ConvertChoiceToINT = validateString(tempStorage,(((countFlag)*5+listFlag-1)),((countFlag)*5));
        if(ConvertChoiceToINT == 0)
        { 
            while(temp_flag != (listFlag))
            {
              i--;
              temp_flag++;
            }
            temp_flag=1;
            listFlag = 1;
            setCursorPos(2,20);
            buildVerticalWall(35);
            setCursorPos(1,20);
            buildHorizontalWall(35," "); 
            goto displayAgain;
        }
        scrClr(0.5);

    } 
    for(i =LIST.begin(),countFlag=1; i != LIST.end();++i,countFlag++)   // set data to string for searching
    {
         if(countFlag==ConvertChoiceToINT)
         {
           put=(*i);
         }
    }                   

   LIST.clear();//flush vector data for re-using
   tempStorage.clear();//flush string for re-using
 }

 void getFolderPath() //? based on input choice of course->sem-subject we find correct folder and save path  to Sem_path
 {
    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find folder path using vector tuple we have 3 input parameter coursename , sem , subject name
    {   
      
        if(course_name==get<0>((*i)))
            if(sem==get<1>((*i)))
                if(subject_name==get<2>((*i)))
                      SemPath=get<3>((*i)); 
      
    }
    SemPath = AMS_Path + "\\" + SemPath; //assigning searched path to SemPath
 }

 void getSemesterRecordFile() //? get data of course-semester-sub-path records
 {
    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt";//making path to AMS->OTHER->semsterRecord.txt
    fstream fin(tempStorage.c_str(),ios::in); // file opened in reading mode
    
    if(!fin.is_open()) // if not opened
    {
        cout<<" DATABASE ERROR 404 : FILE NOT OPENED !";
    }
    else // if opened
    {   
        tempStorage.clear(); // clear for re-using
        getline(fin,tempStorage); // tempStorage used as temporary storage
        
        while(!fin.eof()) // data receive until file ends
        {    
            buffer.push_back(tempStorage); // save that string(data) in vector
            getline(fin,tempStorage); // fetch again from file
        } 
        fin.close();//file close 
    }
    
    sort(buffer.begin(), buffer.end()); //sort file data in vector in Dictionary order
    tempStorage.clear(); 
 }

 void ExtractStringFromBuffer() //? extracting main string into substring like course - sem - sub - path
 {
    for (auto i = buffer.begin(); i != buffer.end(); ++i) //insert in to vector-tuple from vector buffer with extracting string
    {
        tempStorage = (*i); // temp variable for moving vector tempStorage to string
        int found_pos,temp_pos; // temp variable for position storing

        found_pos = tempStorage.find("|"); // find the first occurance of '|'
        course_name = tempStorage.substr(0,(found_pos)); // get proper course name from string and save it to course_name
        temp_pos = (found_pos+1); // making next finding position

        if(checkDuplicateRecord(LIST,course_name)) // cheking if duplicate course
        {
            LIST.push_back(course_name); //making list for input of UI screen of course select
        }
        
        found_pos = tempStorage.find("|",temp_pos);     //finds string till 1st pipe i.e coursename
        sem = tempStorage.substr(temp_pos,(found_pos-temp_pos));//stores the string in TEMP_STR
        temp_pos = (found_pos+1);  //searching next position

        found_pos = tempStorage.find("|", temp_pos);   //finds string till 2nd pipe i.e. semester
        subject_name = tempStorage.substr(temp_pos,(found_pos-temp_pos)); //stores the string in TEMP_STR
        temp_pos = (found_pos+1);  //searching next position
         
        found_pos = tempStorage.find("|", temp_pos); //finds string till 3rd pipe i.e. subjectname
        SemPath = tempStorage.substr(temp_pos); //stores the string in TEMP_STR

        DATA.push_back(make_tuple(course_name,sem,subject_name,SemPath)); //makes a final string to display
    }
    //*clearing for reusing
    tempStorage.clear();      
    course_name.clear();      
    sem.clear();              
    subject_name.clear();     
    SemPath.clear();          
  }
  void lastlineDlt()
  {
      string line; 
      vector<string> lines;
      command.clear();
      command = SemPath + "\\DAILY-RECORD\\records.txt";
      std::ifstream inputStream(command.c_str());
      
      while (getline(inputStream,line)) {
          lines.push_back(line);
      }
      inputStream.close();
      command.clear();
      command = SemPath + "\\DAILY-RECORD\\records.txt";
      std::fstream outputStream(command.c_str(),ios::out | ios::trunc);
      if (outputStream.is_open())
      {
          for (int i=0; i < lines.size()-1; i++)
          {
              outputStream << lines[i] << "\n";
          }
          outputStream.close();
      }
  }

int ValidateAttendance(string &input)
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

void MAP()
{

}

void MAA()
{

}

void EPR()
{

}

void EAR()
{
  
}

string lastline()
{
    ifstream fin;
    string lastLine;  

    command.clear();
    command =  SemPath + "\\DAILY-RECORD\\records.txt";

    fin.open(command.c_str());
    if(fin.is_open()) {
        fin.seekg(-1,ios_base::end);                // go to one position before the EOF

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
        fin.close();

    }
 return lastLine;
}

void AttendanceTakenSuccessfully() //module 1 successfully worked
{
  tempStorage.clear();
  tempStorage = course_name + " SEM " + sem + " " +subject_name;
  MSG("ATTENDANCE TAKEN OF ",tempStorage,2,0,20);
}


 public:

  MODULE_2()
  {
    
  }

  ~MODULE_2()
  {
    buffer.clear(); //clearing buffer
    LIST.clear();   //clearing List
  }

  bool checkDB() //? functions for checking least(1) database semster Records exists or not
  {  
    
    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt";//making path to AMS->OTHER->semsterRecord.txt
    fstream read(tempStorage.c_str(),ios::in); // file opened

       bool isEmpty;

       isEmpty = read.peek() == EOF; // check if file is empty or not 
       if(isEmpty)
       {
          InvalidInputErr("NO SETUP EXIST ! PLEASE ADD ATLEST 1 SETUP",4,19); // error mess
          read.close();
          isEmpty = false;
       }
       else
       { 
          read.close();
          getSemesterRecordFile();
          ExtractStringFromBuffer();
          isEmpty = true;
       }
      
      tempStorage.clear(); 
      return(isEmpty);

  }

  void askCourseChoice() //? take input choice of course for attendance
  {
     DisplayList_Input(course_name);  // display list for taking input

     for (auto i =DATA.begin(); i != DATA.end();++i)  //process to make list of semester in particular course 
      {   
        
          if(course_name==get<0>((*i))) 
          {   
             if(checkDuplicateRecord(LIST,get<1>((*i)))) // cheking if duplicate 
             {
                 LIST.push_back(get<1>((*i))); //making distinguish list
             }
          }
                 
      }


  }
  void askSemsterChoice() //? take input choice of semester for attendance
  {   
      DisplayList_Input(sem,1);

      for (auto i =DATA.begin(); i != DATA.end();++i)  //process to make list of subject in particular course & semester
      {   
          if(course_name==get<0>((*i))&&sem==get<1>((*i))) 
          {   
             if(checkDuplicateRecord(LIST,get<2>((*i)))) 
             {  
                 LIST.push_back(get<2>((*i))); 
             }
          }
                 
      }
  }

  int proceedForAttendance() //* functions for reconfirming to proceed to attendance
  {     
        int line=0;
        reinputforattedance:

        scrClr(0.5); // clear screen

      
        line = 0;
        command.clear();                                                              
        command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // making path to access faculty-sem-?-.tx       

            setCursorPos(1,7);
            buildVerticalWall(65);
        
            while(line < 15)
            {
                setCursorPos(1,7);
                if (line == 1)
                {
                   
                    getDataFromFile(command, FacultyName, 1);
                    buildHorizontalWall(65,"FACULTY NAME         :  "+FacultyName);
                }  
                else if (line == 3)
                {
                  buildHorizontalWall(65,"COURSE               :  " + course_name );
                  
                }
                else if (line == 5)
                {
                  buildHorizontalWall(65,"SEM                  :  " + sem );
                  
                }
                else if (line == 7)
                {
                  buildHorizontalWall(65,"SUBJECT              :  " + subject_name);
                  
                }
                else if (line == 9)
                {
                    getDataFromFile(command,numberOfstudents,6);
                    buildHorizontalWall(65,"NUMBER OF STUDENTS   :  "+numberOfstudents);
                    
                }
                else if(line == 11)
                {   
                   cout<<"|";
                   Date(0,9);
                   Time(0,7);
                   cout<<setw(18)<<"|";
                }
                else if(line == 13)
                { 
                  cout<<"|";
                  SetColor(1);
                  setCursorPos(0,16);
                  cout<<"DO YOU WANT TO PROCEED FURTHER ?";
                  SetColor(0);
                  cout<<setw(18)<<"|";
                }

                else
                    buildHorizontalWall(65, " ");
                line++;
            }

            setCursorPos(1, 7);
            buildVerticalWall(65);
            
            tempStorage.clear();
            command.clear();

            setCursorPos(2,32);
            fflush(stdin);
            ShowConsoleCursor(true);
            cout << "Type : ";
            getline(cin,tempStorage);
            ShowConsoleCursor(false);
            ConvertChoiceToINT = validateString(tempStorage); //validate input // line re used as return value storage
            
            if(ConvertChoiceToINT == -1) //validate input
            {
              InvalidInputErr(); //error message
              goto reinputforattedance;
            }

        return (ConvertChoiceToINT);
  }

  void askSubjectChoice() //? take input choice of subject for attendance
  {
    DisplayList_Input(subject_name);
    getFolderPath(); 
  }

  int AttendanceWindow()
  {
    int i;
    command.clear();
    tempStorage.clear();

    command =  SemPath + "\\DAILY-RECORD\\records.txt";
    fstream finout(command.c_str(), ios::in);
    if(!finout.is_open())
    {
      cout << "FILE NOT NOT OPENED  ! ";
    }
    else
    {
      i = lastline().find("|");
      tempStorage = lastline().substr(0,i-1);
      if(tempStorage == CUR_DATE)
      {   
          command.clear();
          command = course_name + " SEM " + sem + " " +subject_name;
          MSG(command," ATTENDANCE FOR TODAY IS ALREADY TAKEN !",2,0,14);
          command.clear();
          return 0;
      }
    }
    int line=0;

    reAskAtdM:
    scrClr(0.5);
    setCursorPos(4,18);
    buildVerticalWall(43);
    line=0; 
    while(line<9) // build UI-Box screen
    {
        setCursorPos(1,18);
        if(line==1)
        buildHorizontalWall(43,"1) MARK ALL PRESENT ");
        else if(line==3)
        buildHorizontalWall(43,"2) MARK ALL ABSENT ");
        else if(line==5)
        buildHorizontalWall(43,"3) ENTER PRESENT ROLL NO. ");
        else if(line==7)
        buildHorizontalWall(43,"4) ENTER ABSENT ROLL NO. ");
        else 
        buildHorizontalWall(43," ");
        line++;
    }
    setCursorPos(1,18);
    buildVerticalWall(43);

    askChoice(2,30,tempStorage);

    ConvertChoiceToINT = validateString(tempStorage,4,1); 
    if(!ConvertChoiceToINT) 
    { 
        goto reAskAtdM; 
    }

    return (ConvertChoiceToINT);

  }

  void takeAttendance(int choice)
  {
    (choice==1)?MAP():(choice==2)?MAA():(choice==3)?EPR():EAR();
    AttendanceTakenSuccessfully();
  } 


  void takeAttendance()
  {
    //AttendanceWindow();
    command.clear();
    tempStorage.clear();

    int i,tem;
    string MCH,ACH,choice;
    // string ABSENT_ARR[numberOfstudents];

    command =  SemPath + "\\DAILY-RECORD\\records.txt";
  
    fstream finout(command.c_str(), ios::app | ios::in); // opened in append and reading mode
    if (!finout.is_open())
    {
        cout << "FILE NOT NOT OPENED  ! ";
    }
    else
    {
        i = lastline().find("|");
        tempStorage = lastline().substr(0,i-1);

        if(tempStorage == CUR_DATE)
        {   
            command.clear();
            command = course_name + " SEM " + sem + " " +subject_name;
            MSG(command," ATTENDANCE FOR TODAY IS ALREADY TAKEN !",2,0,14);
            command.clear();
        }
        else
        { 
            
            // finout<<"\n"+CUR_DATE +" | ";

            // for(i = 1;i<= stoi(numberOfstudents);i++)
            // {    
                // finout<<"P";
            // }
            // finout.close();

            command.clear();
            command = SemPath + "\\DAILY-RECORD\\records.txt";
            //finout.open(command.c_str(),ios::app);
            i = lastline().find("|");

            
            tempStorage = lastline();

            while(true)
            {   
                   rollNoReask:

                   scrClr(0.5);
                   setCursorPos(5,16);
                   cout << "ENTER ABSENT ROLL NO. : ";
                   getline(cin,MCH);
                   ConvertChoiceToINT = validateString(MCH,stoi(numberOfstudents),1);
                   if(ConvertChoiceToINT)
                   {   
                       tempStorage.replace((i+1+ConvertChoiceToINT),1,"A");
                       
                       lastlineDlt();
                       reConfirmAB:
                       
                       ConvertChoiceToINT = YesNoInput(" ADD MORE ABSENT ROLL NO. ? ",choice);

                       if(ConvertChoiceToINT == -1) //validate input
                       {
                         InvalidInputErr(); //error message
                         goto reConfirmAB;
                       }
                       else if(ConvertChoiceToINT == 0) // no means goto file handling part
                       {
                         break;
                       }
       
                   }
                   else
                   {
                     goto rollNoReask;
                   }
               }

               finout<<tempStorage;
               finout.close();
        
               tempStorage = lastline();
               i = tempStorage.find("|");
               tempStorage = lastline().substr(i+2,tempStorage.length());
               cout << "LIST OF PRESENT ROLL NO. :"<<endl;
               for(i=0;i<tempStorage.length();i++)
               {
                  if(tempStorage[i] == 'P')
                  {
                      cout << i+1 << " ";
                  }
               }

               cout<<endl<<"LIST OF ABSENT ROLL NO. :"<<endl;
               for(i=0;i<tempStorage.length();i++)
               {
                  if(tempStorage[i] == 'A')
                  {
                      cout << i+1 << " ";
                  }
               }

              while(true)
              {
                     cout<<"\n\n1)SUBMIT\n";
                     cout<<"\n2)MODIFICATION\n\n";
                     // cout<<"CHOICE ";
                     // getline(cin,choice);
                     askChoice(5,24,choice);
                     
                     switch(validateString(choice,2,1))
                     {
                             case 1:
                             {       finout<<"\n"+CUR_DATE +" | ";
                                     for(i = 1;i<= stoi(numberOfstudents);i++)
                                     {    
                                          finout<<"P";
                                     }
                                     finout.close();
                                     command.clear();
                                     command = course_name + " SEM " + sem + " " +subject_name;
                                     MSG(" ATTENDANCE FOR " + CUR_DATE +" FOR ",command + " IS TAKEN SUCCESSFULLY ",0,2,14);
                                     break;
                             }
                             case 2:
                             {
                                     finout.close();
                                     reAskRollNo:
                                     cout<<"\n\nENTER ROLL NO. FOR WHICH DO YOU WANT TO MODIFY : ";
                                     getline(cin,MCH);
                                     ConvertChoiceToINT = validateString(MCH,stoi(numberOfstudents),1);
                                     if(ConvertChoiceToINT)
                                     {
                                         reAskAtd:
                                         cout<<"\n\nEnter Attendance For roll no "<<MCH << " :";
                                         getline(cin,ACH);
                                         if(ValidateAttendance(ACH))
                                         {   
                                             command.clear();
                                             command = SemPath + "\\DAILY-RECORD\\records.txt";
                                             finout.open(command.c_str(),ios::app);
                                             tempStorage = lastline().find("|");
                                             tempStorage = lastline();
                                             tempStorage.replace((i+2+ConvertChoiceToINT),1,ACH);
                                             lastlineDlt();
                                             finout<<tempStorage;
                                             finout.close();
                                         }  
                                         else
                                         { 
                                           goto reAskAtd;
                                         }
                                        
                                      }
                                      else
                                      {
                                        goto reAskRollNo;
                                      }
                                         
                              }

                        }

                }

        }

    }
    
   }

 
 protected:

 void SetNoObj()
 {
   //? by empty defination of pure virtual function here we are restricating creation of parent(GENERAL MODULE) class
 } 

//************************************************************************************/

};



//---------------------------STATIC DEFINATIONS-MODULE-2------------------------------/

//-----------------------------------------------------------------------------------/

/****************************MODULE-END**********************************************/

int main()
{
    //* jay swaminrayan *//
    //* jay ganeshay namh *//
    //* jay kashtbhanjan dev *//

    bool loop=true; //set true to run app by 1 time
    
    APP A;
    

    while(loop)
    {
          A.startApp(); 
          A.scrClr();  
          A.setCursorPos(2,10); 
      
            switch(APP::MODULE_CHOICE)// module choice asking
            {
              case 1:{   
                         MODULE_1 MD1;
                         MD1.askFacDetails();
                         MD1.askStudDetails();
                         MD1.SetUpSucceed();
                         break;
                     }
              case 2:{ 
                         MODULE_2 MD2;
                         if(MD2.checkDB())
                         {
                          MD2.askCourseChoice();
                          MD2.askSemsterChoice();
                          MD2.askSubjectChoice();

                          if(MD2.proceedForAttendance())
                          {
                            MD2.takeAttendance(MD2.AttendanceWindow());  
                          }

                        }
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
              default:{cout<<endl<<"ERROR: APPLICATION CRASHED!!!"<<endl;exit(1);break;} //* exception case
            }
    
        A.scrClr();    // screen clear
    }

    return 0;
}
