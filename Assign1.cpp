	#include <iostream>
	#include <fstream>

	using namespace std;


	int main()
	{
		string filename;// string to read in the filename
		fstream infile;// fstream to read from the file

		int row,column;//variable to store rows and column read from the file
		int vertical,horizontal, product;//integer variable to store vertical and horizontal red book found and the product of them
		int firstPlus=1;//variable to storefirst plus sign found
		int secondPlus=1;//variable to storesecond plus sign found

		//prompt user to enter a valid file name.
		do
		{

			cout<< "Enter a filename: ";
			cin>> filename;

	 		//filename.c_str() returns a C style string version
			infile.open(filename.c_str());

		}
		while(!infile.is_open());


		infile>>row>>column;//reading in the column and row from the file 

		char ** array;//2d dynamic array 

		array= new char*[row];//rows

		//assign columns for the rows
		for(int i=0; i<row; i++)
		{
			array[i]= new char[column];
		}


		//reading in from the file to the array
		for (int i = 0; i <row; i++)
		{
			for(int j=0; j< column; j++)
			{
				infile>> array[i][j];

			}
		}
		int rowPosition[column];//array to store horizontal position of red books
		int columnCounter=0;//variable counter for the column
		int checkForTheLargest;//variable to check the biggest plus sign seen

		//storing zero into the array
		for(int n=0; n< column; n++)
		{
			rowPosition[n]=0;
		}

		//the following loops through the whole row given
		for(int i=0; i<row; i++)
		{
			//the following loops through the whole columns given
			for(int j=0; j< column; j++)
			{
				//the following if statment checks how many red book has it seen in a row and it increment horizontal by 1 and store there positions
				if(array[i][j]== 'R')
				{
					horizontal++;
					rowPosition[columnCounter]= j;
					columnCounter++;
					//cout<<horizontal<<endl;
				}
				//the following if statment resets the above variable if it didn't see 3 red books or more in a row
				if(array[i][j]!= 'R' and horizontal < 3)
				{
					horizontal=0;
					columnCounter=0;
					for(int n=0; n< column; n++)
					{
						rowPosition[n]=0;
					}
				}
				
			}
			//the following if statment excutes after the previous loop has located 3 or more red book in a row
			if(horizontal >=3)
			{
				int rowCounter=1;// variable counter
					//cout<< rowPosition[1]<<" : "<< rowPosition[columnCounter-1]<< endl;
				//the following for loop uses the positions of the red books stored and checks vertically
				for(int k= rowPosition[1]; k< rowPosition[columnCounter-1]; k++)
				{
					//the following while loop increments vertical by 2 every time it sees red book up and down
					while(array[i+rowCounter][k] == 'R' &&  array[i-rowCounter][k]=='R' && rowCounter<= (row/2)-1)
					{
						vertical= vertical+2;
						rowCounter++;
					}
				}

				//the following adds the vertical and horizontal that makes the plus sign
				checkForTheLargest= vertical + horizontal;
				//cout<< i<< endl;

				//if statment excutes if vertical is greater than or equal to 2
				if(vertical>=2)
				{
					//this if statment checks if firstPlus is equal to secondPlus and stores checkForTheLargest to firstPlus accordingly
					if(firstPlus < checkForTheLargest and firstPlus <=secondPlus)
					{
						firstPlus= checkForTheLargest;
					}
					/*this if statment checks if firstPlus is not equal to 0 and checForThelargest is larger than firstPlus and
					 stores checkForTheLargest to secondPlus accordingly*/
					else if(firstPlus != 0 and checkForTheLargest > firstPlus)
					{
						secondPlus= checkForTheLargest;
					}
				}
				
			}
			
			//reseting horizontal, vertical, and columnCounter to zero
			horizontal=0;
			vertical=0;
			columnCounter=0;
		}

		product= firstPlus * secondPlus;//finally it finds the product of the two biggest plus sign found

		
		cout<< "The product of the two biggest plus signs is: "<< product<< endl;//then it out puts it on the screen

		//The following it deallocate the dynamic array to prevent memory leaks
		for(int i=0; i< column; i++)
		{
			delete [] array[i];
		}

		delete [] array;




		return 0;
	}