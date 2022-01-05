#include<iostream>
#include<fstream>
#include<conio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<math.h>
#include <sstream>
#include<iomanip>
#include <stdbool.h>
using namespace std;
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
        lines++;//!must add this line in index.cpp code if file does not have 
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
string DoubleBackslashPath(string path)//?insering backslash in path for paython file
{
    int found = path.find("\\",0);//find backslash
    while(found<path.length())//check whether the backslash index no. outof range or not
    {
        path.insert(found,"\\");//insert onr backslash
        found = path.find("\\",found+2);//found backslash again from (found+2)
    }
    return path;//return path
}
int createSixMonthReport(string BasicDetails,string Name,string Percentage,string pdf_name)//?Date Vise Report Generate PDF(If overloding posssible then must overload  GeneratePDF function)
{
    int PresentCount;
    string command,temStorage,AMS_Path= "C:\\Users\\DELL\\OneDrive\\Documents\\{JSN-1008-JSK-22-10-2021}",Sem_Path = "C:\\Users\\DELL\\OneDrive\\Documents\\{JSN-1008-JSK-22-10-2021}\\BCA-SEM-2-CPP";//just temprarory string (delete)
    command.clear();
    command = AMS_Path+"\\OTHER\\6MR_1.py"; // make paython path
    fstream write(command.c_str(),ios::out);
    if(!write.is_open()) // if file  not opened
    {
        cout << "DATA BASE-ERROR-201-204! ";//error 
        return(0);
    }
    else
    {
        command.clear();
        command = "from fpdf import FPDF\npdf=FPDF(format='A4', unit='in')\npdf.add_page()\nepw = pdf.w - 2*pdf.l_margin\npdf.set_font('Arial','B',50.0)\npdf.set_text_color(0,0,0)\n";
        command += "pdf.image('"+DoubleBackslashPath(AMS_Path)+"\\\\OTHER\\\\Telegram.png',x =pdf.l_margin,y=None,w=pdf.w - 2*pdf.l_margin, h=1.5)\npdf.cell(epw, -1.3, 'A M S', align='C')\npdf.ln(0.5)\npdf.line(0.4,1.90,7.8,1.90)\npdf.line(0.4,1.97,7.8,1.97)\npdf.set_font('Arial','B',15.0)\npdf.set_text_color(43, 153, 213)\npdf.cell(epw, 0.0, 'e-ATTENDANCE REPORT', align='C')\npdf.ln(0.5)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(0,0,0)\n";
        getDataFromFile(BasicDetails,temStorage,1);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Faculty Name
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,2);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Faculty Joining Year
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,3);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Department Name
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,4);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Course name
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,5);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Semester
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,6);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Subject Name
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,7);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Report type
        temStorage.clear();
        getDataFromFile(BasicDetails,temStorage,8);
        command += "pdf.cell(epw,0.0,'"+temStorage+"', align='L')\npdf.ln(0.3)\n";//Records
        command += "data = [['ROLL NO.','NAME','ATTENDANCE']";
        for(int i=1;i<=countLinesOfFile(Name);i++)
        {
            command += ",['" + to_string(i) + "',"; 
            temStorage.clear();
            getDataFromFile(Name,temStorage,i);
            command += "'" + temStorage + "',";
            PresentCount = 0;
            for(int k=1;k<=(countLinesOfFile(Percentage));k++)
            {
                temStorage.clear();
                getDataFromFile(Percentage,temStorage,k);

                if(temStorage[19+i] == 'P')
                    PresentCount++;
            }
            stringstream stream;
            stream << fixed << setprecision(2) << (float(100 *  PresentCount)/countLinesOfFile(Percentage));
            string temp = stream.str();
            command += "'"+temp+"%'";
            command+= "]";
        }
        command += "]\n";
        command += "th = pdf.font_size\ncol_width = (epw-4)/2\npdf.ln(0.3)\n";
        command += "for row in range(len(data)):\n\tfor datum in range(len(data[row])):\n\t\tif row==0:\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\t\telse:\n\t\t\tpdf.set_text_color(0,0,0)\n\t\t\tpdf.set_font('Arial','',12.0)\n\t\t\tif datum == 1:\n\t\t\t\tpdf.cell(4, 2*th,data[row][datum], border=1,align='C')\n\t\t\telse:\n\t\t\t\tpdf.cell(col_width, 2*th,data[row][datum], border=1,align='C')\n\tpdf.ln(2*th)\npdf.ln(2)";
        command += "\nLine = \"_\"\nfor i in range(int(pdf.w-pdf.l_margin)):\n\tfor j in range(10):\n\t\tLine+=\"_\" ";
        command += "\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(3, 153, 213)\npdf.cell(epw,0.0,'Have any questions for us or need more information?',align='C')\npdf.ln(0.3)\npdf.set_font('Arial','B',12.0)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0,Line, align='C')\npdf.ln(0.22)\npdf.set_text_color(0,0,0)\npdf.cell(epw,0.0,'Email Address For Support   \"ams.software.team@gmail.com\"',align='C')\npdf.ln(0.1)\npdf.set_text_color(255,0,0)\npdf.cell(epw, 0.0,Line,align='C')\npdf.ln(0.5)\npdf.set_text_color(255,0,0)\npdf.set_font('Arial','B',15.0)\npdf.cell(epw,0.0,'Regards, Team AMS.',align='C')\npdf.output('"+DoubleBackslashPath(Sem_Path) +"\\\\REPORTS\\\\";
        command +=  pdf_name + "','F')\n";
        temStorage.clear();
        temStorage = AMS_Path+"\\OTHER\\6MR.py";   // make python File
        writeDataToFile(temStorage,command);

        command = "python " + AMS_Path+"\\OTHER\\6MR.py";  
        system(command.c_str());//run paython file

        command = AMS_Path+"\\OTHER\\6MR.py"; 
        remove(command.c_str()); //delete paython file
        remove(BasicDetails.c_str());//delete fec_data file
        remove(Name.c_str());//delete stud_name file
        remove(Percentage.c_str());//delete stud_att file
        return 1;

    }
}
int main()
{
     createSixMonthReport("C:\\Users\\DELL\\OneDrive\\Documents\\{JSN-1008-JSK-22-10-2021}\\BCA-SEM-2-CPP\\REPORTS\\fec_data.txt","C:\\Users\\DELL\\OneDrive\\Documents\\{JSN-1008-JSK-22-10-2021}\\BCA-SEM-2-CPP\\REPORTS\\stud_name.txt","C:\\Users\\DELL\\OneDrive\\Documents\\{JSN-1008-JSK-22-10-2021}\\BCA-SEM-2-CPP\\REPORTS\\stud_per.txt","6MR.pdf");
}