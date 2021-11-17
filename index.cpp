#include <iostream>  // * c++ code style use
#include <stdio.h>   //* for c style code use
#include <stdlib.h>  // * standard library like dynamic memory allocation and exit macros and other..
#include <conio.h>   // *  console input output
#include <windows.h> // * windows console related functions handle
#include <unistd.h>  // * for sleep function
#include <iomanip>   // * for manipulator
#include <cwchar>    //* for console font purpose
#include <string.h>  //* C style string related functions access
#include <stdbool.h> // * boolean operation
#include <math.h>    //* math operations
#include <fstream>   //* file handling functions access
#include <string>    //* C++ STL( string library) function access
#include <regex>     //* for email validation
#include <algorithm> //* for transform function access
#include <ctime>     //* for getting current date and time
#include <sstream>   //* for conversion to string
#include <vector>    //*STL DYNAMIC ARRAY used
#include <tuple>     //* for using tuples (group of element key->value type)

//--------FOR-DOCUMENT PATH GETTING------/

#include <shlobj.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

#pragma comment(lib, "shell32.lib") //* for document path finding

//--------FOR-DOCUMENT PATH GETTING-------------/

#ifndef _WIN32_WINNT //*if that macro not exist then condtional compila6ion would be done and those files will be included
  #define _WIN32_WINNT 0x0601
  #include <wincon.h>
  #include <string>

#endif  // user 1  DRASHTI

typedef struct _CONSOLE_FONT_INFOEX
{
  ULONG cbSize;
  DWORD nFont;
  COORD dwFontSize;
  UINT FontFamily;
  UINT FontWeight;
  WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

#ifdef __cplusplus
extern "C"
{
#endif
  BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

//#endif // user 2 HARSHIL

using namespace std; // standard namespace for  resolving naming coflicts

/*******************APP-MAIN-CLASS********************************/
void Debug(string t)
{
  cout<<endl<<t<<getch();
}

class APP //*GRAND PARENT CLASS
{

public:

static int MODULE_CHOICE; //*module selector

public:

  APP()
  {
    //*******************GET-CURRENT-DATE**************************//

    string temp;                      // temp variable for storage
    time_t tmNow;                     // structure variable
    tmNow = time(NULL);               // set to initial zero=NULL
    struct tm t = *localtime(&tmNow); // pre defined function

    stringstream ss; // string stream class object
    ss<<t.tm_mday; // pass day
    temp = ss.str(); // it returns as string
    CUR_DATE = temp; // save to input parameter

    ss.str(""); // flush string stream class so new input can be taken

    ss<<(t.tm_mon + 1);       // pass months
    temp = ss.str();            // returns month
    CUR_DATE = CUR_DATE + "/";  // add slash  for formet dd/mm/yy
    CUR_DATE = CUR_DATE + temp; // concate to input para

    ss.str("");
    ss<<(t.tm_year + 1900);   // pass year
    temp = ss.str();            // returns year
    CUR_DATE = CUR_DATE + "/";  // add slash
    CUR_DATE = CUR_DATE + temp; // concate to input para

    ss.str(""); // flush string stream class so new input can be taken

    //*******************CURRENT-DATE**********************************//

    //*******************GET-CURRENT-TIME******************************//

    int meridiem_Flag = 0; // 0=AM 1=PM
    if(t.tm_hour > 12)    // if hours is greter than 12 then convert into 12 hour formet
    {
      t.tm_hour = (t.tm_hour - 12);
      meridiem_Flag = 1; // Flag set to show AM-PM
    }

    ss<<t.tm_hour; // pass Hours
    temp = ss.str(); // it returns as string
    CUR_TIME = temp;

    if(stoi(CUR_TIME) < 10) // if hours is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      CUR_TIME = "0" + CUR_TIME;
    }

    ss.str("");
    ss<<(t.tm_min);
    temp = ss.str();
    if(stoi(temp) < 10) // convert to int for cheking condition
    {
      temp = "0" + temp;
    }
    CUR_TIME = CUR_TIME + ":";
    CUR_TIME = CUR_TIME + temp;

    ss.str("");

    CUR_TIME += (meridiem_Flag == 0) ? " AM" : " PM"; // AM and PM
    //*******************CURRENT-TIME*********************************//
  }

  void SetColor(int ForgC) //?for setting individual text color
  {
    WORD wColor;                                      // color specifier
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // create windows handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;                  // We use csbi for the wAttributes word.
    
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      // Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut,wColor); // set console text color
    }
    
  }

  void setCursorPos(int x, int y = 0) //* cursor position set up IMPORTANT: relative postion is set
  {

    // vertical lines space
    while(x > 0)
    {
      cout << endl;
      x--;
    }

    // horizontal cursor space by 1 charecter
    while(y != 0)
    {
      printf(" ");
      y--;
    }
  }

  void ShowConsoleCursor(bool showFlag)//? hiding or showing cursor
  {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // set handle

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
  }

  void scrClr(float i = 0.0) //?for clearing screen afer some time
  {
    // by default set to zero with default arguements
    sleep(i);      //  going in sleep mode for particular time
    system("cls"); //  clear  the screen
  }

  void buildVerticalWall(int briks) //? for making vertical side
  {
    cout<<"*";
    while(briks > 0)
    {
      cout<< "-";
      briks--;
    }
    cout<<"*";
  }

  void buildHorizontalWall(int endBrick, string tempStorage) //? for making horizontal side
  {
    cout<<"|";
    int run = 1;
    while(run < endBrick)
    {

      if (run == (endBrick / 6))
      {
        cout<<tempStorage;
        run += (tempStorage.length() - 1);
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

  void startApp() //? start Application
  {
    if(MODULE_CHOICE == 0) //* only 1 time initiaization function need to be called after 1 time just we need ro refresh home screen so is/else here
    {
      initApp();                    // init screen first time by opening console in full screen
      MODULE_CHOICE = HomeScreen(); // home screen will tell which module is selected
    }
    else
    {
      MODULE_CHOICE = HomeScreen();// home screen will tell which module is selected
    }
  }

  ~APP()
  {

  }

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

    system("color F0"); // set white background and text black
  }

  int HomeScreen() //*ask Module choice at Home screen of APP
  {
    int line;

  gotoHomeScreen:

    Date(1, 15); // current date print
    Time(0, 16); // current time print

    setCursorPos(2);
    cout << setw(55) << " || ATTENDANCE MANAGEMENT SYSTEM ||" << endl; // TITLE OF APP

    string operationChoice;

    setCursorPos(1, 15);//set cursor position

    buildVerticalWall(43);//build UI-Box screen

    line = 0;

    while (line < 11) // build UI-Box screen
    {
      setCursorPos(1, 15);
      if (line == 1)
        buildHorizontalWall(43, "1) NEW SETUP FOR SEMESTER");
      else if (line == 3)
        buildHorizontalWall(43, "2) TAKE ATTENDANCE ");
      else if (line == 5)
        buildHorizontalWall(43, "3) CUSTOMIZED ATTENDANCE REPORT ");
      else if (line == 7)
        buildHorizontalWall(43, "4) SEARCH & UPDATE DETAILS ");
      else if (line == 9)
        buildHorizontalWall(43, "5) EXIT ");
      else
        buildHorizontalWall(43, " ");
      line++;
    }

    setCursorPos(1, 15);//set cursor position
    buildVerticalWall(43);

    askChoice(2, 30, operationChoice);//choice inut

    if (!cin) // new line(enter key input ignoring) // not necessary bcz it is set as invalid input error
    {
      cin.clear();
      cin.ignore(80, '\n');
    }

    ConvertChoiceToINT = validateString(operationChoice, 5, 1); // validate and convert choice into integer

    if (!ConvertChoiceToINT) // if wrong input then repeat process until correct input
    {
      goto gotoHomeScreen;//re-ask choice
    }

    return (ConvertChoiceToINT);//return choice
  }

  int GetDesktopResolution() //? for getting particular device size screen
  {
    int size = 22;                            // specified intial size for small screen
    RECT desktop;                             // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow(); // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)

    int horizontal = desktop.right; // horizontal
    int vertical = desktop.bottom;  // vertical

    //*setting up console inside size according to device size and resolution
    if (horizontal <= 600)
    {
      size = 30;
    }
    else if (horizontal <= 800)
    {
      size = 33;
    }
    else if (horizontal <= 1000)
    {
      size = 35;
    }
    else if (horizontal <= 1400)
    {
      size = 38;
    }
    else if (horizontal <= 1900)
    {
      size = 42;
    }
    else if (horizontal <= 2500)
    {
      size = 45;
    }
    else if (horizontal <= 3200)
    {
      size = 50;
    }
    else if (horizontal <= 4000)
    {
      size = 55;
    }
    else if (horizontal <= 4800)
    {
      size = 58;
    }

    return (size);//return size
  }

  void setConsoleSize() //? for setting up console size
  {
    CONSOLE_FONT_INFOEX cfi;  // structure variable
    cfi.cbSize = sizeof(cfi); // total bytes of cfi
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                                                  // Width of each character in the font
    cfi.dwFontSize.Y = GetDesktopResolution();                             // Height getting
    cfi.FontFamily = FF_DONTCARE;                                          // font family doesn't matter
    cfi.FontWeight = FW_NORMAL;                                            // font normally bold
    std::wcscpy(cfi.FaceName, L"JetBrains Mono Bold");                     // Choose your font BY SETTING FONT FACE
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); // pass reference of that structure to OUTPUT HANDLE
  }

protected:
  string CUR_DATE, CUR_TIME; //*CURRENT DATE TIME FOR APPLICATION
  int ConvertChoiceToINT;

  void askChoice(int h, int v, string &input) //?general choice taking function
  {
    setCursorPos(h, v);      // set cursor position
    ShowConsoleCursor(true); // show the cursor
    cout << "CHOICE : ";
    fflush(stdin);            // flushing standard input buffer
    getline(cin, input);      // taking white space string input
    ShowConsoleCursor(false); // hide the cursor
  }

  int YesNoInput(string inputAsk, string &in,string t="",int color=0,int color2=0)//?take input in yes or no 
  {
    int line;
    setCursorPos(2, 17);//set cursor position
    buildVerticalWall(43);//set vertical line on console
    line = 0;
    //build UI-Box screen
    while (line < 3)
    {
      setCursorPos(1,17);

      if (line == 1)
      {
       if(color==0&&color2==0&&t.empty())
       {
         buildHorizontalWall(43, inputAsk); // message BOX-UI
       }
       else
       {
       cout<<"|";
       setCursorPos(0,7);
       SetColor(color);//set color
       cout<<inputAsk;
       SetColor(color2);
       setCursorPos(0,1);
       cout<<t;
       setCursorPos(0,8);
       cout<<"|";
       }

      }
      else
      {
        buildHorizontalWall(43, " ");
      }

      line++;
    }
    setCursorPos(1, 17);
    buildVerticalWall(43);
    setCursorPos(2,31);//set cursor position
    fflush(stdin);//for buffer
    ShowConsoleCursor(true);//cursor show on console
    cout << "Type : ";
    getline(cin, in);//take input
    ShowConsoleCursor(false);//cursor hide on console
    line = validateString(in); // validate input // line re used as return value storage

    return (line);//return line
  }

  void InvalidInputErr() //? invalid input error function
  {
    scrClr(0.5);//clear screen
    ShowConsoleCursor(false);//cursor hide on  console
    setCursorPos(8, 26);//set cursor position
    SetColor(4); // set color for text individual
    cout << "INVALID CHOICE ENTERTED !" << endl;
    setCursorPos(1, 20);
    cout << "PLEASE RE-ENTER YOUR CHOICE CORRECTLY !" << endl;
    ShowConsoleCursor(false);//cursor hide on  console
    scrClr(1);//clear screen
    SetColor(0); // back to normal color
  }
  void warnMsg(string err_msg, int color, int pos,string err_msg2=" ",int color2=0,int pos2=0) //? overloaded version //?medium level error
  {
    scrClr();

    if(err_msg2.length() >= 20)
    {
      setCursorPos(8,pos); // set cursor position
      SetColor(color);      // setting text color
      ShowConsoleCursor(false);
      cout << err_msg << endl; // error msg
      setCursorPos(1,pos2); // set cursor position
      SetColor(color2);      // setting text color
      cout << err_msg2 << endl; // error msg      
      scrClr(1);               // screen stops so user can read message
      SetColor(0);
    }
    else
    {
      setCursorPos(9, pos); // set cursor position
      SetColor(color);      // setting text color
      ShowConsoleCursor(false);
      cout << err_msg << endl; // error msg
      scrClr(2);               // screen stops so user can read message
      SetColor(0);
    }
  }

  void MSG(string msg, string msg2, int color, int color2, int pos) // work succed message print
  {
    
    scrClr();

    if(msg.length()<=30)//msg length is less than and equal to 30 print this msg
    {
        setCursorPos(9, pos);
        SetColor(color);
        ShowConsoleCursor(false);
        cout << msg; // mess 1 st
        SetColor(color2);
        cout << msg2; // mess 2  nd
        scrClr(2);
        SetColor(0);
    }
    else//if length is greater than 30 than print this msg
    {
        setCursorPos(8,pos);
        SetColor(color);
        ShowConsoleCursor(false);
        cout << msg; // mess 1 st
        setCursorPos(2,pos+7);
        SetColor(color2);
        cout << msg2; // mess 2  nd
        scrClr(2);
        SetColor(0);

    }
  }

  int validateString(string input, int Bnd, int start) //? string input validate as integer
  {
    int flag = 0, tem = 1;
    
    if (start == 0)
        start++;

    for(tem = start; tem <= Bnd; tem++)
    {
      if(to_string(tem) == input) // convert tem int to string to check input valid condition
      {
        flag = 1;
        break;
      }
    }

    if(flag == 0) //*IF flag=0 means input is invalid
    {
      InvalidInputErr(); //error msg
      return 0;
    }
    else
    {
      return tem; //*returns converted string.to_int(INT)
    }
    
  }

  int validateString(string input) //?overloaded version of validating string input of yes/no
  {
    if(input == "YES" || input == "yes" || input == "Yes")//check yes input
    {
      return 1; // yes
    }
    else if (input == "NO" || input == "no" || input == "No")//check no input
    {
      return 0; // no
    }
    else// if yes or no anyone not than print error
    {
      return -1; // error
    }
  }

  void Date(int v, int h) //? current Date print function
  {
    setCursorPos(v, h);//set cursor position as vertical and horizontal
    cout << "DATE : ";
    SetColor(2);//set color as green
    cout << CUR_DATE;
    SetColor(0);//set color black
  }

  void Time(int v, int h) //? current Time print function
  {
    setCursorPos(v, h);//set cursor position as vertical and horizontal
    cout << "TIME : ";
    SetColor(2);//set color as green
    cout << CUR_TIME;
    SetColor(0);//set color black
  }
};

//---------STATIC DEFINATIONS-OF-APP---------------//

int APP::MODULE_CHOICE = 0; //? MODULE CHOICE WILL BE ACT LIKE GLOBALLY

//-------------------------------------------------//

/****************************APP-CLASS-END****************************************/

/*****************************************  MODULE-START  ************************************************/
class MODULE_GENERAL : public APP
{
  // TODO: ALL Module development TEAM PLEASE CONTRIBUTE YOUR FUNCTIONS HERE AND INHERIT THIS CLASS TO YOURS
  //  ? this are general function class which can be used by all 4 module developers
  //  *email functionalities also be included here since all 2 modules are using it
  //  ? you have to make functions very generalized so other MD developers can use it
  //  ?use can you OOP concepts here function overloading and other...concepts like template

private:

public:
  MODULE_GENERAL() //?Getting Project path for each module Variable used AMS_Path for storing path
  {
    //* AMS DATABASE PATH WILL BE ACCESSED IN ANY SYSTEM via this function
   
    CHAR pathDocument[MAX_PATH];   // string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL,SHGFP_TYPE_CURRENT,pathDocument); // getting documents path

    if (result == S_OK) // check if  documents path is successfully stored in pathdocuments
    {

      AMS_Path = pathDocument;       // take original documents path into string
      AMS_Path = AMS_Path + "\\AMS"; // making AMS folder path
    }
    else
    {
      cout << "ERROR PATH NOT FOUND : " << result << "\n"; //*error
    }
  }
  ~MODULE_GENERAL()
  {

  }

protected:

  virtual void SetNoObj() = 0; //*WE MAKE THIS CLASS AS PURE VIRTUAL SO NO OBJECT OF THIS CLASS WILL BE CREATED IN MAIN()

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

  void getDataFromFile(string path, string &input, int lineNo) //?get Data of given path file line by line in string
  {
    ifstream get(path.c_str(),ios::in); //file opend in reading mode for getting data

    if(!get.is_open())//if file is not open than print error
    {
       cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<<endl;
    }
    else//if file is open
    {
      int FileLine = 1; // start from first line
      while(FileLine<= lineNo)//whille fileline is <= lineno than
      {
        getline(get,input); // read and get data
        FileLine++;
      }
    }
   get.close(); //file closed
  }

  void writeDataToFile(string path, string &FcName) //?write string data to given path file
  {
    ofstream write(path.c_str(), ios::app); //file opend in reading mode for getting data

    if (!write.is_open())//if file is not open than print path error
    {
      cout<<endl<<"UNABLE TO OPEN THE FILE AT GIVEN PATH : "<<path<< endl;
    }
    else//if file is open than write data in file
    {
      write << FcName << endl; // write data
    }
    write.close();//file close
  }

  string convertIntToString(int &in) //?meaning itself defining
  {
    string str = to_string(in);//convert interger variable to string using string function
    return str;//return string
  }
  
  void replaceWithHyphen(string &str) //? in given string special symbols should be replaced by hyphen and string will be convert into UPPERCASE
  {
    int i = 0, j = 0;
    string list = "#%&{}\\/*>< $!:\'\"@+`|="; // need to be checked as thease are restricated symbols

    for (i = 0; i <= list.length(); i++)//check list condition
    {
      for (j = 0; j <= str.length(); j++)//check str condition
      {
        if (str[j] == list[i])//if string and list are same
        {
          str[j] = '-'; // replace with hyphen symbol
        }
      }
    }
    /* 
        */

    transform(str.begin(), str.end(), str.begin(), ::toupper); // convert to uppercase
  }

  bool EmptyInput(string &input) //?checking if input is empty (e.g. : enter key)
  {
    if (input.empty())//check empty condition
    {
      return true; // if emty then returns  true
    }
    else
    {
      return false; // if not then returns false
    }
  }

  bool validateEmail(string email) //?checking for email validation
  {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); //email pattern
    return regex_match(email, pattern);
  }

  int dirExists(const char *path) //?checking if directory exists or not 1=EXIST 0=NOT EXIST
  {
    struct stat info;

    if (stat(path, &info) != 0)
      return 0;
    else if (info.st_mode & S_IFDIR)
      return 1;
    else
      return 0;
  }
  int checkEmptyFile(string path)//?check empty file
  {
    ifstream read(path.c_str(),ios::binary);             // file opened
    read.seekg(0,ios::end);
    int sz = read.tellg();
    read.close();
    return sz;//return size
  }
};

class MODULE_1 : public MODULE_GENERAL //?module 1 class
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

    tempStorage = course_name;
    replaceWithHyphen(tempStorage);

    SemPath = AMS_Path + "\\" + tempStorage + "-SEM-" + sem; // making semesterpath with coursename

    tempStorage = subject_name;
    replaceWithHyphen(tempStorage);  // make subject hyphen and uppercase
  
    SemPath = SemPath + "-" + tempStorage; // proper subject folder create

    if (!dirExists(SemPath.c_str())) // if directory not exists then create it
    {
      command = "mkdir " + SemPath; // making commad which will pass in cmd

      system(command.c_str()); // creating  directory by CMD

      //*********************  FOLDERS ***********************************************/

      command = "mkdir " + SemPath + "\\DAILY-RECORD"; // making COMMAND FOR DAILY_RECORD folder

      system(command.c_str()); // creating DAILY_RECORD directory by CMD

      command = "mkdir " + SemPath + "\\FAC-STUD-DETAILS"; // making COMMAND FOR FAC&STUD_DETAILS folder

      system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD

      command = "mkdir " + SemPath + "\\MONTHLY-REPORTS"; // making COMMAND FOR MONTHLY_REPORTS folder

      system(command.c_str()); // creating MONTHLY_REPORTS directory by CMD

      /**********************************************************************************/

      //*******************  FILES ******************************************************/

      command = "cd. > " + SemPath + "\\DAILY-RECORD\\records.txt"; // RECORDS.TXT file
      system(command.c_str());

      command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; // faculty_details.TXT file
      system(command.c_str());

      command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; // student_details.TXT file
      system(command.c_str());

      tempStorage = course_name; // re used tempStorage
      replaceWithHyphen(tempStorage);

      command = course_name + "|" + sem + "|" + subject_name + "|" + tempStorage + "-SEM-" + sem + "-";

      transform(command.begin(), command.end(), command.begin(), ::toupper); // convert to uppercase

      tempStorage = subject_name; // re used tempStorage
       
      replaceWithHyphen(tempStorage); 
      //transform(tempStorage.begin(), tempStorage.end(), tempStorage.begin(), ::toupper);

      command = command + tempStorage; // command for making path for writting data to file
      
      tempStorage.clear();

      tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; //* it will keep record of each semester that is created like all data of faculty | folderName

      writeDataToFile(tempStorage, command); //*writting data to file
      return 1;                              // all above code works then returns 1 = successfully
      /***************************************************************************************/
    }
    else // if that semester already exist
    {
      warnMsg("SEMSTER WITH THAT SUBJECT ALREADY EXIST !", 2, 19); // overloadedversion called
      return 0;                                                            // returns 0=failed as we are trying to create that same folder again
    }
  }
  
  //----------------FACULTY DETAILS CONFIRMATION AND MODIFICATION---------------------/

  int confirmation() //?basic confirmation message for user
  {
    int line;

    reConfirm:

    // cofirmation BOX-UI
    scrClr(0.5);

    setCursorPos(4, 15);
    cout << "FACULTY NAME " << right << setw(9) << ": " << FacultyName;
    setCursorPos(1, 15);
    cout << "FACULTY E-MAIL " << right << setw(7) << ": " << FacultyEmail;
    setCursorPos(2, 15);
    cout << "COURSE NAME " << right << setw(10) << ": " << course_name;
    setCursorPos(1, 15);
    cout << "SEMESTER " << right << setw(13) << ": " << sem;
    setCursorPos(1, 15);
    cout << "SUBJECT " << right << setw(14) << ": " << subject_name;
    setCursorPos(1, 15);
    cout << "NUMBER OF STUDENTS " << right << setw(3) << ": " << numberOfstudents;

    // message BOX-UI

    ConvertChoiceToINT = YesNoInput("Confirm these details (yes/no) ", tempStorage); // taking input yes/no

    if (ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); // error message
      goto reConfirm;
    }

    return (ConvertChoiceToINT); // returns basic confirmation value yes=1 / no=0
  }

  int InfoModification() //? MODIFICATIONS OF FACULTY DETAILS
  {

    int line;
    reInputOfmodchoice:

    line = 0;
    setCursorPos(1);
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;

    setCursorPos(1, 25);
    buildVerticalWall(27);

    while (line < 13) // BOX-UI OF modification information
    {
      setCursorPos(1, 25);
      if (line == 0)
        buildHorizontalWall(27, "1) FACULTY NAME ");
      else if (line == 2)
        buildHorizontalWall(27, "2) FACULTY E-MAIL ");
      else if (line == 4)
        buildHorizontalWall(27, "3) COURSE NAME ");
      else if (line == 6)
        buildHorizontalWall(27, "4) SEMESTER ");
      else if (line == 8)
        buildHorizontalWall(27, "5) SUBJECT ");
      else if (line == 10)
        buildHorizontalWall(27, "6) NUMBER OF STUDENTS ");
      else if (line == 12)
        buildHorizontalWall(27, "7) NO CHANGE ");
      else
        buildHorizontalWall(27, " ");
      line++;
    }

    setCursorPos(1, 25);
    buildVerticalWall(27);

    askChoice(2, 32, tempStorage); // ask choice

    if (!cin)// new line(enter key input ignoring) // not necessary bcz it is set as invalid input error
    {
      cin.clear();
      cin.ignore(80, '\n');
    }
    ConvertChoiceToINT = validateString(tempStorage, 7, 1); // validate input

    if (ConvertChoiceToINT == 0) // if wrong input
    {
      goto reInputOfmodchoice; // repeat the process until correct input
    }
    else
    {
      return (ConvertChoiceToINT); // return the number option of modification
    }
  }

  /***************************************************************************/

  //********** STUDENT DETAILS CONFIRMATION AND MODIFICATION ****************/

  int studConfirmation() //?basic confirmation message for user
  {
    int line;

    reConfirm:
    scrClr(0.5);//clear screen

    // BOX-UI FOR STUDENT INFO CONFIRM
    setCursorPos(5, 15);
    cout << "STUDENT ROLL NO " << right << setw(4) << ": " << RoLLNo;
    setCursorPos(1, 15);
    cout << "STUDENT NAME " << right << setw(7) << ": " << student_name;
    setCursorPos(1, 15);
    cout << "STUDENT E-MAIL " << right << setw(5) << ": " << student_email;

    ConvertChoiceToINT = YesNoInput("Confirm these details (yes/no) ", tempStorage); // taking input yes/no

    if (ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); // error message
      goto reConfirm;//again show studnt details
    }

    return (ConvertChoiceToINT); // returns basic confirmation value yes=1 / no=0
  }

  int InfoStudModification() //? MODIFICATIONS OF STUDENTS DETAILS
  {

    int line;
    reInputOfmod:

    line = 0;
    setCursorPos(3);//set cursor position
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;

    setCursorPos(2, 25);
    buildVerticalWall(23);

    // BOX-UI FOR MODIFICATION INFORMATION OF STUDENTS
    while (line < 7)
    {
      setCursorPos(1, 25);
      if (line == 1)
        buildHorizontalWall(23, "1) STUDENT NAME ");
      else if (line == 3)
        buildHorizontalWall(23, "2) STUDENT E-MAIL ");
      else if (line == 5)
        buildHorizontalWall(23, "3) NO CHANGE");
      else
        buildHorizontalWall(23, " ");
      line++;
    }

    setCursorPos(1, 25);
    buildVerticalWall(23);

    askChoice(3, 32, tempStorage);//ask choice

    if (!cin)// new line(enter key input ignoring) // not necessary bcz it is set as invalid input error
    {
      cin.clear();
      cin.ignore(80, '\n');
    }
    ConvertChoiceToINT = validateString(tempStorage, 3, 1); // validate input

    if (ConvertChoiceToINT == 0) // if wrong input
    {
      goto reInputOfmod; // re take choice of modification
    }
    else
    {
      return (ConvertChoiceToINT); // returns number option of modification
    }
  }

  /************************************************************************/

  void UpdateName(string &input) //?Faculty & student name update input
  {
    reinput:

    scrClr(0.5);//clear screen
    setCursorPos(9, 20);
    cout << "ENTER NAME : ";
    fflush(stdin);//buffer empty
    ShowConsoleCursor(true);
    getline(cin, input);//take input
    ShowConsoleCursor(false);

    if (EmptyInput(input))//if input is empty than error
    {
      InvalidInputErr(); // input error
      goto reinput;//re-ask student name
    }
  }

  void UpdateEmail(string &input) //?Faculty & student email address update & input
  {
    reinputOfEmail:

    scrClr(0.5);//clear screen
    setCursorPos(9, 16);
    cout << "ENTER E-MAIL : ";
    fflush(stdin);//buffer clear
    ShowConsoleCursor(true);
    getline(cin, input);//take input
    ShowConsoleCursor(false);
    
    transform(input.begin(), input.end(), input.begin(), ::tolower); // convert to uppercase

    if(EmptyInput(input)) // EmptyInput VALIDATION
    {
      InvalidInputErr(); // input error
      goto reinputOfEmail;
    }
    else if (!validateEmail(input)) // email validation
    {
      warnMsg("INVALID E-MAIL ADDRESS !", 4, 26);//warn msg function call
      goto reinputOfEmail;//re-ask email
    }
    scrClr(0.5); // screen stops for reading
  }

  void EnterCourseName() //?course name input
  {
    reinputOfcourseName:

    scrClr(0.5);//clear screen
    setCursorPos(9, 26);
    cout << "ENTER COURSE NAME : ";
    fflush(stdin);//buffer clear
    ShowConsoleCursor(true);
    getline(cin, course_name);//take input
    ShowConsoleCursor(false);

    if (EmptyInput(course_name))//check course_name is empty or not
    {
      InvalidInputErr();//invalid input error
      goto reinputOfcourseName;//re-ask course_name
    }

    scrClr(0.5);//clear screen
  }

  void EnterSem() //?input of semester
  {
    reinputOfsem:

    scrClr(0.5);//clear screen
    fflush(stdin);//buffer clear
    setCursorPos(9, 26);
    cout << "ENTER SEMESTER : ";
    fflush(stdin);
    ShowConsoleCursor(true);//cursor show on console
    getline(cin, sem);//take input
    ShowConsoleCursor(false);// hide cursor to stop flickring cursor

    if (!validateString(sem, 10, 1)) // validate sem input
    {
      goto reinputOfsem;//re-ask sem
    }

  }
  
  void EnterSubject() //?input subject
  {
    reinput:

    scrClr(0.5);//clear screen
    setCursorPos(9, 26);
    cout << "ENTER SUBJECT : ";
    ShowConsoleCursor(true);//cursor show on console
    fflush(stdin);
    getline(cin, subject_name);//take input
    ShowConsoleCursor(false);// hide cursor to stop flickring cursor

    if (EmptyInput(subject_name))//check subject name is empty or not
    {
      InvalidInputErr();//invalid input error
      goto reinput;//re-ask subject name
    }

  }

  void rollNo(int RollNo) //?show Roll Number
  {
    scrClr(0.5);              // clear screen
    ShowConsoleCursor(false); // hide cursor to stop flickring cursor
    setCursorPos(9, 27);
    cout << " ROLL NO. : " << RollNo;
    scrClr(1); // user can read no. FOR 1 SECOND
  }

  void askNumberOfStudents() //?asking number of students
  {
    reAskNumStud:
    
    scrClr(0.5);//clear screen
    setCursorPos(7, 23);//set cursor position
    cout << " HOW MANY STUDENTS DO YOU HAVE ? ";
    setCursorPos(4, 27);
    cout << "NUMBER OF STUDENT : ";
    fflush(stdin);//buffer clear
    ShowConsoleCursor(true);// show cursor on console
    getline(cin, numberOfstudents);//take input
    ShowConsoleCursor(false);// hide cursor to stop flickring cursor
    
    ConvertChoiceToINT = validateString(numberOfstudents, 5000, 1);
    if (ConvertChoiceToINT == 0)  //if roll no is greater than 5000 and less than 1 then
    {
      goto reAskNumStud;   //take reinput of roll no
    }
  }

  public:

  MODULE_1()//constructer
  {
   command.clear();//command clear
   tempStorage.clear();//tempStorage clear
  }
  ~MODULE_1()//destructer
  {
    command.clear();//command clear
    tempStorage.clear();//tempStorage clear
    
  }

  void askFacDetails() //?asking faculty details
  {

    reAskFacDet: // re asking  details of faculty

    EnterCourseName(); // course name input
    EnterSem();        // sem input
    EnterSubject();    // subject input

    if(!createSemester()) // semester confirmation
    {
      goto reAskFacDet; // reasking faculty details as semester already exists
    }

    askNumberOfStudents(); // number of students INPUT

    command = AMS_Path + "\\USER-INFO\\userdetails.txt"; // making path for getting data from file

    getDataFromFile(command, FacultyName, 1);  // taking faculty name of from file
    getDataFromFile(command, FacultyEmail, 2); // taking  faculty email  of from file

    confirmAgain: // final confirmation

    if (confirmation()) // basic confirmation dialog if yes then semester folder create
    {
      command = SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; // path making for writting into file

      // writting faculty data to files

      writeDataToFile(command, FacultyName);
      writeDataToFile(command, FacultyEmail);
      writeDataToFile(command, course_name);
      writeDataToFile(command, sem);
      writeDataToFile(command, subject_name);
      writeDataToFile(command, numberOfstudents);
    }
    else
    {
      scrClr(0.5); // clear screen so flickring won't happen

      switch(InfoModification()) // which details do you want to update that function returns
      {       // each function called according to requirement
              case 1:
              {
                UpdateName(FacultyName);
                break;
              } 
              case 2:
              {
                UpdateEmail(FacultyEmail);
                break;
              }
              case 3:
              {
                EnterCourseName();
                break;
              }
              case 4:
              {
                EnterSem();
                break;
              }
              case 5:
              {
                EnterSubject();
                break;
              }
              case 6:
              {
                askNumberOfStudents();
                break;
              }
              case 7:
              {
                scrClr(0.5);
                break;
              }

              }
             goto confirmAgain; // ask user to final confirmation
     }
  }

  void askStudDetails() //? asking students details
  {
    int ROLLNO = 0;
    while (ROLLNO < stoi(numberOfstudents)) // functions for taking student data input roll no wise
    {
      ROLLNO++;

      rollNo(ROLLNO);             // for take input of roll no
      UpdateName(student_name);   // for take input of student name
      UpdateEmail(student_email); // for taking input of email

      confirmAgain: // final confirmation
      RoLLNo = convertIntToString(ROLLNO);//convert ROLLNO integer to string

      if (studConfirmation()) // basic confirmation dialog if yes then semester folder create
      {
        command = SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; // path making for writing into file
        RoLLNo = convertIntToString(ROLLNO);                                        // rollNo Int to string
        tempStorage = RoLLNo + "|" + student_name + "|" + student_email;            // folder name
        writeDataToFile(command, tempStorage);                                      // writing data to files
      }
      else
      {
        scrClr(0.5); // clear screen so flickring won't happen

        switch (InfoStudModification()) // which details do you want to update that function returns
        {
            case 1:
            {
              UpdateName(student_name);//student name modifiaction
              break;
            }
            case 2:
            {
              UpdateEmail(student_email);//student email modifiaction
              break;
            }
            case 3:
            {
              scrClr(0.5);//clear screen
              break;
            }
        }
        goto confirmAgain; // ask user to final confirmation
      }
    }
  }

  void SetUpSucceed() // module 1 successfully worked
  {
    tempStorage = course_name + " SEM " + sem + " " + subject_name;//uesr's entered folder name stor in tempStorage
    MSG(tempStorage," SET UP SUCCESSFUL ", 2, 0, 20);//print last succeed msg
  }

  protected:

  void SetNoObj()
  {
    //* by empty defination of pure virtual function here we are restricating creation of parent class
  }

  //*==============================MEMBERS-FUNCTIONS===================================//
};

class MODULE_2 : public MODULE_GENERAL //?module 2 class
{

  //******************************** DATA-MEMBERS **********************************/

private:

  vector<string> buffer, LIST;                        // vector buffer for file handling data receiver
  vector<tuple<string, string, string, string>> DATA; // search-access vector-tuple

public:

  static int AT_OPTION_CHOICE;

protected:

  //*********************************************************************************/

  //******************************** MEMBER-FUNCTIONS *********************************/

private:
 

   int validateRollNo(string input, int Bnd, int start) //? string input validate as integer
   {
      int flag = 0, tem = 1;
     
      if (start == 0)//roll no is 0
          start++;
      for(tem = start; tem <= Bnd; tem++)//roll no start with 1 and go to end boundry
      {
        if(to_string(tem) == input) // convert tem int to string to check input valid condition
        {
          flag = 1;//if condition true than flag =1
          break;
        }
      }
      if(EmptyInput(input))//empty input check
      {
        InvalidInputErr(); // input error
        return 0;        
      } 
      else if(flag == 0) //*IF flag=0 means input is invalid
      {
        MSG("ROLL NO. NOT EXIST ! ","RE-ENTER VALID ROLL NO",4,1,18);
        return 0; //wait
 
      }
      else
      {
        return tem; //*returns converted string.to_int(INT)
      }
     
    }

  int checkDuplicateRecord(vector<string> vec, string search) //?for cheking if duplicate records found in vector_storage
  {
    vector<string>::iterator it; // iterator

    it = find(vec.begin(), vec.end(), search); // finding elemnt in vector

    if (it != vec.end())
    {
      return 0; // if found then return 0
    }
    else
    {
      return 1; // if not found then return 1
    }
  }
  bool checkExistRollNo(string &Attendance,string rl,char AT,int select=0)//?if same roll no is exist than print error
  {
    if(Attendance[(stoi(rl)-1)]==AT)//if user enter roll no is already exist in string than 
    {
      if(select==0)
        MSG("ROLL NO. IS ALREADY IN LIST !"," ",2,0,24);//print error msg
      else
        MSG("ROLL NO. DOESN'T EXIST IN THE LIST !"," ",2,0,22);//else print doesn't exist
      return true;
    }
    else
    {
      return false;
    }
  } 
  void DisplayList_Input(string &put, int select = 0) //? display the list and take appropriate input of corse/sem/subject
  {
    int listFlag = 1, chFlag = 0, countFlag = 0, temp_flag = 1;
    auto i = LIST.begin();

    (LIST.size() > 6) ? setCursorPos(0, 10) : setCursorPos(1, 20); // set box-view for list >5 and less than 5
    buildVerticalWall(35);
    setCursorPos(1, 20);
    buildHorizontalWall(35, " ");

    while (i != LIST.end()) // dynamic list loop for sem course subject input choice
    {

      displayAgain:
      chFlag = 0;
      setCursorPos(1, 20);
      if (select == 0)
        buildHorizontalWall(35, to_string(5 * countFlag + listFlag) + ") " + (*i));
      else
        buildHorizontalWall(35, to_string(5 * countFlag + listFlag) + ") " + "Sem-" + (*i));
        
      setCursorPos(1, 20);
      buildHorizontalWall(35, " ");
      listFlag++;
      i++;

      if (listFlag > 5 && i != LIST.end())
      {

        chFlag = 1;
        countFlag++;
        setCursorPos(1, 20);
        buildHorizontalWall(35, "TYPE '+' FOR EXTENDED LIST");
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");
        setCursorPos(1, 20);
        buildVerticalWall(35);
        askChoice(2, 34, tempStorage);//ask choice
        scrClr(0.5);
        if(tempStorage == "+")//if uesr press +
        {
           setCursorPos(2, 20);
           buildVerticalWall(35);
           listFlag = 1;//list flag =1 
           chFlag = 0;
           setCursorPos(1, 20);
           buildHorizontalWall(35, " ");
           goto displayAgain;//again display screen
        }
        else
        {
          ConvertChoiceToINT = validateString(tempStorage, countFlag * 5, (countFlag - 1) * 5);//validatestring 
          
          if(ConvertChoiceToINT == 0)
          {
            while (temp_flag != (listFlag))
            {
              i--;
              temp_flag++;
            }
            
            temp_flag = 1;
            countFlag--;
            listFlag = 1;
            
            setCursorPos(2, 20);
            buildVerticalWall(35);

            chFlag = 0;

            setCursorPos(1, 20);
            buildHorizontalWall(35, " ");
            
            goto displayAgain;
          }
          else
          {
            break;
          }
        }
      }
    }

    if(chFlag == 0)
    {
      setCursorPos(1, 20);
      buildVerticalWall(35);
      askChoice(2, 30, tempStorage);

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

        setCursorPos(2, 20);
        buildVerticalWall(35);
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");

        goto displayAgain;
      }
      ConvertChoiceToINT = validateString(tempStorage, (((countFlag)*5 + listFlag - 1)), ((countFlag)*5));
      
      if(ConvertChoiceToINT == 0)
      {
        while(temp_flag != (listFlag))
        {
          i--;
          temp_flag++;
        }

        temp_flag = 1;
        listFlag = 1;

        setCursorPos(2, 20);
        buildVerticalWall(35);
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");

        goto displayAgain;
      }
      scrClr(0.5);
    }
    for(i = LIST.begin(), countFlag = 1; i != LIST.end(); ++i, countFlag++) // set data to string for searching
    {
      if(countFlag == ConvertChoiceToINT)
      {
        put = (*i);
      }
    }

    LIST.clear();        // flush vector data for re-using
    tempStorage.clear(); // flush string for re-using
  }

  void getFolderPath() //? based on input choice of course->sem-subject we find correct folder and save path  to Sem_path
  {
    for(auto i = DATA.begin(); i != DATA.end(); ++i) // process to find folder path using vector tuple we have 3 input parameter coursename , sem , subject name
    {

      if(course_name == get<0>((*i)))
        if(sem == get<1>((*i)))
          if(subject_name == get<2>((*i)))
            SemPath = get<3>((*i));
    }

    SemPath = AMS_Path + "\\" + SemPath; // assigning searched path to SemPath and concate AMS_Path

  }

  void getSemesterRecordFile() //? get data of course-semester-sub-path records
  {
    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; // making path to AMS->OTHER->semsterRecord.txt
    fstream fin(tempStorage.c_str(), ios::in);              // file opened in reading mode

    if(!fin.is_open()) // if not opened
    {
      cout << " DATABASE ERROR 404 : FILE NOT OPENED !";
    }
    else // if opened
    {
      tempStorage.clear();       // clear for re-using
      getline(fin, tempStorage); // tempStorage used as temporary storage

      while(!fin.eof()) // data receive until file ends
      {
        buffer.push_back(tempStorage); // save that string(data) in vector
        getline(fin, tempStorage);     // fetch again from file
      }
      fin.close(); // file close
    }

    sort(buffer.begin(), buffer.end()); // sort file data in vector in Dictionary order
    tempStorage.clear();
  }

  void ExtractStringFromBuffer() //? extracting main string into substring like course - sem - sub - path
  {
    for(auto i = buffer.begin(); i != buffer.end(); ++i) // insert in to vector-tuple from vector buffer with extracting string
    {
      tempStorage = (*i);      // temp variable for moving vector tempStorage to string
      int found_pos, temp_pos; // temp variable for position storing

      found_pos = tempStorage.find("|");                // find the first occurance of '|'
      course_name = tempStorage.substr(0, (found_pos)); // get proper course name from string and save it to course_name
      temp_pos = (found_pos + 1);                       // making next finding position

      if(checkDuplicateRecord(LIST, course_name)) // checking if any duplicate course exists
      {
        LIST.push_back(course_name); // making list for input of UI screen of course select
      }

      found_pos = tempStorage.find("|", temp_pos);                // finds string till 1st pipe i.e coursename
      sem = tempStorage.substr(temp_pos, (found_pos - temp_pos)); // stores the string in TEMP_STR
      temp_pos = (found_pos + 1);                                 // searching next position

      found_pos = tempStorage.find("|", temp_pos);                         // finds string till 2nd pipe i.e. semester
      subject_name = tempStorage.substr(temp_pos, (found_pos - temp_pos)); // stores the string in TEMP_STR
      temp_pos = (found_pos + 1);                                          // searching next position

      found_pos = tempStorage.find("|", temp_pos); // finds string till 3rd pipe i.e. subjectname
      SemPath = tempStorage.substr(temp_pos);      // stores the string in TEMP_STR

      DATA.push_back(make_tuple(course_name, sem, subject_name, SemPath)); // makes a final string to display
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
    command = SemPath + "\\DAILY-RECORD\\records.txt";//path stored in command variable   //variable re-use
    std::ifstream inputStream(command.c_str());//read file

    while(getline(inputStream, line))//read line from file
    {
      lines.push_back(line);
    }

    inputStream.close();//file close
    command.clear();//variable clear for re-use

    command = SemPath + "\\DAILY-RECORD\\records.txt";//again path stored in comm
    std::fstream outputStream(command.c_str(), ios::out | ios::trunc);//file open in writing mode

    if(outputStream.is_open())//if file is open
    {
      for(int i = 0; i < lines.size() - 1; i++)//read line from file 
      {
        outputStream << lines[i] << "\n";//put in file
      }
      outputStream.close();//file close
    }
  }

  int ValidateAttendance(string &input) //?attendance validation to mark either P or A
  {
    for(int i = 0; i < input.length(); i++)
    {
      input[i] = toupper(input[i]);//input string covert into uppercase
    }
    if(input == "P" || input == "A")//if is P or A
    {
      return 1;//return true
    }
    else//if p or a not than
    {
      return 0;//return false
    }
  }

  void ListOfAttendance(string &Attendance, int choice) // ? Final List for absent and present student
  {
    int i,spacing_flag=0,space=1;
    
    if(choice == 3)//if user enterd choice is present
    {
      setCursorPos(2,24);
      cout << "|| LIST OF PRESENT ROLL NO. ||" << endl; // present list
      setCursorPos(1,1);
      SetColor(1);//set color 

            for(i = 0;i < Attendance.length(); i++)//list is check while atttandance length
            {
               if(Attendance[i] == 'P')//than is == to P
               { 
                 if(space>=49&&space<=53)//space is between 49 to s3
                    spacing_flag=1;//than set flag as 1
       
                 if(spacing_flag==0)//if flage is 0 than condition is false
                 {
                  cout << i + 1 << " ";
                  if(i<10)
                  space++;
                  else if(i<100)
                  space+=2;
                  else if(i<1000)
                  space+=3;
                  else if(i<10000)
                  space+=4;
                 }
                 else
                 {
                   setCursorPos(1,1);
                   spacing_flag=0;
                   space=-2;
                   cout << i + 1 << " ";
                   if(i<10)
                   space++;
                   else if(i<100)
                   space+=2;
                   else if(i<1000)
                   space+=3;
                   else if(i<10000)
                   space+=4;
                  }
               }
            }
       
    }

    else if(choice == 4)
    {
      setCursorPos(2,24);
      cout << "|| LIST OF ABSENT  ROLL NO. ||" << endl; // absent list
      setCursorPos(1,1);
      SetColor(4);
      
             for(i = 0; i < Attendance.length(); i++)
             {
               if(Attendance[i] == 'A')
               {
                    
                    if(space>=49&&space<=53)
                    {spacing_flag=1;}
       
                    if(spacing_flag==0)
                    {
                      cout << i + 1 << " ";
                      if(i<10)
                      space++;
                      else if(i<100)
                      space+=2;
                      else if(i<1000)
                      space+=3;
                      else if(i<10000)
                      space+=4;      
                    }
                    else
                    { 
                      setCursorPos(1,1);
                      spacing_flag=0;
                      space=-2;
                      cout << i + 1 << " ";
       
                      if(i<10)
                      space++;
                      else if(i<100)
                      space+=2;
                      else if(i<1000)
                      space+=3;
                      else if(i<10000)
                      space+=4;
                    }
               }
             }
            

      
    }

    SetColor(0);

  }

  bool ModificationOfAttDATA(string &Attendance,int choice) // ? modify the attendance data
  {    
      int Empty_flag=0,i;
      bool return_flag=false;
   
      command.clear(); //variable clear


      while(true)
      {    
           MDAgain:
           scrClr(0.5);//clear screen
 
           setCursorPos(1,26);
           SetColor(2);//set color is green
           cout << "TYPE '*' WHEN YOU ARE DONE" ;
           SetColor(0);//set color black
         
           ListOfAttendance(Attendance,choice);//show list of student
          
           setCursorPos(2,13);//set cursor position
          //ask you want to modify
           if(choice == 3)
              cout << " ENTER ROLL NO. THAT YOU WANT TO MARK AS ABSENT  : ";
           else if(choice == 4)
              cout << " ENTER ROLL NO. THAT YOU WANT TO MARK AS PRESENT : ";
         
           ShowConsoleCursor(true);//set console cursor
           getline(cin,command);//take input
           ShowConsoleCursor(false);//set console cursor as hide
           if(command=="*")//if user enter *
           {    
               return_flag=true;//flag is true
               break;
           }

           ConvertChoiceToINT = validateRollNo(command,stoi(numberOfstudents), 1);//validate string
           
           if(ConvertChoiceToINT)
           {
             if(choice == 3)//if choice is prasent
             {
               if(checkExistRollNo(Attendance,command,'A',1))//check roll no is aleady eist than print error
               goto MDAgain;//go to list shown again
               else
               Attendance.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
             }
             else if(choice == 4)//if choice is absent
             {
               if(checkExistRollNo(Attendance,command,'P',1))//check roll no is aleady eist than print error
               goto MDAgain;//go to list shown again
               else
               Attendance.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
             }
           }

           Empty_flag=0;//fkag set as 0
           i=0;//i  set as 0

           if(choice == 3)//if choice is present
           {
             while(i<=Attendance.length())
             {
               if(Attendance[i]=='P')//attendance is == p
               {
                 Empty_flag=1;//flag is true
                 break;
               }
               Empty_flag=0;//else flag set as 0
               i++;
             }
           }
           else if(choice == 4)//if choice is absent
           { 
             while(i<=Attendance.length())
             {
               if(Attendance[i]=='A')//attendance is A
               {
                 Empty_flag=1;//flage set as true
                 break;
               }
               Empty_flag=0;//else flag is 0
               i++;
             }
           } 
           if(!Empty_flag)//if flag is false
           {     
                   
             if(choice == 3)//if choice is present than
              MarkAP_A(2); // all absent
             else if(choice ==4)//if choice is absent than
              MarkAP_A(1); //all present
              return_flag = false;//flag set 0
              break;
           }
           
      }

      return(return_flag);//return flag
      
  }

  void submitAttendanceToDB(string & Attendance) // ? Finally data sent to database
  {
    int sz;
    command.clear();//variable clear
    command = SemPath + "\\DAILY-RECORD\\records.txt"; // making path for file handling

    ifstream finin(command.c_str(), ios::binary);         // open file in append mode
    finin.seekg(0,ios::end);
    sz = finin.tellg();//check file size
    finin.close();//file close

    fstream finout(command.c_str(), ios::app);
    if(!sz)
    {
      finout << CUR_DATE + " | " + CUR_TIME + " | " + Attendance;    // write data to file
    }
    else
    {
       finout <<"\n" + CUR_DATE + " | " + CUR_TIME + " | " + Attendance;
    }
     
     finout.close();                                    // file close
  }

  string lastline()
  {
      ifstream fin;
      string lastLine;

      command.clear();
      command = SemPath + "\\DAILY-RECORD\\records.txt";

      fin.open(command.c_str());
      if(fin.is_open())
      {
        fin.seekg(-1, ios_base::end); // go to one position before the EOF

        bool keepLooping = true;

        while(keepLooping)
        {
          char ch;
          fin.get(ch); // Get current byte's data

          if((int)fin.tellg() <= 1)
          {                      // If the data was at or before the 0th byte
            fin.seekg(0);        // The first line is the last line
            keepLooping = false; // So stop there
          }
          else if (ch == '\n')
          {                      // If the data was a newline
            keepLooping = false; // Stop at the current position.
          }
          else
          {                               // If the data was neither a newline nor at the 0 byte
            fin.seekg(-2, ios_base::cur); // Move to the front of that data, then to the front of the previous data
          }
        }

        getline(fin, lastLine); // Read the current line
        fin.close();

      }

      return lastLine;
    }

    int MarkAP_A(int choice) //? function to mark all students present/absent at once
    {
      tempStorage.clear();
      command.clear();

      for(int i = 1; i <= stoi(numberOfstudents); i++) //*intially data written to tempStorage which will be finally written into DB file
      {
        if(choice == 1)
          tempStorage += "P"; // all present
        else if(choice == 2)
          tempStorage += "A"; // all absent
      }
      
      confirm:

      if(choice == 1)
      {

        scrClr();
        setCursorPos(5, 14);
        ShowConsoleCursor(false);

        SetColor(0);
        cout << "ALL ";

        SetColor(2);
        cout << numberOfstudents;

        SetColor(0);
        cout << " STUDENTS ON ";

        SetColor(2);
        cout << CUR_DATE;

        SetColor(0);
        cout << " WILL BE MARKED AS PRESENT";
        
      }
      else if(choice == 2)
      {
        scrClr();
        setCursorPos(5, 14);
        ShowConsoleCursor(false);

        SetColor(0);
        cout << "ALL ";

        SetColor(2);
        cout << numberOfstudents;

        SetColor(0);
        cout << " STUDENTS ON ";

        SetColor(2);
        cout << CUR_DATE;

        SetColor(0);
        cout << " WILL BE MARKED AS ABSENT";
        
      }

      setCursorPos(3); 

      if(choice==1)
      {
        ConvertChoiceToINT = YesNoInput("ALL PRESENT !", command,"ARE YOU SURE ?",1);
      }
      else if(choice==2)
      {
        ConvertChoiceToINT = YesNoInput("ALL ABSENT  !", command,"ARE YOU SURE ?",1);
      }
      if(ConvertChoiceToINT == -1)
      {
        InvalidInputErr();
        goto confirm;
      }

      if(ConvertChoiceToINT == 1)
        submitAttendanceToDB(tempStorage);

      return (ConvertChoiceToINT);
    }

    int EnterPR_AR(int choice) // ? function for manually entering absent OR present numbers
    {

      int i,Empty_flag=0;
      bool flag=true;
      tempStorage.clear();
      command.clear();

      string MCH;

      for(i = 1; i <= stoi(numberOfstudents); i++) // fill up all data with all absent or all present by default initially
      {
        if (choice == 3)
          tempStorage += "A";
        else if (choice == 4)
          tempStorage += "P";
      }
        if(choice == 3)
        {
          while(i<=tempStorage.length())
          {
            if(tempStorage[i]=='P')
            {
              Empty_flag=1;
              break;
            }
            Empty_flag=0;
            i++;
          }
        }
        else if(choice == 4)
        {
          while(i<=tempStorage.length())
          {
            if(tempStorage[i]=='A')
            {
              Empty_flag=1;
              break;
            }
            Empty_flag=0;
            i++;
          }
        }

   
      while(true)
      {
         

         reInput:
         
         scrClr(0.5);
         
         setCursorPos(1,26);
         SetColor(2);
         cout<<"TYPE '*' WHEN YOU ARE DONE";
         SetColor(0);         

         ListOfAttendance(tempStorage,choice);
        
         setCursorPos(2,26);
         
         if(choice == 3)
            cout << "ENTER PRESENT ROLL NO. : ";
         else if(choice == 4)
            cout << "ENTER ABSENT ROLL NO.  : ";
         
         ShowConsoleCursor(true);
         fflush(stdin);
         getline(cin, MCH);
         ShowConsoleCursor(false);
         
          if(MCH=="*")
          {  

            if(!Empty_flag)
            {
                if(choice == 3)
                {
                 scrClr(0.5);
                 setCursorPos(9,24);
                 SetColor(1);
                 cout << "ADD ATLEAST 1 PRESENT ROLL NO. !"<< endl; //warn message
                 scrClr(1);
                 SetColor(0);
                 goto reInput;

                }
                else if(choice == 4)
                {
                 scrClr(0.5);
                 setCursorPos(9,24);
                 SetColor(4);
                 cout << "ADD ATLEAST 1 ABSENT  ROLL NO. ! " << endl; //warn message
                 scrClr(1);
                 SetColor(0);
                 goto reInput;
                }
             
            }
            else  
            {
              break;
            }
             
          }
             
          ConvertChoiceToINT = validateRollNo(MCH, stoi(numberOfstudents), 1);
          
          if(ConvertChoiceToINT)
          {
            // cout<< endl << "checkexist";
            if(choice == 3)
            {
              // cout<< endl << "checkexist";
              if(checkExistRollNo(tempStorage,MCH,'P')) // check exist warning present
              goto reInput;
              else
              tempStorage.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
              
            }
            else if(choice == 4)
            {
              if(checkExistRollNo(tempStorage,MCH,'A')) // check exist warning absent
              goto reInput;
              else
              tempStorage.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
            }
              
          }

          Empty_flag=0;
          i=0;

          if(choice == 3)
          {
            while(i<=tempStorage.length())
            {
              if(tempStorage[i]=='A')
              {
                Empty_flag=1;
                break;
              }
              Empty_flag=0;
              i++;
            }
         }
         else if(choice == 4)
         {
           while(i<=tempStorage.length())
           {
             if(tempStorage[i]=='P')
             {
               Empty_flag=1;
               break;
             }
             Empty_flag=0;
             i++;
           }
         }

      }

      confirm:
      scrClr(0.5);
      
      ListOfAttendance(tempStorage,choice);
      
      command.clear();
      
      setCursorPos(4,17);
      ConvertChoiceToINT = YesNoInput(" DO YOU CONFIRM THESE ROLL NO. ? ", command);
      if(ConvertChoiceToINT == -1)
      {
        InvalidInputErr();
        goto confirm;
      }
      else if(ConvertChoiceToINT == 0)
      {
        if(ModificationOfAttDATA(tempStorage,choice))
        {
        goto confirm;
        }
        else
         flag=false;
      }

      if(ConvertChoiceToINT == 1&&flag==true)
      {
        submitAttendanceToDB(tempStorage);
      }

      
      return (ConvertChoiceToINT);
    }

  public:

    MODULE_2()
    {
      command.clear();
      tempStorage.clear();
    }

    ~MODULE_2()
    {
      buffer.clear(); // clearing buffer
      LIST.clear();   // clearing List
      command.clear();
      tempStorage.clear();
    }

    int checkDB() //? functions for checking at least(1) database semster Records exists or not
    {
        //tempStorage.clear();
        //tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; // making path to AMS->OTHER->semsterRecord.txt
        
        if(!checkEmptyFile(AMS_Path + "\\OTHER\\semesterRecord.txt")) //check for proper file input
        {
          warnMsg("NO SETUP EXIST ! PLEASE ADD ATLEST 1 SETUP", 4, 19); // warn msg
          return(false);
        }
        else
        {
          getSemesterRecordFile();
          ExtractStringFromBuffer();
          return (true);
        }
  
        //tempStorage.clear();
        
    }

    void askCourseChoice() //? take input choice of course for attendance
    {
      DisplayList_Input(course_name); // display list for taking input

      for(auto i = DATA.begin(); i != DATA.end(); ++i) // process to make list of semester in particular course
      {

        if(course_name == get<0>((*i)))
        {
          if(checkDuplicateRecord(LIST, get<1>((*i)))) // cheking if any duplicate records
          {
            LIST.push_back(get<1>((*i))); // making distinguished list
          }
        }
      }
    }

    void askSemsterChoice() //? take input choice of semester for attendance
    {
      DisplayList_Input(sem, 1);

      for(auto i = DATA.begin(); i != DATA.end(); ++i) // process to make list of subject in particular course & semester
      {
        if(course_name == get<0>((*i)) && sem == get<1>((*i)))
        {
          if(checkDuplicateRecord(LIST, get<2>((*i))))
          {
            LIST.push_back(get<2>((*i)));
          }
        }
      }
    }

    bool askSubjectChoice() //? take input choice of subject for attendance
    {
      //tempStorage.cler();
      DisplayList_Input(subject_name);
      getFolderPath();
      //command.clear();
      //tempStorage.cler();
      
      // tempStorage =  // making path to access student-sem-?-.tx
      //command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // making path to access faculty-sem-?-.tx
      
      if(checkEmptyFile(SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt") && checkEmptyFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt") )
      {
        return true;
      }
      else
      {
        //error part
        warnMsg(course_name +" SEM-" + sem + " " +subject_name,1,23," PLEASE DELETE & RE-CREATE IT",4,21);
        return false;
      }
      
    }

    int proceedForAttendance() //? functions for reconfirming to proceed for attendance
    {
      int line = 0;
      reinputforattedance:

      scrClr(0.5); // clear screen

      line = 0;
      command.clear();
      
      command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // making path to access faculty-sem-?-.tx
      

      //*BOX-UI FOR Details confirmation

      setCursorPos(1, 7);
      buildVerticalWall(65);

      while(line < 13)
      {
        setCursorPos(1,7);
        if(line == 1)
        {
            getDataFromFile(command,FacultyName,1); // getting facultyname file
            buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
        }
        else if(line == 3)
        {
            buildHorizontalWall(65, "COURSE               :  " + course_name);
        }
        else if(line == 5)
        {
            buildHorizontalWall(65, "SEM                  :  " + sem);
        }
        else if(line == 7)
        {  
            buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
        }
        else if(line == 9)
        {
            getDataFromFile(command, numberOfstudents,6);
            buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
        }
        else if(line == 11)
        {
          cout << "|";
          Date(0, 9);
          Time(0, 7);
          cout << setw(18) << "|";
        }
        else
          buildHorizontalWall(65, " ");
        line++;
      }

      setCursorPos(1, 7);
      buildVerticalWall(65);

      tempStorage.clear();

      SetColor(1);
      setCursorPos(2, 23);
      cout << "DO YOU WANT TO PROCEED FURTHER ?";
      SetColor(0);

      setCursorPos(2, 32);
      fflush(stdin);
      ShowConsoleCursor(true);
      cout << "Type : ";
      getline(cin, tempStorage);
      ShowConsoleCursor(false);

      ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value storage

      if(ConvertChoiceToINT == -1) // validate input
      {
        InvalidInputErr(); // error message
        goto reinputforattedance;
      }

      return (ConvertChoiceToINT); // return confirmation for taking attendace
    }
    int condfirmTodayAttendance()
    {

      int i;
      ConvertChoiceToINT = 1; // re-used

      command.clear();
      tempStorage.clear();

      command = SemPath + "\\DAILY-RECORD\\records.txt";
      fstream fin(command.c_str(), ios::in);

      if(!fin.is_open())
      {
        cout << "FILE NOT NOT OPENED  ! ";
      }
      else
      {
        i = lastline().find("|");
        tempStorage = lastline().substr(0, i - 1);
        if(tempStorage == CUR_DATE) // to avoid taking attendance for the same day
        {
          command.clear();
          command = course_name + " SEM " + sem + " " + subject_name;
  
          scrClr();
          setCursorPos(8,25);
          ShowConsoleCursor(false);
          SetColor(2);
          cout << command;
          SetColor(0);
          setCursorPos(2,18);
          cout << " ATTENDANCE FOR ";
          SetColor(1);
          cout << CUR_DATE;
          SetColor(0);
          cout << " IS ALREADY TAKEN !";
          command.clear();
          ConvertChoiceToINT=0;
          scrClr(2);
        }
      
        fin.close();
      }
      return(ConvertChoiceToINT);
    }

    void AttendanceOptionWindow() //? to display window with 4 Options of attendance
    {
      int line;
      command.clear();
      tempStorage.clear();

      reAskAtdM:

      scrClr(0.5);
      setCursorPos(4, 18);
      buildVerticalWall(43);
      line = 0;

      while(line < 9) // build UI-Box screen
      {
        setCursorPos(1, 18);
        if (line == 1)
          buildHorizontalWall(43, "1) MARK ALL PRESENT ");
        else if (line == 3)
          buildHorizontalWall(43, "2) MARK ALL ABSENT ");
        else if (line == 5)
          buildHorizontalWall(43, "3) ENTER PRESENT ROLL NO. ");
        else if (line == 7)
          buildHorizontalWall(43, "4) ENTER ABSENT ROLL NO. ");
        else
          buildHorizontalWall(43, " ");
        line++;
      }
      setCursorPos(1, 18);
      buildVerticalWall(43);

      askChoice(2, 30, tempStorage); // take input

      ConvertChoiceToINT = validateString(tempStorage, 4, 1); // validate and convert to integer

      if (!ConvertChoiceToINT) // repeat process on wrong input
      {
        goto reAskAtdM;
      }

      AT_OPTION_CHOICE = ConvertChoiceToINT;

    }

    int takeAttendance(int choice) //? Select appropriate option for taking attendace
    {
      int process_flag = 0;

      if(choice == 1 || choice == 2)
      {
        process_flag = MarkAP_A(choice);
      }
      else if(choice == 3 || choice == 4)
      {
        process_flag = EnterPR_AR(choice);
      }

      return (process_flag);
    }
    void AttendanceTakenSuccessfully() // module 2 successfully worked
    {
      tempStorage.clear();
      tempStorage = course_name + " SEM " + sem + " " + subject_name;
      MSG("ATTENDANCE TAKEN OF ", tempStorage, 2, 0, 20);
    }

    protected:

    void SetNoObj()
    {
      //? by empty defination of pure virtual function here we are restricting creation of parent(GENERAL MODULE) class
    }
    //************************************************************************************/
  };

  //*---------------------------STATIC DEFINATIONS-MODULE-2------------------------------/

  int MODULE_2::AT_OPTION_CHOICE;

  //-----------------------------------------------------------------------------------/

  /**************************************   MODULES-END   ***************************************************/

  int main()
  {
    //* jay swaminrayan *//
    //* jay ganeshay namh *//
    //* jay kashtbhanjan dev *//

    bool loop = true; // set true to run app by 1 time
    int Tem;          // to accept the Choice
    APP A;

    while (loop)
    {
      A.startApp();
      A.scrClr();
      A.setCursorPos(2, 10);

      switch (APP::MODULE_CHOICE) // module choice asking
      {
        case 1:
        {
            MODULE_1 MD1;
            MD1.askFacDetails();
            MD1.askStudDetails();
            MD1.SetUpSucceed();
            break;
        }
        case 2:
        {
            MODULE_2 MD2;
            if(MD2.checkDB())
            {
              MD2.askCourseChoice();
              MD2.askSemsterChoice();
              
              if(MD2.askSubjectChoice())
              {
                    if(MD2.proceedForAttendance())
                    {
                      if(MD2.condfirmTodayAttendance())
                      {
                           reask:
                           
                           MD2.AttendanceOptionWindow();
                  
                           if(MD2.takeAttendance(MODULE_2::AT_OPTION_CHOICE))
                           {
                             MD2.AttendanceTakenSuccessfully();
                           }
                           else
                           {
                             goto reask;
                           }
      
                      }
                    }
              }     
            }

            break;
        }
        case 3:
        {
          break;
        }
        case 4:
        {
          break;
        }
        case 5:
        {
          loop = false; // exit Application
          break;
        }

        default:{cout << endl<< "ERROR: APPLICATION CRASHED!!!" << endl;exit(1);break;} //* exceptional  case
      }

        A.scrClr(); // screen clear
    }

    return 0;
  }