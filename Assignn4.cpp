#include <iostream>
#include <thread>
#include <vector>

using namespace std;


vector<int> numList;//a variable that will store the list of numbers


void swapElement(int pos);

int main()
{
	int maxNumThreads= thread::hardware_concurrency();//accessing available cores to use
	vector <thread> threadPool;//declearing threads
	int sizeOfList=0;
	int tmp;

			//read in numbers to tmp and push it back to the vector variable until the end of file is reached
			while(!cin.eof())
			{
				cin>>tmp;
				numList.push_back(tmp);
			}



	for (int i = 0; i < numList.size() ; i++)
	{
		////////////////////////////////////////////////////////////////////

		// determine which phase you are in
		if(i%2==0)
		{
			for (int e=0; e<=numList.size()-2; e=e+2)
			{
				// spawn a thread to compare and /or swap two adjacent items
				threadPool.push_back(thread(swapElement, e)); 

				// if no more threads can be spawned , and we have not reached
				if(i% maxNumThreads==0)
				{
					// the end of the list yet , join all the threads
					// and clear the thread pool so we can spawn more threads in this
					for(int k=0; k<threadPool.size(); k++)
					{
						threadPool[k].join();
					}
					threadPool.clear();
				} 
				
				
				// inner loop until each adjacent element has been compared
			}
		}


		/////////////////////////////////////////////////////////////////////

		// We finished the phase so we can join all the threads that are running
		// and clear the thread pool to be prepared for the next phase
		for(int m=0; m<threadPool.size(); m++)
		{
			threadPool[m].join();
		}
		threadPool.clear();

		///////////////////////////////////////////////////////////////////

		if(i%2==1)// determine which phase you are in
		{
			for (int o=1; o<=numList.size()-2; o=o+2)
			{

				// spawn a thread to compare and /or swap two adjacent items
				threadPool.push_back(thread(swapElement, o)); 

				// if no more threads can be spawned , and we have not reached
				if(i% maxNumThreads==0)
				{
					// the end of the list yet , join all the threads
					// and clear the thread pool so we can spawn more threads in this
					for(int k=0; k<threadPool.size(); k++)
					{
						threadPool[k].join();
					}
					threadPool.clear();
				} 

			}
		}

		/////////////////////////////////////////////////////////////////////

		// We finished the phase so we can join all the threads that are running
		// and clear the thread pool to be prepared for the next phase
		for(int m=0; m<threadPool.size(); m++)
		{
			threadPool[m].join();
		}
		threadPool.clear();

		//////////////////////////////////////////////////////////////////////

	}

	// Output the sorted array
	for(int i=0; i<numList.size(); i++)
	{
			cout<<numList[i]<<endl;
	}
	
	return 0;
}


//the following is a swap function that takes in a position of the element
void swapElement(int pos)
{
	//this if statment checks if the element in position pos is bigger than the element next to it and swap them
	if(numList[pos] > numList[pos+1])
	{

		swap(numList[pos], numList[pos+1]);
	}
	
	return;
}