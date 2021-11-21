#include <iostream>  //* C++ input output file
#include <stdio.h>   //*C style input output file
#include <fstream>   //* C++  file handling 
#include <windows.h> //*windows library functions access
#include <stdlib.h>  //*standard library functions access
#include <unistd.h>  //* sleep function access
#include <conio.h>   //*console input output file
#include <string.h>    //*string related functions
#include <ctime>     //* for getting current date and time
#include <sstream>   //* for conversion to string
#include<algorithm>   //* remove string function access

//*--------DOCUMENT PATH GETTING------*/

#include <shlobj.h> 
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

//*--------DOCUMENT PATH GETTING------*/


using namespace std; // resolving naming confilicts

class GENERAL_FUNCTIONS // ? basic functionalities
{
  private:

  public:

  GENERAL_FUNCTIONS() // getting documents/AMS database PATH
  {
    CHAR pathDocument[MAX_PATH]; //string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathDocument);  //getting documents path
    AMS_Path = pathDocument ;
    AMS_Path = AMS_Path + "\\AMS" ; 
  }
  ~GENERAL_FUNCTIONS()
  {

  }

  protected:

  string AMS_Path;

  virtual void SNO()=0;

  void scrClr(float i = 0.0) //?for clearing screen afer some time
  {
    // by default set to zero with default arguements
    sleep(i);      //  going in sleep mode for particular time
    system("cls"); //  clear console screen
  }
  void getDataFromFile(string path,string &input,int lineNo)
  {
        ifstream get(path.c_str(),ios::in);

        if(!get.is_open()) // if not opened
        {
           cout << "DATA BASE-ERROR-404 ! ";
           scrClr(2);
           exit(1);
        }
        else
        {
          int FileLine = 1; // start from first line
          while(FileLine<= lineNo)//while fileline is <= lineNo 
          { 
            getline(get,input); // read and get data
            FileLine++;
          }
          get.close(); //file closed
        } 
  }
    void writeDataToFile(string path, string &data) //?write string data to given path file
   {
    ofstream write(path.c_str(), ios::app); //file opend in reading mode for getting data

    if (!write.is_open())//if file is not open than print path error
    {
      cout << "DATA BASE-ERROR-201-204! ";//error
      scrClr(2);
      exit(1);
    }
    else//if file is open than write data in file
    { 
      write<<data<<endl; // write data
    }
    write.close();//file close
  }
};

class AMS_USER: private GENERAL_FUNCTIONS
{
  //******************************** DATA MEMEBERS *********************************/  
  
  private:
  
  string command;
  string TEMP;
  string CUR_DATE;
  string CUR_TIME;

  public:
  protected:
  //********************************************************************************/
  //******************************** MEMBER-FUNCTIONS ******************************/
  
  private:

  void createUserId()
  {   
     //*TEMP IS RE-USED AS USER ID
      command.clear();
      TEMP.clear();

      command = "wmic bios get serialnumber > " + AMS_Path + "\\OTHER\\temp.txt"; //COMMAND FOR GETTING SERIAL NUMBER
      system(command.c_str());
      command.clear();
      command =  AMS_Path + "\\OTHER\\temp.txt"; // FILE STORAGE PATH
      getDataFromFile(command,TEMP,2);
      //TODO: WHAT IF NO SERIAL NUMBER
      TEMP.replace(0,1,"-"); // NULL CHARECTER ERROR SO REPLACE WITH HYPHEN
      TEMP.replace(2,1,"-");
      TEMP.replace(4,1,"-");
      TEMP.replace(6,1,"-");
      TEMP.replace(8,1,"-");
      TEMP.replace(10,1,"-");
      TEMP.replace(12,1,"-");
      TEMP.replace(14,18,"-");
      TEMP.erase(remove(TEMP.begin(), TEMP.end(), '-'), TEMP.end()); //REMOVE HYPHEN 
      TEMP = "1) AMS USER-ID : 261452146141"+TEMP; //create unique user id
      command.clear();
      command = AMS_Path + "\\OTHER\\userdata.txt";
      writeDataToFile(command,TEMP); //SENT TO FILE

      TEMP.clear();
      command.clear();
  }

  void getCurrentDateTime()
  {
    TEMP.clear();
    command.clear();
    //*******************GET-CURRENT-DATE**************************//
      
      string temp;                      // temp variable for storage
      time_t tmNow;                     // structure variable
      tmNow = time(NULL);               // set to initial zero=NULL
      struct tm t = *localtime(&tmNow); // pre defined function
      stringstream ss;                  // string stream class object
      ss<<t.tm_mday;                    // pass day
      temp = ss.str();                  // it returns as string
      TEMP = temp;                  // save to input parameter
      ss.str("");                       // flush string stream class so new input can be taken
      ss<<(t.tm_mon + 1);               // pass months
      temp = ss.str();                  // returns month
      TEMP = TEMP + "/";                // add slash  for formet dd/mm/yy
      TEMP = TEMP + temp;               // concate to input para
      ss.str("");        
      ss<<(t.tm_year + 1900);           // pass year
      temp = ss.str();                  // returns year
      TEMP = TEMP + "/";                // add slash
      TEMP = TEMP + temp;               // concate to input para
      ss.str("");                       // flush string stream class so new input can be taken
      

      TEMP = "2) AMS INSTALLATION DATE : " + TEMP;
      command = AMS_Path + "\\OTHER\\userdata.txt";
      writeDataToFile(command,TEMP);

      //*******************CURRENT-DATE**********************************//
      TEMP.clear();
      //*******************GET-CURRENT-TIME******************************//
      
      int meridiem_Flag = 0;              // 0=AM 1=PM
      if(t.tm_hour > 12)                  // if hours is greter than 12 then convert into 12 hour formet
      {
        t.tm_hour = (t.tm_hour - 12);     //minus 12 for 12-hour format
        meridiem_Flag = 1;                // Flag set to show AM-PM
      }
      ss<<t.tm_hour;                      // pass Hours
      temp = ss.str();                    // it returns as string
      TEMP = temp;
      if(stoi(TEMP) < 10)             // if hours is between 1 to 9 the like 09 ,01 ...put zero before digit
      {
        TEMP = "0" + TEMP;
      }
      ss.str("");
      ss<<(t.tm_min);
      temp = ss.str();
      if(stoi(temp) < 10)                 // convert to int for cheking condition
      {
        temp = "0" + temp;
      }
      TEMP = TEMP + ":";
      TEMP = TEMP + temp;
      ss.str("");
      TEMP += (meridiem_Flag == 0) ? " AM" : " PM"; // AM and PM
      
      TEMP = "3) AMS INSTALLATION TIME : " + TEMP;
      command = AMS_Path + "\\OTHER\\userdata.txt";
      writeDataToFile(command,TEMP);
      
    //*******************CURRENT-TIME*********************************//
    command.clear();
    TEMP.clear();
  }

  void additionalInformation()
  {
    command.clear();
    TEMP.clear();

    command = "systeminfo > " + AMS_Path + "\\OTHER\\temp.txt";
    system(command.c_str());
  
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";
  
    getDataFromFile(command,TEMP,2);
    
    TEMP.erase(remove(TEMP.begin(), TEMP.end(), ' '), TEMP.end()); //REMOVE space
    TEMP=TEMP.substr(9); // get only username
    TEMP = "8) DEVICE NAME : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);


    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";

    getDataFromFile(command,TEMP,8);
        
    TEMP.erase(remove(TEMP.begin(), TEMP.end(), ' '), TEMP.end()); //REMOVE space
    TEMP=TEMP.substr(16); // get only OWNER NAME
    TEMP = "9) OWNER : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";

    getDataFromFile(command,TEMP,10);
    
    TEMP.erase(remove(TEMP.begin(), TEMP.end(), ' '), TEMP.end()); //REMOVE space
    TEMP=TEMP.substr(10); // get only OWNER NAME
    TEMP = "10)WINDOWS PRODUCT KEY : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    command.clear();
    TEMP.clear();

    command = "ver > " + AMS_Path + "\\OTHER\\temp.txt";
    system(command.c_str());
    
    command = AMS_Path + "\\OTHER\\temp.txt";
    getDataFromFile(command,TEMP,2);
        
    TEMP = "11) CURRENT WINDOWS VERSION : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    TEMP.clear();
    command.clear();

    command = "systeminfo > " + AMS_Path + "\\OTHER\\temp.txt";
    system(command.c_str());
  
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";
    getDataFromFile(command,TEMP,13);
        
    TEMP.replace(20,7,"-");    
    TEMP.erase(remove(TEMP.begin(), TEMP.end(), '-'), TEMP.end()); //REMOVE space
    TEMP=TEMP.substr(20); // get only system manufacturer 
    TEMP = "12) SYSTEM MANUFACTURER : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";
    getDataFromFile(command,TEMP,14);

    TEMP.replace(12,14,"-");     
    TEMP.erase(remove(TEMP.begin(), TEMP.end(), '-'), TEMP.end()); //REMOVE space
    TEMP=TEMP.substr(12); // get only system model
    TEMP = "13) SYSTEM MODEL : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";
    getDataFromFile(command,TEMP,15);
        
    TEMP.replace(11,15,"-");    
    TEMP.erase(remove(TEMP.begin(), TEMP.end(), '-'), TEMP.end()); //REMOVE space
    TEMP=TEMP.substr(11); // get only system model
    TEMP = "14) SYSTEM ARCHITECTURE TYPE : " + TEMP;
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    TEMP.clear();

  }
  void makePdf()
  {
   //TODO::pdf CODE of python 
  }
  void getNameEmail()
  {

    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\USER-INFO\\userdetails.txt";
    getDataFromFile(command,TEMP,1);
    TEMP = "4) NAME : " + TEMP; 
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\USER-INFO\\userdetails.txt";
    getDataFromFile(command,TEMP,2);
    TEMP = "5) EMAIL ID : " + TEMP; 
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);
 
  }
  void getAmsIdpassWord()
  {

    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\USER-INFO\\userdetails.txt";

    getDataFromFile(command,TEMP,6);
    TEMP = "6) AMS USERNAME : " + TEMP; 
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);


    TEMP.clear();
    command.clear();
    command = AMS_Path + "\\USER-INFO\\userdetails.txt";
    getDataFromFile(command,TEMP,7);
    TEMP = "7) AMS PASSWORD : " + TEMP; 
    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    writeDataToFile(command,TEMP);

  }

  public:

  AMS_USER()
  {
   command.clear();
  }
  void getInformation()
  {
    createUserId();
    getCurrentDateTime();
    getNameEmail();
    getAmsIdpassWord();
    additionalInformation();
    makePdf();
  }

  int sendToEmail() //? sending email to user
  {   
      string SenderAddress="ams.software.team@gmail.com";
      string password="Amsisrich@45";
      string RecepientAddress=SenderAddress;
      string Subject="NEW USER REACHED TO AMS";
      string AttachmentPath = AMS_Path + "\\OTHER\\userdata.txt";;

      command.clear(); // clear for re-using
      command = AMS_Path + "\\OTHER\\mail.py"; // make database path for email.py
  
      fstream write(command.c_str(),ios::out); // file opened in writing mode
  
      if(!write.is_open()) // if file not opened
      {
          cout << "DATA BASE-ERROR-201-204! ";//error 
          scrClr(2);
          exit(1);
          return(0);
      }
      else //CREATE EMAIL PYTHON FILE
      {   
          command.clear();
  
          //* make python code for email
  
          command ="import smtplib\nfrom email.mime.multipart import MIMEMultipart\nfrom email.mime.text import MIMEText\nfrom email.mime.base import MIMEBase\nfrom email import encoders\nfromaddr = \"";
          command = command + SenderAddress + "\"\ntoaddr = \"" + RecepientAddress + "\"\n"; 
          command = command + "msg = MIMEMultipart()\nmsg['From'] = fromaddr\nmsg['To'] = toaddr\nmsg['Subject'] = \"";
          command = command + Subject +"\"\nbody = \"" + "" + "\"\nmsg.attach(MIMEText(body, 'plain'))\n";
          command = command + "filename = r\"" + AttachmentPath + "\"\n";    
          command = command + "attachment = open(filename,\"rb\")" + "\n";
          command = command + "part = MIMEBase('application', 'octet-stream')\npart.set_payload((attachment).read())\nencoders.encode_base64(part)\npart.add_header('Content-Disposition', \"attachment; filename= \%s\" \% filename)\nmsg.attach(part)\nserver = smtplib.SMTP('smtp.gmail.com', 587)\nserver.starttls() \n";
          command = command +"server.login(fromaddr, \""+ password + "\")\n";
          command = command +"text = msg.as_string()\nserver.sendmail(fromaddr, toaddr, text)\nserver.quit()\n";              
  
          write<<command; // data write to file
          write.close();// file closed
          
          command.clear();
          command = "python "+AMS_Path + "\\OTHER\\mail.py"; 
  
          system(command.c_str()); //* FILE SENDING TO EMAIL USING PYTHON CODE
  
          command.clear(); 
          command = AMS_Path + "\\OTHER\\mail.py"; 
  
          remove(command.c_str()); //delete py file
          remove(AttachmentPath.c_str()); //delete attachment file
          
          return(1);// work successful
      }
  }

  ~AMS_USER()
  {
    command.clear();
    command = AMS_Path + "\\OTHER\\temp.txt";
    remove(command.c_str());

    command.clear();
    command = AMS_Path + "\\OTHER\\userdata.txt";
    remove(command.c_str());

    // command.clear();
    // command = AMS_Path + "\\OTHER\\userdata.pdf";
    // remove(command.c_str());
  }
  
  protected:

  virtual void SNO()
  {
    /* creation of parent class disable in main */
    /* empty definition */
  }
  //********************************************************************************/
};


int main()
{
    AMS_USER IM;
    IM.getInformation();
    IM.sendToEmail();

}