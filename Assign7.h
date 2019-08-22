#include <iostream>


using namespace std;

template <class Type >
class binMaxHeap
{
public :
binMaxHeap (int = 10);
binMaxHeap ( const binMaxHeap < Type >&);
~ binMaxHeap ();
const binMaxHeap < Type >& operator =( const binMaxHeap < Type >&);
void insert ( Type *);
void deleteMax ();
Type * getMax () const ;
bool isEmpty () const ;
void bubbleUp ( size_t );
void bubbleDown ( size_t );
size_t getSize () const ;
private :
size_t capacity ;
size_t size ;
Type ** heapArray ;
};







/*constructor that sets this->capacity with capacity, and allocates capacity amount of elements to heapArray, 
and sets size to 0 or 1 (depending on how you implement the heap), if nothing is passed into the constructor,
then capacity’s default value will be 10*/
template <class Type >
binMaxHeap<Type>::binMaxHeap(int capacity)
{
	//cout<<"	CAPACITY" << capacity<<endl;
	this->capacity= capacity;
	heapArray= new Type*[capacity];
	size=1;


}

//____________________________________________________________________________________________________________________________

/*copy constructor that creates
a deep copy of the copy object (which is passed into the constructor)*/
template <class Type >
binMaxHeap<Type>::binMaxHeap(const binMaxHeap<Type>& copy)
{
	size= copy.size;//assign copy's size to this-> size
	capacity= copy.capacity;//assign capacity size to this->capacity
	heapArray= new Type*[capacity];//create a heapArray with the capacity

}

//____________________________________________________________________________________________________________________________

/*destructor that deallocates the dynamic array heapArray*/
template <class Type >
binMaxHeap<Type>::~binMaxHeap()
{
	delete [] heapArray;
}

//____________________________________________________________________________________________________________________________

/*assignment operator, creates a deep copy of rhs object into the left hand side object (i.e. the object that
invokes the operator function)*/
template <class Type >
const binMaxHeap<Type>& binMaxHeap<Type>::operator=(const binMaxHeap<Type>& rhs) 
{

	if (this != &rhs)
	{
		this.binMaxHeap(rhs);

	}
	return *this;

}

//____________________________________________________________________________________________________________________________

/* inserts an element into the heap (if the heap is
full, double its size), then insert the item to the end of thee array and bubble the element up the tree,
this returns the index of where this item is stored after the potential bubble ups*/
template <class Type >
void binMaxHeap<Type>::insert(Type* item)
{

	//checks if the array needs to be resized
	if(size==capacity)
	{

		Type **tmp;

		tmp= new Type*[capacity*2];

		for(int i=0; i< size; i++)
		{
			tmp[i]=heapArray[i];
		}

		delete []  heapArray;
		heapArray=tmp;
		capacity=capacity*2;

	}

		//assign item to the positon in the heap array
		heapArray[size]=item;
		bubbleUp(size);
		size++;//increment size by 1


}

//____________________________________________________________________________________________________________________________

/*removes the top element from the heap, assigns the last
element of the heap to the top and bubbles down from the top*/
template <class Type >
void binMaxHeap<Type>::deleteMax()
{
	heapArray[1]= heapArray[size];
	size--;
	bubbleDown(1);
	
}

//____________________________________________________________________________________________________________________________

/* returns the element on top of the heap*/
template <class Type >
Type* binMaxHeap<Type>::getMax() const
{
	return heapArray[1];
}

//____________________________________________________________________________________________________________________________

/*returns true if the structure contains no items and
false otherwise*/
template <class Type >
bool binMaxHeap<Type>::isEmpty() const
{
	if(size==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//____________________________________________________________________________________________________________________________

/*bubbles up from the initial index value passed
in until it cannot bubble up any further, this function uses carType’s operator> function, but the
elements on heapArray are addresses so you would compare by dereferencing the array and then access
an element, so *heapArray[x] > *heapArray[y] would compare the distances of the car at index x
and at index y*/
template <class Type >
void binMaxHeap<Type>::bubbleUp(size_t index)
{
		int i=index;
		int j=index/2;

		while(j>1)
		{

			if(*heapArray[i] > *heapArray[j])
			{	
				swap(heapArray[i], heapArray[j]);
				i=j;
				j=j/2;
			}
			else
			{
				break;
			}

		}


}

//____________________________________________________________________________________________________________________________


/*bubbles down from the initial index value passed
in until it cannot bubble down any further, this function uses carType’s operator> function, but the
elements on heapArray are addresses so you would compare by dereferencing the array and then access
an element, so *heapArray[x] > *heapArray[y] would compare the distances of the car at index x
and at index y*/
template <class Type >
void binMaxHeap<Type>::bubbleDown(size_t index)
{



	int i= index;
	int j= (i * 2);

	while(j<=index)
	{
		//checks for the if both child are greater
		if(*heapArray[j] > *heapArray[i] and *heapArray[j+1] > *heapArray[i])
		{
			if(*heapArray[j] > *heapArray[j+1])
			{
				swap(heapArray[i], heapArray[j]);
				i=j;
				j=(i*2);
			}
			else
			{
				swap(heapArray[i], heapArray[j+1]);
				i=j+1;
				j=(i*2);
			}
		}
		//checks if the left child is greater
		if(*heapArray[j] > *heapArray[j+1] and *heapArray[j] > *heapArray[i])
		{
			swap(heapArray[i], heapArray[j]);
			i=j;
			j=(i*2);
		}
		//checks if the right child is greater
		if(*heapArray[j+1] > *heapArray[j] and *heapArray[j+1] > *heapArray[i])
		{
			swap(heapArray[i], heapArray[j+1]);

			i=j+1;
			j=(i*2);
		}

		else
		{
			break;
		}
	}

}

//____________________________________________________________________________________________________________________________

/*returns the amount of elements in the heap*/
template <class Type >
size_t binMaxHeap<Type>::getSize() const
{
	return size;
}