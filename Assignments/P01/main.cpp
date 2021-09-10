/*****************************************************************************
*                    
*  Author:           Lindsey
*  Email:            nager.lindsey@gmail.com
*  Label:            03-P01
*  Title:            myVector
*  Course:           CMPS 2143-101
*  Semester:         Fall 2021
* 
*  Description:
*        This program implements a class of a double linked list made out of nodes.
*        The class has methods that allow for adding vectors to one another and
*        push and pop to both the front, back, and specified location.
*  
*  Usage:
*        N/A
* 
*  Files:   
*       main.cpp    :   driver program
*****************************************************************************/

#include <iostream>
#include "myVector.cpp"

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the myVector class
 * 
 */

int main()
{
    int x = 0;

    myVector v1;
    v1.pushFront(18);
    v1.pushFront(20);
    v1.pushFront(25);
    v1.pushRear(18);
    v1.pushRear(20);
    v1.pushRear(25);
    v1.print();
    // [25, 20, 18, 18, 20, 25]

    int A[] = {11, 25, 33, 47, 51};
    myVector v2(A, 5);
    v2.print();
    // [11, 25, 33, 47, 51]

    v2.pushFront(9);
    v2.pushAt(3, 27);
    v2.pushRear(63);
    v2.print();
    // [9, 11, 25, 27, 33, 47, 51, 63]

    v1.pushRear(v2);
    v1.print();
    // [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

    x = v1.popFront();
    x = v1.popFront();
    x = v1.popFront();
    v1.print();
    // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
    cout << x << endl;
    // 18

    x = v1.popRear();
    x = v1.popRear();
    x = v1.popRear();
    v1.print();
    // [18, 20, 25, 9, 11, 25, 27, 33]
    cout << x << endl;
    // 47

    x = v2.popAt(3);
    v2.print();
    // [9, 11, 25, 33, 47, 51, 63]
    cout << x << endl;
    // 27

    x = v2.find(51);
    cout << x << endl;
    // 5

    x = v2.find(99);
    cout << x << endl;
    // -1

    myVector v3(v1);
    v3.print();
    // [18, 20, 25, 9, 11, 25, 27, 33]

    v3.pushFront(v2);
    v3.print();
    //[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

    myVector v4("input.dat");
    v4.pushRear(v3);
    v4.print();
    // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

    return 0;
}
