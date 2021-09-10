#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node
{
	public:
   		Node(int d, Node* n, Node* p);
    	int data;
    	Node* next;
		Node* prev;
};

/**
 * myVector
 * 
 * Description:
 *      This class implements a vector based on nodes. The vector can
 *      begin from nothing, array values, data file, or another data type.
 *      
 * Public Methods:
 *                      myVector();
 *                       myVector(int *arry, int size);
 *                       myVector(string fileName);
 *                       myVector(const myVector& V1);
 *
 *   	                ~myVector();
 *
 *       void            pushFront(int val);
 *       void            pushFront(const myVector& V2);
 *
 *       void            pushRear(int val);
 *       void            pushRear(const myVector& V2);
 *
 *       void            pushAt(int loc,int val);
 *       void            inOrderPush(int val);
 *
 *       int             popFront();
 *       int             popRear();
 *       int             popAt(int loc);
 *
 *       int             find(int val);
 *
 *       void            print();
 * 
 * Private Methods:
 *       Node* head;
 *		 Node* tail;
 *
 *       int numNodes = 0;
 * 
 * Usage: 
 *     
 *      myVector v1()                           //Create instance of Circular 
 *                                             
 *      myVector v1(int *arry, int size)        //Array with size
 *
 *      myVector v1(string fileName)            //reads from file
 *
 *      myVector v1(const myVector& V1)         //copy constructor
 *      
 */
class myVector
{
	public:
    	myVector();
        myVector(int *arry, int size);
        myVector(string fileName);
        myVector(const myVector& V1);

    	~myVector();

        void pushFront(int val);
        void pushFront(const myVector& V2);

        void pushRear(int val);
        void pushRear(const myVector& V2);

        void pushAt(int loc,int val);
        void inOrderPush(int val);

        int popFront();
        int popRear();
        int popAt(int loc);

        int find(int val);

        void print();

	private:
    	Node* head;
		Node* tail;

        int numNodes = 0;
};
