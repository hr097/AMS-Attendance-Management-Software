#include <iostream>

#include <fstream>

#include <windows.h>

using namespace std;

void lockfolder();

void unlockfolder();

// void setcolour(unsigned int colour);

int main()

{

unsigned int choice=0;

SetConsoleTitle("Folder Lock");

system("CLS");

// setcolour(14);

cout << "\t\t\t\t" << "- Evil Genious\n";

cout << "\t\t\t\t" << "-----------------\n";

// setcolour(15);

// setcolour(30);

cout << "\n\n" << "Options:\t\t\t\n";

cout << "\t======================\n";

cout << "\t1. - Lock Folder.\n";

cout << "\t2. - Unlock Folder.\n";

cout << "\t3. - Exit.\n";

cout << "\t====================== \n";

// setcolour(128);

cout << "\nEnter your choice: ";

cin >> choice;

switch (choice)

{

case 1: lockfolder(); break;

case 2: unlockfolder(); break;

case 3: exit(0); break;

default: cout << "\nError. Unknown Option Entered. Quitting ....\n"; break;

}

return 0;

}

/* void setcolour(unsigned int colour)

{

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

SetConsoleTextAttribute(handle, colour);

}*/

void lockfolder()

{

char pass[15]="";

ofstream lfolder;

char folder[200]={0};

char tempfolder[200]={'0'};

char attributes[50]={'0'};

// setcolour(13);

cout << "\nEnter the complete path to the Folder: ";

cin >> folder;

strcpy(tempfolder, folder);

strcat(folder, "\\Desktop.ini");

lfolder.open(folder, ios::out);

lfolder << "[.shellClassInfo]" << endl;

lfolder << "CLSID = {63E23168-BFF7-4E87-A246-EF024425E4EC}" << endl;

lfolder.close();

strcpy(attributes, "attrib +h +s ");

strcat(attributes, tempfolder);

WinExec(attributes, NULL);

lfolder.open("C:\\windows\\db.dat", ios::app);

lfolder << "Folder Locked: " << tempfolder << endl;

lfolder.close();

cout << "\n\n" << tempfolder << " has been locked successfully!\n";

}

void unlockfolder()

{

char folder[255];

char tempfolder[255];

char attributes[50];

char del[50];

ofstream lfolder;

// setcolour(14);

cout << "\nEnter the complete path to the Folder: ";

cin >> folder;

strcpy(tempfolder, folder);

strcat(folder, "\\Desktop.ini");

strcpy(del, "del ");

strcat(del, folder);

system(del);

strcpy(attributes, "attrib -h -s ");

strcat(attributes, tempfolder);

WinExec(attributes, NULL);

lfolder.open("C:\\windows\\db.dat", ios::app);

lfolder << "! Folder Unlocked: " << tempfolder << endl;

lfolder.close();

cout << "\n\n" << tempfolder << " has been unlocked successfully!\n";

}