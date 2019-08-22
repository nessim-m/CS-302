#include <iostream>
#include "Assign7.h"
#include <fstream>
#include <cstdlib>


using namespace std;


/*the following struct type which you will declare in main to assign to the templated type
in the binMaxHeap, the heap will contain pointers of carType.*/
struct carType
{
string name;
int currentSpeed;
double distance;
int maxSpeed;

bool operator >( carType rhs )
{

return distance > rhs.distance;

}

};


int main()
{
	string filename;// string to read in the filename
	fstream infile;// fstream to read from the file
	carType *cars;
	int size=5;

	cars= new carType[size];

	//prompt user to enter a valid file name.
	do
	{

		cout<< "Enter a filename: ";
		cin>> filename;

 		//filename.c_str() returns a C style string version
		infile.open(filename.c_str());

	}
	while(!infile.is_open());

	int counter=0;

	while(!infile.eof())
	{
		infile>>cars[counter].name>>cars[counter].maxSpeed;// read in from the file
		cars[counter].currentSpeed=0;//set current speed to 0
		cars[counter].distance=0.0;//set distance to 0
		counter++;

		/*preform a deep copy and resize the struct object*/
		if(counter==size)
		{
			carType *tmpcars;
			tmpcars= new carType[size*2];
			//copy all the info to the resized tmp object
			for(int i=0; i<size; i++)
			{
				tmpcars[i].name=cars[i].name;
				tmpcars[i].maxSpeed= cars[i].maxSpeed;
				tmpcars[i].currentSpeed= cars[i].currentSpeed;
				tmpcars[i].distance= cars[i].distance;
			}

			delete [] cars;//dealloacte the old array object
			cars=NULL;
			cars=tmpcars;
			tmpcars=NULL;
			size= size*2;

		}

	}


	binMaxHeap<carType> race;

	//cout<<"Counter: "<< cars[0].maxSpeed<<endl;

	for(int i=0; i<counter; i++)
	{
		race.insert(&cars[i]);
	}

	//cout<<"Counter: "<< cars[0].maxSpeed<<endl;

	while(race.isEmpty()!= true)
	{
		int rank=1;
		//checks for the finish line
		if(race.getMax()->distance >=10000.0)
		{	
			cout<<"Rank"<<rank<<": "<< race.getMax()->name<<endl;
			race.deleteMax();
			counter--;
		}

		//adjust the current speed and distance of all the cars
		for(int i=0; i< counter; i++)
		{
			int initialSpeed= cars[i].maxSpeed/2;
			int maximumSpeed= cars[i].maxSpeed/2;
			cars[i].currentSpeed= rand()%  initialSpeed + maximumSpeed;
			cars[i].distance=(cars[i].currentSpeed/3600.0)+cars[i].distance;
			
		}

		// bubble up the all the cars
		for(int j=1; j<=counter; j++)
		{
			race.bubbleUp(j);
		}

	}


return 0;
}
