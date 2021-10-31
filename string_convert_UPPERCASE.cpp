#include<iostream>
#include <algorithm>

using namespace std;

int main()
{
   
   string data="hello world";

   transform(data.begin(),data.end(),data.begin(),::toupper);
   
   cout<<data<<endl;
   data="HELLO JSN";
   transform(data.begin(),data.end(),data.begin(),::tolower);  
   cout<<data<<endl;

    return 0;
}