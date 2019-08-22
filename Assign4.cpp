#include <iostream>
#include <thread>
#include <vector>

using namespace std;


void swapElement(int * array, int pos);

int main()
{
	int maxNumThreads= thread::hardware_concurrency();
	vector <thread> threadPool;
	int * numList;
	int sizeOfList=0;
	numList= new int[100];

		for(int i=0; i<100; i++)
		{
			if(!cin.eof())
			{
				cin>>numList[i];
				sizeOfList++;
			}
		}


		/*for(int i=0; i<sizeOfList; i++)
		{
			cout<<numList[i]<<endl;
		}

		cout<<sizeOfList<<endl;
		cout<<maxNumThreads<<endl;*/



	for (int i = 0; i < sizeOfList ; i++)
	{
		////////////////////////////////////////////////////////////////////

		// determine which phase you are in
		if(i%2==0)
		{
			for (int e=0; e<=sizeOfList-2; e=e+2)
			{
				// spawn a thread to compare and /or swap two adjacent items
				threadPool.push_back(thread(swapElement, numList, e)); 

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
			for (int o=1; o<=sizeOfList-2; o=o+2)
			{

				// spawn a thread to compare and /or swap two adjacent items
				threadPool.push_back(thread(swapElement, numList, o)); 

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
	for(int i=0; i<sizeOfList; i++)
	{
			cout<<numList[i]<<endl;
	}

	delete [] numList;
	
	return 0;
}



void swapElement(int * array, int pos)
{
	if(array[pos] > array[pos+1])
	{

		swap(array[pos], array[pos+1]);
	}
	
	return;
}