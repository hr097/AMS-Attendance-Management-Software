#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdbool.h> // * boolean operation

//*NOTE THAT : ACCORDING TO REQUIREMENT sendToEmail() can be changed and you must have only python installed on your system in order to send email and run this function
bool email_flag;
bool process_flag;

using namespace std;

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
  
          command ="import smtplib\nfrom email.mime.multipart import MIMEMultipart\nfrom email.mime.text import MIMEText\nfrom email.mime.base import MIMEBase\nfrom email import encoders\nimport sys\nclass DevNull:\n    def write(self, msg):\n        pass\n\nsys.stderr = DevNull()\nfromaddr = \"";
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
          command = "python "+AMS_Path + "\\OTHER\\mail.py "; 
  
          int err = system(command.c_str()); //* FILE SENDING TO EMAIL USING PYTHON CODE
  
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



int main()
{

   sendToEmail("xyz@gmail.com","password","harshilramani9777@gmail.com","TESTING","HELLO IS THAT SUCCESSFULL","C:\\Users\\DELL\\OneDrive\\Desktop\\cashback 3000\\NOC_w.pdf","happy.pdf");

    return 0;
}
