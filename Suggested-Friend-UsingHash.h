#include <iostream>


using namespace std;


//hashing class
template <class Type1, class Type2>
class myHash
{
public:
	myHash();//default constructor
	myHash(const myHash<Type1, Type2>&);//copy constructor
	const myHash<Type1, Type2>& operator=(const myHash<Type1, Type2>&);//copy operator
	~myHash();//destructor
	Type2& operator[](Type1);/*this function takes in a key and returns
	a reference of the item*/
private:
	struct tableItem
	{
		Type1 key;//char type
		Type2 item;//bool type
	};

	size_t hashFunction01(Type1) const;//first hash function
	size_t hashFunction02(Type1) const;//second hash function
	void resize();//resize function
	size_t tableSize, items;//the capacity of the hash table and the amount of items stored
	tableItem * table;//hash table
};

/////////////////////////////////////////////////////////////////////////

/*default constructor that creates a hash table of capacity 5, and
stores default values into each entry in the table, use Type1(0) and Type2(0) as your default values,
items would be set to 0 and tableSize would be set to 5*/
template <class Type1, class Type2>
myHash<Type1, Type2>::myHash()
{
	items=0;
	tableSize=5;
	table= new tableItem[tableSize];

	//the following loop sets the the whole table's item and key to zero
	for(int i=0; i< tableSize; i++)
	{
		table[i].key=0;
		table[i].item=0;
	}
}

/////////////////////////////////////////////////////////////////////////

//copy constructor that performs a deep copy of the copy object (the object passed into the constructor
template <class Type1, class Type2>
myHash<Type1, Type2>::myHash(const myHash<Type1, Type2>& copy)
{
	items= copy.items;//assign copy's item to this-> items
	tableSize= copy.tableSize;//assign table size to this->tablesize
	table= new tableItem[tableSize];//create a table with the tablesize

	//copy each key and item from copy object to this
	for(int i=0; i<tableSize; i++)
	{
		table[i].key= copy.table[i].key;
		table[i].item= copy.table[i].item;  
	}
}


/////////////////////////////////////////////////////////////////////////

//the following function checks for self assignment and does a deep copy
template <class Type1, class Type2>
const myHash<Type1, Type2>& myHash<Type1, Type2>::operator=(const myHash<Type1, Type2>& rhs)
{
	if (this != &rhs)
	{
		this.myHash(rhs);

	}
	return *this;
}

/////////////////////////////////////////////////////////////////////////

//deallocates the hash table
template <class Type1, class Type2>
myHash<Type1, Type2>::~myHash()
{
       
    delete[] table;
}

/////////////////////////////////////////////////////////////////////////

/*this function takes in a key and returns
a reference of the item (which can be reassigned in main)*/
template <class Type1, class Type2>
Type2& myHash<Type1, Type2>::operator[](Type1 key)
{

	/*If the load factor is greater than or equal to 0.5, call the resize() function and go to the next
	step*/
	if((items/tableSize) >= 0.5)
	{
		resize();
	}

	/*If table[index].key matches the key then return the item of that table entry, if no match
	found then go to the next step
	*/
	if(table[hashFunction01(key)].key==key)
	{
		return table[hashFunction01(key)].item;
	}

	/* If table[index].key contains Type1(0), increment items by 1, then set this element’s key
	field to the key passed into the operator[] function and return the item of that table entry*/
	else if(table[hashFunction01(key)].key== 0)
	{
		items++;
		table[hashFunction01(key)].key= key;
		return table[hashFunction01(key)].item;
	}

	//_________________________________________



	/*If table[index].key matches the key then return the item of that table entry, if no match
	found then go to the next step
	*/
	if(table[hashFunction02(key)].key==key)
	{
		return table[hashFunction02(key)].item;
	}

	/* If table[index].key contains Type1(0), increment items by 1, then set this element’s key
	field to the key passed into the operator[] function and return the item of that table entry*/
	else if(table[hashFunction02(key)].key== 0)
	{
		items++;
		table[hashFunction02(key)].key= key;
		return table[hashFunction02(key)].item;
	}

	//__________________________________________

	//the following loop's the table size time, until it find's an empty postion or it finds match
	for(int i=0; i< tableSize; i++)
	{
		// Compute (hashfunction 1  + hashfunction 2 + i) % tableSize, and if it found it then just return its item
		if(((table[hashFunction01(key)].key + table[hashFunction02(key)].key + i) % tableSize)==key)
		{
			return table[(hashFunction01(key) + hashFunction02(key) + i) % tableSize].item;
		}
		//else if the index is empty increment items by 1 and hash it in that index and return its item
		else if(((table[hashFunction01(key)].key + table[hashFunction02(key)].key + i) % tableSize) == 0)
		{
			items++;
			table[(hashFunction01(key) + hashFunction02(key) + i) % tableSize].key= key;
			return table[(hashFunction01(key) + hashFunction02(key) + i) % tableSize].item;
		}
	}

}

//////////////////////////////////////////////////////////////////////////

/*first hash function, takes in
the key and returns the index*/
template <class Type1, class Type2>
size_t myHash<Type1, Type2>::hashFunction01(Type1 key) const
{
	int index;

	return index= key % tableSize; 
}

////////////////////////////////////////////////////////////////////////////

/* second hash function (that
gets used if the first hash function causes a collision), returns a different index (hopefully)*/
template <class Type1, class Type2>
size_t myHash<Type1, Type2>::hashFunction02(Type1 key) const
{
	int index;

	return index= key % tableSize * (tableSize/2) % tableSize;
}

////////////////////////////////////////////////////////////////////////////

template <class Type1, class Type2>	
void myHash<Type1, Type2>::resize()
{
	//double the size of hash table

	tableItem * tmptable;
	tmptable= table;

	tableSize= tableSize * 2;
	table= new tableItem[tableSize];

	//rehash all the items for table into a larger tableItem  array
	for( int i=0; i< items; i++)
	{
		(*this)[tmptable[i].key]= tmptable[i].item;
	}

	// deallocate table beforehand
	delete [] tmptable;

	tmptable=NULL;
	
}

////////////////////////////////////////////////////////////////////////////
