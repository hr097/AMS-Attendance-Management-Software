#include<iostream>
#include<ctime>
#include<string>
#include<sstream>

using namespace std;

stringstream ss;
string temp;

// time_t tmNow; // structure variable
// tmNow = time(NULL); 
// struct tm t = *localtime(&tmNow);   //pre defined function
// 
void getDate(string &dt) // to get current date 
{  

   time_t tmNow; // structure variable
   tmNow = time(NULL); 
   struct tm t = *localtime(&tmNow);   //pre defined function

   ss<<t.tm_mday;
   temp = ss.str();
   dt = temp;

   ss.str("");

   ss<<(t.tm_mon+1);
   temp = ss.str();
   dt = dt + "/";
   dt = dt + temp;
   
   ss.str("");

   ss<<(t.tm_year+1900);
   temp = ss.str();
   dt = dt + "/";
   dt = dt + temp;
   
   ss.str("");

}

void getTime(string &dt) // to get current date 
{  
   time_t tmNow; // structure variable
   tmNow = time(NULL); 
   struct tm t = *localtime(&tmNow);   //pre defined function

   int meridiem_Flag=0; //0=AM 1=PM

   if(t.tm_hour>12)
   {
       t.tm_hour=(t.tm_hour-12);
       meridiem_Flag=1;    
   } 

   ss<<t.tm_hour;
   temp = ss.str();
   dt = temp;
   
   if(stoi(dt)<10)
   {
       dt = "0" + dt;
   }

   ss.str("");

   ss<<(t.tm_min);
   temp = ss.str();

   if(stoi(temp)<10)
   {
       temp = "0" + temp;
   }

   dt = dt + ":";
   dt = dt + temp;
   
   ss.str("");

   
   dt+=(meridiem_Flag==0)?" AM":" PM";

}

int main()
{
    string str;
    getDate(str);
    cout<<str<<endl;    

    getTime(str);
    cout<<str<<endl;
 
    return 0;
}