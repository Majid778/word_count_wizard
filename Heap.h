#include<iostream>
#include<exception>
#include<math.h>
#include<iomanip>
#include<unistd.h>
#include<sstream>
#include "Hashtable.h"
using namespace std;


class Heap
{
	private:
		HashNode** array;
		int capacity;
		int size;
	
	public:
		Heap(int capacity);
		~Heap();
		void insert(HashNode* Node);
		HashNode* removeMax();
		void find_max();
		int parent(int k);
		int left(int k);
		int right(int k);
		void siftup(int k);
		void siftdown(int k);
		void print(int k=-1);
		void sort();
	private:
		void adjustSize();
};

Heap::Heap(int capacity)
{
	
    this->array  = new HashNode*[capacity];
    this->capacity = capacity;
    this->size = 0;
}
//Destructor
Heap::~Heap()
{
	delete array;
}
// Insert an element in Heap keeping the Heap property intact 
void Heap::insert(HashNode* Node)
{
    if(size >= capacity)
    {
        adjustSize();
    }
    size++;
	array[size-1]= Node;
    siftup(size-1);
}
// Remove the minimum value from Heap keeping the Heap property intact
HashNode* Heap::removeMax()
{
    HashNode* temp = array[0];
    array[0] = array[size-1];
    size--;
    siftdown(0);
    return temp;
}
// Return (but don't remove) the minimum value from the Heap
void Heap::find_max()
{
    if(size <= 0){
        cout<<"Heap is empty"<<endl;
    }
    else
    {
        cout<<"The most frequent word is: "<<array[0]->getkey()<<" and it occured "<<array[0]->getvalue()<<" times"<<endl;
	    return;
    }
}
// Returns the index of the parent of the node i
int Heap::parent(int k)
{
	int parent_index = (k - 1)/2;
    if(k == 0)
    {
        return -1;
    }
    else if (k != 0)
    {
        return parent_index;
    }
}
// Returns the index of the left child of the node i
int Heap::left(int k)
{
	int left = 2*k+1;
    if(left>size-1) { return -1;}
    else { return left;}
}
// Returns the index of the right child of the node i
int Heap::right(int k)
{
	int right = 2*k+2;
    if(right>size-1) { return -1;}
    else { return right;}
}

// Sift-up an element at index k
void Heap::siftup(int k)
{
	if(parent(k) != -1)
    {
        if(array[parent(k)]->getvalue() < array[k]->getvalue())
        {
            HashNode* temp = array[parent(k)];
			array[parent(k)] = array[k];
			array[k] = temp; 
            siftup(parent(k));
        }
    }
}
// Sift-down an element at index k
// 1. if element has no children do nothing
// 2. if element has only a left child which is smaller than element then swap the element with its left child
// 3. if element has both children and smaller child is also smaller than the node then swap it with that node
// 4. keep repeating step 1-3 until the element/node reaches to its correct position
void Heap::siftdown(int k)
{
    if(left(k) == -1 && right(k) == -1)
    {
        return;
    }
    if(array[left(k)]->getvalue()>=array[k]->getvalue() && right(k) == -1)
    {
        HashNode* temp = array[left(k)];
        array[left(k)] = array[k];
        array[k] = temp;
        siftdown(left(k));
    }
    if(array[left(k)]->getvalue()>=array[k]->getvalue() && array[left(k)]->getvalue()>array[right(k)]->getvalue())
    {
        HashNode* temp = array[left(k)];
        array[left(k)] = array[k];
        array[k] = temp;
        siftdown(left(k));
    }
    if(array[right(k)]->getvalue()>=array[k]->getvalue())
    {
        HashNode* temp = array[right(k)];
        array[right(k)] = array[k];
        array[k] = temp; 
        siftdown(right(k));
    }
    return;
}

//==================================================================

void Heap::print(int k)
{
	if(size >0)
	{
		int levels = int(log2(size));

		int spaces[levels+1];
		spaces[levels]=0;

		for(int j=levels-1; j>=0; j--)
		{
				spaces[j]=2*spaces[j+1]+1;
		}
		
		int level=0;
		for (int i=0; i<size; i++)
		{
			if(i == (pow(2,level)-1))
			{
				cout<<endl<<endl;
			
				for(int k=0; k<spaces[level]; k++)
				cout<<"   ";
				level++;
		
			}
			if(i==k)
				cout<<std::left<<"\033[1;31m"<<setw(3)<<array[i]<<"\033[0m";
			else
				cout<<std::left<<setw(3)<<array[i];
			
			if(level>1)
			{
				for(int k=0; k<spaces[level-2]; k++)
					cout<<"   ";
			}
			
		}

		cout<<endl;
		for(int i=0; i<spaces[0]*log2(size/2)+4; i++)
		cout<<"__";
		cout<<endl;
	}

}
//=====================================
// This method will sort the internal array of heap using an Auxilary heap
// Hint: Add element of the array in the Auxilary heap first and they keep 
//       extractin the min. value and write it on the original array


//=============================================
void Heap::adjustSize()
{
	HashNode* *newArray = new HashNode*[capacity*2];
	for(int i=0; i<capacity; i++)
		newArray[i] = array[i];
	delete[] array;
	array = newArray;
	capacity = capacity*2;	
}