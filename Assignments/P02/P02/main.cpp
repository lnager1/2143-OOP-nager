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
#include <fstream>
#include "myVector.cpp"

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the myVector class
 * 
 */

int main()
{
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };

    myVector v1(a1, 5);
    myVector v2(a2, 3);

    ofstream fout;
    fout.open("output.txt");

    cout << v1[2] << endl;
    // writes out 3

    v1[4] = 9;
    // v1 now = [1,2,3,4,9]

    cout << v1 << endl;
    // writes out [1,2,3,4,9] to console.

    fout << v1 << endl;
    // writes out [1,2,3,4,9] to your output file.

    myVector v3 = v1 + v2;
    cout << v3 << endl;
    // writes out [11,22,33,4,9] to console.

    std::cout << "couted" << std::endl;
    v3 = v1 - v2;
    std::cout << "Made it here" << endl;
    cout << v3 << endl;
    // writes out [-9,-18,-27,4,9] to console.

    v3 = v2 - v1;
    cout << v3 << endl;
    // writes out [9,18,27,4,9] to console.

    v3 = v2 * v1;
    cout << v3 << endl;
    // writes out [10,40,90,4,9] to console.

    v3 = v1 * v2;
    cout << v3 << endl;
    // writes out [10,40,90,4,9] to console.

    v3 = v1 / v2;
    cout << v3 << endl;
    // writes out [0,0,0,4,9] to console.

    v3 = v2 / v1;
    cout << v3 << endl;
    // writes out [10,10,10,4,9] to console.

    cout << (v2 == v1) << endl;
    // writes 0 to console (false) .

    myVector v4 = v1;
    cout << (v4 == v1) << endl;
    // writes 1 to console (true) .

     return 0;
}
