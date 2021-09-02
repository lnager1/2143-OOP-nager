/*****************************************************************************
*                    
*  Author:           Lindsey
*  Email:            nager.lindsey@gmail.com
*  Label:            03-A04
*  Title:            Comment Practice
*  Course:           CMPS 2143-101
*  Semester:         Fall 2021
* 
*  Description:
*        This program implements a class that allows an Array to be used just like 
*        a circular queue. It overloads the "<<" (triangle brackets) to print the 
*        entire object as if it were a variable. The class uses methods like "pop"
*        and "push" to add and remove items from the queue in a standard queue 
*        fashion.
*  
*  Usage:
*        N/A
* 
*  Files:   
*       main.cpp    :   driver program
*****************************************************************************/

#include <iostream>

using namespace std;

/**
 * CircularArrayQue
 * 
 * Description:
 *      This class implements a circular queue based on an Array. Circular 
 *      queues say that items are inserted at the end and removed from the
 *      front, however, the front wraps around and points to the end of the queue.
 *      
 * Public Methods:
 *                       CircularArrayQue()
 *                       CircularArrayQue(int size)
 *      void             Push(int item)
 *      int              Pop()
 *      ostream&         operator<<(ostream &os, const CircularArrayQue &other)
 * 
 * Private Methods:
 *      void            init(int size = 0) 
 *      bool            Full()
 * 
 * Usage: 
 *     
 *      CircularArrayQue Queue()              //Create instance of Circular 
                                              //Array Queue
 *      CircularArrayQue Queue(int)           //Create instance of Queue w/ size
 *      
 */
class CircularArrayQue
{
    private:
        int *Container;     // Pointer to allocate dynamic array
        int Front;          // index of the front
        int Rear;           // index of the rear
        int QueSize;        // items in the queue
        int CurrentSize;    // spaces filled in the queue

        /**
        * Private : init
        * 
        * Description:
        *      Sets all variable to 0 with the exception of
        *      QueSize which is initialized to size
        * 
        * Params:
        *      int      :   number of spaces in array
        * 
        * Returns:
        *      No return value
        */
        void init(int size = 0) 
        {
            Front = Rear = CurrentSize = 0;
            QueSize = size;     // Number of spaces available is size
        }

        /**
        * Private : Full
        * 
        * Description:
        *      Checks to see if the currentSize is equal to the Queue size
        * 
        * Params:
        *      No parameters
        * 
        * Returns:
        *      bool     :   true or false based on what is evaluated
        */
        bool Full()
        {
            return CurrentSize == QueSize;
        }

    public:
        /**
        * Public : CircularArrayQue
        * 
        * Description:
        *      Default constuctor that initializes container value to 10
        * 
        * Params:
        *      No parameters
        *
        * Returns:
        *      No return values
        */
        CircularArrayQue()
        {
            Container = new int[10];    //Default size is size 10
            init(10);
        }

        /**
        * Public : CircularArrayQue
        * 
        * Description:
        *      Overloaded constuctor that initializes container value to size
        * 
        * Params:
        *      No parameters
        *
        * Returns:
        *      No return values
        */
        CircularArrayQue(int size)
        {
            Container = new int[size];  //Dynamic array sizing (Overloaded)
            init(size);
        }

        /**
        * Public : Push
        * 
        * Description:
        *      Adds a value to the end of the queue
        * 
        * Params:
        *      int      :   value to add to queue
        *
        * Returns:
        *      No return values
        */
        void Push(int item)
        {
            if (!Full())        
            {
                Container[Rear] = item;         // Adds item to end of queue
                Rear = (Rear + 1) % QueSize;    // Moves rear position
                CurrentSize++;                  
            } 
            else
            {
                cout << "FULL!!!!" << endl;
            }
        }

        /**
        * Public : Pop
        * 
        * Description:
        *      Removes an item from the front of the queue
        * 
        * Params:
        *      No parameters
        *
        * Returns:
        *      int      :   the value at the front of the queue
        */
        int Pop()
        {
            int temp = Container[Front];    // Assigns value to temp
            Front = (Front + 1) % QueSize;  // Moves front
            CurrentSize--;
            return temp;
        }

        // friending ostream to give it access 
        friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

/**
* Function : operator<<
* 
* Description:
*      Overloads the << operator so that the queue can be printed as a normal variable
* 
* Params:
*      ostream &                    :   reference to the stream
*      const CircularArrayQueue&    :   constant class Instance passed by reference
*
* Returns:
*     ostream &                     :   a referece to the stream
*/
ostream &operator<<(ostream &os, const CircularArrayQue &other)
{
    //Goes through each item in queue starting at front
    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize)
    {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main()
{
    CircularArrayQue C1(5);     //Creates instance of CircularArrayQue with size 5

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);         // Pushes value onto queue
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl; // Prints all values in queue

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl; // Prints all values in queue again
}