#include<iostream>
#include<fstream>
#include<conio.h>

using namespace std;


int sendToEmail(string SenderAddress,string password,string RecepientAddress,string Subject,string Msg,string AttachmentPath,string fileName) //? sending email to user
{   
    string command,AMS_Path="C:\\Users\\DELL\\OneDrive\\Documents\\AMS"; // ! remove it later on
   
    command.clear(); // clear for re-using

    command = AMS_Path + "\\OTHER\\mail.py"; // make database path for email.py

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
        command = command + SenderAddress + "\"\ntoaddr = \"" + RecepientAddress + "\"\n"; 
        command = command + "msg = MIMEMultipart()\nmsg['From'] = fromaddr\nmsg['To'] = toaddr\nmsg['Subject'] = \"";
        command = command + Subject +"\"\nbody = \"" + Msg + "\"\nmsg.attach(MIMEText(body, 'plain'))\n";
        command = command + "filename = r\"" + AttachmentPath + "\"\n";    
        command = command + "attachment = open(filename,\"rb\")" + "\n";
        command = command + "part = MIMEBase('application', 'octet-stream')\npart.set_payload((attachment).read())\nencoders.encode_base64(part)\npart.add_header('Content-Disposition', \"attachment; filename= \%s\" \% \" " + fileName + "\")\nmsg.attach(part)\nserver = smtplib.SMTP('smtp.gmail.com', 587)\nserver.starttls() \n";
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

int main()
{

   sendToEmail("ams.software.team@gmail.com","Amsisrich@45","harshilramani9777@gmail.com","TESTING","HELLO IS THAT SUCCESSFULL","C:\\Users\\DELL\\OneDrive\\Desktop\\cashback 3000\\NOC_w.pdf","happy.pdf");

    return 0;
}