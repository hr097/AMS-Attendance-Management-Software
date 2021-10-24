#include<iostream>     // * c++ code style use
#include<stdio.h>     //* for c style code use 
#include<stdlib.h>   // * standard library like dynamic memory allocation and exit macros and other.. 
#include<conio.h>   // *  console input output
#include<windows.h> // * windows console related functions handle
#include<unistd.h> // * for sleep function
#include<iomanip> // * for manipulator
#include<cwchar>  //*for console font purpose 
#include<string.h> //* for fonts purpose making is big-small and bold
#include<stdbool.h> // * boolean operation
#include<math.h> //* math operations

#ifndef _WIN32_WINNT 
  #define _WIN32_WINNT 0x0601
  #include<wincon.h>
  #include<string>

 // #endif  // user 1 

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

#ifndef UNICODE  
  typedef std::string String; 
#else
  typedef std::wstring String; 
#endif

using namespace std; // namespace for  resolving name coflicts

/*******************GENERAL FUNCTION CLASS THAT ARE USED BY GLOBAL SCOPE FUNCTIONS********************************/
class GENERAL_INIT
{

public:

static int MODULE_CHOICE;

void setCursorPos(int x, int y=0) //IMPORTANT : *relative position is set
{
  
  //*vertical lines space 
  
  //? FULL SCREEN MIN Vertical= Horizontal= SET THAT ACCORDING TO GET_DESKTOP_RESOLUTION
  
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
void ShowConsoleCursor(bool showFlag) //* for hiding the cursor just  set showFlag = false(bool value)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void scrClr(float i=0.0) //*for clearing screen afer some time
{
  //*by default set to zero with default arguements
  sleep(i); // * going in sleep mode
  system("cls"); // * clear screen
}

void exitApp(int status=0) // exit program with status 0=success, 1=failure
{
  cout<<"PRESS ANY KEY TO EXIT...";
  ShowConsoleCursor(false);
  getch();
  exit(status);
}


void buildVerticalWall(int briks)
{ cout<<"*";
  while(briks>0){cout<<"-";briks--;}
  cout<<"*";
}
void buildHorizontalWall(int endBrick,string data)
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

void startApp()
{
  if(MODULE_CHOICE==0)
  {
    initApp();
    MODULE_CHOICE = askChoice();
  }
  else
  {
    MODULE_CHOICE = askChoice();
  }
  
}

private:

void initApp()
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

        system("color F0"); //set while background
 
}

int askChoice()
{ 
  
  re_ask:
  mainTitleOFapplication();
  bool match = false;
  float operationChoice;
  //setCursorPos(2,25);
  // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  // SetConsoleTextAttribute(hConsole,10);
  // cout<<"WHAT DO YOU WANT TO DO ?"<<endl;
  // SetConsoleTextAttribute(hConsole,240);
  setCursorPos(2,15);

  buildVerticalWall(43);
  int line=0;
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
  do
  {

   setCursorPos(2,30);
   cout<<"CHOICE : ";
   cin>>operationChoice;

   if (!cin)
   {
       cin.clear();
       cin.ignore(80,'\n');
   }
  else if(operationChoice>=101&&operationChoice<=110)
  {
      match=true;
  }
  if(operationChoice<1||operationChoice>5)
  {        
     scrClr();
     setCursorPos(2,24);
     cout<<"INVALID CHOICE ENTERTED !"<<endl;
     setCursorPos(2,20);
     cout<<"PLEASE RE-ENTER YOUR CHOICE CORRECTLY !"<<endl;
     scrClr(1);
     goto re_ask;
  }
  operationChoice =(int)floor(operationChoice);  // * for stop looping error float
  if(operationChoice==1||operationChoice==2||operationChoice==3||operationChoice==4||operationChoice==5)
  {break;}
}while(match!=true);

return(operationChoice);
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
  std::wcscpy(cfi.FaceName, L"JetBrains Mono ExtraBold"); // Choose your font BY SETTING FONT FACE
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); //pass reference of that structure to OUTPUT HANDLE 

}

void mainTitleOFapplication()
{  
   setCursorPos(1);
   cout<<setw(55)<<" || ATTENDANCE MANAGEMENT SYSTEM ||"<<endl;
}

};

//---------STATIC DEFINATIONS-----------//
 int GENERAL_INIT::MODULE_CHOICE=0;
//-------------------------------------//

/****************************GENERAL-FUNCTION-CLASS-END***************************/
/****************************ATTENDANCE_MODULE************************************/

class MODULE 
{
  
  public:
  MODULE(int Selectmodule)
  {

   if(Selectmodule==1)
   MODULE1();
   else if(Selectmodule==2)
   MODULE2();
   else if(Selectmodule==3)
   MODULE3();
   else if(Selectmodule==4)
   MODULE4();
  }
  MODULE()
  {

  }
  ~MODULE()
  {

  }
  private:

  void MODULE1()
  {
  cout<<"MODULE 1 WILL WORK HERE REMOVE THIS COMMENT "<<endl<<"\n\tAFTER YOU START WORK BUT I WILL EXPLAIN YOU TOMO HOW YOU SHOULD WORK"<<endl;
  }
  void MODULE2()
  {
     cout<<"MODULE 2 WILL WORK HERE REMOVE THIS COMMENT "<<endl<<"\n\tAFTER YOU START WORK BUT I WILL EXPLAIN YOU TOMO HOW YOU SHOULD WORK"<<endl;
  }
  void MODULE3()
  {
     cout<<"MODULE 3 WILL WORK HERE REMOVE THIS COMMENT "<<endl<<"\n\tAFTER YOU START WORK BUT I WILL EXPLAIN YOU TOMO HOW YOU SHOULD WORK"<<endl;
  }
  void MODULE4()
  {
     cout<<"MODULE 4 WILL WORK HERE REMOVE THIS COMMENT "<<endl<<"\n\tAFTER YOU START WORK BUT I WILL EXPLAIN YOU TOMO HOW YOU SHOULD WORK"<<endl;
  }

};

/****************************ATTENDANCE_MODULE************************************/

int main()
{
    //jay swaminrayan
    //jay ganeshay namh
    bool loop=true;

    while(loop)
    {

    GENERAL_INIT APP;
    APP.startApp();
    
    if(GENERAL_INIT::MODULE_CHOICE!=5)
    {
      APP.scrClr();
      APP.setCursorPos(2,10);
      MODULE SELECT(GENERAL_INIT::MODULE_CHOICE);
      APP.scrClr(2);
    }
    else
    loop=false;

    

    }
    
    //APP.setCursorPos(14,25); // !WILL UNCOMMENT AT LAST AFTER DISCUSSION
    //APP.exitApp(0);
    return 0;
}