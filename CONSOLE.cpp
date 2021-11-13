#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;
void setCursorPos(int x, int y = 0) //?IMPORTANT : ->relative position is set
{

    //*vertical lines space

    while (x > 0)
    {
        cout << endl;
        x--;
    }
    while (y != 0) //*horizontal cursor space by 1 charecter
    {
        printf(" ");
        y--;
    }
}

void buildVerticalWall(int briks) //? for making vertical side
{
    cout << "*";
    while (briks > 0)
    {
        cout << "-";
        briks--;
    }
    cout << "*";
}
void buildHorizontalWall(int endBrick, string data) //? for making horizontal side
{
    cout << "|";
    int run = 1;
    while (run < endBrick)
    {

        if (run == (endBrick / 6)) //
        {
            cout << data;
            run += (data.length() - 1);
            cout << " ";
        }
        else
        {
            cout << " ";
        }

        run++;
    }
    cout << "|";
}
int main()
{

    setCursorPos(3, 35);
    buildVerticalWall(35);
    setCursorPos(1, 35);
    buildHorizontalWall(35, " ");
    string data;
    int i=0;
    ifstream fin("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\MBBS-SEM-3-HUMAN-ANATOMY\\FAC-STUD-DETAILS\\faculty-sem-3.txt");

    if (!fin.is_open())
    {
        cout << "file is not open";
    }
    else
    {
        while (!fin.eof())
        {
            while (getline(fin,data))
            {
                setCursorPos(1, 35);
                buildHorizontalWall(35, data);
                setCursorPos(1, 35);
                buildHorizontalWall(35, " ");
            }
        }
    }
    setCursorPos(1, 35);
    buildVerticalWall(35);
    fin.close();
    return 0;
}