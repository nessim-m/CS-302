#include <iostream>



using namespace std;


//struct initialize binary tree
template <class Type >
struct binTreeNode
{
	binTreeNode < Type > * left , * right ;
	Type item ;
};

// function to determine the winingpath for the passed in binary tree
template <class Type > 
bool determineWinningPath ( binTreeNode < Type > * r , bool turn );
//function to output the path that the user should take to win
template <class Type > 
void printWinningPath ( binTreeNode < Type > * r , bool turn );
//function to build the binary tree
template <class Type >
void buildTree ( binTreeNode < Type >* r , int );
// function to deallocate the binary tree
template <class Type >
void destroyTree ( binTreeNode < Type >* r );

//template<class Type>
//int count (binTreeNode <Type>* r);



template <class Type >
void buildTree ( binTreeNode < Type >* r , int rocks)
{
	//base statment
	if(rocks==0)
	{
		return;
	}

	//as long as rocks -1 is greater than zero create a left node and assign it with rock -1 and set its children to NULL
	if(rocks-1>=0)
	{
		r->left= new binTreeNode <Type>;
		r->left->item= rocks-1;
		r->left->left= r->left->right=NULL;
		buildTree(r->left, rocks-1);
	}

	//as long as rocks -2 is greater than zero create a right node and assign it with rock -2 and set its children to NULL
	if(rocks-2>=0)
	{
		r->right= new binTreeNode <Type>;
		r->right->item= rocks-2;
		r->right->right= r->right->left =NULL;
		buildTree(r->right, rocks-2);
	}

	return;

}

///////////////////////////////////////////////////////////////////////////////////////////

template <class Type > 
bool determineWinningPath ( binTreeNode < Type > * r , bool turn )
{
	bool win;// a boolean to determine a win
	
	//base case if r is pointing to NULL and its your turn
	if(r==NULL and turn)
	{
		return false;
	}
	//base case if r is pointing to NULL and its friend's turn
	else if( r==NULL and !turn)
	{
		return true;
	}
	//base case if r item is 0 and its your turn
	if(r->item==0 and turn)
	{
		return false;
	}
	//base case if r item is 0 and its friend's turn
	else if(r->item==0 and !turn)
	{
		return true;
	}


	//the follwing if statement excutes if its our turn and determine if there is winning path.
	//by calling left and right side nodes and alters the turn
	if(turn)
	{


		return win=determineWinningPath(r->left, false) or determineWinningPath(r->right, false);

	}
	//the follwing else statement excutes if its not our turn and determine if there is winning path.
	//by calling left and right side nodes and alters the turn
	else
	{	

		return win=determineWinningPath(r->left, true) and determineWinningPath(r->right, true);
	}


}

//////////////////////////////////////////////////////////////////////////////////////////

template <class Type > 
void printWinningPath ( binTreeNode < Type > * r , bool turn )
{
	//base case if r is NULL
	if( r==NULL)
	{
		return;
	}

	//if its our turn it excutes the following if statement
	if(turn)
	{

		//the follwoing statement calls determineWinningpath function.
		//by passing the left node and once again the right node.
		//if any of them return true it excutes.
		if(determineWinningPath(r->left, !turn) or determineWinningPath(r->right, !turn))
		{

			//if the left node determine winning path return true then it excute the following
			if(determineWinningPath(r->left, !turn))
			{
				//if the r item is not zero it output the following
				if(r->item != 0)
				{
					cout<< "If you have "<<r->item<<" stones remaining"<<endl;
					cout<<"You take 1 stones"<<endl;
					cout<<endl;
				}

				//and calls this function again by passing in the next left node and alters turn
				printWinningPath(r->left, !turn);
			}

			//if the right node determine winning path return true then it excute the following
			if(determineWinningPath(r->right,!turn))
			{
				//if the r item is not bigger than 1 it output the following
				if(r->item > 1)
				{
					cout<< "If you have "<<r->item<<" stones remaining"<<endl;
					cout<<"You take 2 stones"<<endl;
					cout<<endl;
				}

				//and calls this function again by passing in the next right node and alters turn
				printWinningPath(r->right, !turn);
			}

		}

	}
	// if its not our turn then it excutes the following else if statement
	else if(!turn)
	{

		//the follwoing statement calls determineWinningpath function.
		//by passing the left node and once again the right node.
		//if both of them return true it excutes.
		if(determineWinningPath(r->left, !turn) and determineWinningPath(r->right, !turn))
		{
			//and calls this function by passing in left node and then right node and also alters turn 
			printWinningPath(r->left, !turn);
			printWinningPath(r->right, !turn);

		}

	}


}


//////////////////////////////////////////////////////////////////////////////////////////

template <class Type >
void destroyTree ( binTreeNode < Type >* r )
{
	//if r is not pointing to NULL it enters this if statement
	if( r!= NULL)
	{	
		//calls this function again, but passes in the right node and then left node
		//then it deallocate the node
		destroyTree(r->left);
		destroyTree(r->right);
		delete r;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

/*template<class Type>
int Count(binTreeNode<Type> * r)
{
	int counter=1;

	//int left, right;

	if(r==NULL)
	{
		return 1;
	}

	if(r->left==NULL)
	{
		return counter=r->item;
	}
	else
	{
		counter=Count(r->left);
	}


}*/

int main()
{
	binTreeNode <int> * root;// binary tree node
	int rocks;//variable that store amount of rocks

	cout<< "Enter the amount of rocks to start the game : ";
	cin>> rocks;//prompt the user for input of rocks

	//the following while loop excutes if the user input was invalid or less than or equal to 3.
	//keeps prompting untill the input is valid
	while(cin.fail() or rocks <= 3)
	{
		cout<<"Wow! we should try this again!"<<endl;
		cin.clear();
		cin.ignore(100, '\n');

		cout<< "Enter the amount of rocks to start the game : ";
		cin>> rocks;

	}

	root= new binTreeNode<int>;//create the root of binary tree
	root->item= rocks;// assign it with the user's input
	root->left=root->right=NULL;// and set its right and left side to null
	buildTree(root, rocks);//call build tree function and pass in the root binary tree and amount of rocks
	printWinningPath(root, true);// after we build the tree call the print out function and pass in the tree and set turn to true
	
	//cout<< " Total nodes: "<< Count(root)<< endl;

	destroyTree(root);// lastly deallocate the binary tree to prevent memory leaks



	return 0;
}
