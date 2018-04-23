/*  bintree.h-------------------------------------------------------------------
 
 Michael Ji CSS343A
 
 Creation: 4/15/17
 
 Date of Last Modification : 4/22/17
 
 -------------------------------------------------------------------------------
 
 Purpose - contains the declarations of the binary search tree
 
 -------------------------------------------------------------------------------
 
 This file lists out the declarations for the binary search tree bintree class
 
 -----------------------------------------------------------------------------*/

#ifndef bintree_h
#define bintree_h
#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

/* BinTree----------------------------------------------------------------------
 
 Michael Ji CSS343A
 
 Creation: 4/15/17
 
 Date of Last Modification : 4/22/17
 
 -------------------------------------------------------------------------------
 
 Purpose - lists the declarations to be completed by the cpp class.
 
 -------------------------------------------------------------------------------
 
 This class lists the methods to be declared
 
 -----------------------------------------------------------------------------*/
class BinTree
{
/*operator<<--------------------------------------------------------------------
 
 Description: prints the bintree in correct form to the console or identifies
 that it is empty.
 
 operator<<: function to print out bintree
 preconditions: valid bintree.
 postconditions: prints out the bintree to the console or identifies empty.
 
 -----------------------------------------------------------------------------*/
    friend ostream & operator<<(ostream & output, const BinTree & tree);
    
    
public:
    
/*BinTree-----------------------------------------------------------------------
 
 Description: default constructor to create an empty BinTree
 
 BinTree: default constructor
 preconditions: none.
 postconditions: creates empty BinTree.
 
 -----------------------------------------------------------------------------*/
    BinTree();
    
/*BinTree-----------------------------------------------------------------------
 
 Description: copy constructor to create an empty BinTree
 
 BinTree: copy constructor
 preconditions: valid original.
 postconditions: copies bintree.
 
 -----------------------------------------------------------------------------*/
    BinTree(const BinTree & original);
    
/*~BinTree----------------------------------------------------------------------
 
 Description: destructor for bintree
 
 ~BinTree: destructor
 preconditions: none
 postconditions: empty bintree
 
 -----------------------------------------------------------------------------*/
    ~BinTree();
    
/*isEmpty-----------------------------------------------------------------------
 
 Description: function to check if bintree is empty
 
 isEmpty: checks if bintree is empty by returning a bool
 preconditions: valid bintree
 postconditions: returns a bool depending on bintree
 
 -----------------------------------------------------------------------------*/
    bool isEmpty() const;
    
/*makeEmpty---------------------------------------------------------------------
 
 Description: function to empty bintree
 
 makeEmpty: calls helper to empty bintree
 preconditions: valid bintree
 postconditions: empty bintree
 
 -----------------------------------------------------------------------------*/
    void makeEmpty();
    
/*operator=---------------------------------------------------------------------
 
 Description: = operator overload
 
 operator=: sets the left as the right
 preconditions: valid bintrees
 postconditions: left bintree is now right
 
 -----------------------------------------------------------------------------*/
    BinTree& operator=(const BinTree & rhs);
    
/*operator==--------------------------------------------------------------------
 
 Description: == equality overload
 
 operator==: returns bool depending on equality
 preconditions: valid bintree
 postconditions: returns bool
 
 -----------------------------------------------------------------------------*/
    bool operator==(const BinTree & rhs) const;
    
/*operator!=--------------------------------------------------------------------
 
 Description: inequality operator overload
 
 operator!=: returns bool depending on inequality
 preconditions: valid bintree
 postconditions: returns bool
 
 -----------------------------------------------------------------------------*/
    bool operator!=(const BinTree & rhs) const;
    
/*insert------------------------------------------------------------------------
 
 Description: adds a new node to bintree
 
 insert: returns bool depending if adding new data was successful
 preconditions: valid data
 postconditions: returns bool and bintree is updated
 
 -----------------------------------------------------------------------------*/
    bool insert(NodeData *newData);
    
/*retrieve----------------------------------------------------------------------
 
 Description: retrieves a target node
 
 retrieve: returns bool depending on if target is present and sets it to garbage
 preconditions: valid bintree and target
 postconditions: returns bool depending on success and garbage is changed
 
 -----------------------------------------------------------------------------*/
    bool retrieve(const NodeData & target, NodeData*& garbage);
    
/*getHeight---------------------------------------------------------------------
 
 Description: gets height of target
 
 getHeight: returns height of target if it is found else 0
 preconditions: valid target and bintree
 postconditions: returns int depending on targets height
 
 -----------------------------------------------------------------------------*/
    int getHeight(const NodeData & target) const;
    /*
      For this function only, you do not get to know that the tree is a binary search tree. You must solve the problem for a general binary tree where data could be stored anywhere (e.g., tree T4 above). Use this height definition: the height of a node at a leaf is 1, height of a node at the next level is 2, and so on.  The height of a value not found is zero.
     */

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
    void displaySideways() const;
    
/*bstreeToArray-----------------------------------------------------------------
 
 Description: makes bintree to array
 
 bstreeToArray: empties bintree and makes it into array in order
 preconditions: valid bintree
 postconditions: bintree emptied and arr is fill in order
 
 -----------------------------------------------------------------------------*/
    void bstreeToArray(NodeData* arr[]);
    
/*arrayToBSTree-----------------------------------------------------------------
 
 Description: empties array and makes bintree
 
 arrayToBSTree: empties array and makes it into bst
 preconditions: valid arr
 postconditions: arr emptied and bintree filled
 
 -----------------------------------------------------------------------------*/
    void arrayToBSTree(NodeData* arr[]);
    
private:
    struct Node
    {
        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
    };
    Node* root;								// root of the tree
    
// utility functions
    
/*inorderHelper-----------------------------------------------------------------
 
 Description: helps << overload print out bintree in order
 
 inorderHelper: outputs bintree in order
 preconditions: valid bintree
 postconditions: bintree output in order
 
 -----------------------------------------------------------------------------*/
    void inorderHelper(Node* cur, ostream &out) const;
    
//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
    void sideways(Node* head, int start) const;
    
/*insertHelper------------------------------------------------------------------
 
 Description: recursive helper for insert
 
 insertHelper: returns bool depending on success of inserting node
 preconditions: valid bintree
 postconditions: bool depending if node is successfully added
 
 -----------------------------------------------------------------------------*/
    bool insertHelper(NodeData *newData, Node *&cur);
    
/*deallocateHelper--------------------------------------------------------------
 
 Description: recursive deallocate helper
 
 deallocateHelper: recursively deallocates a node
 preconditions: valid bintree
 postconditions: empty bintree
 
 -----------------------------------------------------------------------------*/
    void deallocateHelper(Node *&cur);
    
/*copyHelper--------------------------------------------------------------------
 
 Description: recursive copy helper
 
 copyHelper: recursively copies node from rhs to cur
 preconditions: valid bintree
 postconditions: cur is now deep copied as rhs
 
 -----------------------------------------------------------------------------*/
    void copyHelper(Node* &cur, Node* rhs);
    
/*equalityHelper----------------------------------------------------------------
 
 Description: recursive equality helper
 
 equalityHelper: recursively checks if bintree are equal
 preconditions: valid bintree
 postconditions: returns bool depending if nodes are equal
 
 -----------------------------------------------------------------------------*/
    bool equalityHelper(Node* cur, Node* rhs) const;
    
/*retrieveHelper----------------------------------------------------------------
 
 Description: recursive helper for retriving node
 
 retrieveHelper: checks if node is present returns bool depending on success
 preconditions: valid bintree and target
 postconditions: returns bool, garbage is pointer to present target
 
 -----------------------------------------------------------------------------*/
    bool retrieveHelper(Node* cur, const NodeData &target, NodeData*& garbage);
    
/*heightHelper------------------------------------------------------------------
 
 Description: recursive helper for height
 
 heightHelper: recursively searches through bintree to find height of node
 preconditions: valid target and bintree
 postconditions: returns int depending on height of node
 
 -----------------------------------------------------------------------------*/
    int heightHelper(const NodeData target, Node *cur, int height) const;
    
/*toArrayHelper-----------------------------------------------------------------
 
 Description: helper for bintree to array
 
 toArrayHelper: recursively adds bintree to array
 preconditions:  valid bintree
 postconditions: empty bintree and full array
 
 -----------------------------------------------------------------------------*/
    void toArrayHelper(Node* cur, NodeData* arr[], int &pos) const;
    
/*toBSTreeHelper----------------------------------------------------------------
 
 Description: helper for array to bintree
 
 toBSTreeHelper: recursively adds array to bintree
 preconditions: valid array
 postconditions: empty array and fills bintree
 
 -----------------------------------------------------------------------------*/
    void toBSTreeHelper(Node* cur, NodeData* arr[], int low, int high);
};

#endif /* bintree_h */
