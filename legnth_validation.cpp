#include<iostream>

using namespace std;

bool LengthValidation(string &input,int l)
{
  if(input.length()<=l)
  {
    return(true);
  }
  else
  {
      return(false);
  }
}


int main()
{   
    string str;
    int length_input;

    while(true)
    { 
       fflush(stdin);
       cout<<endl<<"Enter string : ";
       getline(cin,str);
       
       cout<<endl<<"Enter max length : ";
       cin>>length_input;

       if(LengthValidation(str,length_input))
       {
           cout<<endl<<"VALID STRING LENGTH !"<<endl;
       }
       else
       {
            cout<<endl<<"INVALID STRING LENGTH !"<<endl;
       }
    }
    

    return(0);
}