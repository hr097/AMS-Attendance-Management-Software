// CPP program to illustrate
// std::find
// CPP program to illustrate
// std::find
#include<iostream>
#include<vector>
#include<algorithm>

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

int main ()
{
	vector<string> v;
	
	v.push_back("drashti");
	v.push_back("shikhaa");
	v.push_back("fenil");
	
	// Iterator used to store the position
	// of searched element
	//vector<string>::iterator it;
	
	// Print Original Vector
//	std::cout << "Original vector :";
	
// 	for (auto i=0; i<vec.size(); i++)
// 		std::cout << " " << vec[i];
		
// 	std::cout << endl;
	
	// Element to be searched
	string s = "Fenil";
	
	if(checkDuplicate(v,s))
	{
	   cout<<"Element addedd "<<endl; 
       v.push_back("Fenil");
	}
	else
	{
	    cout<<"Element has already been added "<<endl; 
	}
	
	// std::find function call

    // Print Original Vector
    cout << "Original vector :";
    	
    for (auto i=0; i<v.size(); i++)
	cout << " " << v[i];
	
	
	
		
	return 0;
}
