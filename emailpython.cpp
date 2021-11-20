#include<iostream>
#include<fstream>
#include<conio.h>

using namespace std;


//! need to set AMS DATABASE path be we can't directly create file in program *86 file
//! later on after shubham's review we will change the path according to him
//! PYCACHE FOLDER will be automatically created so need to discuss on that

int sendEmail(string SenderAddress,string password,string RecepientAddress,string Subject,string Msg,string AttachmentPath) //? sending email to user
{   
    string command,AMS_Path="C:\\Users\\DELL\\OneDrive\\Documents\\AMS"; // ! remove it later on
   
    command.clear(); // clear for re-using

    command = AMS_Path + "\\OTHER\\email.py"; // make database path for email.py

    fstream write(command.c_str(),ios::out); // file opened in writing mode

    if(!write.is_open()) // if file not opened
    {
        cout << "DATA BASE-ERROR-201-204! ";//error 
        //scrClr(2);
        //exit(1);
        return(0);
    }
    else //CREATE EMAIL PYTHON FILE
    {   
        command.clear();

        //* make python code for email

        command ="import smtplib\nfrom email.mime.multipart import MIMEMultipart\nfrom email.mime.text import MIMEText\nfrom email.mime.base import MIMEBase\nfrom email import encoders\nfromaddr = \"";
        command = command + SenderAddress + "\"\ntoaddr = \"" + RecepientAddress + "\"\n"; //"ams.software.team@gmail.com"  
        command = command + "msg = MIMEMultipart()\nmsg['From'] = fromaddr\nmsg['To'] = toaddr\nmsg['Subject'] = \"";
        command = command + Subject +"\"\nbody = \"" + Msg + "\"\nmsg.attach(MIMEText(body, 'plain'))\n";
        command = command + "filename = \"" + AttachmentPath + "\"\n";    
        command = command + "attachment = open(filename,\"rb\")" + "\n";
        command = command + "part = MIMEBase('application', 'octet-stream')\npart.set_payload((attachment).read())\nencoders.encode_base64(part)\npart.add_header('Content-Disposition', \"attachment; filename= \%s\" \% filename)\nmsg.attach(part)\nserver = smtplib.SMTP('smtp.gmail.com', 587)\nserver.starttls() \n";
        command = command +"server.login(fromaddr, \""+ password + "\")\n";
        command = command +"text = msg.as_string()\nserver.sendmail(fromaddr, toaddr, text)\nserver.quit()\n";              

        write<<command; // data write to file
        write.close();// file closed
        
        command.clear();
        command = "python "+AMS_Path + "\\OTHER\\email.py"; 

        system(command.c_str()); //* FILE SENDING TO EMAIL USING PYTHON CODE

        command.clear(); 
        command = AMS_Path + "\\OTHER\\email.py"; 

        remove(command.c_str()); //delete py file
        remove(AttachmentPath.c_str()); //delete attachment file
        
        return(1);// work successful
    }
}

int main()
{

   sendEmail("ams.software.team@gmail.com","Amsisrich@45","harshilramani9777@gmail.com","TESTING","HELLO IS THAT SUCCESSFULL","my.pdf");

    return 0;
}