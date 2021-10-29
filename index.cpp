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


using namespace std; // namespace for  resolving naming coflicts

/*******************APP-CONTROL_CLASS********************************/



class APP //*GRAND PARENT CLASS
{

  public:

  static int MODULE_CHOICE; //*module selector static variable
  
  APP(){ }

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

  void debug(int do_what=0) //for debugging purposes at last we will delete it 0=pause 1=pause & print
  {
    #include<conio.h> // * console input output library
    if(!do_what)
    getch();
    else
    cout<<endl<<"DEBUG"<<endl;
  } 

  void startApp() //* for startup of home screen
  {
    if(MODULE_CHOICE==0) // only 1 time initiaization function need to be called after 1 time just we need ro refresh home screen so is/else here
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

  void initApp() //setting up first time APP screen by making console in full screen
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
    
       setCursorPos(2,30);
       ShowConsoleCursor(true);
       cout<<"CHOICE : ";
       getline(cin,operationChoice);
       ShowConsoleCursor(false);
    
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
  
  void InvalidInputErr()
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

  int validateString(string input,int Bnd) //* string input validate as integer
  {

      int flag=0,tem=1;
      string i;
      for(tem=1;tem<=Bnd;tem++)
      {
          i = to_string(tem);
          if(i == input)
          {
            flag = 1; 
            break;
          }
      }
  
      if(flag==0)
      {
        InvalidInputErr(); 
        return 0;
      }
      else
      {
        return tem;
      }


  }
  
  int validateString(string input)
  {
    if(input == "YES" || input == "yes" || input == "Yes")
    {
      return 1;
    }
    else if(input == "NO" || input == "no" || input == "No")
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }

};

//---------STATIC DEFINATIONS  OF APP-----------//
 int APP::MODULE_CHOICE=0;
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
 
  string AMS_Path,command,FacultyName,FacultyEmail,course_name,sem,subject_name,SemCreatePath,ans,temp_path;
 


  void AppPath(string &path)
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
        cout << "ERROR PATH NOT FOUND : " << result << "\n";
    }
  } 

  void getDataFromFile(string path,string &FcName,int lineNo)
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

  void writeDataToFile(string path,string &FcName)
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

  void convertStringtoArray(string arg,char* argcopy) //meaning itself defining
  {
  int i;
  for(i=0;i<arg.length();i++)
  {
   *(argcopy+i) = arg[i];
  }
  *(argcopy+i)='\0';
  }

  string convertIntToString(int &in) //meaning itself defining
  {
  string str = to_string(in);
  return str;
  }

  string convertArrayTostring(char* arg) //meaning itself defining
  {
  string re(arg);
  return re;
  }

  void replaceWith_(string &str) //*special symbols are not allowed in file name so need to convert them into -hyphen
  {   
      int i=0,j=0;
      string list = "#%&{}\\/*>< $!:\'\"@+`|="; //*need to be checked
      
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
   
  //  i=0,j=0;// re used i as position of -

   //while(i<=str.length())
   //{
      // for(i=0;i<=str.length();i++)
      // {
        // if(str[i]=='-')
        // { 
          // int del_pos=i;
          // while(del_pos=='-')
          // {
            // del_pos++;
          // }
          // for(j=del_pos;j<=str.length();j++)  // h a r s h 
          // {							   // 0 1 2 3 4
          	// str[j-1]=str[j];
          // }   
        // }
      // }
      
  }

  bool EmptyInput(string &input)
  {
   if(input.empty())
   {
     return true;
   }
   else
   {
     return false;
   }
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

};

class SET_WRITE_DB: public MODULE_GENERAL //TODO : just like that you have to develop your own class named MODULE_1/2/3/4
{
  
  //!=============================DATA-MEMBERS================================//

  /********************************* MODULE_1 *********************************/
  
  private:

  public:

  protected:
    void SetNoObj(){} //JUST STOP DISABLING CREATION OF PARENT & GRAND PARENT CLASS OBJECT

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
    AppPath(AMS_Path);
  }
  /********************************* MODULE_1 *********************************/

  private:
  
  int createSemester() //* return 1=craetd successfully return 0=not created
  { 
    
    temp_path=course_name;
    replaceWith_(temp_path);

    SemCreatePath = AMS_Path + "\\" + temp_path + "-SEM-" + sem ; //making semesterpath with coursename
  
    temp_path=subject_name;
    replaceWith_(temp_path);

    SemCreatePath = SemCreatePath + "-" + temp_path  ; //proper subject folder create

    if(!dirExists(SemCreatePath.c_str())) //if directory not exists then create it
        {  
            command = "mkdir " +  SemCreatePath;                //making commad which will pass in cmd
            ////cout<<"commad 1 for creating directory "<<command<<endl;
            system(command.c_str());      // creating  directory by CMD
             
            /*********************  FOLDERS *******************/
            
             command = "mkdir " + SemCreatePath + "\\DAILY-RECORD" ; // making COMMAND FOR DAILY_RECORD folder
             ////cout<<"commad 1 for creating directory "<<command<<endl;
             system(command.c_str()); // creating DAILY_RECORD directory by CMD
             
             command = "mkdir " + SemCreatePath + "\\FAC-STUD-DETAILS" ; // making COMMAND FOR FAC&STUD_DETAILS folder
             ////cout<<"commad 1 for creating directory "<<command<<endl;
             system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD
             
             command = "mkdir " + SemCreatePath + "\\MONTHLY-RECORDS" ; // making COMMAND FOR MONTHLY_RECORDS folder
             ////  cout<<"commad 1 for creating directory "<<command<<endl;
             system(command.c_str()); // creating MONTHLY_RECORDS directory by CMD

             /**************************************************/
             
             /*******************  FILES *********************/
             
              command = "cd. > " + SemCreatePath + "\\DAILY-RECORD\\records.txt"; // RECORDS.TXT file
              system(command.c_str()); 
               
              command = "cd. > " + SemCreatePath + "\\FAC-STUD-DETAILS\\faculty"+"-sem-"+ sem +".txt"; // faculty_details.TXT file
              system(command.c_str());  
               
              command = "cd. > " + SemCreatePath + "\\FAC-STUD-DETAILS\\student"+"-sem-"+ sem +".txt"; // student_details.TXT file
              system(command.c_str()); 
             
              return 1;
              /***********************************************/
        }
        else 
        {
          scrClr();
          setCursorPos(9,26);
          SetColor(2);
          ShowConsoleCursor(false);
          cout<<"SEMSTER ALREADY EXIST !"<<endl;
          scrClr(1);
          SetColor(0);
          return 0;
        }
  }

  int confirmation()
  {
    int line; 

    reInput:

    setCursorPos(5,15);
    cout<<"FACULTY NAME "<< right << setw(5) <<": " <<FacultyName;
    setCursorPos(1,15);
    cout<<"FACULTY E-MAIL "<< right << setw(3) <<": " <<FacultyEmail;
    setCursorPos(2,15);
    cout<<"COURSE NAME "<< right << setw(6) <<": " <<course_name;
    setCursorPos(1,15);
    cout<<"SEMESTER "<< right << setw(9) <<": " <<sem;
    setCursorPos(1,15);
    cout<<"SUBJECT "<< right << setw(10) <<": " <<subject_name;
      
  
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
    getline(cin,ans);
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(ans);
    
    if(ConvertChoiceToINT == -1)
    {
      InvalidInputErr();
      goto reInput;
    }

   return(ConvertChoiceToINT);
  }

  int InfoModification() //* MODIFICATIONS OF FACULTY DETAILS
  { 
       int line=0;

       reInput:
    
       setCursorPos(1);
       cout<< setw(62) <<" => WHICH INFORMATION DO YOU WANT TO MODIFY ? "<<endl; 

       bool match = false;
       string operationChoice;
    
       setCursorPos(2,25);
    
       buildVerticalWall(23);
    
       while(line<11)
        {
            setCursorPos(1,25);
            if(line==0)
            buildHorizontalWall(23,"1) FACULTY NAME ");
            else if(line==2)
            buildHorizontalWall(23,"2) FACULTY E-MAIL ");
            else if(line==4)
            buildHorizontalWall(23,"3) COURSE NAME ");
            else if(line==6)
            buildHorizontalWall(23,"4) SEMESTER ");
            else if(line==8)
            buildHorizontalWall(23,"5) SUBJECT ");
            else if(line==10)
            buildHorizontalWall(23,"6) NO CHANGE ");
            else 
            buildHorizontalWall(23," ");
            line++;
        }
    
       setCursorPos(1,25);
       buildVerticalWall(23);
    
       setCursorPos(2,30);
       ShowConsoleCursor(true);
       cout<<"CHOICE : ";
       getline(cin,operationChoice);
       ShowConsoleCursor(false);
    
       if(!cin)
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
       ConvertChoiceToINT = validateString(operationChoice,6);

       if(ConvertChoiceToINT==-1)
       { 
           InvalidInputErr();
           goto reInput;
       }
       else 
       {
       return(ConvertChoiceToINT);
       }
  }

   void UpdateFacName()
   { 
      reinput:
      scrClr(0.5);
      setCursorPos(9,26);
      cout<<"ENTER FACULTY NAME : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,FacultyName);
      ShowConsoleCursor(false);
      if(EmptyInput(FacultyName))
      {
        InvalidInputErr();
        goto reinput;
      }
      
      scrClr(0.5);
  }
  void UpdateEmail()
  {   reinput:
      scrClr(0.5);
      setCursorPos(9,26);
      cout<<"ENTER FACULTY EMAIL : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,FacultyEmail);
      ShowConsoleCursor(false);
      if(EmptyInput(FacultyEmail))
      {
        InvalidInputErr();
        goto reinput;
      }
      scrClr(0.5);
  
      
  }
  void EnterCourseName()
  {   
      reinput:
      scrClr(0.5);
      setCursorPos(9,26);
      cout<<"ENTER COURSE NAME  : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,course_name);
      ShowConsoleCursor(false);
      if(EmptyInput(course_name))
      {
        InvalidInputErr();
        goto reinput;
      }
      scrClr(0.5);
  
  }
  void EnterSem()
  {   
      scrClr(0.5);
      reinputOfsem:
      fflush(stdin);
      setCursorPos(9,26);
      cout<<"ENTER SEMESTER : ";
      fflush(stdin);
      ShowConsoleCursor(true);
      getline(cin,sem);
      ShowConsoleCursor(false);
      scrClr(0.5);
  
      if(!validateString(sem,10))
      {goto reinputOfsem;}
  
      
  }
  void EnterSubject()
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
      fflush(stdin);
      scrClr(0.5); 
  
      
  }
  
  public:
   
  void askFacDetails()
  { 

    reAskFacDet:

    EnterCourseName();
    
    
    EnterSem();
    
  
    EnterSubject();

    command = AMS_Path + "\\USER-INFO\\userdetails.txt";
   
    getDataFromFile(command,FacultyName,1);
    getDataFromFile(command,FacultyEmail,2);
    
    
    fflush(stdin);

    confirmAgain:

    if(confirmation())
    {  
        if(createSemester())
        {

        command = SemCreatePath + "\\FAC-STUD-DETAILS\\faculty"+"-sem-"+ sem +".txt";
        
        writeDataToFile(command,FacultyName);
        writeDataToFile(command,FacultyEmail);
        writeDataToFile(command,course_name);
        writeDataToFile(command,sem);
        writeDataToFile(command,subject_name);
        
        }
        else
        {
          goto reAskFacDet;
        }
    }
    else
    { 
      scrClr(0.5);

      switch(InfoModification())
      {
        case 1:{UpdateFacName(); break;}
        case 2:{UpdateEmail();break;}
        case 3:{EnterCourseName();break;}
        case 4:{EnterSem();break;}
        case 5:{EnterSubject();break;}
        case 6:{scrClr(0.5);break;}
      }
      goto confirmAgain;
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
   //jay swaminrayan
    //jay ganeshay namh
    bool loop=true;
    
    SET_WRITE_DB SW;
 
    while(loop)
    {
          SW.startApp();
      
          if(APP::MODULE_CHOICE!=5)
          {
            SW.scrClr();
      
            SW.setCursorPos(2,10);
      
            switch(APP::MODULE_CHOICE)
            {
              case 1:{
                         SW.askFacDetails();
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
              default:{cout<<endl<<"ERROR: APPLICATION CRASHED!!!"<<endl;exit(1);}
            }
      
            SW.scrClr(2);
          }
          else
          {
            loop=false;
          }

    }

    return 0;
}

