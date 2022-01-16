#include <algorithm> // * for transform function access
#include <conio.h>   // * console input output
#include <ctime>     // * for getting current date and time
#include <cwchar>    // * for console font purpose
#include <fstream>   // * file handling functions access
#include <iostream>  // * c++ code style use
#include <iomanip>   // * for manipulator
#include <math.h>    // * math operations
#include <regex>     // * for email validation
#include <string.h>  // * C style string related functions access
#include <string>    // * C++ STL( string library) function access
#include <stdbool.h> // * boolean operation
#include <sstream>   // * for conversion to string
#include <stdio.h>   // * for c style code use
#include <stdlib.h>  // * standard library like dynamic memory allocation and exit macros and other..
#include <tuple>     // * for using tuples
#include <thread>    // * using multi threading
#include <unistd.h>  // * for sleep function
#include <vector>    // * STL DYNAMIC ARRAY used
#include <windows.h> // * windows console related functions handle
#include <signal.h>  // * signal crtl + c handler

//--------FOR-DOCUMENT PATH GETTING------/

#include <shlobj.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

#pragma comment(lib, "shell32.lib")


inline void signal_callback_handler(int signum){signal(SIGINT, signal_callback_handler);}

//--------FOR-DOCUMENT PATH GETTING-------------/

//*if _WIN32_WINNT macro doesn't exist then conditional compilation will be done and those files will be included

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#include <wincon.h>
#include <string>

//#endif  // user 1  e.g.DRASHTI //! EOP() seek.edit(*required) :DRASHTI DHOLA

typedef struct _CONSOLE_FONT_INFOEX
{
  ULONG cbSize;
  DWORD nFont;
  COORD dwFontSize;
  UINT FontFamily;
  UINT FontWeight;
  WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

#ifdef __cplusplus
extern "C"
{
#endif
  BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

#endif // user 2 e.g.HARSHIL //! EOP() seek.edit(*required) :HARSHIL RAMANI

using namespace std; // standard namespace for  resolving naming coflicts

//***************************** APP-CLASS ***********************************/

void Debug(string t) 
{ 
  system("cls");
  cout << endl << t << getch();
}
void Debug(int t)
{ 
  system("cls");
  cout << endl << t << getch();
}

//********* GLOBAL VARIABLE **************//

bool process_flag = false;
bool email_flag = false;

/****************************************/

class APP
{

public:
  static int MODULE_CHOICE; // module selector

public:
  APP()
  {
    //*******************GET-CURRENT-DATE**************************//

    string temp;                      // temp variable for storage
    time_t tmNow;                     // structure variable
    tmNow = time(NULL);               // set to initial zero=NULL
    struct tm t = *localtime(&tmNow); // pre defined function

    stringstream ss; // string stream class object
    ss << t.tm_mday; // pass day
    temp = ss.str(); // it returns as string

    if (stoi(temp) < 10) // if date-day is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      temp = "0" + temp;
    }

    CUR_DATE = temp; // save to input parameter

    ss.str(""); // flush string stream class so new input can be taken

    ss << (t.tm_mon + 1);      // pass months
    temp = ss.str();           // returns month
    cur_month = stoi(temp);    // store current month
    CUR_DATE = CUR_DATE + "/"; // add slash  for formet dd/mm/yy

    if (stoi(temp) < 10) // if date-month is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      temp = "0" + temp;
    }

    CUR_DATE = CUR_DATE + temp; // concate to input para

    ss.str("");
    ss << (t.tm_year + 1900);   // pass year
    temp = ss.str();            // returns year
    CUR_DATE = CUR_DATE + "/";  // add slash
    CUR_DATE = CUR_DATE + temp; // concate to input para

    ss.str(""); // flush string stream class so new input can be taken

    /*******************CURRENT-DATE**********************************/

    //*******************GET-CURRENT-TIME******************************//

    int meridiem_Flag = 0; // 0=AM 1=PM
    if (t.tm_hour > 12)    // if hours is greter than 12 then convert into 12 hour formet
    {
      t.tm_hour = (t.tm_hour - 12);
      meridiem_Flag = 1; // Flag set to show AM-PM
    }

    if (t.tm_hour == 00) // for night set 24- to 12 hour format e.g. 00:24 -> 12:24
    {
      t.tm_hour = 12;
    }

    ss << t.tm_hour; // pass Hours
    temp = ss.str(); // it returns as string
    CUR_TIME = temp;

    if (stoi(CUR_TIME) < 10) // if hours is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      CUR_TIME = "0" + CUR_TIME;
    }

    ss.str("");
    ss << (t.tm_min);
    temp = ss.str();
    if (stoi(temp) < 10) // if minutes is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      temp = "0" + temp;
    }
    CUR_TIME = CUR_TIME + ":"; // add : to look format appropriate
    CUR_TIME = CUR_TIME + temp;

    ss.str("");

    CUR_TIME += (meridiem_Flag == 0) ? " AM" : " PM"; // AM and PM

    /*******************CURRENT-TIME*********************************/

    //**************** AMS DATABASE PATH GETTING *********************//

    CHAR pathDocument[MAX_PATH];                                                                    // string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathDocument); // getting documents path

    if (result == S_OK) // check if documents path is successfully stored in pathdocuments
    {
      AMS_Path = pathDocument;                             // take original documents path into string
      AMS_Path = AMS_Path + "\\{JSN-1008-JSK-22-10-2021}"; // making AMS folder path
    }
    else
    {
      scrClr();
      setCursorPos(9, 24);
      cout << "DATA BASE-ERROR : 424-500-503 ";
      scrClr(2);
      exit(1);
    }
    /**************** AMS DATABASE PATH GETTING *********************/

    /***************** DESKTOP FOLDER AMS CREATE ********************/
     makeDesktopPath_AMS();
     makeSampleCsv();
    /***************** DESKTOP FOLDER AMS CREATE ********************/
  }

  
  void setCursorPos(int x, int y = 0) //? cursor position set ->IMPORTANT: relative postion is set
  {

    // vertical lines space
    while (x > 0)
    {
      cout << endl;
      x--;
    }

    // horizontal cursor space by 1 charecter
    while (y != 0)
    {
      printf(" ");
      y--;
    }
  }

  void scrClr(float i = 0.0) //?for clearing screen after particular time
  {
    // by default set to zero with default arguements
    sleep(i);      //  going in sleep mode for particular time
    system("cls"); //  clear  the screen
  }

  void startApp() //? start Application
  {
    if (MODULE_CHOICE == 0) //* only 1 time initiaization function need to be called after then just we need to refresh home screen
    {
      initApp(); // init screen first time by opening console in full screen

      if (!dirExists(AMS_Path.c_str())) //? check for availability of DataBase
      {
        scrClr();
        setCursorPos(9, 24);
        cout << "DATA BASE-ERROR : 404-500-503 ";
        scrClr(3);
        exit(1);
      }

      MODULE_CHOICE = HomeScreen(); // home screen will tell which module is selected
    }
    else
    {
      MODULE_CHOICE = HomeScreen(); // home screen will tell which module is selected
    }
  }

  ~APP()
  {
    
  }

private:

  bool makeDesktopPath_AMS()
  {
      TCHAR appData[MAX_PATH];
      if (SUCCEEDED(SHGetFolderPath(NULL,CSIDL_DESKTOPDIRECTORY | CSIDL_FLAG_CREATE,NULL,SHGFP_TYPE_CURRENT,appData)));
      DesktopPath = appData;
      DesktopPath = DesktopPath + "\\" + "AMS";

      if(!dirExists(DesktopPath.c_str()))
      {
          command.clear();
          command="mkdir "+DesktopPath;
          system(command.c_str());
          command.clear();
          return(true);
      }
      else
      {
          return(false);
      }
  }

  void makeSampleCsv()
  {
    tempStorage.clear();
    tempStorage = DesktopPath + "\\Sample.csv";
    if(!dirExists(tempStorage.c_str()))
    {
      writeDataToFile(DesktopPath + "\\Sample.csv" , "Roll Number,Name,Email");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "1,Harshil Ramani,harshilramani9777@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "2,Shubham Khunt,shubhamkhunt1872003@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "3,Drashti Dhola,drashtishola1511@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "4,Fenil Munjani,fenilmunjani82@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "5,Shikhaa Tikiwala,shikhatikiwala@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "6,Viraj Talaviya,virajtalaviya02@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "7,Archit Gevariya,ghevariyaarchit3@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "8,Isha Dadawala,isha.dadawala@gmail.com");
      writeDataToFile(DesktopPath + "\\Sample.csv" , "9,Sanjal Desai,sanjaldesai1234@gmail.com");
    }
    tempStorage.clear();
  }
  
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

    setConsoleSize(); // set full screen console

    system("color F0"); // set white background and text color black
  }

  int HomeScreen() //?ask Module choice at Home screen of APP
  {
    int line;

    gotoHomeScreen:

    Date(1, 15); // current date print
    Time(0, 16); // current time print

    setCursorPos(2);
    cout << setw(57) << " || ATTENDANCE MANAGEMENT SYSTEM ||" << endl; // TITLE OF APP

    string operationChoice;

    // build UI-Box screen of HOME SCREEN
    setCursorPos(1, 17); // set cursor position
    buildVerticalWall(43);

    line = 0;

    while (line < 11)
    {
      setCursorPos(1, 17);
      if (line == 1)
        buildHorizontalWall(43, "1) NEW AMS SETUP ");
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

    setCursorPos(1, 17);
    buildVerticalWall(43);
    
    askChoice(2, 32, operationChoice);

    ConvertChoiceToINT = validateString(operationChoice, 5, 1); // validate and convert choice into integer

    if (!ConvertChoiceToINT) // if wrong input then repeat process until correct input
    {
      goto gotoHomeScreen; // re-ask choice
    }

    return (ConvertChoiceToINT); // return choice
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

    return (size); // return size
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
  
//? **************************  DATA - MEMEBERS ***************************************

protected:

  string CUR_DATE, CUR_TIME; //* CURRENT DATE TIME FOR APPLICATION
  int ConvertChoiceToINT;    //* INTEGER CONVERT VARIABLE FOR INPUT FOR APPLICATION
  string AMS_Path;           //* DATABASE PATH
  string tempStorage;        //* TEMPORARY STORAGE FOR APPLICATION VARIABLE
  string command;            //* COMMAND VARIABLE FOR SYSTEM()
  int cur_month;             //* CURRENT MONTH STORE FOR MONTHLY REPORT
  string pdfName;            //* email attachment name
  string DesktopPath;        //* desktop path for .csv input


  //? ***********************  DATA - MEMEBERS -END ***************************************

  void SetColor(int color) //?for setting individual text color
  {
    WORD wColor;                                      // color specifier
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // create windows handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;                  // We use csbi for the wAttributes word.

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      // Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor); // set console text color
    }
  }

  void buildVerticalWall(int briks) //? for making vertical side
  {
    cout << "*";
    while (briks > 0)
    {
      cout << "-";
      briks--;
    }
    cout << "*";
  }

  void buildHorizontalWall(int endBrick, string tempStorage) //? for making horizontal side
  {
    cout << "|";
    int run = 1;
    while (run < endBrick)
    {

      if (run == (endBrick / 6))
      {
        cout << tempStorage;
        run += (tempStorage.length() - 1);
        cout << " ";
      }
      else
      {
        cout << " ";
      }

      run++;
    }
    cout << "|";
  }

  int dirExists(const char *path) //?checking if directory exists or not 1=EXIST 0=NOT EXIST
  {
    struct stat info;

    if (stat(path, &info) != 0)
      return (0);
    else if (info.st_mode & S_IFDIR)
      return (1);
    else
      return (0);
  }

  void ShowConsoleCursor(bool showFlag) //? hiding or showing cursor
  {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // set handle

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
  }

  void askChoice(int h, int v, string &input) //?general choice taking function  e.g. 1,2,3,4...N
  {
    setCursorPos(h, v);      // set cursor position
    ShowConsoleCursor(true); // show the cursor
    cout << "CHOICE : ";
    fflush(stdin);       // flushing standard input buffer
    getline(cin, input); // taking white space string input
    cin.clear();
    ShowConsoleCursor(false); // hide the cursor
  }

  int YesNoInput(string inputAsk, string &in, string t = "", int color = 0, int color2 = 0) //?take input in yes or no
  {
    int line;
    setCursorPos(2, 17);
    buildVerticalWall(43); // set vertical line on console
    line = 0;
    // build UI-Box screen
    while (line < 3)
    {
      setCursorPos(1, 17);

      if (line == 1)
      {
        if (color == 0 && color2 == 0 && t.empty())
        {
          buildHorizontalWall(43, inputAsk); // message BOX-UI
        }
        else
        {
          cout << "|";
          setCursorPos(0, 7);
          SetColor(color); // set color
          cout << inputAsk;
          SetColor(color2);
          setCursorPos(0, 1);
          cout << t;
          setCursorPos(0, 8);
          cout << "|";
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
    setCursorPos(2, 31);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, in); // take input
    cin.clear();
    ShowConsoleCursor(false);
    line = validateString(in); // validate input // line re used as return value storage

    return (line); // return line
  }

  void InvalidInputErr() //? invalid input error function
  {
    scrClr(0.5); // clear screen
    ShowConsoleCursor(false);
    setCursorPos(8, 26);
    SetColor(4); // set color for text individual
    cout << "INVALID INPUT ENTERTED !" << endl;
    setCursorPos(1, 20);
    cout << "PLEASE RE-ENTER YOUR INPUT CORRECTLY !" << endl;
    ShowConsoleCursor(false);
    scrClr(1);
    SetColor(0); // back to normal color
  }

  void warnMsg(string err_msg, int color, int pos, string err_msg2 = " ", int color2 = 0, int pos2 = 0) //? overloaded version //?medium level Warning
  {
    scrClr();

    if (err_msg2.length() >= 20)
    {
      setCursorPos(8, pos);
      SetColor(color);
      ShowConsoleCursor(false);
      cout << err_msg << endl;
      setCursorPos(1, pos2);
      SetColor(color2);
      cout << err_msg2 << endl;
      scrClr(2); // screen stops so user can read message
      SetColor(0);
    }
    else
    {
      setCursorPos(9, pos);
      SetColor(color);
      ShowConsoleCursor(false);
      cout << err_msg << endl;
      scrClr(2); // screen stops so user can read message
      SetColor(0);
    }
  }

  void MSG(string msg, string msg2, int color, int color2, int pos) //? succeed message print
  {

    scrClr();

    if (msg.length() <= 30) // msg length is less than and equal to 30 print this msg
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
    else // if length is greater than 30 than print this msg
    {
      setCursorPos(8, pos);
      SetColor(color);
      ShowConsoleCursor(false);
      cout << msg; // mess 1 st
      setCursorPos(2, pos + 7);
      SetColor(color2);
      cout << msg2; // mess 2  nd
      scrClr(2);
      SetColor(0);
    }
  }

  int validateString(string input, int Bnd, int start) //? string input validate as integer
  {
    int flag = 0, tem;

    if(start == 0)
      start++;

    for (tem = start; tem <= Bnd; tem++)
    {
      if(to_string(tem) == input) // convert tem int to string to check input valid condition
      {
        flag = 1;
        break;
      }
    }

    if (flag == 0) // IF flag=0 means input is invalid
    {
      InvalidInputErr(); // error msg
      return 0;
    }
    else
    {
      return tem; // returns converted string.to_int(INT)
    }
  }

  int validateString(string input) //?overloaded version of validating string input of yes/no
  {
    if (input == "YES" || input == "yes" || input == "Yes") // check yes input
    {
      return 1; // yes
    }
    else if (input == "NO" || input == "no" || input == "No") // check no input
    {
      return 0; // no
    }
    else
    {
      return -1; // error
    }
  }

  bool specialSyValidations(string &input)
  {
     string list = "#%&{}\\/*><$!:\'\"@+`|=-.,;[]_()^~?";
     int i,j;
     bool flag = false;

     for (i = 0; i < list.length(); i++) // checking special  symbols
     {
       for (j = 0; j < input.length(); j++)
       {
         if (input[j] == list[i])
         { 
           scrClr(0.5);
           setCursorPos(9, 24); // set cursor
           SetColor(4);
           cout << "SPECIAL SYMBOLS ISN'T ALLOWED !" << endl; // warn message
           scrClr(1.5);
           SetColor(0);
           flag = true;
           break;
         }
       }
       if(flag==true)
       break;
     }
     return(flag);
  }

  bool checkAlphaSpInput(string &input, int both = 0) //?function to check occurence of special charaters and alphabets
  {

    string list = "#%&{}\\/*>< $!:\'\"@+`|=-.,;[]_()^~?";
    string list2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    int j = 0, i = 0;
    bool flag = false;

    if (!both) // SELECT IF ONLY ALPHABET validation of both
    {

      for (i = 0; i < list.length(); i++) // checking special  symbols
      {
        for (j = 0; j < input.length(); j++)
        {
          if (input[j] == list[i])
          {
            flag = true;
            break;
          }
        }
      }

      for (i = 0; i < list2.length(); i++) // checking alphabets
      {
        for (j = 0; j < input.length(); j++)
        {
          if (list2[i] == input[j])
          {
            flag = true;
            break;
          }
        }
      }
    }
    else
    {
      for (i = 0; i < list2.length(); i++) // checking alphabets only
      {
        for (j = 0; j < input.length(); j++)
        {
          if (list2[i] == input[j])
          {
            flag = true;
            break;
          }
        }
      }
    }

    return (flag);
  }

  void Date(int v, int h) //? current Date print function
  {
    setCursorPos(v, h); // set cursor position as vertical and horizontal
    cout << "DATE : ";
    SetColor(2); // set color as green
    cout << CUR_DATE;
    SetColor(0); // set color black
  }

  void Time(int v, int h) //? current Time print function
  {
    setCursorPos(v, h); // set cursor position as vertical and horizontal
    cout << "TIME : ";
    SetColor(2); // set color as green
    cout << CUR_TIME;
    SetColor(0); // set color black
  }

  int countLinesOfFile(string FilePath) //? function for counting lines in text file
  {
    string data;                              // store data temp variable
    int lines = 0;                            // to store the lines
    ifstream read(FilePath.c_str(), ios::in); // reading mode file opened
    if (!read.is_open())
    {
      scrClr();
      setCursorPos(9, 28);
      cout << "DATABASE-ERROR : 404 "; // error
      scrClr(2);
      exit(1);
    }
    else
    {
      getline(read, data); // take first line
      while (!read.eof())
      {
        lines++;
        getline(read, data);
      }
      lines++;
      read.close();
    }
    return (lines - 1);
  }

  int checkEmptyFile(string path) //?check empty file
  {
    ifstream read(path.c_str(), ios::binary); // file opened
    if (!read.is_open())
    {
      scrClr();
      setCursorPos(9, 28);
      cout << "DATA BASE-ERROR : 404 ";
      scrClr(2);
      exit(1);
    }
    read.seekg(0, ios::end);
    int sz = read.tellg();
    read.close();
    return sz; // return size of file
  }

  void getDataFromFile(string path, string &input, int lineNo) //?get Data of given path file line in string
  {
    ifstream get(path.c_str(), ios::in); // file opened in reading mode

    if (!get.is_open()) // if file is not opened
    {
      scrClr();
      setCursorPos(9, 28);
      cout << "DATA BASE-ERROR : 404 ";
      scrClr(2);
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

  void writeDataToFile(string path, string write_data) //?write string data to given path file at latest line
  {
    ofstream write(path.c_str(), ios::app); // file opened in append mode

    if (!write.is_open()) // if file is not opened
    {
      scrClr();
      setCursorPos(9, 26);
      cout << "DATA BASE-ERROR : 203-204 ";
      scrClr(2);
      exit(1);
    }
    else
    {
      write << write_data << endl; // write data
    }
    write.close(); // file closed
  }

  void replaceWithHyphen(string &str) //? in given string special symbols should be replaced by hyphen and string will be convert into UPPERCASE
  {
    int i = 0, j = 0;
    string list = "#%&{}\\/*>< $!:\'\"@+`|="; // need to be checked as these are restricated symbols

    for (i = 0; i <= list.length(); i++) // check list condition
    {
      for (j = 0; j <= str.length(); j++) // check str condition
      {
        if (str[j] == list[i]) // if string and list are same
        {
          str[j] = '-'; // replace with hyphen symbol
        }
      }
    }

    transform(str.begin(), str.end(), str.begin(), ::toupper); // convert to uppercase
  }

  bool EmptyInput(string &input) //?checking if input is empty (e.g. : enter key)
  {
    if (input.empty())
    {
      return true; // if emty then returns  true
    }
    else
    {
      return false; // if not then returns false
    }
  }

  bool LengthValidation(string &input, int l) //? input string length validation
  {
    if (input.length() <= l)
    {
      return (true); // if valid then true return
    }
    else
    {
      warnMsg("INPUT LENGTH EXCEED !", 4, 28); // if invalid then return false
      return (false);
    }
  }
  bool LengthValidationCSVEmail(string input, int l) //? input string length validatio
  {

    if (input.length() <= l)
    {
      return (true); // if valid then true return
    }
    else
    {
      return (false);
    }

  }
  bool validateEmail(string email) //?checking for email validation
  {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"); // email pattern
    return regex_match(email, pattern);
  }
  
  void LoadingProcess() //? LOADING WINDOWS WHILE TASK PROCESSING
  {
    tempStorage.clear();
    tempStorage = "WORKING ON IT";
    int i = 1;
    do
    {
      scrClr();
      setCursorPos(9, 28);
      SetColor(2);
      ShowConsoleCursor(false);
      cout << tempStorage;
      scrClr(1);
      tempStorage = tempStorage + ".";
      Beep(1245,200);

      if (process_flag || i == 15)
      {
        break;
      }
      i++;

    } while (true);

    tempStorage.clear();
    SetColor(0);
  }

  bool checkUpperCase(string filename) 
  {
    bool flag=false;
    for(int i=0; i<filename.length() ; i++)
    {
      if(filename[i] >= 'A' && filename[i] <= 'Z')
      {
        flag=true;
        break;
      }
    }
   return(flag);
  }

  void sendToEmail(string SenderAddress, string password, string RecepientAddress, string Subject, string Msg, string AttachmentPath, string fileName) //? sending email to user
  {
    command.clear(); // clear for re-using

    command = AMS_Path + "\\OTHER\\mail.py"; // make database path for email.py

    fstream write(command.c_str(), ios::out); // file opened in writing mode

    if (!write.is_open()) // if file not opened
    {
      scrClr();
      setCursorPos(9, 26);
      cout << "DATA BASE-ERROR : 201-203 "; // error
      scrClr(2);
      exit(1);
    }
    else // CREATE EMAIL PYTHON FILE
    {
      command.clear();

      //* make python code for email

      command = "import smtplib\nfrom email.mime.multipart import MIMEMultipart\nfrom email.mime.text import MIMEText\nfrom email.mime.base import MIMEBase\nfrom email import encoders\n\nfromaddr = \"";
      command = command + SenderAddress + "\"\ntoaddr = \"" + RecepientAddress + "\"\n";
      command = command + "msg = MIMEMultipart()\nmsg['From'] = fromaddr\nmsg['To'] = toaddr\nmsg['Subject'] = \"";
      command = command + Subject + "\"\nbody = \"\"\"" + Msg + "\"\"\"\nmsg.attach(MIMEText(body, 'plain'))\n";
      command = command + "filename = r\"" + AttachmentPath + "\"\n";
      command = command + "attachment = open(filename,\"rb\")" + "\n";
      command = command + "part = MIMEBase('application', 'octet-stream')\npart.set_payload((attachment).read())\nencoders.encode_base64(part)\npart.add_header('Content-Disposition', \"attachment; filename= \%s\" \% \" " + fileName + "\")\nmsg.attach(part)\nserver = smtplib.SMTP('smtp.gmail.com', 587)\nserver.starttls() \n";
      command = command + "server.login(fromaddr, \"" + password + "\")\n";
      command = command + "text = msg.as_string()\nserver.sendmail(fromaddr, toaddr.split(\",\"), text)\nserver.quit()\n";

      write << command; // data write to file
      write.close();    // file closed

      command.clear();
      command = "python " + AMS_Path + "\\OTHER\\mail.py " + "1> " + AMS_Path + "\\OTHER\\output.txt 2>&1";

      system(command.c_str()); //* FILE SENDING TO EMAIL USING PYTHON CODE

      command.clear();
      command = AMS_Path + "\\OTHER\\output.txt";

      int err = checkEmptyFile(command);
      remove(command.c_str()); // delete output/error file

      command.clear();
      command = AMS_Path + "\\OTHER\\mail.py";

      remove(command.c_str());        // delete py file
      remove(AttachmentPath.c_str()); // delete attachment file

      process_flag = true;

      if (err)
        email_flag = false;
      else
        email_flag = true;
    }
  }

  int validateRollNo(string input, int Bnd, int start) //? string input validate as integer
  {
        int flag = 0, tem = 1;
    
        if (start == 0) // roll no is 0
          start++;
        for (tem = start; tem <= Bnd; tem++) // roll no start with 1 and go up to boundry
        {
          if (to_string(tem) == input) // convert tem int to string to check input valid condition
          {
            flag = 1; // if condition true than flag =1
            break;
          }
        }
    
        if (EmptyInput(input) || checkAlphaSpInput(input)) // empty input check
        {
          InvalidInputErr(); // input error
          return 0;
        }
        else if (flag == 0) // IF flag=0 means input is invalid
        {
          MSG(" ROLL NUMBER DOESN'T EXIST !", " ", 4, 0, 23);
          return 0;
        }
        else
        {
          return tem; // returns converted string.to_int(INT)
        }
  }

  string DoubleBackslashPath(string path) //?insering backslash in path for paython file
  {
      int found = path.find("\\", 0); // find backslash
      while (found < path.length())   // check whether the backslash index no. out of range or not
      {
        path.insert(found, "\\");           // insert one backslash
        found = path.find("\\", found + 2); // found backslash again from (found+2)
      }
      return path; // return path
  }

  bool pipilineValidation(string &str)
  {
     size_t pos = str.find("|");
     if (pos != string::npos)
     {
       scrClr(0.5);
       setCursorPos(9, 25); // set cursor
       SetColor(4);
       cout << "PIPLINE('|') ISN'T ALLOWED !" << endl; // warn message
       scrClr(1.5);
       SetColor(0);
       return(true);
     }
     else
     {
     return(false);
     }
  }
  
  bool fileExists(const string &path) //? checking function if file exists or not 
  {   
     bool status_flag = false;
     ifstream read(path.c_str(),ios::binary|ios::in);     // file opened in binary mode 
     if(!read.is_open())
     {
      status_flag=false; // not exists 
     }
     else
     {
       status_flag=true; //exists
     }
     read.close();
     return(status_flag); 
  }

};

//*---------STATIC DEFINATIONS-OF-APP---------------//

int APP::MODULE_CHOICE = 0; //? MODULE CHOICE WILL

//-------------------------------------------------//

/****************************APP-CLASS-END****************************************/

//*****************************************  MODULE-START  ************************************************/
class MODULE_GENERAL : public APP
{

private:
public:
  MODULE_GENERAL()
  {
  }
  ~MODULE_GENERAL()
  {
  }

  bool checkDB() //? functions for checking at least(1) database semster Records exists or not
  {

    if (!checkEmptyFile(AMS_Path + "\\OTHER\\semesterRecord.txt")) // check file size IF=0 -> NO RECORD IF=1 ->RECORD EXITS
    {
      warnMsg("NO SETUP EXISTS! KINDLY ADD ATLEST 1 SETUP", 4, 19); // warn msg
      return (false);
    }
    else
    {
      getSemesterRecordFile();
      ExtractStringFromBuffer();
      return (true);
    }
  }

  void askCourseChoice() //? take input choice of course for attendance
  {
    
    DisplayList_Input(course_name);                   // display list for taking input
    for (auto i = DATA.begin(); i != DATA.end(); ++i) // process to make list of semester in particular course
    {
      if (course_name == get<0>((*i)))
      {
        if (checkDuplicateRecord(LIST, get<1>((*i)))) // cheking if any duplicate records
        {
          LIST.push_back(get<1>((*i))); // making distinguished list
        }
      }
    }
  }

  void askSemsterChoice() //? take input choice of semester for attendance
  {
    
    DisplayList_Input(sem, 1);                        // display list for taking input
    for (auto i = DATA.begin(); i != DATA.end(); ++i) // process to make list of subject in particular course & semester
    {
      if (course_name == get<0>((*i)) && sem == get<1>((*i)))
      {
        if (checkDuplicateRecord(LIST, get<2>((*i))))
        {
          LIST.push_back(get<2>((*i)));
        }
      }
    }
  }

  bool askSubjectChoice() //? take input choice of subject for attendance
  { 
    
    DisplayList_Input(subject_name);
    getFolderPath(); // get folder path into SemPath

    //* below is for checking database scrambling

    if ((!checkEmptyFile(SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt")) || (!checkEmptyFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt")))
    {
      // error part
      warnMsg(course_name + " SEM-" + sem + " " + subject_name, 1, 24, " ERROR CODE: 206-400-412 , PLEASE DELETE & RE-CREATE IT ", 4, 12);
      return false;
    }
    else
    {
      return true;
    }
  }

  bool MailTo(string prompt,int pos)  //? function to ask that you want to send mail to that person also
  {
    ReAskChoice:
    tempStorage.clear();
    scrClr(0.5);
    SetColor(1);
    setCursorPos(6, pos);
    cout << prompt;
    fflush(stdin);
    SetColor(0);

    ConvertChoiceToINT = YesNoInput("   TYPE [Yes/No] AS FOLLOWS ", tempStorage);

    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto ReAskChoice;
    }
    else if (ConvertChoiceToINT == 0)
    {
      return false;
    }
    else
    {
      return true;
    }
    tempStorage.clear();
  }

  int proceedFurther() //? functions for confirming to proceed for attendance
  {
    int line = 0;

   reinputforattendanceTakeOption:

    scrClr(0.5);
    line = 0;

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // making path to access faculty details

    //*BOX-UI FOR Details confirmation

    setCursorPos(1, 7);
    buildVerticalWall(65);

    while (line < 13)
    {
      setCursorPos(1, 7);
      if (line == 1)
      {
        getDataFromFile(command, FacultyName, 1); // get faculty name from file
        buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
      }
      else if (line == 3)
      {
        buildHorizontalWall(65, "COURSE               :  " + course_name);
      }
      else if (line == 5)
      {
        buildHorizontalWall(65, "SEM                  :  " + sem);
      }
      else if (line == 7)
      {
        buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
      }
      else if (line == 9)
      {
        getDataFromFile(command, numberOfstudents, 6); // get the number of students
        buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
      }
      else if (line == 11)
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

    tempStorage.clear(); // clear variable for re-using
    SetColor(1);
    setCursorPos(2, 23);
    cout << "DO YOU WANT TO PROCEED FURTHER ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value
    if (ConvertChoiceToINT == -1)                     // validate input
    {
      InvalidInputErr();
      goto  reinputforattendanceTakeOption;
    }
    return (ConvertChoiceToINT); // return confirmation for taking attendace
  }

  int proceedFurther(int i)   //? confirmation  step
  {
    int line = 0;
    reinputforattendanceTakeOption:
    scrClr(0.5);
    line = 0;
    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt"; // forming path to fetch details from faculty file
    getDataFromFile(command, FacultyEmail, 2);  
                               
    // BOX-UI FOR Details confirmation
    setCursorPos(1, 7);
    buildVerticalWall(65);
    if(i == 1)
    {
      while (line < 13)
      {
        setCursorPos(1, 7);
        if (line == 1)
        {
          getDataFromFile(command, FacultyName, 1); 
          buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
        }
        else if (line == 3)
        {
          buildHorizontalWall(65, "EMAIL                :  " + FacultyEmail);
        }
        else if (line == 5)
        {
          buildHorizontalWall(65, "COURSE               :  " + course_name);
        }
        else if (line == 7)
        {
          buildHorizontalWall(65, "SEM                  :  " + sem);
        }
        else if (line == 9)
        {
            buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
        }
        else if (line == 11)
        {
          getDataFromFile(command, numberOfstudents, 6); 
          buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
        }
        else
          buildHorizontalWall(65, " ");
        line++;
      }
    }
    else
    {
        while (line < 11)
        {
          setCursorPos(1, 7);
          if (line == 1)
          {
            getDataFromFile(command, FacultyName, 1); 
            buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
          }
          else if (line == 3)
          {
            buildHorizontalWall(65, "COURSE               :  " + course_name);
          }
          else if (line == 5)
          {
            buildHorizontalWall(65, "SEM                  :  " + sem);
          }
          else if (line == 7)
          {
            buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
          }
          else if (line == 9)
          {
              getDataFromFile(command, numberOfstudents, 6); 
              buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
          }
          else
            buildHorizontalWall(65, " ");
          line++;
        }

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
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); // input validated using the function
    if (ConvertChoiceToINT == -1) 
    {
      InvalidInputErr();
      goto reinputforattendanceTakeOption;
    }
    return (ConvertChoiceToINT); // return confirmation
  }



protected:
  virtual void SetNoObj() = 0; //* THIS CLASS IS SET PURE VIRTUAL SO, OBJECT OF THIS CLASS WON'T BE CREATED IN MAIN()

  //********** MODULE_GENERAL *************/

  string SemPath;

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

  //*********** USER-HOD ***************/  

  string HodEmail;
  string department_name;
  string joining_year;

  /********************************/

  //********MODULE-2-3************/

  vector<string> buffer, LIST;                        // vector buffer for file handling data receiver  LIST FOR STORE LIST CONTENT
  vector<tuple<string, string, string, string>> DATA; // search-key-value-access vector-tuple
  string date;
  string time;

  /*******************************/

  //*************************  MODULE 2-3 **********************************//

  void reportSentSuccessfully(string pdf_name, string stud_email = "")   //? function to give message for successfully email sending
  {
       scrClr(0.5);
       setCursorPos(7, 18);
       SetColor(2);
       cout << pdf_name;
       setCursorPos(2, 21);
       SetColor(0);
       cout << "REPORT HAS BEEN SENT SUCCESSFULLY TO :";
       setCursorPos(2, 24);
       SetColor(1);
       cout << FacultyEmail;
       if (!stud_email.empty())
       {
         cout << " & ";
         setCursorPos(2, 24);
         SetColor(1);
         cout << stud_email;
       }
       scrClr(3);
       SetColor(0);
       process_flag = false;
       email_flag = false;
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

  void DisplayList_Input(string &put, int select = 0) //? display the list and take appropriate input of corse/sem/subject
  {
    scrClr();
    int listFlag = 1, chFlag = 0, countFlag = 0, temp_flag = 1;
    auto i = LIST.begin();

    //(LIST.size() > 6) ? setCursorPos(1, 20) : setCursorPos(1, 20); // set box-view for list >5 and less than 5
    setCursorPos(1,20);
    buildVerticalWall(35);
    setCursorPos(1,20);
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
        askChoice(2, 34, tempStorage); // ask choice
        scrClr(0.5);
        if (tempStorage == "+") // if user press +
        {
          setCursorPos(2, 20);
          buildVerticalWall(35);
          listFlag = 1; // list flag =1
          chFlag = 0;
          setCursorPos(1, 20);
          buildHorizontalWall(35, " ");
          goto displayAgain; // again display screen
        }
        else
        {
          ConvertChoiceToINT = validateString(tempStorage, countFlag * 5, (countFlag - 1) * 5); // validatestring

          if (ConvertChoiceToINT == 0)
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

    if (chFlag == 0)
    {
      setCursorPos(1, 20);
      buildVerticalWall(35);
      askChoice(2, 30, tempStorage);

      if (tempStorage == "+")
      {
        InvalidInputErr();
        while (temp_flag != (listFlag))
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

      if (ConvertChoiceToINT == 0)
      {
        while (temp_flag != (listFlag))
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
    for (i = LIST.begin(), countFlag = 1; i != LIST.end(); ++i, countFlag++) // set data to string for searching
    {
      if (countFlag == ConvertChoiceToINT)
      {
        put = (*i);
      }
    }

    LIST.clear();        // flush vector data for re-using
    tempStorage.clear(); // flush string for re-using
    scrClr();
  }

  void getFolderPath() //? based on input choice of course->sem-subject we find correct folder and save path  to Sem_path
  {
    for (auto i = DATA.begin(); i != DATA.end(); ++i) // process to find folder path using vector tuple we have 3 input parameter coursename , sem , subject name
    {

      if (course_name == get<0>((*i)))
        if (sem == get<1>((*i)))
          if (subject_name == get<2>((*i)))
            SemPath = get<3>((*i));
    }

    SemPath = AMS_Path + "\\" + SemPath; //* assigning searched path to SemPath and concate AMS_Path
  }

  void getSemesterRecordFile() //? get data of course-semester-sub-path records
  {
    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; // making path to AMS->OTHER->semsterRecord.txt
    fstream fin(tempStorage.c_str(), ios::in);              // file opened

    if (!fin.is_open()) // if not opened
    {
      scrClr();
      setCursorPos(9, 28);
      cout << "DATA BASE-ERROR : 404 ";
      scrClr(2);
      exit(1);
    }
    else // if opened
    {
      tempStorage.clear();       // clear for re-using
      getline(fin, tempStorage); // tempStorage used as temporary storage

      while (!fin.eof()) // data receive until file ends
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
    for (auto i = buffer.begin(); i != buffer.end(); ++i) // insert in to vector-tuple from vector buffer with extracting string
    {
      tempStorage = (*i);      // temp variable for moving vector tempStorage to string
      int found_pos, temp_pos; // temp variable for position storing

      found_pos = tempStorage.find("|");                // find the first occurance of '|'
      course_name = tempStorage.substr(0, (found_pos)); // get proper course name from string and save it to course_name
      temp_pos = (found_pos + 1);                       // making next finding position

      if (checkDuplicateRecord(LIST, course_name)) // checking if any duplicate course exists
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
  
  int studConfirmation() //? student confirmation  function (also available in general module as virtual)
  {
    tempStorage.clear();
    int line;
    reAsk:
    scrClr(0.5);
    line = 0;
    setCursorPos(2, 7);
    buildVerticalWall(65);
    while (line < 7)
    {
      setCursorPos(1, 7);
      if (line == 1)
      {
        buildHorizontalWall(65, "STUDENT ROLL NUMBER   :  " + RoLLNo);
      }
      else if (line == 3)
      {
        buildHorizontalWall(65, "STUDENT NAME          :  " + student_name);
      }
      else if (line == 5)
      {
        buildHorizontalWall(65, "STUDENT EMAIL         :  " + student_email);
      }
      else
        buildHorizontalWall(65, " ");
      line++;
    }
    setCursorPos(1, 7);
    buildVerticalWall(65);
    SetColor(1);
    setCursorPos(3, 23);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value storage
    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reAsk;
    }
    else if (ConvertChoiceToINT)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }

  int studConfirmation(int argc) //? overloaded version basic confirmation message for user
  {
    int line;
    reConfirm:
    scrClr(0.5);
    // BOX-UI FOR STUDENT INFO CONFIRM
    setCursorPos(5, 15);
    cout << "STUDENT ROLL NUMBER " << right << setw(4) << ": " << RoLLNo;
    setCursorPos(1, 15);
    cout << "STUDENT NAME " << right << setw(11) << ": " << student_name;
    setCursorPos(1, 15);
    if (student_email.length() <= 35)
    {
      cout << "STUDENT E-MAIL " << right << setw(9) << ": " << student_email;
    }
    else
    {
      int l = 0;
      cout << "STUDENT E-MAIL " << right << setw(9) << ": ";
      while (l < student_email.length())
      {
        if (l == 35)
        {
          setCursorPos(1, 39);
        }
        cout << student_email[l];
        l++;
      }
    }
    ConvertChoiceToINT = YesNoInput("CONFIRM THESE DETAILS (Yes/No) ", tempStorage); // taking input yes/no
    if (ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); // error message
      goto reConfirm;
    }
    return (ConvertChoiceToINT); // returns confirmation value yes=1 / no=0
  }

  bool RollNoInput() //? take roll number input
  {
    rollNoReInput:
    scrClr(0.5);
    RoLLNo.clear();
    setCursorPos(9, 22);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "ENTER ROLL NUMBER OF STUDENT : ";
    getline(cin, RoLLNo);
    cin.clear(); // clear bad input flag
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateRollNo(RoLLNo, stoi(numberOfstudents), 1); // validate roll number
    if (!ConvertChoiceToINT)
    {
      goto rollNoReInput;
    }
    getStudentData(); // get data of that student
    return (true);
  }

  void getStudentData() //? get student data of that particular roll number
  {
    command.clear();
    tempStorage.clear();
    int found_pos, temp_pos;
    command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt"; // path for access student data file
    getDataFromFile(command, tempStorage, stoi(RoLLNo));
    found_pos = tempStorage.find("|");
    temp_pos = (found_pos + 1);
    found_pos = tempStorage.find("|", temp_pos);
    student_name = tempStorage.substr(temp_pos, (found_pos - temp_pos));
    temp_pos = (found_pos + 1);
    found_pos = tempStorage.find("|", temp_pos);
    student_email = tempStorage.substr(temp_pos);
  }
  
  void UpdateName(string &input,string display) //?Faculty & student name update input
  {

    reinput:
    scrClr(0.5);
    setCursorPos(9, 15);
    cout << display + "  :  ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, input);
    cin.clear();
    ShowConsoleCursor(false);
    if (!LengthValidation(input, 27))
    {
      goto reinput; // re-ask student name as length exceed
    }
    if (EmptyInput(input)) // if input is empty than error
    {
      InvalidInputErr(); // input error
      goto reinput;      // re-ask student name
    }
    if(pipilineValidation(input))
    {
      goto reinput; 
    }
  }

  void UpdateEmail(string &input,string display) //?Faculty & student email address update & input
  {
    reinputOfEmail:
    scrClr(0.5);
    setCursorPos(9, 14);
    cout << display + " : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, input);
    cin.clear();
    ShowConsoleCursor(false);
    transform(input.begin(), input.end(), input.begin(), ::tolower); // convert to uppercase
    if (!LengthValidation(input, 58)) // check email input length
    {
      goto reinputOfEmail; // re-ask student email as length exceed
    }
    if (EmptyInput(input)) // EmptyInput VALIDATION
    {
      InvalidInputErr(); // input error
      goto reinputOfEmail;
    }
    else if (!validateEmail(input)) // email validation
    {
      warnMsg("INVALID E-MAIL ADDRESS !", 4, 26); // warn msg
      goto reinputOfEmail;                        // re-ask email
    }
    scrClr(0.5); //! EOP() seek.review(*required) we can remove it : ALL AMS TEAM
  }


  /***********************************************************************************************/
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
  bool notRegularCSV(string filename)
  {
     return(false); //!HR:EDIT* required in Version 2
  }
  bool createSemester() //? return 1=semester created successfully & return 0=not created
  {

    tempStorage = course_name;
    replaceWithHyphen(tempStorage); // replace with hyphen an make capital letter string

    SemPath = AMS_Path + "\\" + tempStorage + "-SEM-" + sem; // making semesterpath with coursename

    tempStorage = subject_name;
    replaceWithHyphen(tempStorage); // make subject hyphen and uppercase

    SemPath = SemPath + "-" + tempStorage; // proper subject folder create

    if (!dirExists(SemPath.c_str())) // if directory not exists then create it
    {

      return (true); // semester no exists so create it                             

      /***************************************************************************************/
    }
    else //* if that semester already exist
    {
      warnMsg("SEMSTER WITH THAT SUBJECT ALREADY EXIST !", 2, 19);
      return (false); // returns 0=failed as User trying to create that same folder again
    }
  }
  
  //*----------------FACULTY DETAILS CONFIRMATION AND MODIFICATION---------------------/

  int confirmation() //?basic confirmation message for user(faculty details)
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

    ConvertChoiceToINT = YesNoInput("CONFIRM THESE DETAILS (Yes/No) ", tempStorage); // taking input yes/no

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

    // BOX-UI OF modification information
    setCursorPos(1, 25);
    buildVerticalWall(27);

    while (line < 13)
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

  

  int InfoStudModification() //? MODIFICATIONS OF STUDENTS DETAILS
  {

    int line;
    reInputOfmod:

    line = 0;
    setCursorPos(3);
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;

    // BOX-UI FOR MODIFICATION INFORMATION OF STUDENTS
    setCursorPos(2, 25);
    buildVerticalWall(23);

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

    askChoice(3, 32, tempStorage); // ask choice

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

  /***********************************************************************************/


  void EnterCourseName() //?course name input
   {
      reinputOfcourseName:
      scrClr(0.5);
      setCursorPos(9, 26);
      cout << "ENTER COURSE NAME : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin, course_name);
      cin.clear();
      ShowConsoleCursor(false);

      if (!LengthValidation(course_name, 27))
      {
        goto reinputOfcourseName; // re-ask course_name as length exceed
      }
      if (EmptyInput(course_name)) // check course_name is empty or not
      {
        InvalidInputErr();        // invalid input error
        goto reinputOfcourseName; // re-ask course_name
      }
      if(pipilineValidation(course_name))
      {
        goto reinputOfcourseName; 
      }
      if(specialSyValidations(course_name))
      {
        goto reinputOfcourseName; 
      }
      if(!checkAlphaSpInput(course_name))
      {
        scrClr(0.5);
        setCursorPos(9, 16); // set cursor
        SetColor(4);
        cout << "COURSE NAME SHOULD CONTAIN ATLEAST ONE ALPHABET !" << endl; // warn message
        scrClr(2);
        SetColor(0);
        goto reinputOfcourseName; 
      }

      scrClr(0.5); //! EOP() seek.review(*required) we can remove it :ALL AMS TEAM
   }

  void EnterSem() //?input of semester
  {
    reinputOfsem:
    scrClr(0.5);
    fflush(stdin);
    setCursorPos(9, 26);
    cout << "ENTER SEMESTER : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, sem);
    cin.clear();
    ShowConsoleCursor(false);

    if (!validateString(sem, 15, 1)) // validate sem input
    {
      goto reinputOfsem; // re-ask sem
    }
  }
  
  void EnterSubject() //?input subject
  {
      reinputOfsubjectName:
      scrClr(0.5);
      setCursorPos(9, 26);
      cout << "ENTER SUBJECT : ";
      ShowConsoleCursor(true);
      fflush(stdin);
      getline(cin, subject_name);
      cin.clear();
      ShowConsoleCursor(false);
      if (!LengthValidation(subject_name, 27))
      {
        goto reinputOfsubjectName; // re-ask subject name as length exceed
      }
      if (EmptyInput(subject_name)) // check subject name is empty or not
      {
        InvalidInputErr();         // invalid input error
        goto reinputOfsubjectName; // re-ask subject name
      }
      if(pipilineValidation(subject_name))
      {
        goto reinputOfsubjectName; 
      }
      if(specialSyValidations(subject_name))
      {
        goto reinputOfsubjectName; 
      }
  
  }

  void rollNo(int RollNo) //?show Roll Number
  {
    scrClr(0.5);
    ShowConsoleCursor(false);
    setCursorPos(9, 27);
    cout << " ROLL NUMBER : " << RollNo;
    scrClr(1); // user can read no. FOR 1 SECOND
  }

  void askNumberOfStudents() //?asking number of students
  {
    reAskNumStud:
    scrClr(0.5);
    setCursorPos(7, 23);
    cout << " HOW MANY STUDENTS DO YOU HAVE ? ";
    setCursorPos(4, 27);
    cout << "NUMBER OF STUDENT : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, numberOfstudents);
    cin.clear();
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(numberOfstudents, 5000, 1); // validate number of students input
    if (ConvertChoiceToINT == 0)
    {
      goto reAskNumStud; // take reinput of number of students
    }
  }

  bool preReqCSV()  //? to show pre-requirements to take records from .CSV file
  {
    int line = 0;
    confirm:
    scrClr(0.5);
    line = 0;
    //BOX-UI FOR CSV requirement
    setCursorPos(1);
    buildVerticalWall(78);
    while (line < 14)
    {
      setCursorPos(1);
      if (line == 0)
      {
        cout << "|";
        SetColor(1);
        cout<<"                       PRE-REQUIREMENT OF .CSV FILE";
        SetColor(0);
        cout << setw(28) << "|";
      }
      else if (line == 2)
      {
        cout << "|";
        cout<<"    1) .CSV FILE SHOULD BE IN DESKTOP->AMS FOLDER";
        SetColor(2);
        cout<<" (SWITCH TABS : \"ALT+TAB\")";
        SetColor(0);
        cout << setw(4) << "|";
      }
      else if (line == 4)
      { 
        cout << "|";
        cout<<"    2) .CSV FILE SHOULD HAVE ONLY TWO COLUMNS NAME & EMAIL OF STUDENT ";
        cout << setw(9) << "|";
      }
      else if (line == 6)
      { 
        cout << "|";
        cout<<"    3) NAME & EMAIL COLUMNS SHOULD NOT CONTAIN ANY EMPTY CELL ";
        cout << setw(17) << "|";
      }
      else if (line == 8)
      {  
        cout << "|";
        cout<<"    4) .CSV FILE NAME SHOULD BE IN LOWER-CASE ONLY ";
        cout << setw(28) << "|";
      }
      else if (line == 10)
      {  
        cout << "|";
        cout<<"    5) COLUMNS MUST HAVE TITLE IN FIRST ROW LIKE NAME & EMAIL ";
        cout << setw(17) << "|";
      }
      else if(line == 12)
      {
        cout << "|";
        cout<<"    6) .CSV FILE MUST BE IN \"CSV(COMMA DELIMITED)\" FORMAT !";
        SetColor(4);
        cout<<" (NOT UTF-8/OTHER)";
        SetColor(0);
        cout << setw(2) << "|";
      }    
      else
        buildHorizontalWall(78, " ");
      line++;
    }
    setCursorPos(1);
    buildVerticalWall(78);
    tempStorage.clear(); // clear variable for re-using
    SetColor(1);
    setCursorPos(1, 23);
    cout << "DO YOU WANT TO PROCEED FURTHER ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value
    if (ConvertChoiceToINT == -1)                     // validate input
    {
      InvalidInputErr();
      goto confirm;
    }
    
    if(ConvertChoiceToINT)
    {  
      return (true);
    } 
    else
    { 
      return (false);
    }
  }

  bool pipilineValidation2(string &str)  //? to check pipeline presence in any input string
  {
     size_t pos = str.find("|");
     if (pos != string::npos)
     {
       return(true); //if found
     }
     else
     {
     return(false); //if not found
     }
  }

  short int readDataFromCSV(string filePath,unsigned int max_row,vector<string> &data)  //? function to take records from .CSV file
  {
    //student_name used as temp 1
    //student_email used as temp 2
    //unsigned int count = 0;

    tempStorage.clear();
    unsigned int roll_no = 0; //local variable

    short int csv_read_code = 1; //by default data is okay
  
    while(roll_no < max_row)
    {   
        tempStorage.clear();
        student_name.clear();
        student_email.clear();
        getDataFromFile(filePath,tempStorage,roll_no+1);
        if(roll_no ==0 )
        RoLLNo = to_string(1);
        else
        RoLLNo = to_string(roll_no+1);    
        
        //* code 1 is for complete error free  code
        if(std::count(tempStorage.begin(), tempStorage.end(), ',')>1)
        {
          csv_read_code=2; // 2 Means more than two columns
          break;
        }
        if(roll_no==0 && (tempStorage!="name,email"&&tempStorage!="Name,Email"&&tempStorage!="NAME,EMAIL"&&tempStorage!="name,Email"&&tempStorage!="Name,email"&&tempStorage!="NAME,email"&&tempStorage!="name,EMAIL"&&tempStorage!="NAME,Email"))
        {
          csv_read_code=5; // 5 Means First ROW: name and email title are missing
          break;
        }
        if(tempStorage[0]==','||tempStorage[ (tempStorage.length()-1) ]==','||EmptyInput(tempStorage)) 
        {
           csv_read_code=3; // 3 Means empty cell
           break;
        }
        if( ( roll_no != 0 )&& ( (!validateEmail(tempStorage.substr( (tempStorage.find(",") + 1 ) )) )|| ( !LengthValidationCSVEmail(tempStorage.substr( (tempStorage.find(",") + 1 ) ),58)) )  )
        {
          csv_read_code=4; // 4 Means email not valid
          break;
        }
        if(pipilineValidation2(tempStorage))
        {
          csv_read_code=6; // 6 Means Pipline contain cell
          break;
        }

        
        if(roll_no != 0)
        {  
          string temp;
          replace( tempStorage.begin(), tempStorage.end(), ',', '|'); // replace all 'x' to 'y'
          temp = to_string(roll_no) ;
          student_name = tempStorage.substr(0,(tempStorage.find("|")));
          student_email = tempStorage.substr((tempStorage.find("|")+1));
          tempStorage.clear();
          transform(student_email.begin(), student_email.end(), student_email.begin(), ::tolower); // convert to uppercase
          tempStorage = temp + "|" + student_name + "|" + student_email;
          data.push_back(tempStorage);
          temp.clear();
        }
        roll_no++;
    }
   tempStorage.clear();
   return(csv_read_code);
  }
   
  void askStudDetails() //? asking students details manual version
  {

    int ROLLNO = 0;
    while (ROLLNO < stoi(numberOfstudents)) // functions for taking student data input roll no wise
    {
      ROLLNO++;

      rollNo(ROLLNO);             // for take input of roll no
      UpdateName(student_name,"ENTER STUDENT NAME");   // for take input of student name
      UpdateEmail(student_email,"ENTER STUDENT E-MAIL"); // for taking input of email

      confirmAgain:                 // final confirmation

      RoLLNo = to_string(ROLLNO); // convert ROLLNO integer to string

      if (studConfirmation()) // basic confirmation dialog if yes then semester folder create
      {
        tempStorage.clear();
        RoLLNo = to_string(ROLLNO);                                      // rollNo Int to string
        tempStorage = RoLLNo + "|" + student_name + "|" + student_email; // folder name
                                                                         // writeDataToFile(command, tempStorage);                                      // writing data to files
        LIST.push_back(tempStorage);
      }
      else
      {
        scrClr(0.5); // clear screen so flickring won't happen

        switch (InfoStudModification()) // which details do you want to update that function returns
        {
        case 1:
        {
          UpdateName(student_name,"ENTER STUDENT NAME"); // student name modification
          break;
        }
        case 2:
        {
          UpdateEmail(student_email,"ENTER STUDENT E-MAIL"); // student email modification
          break;
        }
        case 3:
        {
          scrClr(0.5);
          break;
        }
        }
        goto confirmAgain; // ask user to final confirmation
      }
    }
  }

  void EnterFileCSVName(string &filename) //?input subject
  {
     reinput_f_name:
      scrClr(0.5);
      setCursorPos(9,22);
      cout << "ENTER .CSV FILE NAME : ";
      ShowConsoleCursor(true);
      fflush(stdin);
      getline(cin, filename);
      cin.clear();
      ShowConsoleCursor(false);
      if (!LengthValidation(filename, 256))
      {
        goto reinput_f_name; 
      }
      if (EmptyInput(filename)) 
      {
        InvalidInputErr();         // invalid input error
        goto reinput_f_name; 
      }
      if(pipilineValidation(filename))
      {
        goto reinput_f_name; 
      }
      if(filename.substr((filename.length()-4))!=".csv"&&filename.substr((filename.length()-4))!=".CSV"||notRegularCSV(filename))
      { 
        scrClr(0.5);
        setCursorPos(9, 15); // set cursor
        SetColor(4);
        cout << ".CSV(COMMA DELIMITED) FILE FORMAT IS ONLY ALLOWED !" << endl; // warn message
        scrClr(2);
        SetColor(0);
        goto reinput_f_name; 
      }
      if(checkUpperCase(filename))
      {
        scrClr(0.5);
        setCursorPos(9,22); // set cursor
        SetColor(4);
        cout << "FILE NAME CONTAINS UPPER CASE LETTER !" << endl; // warn message
        scrClr(2);
        SetColor(0);
        goto reinput_f_name; 
      }
  
  }

  bool askStudDetailsInCSV() //? asking students details csv version
  {
    bool opRead=false; // reverse flag
    
    LIST.clear(); // clear list  on every wrong

    if(preReqCSV())
    { 
      string fileName; //file Name to .CSV file
      EnterFileCSVName(fileName);
      
      if(fileExists(DesktopPath+"\\"+fileName)) //pre requirement 1 check
      {
        switch(readDataFromCSV(DesktopPath+"\\"+fileName,(stoi(numberOfstudents)+1),LIST))
        {
          case 1:{opRead=true;break;}
          case 2:
          { warnMsg("ERROR : .CSV FILE HAS MORE THAN TWO COLUMNS !", 4,19,fileName + " => ROW NUMBER : "+RoLLNo,1,22);
            opRead=false;
            break;
          }
          case 3:
          { warnMsg("ERROR : .CSV FILE NAME/EMAIL COLUMN HAS EMPTY CELL !", 4, 14, fileName + " => ROW NUMBER : "+RoLLNo,1,22);
            opRead=false;
            break;
          }
          case 4:
          { warnMsg("ERROR : .CSV FILE HAS INVALID STUDENT EMAIL ADDRESS !", 4, 14, fileName + " => ROW NUMBER : "+RoLLNo,1,22);
            opRead=false;
            break;
          }
          case 5:
          {    
              scrClr();
              setCursorPos(7,14);
              SetColor(4);
              ShowConsoleCursor(false);
              cout <<" ERROR : .CSV FILE HAS NO TITLE COLUMNS NAME / EMAIL !" << endl;
              SetColor(4);
              setCursorPos(1,10);
              SetColor(4);
              cout <<" ERROR : INCOMPATIBLE .CSV FILE ENCODING FORMAT(UTF-8/OTHER) ! "<< endl;
              setCursorPos(1,22);
              SetColor(1);
              cout << fileName + " => ROW NUMBER : "+RoLLNo << endl;
              scrClr(3); // screen stops so user can read message
              SetColor(0);
              opRead=false;
              break;

          }
          
          case 6:
          { 
            warnMsg("ERROR : .CSV FILE CELL DATA HAS PIPLINE ('|') WHICH IS NOT ALLOWED !", 4, 6, fileName + " => ROW NUMBER : "+RoLLNo,1,22);
            opRead=false;
            break;
          }
          

        }
        
      }
      else
      {
        scrClr(0.5);
        setCursorPos(9,19); // set cursor
        SetColor(4);
        cout << ".CSV FILE NOT FOUND IN DESKTOP->AMS FOLDER !" << endl; // warn message
        scrClr(2);
        SetColor(0);
      }
    }
  

   return(opRead); 
  }

  int askDataInputChoice() // Ask Data Input Choice
  {
     int line = 0;
     reask_report:
     
     // BOX-UI FOR INPUT CHOICE
     scrClr(0.5);
     setCursorPos(3,14);
     cout << " BY WHICH METHOD DO YOU WANT TO INPUT STUDENT DATA ? " << endl;
     setCursorPos(2,23);
     buildVerticalWall(30);
     line = 0;
     while (line < 5)
     {
       setCursorPos(1, 23);
       if (line == 1)
       {
         buildHorizontalWall(30, "1) MANUAL INPUT ");
       }
       else if (line == 3)
       {
         buildHorizontalWall(30, "2) CSV FILE INPUT ");
       }
       else
         buildHorizontalWall(30, " ");
       line++;
     }
     setCursorPos(1, 23);
     buildVerticalWall(30);
     askChoice(3, 33, tempStorage);
     ConvertChoiceToINT = validateString(tempStorage, 2, 1);
     if (ConvertChoiceToINT == 0)
     {
       goto reask_report;
     }
     
     return(ConvertChoiceToINT);
   }

public:

  MODULE_1()
  {
    buffer.clear();
    LIST.clear();
    command.clear();     // command clear for re-use
    tempStorage.clear(); // tempStorage clear for re-use
  }

  ~MODULE_1()
  {
    buffer.clear();
    LIST.clear();
    command.clear();
    tempStorage.clear();
  }

  void askFacDetails() //?asking faculty details
  {

  reAskFacDet:

    EnterCourseName(); // course name input
    EnterSem();        // sem input
    EnterSubject();    // subject input

    askNumberOfStudents(); // number of students INPUT

    command = AMS_Path + "\\USER-INFO\\userdetails.txt"; // making path for getting data from file

    getDataFromFile(command, FacultyName, 1);  // taking faculty name  from file
    getDataFromFile(command, FacultyEmail, 2); // taking  faculty email  from file

  confirmAgain:

    if (confirmation()) // basic confirmation dialog if yes then semester folder create
    {
      
      if(!createSemester()) // semester confirmation
      {
        goto reAskFacDet; // reasking faculty details as semester already exists
      }
      // pushing data into the buffer

      buffer.push_back(FacultyName);
      buffer.push_back(FacultyEmail);
      buffer.push_back(course_name);
      buffer.push_back(sem);
      buffer.push_back(subject_name);
      buffer.push_back(numberOfstudents);

    }
    else
    {
      scrClr(0.5); // clear screen so flickring won't happen

      switch (InfoModification()) // which details do you want to update that function returns
      {                           // each function is called according to requirement
      case 1:
      {
        UpdateName(FacultyName,"ENTER FACULTY NAME"); // update faculty Name
        break;
      }
      case 2:
      {
        UpdateEmail(FacultyEmail,"ENTER FACULTY E-MAIL"); // update faculty email
        break;
      }
      case 3:
      {
        EnterCourseName(); // course Name
        break;
      }
      case 4:
      {
        EnterSem(); // semester
        break;
      }
      case 5:
      {
        EnterSubject(); // subject
        break;
      }
      case 6:
      {
        askNumberOfStudents(); // total number of students
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

  void getDataInputOfstudent()
  {  
    reask:
    scrClr();
    if(askDataInputChoice()==1)
    {
      askStudDetails();
    }
    else
    {
      bool repeat_flag = askStudDetailsInCSV();
      if(!repeat_flag)
      {
        goto reask;
      }
    }
  }

  void SetUpSucceed() // module 1 successfully worked
  {
    command.clear();

    command = "mkdir " + SemPath; // making commad which will pass in cmd

    system(command.c_str()); // creating  directory by CMD

    //*********************  FOLDERS ***********************************************/

    command = "mkdir " + SemPath + "\\DAILY-RECORD"; // making COMMAND FOR DAILY_RECORD folder

    system(command.c_str()); // creating DAILY_RECORD directory by CMD

    command = "mkdir " + SemPath + "\\FAC-STUD-DETAILS"; // making COMMAND FOR FAC&STUD_DETAILS folder

    system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD

    command = "mkdir " + SemPath + "\\REPORTS"; // making COMMAND FOR MONTHLY_REPORTS folder

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

    command = command + tempStorage; // command for making path for writting data to file

    tempStorage.clear();

    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; //* it will keep record of each semester that is created like all data of faculty | folderName

    writeDataToFile(tempStorage, command); //*writting data to file

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; // path making for writing into file

    for (auto i = LIST.begin(); i != LIST.end(); i++) // at last we are writing student data to database file
    {
      writeDataToFile(command, (*i));
    }

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; // path making for writting into file

    for (auto i = buffer.begin(); i != buffer.end(); i++) // at last we are writing faculty data to database file
    {
      writeDataToFile(command, (*i));
    }

    tempStorage = course_name + " SEM " + sem + " " + subject_name;
    MSG(tempStorage, " SET UP SUCCESSFUL ", 2, 0, 20); // succeed msg
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
  bool month_report_flag;
  int file_month;

public:
  static int AT_OPTION_CHOICE; // attendance taking option select

protected:
  //*********************************************************************************/

  //******************************** MEMBER-FUNCTIONS *********************************/

private:
  void makeMonthReport()  //? function to make file to generate report
  {
    buffer.clear();
    LIST.clear();
    DATA.clear();

    tempStorage.clear();

    string temp, attendance;

    command.clear();
    command = SemPath + "\\REPORTS\\fac_data.txt";
    tempStorage = "1) FACULTY NAME : " + FacultyName;
    writeDataToFile(command, tempStorage);

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt";
    getDataFromFile(command, FacultyEmail, 2);

    command.clear();
    command = SemPath + "\\REPORTS\\fac_data.txt";
    tempStorage = "2) FACULTY EMAIL : " + FacultyEmail;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "3) COURSE NAME  : " + course_name;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "4) SEMSTER : " + sem;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "5) SUBJECT NAME : " + subject_name;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "-: [ Attendance Data ] :- ";
    writeDataToFile(command, tempStorage);

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";
    int j = 1, found_pos, temp_pos, line = countLinesOfFile(command);

    while (j <= line)
    {
      tempStorage.clear();
      found_pos = temp_pos = 0;

      command.clear();
      command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";
      getDataFromFile(command, tempStorage, j);

      found_pos = tempStorage.find("|");
      student_name.clear();
      student_name = tempStorage.substr((found_pos + 1), (tempStorage.find("|", (found_pos + 1)) - (found_pos + 1))); // time re used as student name

      command.clear();
      command = SemPath + "\\REPORTS\\stud_name.txt";
      writeDataToFile(command, student_name);
      j++;
    }

    tempStorage.clear();
    j = 1;
    command = SemPath + "\\DAILY-RECORD\\records.txt"; // path stored in command var
    line = countLinesOfFile(command);
    while (j <= line)
    {
      tempStorage.clear();
      getDataFromFile(command, tempStorage, j);
      buffer.push_back(tempStorage);
      j++;
    }

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
    {
      tempStorage.clear();
      tempStorage = (*i);
      found_pos = tempStorage.find("|");

      date = tempStorage.substr(0, found_pos);
      temp_pos = (found_pos + 1);
      found_pos = tempStorage.find("|", temp_pos);
      time = tempStorage.substr(temp_pos, (found_pos - temp_pos));
      temp_pos = (found_pos + 1);
      found_pos = tempStorage.find("|", temp_pos);
      attendance = tempStorage.substr(temp_pos);
      DATA.push_back(make_tuple(date, time, attendance, ""));
    }

    auto i = DATA.begin();
    auto x = buffer.begin();
    for (; i != DATA.end() && x != buffer.end(); ++i, ++x)
    {
      tempStorage.clear();
      tempStorage = get<0>((*i));
      date.clear();

      date = tempStorage.substr(3, 2);

      if (!date.empty())
      {
      
       if (date == "01")
       {
         date = "1";
       }
       else if (date == "02")
       {
         date = "2";
       }
       else if (date == "03")
       {
         date = "3";
       }
       else if (date == "04")
       {
         date = "4";
       }
       else if (date == "05")
       {
         date = "5";
       }
       else if (date == "06")
       {
         date = "6";
       }
       else if (date == "07")
       {
         date = "7";
       }
       else if (date == "08")
       {
         date = "8";
       }
       else if (date == "09")
       {
         date = "9";
       }

      }

      if (date == to_string(getPrevMonth(cur_month)))
      {
        temp.clear();
        temp = (*x);
        command.clear();
        command = SemPath + "\\REPORTS\\stud_att.txt";
        writeDataToFile(command, temp);
      }
    }
  }

  bool createMonthlyReportPDF(string fac_data,string stud_name,string stud_att,string pdf_name)  //? function for generating pdf
  {  
    tempStorage.clear(); 
    command.clear();
    bool flag;
    int PresentCount = 0;
    command = "from fpdf import FPDF\npagesize = ("+to_string(25+countLinesOfFile(stud_att))+",12)\npdf=FPDF(format=pagesize, unit='in')\npdf.add_page()\nepw = pdf.w - 2*pdf.l_margin\npdf.set_font('Arial','B',50.0)\npdf.set_text_color(0,0,0)\n";
    command += "pdf.image('"+DoubleBackslashPath(AMS_Path)+"\\\\OTHER\\\\Telegram.png',x =pdf.l_margin,y=None,w=pdf.w - 2*pdf.l_margin, h=1.5)\npdf.cell(epw, -1.3, 'A M S', align='C')\npdf.ln(0.5)\npdf.line(0.4,1.90,pdf.w-pdf.l_margin,1.90)\npdf.line(0.4,1.97,pdf.w-pdf.l_margin,1.97)\npdf.set_font('Arial','B',15.0)\npdf.set_text_color(43, 153, 213)\npdf.cell(epw, 0.0, 'e-ATTENDANCE REPORT', align='C')\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(0,0,0)\npdf.ln(0.5)\n";
    getDataFromFile(fac_data,tempStorage,1);
    command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Faculty Name
    tempStorage.clear();
    getDataFromFile(fac_data,tempStorage,2);
    command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Faculty Email
    tempStorage.clear();
    getDataFromFile(fac_data,tempStorage,3);
    command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Course Name
    tempStorage.clear();
    getDataFromFile(fac_data,tempStorage,4);
    command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Semester
    tempStorage.clear();
    getDataFromFile(fac_data,tempStorage,5);
    command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.5)\n";//Subject Name
    tempStorage.clear();
    getDataFromFile(fac_data,tempStorage,6);
    command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='C')\n";//Attendance Data Title

    /*Making 2D array for tabuler Data*/
    command += "data = [['ROLL NO.','NAME','PRESENT DAYS','ABSENT DAYS','PER'";
    for(int i=1;i<=(countLinesOfFile(stud_name)+1);i++)
    {
        if(i!=1)
        {
            command += ",[";
            PresentCount = 0;
            for(int k=1;k<=(countLinesOfFile(stud_att));k++)
            {
                tempStorage.clear();
                getDataFromFile(stud_att,tempStorage,k);
                if(tempStorage[19+i-1] == 'P')
                    PresentCount++;
            }
        }
            
        for(int j=1;j<=(countLinesOfFile(stud_att)+5);j++)
        {
            if(i==1 && j > 5)//Dates (Column wise)
            {
                tempStorage.clear();
                getDataFromFile(stud_att,tempStorage,j-5);
                command += ",'"+tempStorage.substr(0,10)+"'";
            }
            if(i>1 && j==1)//Roll Number(Row wise)
            {
                command += "'"+to_string(i-1)+"',";
            }
            
            if(i>1 && j==2)//Name (Row wise)
            {
                tempStorage.clear();
                getDataFromFile(stud_name,tempStorage,i-1);
                command+= "'"+tempStorage+"',";
            }
            if(i>1 && j == 3)//Present Days
            {
                command += "'"+to_string(PresentCount)+"',";
            } 
            if(i>1 && j == 4)//Absent Days
            {
                command += "'"+to_string(countLinesOfFile(stud_att) - PresentCount)+"',";
            } 
            if(i>1 && j == 5)//Percentage Calculation
            {
                stringstream stream;
                stream << fixed << setprecision(2) << (float(100 *  PresentCount)/countLinesOfFile(stud_att));
                string temp = stream.str();
                command += "'"+temp+"%'";
            } 
            if(i>1 && j > 5)
            {
                tempStorage.clear();
                getDataFromFile(stud_att,tempStorage,j-5);
                if(tempStorage[19+i-1] == 'P')
                    command += ",'Present'";
                else
                    command += ",'Absent'";
            }
        }
        command += "]";
    }
    command += "]\n";
    command += "th = pdf.font_size\ncol_width = (epw-4)/"+to_string(countLinesOfFile(stud_att)+4)+"\npdf.ln(0.3)\n";
    command += "for row in range(len(data)):\n\tfor datum in range(len(data[row])):\n\t\tif row==0:\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\t\telse:\n\t\t\tpdf.set_text_color(0,0,0)\n\t\t\tpdf.set_font('Arial','',12.0)\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\tpdf.ln(2*th)\npdf.ln(2)";
    command += "\nLine = \"_\"\nfor i in range(int(pdf.w-pdf.l_margin)):\n\tfor j in range(10):\n\t\tLine+=\"_\" ";
    command += "\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(3, 153, 213)\npdf.cell(epw,0.0,'Have any questions for us or need more information?',align='C')\npdf.ln(0.3)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0,Line, align='C')\npdf.ln(0.22)\npdf.set_text_color(0,0,0)\npdf.cell(epw,0.0,'Email Address For Support   \"ams.software.team@gmail.com\"',align='C')\npdf.ln(0.1)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0,Line,align='C')\npdf.ln(0.5)\npdf.set_text_color(255,0,0)\npdf.set_font('Arial','B',15.0)\npdf.cell(epw,0.0,'Regards, Team AMS.',align='C')\npdf.output('"+DoubleBackslashPath(SemPath) +"\\\\REPORTS\\\\";
    command +=  pdf_name + "','F')\n";

    tempStorage.clear();
    tempStorage = AMS_Path+"\\OTHER\\MWR.py";   // make python File
    writeDataToFile(tempStorage,command);
    
    command.clear();
    command = "python " + AMS_Path + "\\OTHER\\MWR.py" + " 1> " + AMS_Path + "\\OTHER\\output.txt 2>&1";

    system(command.c_str());    //run python file


    command.clear();
    command = AMS_Path + "\\OTHER\\output.txt"; //error file size get
        
    int err = checkEmptyFile(command);
    if(err)
    flag=false;
    else
    flag=true;
    remove(command.c_str()); // delete output/error file 

    command = AMS_Path+"\\OTHER\\MWR.py"; 
    remove(command.c_str());    //delete python file

    remove(fac_data.c_str());     //delete fac_data file
    remove(stud_name.c_str());    //delete stud_name file
    remove(stud_att.c_str());     //delete stud_att file
  
    tempStorage.clear(); //clear for re-using
    command.clear();
    return (flag); 
  
}



  bool checkExistRollNo(string &Attendance, string rl, char AT, int select = 0) //?checking if same roll no exist in the list
  {
    if (Attendance[(stoi(rl) - 1)] == AT) // if user entered roll no is already exist in list
    {
      if (select == 0)
        MSG("ROLL NUMBER ALREADY ", "EXISTS IN THE LIST!", 2, 2, 19); // print error msg
      else
        MSG("ROLL NUMBER DOESN'T ", "EXIST IN THE LIST!", 2, 2, 20); // else print doesn't exist
      return true;
    }
    else
    {
      return false;
    }
  }

  void ListOfAttendance(string &Attendance, int choice) // ? Final List for absent / present student
  {
    int i, spacing_flag = 0, space = 1;

    if (choice == 3)
    {
      setCursorPos(2, 24);
      cout << "|| LIST OF PRESENT ROLL NUMBER ||" << endl; // present list
      setCursorPos(1, 1);
      SetColor(1);

      for (i = 0; i < Attendance.length(); i++) // full list
      {
        if (Attendance[i] == 'P')
        {
          if (space >= 49 && space <= 53) // new line &space logic
            spacing_flag = 1;

          if (spacing_flag == 0)
          {
            cout << i + 1 << " ";
            if (i < 10)
              space++;
            else if (i < 100)
              space += 2;
            else if (i < 1000)
              space += 3;
            else if (i < 10000)
              space += 4;
          }
          else
          {
            setCursorPos(1, 1);
            spacing_flag = 0;
            space = -2;
            cout << i + 1 << " ";
            if (i < 10)
              space++;
            else if (i < 100)
              space += 2;
            else if (i < 1000)
              space += 3;
            else if (i < 10000)
              space += 4;
          }
        }
      }
    }

    else if (choice == 4)
    {
      setCursorPos(2, 24);
      cout << "|| LIST OF ABSENT  ROLL NUMBER ||" << endl; // absent list
      setCursorPos(1, 1);
      SetColor(4);

      for (i = 0; i < Attendance.length(); i++)
      {
        if (Attendance[i] == 'A')
        {

          if (space >= 49 && space <= 53)
          {
            spacing_flag = 1;
          }

          if (spacing_flag == 0)
          {
            cout << i + 1 << " ";
            if (i < 10)
              space++;
            else if (i < 100)
              space += 2;
            else if (i < 1000)
              space += 3;
            else if (i < 10000)
              space += 4;
          }
          else
          {
            setCursorPos(1, 1);
            spacing_flag = 0;
            space = -2;
            cout << i + 1 << " ";

            if (i < 10)
              space++;
            else if (i < 100)
              space += 2;
            else if (i < 1000)
              space += 3;
            else if (i < 10000)
              space += 4;
          }
        }
      }
    }

    SetColor(0);
  }

  int ModifyChoice(int choice)
  {
    int line = 0;
    command.clear();
  reAskModify:

    scrClr(0.5);
    setCursorPos(3, 21);
    cout << " HOW DO YOU WANT TO MODIFY THE LIST ? " << endl;
    setCursorPos(2, 21);
    buildVerticalWall(35);

    line = 0;

    while (line < 5)
    {
      setCursorPos(1, 21);
      if (line == 1)
      {
        if (choice == 3)
          buildHorizontalWall(35, "1) REMOVE PRESENT ROLL NUMBER ");
        else
          buildHorizontalWall(35, "1) REMOVE ABSENT ROLL NUMBER ");
      }
      else if (line == 3)
      {
        if (choice == 3)
          buildHorizontalWall(35, "2) ADD PRESENT ROLL NUMBER  ");
        else
          buildHorizontalWall(35, "2) ADD ABSENT ROLL NUMBER ");
      }
      else
        buildHorizontalWall(35, " ");
      line++;
    }
    setCursorPos(1, 21);
    buildVerticalWall(35);

    askChoice(3, 33, command);
    if (EmptyInput(command))
    {
      InvalidInputErr();
      goto reAskModify;
    }

    ConvertChoiceToINT = validateString(command, 2, 1);

    if (ConvertChoiceToINT == 0)
    {
      InvalidInputErr();
      goto reAskModify;
    }
    return (ConvertChoiceToINT);
  }

  bool ModificationOfAttDATA(string &Attendance, int choice) // ? modify the attendance data
  {
    int Empty_flag = 0, i, temp;
    bool return_flag = false;

    command.clear();
    temp = ModifyChoice(choice);

    while (true)
    {
    MDAgain:
      scrClr(0.5);

      setCursorPos(1, 26);
      SetColor(2);
      cout << "PRESS '*' TO PROCEED FURTHER";
      SetColor(0);

      ListOfAttendance(Attendance, choice); // show list of student  attendance data

      setCursorPos(2, 10);
      // ask if you want to modify
      if ((choice == 3 && temp == 1) || (choice == 4 && temp == 2))
        cout << " ENTER ROLL NUMBER THAT YOU WANT TO MARK AS ABSENT  : ";
      else if ((choice == 4 && temp == 1) || (choice == 3 && temp == 2))
        cout << " ENTER ROLL NUMBER THAT YOU WANT TO MARK AS PRESENT : ";

      ShowConsoleCursor(true);
      fflush(stdin);         // flushing standard input buffer
      getline(cin, command); // take input
      cin.clear();
      ShowConsoleCursor(false);
      if (command == "*")
      {
        return_flag = true;
        break;
      }

      ConvertChoiceToINT = validateRollNo(command, stoi(numberOfstudents), 1); // validate string

      if (ConvertChoiceToINT)
      {
        if ((choice == 3 && temp == 1) || (choice == 4 && temp == 2)) // if choice is prasent
        {
          if (temp == 1)
          {
            if (checkExistRollNo(Attendance, command, 'A', 1)) // check roll no is already exist then print error
              goto MDAgain;                                    // go to list shown again
            else
              Attendance.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
          }
          else
          {
            if (checkExistRollNo(Attendance, command, 'A', 0)) // check roll no is already exist then print error
              goto MDAgain;                                    // go to list shown again
            else
              Attendance.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
          }
        }
        else if ((choice == 4 && temp == 1) || (choice == 3 && temp == 2)) // if choice is absent
        {
          if (temp == 1)
          {
            if (checkExistRollNo(Attendance, command, 'P', 1)) // check roll no is aleady exist then print error
              goto MDAgain;                                    // go to list shown again
            else
              Attendance.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
          }
          else
          {
            if (checkExistRollNo(Attendance, command, 'P', 0)) // check roll no is aleady exist then print error
              goto MDAgain;                                    // go to list shown again
            else
              Attendance.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
          }
        }
      }

      Empty_flag = 0; // flag set as 0
      i = 0;          // i  set as 0

      if (choice == 3) // if choice is present
      {
        while (i <= Attendance.length())
        {
          if (Attendance[i] == 'P')
          {
            Empty_flag = 1; // flag is true
            break;
          }
          Empty_flag = 0; // else flag set as 0
          i++;
        }
      }
      else if (choice == 4) // if choice is absent
      {
        while (i <= Attendance.length())
        {
          if (Attendance[i] == 'A')
          {
            Empty_flag = 1; // flag set as true
            break;
          }
          Empty_flag = 0; // else flag is 0
          i++;
        }
      }
      if (!Empty_flag) // if flag is false
      {

        if (choice == 3)      // if choice is present than
          MarkAP_A(2);        // all absent
        else if (choice == 4) // if choice is absent than
          MarkAP_A(1);        // all present
        return_flag = false;  // flag set 0
        break;
      }
    }

    return (return_flag); // return flag
  }

  void submitAttendanceToDB(string &Attendance) // ? Finally data sent to database
  {
    
    command.clear();
    command = SemPath + "\\DAILY-RECORD\\records.txt"; // making path for file handling
    string temp;

    temp = CUR_DATE + "|" + CUR_TIME + "|" + Attendance;
    writeDataToFile(command, temp);
  }

  int MarkAP_A(int choice) //? function to mark all students present/absent at once
  {
    // variable clear for re-use
    tempStorage.clear();
    command.clear();

    for (int i = 1; i <= stoi(numberOfstudents); i++) //*intial data
    {
      if (choice == 1)
        tempStorage += "P"; // all present
      else if (choice == 2)
        tempStorage += "A"; // all absent
    }

  confirm:

    if (choice == 1) // if all student are present
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
    else if (choice == 2) // if all students are absent
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
    // confirm msg
    if (choice == 1) // all students are present then confirm this details with yes /no in
    {
      ConvertChoiceToINT = YesNoInput("ALL PRESENT !", command, "ARE YOU SURE ?", 1);
    }
    else if (choice == 2) // all students are absent then confirm this details with yes /no in
    {
      ConvertChoiceToINT = YesNoInput("ALL ABSENT  !", command, "ARE YOU SURE ?", 1);
    }
    if (ConvertChoiceToINT == -1) // if choice is not yes/no then print error
    {
      InvalidInputErr();
      goto confirm; // go to confirm again
    }

    if (ConvertChoiceToINT == 1)         // if choice is yes then submit this details
      submitAttendanceToDB(tempStorage); // submit

    return (ConvertChoiceToINT); // return user input
  }

  int EnterPR_AR(int choice) // ? function for manually entering absent / present numbers
  {

    int i, Empty_flag = 0, count = 1;
    bool flag = true;
    bool CC_flag = true;

    tempStorage.clear();
    command.clear();

    string MCH;

    for (i = 1; i <= stoi(numberOfstudents); i++)
    {
      // fill up all data with all absent / all present by default initially
      if (choice == 3)
        tempStorage += "A";
      else if (choice == 4)
        tempStorage += "P";
    }
    if (choice == 3) // if choice is present
    {
      while (i <= tempStorage.length())
      {
        if (tempStorage[i] == 'P') // fill up data with present
        {
          Empty_flag = 1; // empty flag true
          break;
        }
        Empty_flag = 0; // else empty flag false
        i++;
      }
    }
    else if (choice == 4) // if choice is absent
    {
      while (i <= tempStorage.length())
      {
        if (tempStorage[i] == 'A') // fill up with absent
        {
          Empty_flag = 1; // flag set as true
          break;
        }
        Empty_flag = 0; // else 0
        i++;
      }
    }

    while (true)
    {
      reInput:
      scrClr(0.5);
      setCursorPos(1, 26);
      SetColor(2);
      cout << "PRESS '*' TO PROCEED FURTHER";
      SetColor(0);

      ListOfAttendance(tempStorage, choice); // show list of students

      setCursorPos(2, 26);

      if (choice == 3)
        cout << "ENTER PRESENT ROLL NUMBER : ";
      else if (choice == 4)
        cout << "ENTER ABSENT ROLL NUMBER : ";

      ShowConsoleCursor(true);
      fflush(stdin);
      getline(cin, MCH); // take input
      cin.clear();
      ShowConsoleCursor(false);

      if (MCH == "*") // if user press *
      {

        if (!Empty_flag) // flag is 0
        {

          if (choice == 3) // choice is present
          {
            scrClr(0.5);
            setCursorPos(9, 19); // set cursor
            SetColor(1);
            cout << "KINDLY ADD PRESENT ROLL NUMBERS TO LIST !" << endl; // warn message
            scrClr(1);
            SetColor(0);
            goto reInput; // re-ask roll no
          }
          else if (choice == 4) // if choice is absent
          {
            scrClr(0.5);
            setCursorPos(9, 19);
            SetColor(4);
            cout << "KINDLY ADD ABSENT  ROLL NUMBERS TO LIST ! " << endl; // warn message
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

      ConvertChoiceToINT = validateRollNo(MCH, stoi(numberOfstudents), 1); // validate string

      if (ConvertChoiceToINT)
      {
        count++;
        if (choice == 3)
        {
          if (checkExistRollNo(tempStorage, MCH, 'P')) // check exist warning present
            goto reInput;
          else
            tempStorage.replace((ConvertChoiceToINT - 1), 1, "P"); // modify for first time according to choice
        }
        else if (choice == 4)
        {
          if (checkExistRollNo(tempStorage, MCH, 'A')) // check exist warning absent
            goto reInput;
          else
            tempStorage.replace((ConvertChoiceToINT - 1), 1, "A"); // modify for first time according to choice
        }
      }

      if ((count - 1) == tempStorage.length())
      {
        break;
      }

      Empty_flag = 0; // set flag as 0
      i = 0;

      if (choice == 3)
      {
        while (i <= tempStorage.length())
        {
          if (tempStorage[i] == 'A') // set absent
          {
            Empty_flag = 1; // set flag as 1
            break;
          }
          Empty_flag = 0; // set flag as 0
          i++;
        }
      }
      else if (choice == 4) // if choice is absent
      {
        while (i <= tempStorage.length())
        {
          if (tempStorage[i] == 'P') // if tempstorage == p
          {
            Empty_flag = 1; // set flag as 1
            break;
          }
          Empty_flag = 0; // set flag as 0
          i++;
        }
      }
    }

  confirm:
    scrClr(0.5);

    ListOfAttendance(tempStorage, choice); // list Attendance

    command.clear();

    setCursorPos(4, 14);
    ConvertChoiceToINT = YesNoInput(" DO YOU CONFIRM THESE NUMBERS ? ", command); // confirm msg
    if (ConvertChoiceToINT == -1)                                                 // if choice is not yes or no
    {
      InvalidInputErr(); // error
      goto confirm;
    }
    else if (ConvertChoiceToINT == 0) // if choice is no than modify
    {
      if (ModificationOfAttDATA(tempStorage, choice)) // modifiction
      {
        goto confirm; // re-ask confirm
      }
      else
        flag = false;
    }

    if (ConvertChoiceToINT == 1 && flag == true) // choice is yes
    {
      submitAttendanceToDB(tempStorage); // submit
    }

    return (ConvertChoiceToINT); // return choice
  }

  void MonthlyReportGenerating(string &month)
  {
    string temp;
    tempStorage.clear();
    temp = "ATTENDANCE REPORT FOR ";
    tempStorage = " IS BEING GENERATED";

    int i = 1;
    do
    {
      scrClr(0.5);
      setCursorPos(9, 14);
      SetColor(0);
      cout << temp;
      SetColor(1);
      cout << month;
      SetColor(0);
      cout << tempStorage;
      ShowConsoleCursor(false);
      scrClr(1);
      tempStorage = tempStorage + ".";

      if (i == 4)
      {
        break;
      }
      i++;

    } while (true);

    tempStorage.clear();
    SetColor(0);
    scrClr();
  }

  int getPrevMonth(int cur_month)
  {
     cur_month--;
     
     if(cur_month<=0)
     {
       cur_month=12;
     }
     
     return(cur_month);
     
  }


  bool checkPreMonthData(int month)
  {
    tempStorage.clear();

    int j = 1;
    command = SemPath + "\\DAILY-RECORD\\records.txt"; // path stored in command var
    int line = countLinesOfFile(command);
    bool flag = false;
    
    while (j <= line)
    {
      tempStorage.clear();
      getDataFromFile(command, tempStorage, j);
      tempStorage =  tempStorage.substr(3,2);

      if (!tempStorage.empty())
      {
          if (tempStorage == "01")
          {
            tempStorage = "1";
          }
          else if (tempStorage == "02")
          {
            tempStorage = "2";
          }
          else if (tempStorage == "03")
          {
            tempStorage = "3";
          }
          else if (tempStorage == "04")
          {
            tempStorage = "4";
          }
          else if (tempStorage == "05")
          {
            tempStorage = "5";
          }
          else if (tempStorage == "06")
          {
            tempStorage = "6";
          }
          else if (tempStorage == "07")
          {
            tempStorage = "7";
          }
          else if (tempStorage == "08")
          {
            tempStorage = "8";
          }
          else if (tempStorage == "09")
          {
            tempStorage = "9";
          }

      }

      if(stoi(tempStorage)==month)
      {
        flag=true;
        break;
      }

      j++;
    }

    tempStorage.clear();
    return(flag);
  }


public:

  MODULE_2()
  {
    // clear variable for re-use
    command.clear();
    tempStorage.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
    month_report_flag = false;
   
  }

  ~MODULE_2()
  {
    
    /******************************** MONTHLY REPORT **************************************/
    if(month_report_flag) // ? according to 1 month trigger
    {
      string month = (file_month == 1) ? "JANUARY" : (file_month == 2) ? "FEBRUARY"
                                                 : (file_month == 3)   ? "MARCH"
                                                 : (file_month == 4)   ? "APRIL"
                                                 : (file_month == 5)   ? "MAY"
                                                 : (file_month == 6)   ? "JUNE"
                                                 : (file_month == 7)   ? "JULY"
                                                 : (file_month == 8)   ? "AUGUST"
                                                 : (file_month == 9)   ? "SEPTEMBER"
                                                 : (file_month == 10)  ? "OCTOBER"
                                                 : (file_month == 11)  ? "NOVEMBER"
                                                 : (file_month == 12)  ? "DECEMBER"
                                                                       : "null";

      MonthlyReportGenerating(month);
      makeMonthReport();

      pdfName += "AMS_REPORT_" + course_name + "_SEM_" + sem + "_" + subject_name + "_" + month;
      replaceWithHyphen(pdfName);
      pdfName += ".pdf";

      if (createMonthlyReportPDF(SemPath + "\\REPORTS\\fac_data.txt", SemPath + "\\REPORTS\\stud_name.txt", SemPath + "\\REPORTS\\stud_att.txt", pdfName))
      {
        //*threading used for  processing email part

        MODULE_2 MD2;
        thread t1(&sendToEmail, MD2, "ams.software.team@gmail.com", "Amsisrich@45", FacultyEmail, "MONTHLY-ATTENDANCE-REPORT", "Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your MONTHLY Attendance Report.\n\nThank You.\n\n", SemPath + "\\REPORTS\\" + pdfName, pdfName);
        thread t2(&LoadingProcess, MD2);

        t1.join(); // join the thread
        t2.join(); // join the thread

        scrClr(); // by clearing screen it resolves flickring error of screen...

        if (process_flag && email_flag)
        { 
          Beep(1950,500);
          reportSentSuccessfully(pdfName);   // sent email successfully with attachment
        }
        else
        {
          warnMsg("REPORT COULDN'T BE SENT !", 4, 26, "ERROR CODE : 404/444/599 ", 1, 26); // error while sending email
        }
      }
      else
      {
        warnMsg("PDF REPORT COULDN'T BE GENERATED !", 4, 22, "ERROR CODE : 404/417/424 ", 1, 26); // error while sending email
      }
    }
    buffer.clear();      // clearing buffer
    LIST.clear();        // clearing List
    command.clear();     // clearing command
    tempStorage.clear(); // clearing tempstorage
    DATA.clear();        // clearing DATA
  }

  void MonthlyReport() //? 1 month trigger enble /disable
  {
    /***************************************/

    command.clear();
    tempStorage.clear();

    command = SemPath + "\\DAILY-RECORD\\records.txt";
    getDataFromFile(command, tempStorage, countLinesOfFile(command));

    if (!tempStorage.empty())
    {
      tempStorage = tempStorage.substr(3, 2);

      if (tempStorage == "01")
      {
        tempStorage = "1";
      }
      else if (tempStorage == "02")
      {
        tempStorage = "2";
      }
      else if (tempStorage == "03")
      {
        tempStorage = "3";
      }
      else if (tempStorage == "04")
      {
        tempStorage = "4";
      }
      else if (tempStorage == "05")
      {
        tempStorage = "5";
      }
      else if (tempStorage == "06")
      {
        tempStorage = "6";
      }
      else if (tempStorage == "07")
      {
        tempStorage = "7";
      }
      else if (tempStorage == "08")
      {
        tempStorage = "8";
      }
      else if (tempStorage == "09")
      {
        tempStorage = "9";
      }

      file_month = stoi(tempStorage);
      if ( file_month != cur_month && checkPreMonthData(getPrevMonth(cur_month)) )
        month_report_flag = true;
    }

    tempStorage.clear();
  }
  
  int confirmTodayAttendance()
  {
    ConvertChoiceToINT = 1; // re-used

    command.clear();
    tempStorage.clear();    

    command = SemPath + "\\DAILY-RECORD\\records.txt"; // path stored in command var
    getDataFromFile(command, tempStorage, countLinesOfFile(command));

    tempStorage = tempStorage.substr(0, tempStorage.find("|"));

    if (tempStorage == CUR_DATE) // to avoid taking attendance for the same day
    {
      command.clear();
      command = course_name + " SEM " + sem + " " + subject_name;

      scrClr();
      setCursorPos(8, 25);
      ShowConsoleCursor(false);
      SetColor(2);
      cout << command;
      SetColor(0);
      setCursorPos(2, 18);
      cout << " ATTENDANCE FOR ";
      SetColor(1);
      cout << CUR_DATE;
      SetColor(0);
      cout << " IS ALREADY TAKEN!";
      command.clear();
      ConvertChoiceToINT = 0;
      scrClr(2);
    }

    return (ConvertChoiceToINT); // return
  }

  void AttendanceOptionWindow() //? to display window with 4 Options of attendance
  {
    int line;
    command.clear();
    tempStorage.clear();

    reAskAtdM:

    // build UI-Box screen
    scrClr(0.5);
    setCursorPos(4, 18);
    buildVerticalWall(43);
    line = 0;

    while (line < 9)
    {
      setCursorPos(1, 18);
      if (line == 1)
        buildHorizontalWall(43, "1) MARK ALL PRESENT ");
      else if (line == 3)
        buildHorizontalWall(43, "2) MARK ALL ABSENT ");
      else if (line == 5)
        buildHorizontalWall(43, "3) ENTER PRESENT ROLL NUMBER ");
      else if (line == 7)
        buildHorizontalWall(43, "4) ENTER ABSENT ROLL NUMBER ");
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

    AT_OPTION_CHOICE = ConvertChoiceToINT; // string store in static variable
  }

  int takeAttendance(int choice) //? select appropriate option for taking attendace
  {
    int process_flag = 0;

    if (choice == 1 || choice == 2) // if choice is all present or all absent
    {
      process_flag = MarkAP_A(choice); // choice is stored in process flag
    }
    else if (choice == 3 || choice == 4)
    {
      process_flag = EnterPR_AR(choice);
    }

    return (process_flag); // return flag
  }
  void AttendanceTakenSuccessfully() //? module 2 successfully worked
  {
    tempStorage.clear();
    tempStorage = course_name + " SEM " + sem + " " + subject_name; // folder name stored in tempstorage
    MSG("ATTENDANCE TAKEN OF ", tempStorage, 2, 0, 20);             // print msg
  }

protected:
  void SetNoObj()
  {
    //? by empty defination of pure virtual function here we are restricting creation of parent(GENERAL MODULE) class
  }
  //************************************************************************************/
};

//*---------------------------STATIC DEFINATIONS-MODULE-2------------------------------/

int MODULE_2::AT_OPTION_CHOICE; // ATTEDANCE OPTION-CHOICE ALL AUTO / ENTER MANUAL;

//-----------------------------------------------------------------------------------/

class MODULE_3 : public MODULE_GENERAL //?module 3 class
{

  //*=============================DATA-MEMBERS================================//

private:
  string attendance;

public:
  static int CUS_REPORT_CHOICE; // REPORT CHOICE DATE / STUDENT

protected:
  //*=============================DATA-MEMBERS-END================================//

  //*=============================MEMBERS-FUNCTIONS===================================//

private:

  bool characterValidate(string &input)
  {
    string list = "#%&{}*><$!:\\\'\"@+`|=-.,;[]_()^~?";
    bool flag = false;
    for(int j = 0 ; j < list.length() ; j++)
    {
      for(int i = 0 ; i < input.length() ; i++)
      {
        if(input[i] == list[j])
        {
          flag = true;
        }
      }
      if(flag==true)
       break;
    }

    for(int i = 0 ; i < input.length() ; i++)
    {
      if( (input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))
      {
        flag = true;
        break;
      }
    }

    return(flag);
  }
  
  bool DateInput() //? taking date input
  {
    reAskDate:

    date.clear(); // clear for re-using

    scrClr(0.5);
    fflush(stdin);
    setCursorPos(9, 22);
    cout << "Enter Date ";
    SetColor(2);
    cout << "(DD/MM/YYYY)";
    SetColor(0);
    cout << " : ";
    ShowConsoleCursor(true);
    SetColor(1);
    getline(cin, date);
    cin.clear();
    SetColor(0);

    if (EmptyInput(date) || characterValidate(date)) // validating date
    {
      scrClr(0.5);
      InvalidInputErr();
      goto reAskDate;
    }

    
    if (!IfDateExistThenGetData(date)) // if valid and exists then get data
    {
      goto reAskDate;
    }

    if (tempStorage == "false") // logic for if date valid and record not exist then return to home screen
      return (true);
    else
      return (false);
  }

  bool IfDateExistThenGetData(string dt) //? if date valid & exist in DATABASE then get data of that date
  {
    command.clear();
    tempStorage.clear();
    buffer.clear();
    DATA.clear();

    string d, m, y;
    int found_pos, temp_pos;
    bool flag = true;

    // validation format DD/MM/YYYY

    found_pos = dt.find("/");
    d = dt.substr(0, found_pos);
    temp_pos = (found_pos + 1);

    found_pos = dt.find("/", temp_pos);
    m = dt.substr(temp_pos, (found_pos - temp_pos));
    temp_pos = (found_pos + 1);

    found_pos = dt.find("/", temp_pos);
    y = dt.substr(temp_pos);

    // validation of leap year and all that related stuff
    if (stoi(d) < 1 || stoi(d) > 31)
    {
      flag = false;
    }
    else if (stoi(m) < 1 || stoi(m) > 12)
    {
      flag = false;
    }
    else if (stoi(y) < 2022 || stoi(y) > 9999) 
    {
      flag = false;
    }
    else if (stoi(d) > 29 && stoi(m) == 2)
    {
      flag = false;
    }
    else if ((stoi(d) == 31) && (stoi(m) == 4 || stoi(m) == 6 || stoi(m) == 9 || stoi(m) == 11))
    {
      flag = false;
    }
    else if ((stoi(d) == 29 && stoi(m) == 2) && ((stoi(y) % 100 == 0 && stoi(y) % 400 != 0) || (stoi(y) % 4 != 0)))
    {
      flag = false;
    }

    if (flag)
    {

      command = SemPath + "\\DAILY-RECORD\\records.txt"; // path stored in command var
      ifstream fin(command.c_str(), ios::in);            // file open

      if (!fin.is_open())
      {
        scrClr();
        setCursorPos(9, 28);
        cout << "DATA BASE-ERROR : 404 ";
        scrClr(2);
        exit(1);
      }
      else
      {
        fflush(stdin);
        command.clear();
        getline(fin, command);
        buffer.push_back(command);

        while (!fin.eof()) // data receive until file ends
        {
          getline(fin, command);     // fetch again from file
          buffer.push_back(command); // save that string(data) in vector
        }

        // extracting data from buffer
        for (auto i = buffer.begin(); i != buffer.end(); ++i)
        {
          tempStorage = (*i);
          found_pos = tempStorage.find("|");

          d = tempStorage.substr(0, found_pos);
          temp_pos = (found_pos + 1);

          found_pos = tempStorage.find("|", temp_pos);
          time = tempStorage.substr(temp_pos, (found_pos - temp_pos));
          temp_pos = (found_pos + 1);

          found_pos = tempStorage.find("|", temp_pos);
          attendance = tempStorage.substr(temp_pos);

          DATA.push_back(make_tuple(d, time, attendance, ""));
        }

        // get exact match of that input date
        for (auto i = DATA.begin(); i != DATA.end(); i++)
        {

          if (dt == get<0>((*i)))
          {
            time = get<1>((*i));
            attendance = get<2>((*i));
            flag = true;
            tempStorage.clear();   // re use as flag return to home screen value store
            tempStorage = "false"; // no return and further process for report making
            break;
          }
          flag = false;
        }

        fin.close();
      }
      if (!flag)
      {
        scrClr(0.5);
        setCursorPos(9, 22);
        ShowConsoleCursor(false);
        SetColor(0);
        cout << "REPORT FOR ";
        SetColor(2);
        cout << date;
        SetColor(0);
        cout << " DOESN'T EXIST !";
        scrClr(2);
        flag = true;
        tempStorage.clear();  // re use as flag return to home screen value store
        tempStorage = "true"; // yes return to home screen
      }
    }
    else
    {
      scrClr(0.5);
      warnMsg("INVALID DATE / DATE FORMAT !!!", 4, 25); // error
    }

    return (flag);
  }

  void makeDateReport() //? make the corresponding Date Wise Report
  {
    command.clear();
    tempStorage.clear();

    int j = 1, found_pos, temp_pos;

    command = SemPath + "\\REPORTS\\fac_data.txt";

    tempStorage = "ATTENDANCE DATE : " + date + " TIME : " + time;
    writeDataToFile(command, tempStorage);

    tempStorage = "1) FACULTY NAME : " + FacultyName;
    writeDataToFile(command, tempStorage);

    tempStorage = "2) COURSE NAME  : " + course_name;
    writeDataToFile(command, tempStorage);

    tempStorage = "3) SEMSTER : " + sem;
    writeDataToFile(command, tempStorage);

    tempStorage = "4) SUBJECT NAME : " + subject_name;
    writeDataToFile(command, tempStorage);

    tempStorage = "-: [ Attendance Data ] :- ";
    writeDataToFile(command, tempStorage);

    while (j <= stoi(numberOfstudents))
    {
      tempStorage.clear();
      found_pos = temp_pos = 0;
      command.clear();
      student_name.clear();

      command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";
      getDataFromFile(command, tempStorage, j);

      found_pos = tempStorage.find("|");
      scrClr();

      student_name = tempStorage.substr((found_pos + 1), (tempStorage.find("|", (found_pos + 1)) - (found_pos + 1))); 

      command = SemPath + "\\REPORTS\\stud_name.txt";
      writeDataToFile(command, student_name);

      j++;
    }

    command.clear();
    command = SemPath + "\\REPORTS\\stud_att" + ".txt";
    writeDataToFile(command, date + "|" + time + "|" + attendance);
  }

  bool createDateWiseReportPDF(string fac_data, string stud_name, string stud_att, string pdf_name) //?Date Vise Report Generate PDF(If overloding posssible then must overload  GeneratePDF function)
  {
    tempStorage.clear();
    command.clear();
    string temp;
    bool flag;

    command = "from fpdf import FPDF\npdf=FPDF(format='A4', unit='in')\npdf.add_page()\nepw = pdf.w - 2*pdf.l_margin\npdf.set_font('Arial','B',50.0)\npdf.set_text_color(0,0,0)\n";
    command += "pdf.image('" + DoubleBackslashPath(AMS_Path) + "\\\\OTHER\\\\Telegram.png',x =pdf.l_margin,y=None,w=pdf.w - 2*pdf.l_margin, h=1.5)\npdf.cell(epw, -1.3, 'A M S', align='C')\npdf.ln(0.5)\npdf.line(0.4,1.90,7.8,1.90)\npdf.line(0.4,1.97,7.8,1.97)\npdf.set_font('Arial','B',15.0)\npdf.set_text_color(43, 153, 213)\npdf.cell(epw, 0.0, 'e-ATTENDANCE REPORT', align='C')\npdf.ln(0.5)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(0,0,0)\n";
    getDataFromFile(fac_data, tempStorage, 1);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Attendance taken on : date & time
    tempStorage.clear();
    getDataFromFile(fac_data, tempStorage, 2);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Faculty Name
    tempStorage.clear();
    getDataFromFile(fac_data, tempStorage, 3);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Course Name
    tempStorage.clear();
    getDataFromFile(fac_data, tempStorage, 4);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Semester
    tempStorage.clear();
    getDataFromFile(fac_data, tempStorage, 5);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.5)\n"; // Subject Name
    tempStorage.clear();
    getDataFromFile(fac_data, tempStorage, 6);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='C')\n"; // Attendance Data Title

    /*Making 2D array for tabular Data*/

    command += "data = [['ROLL NO.','NAME','ATTENDANCE']";
    getDataFromFile(stud_att, temp, 1);
    temp = temp.substr(20);

    for (int i = 1; i <= stoi(numberOfstudents); i++)
    {
      command += ",['" + to_string(i) + "',";
      tempStorage.clear();
      getDataFromFile(stud_name, tempStorage, i);
      command += "'" + tempStorage + "',";
      if (temp[i - 1] == 'P')
        command += "'Present'";
      else
        command += "'Absent'";
      command += "]";
    }
    command += "]\n";

    /*2D Array ended */

    command += "pdf.set_font('Arial','B',12.0)\npdf.set_text_color(3, 153, 213)\nth = pdf.font_size\ncol_width = (epw-4)/2\npdf.ln(0.3)\n";
    command += "for row in range(len(data)):\n\tfor datum in range(len(data[row])):\n\t\tif row==0:\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\t\telse:\n\t\t\tpdf.set_text_color(0,0,0)\n\t\t\tpdf.set_font('Arial','',12.0)\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\tpdf.ln(2*th)\n";
    command += "pdf.ln(2)\n";
    command += "pdf.set_font('Arial','B',12.0)\npdf.set_text_color(3, 153, 213)\npdf.cell(epw,0.0,'Have any questions for us or need more information?',align='C')\npdf.ln(0.3)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0, '_______________________________________________________________________________', align='L')\npdf.ln(0.22)\npdf.set_text_color(0,0,0)\npdf.cell(epw,0.0,'Email Address For Support   \"ams.software.team@gmail.com\"',align='C')\npdf.ln(0.1)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0, '_______________________________________________________________________________', align='L')\npdf.ln(0.5)\npdf.set_text_color(255,0,0)\npdf.set_font('Arial','B',15.0)\npdf.cell(epw,0.0,'Regards, Team AMS.',align='C')\npdf.output('" + DoubleBackslashPath(SemPath) + "\\\\REPORTS\\\\";
    command += pdf_name + "','F')\n";

    temp.clear();
    temp = AMS_Path + "\\OTHER\\DWR.py"; // form python path
    writeDataToFile(temp, command);      // write all the data in python file

    command.clear();
    command = "python " + AMS_Path + "\\OTHER\\DWR.py" + " 1> " + AMS_Path + "\\OTHER\\output.txt 2>&1";
    system(command.c_str()); // run python file

    command.clear();
    command = AMS_Path + "\\OTHER\\output.txt";
    int err = checkEmptyFile(command);
    if (err)
      flag = false;
    else
      flag = true;
    remove(command.c_str()); // delete output/error file

    command.clear();
    command = AMS_Path + "\\OTHER\\DWR.py";
    remove(command.c_str()); // delete python file

    remove(fac_data.c_str());  // delete fac_data file
    remove(stud_name.c_str()); // delete stud_name file
    remove(stud_att.c_str());  // delete stud_att file

    tempStorage.clear(); // clear for reusability
    command.clear();

    return (flag);
  }


  void makeStudentReport()
  {
    command.clear();
    tempStorage.clear();

    command = SemPath + "\\DAILY-RECORD";
    double count = 0, totalDay = countLinesOfFile(command + "\\records.txt");

    double per;

    for (int i = 1; i <= totalDay; i++)
    {
      tempStorage.clear(); // used as whole string of single day record
      command = SemPath + "\\DAILY-RECORD";
      getDataFromFile(command + "\\records.txt", tempStorage, i);

      command.clear();
      command = SemPath + "\\REPORTS";

      date.clear(); // clear for reusability
      date = tempStorage.substr(0, 10);
      writeDataToFile(command + "\\stud_date.txt", date);

      time.clear();
      time = tempStorage.substr(11, 8);
      writeDataToFile(command + "\\stud_time.txt", time);

      attendance.clear();
      attendance = tempStorage.substr(20);

      if (attendance[stoi(RoLLNo) - 1] == 'P')
      {
        writeDataToFile(command + "\\stud_att.txt", "Present");
        count++;
      }
      else
      {
        writeDataToFile(command + "\\stud_att.txt", "Absent");
      }
    }
    tempStorage.clear();

    command = SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt";
    getDataFromFile(command, FacultyName, 1);

    command.clear();
    command = SemPath + "\\REPORTS\\stud_data.txt";

    tempStorage.clear();
    tempStorage = "1) STUDENT ROLL NUMBER : " + RoLLNo;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "2) STUDENT NAME : " + student_name;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "3) STUDENT EMAIL  : " + student_email;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "4) FACULTY NAME  : " + FacultyName;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "5) COURSE NAME  : " + course_name;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "6) SEMSTER : " + sem;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "7) SUBJECT NAME : " + subject_name;
    writeDataToFile(command, tempStorage);

    if (totalDay >= count) // double assurity
      per = double((count * 100) / totalDay);
    else
      per = 0.00;

    stringstream stream;
    stream << fixed << setprecision(2) << per;
    string temp = stream.str();

    tempStorage.clear();
    tempStorage = "8) CURRENT ATTENDANCE PERCENTAGE : " + temp + " %";
    writeDataToFile(command, tempStorage);

    tempStorage = " -: [Attendance Data] :- ";
    writeDataToFile(command, tempStorage);
  }

  bool createStudentWiseReportPDF(string stud_data, string stud_date, string stud_time, string stud_att, string pdfname) //?Student Wise Report Generate PDF
  {

    tempStorage.clear();
    command.clear();
    string temp;
    bool flag;

    command = "from fpdf import FPDF\npdf=FPDF(format='A4', unit='in')\npdf.add_page()\nepw = pdf.w - 2*pdf.l_margin\npdf.set_font('Arial','B',50.0)\npdf.set_text_color(0,0,0)\n";
    command += "pdf.image('" + DoubleBackslashPath(AMS_Path) + "\\\\OTHER\\\\Telegram.png',x =pdf.l_margin,y=None,w=pdf.w - 2*pdf.l_margin, h=1.5)\npdf.cell(epw, -1.3, 'A M S', align='C')\npdf.ln(0.5)\npdf.line(0.4,1.90,7.8,1.90)\npdf.line(0.4,1.97,7.8,1.97)\npdf.set_font('Arial','B',15.0)\npdf.set_text_color(43, 153, 213)\npdf.cell(epw, 0.0, 'e-ATTENDANCE REPORT', align='C')\npdf.ln(0.5)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(0,0,0)\n";
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 1);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Roll No
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 2);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Student Name
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 3);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Student Email
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 4);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Faculty Name
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 5);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Course Name
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 6);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Semester
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 7);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.3)\n"; // Subject name
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 8);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='L')\npdf.ln(0.5)\n\n"; // current attendance percentage
    tempStorage.clear();
    getDataFromFile(stud_data, tempStorage, 9);
    command += "pdf.cell(epw,0.0,'" + tempStorage + "', align='C')\n"; // Attendance data 

    /*Making 2D array of tabuler data*/
    command += "data = [['DATE','TIME','ATTENDANCE']";
    for (int i = 1; i <= countLinesOfFile(stud_date); i++)
    {
      tempStorage.clear();
      getDataFromFile(stud_date, tempStorage, i);
      command += ",['" + tempStorage + "',";
      tempStorage.clear();
      getDataFromFile(stud_time, tempStorage, i);
      command += "'" + tempStorage + "',";
      tempStorage.clear();
      getDataFromFile(stud_att, tempStorage, i);
      command += "'" + tempStorage + "']";
    }
    command += "]\n";

    /*2D array done*/
    command += "pdf.set_font('Arial','B',12.0)\npdf.set_text_color(43, 153, 213)\nth = pdf.font_size\ncol_width = epw/3\npdf.ln(0.3)\nfor row in range(len(data)):\n\tfor datum in range(len(data[row])):\n\t\tif row==0:\n\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\t\telse:\n\t\t\tpdf.set_text_color(0,0,0)\n\t\t\tpdf.set_font('Arial','',12.0)\n\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\tpdf.ln(2*th)\n\npdf.ln(2)\n";
    command += "pdf.set_font('Arial','B',12.0)\npdf.set_text_color(43, 153, 213)\npdf.cell(epw,0.0,'Have any questions for us or need more information?',align='C')\npdf.ln(0.3)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0, '_______________________________________________________________________________', align='L')\npdf.ln(0.22)\npdf.set_text_color(0,0,0)\npdf.cell(epw,0.0,'Email Address For Support   \"ams.software.team@gmail.com\"',align='C')\npdf.ln(0.1)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0, '_______________________________________________________________________________', align='L')\npdf.ln(0.5)\npdf.set_text_color(255,0,0)\npdf.set_font('Arial','B',15.0)\npdf.cell(epw,0.0,'Regards, Team AMS.',align='C')\npdf.output('" + DoubleBackslashPath(SemPath) + "\\\\REPORTS\\\\";
    command += pdfname + "','F')\n";

    tempStorage.clear();
    tempStorage = AMS_Path + "\\OTHER\\SWR.py"; // make python File
    writeDataToFile(tempStorage, command);

    command.clear();
    command = "python " + AMS_Path + "\\OTHER\\SWR.py" + " 1> " + AMS_Path + "\\OTHER\\output.txt 2>&1";

    system(command.c_str()); // run python file

    command = AMS_Path + "\\OTHER\\SWR.py";
    remove(command.c_str()); // delete python file

    command.clear();
    command = AMS_Path + "\\OTHER\\output.txt"; // to fetch error file size

    int err = checkEmptyFile(command);
    if (err)
      flag = false;
    else
      flag = true;

    remove(command.c_str()); // delete output/error file

    remove(stud_data.c_str()); // delete stud_data file
    remove(stud_date.c_str()); // delete stud_date file
    remove(stud_time.c_str()); // delete stud_time file
    remove(stud_att.c_str());  // delete stud_att file
    tempStorage.clear();
    command.clear();

    return (flag);
  }
  
  bool createSemesterReportPDF(string BasicDetails,string Name,string Attendance,string pdf_name)//?Date Vise Report Generate PDF(If overloding posssible then must overload  GeneratePDF function)
  { 
    int PresentCount;
    tempStorage.clear(); 
    command.clear();
    bool flag;
    command = AMS_Path+"\\OTHER\\6MR.py"; // make python path
    fstream write(command.c_str(),ios::out);

    if(!write.is_open()) // if file not opened
    {   
      scrClr();
      setCursorPos(9, 28);
      cout << "DATA BASE-ERROR-201-204! "; 
      scrClr(2);
      exit(1);
    }
    else
    {
        command.clear();
        command = "from fpdf import FPDF\npdf=FPDF(format='A4', unit='in')\npdf.add_page()\nepw = pdf.w - 2*pdf.l_margin\npdf.set_font('Arial','B',50.0)\npdf.set_text_color(0,0,0)\n";
        command += "pdf.image('"+DoubleBackslashPath(AMS_Path)+"\\\\OTHER\\\\Telegram.png',x =pdf.l_margin,y=None,w=pdf.w - 2*pdf.l_margin, h=1.5)\npdf.cell(epw, -1.3, 'A M S', align='C')\npdf.ln(0.5)\npdf.line(0.4,1.90,7.8,1.90)\npdf.line(0.4,1.97,7.8,1.97)\npdf.set_font('Arial','B',15.0)\npdf.set_text_color(43, 153, 213)\npdf.cell(epw, 0.0, 'e-ATTENDANCE REPORT', align='C')\npdf.ln(0.5)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(0,0,0)\n";
        getDataFromFile(BasicDetails,tempStorage,1);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Faculty Name
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,2);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Faculty Joining Year
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,3);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Department Name
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,4);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Course name
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,5);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Semester
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,6);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Subject Name
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,7);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Number of student
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,8);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Report type
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,9);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='L')\npdf.ln(0.3)\n";//Records
        tempStorage.clear();
        getDataFromFile(BasicDetails,tempStorage,10);
        command += "pdf.cell(epw,0.0,'"+tempStorage+"', align='C')\npdf.ln(0.3)\n";//Attendance
        command += "data = [['ROLL NO.','NAME','ATTENDANCE']";
        
        for(int i=1;i<=countLinesOfFile(Name);i++)
        {
            command += ",['" + to_string(i) + "',"; 
            tempStorage.clear();
            getDataFromFile(Name,tempStorage,i);
            command += "'" + tempStorage + "',";
            PresentCount = 0;
            for(int k=1;k<=(countLinesOfFile(Attendance));k++)
            {
                tempStorage.clear();
                getDataFromFile(Attendance,tempStorage,k);
  
                 if(tempStorage[19+i] == 'P')
                     PresentCount++;
            }
            stringstream stream;
            stream << fixed << setprecision(2) << (float(100 *  PresentCount)/countLinesOfFile(Attendance));
            string temp = stream.str();
            command += "'"+temp+"%'";
            command+= "]";  
        }

        command += "]\n";
        command += "th = pdf.font_size\ncol_width = (epw-4)/2\npdf.ln(0.3)\n";
        command += "for row in range(len(data)):\n\tfor datum in range(len(data[row])):\n\t\tif row==0:\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\t\telse:\n\t\t\tpdf.set_text_color(0,0,0)\n\t\t\tpdf.set_font('Arial','',12.0)\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\tpdf.ln(2*th)\npdf.ln(2)";
        command += "\nLine = \"\"\nfor i in range(int(pdf.w-pdf.l_margin)):\n\tfor j in range(10):\n\t\tLine+=\"\" ";
        command += "\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(3, 153, 213)\npdf.cell(epw,0.0,'Have any questions for us or need more information?',align='C')\npdf.ln(0.3)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0,Line, align='C')\npdf.ln(0.22)\npdf.set_text_color(0,0,0)\npdf.cell(epw,0.0,'Email Address For Support   \"ams.software.team@gmail.com\"',align='C')\npdf.ln(0.1)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0,Line,align='C')\npdf.ln(0.5)\npdf.set_text_color(255,0,0)\npdf.set_font('Arial','B',15.0)\npdf.cell(epw,0.0,'Regards, Team AMS.',align='C')\npdf.output('"+DoubleBackslashPath(SemPath) +"\\\\REPORTS\\\\";
        command +=  pdf_name + "','F')\n";
        tempStorage.clear();
        tempStorage = AMS_Path+"\\OTHER\\6MR.py";   // make python File
        writeDataToFile(tempStorage,command);
          
        command.clear();
        command = "python " + AMS_Path + "\\OTHER\\6MR.py" + " 1> " + AMS_Path + "\\OTHER\\output.txt 2>&1";  
        system(command.c_str());//run python file
        
        command.clear();
        command = AMS_Path + "\\OTHER\\output.txt"; // to fetch error file size 
             
        int err = checkEmptyFile(command);
        if(err)
        flag=false;
        else
        flag=true;
        
        remove(command.c_str()); 
        
        command.clear();
        command = AMS_Path+"\\OTHER\\6MR.py"; 
        remove(command.c_str());   //delete python file
        remove(BasicDetails.c_str());  //delete basic_details file
        remove(Name.c_str());  //delete stud_name file
        remove(Attendance.c_str());  //delete stud_att file
     
    } 
    return flag;
  }

  void semesterReportGenerating()   //? generation of semester-wise report   
  {
    tempStorage.clear();
    string temp;
    temp = "SEMESTER ATTENDANCE REPORT";
    tempStorage = " IS BEING GENERATED ";

    int i = 1;
    do
    {
      scrClr(0.5);
      setCursorPos(9, 16);
      SetColor(2);
      cout << temp;
      SetColor(0);
      cout<<tempStorage;
      ShowConsoleCursor(false);
      scrClr(1);
      tempStorage = tempStorage + ".";

      if (i == 4)
      {
        break;
      }
      i++;

    } while (true);

    tempStorage.clear();
    SetColor(0);
    scrClr();
  }

  void makeSemesterReport()
  {
  
    tempStorage.clear();

    command.clear();
    command = SemPath + "\\REPORTS\\basic_details.txt";
    tempStorage = "1) FACULTY NAME : " + FacultyName;
    writeDataToFile(command,tempStorage);
    
    command.clear();
    command = AMS_Path + "\\USER-INFO\\userdetails.txt";
    getDataFromFile(command,department_name,3);
    getDataFromFile(command,HodEmail,4);
    getDataFromFile(command,joining_year,5);

    tempStorage = "2) FACULTY JOINING YEAR : " + joining_year ; // re used as  join_year
  
    command.clear();
    command = SemPath + "\\REPORTS\\basic_details.txt";
    writeDataToFile(command, tempStorage);
    
    tempStorage.clear();
    tempStorage = "3) DEPARTMENT NAME : " + department_name ; // re used as department_name
    command = SemPath + "\\REPORTS\\basic_details.txt";
    writeDataToFile(command,tempStorage);  

    tempStorage.clear();
    tempStorage = "4) COURSE NAME  : " + course_name;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "5) SEMSTER : " + sem;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "6) SUBJECT NAME : " + subject_name;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "7) NUMBER OF STUDENT : " + numberOfstudents;
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "8) REPORT TYPE : SEMESTER REPORT ";
    writeDataToFile(command, tempStorage);

    date.clear();
    time.clear();
    command = SemPath + "\\DAILY-RECORD\\records.txt";  
    getDataFromFile(command,date,1);
    date = date.substr(0,date.find("|"));
    getDataFromFile(command,time,(countLinesOfFile(command)));  // time as last date
    time = time.substr(0,time.find("|"));
    
    tempStorage.clear();
    command.clear();
    tempStorage = "9) REPORT DURATION : " + date + "  -  " + time;
    command = SemPath + "\\REPORTS\\basic_details.txt";
    writeDataToFile(command, tempStorage);

    tempStorage.clear();
    tempStorage = "-: [ Attendance Data ] :- ";
    writeDataToFile(command, tempStorage);

    command.clear();
    command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";
    int j = 1, found_pos, temp_pos, line = countLinesOfFile(command);

    while (j <= line)
    {
      tempStorage.clear();
      found_pos = temp_pos = 0;

      command.clear();
      command = SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt";
      getDataFromFile(command, tempStorage, j);

      found_pos = tempStorage.find("|");
      student_name.clear();
      student_name = tempStorage.substr((found_pos + 1), (tempStorage.find("|", (found_pos + 1)) - (found_pos + 1))); // time re used as student name

      command.clear();
      command = SemPath + "\\REPORTS\\stud_name.txt";
      writeDataToFile(command, student_name);
      j++;
    }

    tempStorage.clear();
    j = 1;
    command = SemPath + "\\DAILY-RECORD\\records.txt"; // path stored in command variable
    line = countLinesOfFile(command);
    while (j <= line)
    {
      tempStorage.clear();
      command.clear();
      command = SemPath + "\\DAILY-RECORD\\records.txt"; // path stored in command variable
      getDataFromFile(command, tempStorage, j);
      command.clear();
      command = SemPath + "\\REPORTS\\stud_att.txt";
      writeDataToFile(command, tempStorage);
      j++;
    }
    
  }

  int confirmSemReport(string d,string d2)
  {
    re_ask_report :
    
    tempStorage.clear();
    scrClr();
    setCursorPos(7,15);
    SetColor(0);
    ShowConsoleCursor(false);
    cout << "SEMESTER REPORT DURATION : " ; 
    SetColor(1);
    cout << d + " - " + d2 << endl;
    SetColor(0);

    ConvertChoiceToINT = YesNoInput("DO YOU WANT TO PROCEED FURTHER ? ", tempStorage); // taking input yes/no

    if (ConvertChoiceToINT == -1) // validate input
    {
      InvalidInputErr(); // error message
      goto re_ask_report;
    }

    return (ConvertChoiceToINT); // returns basic confirmation value yes=1 / no=0
  }

public:

  MODULE_3()
  {
    tempStorage.clear();
    command.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
    pdfName.clear();
    date.clear();
    time.clear();
  }
  
  void semesterReport()
  {
    bool mailTo=false;
    tempStorage.clear();
    date.clear();
    command.clear();
    time.clear();

    if(checkEmptyFile(SemPath + "\\DAILY-RECORD\\records.txt"))
    {

        getDataFromFile(SemPath+"\\DAILY-RECORD\\records.txt",date,1);
        getDataFromFile(SemPath+"\\DAILY-RECORD\\records.txt",time,countLinesOfFile(SemPath+"\\DAILY-RECORD\\records.txt"));
        
        date = date.substr(0,10); //re-used as beginning date
        time = time.substr(0,10); // re-used as semester termination date
    
          if(confirmSemReport(date,time)) // basic confirmation of semester end
          {
                 semesterReportGenerating();
                 makeSemesterReport(); 
                 pdfName += "AMS_REPORT "  + date + "__"+ time + " " + course_name + "_SEM_" + sem + "_" + subject_name;
                 replaceWithHyphen(pdfName);
                 pdfName += ".pdf";
                
                 if(createSemesterReportPDF(SemPath + "\\REPORTS\\basic_details.txt", SemPath + "\\REPORTS\\stud_name.txt", SemPath + "\\REPORTS\\stud_att.txt", pdfName))
                 {   
                   
                     tempStorage.clear();
                     if (MailTo("WOULD YOU LIKE TO SEND THIS REPORT TO H.O.D. ALSO ? ",14))
                     {  
                        
                        command.clear();
                        command = AMS_Path + "\\USER-INFO\\userdetails.txt";
                        getDataFromFile(command,HodEmail,4);
                        tempStorage = FacultyEmail + ",";
                        tempStorage += HodEmail;
                        mailTo=true;
                     }
                     else
                     {
                       tempStorage = FacultyEmail;
                       mailTo=false;
                     }
                     
                     //*threading used for processing email part
                     MODULE_2 MD2;
                     thread t1(&sendToEmail, MD2, "ams.software.team@gmail.com", "Amsisrich@45",tempStorage, "SEMESTER ATTENDANCE REPORT", "Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your Semester Attendance Report.\n\nThank You.\n\n", SemPath + "\\REPORTS\\" + pdfName, pdfName);
                     thread t2(&LoadingProcess, MD2);
                     t1.join(); 
                     t2.join(); 
                     scrClr(); 
                     if(process_flag && email_flag)
                     {
                         Beep(1950, 500);
                         if(mailTo)
                         reportSentSuccessfully(pdfName,HodEmail); 
                         else 
                         reportSentSuccessfully(pdfName); 
                     }
                     else
                     {
                         warnMsg("REPORT COULDN'T BE SENT !", 4, 26, "ERROR CODE : 404/444/599 ", 1, 26);                                  
                     }
                 }
                 else
                 {
                     warnMsg("PDF REPORT COULDN'T BE GENERATED !", 4, 22, "ERROR CODE : 404/417/424 ", 1, 26); 
                 }
                 command.clear();
                 tempStorage.clear();
            }
    
    }
    else
    {
      warnMsg("NO RECORDS EXISTS ! KINDLY TAKE ATTENDANCE FIRST", 2, 19); 
    }

   tempStorage.clear();
   command.clear();
  } 

  void askReportChoice() // ? choice to select report type
  {
    int line;
    reask_report:

    // BOX-UI FOR REPORT CHOICE
    scrClr(0.5);
    setCursorPos(3);
    cout << setw(64) << " WHICH TYPE OF REPORT DO YOU WANT TO GENERATE ? " << endl;
    setCursorPos(2, 23);
    buildVerticalWall(30);

    line = 0;

    while (line < 7)
    {
      setCursorPos(1, 23);
      if (line == 1)
      {
        buildHorizontalWall(30, "1) DATE-WISE REPORT ");
      }
      else if (line == 3)
      {
        buildHorizontalWall(30, "2) STUDENT REPORT ");
      }
      else if (line == 5)
      {
        buildHorizontalWall(30, "3) SEMESTER REPORT ");
      }
      else
        buildHorizontalWall(30, " ");
      line++;
    }
    setCursorPos(1, 23);
    buildVerticalWall(30);

    tempStorage.clear();
    
    askChoice(3,33,tempStorage);
    
    ConvertChoiceToINT = validateString(tempStorage,3,1);
    if (ConvertChoiceToINT == 0)
    {
      goto reask_report;
    }
    else
    {
      CUS_REPORT_CHOICE = (ConvertChoiceToINT);
    }
  }

  void DateWiseReport()   //? Method to create DateWise report 
  {
    if(checkEmptyFile(SemPath + "\\DAILY-RECORD\\records.txt"))
    {
        if (DateInput())
        {
    
            makeDateReport(); // make Report of the corresponding date
            pdfName += "AMS_REPORT_" + course_name + "_SEM_" + sem + "_" + subject_name + "_" + date;
            replaceWithHyphen(pdfName);
            pdfName += ".pdf";
      
            if (createDateWiseReportPDF(SemPath + "\\REPORTS\\fac_data.txt", SemPath + "\\REPORTS\\stud_name.txt", SemPath + "\\REPORTS\\stud_att.txt", pdfName))
            {
              //*threading used for  processing email part
      
              MODULE_3 MD3;
              thread t1(&sendToEmail, MD3, "ams.software.team@gmail.com", "Amsisrich@45", FacultyEmail, "CUSTOMIZE-ATTENDANCE-REPORT", "Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your Customized Attendance Report.\n\nThank You.\n\n", SemPath + "\\REPORTS\\" + pdfName, pdfName);
              thread t2(&LoadingProcess, MD3);
      
              t1.join();    //  used to join the threads
              t2.join();   //  used to join the threads
      
              scrClr();
      
              if (process_flag && email_flag)
              { 
                Beep(1950,500);
                reportSentSuccessfully(pdfName); 
              }
              else
              {
                warnMsg("REPORT COULDN'T BE SENT !", 4, 26, "ERROR CODE : 404/444/599 ", 1, 26); 
              }
            }
            else
            {
              warnMsg("PDF REPORT COULDN'T BE GENERATED !", 4, 22, "ERROR CODE : 404/417/424 ", 1, 26); 
            }
        }
    }
    else
    {
      warnMsg("NO RECORDS EXISTS ! KINDLY TAKE ATTENDANCE FIRST", 2, 19); 
    }

  }

  void studentWiseReport()
  {
    if (checkEmptyFile(SemPath + "\\DAILY-RECORD\\records.txt"))
    {
      if (RollNoInput())
      {
        if (student_email.length() > 29)
        {
          if (studConfirmation(1))
          {
            makeStudentReport(); 

            pdfName += "AMS_REPORT_" + course_name + "_SEM_" + sem + "_" + subject_name + "_Roll_No_" + RoLLNo;
            replaceWithHyphen(pdfName);
            pdfName += ".pdf";

            if (createStudentWiseReportPDF(SemPath + "\\REPORTS\\stud_data.txt", SemPath + "\\REPORTS\\stud_date.txt", SemPath + "\\REPORTS\\stud_time.txt", SemPath + "\\REPORTS\\stud_att.txt", pdfName))
            {
              tempStorage.clear();
              if (MailTo("WOULD YOU LIKE TO SEND THIS REPORT TO STUDENT ? ",18))
              {
                tempStorage = FacultyEmail + ",";
                tempStorage += student_email;
              }
              else
              {
                tempStorage = FacultyEmail;
                student_email.clear();
              }

              //* threading used for  processing email part

              MODULE_3 MD3;
              thread t1(&sendToEmail, MD3, "ams.software.team@gmail.com", "Amsisrich@45", tempStorage, "CUSTOMIZE-ATTENDANCE-REPORT", "Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your Customized Attendance Report.\n\nThank You.\n\n", SemPath + "\\REPORTS\\" + pdfName, pdfName);
              thread t2(&LoadingProcess, MD3);

              t1.join(); 
              t2.join(); 

              scrClr(); 

              if (process_flag && email_flag)
              {  
                Beep(1950,500); 
                reportSentSuccessfully(pdfName, student_email); 
              }
              else
              {
                warnMsg("REPORT COULDN'T BE SENT !", 4, 26, "ERROR CODE : 404/444/599 ", 1, 26); 
              }
            }
            else
            {
              warnMsg("PDF REPORT COULDN'T BE GENERATED !", 4, 22, "ERROR CODE : 404/417/424 ", 1, 26); 
            }
          }
        }
        else
        {
          if (studConfirmation())
          {
            makeStudentReport(); 

            pdfName += "AMS_REPORT_" + course_name + "_SEM_" + sem + "_" + subject_name + "_Roll_No_" + RoLLNo;
            replaceWithHyphen(pdfName);
            pdfName += ".pdf";

            if(createStudentWiseReportPDF(SemPath + "\\REPORTS\\stud_data.txt", SemPath + "\\REPORTS\\stud_date.txt", SemPath + "\\REPORTS\\stud_time.txt", SemPath + "\\REPORTS\\stud_att.txt", pdfName))
            {
              tempStorage.clear();

              if (MailTo("WOULD YOU LIKE TO SEND THIS REPORT TO STUDENT ALSO ? ",14))
              {
                tempStorage = FacultyEmail + ",";
                tempStorage += student_email;
              }
              else
              {
                tempStorage = FacultyEmail;
                student_email.clear();
              }
              //*threading used for  processing email part

              MODULE_3 MD3;
              thread t1(&sendToEmail, MD3, "ams.software.team@gmail.com", "Amsisrich@45", tempStorage, "CUSTOMIZE-ATTENDANCE-REPORT", "Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your Customized Attendance Report.\n\nThank You.\n\n", SemPath + "\\REPORTS\\" + pdfName, pdfName);
              thread t2(&LoadingProcess, MD3);

              t1.join(); 
              t2.join(); 

              scrClr(); 

              if (process_flag && email_flag)
              { 
                Beep(1950,500);
                reportSentSuccessfully(pdfName, student_email); 
              }
              else
              {
                warnMsg("REPORT COULDN'T BE SENT !", 4, 26, "ERROR CODE : 404/444/599 ", 1, 26); 
              }
            }
            else
            {
              warnMsg("PDF REPORT COULDN'T BE GENERATED !", 4, 22, "ERROR CODE : 404/417/424 ", 1, 26);
            }
          }
        }
      }
    }
    else
    {
      warnMsg("NO RECORDS EXISTS ! KINDLY TAKE ATTENDANCE FIRST", 2, 19); 
    }
  }

  ~MODULE_3()
  {
    tempStorage.clear();
    command.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
    pdfName.clear();
    date.clear();
    time.clear();
  }

protected:
  void SetNoObj()
  {
    //*empty defination of pure virtual functions , parent class object can't be created
  }

  //*=============================MEMBERS-FUNCTIONS-END===================================//
};

//*---------------------------STATIC DEFINATIONS-MODULE-3------------------------------/

int MODULE_3::CUS_REPORT_CHOICE; // choice for student/datewise report generation

//-----------------------------------------------------------------------------------/


class MODULE_4 : public MODULE_GENERAL        //? module 4 class
{

  //*=============================DATA-MEMBERS================================//

  private:
    
  public:

  static int MOD_CHOICE;
  
  protected:

  //*=============================DATA-MEMBERS-END================================//

  //*=============================MEMBERS-FUNCTIONS===================================//
  private:
  
  bool passwordAuthetication()  //? password authentication while updating any detail to DB
  { 
    string password,ams_password;
    int counter_pwd = 3;
    getDataFromFile(AMS_Path+"\\LOG-INFO\\logincredentials.txt",ams_password,3);//updated 2->3
    
    re_input_ams_password : 
    scrClr();
    if(counter_pwd)
    {
      ShowConsoleCursor(true);
      setCursorPos(1,27);
      
      cout<<"REMAINING ATTEMPTS : ";
      if(counter_pwd!=1)
      SetColor(2);
      else
      SetColor(4);
      cout<<counter_pwd;
      
      password = getpass("ENTER AMS PASSWORD : ",24);
      if(password!=ams_password)
      { 
        scrClr();
        setCursorPos(9,29);
        SetColor(4);
        ShowConsoleCursor(false);
        cout << "INCORRECT PASSWORD ! " << endl;
        scrClr(2); // screen pause so user can read the whole message conveniently
        SetColor(0);
        counter_pwd--;
        goto re_input_ams_password;
      }
      else
      {
        return(true);
      }
    }
    else
    {
      scrClr();
      setCursorPos(9,14);
      SetColor(4);
      ShowConsoleCursor(false);
      cout << "YOU ARE AN UNAUTHORIZED USER TO MODIFY THIS DATA !!! " << endl;
      scrClr(2.5); 
      exit(0);
      return(false);
    }
  }

  string getpass(const char *prompt,unsigned int pos,bool show_asterisk=true) // ?   password input as *
  {
    const char BACKSPACE=8;
    const char RETURN=13;
    
    string pswd;
    unsigned char ch=0;
    
    setCursorPos(8,pos);
    SetColor(0);
    cout <<prompt;
  
    DWORD con_mode;
    DWORD dwRead;
  
    HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
  
    GetConsoleMode( hIn, &con_mode );
    SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );
  
    while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN)
    {
        if(ch==BACKSPACE)
        {
           if(pswd.length()!=0)
             {  
                if(show_asterisk)
                    cout <<"\b \b";
                pswd.resize(pswd.length()-1);
             }
        }
        else
        {
            pswd+=ch;
            if(show_asterisk)
                cout <<'*';
        }
    }
    cout <<endl;
    ShowConsoleCursor(false);
    return pswd;
  }

  void removeSetUp()  //? function to remove semester setup from DB
  {
    command.clear();
    LIST.clear();
    tempStorage.clear();
    
    tempStorage = "rmdir /s /q " + SemPath; 
    system(tempStorage.c_str());
    command = course_name + " SEM " + sem + " " + subject_name;
    MSG(command," SUCCESSFULLY DELETED.",2,0,19);
    command = course_name + "|" + sem + "|" + subject_name + "|" ;
    replaceWithHyphen(course_name);
    replaceWithHyphen(subject_name);
    command += course_name + "-SEM-" + sem + "-" +subject_name;
    
    for(int LN = 1; LN <= (countLinesOfFile(AMS_Path + "\\OTHER\\semesterRecord.txt"));LN++)
    {      
      tempStorage.clear();
      getDataFromFile(AMS_Path + "\\OTHER\\semesterRecord.txt",tempStorage,LN);
      if(tempStorage!=command)
      LIST.push_back(tempStorage);
    }

    ofstream write(AMS_Path + "\\OTHER\\semesterRecord.txt",ios::trunc);

    if(!write.is_open())
    {
      scrClr();
      setCursorPos(9, 26);
      cout << "DATABASE-ERROR : 201/204 "; // error
      scrClr(2);
      exit(1);
    }
    else
    {

      for(auto i= LIST.begin(); i != LIST.end();i++)
      {
        write<<(*i)<<endl;
      }

      write.close();

    }

    LIST.clear();
    tempStorage.clear();
  }

  int confirmDelete()  //? confirmation for semester delete
  {
      tempStorage.clear();
      int line;
  
    reDeleConfirm:
  
      scrClr(0.5);
      line = 0;
      setCursorPos(2,7);
      buildVerticalWall(61);
      while (line < 7)
      {
        setCursorPos(1, 7);
  
        if (line == 1)
        {
          buildHorizontalWall(61, "          COURSE NAME  :  " + course_name);
        }
        else if (line == 3)
        {
          buildHorizontalWall(61, "          SEMESTER     :  " + sem);
        }
        else if (line == 5)
        {
          buildHorizontalWall(61, "          SUBJECT      :  " + subject_name);
        }
        else
          buildHorizontalWall(61, " ");
        line++;
      }
  
      setCursorPos(1, 7);
      buildVerticalWall(61);
  
      SetColor(1);
      setCursorPos(2, 22);
      cout << "DO YOU WANT TO DELETE THIS SETUP ?";
      SetColor(0);
      setCursorPos(2, 32);
      fflush(stdin);
      ShowConsoleCursor(true);
      cout << "Type : ";
      getline(cin, tempStorage);
      cin.clear();
  
      ShowConsoleCursor(false);
      ConvertChoiceToINT = validateString(tempStorage); // validate input; line re used as return value
  
      if (ConvertChoiceToINT == -1) // validate input
      {
        InvalidInputErr();
        goto reDeleConfirm;
      }
      return (ConvertChoiceToINT); // return confirmation
  }

  int userConfirmation()    //? basic confirmation message box for user after updation
  {
    int line;
    reAsk:
    
    scrClr();
    line = 0;
    setCursorPos(2, 7);
    buildVerticalWall(65);
    while (line < 11)
    {
      setCursorPos(1, 7);
      if (line == 1)
      {
        buildHorizontalWall(65, "FACULTY NAME        :  " + FacultyName);
      }
      else if (line == 3)
      {
        buildHorizontalWall(65, "FACULTY EMAIL       :  " + FacultyEmail);
      }
      else if (line == 5)
      {
        buildHorizontalWall(65, "DEPARTMENT NAME     :  " + department_name);
      }
      else if (line == 7)
      {
        buildHorizontalWall(65, "H.O.D. EMAIL        :  " + HodEmail);
      }
      else if (line == 9)
      {
        buildHorizontalWall(65, "YEAR OF JOINING     :  " + joining_year);
      }
      else
        buildHorizontalWall(65, " ");
      line++;
    }
    setCursorPos(1, 7);
    buildVerticalWall(65);
    SetColor(1);
    setCursorPos(2, 25);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); 
    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reAsk;
    }
    else if (ConvertChoiceToINT)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }

  int userConfirmation(int arg)  //? overloaded version of basic confirmation msg box for user after updation
  {

    reConfirm:
    // cofirmation BOX-UI
    scrClr();

    setCursorPos(3,7);
    buildVerticalWall(65);

    setCursorPos(2, 12);
    cout << "FACULTY NAME " << right << setw(9) << ": " << FacultyName;
    
    setCursorPos(1, 12);
    if (FacultyEmail.length() <= 35)
    {
      cout << "FACULTY E-MAIL " << right << setw(7) << ": " << FacultyEmail;
    }
    else
    {
      int l = 0;
      cout << "FACULTY E-MAIL " << right << setw(7) << ": ";
      while (l < FacultyEmail.length())
      {
        if (l == 38)
        {
          setCursorPos(1,34);
        }
        cout << FacultyEmail[l];
        l++;
      }
    }
    
    setCursorPos(2, 12);
    cout << "DEPARTMENT NAME " << right << setw(6) << ": " << department_name;
    
    setCursorPos(1, 12);
   
    if (HodEmail.length() <= 35)
    {
      cout << "H.O.D. EMAIL " << right << setw(9) << ": " << HodEmail;
    }
    else
    {
      int l = 0;
      cout << "H.O.D. EMAIL " << right << setw(9) << ": ";
      while (l < HodEmail.length())
      {
        if (l == 38)
        {
          setCursorPos(1, 34);
        }
        cout << HodEmail[l];
        l++;
      }
    }
    setCursorPos(1, 12);
    cout << "YEAR OF JOINING " << right << setw(6) << ": " << joining_year;

    setCursorPos(2,7);
    buildVerticalWall(65);

    // message BOX-UI

    setCursorPos(2, 25);
    SetColor(1);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
            
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); 
    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reConfirm;
    }
    else if (ConvertChoiceToINT)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }

  int facConfirmation()  //?  basic confirmation msg for faculty after updation
  {
      int line = 0;
    reInputFacConfirm:
      scrClr();
      line = 0;
      // BOX-UI FOR Details confirmation
      setCursorPos(1, 7);
      buildVerticalWall(65);
      
      while (line < 13)
      {
        setCursorPos(1, 7);
        if (line == 1)
        {
          buildHorizontalWall(65, "FACULTY NAME         :  " + FacultyName);
        }
        else if (line == 3)
        {
          buildHorizontalWall(65, "FACULTY  EMAIL       :  " + FacultyEmail);
        }
        else if (line == 5)
        {
          buildHorizontalWall(65, "COURSE               :  " + course_name);
        }
        else if (line == 7)
        {
          buildHorizontalWall(65, "SEM                  :  " + sem);
        }
        else if (line == 9)
        {
          buildHorizontalWall(65, "SUBJECT              :  " + subject_name);
        }
        else if (line == 11)
        {
          buildHorizontalWall(65, "NUMBER OF STUDENTS   :  " + numberOfstudents);
        }
        else
          buildHorizontalWall(65, " ");
        line++;
      }
      setCursorPos(1, 7);
      buildVerticalWall(65);
      SetColor(1);
      setCursorPos(2, 25);
      cout << "DO YOU CONFIRM THESE DETAILS ?";
      SetColor(0);
      setCursorPos(2, 32);
      fflush(stdin);
      ShowConsoleCursor(true);
      cout << "Type : ";
      getline(cin, tempStorage);
      cin.clear();
      ShowConsoleCursor(false);
      ConvertChoiceToINT = validateString(tempStorage); 
      if (ConvertChoiceToINT == -1)
      {
        InvalidInputErr();
        goto reInputFacConfirm;
      }
      else if (ConvertChoiceToINT)
      {
        return (1);
      }
      else
      {
        return (0);
      }
  }

  int facConfirmation(short int arg) //? overloaded version of basic confirmation msg for faculty after updation
  {

    reConfirm:

    // cofirmation BOX-UI
    scrClr();

    setCursorPos(3,7);
    buildVerticalWall(65);

    setCursorPos(2, 12);
    cout << "FACULTY NAME " << right << setw(9) << ": " << FacultyName;
    setCursorPos(1, 12);
     
    if (FacultyEmail.length() <= 35)
    {
      cout << "FACULTY E-MAIL " << right << setw(7) << ": " << FacultyEmail;
    }
    else
    {
      int l = 0;
      cout << "FACULTY E-MAIL " << right << setw(7) << ": ";
      while (l < FacultyEmail.length())
      {
        if (l == 38)
        {
          setCursorPos(1, 34);
        }
        cout << FacultyEmail[l];
        l++;
      }
    }
    setCursorPos(2, 12);
    cout << "COURSE NAME " << right << setw(10) << ": " << course_name;
    setCursorPos(1, 12);
    cout << "SEMESTER " << right << setw(13) << ": " << sem;
    setCursorPos(1, 12);
    cout << "SUBJECT " << right << setw(14) << ": " << subject_name;
    setCursorPos(1, 12);
    cout << "NUMBER OF STUDENTS " << right << setw(3) << ": " << numberOfstudents;

    setCursorPos(2,7);
    buildVerticalWall(65);

    // message BOX-UI

    setCursorPos(3, 25);
    SetColor(1);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); 
    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reConfirm;
    }
    else if (ConvertChoiceToINT)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }

  int stdConfirmation() //? basic confirmation message for student after updation
  {
   
    int line = 0;
    reInputStdConfirm:
    scrClr();
    line = 0;
    // BOX-UI FOR Details confirmation
    setCursorPos(4, 7);
    buildVerticalWall(65);
    while (line < 7)
    {
      setCursorPos(1, 7);
      if (line == 1)
      {
        buildHorizontalWall(65, "ROLL NUMBER         :  " + RoLLNo);   
      }
      else if (line == 3)
      {
        buildHorizontalWall(65, "STUDENT NAME        :  " + student_name);
      }
      else if (line == 5)
      {
        buildHorizontalWall(65, "STUDENT E-MAIL      :  " + student_email);
      }
      else
        buildHorizontalWall(65, " ");
      line++;
    }
    setCursorPos(1, 7);
    buildVerticalWall(65);
    SetColor(1);
    setCursorPos(3, 25);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); 
    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reInputStdConfirm;
    }
    else if (ConvertChoiceToINT)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }

  int stdConfirmation(int argc) //? overloaded version basic confirmation message for student after updation
  {
    reConfirm:
    scrClr();
    // BOX-UI FOR STUDENT INFO CONFIRMAT
    setCursorPos(4,7);
    buildVerticalWall(65);

    setCursorPos(2, 12);
    cout << "STUDENT ROLL NUMBER " << right << setw(4) << ": " << RoLLNo;
    setCursorPos(1, 12);
    cout << "STUDENT NAME " << right << setw(11) << ": " << student_name;
    setCursorPos(1, 12);
    if (student_email.length() <= 35)
    {
      cout << "STUDENT E-MAIL " << right << setw(9) << ": " << student_email;
    }
    else
    {
      int l = 0;
      cout << "STUDENT E-MAIL " << right << setw(9) << ": ";
      while (l < student_email.length())
      {
        if (l == 38)
        {
          setCursorPos(1, 34);
        }
        cout << student_email[l];
        l++;
      }
    }

    setCursorPos(2,7);
    buildVerticalWall(65);

    tempStorage.clear();
    setCursorPos(2, 25);
    SetColor(1);
    cout << "DO YOU CONFIRM THESE DETAILS ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage); 
    if (ConvertChoiceToINT == -1) 
    {
      InvalidInputErr(); 
      goto reConfirm;
    }
    return (ConvertChoiceToINT);
  }

  int confirmation() //? after sem and course selecting first confirmation box (faculty details)
  {
    int line;

    reConfirm:
    
    tempStorage.clear(); 

    line=0;
    // cofirmation BOX-UI
    scrClr(0.5);
    setCursorPos(2,7);
    buildVerticalWall(65);

    setCursorPos(2, 12);
    getDataFromFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt",FacultyName,1);
    cout << "FACULTY NAME " << right << setw(9) << ": " << FacultyName;
    setCursorPos(1, 12);
    getDataFromFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt",FacultyEmail,2);
    cout << "FACULTY E-MAIL " << right << setw(7) << ": " << FacultyEmail;
    setCursorPos(2, 12);
    cout << "COURSE NAME " << right << setw(10) << ": " << course_name;
    setCursorPos(1, 12);
    cout << "SEMESTER " << right << setw(13) << ": " << sem;
    setCursorPos(1, 12);
    cout << "SUBJECT " << right << setw(14) << ": " << subject_name;
    setCursorPos(1, 12);
    getDataFromFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt",numberOfstudents,6);
    cout << "NUMBER OF STUDENTS " << right << setw(3) << ": " << numberOfstudents;

    // message BOX-UI

    setCursorPos(2,7);
    buildVerticalWall(65);

    tempStorage.clear(); // clear variable for re-using
    SetColor(1);
    setCursorPos(2, 23);
    cout << "DO YOU WANT TO PROCEED FURTHER ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage); // validate input // line re used as return value
    if (ConvertChoiceToINT == -1)                     // validate input
    {
      InvalidInputErr();
      goto  reConfirm;
    }

    return (ConvertChoiceToINT); 
  }

  void semDetailModChoice() //? Ask Data Input Choice for semester modification
  {
    scrClr(0.5);
    setCursorPos(2);
    askCourseChoice(); 
    askSemsterChoice();
      
    if(askSubjectChoice())
    {
      getDataFromFile(SemPath + "\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt",command,2);
      bool flag = ( command.length()<=30 ) ? proceedFurther(1) : confirmation();
    
      if(flag)
      {
        int line = 0;
        reask_semMod:
            
        // BOX-UI FOR INPUT CHOICE
        scrClr(0.5);
        setCursorPos(3,25);
        cout << " WHAT DO YOU WANT TO MODIFY ? " << endl;
        setCursorPos(2,24);
        buildVerticalWall(30);
        line = 0;
        while (line < 5)
        {
             setCursorPos(1, 24);
             if (line == 1)
             {
               buildHorizontalWall(30, "1) FACULTY DETAILS ");
             }
             else if (line == 3)
             {
               buildHorizontalWall(30, "2) STUDENT DETAILS ");
             }
             else
               buildHorizontalWall(30, " ");
             line++;
        }
        setCursorPos(1, 24);
        buildVerticalWall(30);
        askChoice(3, 33, tempStorage);
        ConvertChoiceToINT = validateString(tempStorage,2,1);
        if (ConvertChoiceToINT == 0)
        {
          goto reask_semMod;
        }  
        if (ConvertChoiceToINT == 1)
        {
           facDetailModChoice();
        }
        else if (ConvertChoiceToINT == 2)
        {
          RollNoInput();
          flag = ( student_email.length() <= 30 ) ? studConfirmation() : studConfirmation(1);
          if(flag)
          studDetailModChoice();  
        }
      }
    }
    
  }

  void userDetailModChoice() //? Ask Data Input Choice for user details modification
  {
    int line;
    reask_userMod:

    line = 0;

    // BOX-UI FOR INPUT CHOICE
    scrClr(0.5);
    setCursorPos(3,22);
    cout << " WHICH DETAIL DO YOU WANT TO MODIFY ? " << endl;
    setCursorPos(2,24);
    buildVerticalWall(30);
    line = 0;
    while (line < 9)
    {
      setCursorPos(1, 24);
      if (line == 1)
      {
        buildHorizontalWall(30, "1) FACULTY NAME ");
      }
      else if (line == 3)
      {
        buildHorizontalWall(30, "2) FACULTY EMAIL ");
      }
      else if (line == 5)
      {
        buildHorizontalWall(30, "3) H.O.D. EMAIL ");
      }
      else if (line == 7)
      {
        buildHorizontalWall(30, "4) DEPARTMENT NAME ");
      }
      else
        buildHorizontalWall(30, " ");
      line++;
    }
    setCursorPos(1, 24);
    buildVerticalWall(30);
    askChoice(3, 33, tempStorage);
    
    ConvertChoiceToINT = validateString(tempStorage,4,1);
    if (ConvertChoiceToINT == 0)
    {
      goto reask_userMod;
    }

    updateUserDetail(ConvertChoiceToINT); 
    
  }
  
  void update(char mode)  //? generalize-function-to-update-user-faculty-student-data
  {

    bool flag;
    if(mode == 'A')
    {
      flag = (FacultyEmail.length() > 35 || HodEmail.length() > 35 ) ? userConfirmation(1) : userConfirmation();
      if(flag)
      {
        if(passwordAuthetication())
        {
          ofstream write(AMS_Path + "\\USER-INFO\\userdetails.txt",ios::trunc);
          if(!write.is_open())
          {
            scrClr();
            setCursorPos(9, 26);
            cout << "DATABASE-ERROR : 201/204 "; 
            scrClr(2);
            exit(1);
          }
          else
          {
            

            tempStorage.clear();
            tempStorage = FacultyEmail;
            
            write << FacultyName << endl;
            write << FacultyEmail<< endl;
            write << department_name << endl;
            write << HodEmail << endl;
            write << joining_year << endl;
            write.close();
            
            /************ user email update code ****************/

            command.clear();
            string temp; // as faculty user email
            date.clear(); // as username
            time.clear(); // as password

            command = AMS_Path + "\\LOG-INFO\\logincredentials.txt";
            getDataFromFile(command,temp,1); // get user email
            getDataFromFile(command,date,2); //get username
            getDataFromFile(command,time,3); //get password

            ofstream write(command.c_str(),ios::trunc);
            if(!write.is_open())
            {
              scrClr();
              setCursorPos(9, 26);
              cout << "DATABASE-ERROR : 201/204 "; 
              scrClr(2);
              exit(1);
            }
            else
            {
              temp = tempStorage; 
              write << temp << endl;
              write << date << endl;
              write << time << endl;
            }

            /************ user email update code end ****************/
            
            warnMsg("USER DETAILS HAVE BEEN SUCCESSFULLY UPDATED.",2,18);
            tempStorage.clear();
            date.clear(); // as username
            time.clear(); // as password
          }
        }
      }
    }
    else if(mode=='B')
    {
      flag = (FacultyEmail.length()<=35 ) ? facConfirmation() : facConfirmation(1); 
      if(flag)
      {   
        if(passwordAuthetication())
        {
          ofstream write(SemPath+"\\FAC-STUD-DETAILS\\faculty-sem-" + sem + ".txt",ios::trunc);
          if(!write.is_open())
          {
            scrClr();
            setCursorPos(9, 26);
            cout << "DATABASE-ERROR : 201/204 "; 
            scrClr(2);
            exit(1);
          }
          else
          { 
            write << FacultyName << endl;
            write << FacultyEmail << endl;
            write << course_name << endl;
            write << sem << endl;
            write << subject_name << endl;
            write << numberOfstudents << endl;
            write.close();
            warnMsg("FACULTY DETAILS HAVE BEEN SUCCESSFULLY UPDATED.",2,16); 
          }
        } 
      }
    }
    else if(mode=='C')
    {
      flag = ( student_email.length()<=35 ) ? stdConfirmation() : stdConfirmation(1);
      if(flag)
      {
        if(passwordAuthetication())
        {
          command.clear();
          date.clear(); 
          buffer.clear();
          time.clear();
          time = RoLLNo + "|" + student_name + "|" + student_email;// modified student
          command =  SemPath + "\\FAC-STUD-DETAILS\\student-sem-" + sem + ".txt"; //path to file update
          int line=1,TotalLine=countLinesOfFile(command);

          for(line=1;line<=TotalLine;line++)
          { 
            date.clear();
            tempStorage.clear();
            getDataFromFile(command,tempStorage,line); 
            date = tempStorage;   // date backup as file single record string
            tempStorage =  tempStorage.substr(0,tempStorage.find("|")); 
            if(tempStorage==RoLLNo)
            {
               buffer.push_back(time);
            }
            else
            {
               buffer.push_back(date);
            }
          }

          ofstream write(command,ios::trunc);
          if(!write.is_open())
          {
            scrClr();
            setCursorPos(9, 26);
            cout << "DATABASE-ERROR : 201/204 ";
            scrClr(2);
            exit(1);
          }
          else
          {
            for(auto i= buffer.begin(); i != buffer.end();i++) 
            {
              write<<(*i)<<endl;
            }
            write.close();
            warnMsg("STUDENT DETAILS HAVE BEEN SUCCESSFULLY UPDATED.",2,16);
          }
        }
      }
    }
        
  }
  
  bool alreadyUpdatedDetail(string &one,string &two)   //? to check updated details that is already there in file
  {
    if(one==two)
    {
      warnMsg("DETAIL HAS BEEN ALREADY UPDATED ! ",2,25);
      return(true);
    }
    else
    {
      two = one ;  // copy unique data
      one.clear(); // tempStorage clear
      return(false);
    }
  }
  
  void updateUserDetail(int ch)  //? user detail updation choice
  {
    tempStorage.clear();

    getDataFromFile(AMS_Path + "\\USER-INFO\\userdetails.txt",FacultyName,1);
    getDataFromFile(AMS_Path + "\\USER-INFO\\userdetails.txt",FacultyEmail,2);
    getDataFromFile(AMS_Path + "\\USER-INFO\\userdetails.txt",department_name,3);
    getDataFromFile(AMS_Path + "\\USER-INFO\\userdetails.txt",HodEmail,4);
    getDataFromFile(AMS_Path + "\\USER-INFO\\userdetails.txt",joining_year,5);

    switch(ch)
    {
      case 1:
      {
        if(singleConfirmation(AMS_Path + "\\USER-INFO\\userdetails.txt","FACULTY NAME   :  ",ch))
        {
          UpdateName(tempStorage,"ENTER FACULTY NAME"); 
          if(!alreadyUpdatedDetail(tempStorage,FacultyName))
          update('A');
        }
        break;
      }
      case 2:
      {
        
        if(singleConfirmation(AMS_Path + "\\USER-INFO\\userdetails.txt","FACULTY E-MAIL",ch))
        {
          UpdateEmail(tempStorage,"ENTER FACULTY E-MAIL");
          if(!alreadyUpdatedDetail(tempStorage,FacultyEmail))
          update('A');
        }
        break;
      }
      case 3:
      {
        if(singleConfirmation(AMS_Path + "\\USER-INFO\\userdetails.txt","H.O.D. E-MAIL",(ch+1)))
        {
          
          UpdateEmail(tempStorage,"ENTER H.O.D. E-MAIL");
          if(!alreadyUpdatedDetail(tempStorage,HodEmail))
          update('A');
        }
        break;
      }
      case 4:
      {
        if(singleConfirmation(AMS_Path + "\\USER-INFO\\userdetails.txt","DEPARTMENT NAME  : ",(ch-1)))
        {
         
          UpdateName(tempStorage,"ENTER DEPARTMENT NAME"); 
          if(!alreadyUpdatedDetail(tempStorage,department_name))
          update('A');
        }
        break;
      }

      default:
      break;
    }

  }

  int singleConfirmation(string path , string display , int choice)
  {
    int line;
    reAsk:
    scrClr(0.5);
    line = 0;
    command.clear();
    
    if(choice == 1 || choice == 3)
    {
      setCursorPos(5, 7);
      buildVerticalWall(65);
      while (line < 3)
      {
        setCursorPos(1, 7);
        if (line == 1)
        {
          getDataFromFile(path , command, choice);
          buildHorizontalWall(65, display + command);
        }
        else
        {
          buildHorizontalWall(65, " ");
        }
        line++;
      }
      setCursorPos(1, 7);
      buildVerticalWall(65);
    }
    else
    {
      command.clear();
      setCursorPos(5, 7);
      getDataFromFile(path , command, choice);
      if (command.length() <= 30)
      {
        buildVerticalWall(65);
        while (line < 3)
        {
          setCursorPos(1, 7);
          if (line == 1)
          {
            getDataFromFile(path , command, choice);
            buildHorizontalWall(65, display + "  :  " + command);
          }
          else
          {
            buildHorizontalWall(65, " ");
          }
          line++;
        }
        setCursorPos(1, 7);
        buildVerticalWall(65);
      }
      else
      {
        int l = 0;
        cout << display << right << setw(5) << "  :  ";
        while (l < command.length())
        {
          if (l == 35)
          {
            setCursorPos(1, 39);
          }
          cout << command[l];
          l++;
        }
      }
      command.clear();
    }

    
    SetColor(1);
    setCursorPos(3, 21);
    cout << "DO YOU WANT TO MODIFY THIS DETAIL ?";
    SetColor(0);
    setCursorPos(2, 32);
    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage);
    cin.clear();
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(tempStorage);

    if (ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reAsk;
    }
          
    return(ConvertChoiceToINT);
  }

  void facDetailModChoice()  //? ask choice to update faculty details 
  {
    int line = 0;
    reask_semMod:
    
    // BOX-UI FOR INPUT CHOICE
    scrClr(0.5);
    setCursorPos(3,22);
    cout << " WHICH DETAIL DO YOU WANT TO MODIFY ? " << endl;
    setCursorPos(2,24);
    buildVerticalWall(30);
    line = 0;
    while (line < 5)
    {
      setCursorPos(1, 24);
      if (line == 1)
      {
        buildHorizontalWall(30, "1) FACULTY NAME ");
      }
      else if (line == 3)
      {
        buildHorizontalWall(30, "2) FACULTY EMAIL ");
      }
      else
        buildHorizontalWall(30, " ");
      line++;
    }
    setCursorPos(1, 24);
    buildVerticalWall(30);
    askChoice(3, 33, tempStorage);
    
    ConvertChoiceToINT = validateString(tempStorage,2,1);
    if (ConvertChoiceToINT == 0)
    {
      goto reask_semMod;
    }
    
    facDetailMod(ConvertChoiceToINT);
  }

  void facDetailMod(short int choice)
  {   
    tempStorage.clear();
    
    switch (choice)
    {
      case 1:
      {
        
          UpdateName(tempStorage,"ENTER FACULTY NAME");
          if(!alreadyUpdatedDetail(tempStorage,FacultyName))
          update('B');
           
        break;
      }
      case 2:
      {
        
          UpdateEmail(tempStorage,"ENTER FACULTY E-MAIL");
          if(!alreadyUpdatedDetail(tempStorage,FacultyEmail))
          update('B');  
     
        break;
      }
      default:
      break;
    }

  }

  void studDetailModChoice() //? ask student detail updation choice 
  {
    int line = 0;
    reask_semMod:
    
    
    // BOX-UI FOR INPUT CHOICE
    scrClr(0.5);
    setCursorPos(3,22);
    cout << " WHICH DETAIL DO YOU WANT TO MODIFY ? " << endl;
    setCursorPos(2,24);
    buildVerticalWall(30);
    line = 0;
    while (line < 5)
    {
      setCursorPos(1, 24);
      if (line == 1)
      {
        buildHorizontalWall(30, "1) STUDENT NAME ");
      }
      else if (line == 3)
      {
        buildHorizontalWall(30, "2) STUDENT EMAIL ");
      }
      else
        buildHorizontalWall(30, " ");
      line++;
    }
    setCursorPos(1, 24);
    buildVerticalWall(30);
    askChoice(3, 33, tempStorage);
  
    ConvertChoiceToINT = validateString(tempStorage,3,1);
    if (ConvertChoiceToINT == 0)
    {
      goto reask_semMod;
    }
  
    studDetailMod(ConvertChoiceToINT);
    
  }

  void studDetailMod(int choice)
  {
    tempStorage.clear();
    switch (choice)
    {
      case 1:
      {
        UpdateName(tempStorage,"ENTER STUDENT NAME");
        if(!alreadyUpdatedDetail(tempStorage,student_name));
        update('C');
        break;
      }
      case 2:
      {
        UpdateEmail(tempStorage,"ENTER STUDENT E-MAIL");
        if(!alreadyUpdatedDetail(tempStorage,student_email));
        update('C');
        break;
      }
    
      default:
      break;
    }
  }
  
  
  public:

  MODULE_4()  
  {

    tempStorage.clear();
    command.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
    
    FacultyName.clear();
    FacultyEmail.clear();

    student_name.clear();
    student_email.clear();
    RoLLNo.clear();
    course_name.clear();
    sem.clear();
    subject_name.clear();

    date.clear();
    time.clear();

  }

  void modDataChoice() 
  {
    int line = 0;
    reask_mod:
    
    // BOX-UI FOR INPUT CHOICE
    scrClr(0.5);
    setCursorPos(3,27);
    cout << " WHAT DO YOU WANT TO DO ? " << endl;
    setCursorPos(2,21);
    buildVerticalWall(36);
    line = 0;
    while (line < 7)
    {
      setCursorPos(1, 21);
      if (line == 1)
      {
        buildHorizontalWall(36, "1) DETAILS MODIFICATION ");
      }
      else if (line == 3)
      {
        buildHorizontalWall(36, "2) AMS SETUP DELETION ");
      }
      else if (line == 5)
      {
        buildHorizontalWall(36, "3) GENERATE .CSV FILE ");
      }
      else
        buildHorizontalWall(36, " ");
      line++;
    }
    setCursorPos(1, 21);
    buildVerticalWall(36);
    askChoice(3, 33, tempStorage);
  
    ConvertChoiceToINT = validateString(tempStorage,3,1);
    if (ConvertChoiceToINT == 0)
    {
      goto reask_mod;
    }
    
    MOD_CHOICE = (ConvertChoiceToINT);
  }

  void modDetailChoice()  
  {
    int line = 0;
    reask_userMod:
    
    // BOX-UI FOR INPUT CHOICE
    scrClr(0.5);
    setCursorPos(3,21);
    cout << " WHICH DETAILS DO YOU WANT TO MODIFY ? " << endl;
    setCursorPos(2,24);
    buildVerticalWall(30);
    line = 0;
    while (line < 5)
    {
      setCursorPos(1, 24);
      if (line == 1)
      {
        buildHorizontalWall(30, "1) USER DETAILS ");
      }
      else if (line == 3)
      {
        buildHorizontalWall(30, "2) SEMESTER DETAILS ");
      }
      else
        buildHorizontalWall(30, " ");
      line++;
    }
    setCursorPos(1, 24);
    buildVerticalWall(30);
    askChoice(3, 33, tempStorage);
  
    ConvertChoiceToINT = validateString(tempStorage,2,1);
    if (ConvertChoiceToINT == 0)
    {
      goto reask_userMod;
    }

    if(ConvertChoiceToINT == 1)
    {
      userDetailModChoice();
    }
    else if (ConvertChoiceToINT == 2)
    {
      semDetailModChoice();
    }

  }

  void deleteSetUp()
  {
   if(passwordAuthetication())
   {
       if (confirmDelete()) 
       {
           removeSetUp();
       }
   }

  }

  void generateCSV() //? function to generate .CSV file for student data
  {  
    bool flag=false;
    string filename = "\\AMS ";
    filename += course_name + " SEM " + sem + " " + subject_name + ".csv";
    command.clear();
    command = DesktopPath + filename;
    if(!fileExists(command))
    {
       flag=true;
       tempStorage.clear();
       int i;
       writeDataToFile(DesktopPath+filename,"Roll Number,Name,Email"); //title added in csv
       for(i=1;i<=countLinesOfFile(SemPath+"\\FAC-STUD-DETAILS"+"\\student-sem-"+sem+".txt");i++)
       { 
         tempStorage.clear();
         getDataFromFile(SemPath+"\\FAC-STUD-DETAILS"+"\\student-sem-"+sem+".txt",tempStorage,i);
         replace(tempStorage.begin(), tempStorage.end(), '|', ',');
         writeDataToFile(DesktopPath+filename,tempStorage);
       }
       tempStorage.clear();
    }
    else
    {
      flag=false;
    }
  
  
  if(flag)
  {
      tempStorage = course_name + " SEM " + sem + " " + subject_name + ".CSV ";
      warnMsg(tempStorage,2,22, " GENERATED SUCCESSFULLY IN DESKTOP->AMS FOLDER",0, 17); 
  }
  else
  {
    tempStorage = course_name + " SEM " + sem + " " + subject_name + ".CSV ";
    warnMsg(tempStorage,2,22, " IS ALREADY EXISTS IN DESKTOP->AMS FOLDER",0, 18); 
  }
  command.clear();
  } 

  ~MODULE_4()
  {
    tempStorage.clear();
    command.clear();
    buffer.clear();
    LIST.clear();
    DATA.clear();
    FacultyName.clear();
    FacultyEmail.clear();
    course_name.clear();
    sem.clear();
    subject_name.clear();
    student_name.clear();
    student_email.clear();
    RoLLNo.clear();
    numberOfstudents.clear();
    date.clear();
    time.clear();

  }

  protected:
  
  void SetNoObj()
  {
    //* empty defination of pure virtual functions, parent class object can't be created
  }
   //*=============================MEMBERS-FUNCTION-END================================//
};

//*---------------------------STATIC DEFINATIONS-MODULE-4------------------------------/

int MODULE_4::MOD_CHOICE; //*  MODIFICATION OPTION-CHOICE 

//*-----------------------------------------------------------------------------------/




//**************************************   MODULES-END   ***************************************************/

//? ****************************** GENERAL FUNCTIONS ***********************************/

//? ********************************************************************************/


int main(int argc, char *argv[])
{
  //* jay swaminrayan *//
  //* jay ganeshay namh *//
  //* jay kashtbhanjan dev *//
  //system("cls");
  //if( (!strcmp(argv[1],"JonSnow")) && (argc == 2 ) )
  //{
    APP A;
    bool loop = true; // set true to run app by 1 time
    signal(SIGINT, signal_callback_handler);

    while (loop)
    {
          
          A.startApp();          // start app
          A.scrClr();            // clear screen
          A.setCursorPos(2, 10); // set cursor position
      
      switch (APP::MODULE_CHOICE) // module choice asking
      {

              case 1:
              {
                  MODULE_1 MD1;
                  MD1.askFacDetails(); // ask faculty details
                  MD1.getDataInputOfstudent(); //get data input of student like name email
                  MD1.SetUpSucceed(); // succeed msg print
                  break;
              }
              case 2:
              {
                MODULE_2 MD2;
                if (MD2.checkDB()) // check database
                {
                  MD2.askCourseChoice();  // ask course
                  MD2.askSemsterChoice(); // ask semester
                  if (MD2.askSubjectChoice()) // ask subject
                  {
                    if (MD2.proceedFurther()) // confirmation for right choice
                    {
                      if (MD2.confirmTodayAttendance()) // check if already taken for today
                      {
                        MD2.MonthlyReport();
                        reask:
                        MD2.AttendanceOptionWindow(); // ask easy option for attendance taking method
                        if (MD2.takeAttendance(MODULE_2::AT_OPTION_CHOICE)) // take attendance
                        {
                          MD2.AttendanceTakenSuccessfully(); // finally taken
                        }
                        else
                        {
                          goto reask; // if option change automatically at last step
                        }
                      }
                    }
                  }
                }
              break; // coding /*/
              }
              case 3:
              {
                MODULE_3 MD3;
                if (MD3.checkDB()) 
                {
                  MD3.askCourseChoice();  
                  MD3.askSemsterChoice(); 
                  if(MD3.askSubjectChoice()) 
                  {
                    if(MD3.proceedFurther(0))     // confirm taking attendance or Return to Home Screen
                    {
                      MD3.askReportChoice();      // select datewise/studentwise report generation
                      switch(MODULE_3::CUS_REPORT_CHOICE)
                      {
                          case 1:
                          {
                            MD3.DateWiseReport();
                            break;
                          }
                          case 2:
                          {
                            MD3.studentWiseReport();
                            break;
                          }
                          case 3:
                          {
                            MD3.semesterReport();
                            break;
                          }
                          default:
                          {
                            break;
                          }
                      }
                    }
                  }
                }
              break;
              }
              case 4:
              {
                MODULE_4 MD4;
                if(MD4.checkDB()) 
                {
                      MD4.modDataChoice();
                      switch (MODULE_4::MOD_CHOICE)
                      {
                             case 1:
                             {
                                  MD4.modDetailChoice();
                                  break;
                             }
                             case 2:
                             {
                                  MD4.askCourseChoice(); 
                                  MD4.askSemsterChoice(); 
                                  MD4.askSubjectChoice(); 
                                  MD4.deleteSetUp();
                               break;
                             }
                             case 3:
                             { 
                                  MD4.askCourseChoice(); 
                                  MD4.askSemsterChoice(); 
                                  MD4.askSubjectChoice(); 
                                  MD4.generateCSV();
                               break;
                             }
                             default:
                             {
                               break;
                             }
                      }
                }
              break;
              }

              case 5:
              { 
                loop = false; // exit Application
                break;
              }

              default:
              {
                A.setCursorPos(9, 24);cout << "ERROR CODE : 421/422/424 : APPLICATION CRASHED !!!" << endl;A.scrClr(3);exit(1);break;// exceptional  case
              } 

      }

       A.scrClr(); 
  }

  //} 
  return(EXIT_SUCCESS);
}