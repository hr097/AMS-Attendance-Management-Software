#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
    char key_press;
    int ascii_value;
    cout<<"\n\t\t\tPress Any Key To Check  Its ASCI Value\n\n\t\t\tPress ESC to EXIT\n\n\n";
    while(1)
    {
    key_press=getch();
    ascii_value=key_press;
    if(ascii_value==27) // For ESC
     break;
   cout<<"\t\t\tKEY Pressed-> \" "<<key_press<<" \" Ascii Value =  "<<ascii_value<<"\n\n";
    }
    return 0;
}