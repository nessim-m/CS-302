#include <iostream>
#include <stack>



using namespace std;

void drawStars(int amount);//declared function that takes integer
void drawStarsUtil(int amount);//declared function that takes integer
stack<bool> converToBin(int x);// declared function that takes integer and return a stack
void outputBits(stack<bool> binNum);// declared function that takes a stack


//recursive function for processing amount of input
void drawStars(int amount)
{

	//the following if statment is the end of the recursion
	if ( amount ==0)
	{
		return;
	}
	// the following else statment calls another function with amount and calls itself with amount - 1
	else
	{

		drawStarsUtil(amount);
		cout<<endl;
		drawStars( amount -1);
	}
	//once the else statment is done computing it excute the following backward
	drawStarsUtil(amount);
	cout<<endl;

}
//recursive function that out put for the amount passed in
void drawStarsUtil(int amount)
{

	//the following if statment  is the end of the recursion
	if (amount == 0)
	{
		return ;
	}
	// this else statment outputs a star to the screen
	else
	{
		cout<<"*";
	}

	//the following calls itself every time with amount -1
	return drawStarsUtil(amount-1);
}
	


// Its a recrusrive function that computes and return a stack
stack<bool> converToBin(int x)
{
	stack<bool> binary;// a stack to push 1 and 0

	
	if(x==0)
	{
		return binary;
	}

	binary= converToBin(x/2);//it call this function recursively but with different value,(value divided by 2).

	//once it reach base statment is maintain binary and pushes 1 and 0 to it
	if(x%2==1)
	{
		binary.push(1);
	}
	else if( x%2==0)
	{
		binary.push(0);
	}

	return binary;// it return the pushed number
	

}


//Its a void recursive function that takes in a stack and output's the stack until its empty
void outputBits(stack<bool> binNum)
{

	stack<bool> tmp;//a temperory stack to output the stack properly

	//the following statment excutes while the binNum stack is not empty
	if(!binNum.empty())
	{
		tmp.push(binNum.top());//pushes binNum.top to the bottom of tmp stack
		binNum.pop();//pops the top item of binNUm
		outputBits(binNum);//calls this function recursively but after it pops the top item every time
	}
	else
	{
		return;//once it empty it returns
	}

		cout<<tmp.top();//going back it output the tmp's top
		tmp.pop();//after it outputs the top it pops it

}

int main()
{

	int amount;//integer amount input from user
	cout<< "How many stars to you wish upon: ";//output to the screen
	cin>> amount;//promt the user to input an integer amount

	drawStars(amount);//calls the recursive function with the input amount from the user 

	int x;//integer amount input from user
	stack <bool> number;// declared stack

	cout<< "Ok almost done!"<<endl;//output to the screen
	cout<<"Enter an integer and I'll try to convert it to binary: ";//output to the screen
	cin>>x;//prompt the user for an integer input

	number= converToBin(x);//calls the recursive function with integer input and sets function stack return to (number), stack.
	outputBits(number);//calls the recursive function to output the whole stack until its empty


	return 0;
}
