#include<iostream>
#include<string> 
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<tuple>    //* for using tuples (group of element key->value type)

using namespace std;

int checkDuplicate(vector<string> vec,string search) //*for cheking if duplicate records found in vector_storage
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

int main()
{
    vector<string> buffer,LIST; //vector buffer for file handling data receiver

    string TEMP_STR[4];//course name , sem , sub , folder_accces_path
    
    vector<tuple<string,string,string,string>> DATA; // search-access vector-tuple

    fstream fin("sample.txt",ios::in); // file opened in reading mode
    
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

         if(checkDuplicate(LIST,TEMP_STR[0])) // cheking if duplicate 
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

    for (auto i =LIST.begin(); i !=LIST.end(); ++i)
    cout<<endl<< *i;; //displaying final course list

    LIST.clear();//flush vector data for re-using

    cout<<endl<<"choose course : ";
    cin>>TEMP_STR[0];

    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find searched data by user
     {   
       
         if(TEMP_STR[0]==get<0>((*i))) //! input required
         {   
            if(checkDuplicate(LIST,get<1>((*i)))) // cheking if duplicate 
            {
                LIST.push_back(get<1>((*i))); //making list for input of UI screen
            }
         }
                
     }
     
    for (auto i =LIST.begin(); i !=LIST.end(); ++i)
    cout<<endl<< *i;; //displaying final course list

    LIST.clear();//flush vector data for re-using
    
    cout<<endl<<"choose semester : ";
    cin>>TEMP_STR[1];


    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find searched data by user
     {   
       
         if(TEMP_STR[0]==get<0>((*i))&&TEMP_STR[1]==get<1>((*i))) //! input required
         {
            if(checkDuplicate(LIST,get<2>((*i)))) // cheking if duplicate 
            {
                LIST.push_back(get<2>((*i))); //making list for input of UI screen
            }
         }
                
     }

    for (auto i =LIST.begin(); i !=LIST.end(); ++i)
    cout<<endl<< *i;; //displaying final subjectlist

    LIST.clear();//flush vector data for re-using

    cout<<endl<<"choose subject : ";
    cin>>TEMP_STR[2];
     

    cout<<endl<<"searched data :"<<endl;

    TEMP_STR[3]="NOT FOUND !";// set temp_str = not found flag so if data not found then print it

    for (auto i =DATA.begin(); i != DATA.end();++i)  //process to find searched data by user
    {   
      
        if(TEMP_STR[0]==get<0>((*i)))
            if(TEMP_STR[1]==get<1>((*i)))
                if(TEMP_STR[2]==get<2>((*i)))
                      TEMP_STR[3]=get<3>((*i)); 
      
    }

    cout<<endl<<TEMP_STR[3]; 

    return 0;
}