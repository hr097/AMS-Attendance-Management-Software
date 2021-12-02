#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdbool.h> // * boolean operation
#include<thread> //* for therading


//*NOTE THAT : ACCORDING TO REQUIREMENT sendToEmail() can be changed and you must have only python installed on your system in order to send email and run this function

//* THIS IS JUST A LOGIC MAY BE ACCORDING TO YOUR  APPLICATION REQUIREMENT YOUR CODE CAN BE DIFFERENT

//for more help : harshilramani9777@gmail.com / harshilramani.mscit20@vnsgu.ac.in


bool email_flag;
bool process_flag;

using namespace std;

  void LoadingProcess()
  {
    tempStorage.clear();
    tempStorage = "WORKING ON IT";
    do
    {
    scrClr(0.5);
    setCursorPos(9,26);
    SetColor(2);
    ShowConsoleCursor(false);
    cout << tempStorage ;
    scrClr(1);
    tempStorage = tempStorage + ".";
 
    if(process_flag)
    {
      break;
    }

    }while(true);
    
    tempStorage.clear();
    SetColor(0);
  }

  void sendToEmail(string SenderAddress,string password,string RecepientAddress,string Subject,string Msg,string AttachmentPath,string fileName) //? sending email to user
  {   
      command.clear(); // clear for re-using
  
      command = AMS_Path + "\\OTHER\\mail.py"; // make database path for email.py
  
      fstream write(command.c_str(),ios::out); // file opened in writing mode
  
      if(!write.is_open()) // if file not opened
      {
          cout << "DATA BASE-ERROR-201-204! ";//error 
          scrClr(2);
          exit(1);
      }
      else //CREATE EMAIL PYTHON FILE
      {   
          command.clear();
  
          //* make python code for email
  
          command ="import smtplib\nfrom email.mime.multipart import MIMEMultipart\nfrom email.mime.text import MIMEText\nfrom email.mime.base import MIMEBase\nfrom email import encoders\n\nfromaddr = \"";
          command = command + SenderAddress + "\"\ntoaddr = \"" + RecepientAddress + "\"\n"; 
          command = command + "msg = MIMEMultipart()\nmsg['From'] = fromaddr\nmsg['To'] = toaddr\nmsg['Subject'] = \"";
          command = command + Subject +"\"\nbody = \"\"\"" + Msg + "\"\"\"\nmsg.attach(MIMEText(body, 'plain'))\n";
          command = command + "filename = r\"" + AttachmentPath + "\"\n";    
          command = command + "attachment = open(filename,\"rb\")" + "\n";
          command = command + "part = MIMEBase('application', 'octet-stream')\npart.set_payload((attachment).read())\nencoders.encode_base64(part)\npart.add_header('Content-Disposition', \"attachment; filename= \%s\" \% \" " + fileName + "\")\nmsg.attach(part)\nserver = smtplib.SMTP('smtp.gmail.com', 587)\nserver.starttls() \n";
          command = command +"server.login(fromaddr, \""+ password + "\")\n";
          command = command +"text = msg.as_string()\nserver.sendmail(fromaddr, toaddr, text)\nserver.quit()\n";              
  
          write<<command; // data write to file
          write.close();// file closed
          
          command.clear();
          command = "python "+AMS_Path + "\\OTHER\\mail.py " + "1> " + AMS_Path + "\\OTHER\\output.txt 2>&1"; 
  
          system(command.c_str()); //* FILE SENDING TO EMAIL USING PYTHON CODE
          
          command.clear(); 
          command = AMS_Path + + "\\OTHER\\output.txt";

          int err = checkEmptyFile(command);
          remove(command.c_str()); // delete output/error file

          command.clear(); 
          command = AMS_Path + "\\OTHER\\mail.py"; 
  
          remove(command.c_str()); //delete py file
          remove(AttachmentPath.c_str()); //delete attachment file

          
          process_flag=true;

          if(err)
          email_flag=false;
          else
          email_flag=true;
          
      }

  }

//*threading used for  processing email part  
      MODULE_3 MD3;
      thread t1(&sendToEmail,MD3,"ams.software.team@gmail.com","Amsisrich@45",FacultyEmail,"CUSTOMIZE-ATTENDANCE-REPORT","Dear Sir/Madam, \nGreetings From Team AMS. \n\nKindly Go throgh Your Customized Attendance Report.\n\nThank You.\n\n",SemPath+"\\DAILY-RECORD\\052_Harshil_Ramani_PA04.pdf","AMS_REPORT_BSCIT_SEM_3_OOP.pdf"); 
      thread t2(&LoadingProcess,MD3);

      t1.join();
      t2.join();

      scrClr();
      
      if(process_flag && email_flag)
      {
        reportSentSuccessfully();
      }
      else
      {
        warnMsg("REPORT COULDN'T BE SENT !",4,26,"ERROR CODE : 503/599/408/424/444",1,22);
      }     
      



int main()
{

   sendToEmail("xyz@gmail.com","password","harshilramani9777@gmail.com","TESTING","HELLO IS THAT SUCCESSFULL","C:\\Users\\DELL\\OneDrive\\Desktop\\cashback 3000\\NOC_w.pdf","happy.pdf");

    return 0;
}
