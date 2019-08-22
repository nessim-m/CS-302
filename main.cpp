#include <iostream>
#include <fstream>
#include <string>
#include "Assign8.h"
using namespace std;

int main()
{
    string filename;// string to read in the filename
    fstream infile;// fstream to read from the file
    vertex<string> * vertices;
    vertices= new vertex<string>[26];
    string  to,from;

    //prompt user to enter a valid file name.
    do
    {

        cout<< "Enter a filename: ";
        cin>> filename;

        //filename.c_str() returns a C style string version
        infile.open(filename.c_str());

    }
    while(!infile.is_open());
    int counter=0;//counter
    //reads in from the file and stores the followers into a vertex object at an index
   while(!infile.eof())
   {
       infile>>from>>to;
       vertices[from[0]-'A'].addEdge(to);
       counter++;
   }

   vertex<string>::edgeIterator followIter;//iterate the follower list

    /*Dynamic array that stores the count of mutual friends for each user*/
   int ** info;
   info= new int*[26];
   for(int i=0; i<26; i++)
   {
      info[i]= new int[26];
   }

    //initializing everything to zero
   for(int i=0; i<26; i++)
   {
       for(int j=0; j<26; j++)
       {
           info[i][j]=0;
       }

   }

    vertex<string>::edgeIterator compareup;//iterate through user's followers forward to find a match
    vertex<string>::edgeIterator comparedown;//iterate through user's followers backward to find a match
   //set's the iterator to point to the first node in the list.
   for(int i=0; i<26; i++) {
       followIter = vertices[i].begin();//iterator points to the first node

       string follower;//stores the follower that the iterator is pointing to
        //traverse the whole follower's list
       while (followIter != vertices[i].end()) {

          follower= *followIter;//stores the follower

          //checks if there is users at index less than current
           if(i-1>=0)
           {
               //if there is users it traverse through to find a mutual friend
               for(int k=i-1; k>=0; k--)
               {
                   comparedown = vertices[k].begin();// traverse through follower list for the given user
                   while (comparedown != vertices[k].end())
                   {
                       string tmp = *comparedown;//stores the follower

                       //if they are friends it stops searching for mutual friends and break
                       if (i == tmp[0] - 'A')
                       {
                           info[i][k] = 0;
                           break;
                       }
                       //if they are not friends and have mutual friends increments at a given index
                       else if(follower[0]-'A'==tmp[0]-'A')
                       {
                           info[i][k]++;
                       }

                       comparedown++;//goes to the next node
                   }
               }

           }
            // the following loop traverse through the next user's followers
          for(int j=i+1; j<26; j++)
           {
               compareup = vertices[j].begin();//looks at the first node
               //the following loops through all the followers
               while (compareup != vertices[j].end())
               {
                   string tmp = *compareup;//stores the follower

                   //if they are friends it stop, stores zero and breaks the loop
                   if (i == tmp[0] - 'A')
                   {
                       info[i][j] = 0;
                       break;
                   }

                   //if they are not friends and have mutual friends it increment at a given index
                   else if(follower[0]-'A'==tmp[0]-'A')
                   {
                       info[i][j]++;
                   }

                   compareup++;//goes to the next node
               }
           }

           //calls the operator++ function for the edgeIterator class
           //moves the iterator to the next node in the list
           followIter++;//goes to the next node
       }


   }


    int maxRowIndex=0;//stores the max mutual friend found. Row
    int maxColumnIndex=0;//stores the max mutual friend found. Column

    //the following 4 loops goes through the whole 2d array to find the largest mutual friends it can find
    for(int i=0; i<26; i++)
    {
        for(int j=0; j<26; j++)
        {
            //checks if the positon is greater than zero
            if(info[i][j]!=0)
            {
                for(int k=i; k< 26; k++)
                {
                    for(int n=0; n<26; n++)
                    {
                        //if the following index are greater than max it updates for a new max
                        if (info[maxRowIndex][maxColumnIndex] <= info[k][n])
                        {
                            maxRowIndex = k;
                            maxColumnIndex = n;
                        }
                    }
                }
            }
        }
    }

    string suggestedFriend2;// suggested friend with most mutual friend
    string suggestedFriend1;//suggested friend with most mutual friend
    suggestedFriend1=maxRowIndex + 'A';//retrive back the first letter with most mutual friends
    suggestedFriend2=maxColumnIndex + 'A';//retrive back the first letter with most mutual friends

    //1 fills the name extracted
    if(maxRowIndex+ 'A' == 'A')
    {
        suggestedFriend1= "Ada";
    }
    if(maxColumnIndex + 'A' =='A')
    {
        suggestedFriend2= "Ada";
    }

    //2 fills the name extracted
    if(maxRowIndex+ 'A' == 'B')
    {
        suggestedFriend1= "Ben";
    }
    if(maxColumnIndex + 'A' =='B')
    {
        suggestedFriend2= "Ben";
    }

    //3 fills the name extracted
    if(maxRowIndex+ 'A' == 'C')
    {
        suggestedFriend1= "Chrisitine";
    }
    if(maxColumnIndex + 'A' =='C')
    {
        suggestedFriend2= "Chrisitine";
    }

    //4 fills the name extracted
    if(maxRowIndex+ 'A' == 'D')
    {
        suggestedFriend1= "Danielle";
    }
    if(maxColumnIndex + 'A' =='D')
    {
        suggestedFriend2= "Danielle";
    }

    //5 fills the name extracted
    if(maxRowIndex+ 'A' == 'Z')
    {
        suggestedFriend1= "Zoltan";
    }
    if(maxColumnIndex + 'A' =='Z')
    {
        suggestedFriend2= "Zoltan";
    }

    //6 fills the name extracted
    if(maxRowIndex+ 'A' == 'R')
    {
        suggestedFriend1= "Rachael";
    }
    if(maxColumnIndex + 'A' =='R')
    {
        suggestedFriend2= "Rachael";
    }

    //7 fills the name extracted
    if(maxRowIndex+ 'A' == 'J')
    {
        suggestedFriend1= "Jimi";
    }
    if(maxColumnIndex + 'A' =='J')
    {
        suggestedFriend2= "Jimi";
    }

    //8 fills the name extracted
    if(maxRowIndex+ 'A' == 'S')
    {
        suggestedFriend1= "Sandor";
    }
    if(maxColumnIndex + 'A' =='S')
    {
        suggestedFriend2= "Sandor";
    }

    //9 fills the name extracted
    if(maxRowIndex+ 'A' == 'T')
    {
        suggestedFriend1= "Tom";
    }
    if(maxColumnIndex + 'A' =='T')
    {
        suggestedFriend2= "Tom";
    }

    //10 fills the name extracted
    if(maxRowIndex+ 'A' == 'N')
    {
        suggestedFriend1= "Noemi";
    }
    if(maxColumnIndex + 'A' =='N')
    {
        suggestedFriend2= "Noemi";
    }

    //11 fills the name extracted
    if(maxRowIndex+ 'A' == 'K')
    {
        suggestedFriend1= "Katherine";
    }
    if(maxColumnIndex + 'A' =='C')
    {
        suggestedFriend2= "Katherine";
    }

    //out puts the two user's with most mutual friends
    cout<<suggestedFriend2<<" and "<<suggestedFriend1;
    cout<<" Will be friends soon because they have the most mutual friends, they have ";
    cout<<info[maxRowIndex][maxColumnIndex]-1;
    cout<<" mutual friends."<<endl;

    //deallocated the 2d dynamic array
    for(int i=0; i<26; i++)
    {
        delete [] info[i];
    }
    delete [] info;
    delete [] vertices;//deallocate the vertex object by calling the deconstructor


    return 0;
}