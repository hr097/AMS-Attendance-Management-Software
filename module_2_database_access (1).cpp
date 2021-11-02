#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<tuple>

using namespace std;



int checkDuplicate(vector<string> vec,string search)
{
    vector<string>::iterator it;

    it = find(vec.begin(), vec.end(),search);

    if (it != vec.end())
	{
      return 0;
	}
	else
    {
      return 1;
    }
}

int main()
{
    
    vector<string> buffer; //vector buffer for file handling data receiver
    string TEMP_STR[4];//course name , sem , sub , accces_path
    vector<tuple<string,string,string,string>> DATA; // search-access vector-tuple
    int j=0;

    fstream fin("sample.txt",ios::in);
    
    if(!fin.is_open())
    {
        cout<<" FILE NOT OPENED !";
    }
    else
    {
        getline(fin,TEMP_STR[1]);
        
        while(!fin.eof())
        {    
            buffer.push_back(TEMP_STR[1]);
            getline(fin,TEMP_STR[1]);
        }  
    }
    
    cout<<endl<<"bufferdata : "<<endl;  //checkinf data in vector buffer

    for (auto i = buffer.begin(); i != buffer.end(); ++i)
        cout << *i<<endl;

    sort(buffer.begin(), buffer.end()); //sorted file


    for (auto i = buffer.begin(); i != buffer.end(); ++i,++j) //insert in to vector-tuple from vector buffer
    {
        string data = (*i);
       
        int found_pos = data.find("|");
        
        TEMP_STR[0] = data.substr(0,(found_pos));
        //if()
        //{
        /*store*/
        //}
        int temp_pos = (found_pos+1);
        
        found_pos = data.find("|",temp_pos);
        TEMP_STR[1] = data.substr(temp_pos,(found_pos-temp_pos));
        temp_pos = (found_pos+1);

        found_pos = data.find("|", temp_pos);
        TEMP_STR[2] = data.substr(temp_pos,(found_pos-temp_pos));
        temp_pos = (found_pos+1);
         

        found_pos = data.find("|", temp_pos);
        TEMP_STR[3] = data.substr(temp_pos);
         
        DATA.push_back( make_tuple(TEMP_STR[0],TEMP_STR[1],TEMP_STR[2],TEMP_STR[3]) );
      

    }
     

     //* FENIL -SHIKHAA WORK

     TEMP_STR[1] = "IOT";
     TEMP_STR[2] = "1";
     TEMP_STR[3] = "arduino";
     
     //* FENIL -SHIKHAA WORK-END


     cout<<endl<<"searched data :"<<endl;

    for (auto i =DATA.begin(); i != DATA.end();++i) 
    {   
      
        if(TEMP_STR[1]==get<0>((*i)))
            if(TEMP_STR[2]==get<1>((*i)))
                if(TEMP_STR[3]==get<2>((*i)))
                  cout<<endl<<get<3>((*i));
                  else{cout<<endl<<"not found !";}
    }

    // vector<string> course_list;
    // vector<string> sem_list;
    // vector<string> sub_list;

    // j=0; //re-used

    // while(j!=buffer.size())
    // {    
    //    
        // if(!checkDuplicate(displayData[j][0],displayData,buffer.size(),0))
        // {
            // course_list.push_back(displayData[j][0]);
        // }
        // j++;
    // }
//    
    // for (auto i = course_list.begin(); i != course_list.end(); ++i)
        //    cout<<endl<< *i;

    //  j=0; //re-used
    //  while(j<=3)
    //  {    
        // 
        //  if(checkDuplicate(displayData[j][1],displayData,4,1))
        //  {
            //  sem_list.push_back(displayData[j][1]);
        //  }
        //  j++;
    //  }
    // 
    //for (auto i = sem_list.begin(); i != sem_list.end(); ++i)
           //   cout<<endl<< *i;
   
    
     return 0;
}