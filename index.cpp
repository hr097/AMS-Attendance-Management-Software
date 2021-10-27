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

#ifndef _WIN32_WINNT  //*if that macro not exist then condtional compila6ion would be done and those files will be included
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

//*code removed here which was for desktop path

using namespace std; // namespace for  resolving naming coflicts

/*******************GENERAL FUNCTION CLASS THAT ARE USED BY GLOBAL SCOPE FUNCTIONS********************************/

class GENERAL_INIT //*GRAND PARENT CLASS
{

public:

int ConvertChoiceToINT; //*variable for converting string input to integer
static int MODULE_CHOICE; //*module selector static variable

GENERAL_INIT()
{
  ConvertChoiceToINT=0;
}
void SetColor(int ForgC) //*for setting individual text color
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
  
void setCursorPos(int x, int y=0) //IMPORTANT : ->relative position is set
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

//*exit app code removed as we have exit option in input choice 

void buildVerticalWall(int briks) //* for making rectangle shape
{ cout<<"*";
  while(briks>0){cout<<"-";briks--;}
  cout<<"*";
}
  
void buildHorizontalWall(int endBrick,string data) //* for making rectangle shape
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

void startApp() //* for startup of home screen
{
  if(MODULE_CHOICE==0) // only 1 time initiaization function need to be called after 1 time just we need ro refresh home screen so is/else here
  {
    initApp();
    MODULE_CHOICE = askChoice();
  }
  else
  {
    MODULE_CHOICE = askChoice();
  }
  
}
 
int validateString(string input,int Bnd) //* string input validate as integer
  {

      int flag=0,tem=1;
      string i;
      for(tem=1;tem<=Bnd;tem++)
      {
          i = to_string(tem);
          if(i == input)
          {
            flag = 1; //*flag set means we have to give error message otherwise just return control with status original input after string->int conversion int will be returned
            break;
          }
      }
  
      if(flag==0)
      {
        scrClr();
        setCursorPos(8,26);
        SetColor(4);
        cout<<"INVALID CHOICE ENTERTED !"<<endl;
        setCursorPos(1,20);
        cout<<"PLEASE RE-ENTER YOUR CHOICE CORRECTLY !"<<endl;
        scrClr(1);
        SetColor(0);
        
        return 0;
      }
      else
      {
        return tem;
      }


  }


~ConvertChoiceToINT()
{
  
}
  
private:

void initApp() //setting up first time APP screen by making  console full screen
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

int askChoice() //*ask choice at home screen of APP
{ 
  
  re_ask:

  
  mainTitleOFapplication(); //TITLE OF APP
  bool match = false;
  string operationChoice;


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

   setCursorPos(2,30);
   cout<<"CHOICE : ";
   cin>>operationChoice;

   if (!cin)
   {
       cin.clear();
       cin.ignore(80,'\n');
   }

  ConvertChoiceToINT = validateString(operationChoice,10);
  if(!ConvertChoiceToINT)
  {
       
      goto re_ask;
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
  std::wcscpy(cfi.FaceName, L"JetBrains Mono ExtraBold"); // Choose your font BY SETTING FONT FACE
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); //pass reference of that structure to OUTPUT HANDLE 

}

void mainTitleOFapplication()
{  
   setCursorPos(1);
   cout<<setw(55)<<" || ATTENDANCE MANAGEMENT SYSTEM ||"<<endl;
}
 
  protected:
  
};

//---------STATIC DEFINATIONS-----------//
 int GENERAL_INIT::MODULE_CHOICE=0;
//-------------------------------------//

/****************************GENERAL-FUNCTION-CLASS-END***************************/

/****************************MODULE-START*****************************************/
class MODULE_GENERAL_FUNCTION : public GENERAL_INIT  //TODO: ALL MD TEAM PLEASE CONTRIBUTE YOUR FUNCTIONS HERE AND INHERIT THIS CLASS TO YOURS
{

  // ? this are general function class which can be used by all 4 module developers
  // *email functionalities also be included here since all 2 modules are using it
  // ? you have to make functions very generalized so other MD developers can use it
  // ?use can you OOP concepts here function overloading and other...concepts like template

  private:

  public:

  protected:
  

};

class SET_WRITE_DB: public MODULE_GENERAL_FUNCTION //TODO : just like that you have to develop your own class named MODULE_1/2/3/4
{
  
  //!=============================DATA-MEMBERS================================//

  /********************************* MODULE_1 *********************************/
  
  private:


  string course_name,sem,subject_name;

  
  public:

  protected:

  /*****************************************************************************/

  /********************************* MODULE_2 *********************************/
   private:
   public:
   protected:
  /*****************************************************************************/
  
  //!=============================DATA-MEMBERS-END================================// 
  

  //?=============================MEMBERS-FUNCTIONS===================================//
  
  public:
  SET_WRITE_DB() //TODO:CONSTRUCTOR
  {
    
  }
  /********************************* MODULE_1 *********************************/

  private:

  public:

  void askDeatails()
  { 


    scrClr(0.5);
    setCursorPos(9,26);
    
    cout<<"ENTER COURSE NAME : ";
    fflush(stdin);
    getline(cin,course_name);
    scrClr(0.5);
    
    
    reinputOfsem:
    fflush(stdin);
    setCursorPos(9,26);
    cout<<"ENTER SEMESTER : ";
    cin>>sem;
    scrClr(0.5);
    
    if(!validateString(sem,10))
    {goto reinputOfsem;}

    fflush(stdin);
    
    setCursorPos(9,26);
    cout<<"ENTER SUBJECT  : ";
    getline(cin,subject_name);
    scrClr(0.5);

    fflush(stdin);

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
    //jay swaminrayan
    //jay ganeshay namh
    bool loop=true;
    GENERAL_INIT APP;
    SET_WRITE_DB SW;

    while(loop)
    {
          APP.startApp();
      
          if(GENERAL_INIT::MODULE_CHOICE!=5)
          {
            APP.scrClr();
      
            APP.setCursorPos(2,10);
      
            switch(GENERAL_INIT::MODULE_CHOICE)
            {
              case 1:{
                     SW.askDeatails();
                     break;
                     }
              case 2:{
                       break;
                      }
              case 3:{}
              case 4:{}
              default:{cout<<endl<<"ERROR: APPLICATION CRASHED!!!"<<endl;exit(1);}
            }
      
            APP.scrClr(2);
          }
          else
          {
            loop=false;
          }
    

    }
    
    //APP.setCursorPos(14,25); // !WILL UNCOMMENT AT LAST AFTER DISCUSSION
    //APP.exitApp(0);
    return 0;
}
