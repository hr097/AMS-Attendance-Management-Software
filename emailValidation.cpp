#include<iostream>
#include<regex>
#include<stdio.h>
using namespace std;

bool Email_check(string email)
{
     const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email,pattern);
}
int main()
{
    string str;
    cout<<"Enter your Email-Id:"<<endl;
    cin>>str;
    if(Email_check(str))
        cout<<"Your Email-Id is valid"<<endl;
    else
        cout<<"Your Email-Id is invalid"<<endl;
    return 0;
}