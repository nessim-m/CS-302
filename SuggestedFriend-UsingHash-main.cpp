#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Assign6.h"
using namespace std;



int main()
{

	myHash<char, bool> h;// create myHash object of type1 char and type2 bool
	int testCases;//testcases variable
	string name;//name to compare with

	cin>>name>>testCases;

	// hash name by calling the operter[] function
		for(int j=0; j< name.length(); j++)
		{
			h[toupper(name[j])]=true;

		}

	//The following loops through all the cases on the file and compare it with name
	for(int i=0; i<testCases;i++)
	{

		int k,s;//amount of names and the largest s amount to output
		string *arrayNames;//dynamic array to store names to be compared
		int *arrayMatch;//dynamic array to store the matches for each name compared
		cin>>k>>s;

		arrayNames= new string[k];//create a pointer array for amount of name size
		arrayMatch= new int[k];//create a pointer array for matches of name size

		//the following loop assign the whole array to 0
		for(int v=0; v< k; v++)
		{
			arrayMatch[v]=0;
		}

		//the following loop is reading in the comparing names in to the array
		for(int l=0; l<k; l++)
		{

			cin>>arrayNames[l];

			//the following loop  does the hashing for the comparing names and check if they match
			for(int j=0; j< arrayNames[l].length(); j++)
			{	
				//if a letter match then increment by 1 in the arrayMtach at a given index
				if(h[toupper(arrayNames[l][j])])
				{
					arrayMatch[l]++;
				}
				//if not hash the letter but set its item to false
				else
				{
					h[toupper(arrayNames[l][j])];
				}
			}

		}


		//_______________________________________________



		/*the following is a bubble sorting from larger to smaller*/
		 for (int p = 0; p < k-1; p++)     
		 {  
		    for (int u = 0; u < k-p-1; u++) 
		    {
		        if (arrayMatch[u] < arrayMatch[u+1]) 
		        {
		            swap(arrayNames[u], arrayNames[u+1]);
		            swap(arrayMatch[u], arrayMatch[u+1]); 
		        }
		     }
		 }


		//___________________________________________________

		//the following loop outputs the largest s names that have a match
		 cout<<"Case "<<i+1<<" ";
		for(int b=0; b<s; b++)
		{
			cout<<arrayNames[b]<<" ";
		}

		cout<<endl;

		delete[] arrayNames;//deallocate the array

		arrayNames=NULL;

		delete[] arrayMatch;//deallocate the array

		arrayMatch=NULL;

	}

	return 0;
}
