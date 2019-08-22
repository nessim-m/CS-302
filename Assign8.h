#include <cstdlib>
#include <iostream>
using namespace std;

template <class Type>
class vertex
{
    struct node
    {
        Type item;
        node * link;
    };

public:
    class edgeIterator
    {
    public:
        friend class vertex;
        edgeIterator();
        edgeIterator(node*);
        edgeIterator operator++(int);
        Type operator*();
        bool operator==(const edgeIterator&);
        bool operator!=(const edgeIterator&);
    private:
        node * current;
    };

    vertex();
    vertex(const vertex&);
    const vertex& operator=(const vertex&);
    ~vertex();
    edgeIterator begin();
    edgeIterator end();
    void addEdge(const Type&);
private:
    node * neighbors;
};

//_____________________________________________________________________________________________________

// default constructor that sets current to NULL
template <class Type>
vertex<Type>::edgeIterator::edgeIterator()
{
    current=NULL;
}

//_____________________________________________________________________________________________________

// a constructor that
//takes in a node object which gets assigned to current
template <class Type>
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node * edge)
{
    current= edge;
}

//_____________________________________________________________________________________________________

//an operator function that sets the iterator to point to the next node object, you will need to set current to
//point to the next node
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int)
{
    current=current->link;
}

//_____________________________________________________________________________________________________

//an operator that dereferences the iterator, returns the item field of the node that current points to
template <class Type>
Type vertex<Type>::edgeIterator::operator*()
{
    return current->item;
}

//_____________________________________________________________________________________________________

//compares the address of the iterator on the left side with the iterator on the right side, returns true if they
//both point to the same node, and returns false otherwise
template <class Type>
bool vertex<Type>::edgeIterator::operator==(const vertex<Type>::edgeIterator& rhs)
{
    return rhs.current == current;
}

//_____________________________________________________________________________________________________

// compares the address of the iterator on the left side with the iterator on the right side, returns false if
//they both point to the same node, and returns true otherwise
template <class Type>
bool vertex<Type>::edgeIterator::operator!=(const vertex<Type>::edgeIterator& rhs)
{
    return rhs.current != current;
}

//_____________________________________________________________________________________________________

//default constructor that sets neighbors to NULL
template <class Type>
vertex<Type>::vertex()
{
    neighbors=NULL;
}

//_____________________________________________________________________________________________________

// a copy constructor that deep copies the neighbor list of the object passed into the constructor
//to the object that calls the constructor
template <class Type>
vertex<Type>::vertex(const vertex<Type>& copy)
{
    neighbors->item=copy.neighbors->item;
    neighbors->link= NULL;
    node* i= copy.neighbors;
    node* j= neighbors;

    while(j->link!=NULL)
    {
        i= i->link;
        j->link= new node;
        j= j->link;
        j->item= i->item;
        j->link= NULL;
    }


}

//_____________________________________________________________________________________________________

// assignment operator, that performs a deep copy of the right side object with the left side object (the object that calls
//the operator function)
template <class Type>
const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& rhs)
{
    if (this != &rhs)
    {
        vertex<Type> temp(rhs);
        swap(temp.neighbors, neighbors);
        delete temp;
        temp=NULL;
    }
    return *this;
}

//_____________________________________________________________________________________________________

//destructor, deallocates all the nodes in its neighbor list
template <class Type>
vertex<Type>::~vertex()
{
    while(neighbors!=NULL)
    {
        node* d= neighbors;
        neighbors= neighbors->link;
        delete d;
        d=NULL;
    }


}

//_____________________________________________________________________________________________________

//returns a edgeIterator object
//whose current will be the head of the neighbor list for the vertex object
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::begin()
{
    edgeIterator tmp;
    tmp=neighbors;
    return tmp;
}

//_____________________________________________________________________________________________________

//returns a edgeIterator object whose current will be assigned to NULL
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::end()
{
   edgeIterator tmp;
   return tmp;
}

//_____________________________________________________________________________________________________

//adds a new node into the neighbor list (a head insert would be the best way to implement this)
template <class Type>
void vertex<Type>::addEdge(const Type& edge)
{
    node * tmp=neighbors;
    neighbors= new node;
    neighbors->item=edge;
    neighbors->link=tmp;
    tmp=NULL;

}