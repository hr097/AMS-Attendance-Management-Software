#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#include <direct.h>
#include <shlobj.h>
#include <unistd.h>  
#include <sys/stat.h>
#include <direct.h>   
#include <conio.h>   
#include <cwchar>    


using namespace std;


#ifndef _WIN32_WINNT  
  #define _WIN32_WINNT 0x0601
  #include<wincon.h>
  #include<string>

  //#endif  // user 1  e.g.DRASHTI //! EOP() seek.edit(*required) :DRASHTI DHOLA
  
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
    BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX  lpConsoleCurrentFontEx);
  #ifdef __cplusplus
  }
  #endif

#endif // user 2 e.g.HARSHIL //! EOP() seek.edit(*required) :HARSHIL RAMANI


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

    void setConsoleFont() //? for setting up console font
    {
      CONSOLE_FONT_INFOEX cfi;                                               // structure variable
      cfi.cbSize = sizeof(cfi);                                              // total bytes of cfi
      cfi.nFont = 0;                                                         //by default
      cfi.dwFontSize.X = 0;                                                  // Width of each character in the font
      cfi.dwFontSize.Y = 20;                                                 // Height fixed
      cfi.FontFamily = FF_DONTCARE;                                          // font family doesn't matter
      cfi.FontWeight = FW_NORMAL;                                            // font normally bold
      std::wcscpy(cfi.FaceName, L"JetBrains Mono Bold");                     // Choose your font BY SETTING FONT FACE
      SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); // pass reference of that structure to OUTPUT HANDLE
    }

    string getDataBasePath()
    {
      string AMS_Path;

      CHAR pathDocument[MAX_PATH];   // string to store path
      HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL,SHGFP_TYPE_CURRENT,pathDocument); // getting documents path
  
      if (result == S_OK) // check if documents path is successfully stored in pathdocuments
      {
        AMS_Path = pathDocument;       // take original documents path into string
        AMS_Path = AMS_Path + "\\{JSN-1008-JSK-22-10-2021}"; // making AMS folder path
      }
      else
      { 
        cout <<endl << "something went wrong....";
        exit(1);
      }

      return(AMS_Path);
    }

    void setCursorPos(int x, int y = 0) //? cursor position set ->IMPORTANT: relative postion is set
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
    void SetColor(int color) //?for setting individual text color
    {

    WORD wColor;                                      // color specifier
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // create windows handle
    CONSOLE_SCREEN_BUFFER_INFO csbi;                  // We use csbi for the wAttributes word.
    
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      // Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
      SetConsoleTextAttribute(hStdOut,wColor); // set console text color
    }
    
    }

    void scrClr(float i = 0.0) //?for clearing screen afer particular time
    {
      // by default set to zero with default arguements
      sleep(i);      //  going in sleep mode for particular time
      system("cls"); //  clear  the screen
    }

    string getpass(const char *prompt, bool show_asterisk=true) // ?password input as *
    {
          const char BACKSPACE=8;
          const char RETURN=13;
          SetColor(7);
        
          string pswd;
          unsigned char ch=0;
        
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
          return pswd;
    }

    void getDataFromFile(string path, string &input, int lineNo) //?get Data of given path file line in string
    {
      ifstream get(path.c_str(),ios::in); //file opened in reading mode 
  
      if(!get.is_open())//if file is not opened
      {  
         scrClr();
         setCursorPos(9,28);
         cout << "DATA BASE-ERROR : 404 ";
         scrClr(2);
         exit(1);
      }
      else//if file is opened
      {
        int FileLine = 1; // start from first line
        while(FileLine<= lineNo)//whille fileline is <= lineno then
        {
          getline(get,input); //get data
          FileLine++;         //increment the fileline
        }
      }
     get.close(); //file closed
    }

    bool fileExists(const string &path) //checking function if file exists or not 
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

    public:

    void unLockDataBase()
    {   

        string password_confirm,password,temp_path;
        string path = getDataBasePath();
        getDataFromFile(path+"\\LOG-INFO\\pwd.txt",password_confirm,1);
    
        short unsigned int attempt = 3;
      
        r_ask_psed:
               
        scrClr();
        setCursorPos(1,48);
        SetColor(15);
        cout<<" Remaining Attempts : ";
        SetColor(10);
        cout<<attempt;
        SetColor(15);
      
        setCursorPos(2,35);
        fflush(stdin);
        password =  getpass("Enter your password : ",true);
        SetColor(15);
      
        if(password_confirm!=password) // password verification
        {
              setCursorPos(2,48);
              SetColor(12);
              cout << "Incorrect Password ! ";
              scrClr(1.5);
              SetColor(15);
              attempt--;
      
              if(!attempt)
              {
                  setCursorPos(2,36);
                  SetColor(12);
                  cout << "Suspicious User Found-Access Denied !!! ";
                  scrClr(1.75);
                  SetColor(15);
                  exit(0);
              }
                    else
                    goto r_ask_psed;
        }
        
        if(!fileExists(path.c_str())) // cross check if already unlocked
        {
          setCursorPos(2,45);
          SetColor(10);
          cout << " AMS Database is already unlocked !";
          scrClr(1.5);
          SetColor(15);
          exit(0);
        }
        else
        {

        tempStorage = path;
        path = path + "\\mn-cs-gxv-jsnfe-1008-jsn-db-lock.ini";
        
        command = "del ";
        command =  command + path;
        system(command.c_str());
        
        command.clear();
        command = "attrib -h -s " + tempStorage;
        WinExec(command.c_str(),0);

        setCursorPos(2,40);
        SetColor(10);
        cout << " AMS Database Unlocked Successfully ! "<<endl; // process success 
        scrClr(1.5);
        SetColor(15);
        exit(0);

      }
    }

    dataBase()
    {
      setConsoleFont();
    }
    ~dataBase()
    {
   
    }

    protected:

};

int main()
{   
    dataBase D;
    D.unLockDataBase();
    return(0);
}
