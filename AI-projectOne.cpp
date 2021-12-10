// AI-projectOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/* To DO: 
1. Fix the delete
2. Implement the backTrack solution path function 
3. the fuck am I supposed to print it as steps!! 
*/

#include <iostream>
#include <string>

using namespace std;

// A linked list node
struct Node
{
    string state = "";
    struct Node* parentState = NULL;
    struct Node* next = NULL;
};

// Lists create and initialize: 
struct Node* openList = NULL;
struct Node* closedList = NULL;
struct Node* solutionList = NULL;
// insert new node at the end of the linked list 
void append(struct Node** head, struct Node* node)
{
    // create and allocate node 
    struct Node* newNode = new Node;

    struct Node* last = *head;

    // assign state to the node 
    newNode->state = node->state;

    // set next pointer of new node to null as its the last node
    node->next = NULL;

    // if list is empty, new node becomes first node 
    if (*head == NULL)
    {
        *head = node;
        return;
    }

    // 5. else traverse till the last node 
    while (last->next != NULL)
        last = last->next;

    // change the next of last node 
    last->next = node;
    return;
}

//delete first node in the linked list
Node* deleteFirstNode(struct Node* head)
{
    if (head == NULL)
        return NULL;

    // Move the head pointer to the next node
    Node* tempNode = head;
    head = head->next;
    //delete tempNode;

    return tempNode;
}
//delete last node from linked list
Node* deleteLastNode(struct Node* head)
{
    if (head == NULL)
        return NULL;

    if (head->next == NULL) {
        delete head;
        return NULL;
    }

    // first find second last node
    Node* second_last = head;
    while (second_last->next->next != NULL)
        second_last = second_last->next;

    // delete the last node
    delete (second_last->next);

    // set next of second_last to null
    second_last->next = NULL;

    return head;
}

// display linked list contents
void displayList(struct Node* node)
{
    //traverse the list to display each node
    while (node != NULL)
    {
        cout << node->state << " --> ";
        node = node->next;
    }

    if (node == NULL)
        cout << "null";
}

// check if node's state is the goal state
bool isGoal(struct Node* node)
{
    if (node->state == "000_111")
        return true;
    else
        return false;
}

// return the position of the empty rock
int findEmptyIndex(string state)
{
    return state.find("_");
}

//Operators on node, in order of execution: 
// 1. swap empty space one step to the left if legal move
Node* oneLeft(struct Node* node)
{
    Node* newNode = new Node;
    newNode->parentState = node;
    newNode->state = node->state; 
    newNode->next = NULL;
    int position = findEmptyIndex(newNode->state) - 1;

    newNode->state[position] = '_';
    newNode->state[position + 1] = '1';

    return newNode;
}
// 2. swap empty space 2 steps to the left if legal move
Node* twoLeft(struct Node* node)
{
    Node* newNode = new Node;
    newNode->parentState = node;
    newNode->state = node->state;
    newNode->next = NULL;
    int position = findEmptyIndex(newNode->state) - 2;

    newNode->state[position] = '_';
    newNode->state[position + 2] = '1';
    
    return newNode;
}
// 3. swap empty space one step to the right if legal move
Node* oneRight(struct Node* node)
{
    Node* newNode = new Node;
    newNode->parentState = node;
    newNode->state = node->state;
    newNode->next = NULL;
    int position = findEmptyIndex(newNode->state) + 1;
    
    newNode->state[position] = '_';
    newNode->state[position - 1] = '0';
    
    return newNode;
}
// 4. swap empty space two steps to the right if legal move
Node* twoRight(struct Node* node)
{
    Node* newNode = new Node;
    newNode->parentState = node;
    newNode->state = node->state;
    newNode->next = NULL;
    int position = findEmptyIndex(newNode->state) + 2;

    newNode->state[position] = '_';
    newNode->state[position - 2] = '0';

    return newNode;
}
// check if list contains a state: 
bool containsState(Node* head, string state)
{
    Node* current = head; 
    while (current != NULL)
    {
        if (current->state == state)
            return true;
        current = current->next;
    }
    return false;
}

// main program 
int main()
{

    struct Node* initialState = new Node;
    initialState->state = "111_000";
    initialState->next = NULL;
    struct Node* goalState = new Node;
    goalState->state = "000_111";
    goalState->next = NULL;
    struct Node* tempNode = NULL;

    // Insert to the right of the list.
   append(&openList, initialState);
    
    while (openList != NULL)
    {
            cout << "OPEN before iteration: " << endl;
            displayList(openList);
            cout << endl;
            tempNode = openList;
            openList = openList->next;
            cout << "OPEN at iteration: " << endl;
            displayList(openList);
            cout << endl; 

        if (isGoal(tempNode))
        {
            cout << "Goal Found!!" << endl;

            cout << "Final OPEN" << endl;
            displayList(openList);

            cout << endl << "Final CLOSED" << endl;
            displayList(closedList);

            return 0;
        }
        else
        {
            append(&closedList, tempNode);
            int position = findEmptyIndex(tempNode->state) - 1;
            if (position >= 0 && tempNode->state[position] == '1')
            {
                if (!containsState(openList, oneLeft(tempNode)->state) && !containsState(closedList, oneLeft(tempNode)->state))
                    append(&openList, oneLeft(tempNode));
            }
            position = findEmptyIndex(tempNode->state) - 2;
            if (position >= 0 && tempNode->state[position] == '1')
            {
                if (!containsState(openList, twoLeft(tempNode)->state) && !containsState(closedList, twoLeft(tempNode)->state))
                    append(&openList, twoLeft(tempNode));
            }
            position = findEmptyIndex(tempNode->state) + 1;
            if (position <= 6 && tempNode->state[position] == '0')
            {
                if (!containsState(openList, oneRight(tempNode)->state) && !containsState(closedList, oneRight(tempNode)->state))
                    append(&openList, oneRight(tempNode));
            }
            position = findEmptyIndex(tempNode->state) + 2;
            if (position <= 6 && tempNode->state[position] == '0')
            {
                if (!containsState(openList, twoRight(tempNode)->state) && !containsState(closedList, twoRight(tempNode)->state))
                    append(&openList, twoRight(tempNode));
            }
        }
    }
}

