#include<iostream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<algorithm>

using namespace std;


//! need to set AMS DATABASE path be we can't directly create file in program *86 file
//! later on after shubham's review we will change the path according to him
//! PYCACHE FOLDER will be automatically created so need to discuss on that

   int countLinesOfFile(string FilePath) //? function for counting lines in text file
   {   
       string data; // store data temp variable
       int lines=0; // to store the lines

       ifstream read(FilePath.c_str(),ios::in); // reading mode file opened

       if(!read.is_open()) 
       {
           cout << "DATA BASE-ERROR-404 ! ";//error
           //scrClr(2);
           //exit(1);
           return(0);
       } 
       else
       {   
           getline(read,data); // take first line

           while(!read.eof())
           {
               lines++;
               getline(read,data);
           }

           read.close();
   
       }

       return(lines);

   } 

   void writeDataToFile(string path, string &FcName) //?write string data to given path file
   {
    ofstream write(path.c_str(), ios::app); //file opend in reading mode for getting data

    if (!write.is_open())//if file is not open than print path error
    {
      cout << "DATA BASE-ERROR-201-204! ";//error
      // scrClr(2);
      //exit(1);
    }
    else//if file is open than write data in file
    {
      write << FcName << endl; // write data
    }
    write.close();//file close
  }

  void getDataFromFile(string path, string &input, int lineNo) //?get Data of given path file line by line in string
  {
    ifstream get(path.c_str(),ios::in); //file opend in reading mode for getting data

    if(!get.is_open())//if file is not open than print error
    {
       cout << "DATA BASE-ERROR-404 ! ";//error
       //scrClr(2);
      // exit(1);
    }
    else//if file is open
    {
      int FileLine = 1; // start from first line
      while(FileLine<= lineNo)//whille fileline is <= lineno than
      {
        getline(get,input); // read and get data
        FileLine++;
      }
    }
   get.close(); //file closed
   }

int makePdf(string atachmentPath,string pdfName) //? making pdf
{   
    vector<string> LIST; //! remove it later
    string command,AMS_Path="C:\\Users\\DELL\\OneDrive\\Documents\\AMS"; // make string for file making  //! need to remove this
    
    for(int i=1;i<= countLinesOfFile(atachmentPath);i++)
    {   
        command.clear();
        getDataFromFile(atachmentPath,command,i);
        LIST.push_back(command);
    }
    
    // cout<<endl<<"LIST DATA :";
    // for(auto j=LIST.begin();j!=LIST.end();j++)
    // {
        // cout<<endl<<*(j);
    // }

    //TODO : SHUBHAM KHUNT LIST VECTOR HAS ALL DATA WHICH WILL BE INCLUDED IN PDF AND
    //TODO : WE HAVE TO MAKE TABLE ACCORDING TO THAT DATA WHENEVER YOU ARE FREE JUST TELL ME
    //TODO : WE WILL DO DISCUSSION AND CHNAGES
    
    command.clear(); // clear for re-using

    command = AMS_Path + "\\OTHER\\pdf.py"; // make database path

    fstream write(command.c_str(),ios::out); // file opened in wrtting mode

    if(!write.is_open()) // if file  not opened
    {
        cout << "DATA BASE-ERROR-201-204! ";//error 
        return(0);
    }
    else //CREATE EMAIL PYTHON FILE
    {   
        command.clear();

        command ="from fpdf import FPDF\npdf = FPDF()\npdf.add_page()\npdf.set_font(\"Arial\", size = 15)\npdf.cell(200, 10, txt = \"Fedingo.com\", ln = 1, align = 'C')\npdf.cell(200, 10, txt = \"Useful tech articles\", ln = 2, align = 'C')\n";
        command = command + "pdf.output(\"" + pdfName + "\")";

        write<<command; //WRITE TO PY PDF CODE FILE
        write.close();// file closed

        command.clear();
        command = "python "+AMS_Path + "\\OTHER\\pdf.py"; 
        
        system(command.c_str()); // FILE SENDING CODE HERE by running python file

        command.clear(); // clear for re-using
        command = AMS_Path + "\\OTHER\\pdf.py"; // make database path

        remove(command.c_str()); //delete file

        return(1);// work successful
    }
}

int main()
{

   makePdf("C:\\Users\\DELL\\OneDrive\\Desktop\\userdetails.txt","userdetails.pdf");

   return 0;
}