/*  bintree.cpp-----------------------------------------------------------------
 
 Michael Ji CSS343A
 
 Creation: 4/15/17
 
 Date of Last Modification : 4/22/17
 
 -------------------------------------------------------------------------------
 
 Purpose - contains the declarations and full functions 
 of the binary search tree class
 
 -------------------------------------------------------------------------------
 
 This file holds the full functions based off the declarations made in the
 bintree.h class. Assumes that the user will use the properly parameters
 identified for each function.
 
 -----------------------------------------------------------------------------*/

#include "bintree.h"
#include "nodedata.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/*operator<<--------------------------------------------------------------------
 
 Description: prints the bintree in correct form to the console or identifies
 that it is empty.
 
 operator<<: function to print out bintree
 preconditions: valid bintree.
 postconditions: prints out the bintree to the console or identifies empty.
 
 -----------------------------------------------------------------------------*/
ostream& operator<<(ostream & output, const BinTree & tree)
{
    tree.inorderHelper(tree.root, output);
    output << endl;
    return output;
}

/*BinTree-----------------------------------------------------------------------
 
 Description: default constructor to create an empty BinTree
 
 BinTree: default constructor
 preconditions: none.
 postconditions: creates empty BinTree.
 
 -----------------------------------------------------------------------------*/
BinTree::BinTree()
{
    root = NULL;
}

/*BinTree-----------------------------------------------------------------------
 
 Description: copy constructor to create an empty BinTree
 
 BinTree: copy constructor
 preconditions: valid original.
 postconditions: copies bintree.
 
 -----------------------------------------------------------------------------*/
BinTree::BinTree(const BinTree & original)
{
    copyHelper(root, original.root);
}

/*~BinTree----------------------------------------------------------------------
 
 Description: destructor for bintree
 
 ~BinTree: destructor
 preconditions: none
 postconditions: empty bintree
 
 -----------------------------------------------------------------------------*/
BinTree::~BinTree()
{
    deallocateHelper(root);
}

/*isEmpty-----------------------------------------------------------------------
 
 Description: function to check if bintree is empty
 
 isEmpty: checks if bintree is empty by returning a bool
 preconditions: valid bintree
 postconditions: returns a bool depending on bintree
 
 -----------------------------------------------------------------------------*/
bool BinTree::isEmpty() const
{
    if (root == NULL)
    {
        return true;
    }
    return false;
}

/*makeEmpty---------------------------------------------------------------------
 
 Description: function to empty bintree
 
 makeEmpty: calls helper to empty bintree
 preconditions: valid bintree
 postconditions: empty bintree
 
 -----------------------------------------------------------------------------*/
void BinTree::makeEmpty()
{
    deallocateHelper(root);
}

/*operator=---------------------------------------------------------------------
 
 Description: = operator overload
 
 operator=: sets the left as the right
 preconditions: valid bintrees
 postconditions: left bintree is now right
 
 -----------------------------------------------------------------------------*/
BinTree& BinTree::operator=(const BinTree & rhs)
{
    if (*this == rhs)
    {
        return *this;
    }
    // deallocate
    deallocateHelper(root);
    // copy
    copyHelper(root, rhs.root);
    return *this;
}

/*operator==--------------------------------------------------------------------
 
 Description: == equality overload
 
 operator==: returns bool depending on equality
 preconditions: valid bintree
 postconditions: returns bool
 
 -----------------------------------------------------------------------------*/
bool BinTree::operator==(const BinTree & rhs) const
{
    return equalityHelper(root, rhs.root);
}

/*operator!=--------------------------------------------------------------------
 
 Description: inequality operator overload
 
 operator!=: returns bool depending on inequality
 preconditions: valid bintree
 postconditions: returns bool
 
 -----------------------------------------------------------------------------*/
bool BinTree::operator!=(const BinTree & rhs) const
{
    return !(*this == rhs);
}

/*insert------------------------------------------------------------------------
 
 Description: adds a new node to bintree
 
 insert: returns bool depending if adding new data was successful
 preconditions: valid data
 postconditions: returns bool and bintree is updated
 
 -----------------------------------------------------------------------------*/
bool BinTree::insert(NodeData *newData)
{
    return insertHelper(newData, root);
}

/*retrieve----------------------------------------------------------------------
 
 Description: retrieves a target node
 
 retrieve: returns bool depending on if target is present and sets it to garbage
 preconditions: valid bintree and target
 postconditions: returns bool depending on success and garbage is changed
 
 -----------------------------------------------------------------------------*/
bool BinTree::retrieve(const NodeData & target, NodeData*& garbage)
{
    if (root == NULL)
    {
        return false;
    }
    else
        return retrieveHelper(root, target, garbage);
}

/*getHeight---------------------------------------------------------------------
 
 Description: gets height of target
 
 getHeight: returns height of target if it is found else 0
 preconditions: valid target and bintree
 postconditions: returns int depending on targets height
 
 -----------------------------------------------------------------------------*/
int BinTree::getHeight(const NodeData & target) const
{
    if (root == NULL)
    {
        return 0;
    }
    Node* cur = root;
    return heightHelper(target, cur, 1);
}


//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
    sideways(root, 0);
}

/*bstreeToArray-----------------------------------------------------------------
 
 Description: makes bintree to array
 
 bstreeToArray: empties bintree and makes it into array in order
 preconditions: valid bintree
 postconditions: bintree emptied and arr is fill in order
 
 -----------------------------------------------------------------------------*/
void BinTree::bstreeToArray(NodeData* arr[])
{
    int pos = 0;
    toArrayHelper(root, arr, pos);
    makeEmpty();
}

/*arrayToBSTree-----------------------------------------------------------------
 
 Description: empties array and makes bintree
 
 arrayToBSTree: empties array and makes it into bst
 preconditions: valid arr
 postconditions: arr emptied and bintree filled
 
 -----------------------------------------------------------------------------*/
void BinTree::arrayToBSTree(NodeData* arr[])
{
    int max = 0;
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] != NULL)
        {
            max++;
        }
    }
    toBSTreeHelper(root, arr, 0, max - 1);
}

/*bstreeToArray-----------------------------------------------------------------
 
 Description: makes bintree to array
 
 bstreeToArray: empties bintree and makes it into array in order
 preconditions: valid bintree
 postconditions: bintree emptied and arr is fill in order
 
 -----------------------------------------------------------------------------*/
void BinTree::toArrayHelper(Node* cur, NodeData* arr[], int &pos) const
{
    if (cur == NULL)
    {
        return;
    }

    toArrayHelper(cur->left, arr, pos);
    arr[pos] = cur->data;
    
    /*
    arr[pos] = cur->data;
    NodeData* dataToArr = cur->data;
    cur->data = NULL;
    *(arr + pos) = dataToArr;
    dataToArr = NULL;
     */
    pos++;
    toArrayHelper(cur->right, arr, pos);
}

/*arrayToBSTree-----------------------------------------------------------------
 
 Description: empties array and makes bintree
 
 arrayToBSTree: empties array and makes it into bst
 preconditions: valid arr
 postconditions: arr emptied and bintree filled
 
 -----------------------------------------------------------------------------*/
void BinTree::toBSTreeHelper(Node* cur, NodeData* arr[], int low, int high)
{
 
    if (high < low)
    {
        cur = NULL;
    }
    else
    {
  
        int mid = (low + high) / 2;
	/*
        NodeData* dataToBST;
        dataToBST = arr[mid];
        arr[mid] = NULL;
        insert(dataToBST);
	*/
	insert(arr[mid]);
	arr[mid] = NULL;
	
        toBSTreeHelper(cur, arr, low, mid - 1);
        toBSTreeHelper(cur, arr, mid + 1, high);
	}
}

/*inorderHelper-----------------------------------------------------------------
 
 Description: helps << overload print out bintree in order
 
 inorderHelper: outputs bintree in order
 preconditions: valid bintree
 postconditions: bintree output in order
 
 -----------------------------------------------------------------------------*/
void BinTree::inorderHelper(Node* cur, ostream &out) const
{
    if (cur == NULL)
    {
        return;
    }
    inorderHelper(cur->left, out);
    out << *cur->data << " "; 
    inorderHelper(cur->right, out);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);
        
        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }
        
        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}

/*insertHelper------------------------------------------------------------------
 
 Description: recursive helper for insert
 
 insertHelper: returns bool depending on success of inserting node
 preconditions: valid bintree
 postconditions: bool depending if node is successfully added
 
 -----------------------------------------------------------------------------*/
bool BinTree::insertHelper(NodeData *newData, Node *&cur)
{
    if (cur == NULL)
    {
        cur = new Node;
        cur->data = newData;
        cur->right = NULL;
        cur->left = NULL;
        return true;
    }
    else if (*newData == *cur->data)
    {
        return false;
    }
    else if (*newData < *cur->data)
    {
        return insertHelper(newData, cur->left);
    }
    else if (*newData > *cur->data)
    {
        return insertHelper(newData, cur->right);
    }
    return false;
    
    
}

/*deallocateHelper--------------------------------------------------------------
 
 Description: recursive deallocate helper
 
 deallocateHelper: recursively deallocates a node
 preconditions: valid bintree
 postconditions: empty bintree
 
 -----------------------------------------------------------------------------*/
void BinTree::deallocateHelper(Node *&cur)
{
    /*
    if (cur == NULL)
    {
        return;
    }
    deallocateHelper(cur->left);
    deallocateHelper(cur->right);
    if (cur != NULL) //->data
    {
        delete cur->data;
    }
    cur->data = NULL;
    cur->left = NULL;
    cur->right = NULL;
    //deleting cur might error
    delete cur;
    cur = NULL;
    */
 
    if (cur != NULL)
    {
        deallocateHelper(cur->left);
        deallocateHelper(cur->right);
        delete cur;
        cur = NULL;
    }
}

/*copyHelper--------------------------------------------------------------------
 
 Description: recursive copy helper
 
 copyHelper: recursively copies node from rhs to cur
 preconditions: valid bintree
 postconditions: cur is now deep copied as rhs
 
 -----------------------------------------------------------------------------*/
void BinTree::copyHelper(Node* &cur, Node* rhs)
{
    if (rhs == NULL)
    {
        return;
    }
    cur = new Node;
    //cur->data = rhs->data;
    NodeData  * temp = new NodeData(*rhs->data);
    cur->data = temp;
    cur->left = NULL;
    cur->right = NULL;
    copyHelper(cur->left, rhs->left);
    copyHelper(cur->right, rhs->right);
}

/*equalityHelper----------------------------------------------------------------
 
 Description: recursive equality helper
 
 equalityHelper: recursively checks if bintree are equal
 preconditions: valid bintree
 postconditions: returns bool depending if nodes are equal
 
 -----------------------------------------------------------------------------*/
bool BinTree::equalityHelper(Node* cur, Node* rhs) const
{
    if (cur == NULL && rhs == NULL)
    {
        return true;
        
    }
    if (cur == NULL || rhs == NULL)
    {
        return false;
    }
    if (*cur->data != *rhs->data)
    {
        return false;
        
    }
    return (*cur->data == *rhs->data && equalityHelper(cur->left, rhs->left)
	    && equalityHelper(cur->right, rhs->right));
}

/*retrieveHelper----------------------------------------------------------------
 
 Description: recursive helper for retriving node
 
 retrieveHelper: checks if node is present returns bool depending on success
 preconditions: valid bintree and target
 postconditions: returns bool, garbage is pointer to present target
 
 -----------------------------------------------------------------------------*/
bool BinTree::retrieveHelper(Node* cur, const NodeData &target, NodeData*& garbage)
{
    if (cur == NULL)
    {
        garbage = NULL;
        return false;
    }
    if (*cur->data == target)
    {
        garbage = cur->data;
        return true;
    }
    else if (*cur->data > target)
    {
        //if (cur->left == NULL)
        //{
        //    return false;
        //}
        //else
        return retrieveHelper(cur->left, target, garbage);
    }
    else if (*cur->data < target)
    {
        //if (cur->right == NULL)
        //{
        //   return false;
        //}
        //else
        return retrieveHelper(cur->right, target, garbage);
    }
    return false;
}

/*heightHelper------------------------------------------------------------------
 
 Description: recursive helper for height
 
 heightHelper: recursively searches through bintree to find height of node
 preconditions: valid target and bintree
 postconditions: returns int depending on height of node
 
 -----------------------------------------------------------------------------*/
int BinTree::heightHelper(const NodeData target, Node *cur, int height) const
{

    if (cur == NULL)
    {
        return 0;
    }
    if (*cur->data == target)
    {
        return height;
    }
    int level = heightHelper(target, cur->left, height + 1);
    if (level != 0)
    {
        return level;
    }
    return heightHelper(target, cur->right, height + 1);

}
