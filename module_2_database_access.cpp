#include<iostream>  //*C++ std input out put use
#include<string>   //* C++ STRING STL use
#include<fstream> //* file handling use
#include<vector> //*STL DYNAMIC ARRAY used
#include<algorithm> //* STL class use
#include<stdlib.h> //*c language standard library functions
#include<tuple>   //* for using tuples (group of element key->value type)
#include<iterator>
#include<unistd.h>
#include<stdbool.h> // * boolean operation
#include<windows.h> // * windows console related functions handle
#include<math.h>

using namespace std;

int checkDuplicateRecord(vector<string> vec,string search) //*for cheking if duplicate records found in vector_storage
{
    vector<string>::iterator it; //iterator

    it = find(vec.begin(), vec.end(),search); // finding elemnt in vector

    if (it != vec.end())
	{
      return 0; // if found then return 0
	}
	else
    {
      return 1; // if not found then return 1
    }
}

void scrClr(float i=0.0) //*for clearing screen afer some time
{
  //*by default set to zero with default arguements
  sleep(i); // * going in sleep mode
  system("cls"); // * clear screen
}

  void buildVerticalWall(int briks) //* for making rectangle shape
  { cout<<"*";
    while(briks>0){cout<<"-";briks--;}
    cout<<"*";
  }
  
  void buildHorizontalWall(int endBrick,string data) //* for making rectangle shape
  { 
    cout<<"|";
    int run=1;
    int line_start = int(endBrick / 6);
  
    while(run<endBrick)
    {
      
      if(run == line_start)
      {
        cout<<data;
        run+=(data.length()-1);
        cout<<" ";
      }
      else
      {
      cout<<" ";
      }
  
     run++;
    } 
    cout<<"|";
  }

 void setCursorPos(int x, int y=0) //IMPORTANT : ->relative position is set
{
  
  //*vertical lines space 
  
  while(x>0)
  {
    cout<<endl;  
    x--;
  }
  while(y!=0) //*horizontal cursor space by 1 charecter
  {
    printf(" ");
    y--;
  }
  
}

void ShowConsoleCursor(bool showFlag) //* for hiding the cursor just  set showFlag = false(bool value)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
  
    CONSOLE_CURSOR_INFO     cursorInfo;
  
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}


int main()
{
    vector<string> buffer,LIST; //vector buffer for file handling data receiver

    string TEMP_STR[4];//course name , sem , sub , folder_accces_path
    
    vector<tuple<string,string,string,string>> DATA; // search-access vector-tuple

    fstream fin("C:\\Users\\DELL\\OneDrive\\Documents\\AMS\\OTHER\\semesterRecord.txt",ios::in); // file opened in reading mode
    
    if(!fin.is_open()) // if not opened
    {
        cout<<" FILE NOT OPENED !";
    }
    else // if opened
    {
        getline(fin,TEMP_STR[1]); // TEMP_STR[1] used as temporary storage
        
        while(!fin.eof()) // data receive until file ends
        {    
            buffer.push_back(TEMP_STR[1]); // save that string(data) in vector
            getline(fin,TEMP_STR[1]); // fetch again from file
        }  
    }

    sort(buffer.begin(), buffer.end()); //sorted file data in vector in Dictionary order

    for (auto i = buffer.begin(); i != buffer.end(); ++i) //insert in to vector-tuple from vector buffer with extracting string
    {
        string data = (*i); // temp variable for moving vector data to string
        int found_pos,temp_pos; // temp variable for position storing

        found_pos = data.find("|"); // find the first occurance of '|'
        TEMP_STR[0] = data.substr(0,(found_pos)); // get proper course name from string and save it to TEMP_STR[0]
        temp_pos = (found_pos+1); // making next finding position

        if(checkDuplicateRecord(LIST,TEMP_STR[0])) // cheking if duplicate 
        {
            LIST.push_back(TEMP_STR[0]); //making list for input of UI screen
        }
        
        found_pos = data.find("|",temp_pos);     //finds string till 1st pipe i.e coursename
        TEMP_STR[1] = data.substr(temp_pos,(found_pos-temp_pos));//stores the string in TEMP_STR
        temp_pos = (found_pos+1);  //searching next position

        found_pos = data.find("|", temp_pos);   //finds string till 2nd pipe i.e. semester
        TEMP_STR[2] = data.substr(temp_pos,(found_pos-temp_pos)); //stores the string in TEMP_STR
        temp_pos = (found_pos+1);  //searching next position
         
        found_pos = data.find("|", temp_pos); //finds string till 3rd pipe i.e. subjectname
        TEMP_STR[3] = data.substr(temp_pos); //stores the string in TEMP_STR

        DATA.push_back(make_tuple(TEMP_STR[0],TEMP_STR[1],TEMP_STR[2],TEMP_STR[3]) ); //makes a final string to display
    }

    //cout<<endl<<"String Data : "<<endl;
    int flag = 1,CH_FLAG=0,count_flag=0;
    auto i = LIST.begin();
    setCursorPos(1,20);
    buildVerticalWall(30);
    setCursorPos(1,20);
    buildHorizontalWall(30," ");
        
    //cout << LIST.size();
    while(i != LIST.end()) 
    {
        
        // cout << temp;
        start:
        //flag = 0;
        CH_FLAG=0;
        setCursorPos(1,20);
        buildHorizontalWall(30,to_string(5*count_flag+flag) + ") " + (*i)); 
        setCursorPos(1,20);
        buildHorizontalWall(30," "); 
        flag++;
        i++;
        //cout << "flag : " << flag;
        
        if(flag > 5 && i !=LIST.end())
        {
         
            CH_FLAG=1;
            count_flag++;
            setCursorPos(1,20);
            buildHorizontalWall(30,"             More...");
            setCursorPos(1,20);
            buildVerticalWall(30);
            ShowConsoleCursor(true);
            cout<<endl<<"choose course : ";
            getline(cin,TEMP_STR[0]);
            ShowConsoleCursor(false);
            flag = 1;
            scrClr(0.5);
            if(TEMP_STR[0]=="+")
            {
                setCursorPos(1,20);
                buildVerticalWall(30);
                goto start;
            }
            else
            {
                break;
            }
        
        
        }
    }
    if(CH_FLAG==0)
    {
        setCursorPos(1,20);
        buildVerticalWall(30);
        ShowConsoleCursor(true);
        cout<<endl<<"choose course : ";
        getline(cin,TEMP_STR[0]);
        ShowConsoleCursor(false);
        scrClr(0.5);

    }

    LIST.clear();//flush vector data for re-using

    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find searched data by user
     {   
       
         if(TEMP_STR[0]==get<0>((*i))) //! input required
         {   
            if(checkDuplicateRecord(LIST,get<1>((*i)))) // cheking if duplicate 
            {
                LIST.push_back(get<1>((*i))); //making list for input of UI screen
            }
         }
                
     }
    
    flag = 1,CH_FLAG=0;
    i = LIST.begin();
    setCursorPos(1,20);
    buildVerticalWall(20);
    setCursorPos(1,20);
    buildHorizontalWall(20," "); 
        
    while(i != LIST.end()) 
    {
        start1:
        //flag = 0;
        setCursorPos(1,20);
        buildHorizontalWall(20,"Sem-"+(*i)); 
        setCursorPos(1,20);
        buildHorizontalWall(20," "); 
        flag++;
        i++;
        //cout << "flag : " << flag;
                
        if(flag > 5 && i !=LIST.end())
        {
            CH_FLAG=1;
            setCursorPos(1,20);
            buildHorizontalWall(20,"                 More...");
            setCursorPos(1,20);
            buildVerticalWall(20);
            ShowConsoleCursor(true);
            cout<<endl<<"choose Semester : ";
            getline(cin,TEMP_STR[1]);
            ShowConsoleCursor(false);
            flag = 1;
            scrClr(0.5);
            if(TEMP_STR[1]=="+")
            {
                setCursorPos(1,20);
                buildVerticalWall(20);
                goto start1;
            }
            else
            {
                break;
            }
                
        }
    }
    if(CH_FLAG==0)
    {
        setCursorPos(1,20);
        buildVerticalWall(20);
        ShowConsoleCursor(true);
        cout<<endl<<"choose Semester : ";
        getline(cin,TEMP_STR[1]);
        ShowConsoleCursor(false);
        scrClr(0.5);
    }

    LIST.clear();//flush vector data for re-using
    
    // cout<<endl<<"choose semester : ";
    // getline(cin,TEMP_STR[1]);
    // scrClr(0.5);


    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find searched data by user
     {   
       
         if(TEMP_STR[0]==get<0>((*i))&&TEMP_STR[1]==get<1>((*i))) //! input required
         {
            if(checkDuplicateRecord(LIST,get<2>((*i)))) // cheking if duplicate 
            {
                LIST.push_back(get<2>((*i))); //making list for input of UI screen
            }
         }
                
     }
     
     flag = 1,CH_FLAG=0;
     i = LIST.begin();
     setCursorPos(1,20);
     buildVerticalWall(20);
     setCursorPos(1,20);
     buildHorizontalWall(20," "); 
         
     while(i != LIST.end()) 
     {
         start2:
         //flag = 0;
         setCursorPos(1,20);
         buildHorizontalWall(20,to_string(flag) + ") " + (*i)); 
         setCursorPos(1,20);
         buildHorizontalWall(20," "); 
         flag++;
         i++;
         //cout << "flag : " << flag;
                 
         if(flag > 5 && i !=LIST.end())
         {
             CH_FLAG=1;
             setCursorPos(1,20);
             buildHorizontalWall(20,"                 More...");
             setCursorPos(1,20);
             buildVerticalWall(20);
             ShowConsoleCursor(true);
             cout<<endl<<"choose Subject : ";
             getline(cin,TEMP_STR[2]);
             ShowConsoleCursor(false);
             flag = 1;
             scrClr(0.5);
             if(TEMP_STR[2]=="+")
             {
                 setCursorPos(1,20);
                 buildVerticalWall(20);
                 goto start2;
             }
             else
             {
                 break;
             }
                 
         }
     }
     if(CH_FLAG==0)
     {
         setCursorPos(1,20);
         buildVerticalWall(20);
         ShowConsoleCursor(true);
         cout<<endl<<"choose Subject : ";
         getline(cin,TEMP_STR[2]);
         ShowConsoleCursor(false);
         scrClr(0.5);
     }

    // for (auto i =LIST.begin(); i !=LIST.end(); ++i)
    // cout<<endl<< *i;; //displaying final subjectlist

    LIST.clear();//flush vector data for re-using
     

    cout<<endl<<"searched data :"<<endl;

    TEMP_STR[3]="NOT FOUND !";// set temp_str = not found flag so if data not found then print it

    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find folder path using vector tuple we have 3 input parameter coursename , sem , subject name
    {   
      
        if(TEMP_STR[0]==get<0>((*i)))
            if(TEMP_STR[1]==get<1>((*i)))
                if(TEMP_STR[2]==get<2>((*i)))
                      TEMP_STR[3]=get<3>((*i)); 
      
    }

    cout<<endl<<TEMP_STR[3]; 

    return 0;
}