#include "myVector.h"

/**
* Public : Node
* 
* Description:
*      Contructor that creates new node and doubley 
*      links it with nodes around it
* 
* Params:
*      int      :       the data value
*      Node*    :       points to next node or null
*      Node*    :       points to prev node or null
*
* Returns:
*      No return values
*/
Node::Node(int d, Node *n = nullptr, Node *p = nullptr)
{

    data = d;
    next = n;
    prev = p;
}

/**
* Public : myVector
* 
* Description:
*      Contructor that creates an empty linkedList
* 
* Params:
*      No parameter
*
* Returns:
*      No return values
*/
myVector::myVector()
{
    head = nullptr;
    tail = nullptr;
}

/**
* Public : myVector
* 
* Description:
*      Contructor that creates a linked list initialized
*      with array values
* 
* Params:
*      int      :       array with values
*      int      :       size
*
* Returns:
*      No return values
*/
myVector::myVector(int arry[], int size)
{
    head = nullptr;
    tail = nullptr;

    for (int i = 0; i < size; i++)
    {
        pushRear(arry[i]);
    }
}

/**
* Public : myVector
* 
* Description:
*      Contructor that creates a linked list initialized
*      with values from a file
* 
* Params:
*      string      :    submits file name
*
* Returns:
*      No return values
*/
myVector::myVector(string fileName)
{
    head = tail = nullptr;

    ifstream fin;
    int dat;

    fin.open(fileName);

    while (!fin.eof())
    {
        fin >> dat;
        pushRear(dat);
    }
}

/**
* Public : myVector
* 
* Description:
*      Contructor that creates a linked list initialized
*      with values from a myVector type
* 
* Params:
*      const myVector      :    different instance of myVector
*
* Returns:
*      No return values
*/
myVector::myVector(const myVector &V1)
{
    head = tail = nullptr;
    pushRear(V1);
}

/**
* Public : ~myVector
* 
* Description:
*      Decontructor that deletes each node from
*      the linked list
* 
* Params:
*       No parameter types
*
* Returns:
*      No return values
*/
myVector::~myVector()
{
    Node *travel = head;

    while (travel != nullptr)
    {
        Node *tempnode = travel;
        travel = travel->next;

        // Auto delete nodes
        delete tempnode;
    }

    head = nullptr;
}

/**
* Public : pushFront
* 
* Description:
*      Method that creates a newNode and pushes it 
*      at the head
* 
* Params:
*      int      :    data being added in the node
*
* Returns:
*      No return values
*/
void myVector::pushFront(int val)
{
    // Creates first item
    if (tail == nullptr && head == nullptr)
    {
        tail = new Node(val);
        head = tail;

        numNodes++;
    }

    // Creates every addition item
    else
    {
        // Creates second item
        if (head->next == nullptr)
        {
            head = new Node(val, head);
            tail->prev = head;

            numNodes++;
        }

        // Creates third-n items
        else
        {
            head->prev = new Node(val, head);
            head = head->prev;

            numNodes++;
        }
    }
}

/**
* Public : pushFront
* 
* Description:
*      Method that adds a newVector and pushes it 
*      at the head
* 
* Params:
*      const myVector      :    data being added 
*
* Returns:
*      No return values
*/
void myVector::pushFront(const myVector &V2)
{
    Node *travel = V2.tail;

    while (travel != nullptr)
    {
        pushFront(travel->data);
        travel = travel->prev;
    }
}

/**
* Public : pushRear
* 
* Description:
*      Method that creates a newNode and pushes it 
*      at the tail
* 
* Params:
*      int      :    data being added in the node
*
* Returns:
*      No return values
*/
void myVector::pushRear(int val)
{
    if (head == nullptr)
    {
        head = new Node(val, head);
        tail = head;
        numNodes++;
    }
    else
    {
        if (tail == head)
        {
            tail = new Node(val, nullptr, head);
            head->next = tail;
            numNodes++;
        }
        else
        {
            tail->next = new Node(val, nullptr, tail);
            tail = tail->next;
            numNodes++;
        }
    }
}

/**
* Public : pushRear
* 
* Description:
*      Method that adds a newVector and pushes it 
*      at the tail
* 
* Params:
*      const myVector      :    data being added 
*
* Returns:
*      No return values
*/
void myVector::pushRear(const myVector &V2)
{
    Node *travel = V2.head;

    while (travel != nullptr)
    {
        pushRear(travel->data);
        travel = travel->next;
    }
}

/**
* Public : pushAt
* 
* Description:
*      Method that adds a newNode and pushes it 
*      at the specified location
* 
* Params:
*      int      :    location to insert at
*      int      :    data being added in the node 
*
* Returns:
*      No return values
*/
void myVector::pushAt(int loc, int val)
{
    if (loc == 0)
    {
        pushFront(val);
    }
    else
    {
        if (loc < numNodes)
        {
            // Moving to loc
            Node *useMe = head;
            for (int i = 0; i != loc; i++)
            {
                useMe = useMe->next;
            }

            // Relinking
            useMe->prev->next = new Node(val, useMe, useMe->prev);
            useMe->prev = useMe->prev->next;

            numNodes++;
        }

        // Edge case for when out of bounds
        else
        {
            std::cout << "Pushed to Rear\n";
            pushRear(val);
        }
    }
}

// void myVector::inOrderPush(int val)
// {
//     Node* travel = head;
//     int loc = 0;

//     if(head == nullptr)
//     {
//         pushFront(val);
//     }
//     else
//     {
//         std::cout << travel->data << ' ' << travel->next->data << std::endl;
//         while(travel->data < val && travel->next->data > val || loc+1 != numNodes)
//         {
//             std::cout << "here " <<  travel->data << ' ' << (travel->data < val) << ' ' << travel->next->data << ' ' << (travel->next->data > val) << ' ' << (loc != numNodes) << std::endl;
//             travel = travel->next;
//             loc++;
//         }

//         pushAt(loc, val);
//     }
// }

/**
* Public : popFront
* 
* Description:
*      Method that removes a Node from the head
* 
* Params:
*      No parameter values
*
* Returns:
*      int      :   value that is popped
*/
int myVector::popFront()
{
    // Empty list
    if (head == nullptr && tail == nullptr)
    {
        return -1;
    }

    // One item
    else if (head == tail)
    {
        Node *deleteMe = head;
        int val = deleteMe->data;

        deleteMe->prev = nullptr;
        deleteMe->next = nullptr;
        head = nullptr;
        tail = nullptr;

        delete deleteMe;
        numNodes--;

        return val;
    }

    // All the items
    else
    {
        Node *deleteMe = head;
        int val = deleteMe->data;

        // Relinking
        head = head->next;
        head->prev = nullptr;

        delete deleteMe;
        numNodes--;

        return val;
    }
}

/**
* Public : popFront
* 
* Description:
*      Method that removes a Node from the tail
* 
* Params:
*      No parameter values
*
* Returns:
*      int      :   value that is popped
*/
int myVector::popRear()
{
    if (head == nullptr && tail == nullptr)
    {
        return -1;
    }
    else if (head == tail)
    {
        Node *deleteMe = head;
        int val = deleteMe->data;

        deleteMe->prev = nullptr;
        deleteMe->next = nullptr;
        head = nullptr;
        tail = nullptr;

        delete deleteMe;
        numNodes--;

        return val;
    }
    else
    {
        Node *deleteMe = tail;
        int val = deleteMe->data;

        tail = tail->prev;
        tail->next = nullptr;

        delete deleteMe;
        numNodes--;

        return val;
    }
}

/**
* Public : popAt
* 
* Description:
*      Method that removes a Node from specified location
* 
* Params:
*      int      :   location to remove at
*
* Returns:
*      int      :   value that is popped
*/
int myVector::popAt(int loc)
{
    if (loc == 0)
    {
        return popFront();
    }
    else
    {
        if (loc < numNodes)
        {
            Node *useMe = head;
            for (int i = 0; i != loc; i++)
            {
                useMe = useMe->next;
            }

            // Relinking
            useMe->prev->next = useMe->next;
            useMe->next->prev = useMe->prev;

            int val = useMe->data;
            delete useMe;

            numNodes--;
            return val;
        }
        else
        {
            return -1;
        }
    }
}

/**
* Public : find
* 
* Description:
*      Returns the location of a given value
* 
* Params:
*      int      :   value to search for
*
* Returns:
*      int      :   location found at
*/
int myVector::find(int val)
{
    Node* travel = head;
    int loc = 0;
    
    // Finding val
    while(travel->data != val && travel->next != nullptr)
    {
        travel = travel->next;
        loc++;
    }

    // returning loc or -1 if not found
    if(travel->data == val)
    {
        return loc;
    }
    else
    {
        return -1;
    }

}

/**
* Public : print
* 
* Description:
*      prints vector asthetically 
* 
* Params:
*      No parameter values
*
* Returns:
*      No return values
*/
void myVector::print()
{
    Node *travel = head;

    std::cout << "[";

    while (travel != nullptr)
    {
        std::cout << travel->data;

        if (travel->next != nullptr)
        {
            std::cout << ", ";
        }
        else
        {
            std::cout << "]";
        }

        travel = travel->next;
    }
    std::cout << "\n\n";
}

/**
* Public : operator[]
* 
* Description:
*      overloads the brackets operator to access memory in the class
* 
* Params:
*      int      :   location to grab information from
*
* Returns:
*      int&      :  value inside node at specified loc
*/
int& myVector::operator[] (int loc)
{
    int* temp;
    if (loc == 0)
    {
        return (head->data);
    }
    else
    {
        if (loc < numNodes)
        {
            Node *useMe = head;
            for (int i = 0; i != loc; i++)
            {
                useMe = useMe->next;
            }
            return (useMe->data);
        }
        else
        {
            throw std::out_of_range("Out of Bounds");
        }
    }
}

/**
* Public : operator+
* 
* Description:
*      overloads the addition operator to add vectors together
* 
* Params:
*      const myVector&      :   vector to be added to original    
*
* Returns:
*      const myVector       :   new vector that contain added values
*/
const myVector myVector::operator+ (const myVector &other)
{
    Node* travel = head;
    Node* otherTravel = other.head;
    myVector returnVal;

    if(numNodes != other.numNodes)
    {
        if(numNodes > other.numNodes)
        {
            for(int i = 0; i < other.numNodes; i++)
            {
                returnVal.pushRear(travel->data + otherTravel->data);

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(travel != nullptr)
            {
                returnVal.pushRear(travel->data);
                travel = travel->next;
            }
            
            return returnVal;
        }
        else
        {
            for(int i = 0; i < numNodes; i++)
            {
                returnVal.pushRear(travel->data + otherTravel->data);

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(otherTravel != nullptr)
            {
                returnVal.pushRear(otherTravel->data);
                otherTravel = otherTravel->next;
            }    

            return returnVal;
        }
    }
    else
    {
        for(int i = 0; i < numNodes; i++)
        {
            returnVal.pushRear(travel->data + otherTravel->data);

            travel = travel->next;
            otherTravel = otherTravel->next;
        }
        return returnVal;
    }
}

/**
* Public : operator-
* 
* Description:
*      overloads the subtraction operator to subtract vectors from one another
* 
* Params:
*      const myVector&      :   vector to be subtracted from original    
*
* Returns:
*      const myVector       :   new vector that contain subtracted values
*/
const myVector myVector::operator- (const myVector &other)
{
    Node* travel = head;
    Node* otherTravel = other.head;
    myVector returnVal;

    if(numNodes != other.numNodes)
    {
        if(numNodes > other.numNodes)
        {
            for(int i = 0; i < other.numNodes; i++)
            {
                returnVal.pushRear(travel->data - otherTravel->data);

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(travel != nullptr)
            {
                returnVal.pushRear(travel->data);
                travel = travel->next;
            }
            
            return returnVal;
        }
        else
        {
            for(int i = 0; i < numNodes; i++)
            {
                returnVal.pushRear(travel->data - otherTravel->data);

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(otherTravel != nullptr)
            {
                returnVal.pushRear(otherTravel->data);
                otherTravel = otherTravel->next;
            }    

            return returnVal;
        }
    }
    else
    {
        for(int i = 0; i < numNodes; i++)
        {
            returnVal.pushRear(travel->data - otherTravel->data);

            travel = travel->next;
            otherTravel = otherTravel->next;
        }
        return returnVal;
    }
}

/**
* Public : operator*
* 
* Description:
*      overloads the multiplication operator to multipy vectors together
* 
* Params:
*      const myVector&      :   vector to be multipy to original    
*
* Returns:
*      const myVector       :   new vector that contain multiplied values
*/
const myVector myVector::operator* (const myVector &other)
{
    Node* travel = head;
    Node* otherTravel = other.head;
    myVector returnVal;

    if(numNodes != other.numNodes)
    {
        if(numNodes > other.numNodes)
        {
            for(int i = 0; i < other.numNodes; i++)
            {
                returnVal.pushRear(travel->data * otherTravel->data);

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(travel != nullptr)
            {
                returnVal.pushRear(travel->data);
                travel = travel->next;
            }
            
            return returnVal;
        }
        else
        {
            for(int i = 0; i < numNodes; i++)
            {
                returnVal.pushRear(travel->data * otherTravel->data);

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(otherTravel != nullptr)
            {
                returnVal.pushRear(otherTravel->data);
                otherTravel = otherTravel->next;
            }    

            return returnVal;
        }
    }
    else
    {
        for(int i = 0; i < numNodes; i++)
        {
            returnVal.pushRear(travel->data * otherTravel->data);

            travel = travel->next;
            otherTravel = otherTravel->next;
        }
        return returnVal;
    }
}

/**
* Public : operator/
* 
* Description:
*      overloads the division operator to divide vectors from one another
* 
* Params:
*      const myVector&      :   vector to be divided from original    
*
* Returns:
*      const myVector       :   new vector that contain divided values
*/
const myVector myVector::operator/ (const myVector &other)
{
    Node* travel = head;
    Node* otherTravel = other.head;
    myVector returnVal;

    if(numNodes != other.numNodes)
    {
        if(numNodes > other.numNodes)
        {
            for(int i = 0; i < other.numNodes; i++)
            {
                if(otherTravel->data != 0)
                {
                    returnVal.pushRear(travel->data / otherTravel->data);    
                }
                else
                {
                    returnVal.pushRear(0);
                }

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(travel != nullptr)
            {
                returnVal.pushRear(travel->data);
                travel = travel->next;
            }
            
            return returnVal;
        }
        else
        {
            for(int i = 0; i < numNodes; i++)
            {
                if(otherTravel->data != 0)
                {
                    returnVal.pushRear(travel->data / otherTravel->data);    
                }
                else
                {
                    returnVal.pushRear(0);
                }

                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            while(otherTravel != nullptr)
            {
                returnVal.pushRear(otherTravel->data);
                otherTravel = otherTravel->next;
            }    

            return returnVal;
        }
    }
    else
    {
        for(int i = 0; i < numNodes; i++)
        {
            if(otherTravel->data != 0)
            {
                returnVal.pushRear(travel->data / otherTravel->data);    
            }
            else
            {
                returnVal.pushRear(0);
            }

            travel = travel->next;
            otherTravel = otherTravel->next;
        }
        return returnVal;
    }
}

/**
* Public : operator==
* 
* Description:
*      overloads the equivilancy operator to see if vectors are identical
* 
* Params:
*      const myVector&      :   vector to checked against     
*
* Returns:
*      bool                 :   true or false based on eqivilancy
*/
bool myVector::operator== (const myVector &other)
{
    Node* travel = head;
    Node* otherTravel = other.head;

    if(numNodes == other.numNodes)
    {
        for(int i = 0; i < numNodes; i++)
        {
            if(travel->data == otherTravel->data)
            {
                travel = travel->next;
                otherTravel = otherTravel->next;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
* Public : operator=
* 
* Description:
*      overloads the assignment operator to assign an entire vectors values to another
* 
* Params:
*      const myVector&      :   vector to be assigned to original    
*
* Returns:
*      const myVector       :   original vector that contains new values
*/
void myVector::operator= (const myVector &other)
{
    Node* travel = this->head;

    while(travel != nullptr)
    {
        travel = travel->next;
        popFront();
    }

    pushFront(other);
}

/**
* Public : operator<<
* 
* Description:
*      overloads the ostream operator to make vectors printable to console and file
* 
* Params:
*      std::ostream &       :   ostream value that allows for output
*      const myVector&      :   vector to be ostreamed    
*
* Returns:
*      std::ostream &       :   allows for continual operations
*/
std::ostream &operator<< (std::ostream &os, myVector &other)
{
    Node *travel = other.head;

    os << "[";

    while (travel != nullptr)
    {
        os << travel->data;

        if (travel->next != nullptr)
        {
            os << ", ";
        }
        else
        {
            os << "]";
        }

        travel = travel->next;
    }
    os << "\n\n";

    return os;
}