/*
Container.cpp
Author: Michael Ji
Description: Contains and defines the functions to be used for the container class
Purpose of the container class is to hold a linked list of pixels and its coordinates.
The container is supposed to contain pixels/coordinates of a pixel similar to the first/seed pixel.
Contains bool for equality and inequality between containers.
Contains functions to add pixels to a container and check if the container is empty.
Can get seed pixel. Can merge containers together. Can change colors of the pixels in the container.
*/

#include "Container.h"
#include "ImageObj.h"
#include "ImageLib.h"
#include <iostream>
using namespace std;

/*
Container: default constructor.
precondtion: none.
postcondition: creates empty container.
*/
Container::Container()
{
	head = nullptr;
}

/*
~Container: destructs the container.
precondtion: none.
postcondition: deletes all nodes and sets their pointers to null, with head being null.
*/
Container::~Container()
{
	if (head == nullptr)
	{
		return;
	}
	Node *cur = head;
	Node *temp = head;
	head = nullptr;
	while (cur != nullptr)
	{
		cur = cur->next;
		delete temp;
		temp = cur;
	}
}

/*
Container: constructs a container with following data as the first node.
precondtion: valid pixel and int.
postcondition: creates a container with the first node containing the data entered.
*/
Container::Container(const pixel seed, const int rowIn, const int colIn)
{

	head = new Node;
	head->next = nullptr;
	head->p = seed;
	head->row = rowIn;
	head->col = colIn;
}

/*
container: copy constructor that copies obj over to this.
precondtion: valid obj container.
postcondition: deep copies obj over onto this.
*/
Container::Container(const Container & obj)
{
	if (obj.head == nullptr)
	{
		head = nullptr;
		return;
	}
	else
	{
		//Node *head is already done, pointer is declared and now we can make what it points to
		head = new Node;
		head->next = nullptr;
		head->col = obj.head->col;
		head->row = obj.head->row;
		head->p = obj.head->p;
		Node *cur = head;
		//Node *objHead = obj.head;
		Node *curObj = obj.head;
		while (curObj->next != nullptr) {
			cur->next = new Node;
			cur->next->next = nullptr;
			cur->next->col = curObj->next->col;
			cur->next->row = curObj->next->row;
			cur->next->p = curObj->next->p;
			curObj = curObj->next;
			cur = cur->next;
		}
	}
}

/*
operator==: boolean to check equality.
precondition: two valid containers.
postcondition: returns boolean depending on if they are equal or not
*/
bool Container::operator==(const Container &obj) const
{
	if ((head == nullptr) && (obj.head == nullptr))
	{
		return true;
	}
	Node *cur = head;
	Node *objCur = obj.head;

	while ((cur != nullptr) && (objCur != nullptr))
	{
		if (cur == nullptr || objCur == nullptr)
		{
			return false;
		}
		if ((cur->p.blue != objCur->p.blue) || (cur->p.red != objCur->p.red) || (cur->p.green != objCur->p.green))
		{
			return false;
		}
		if (cur->row != objCur->row)
		{
			return false;
		}
		if (cur->col != objCur->col)
		{
			return false;
		}
		cur = cur->next;
		objCur = objCur->next;
	}
	return true;
}

/*
operator!=: boolean to check inequality.
precondition: two valid containers.
postcondition: returns boolean opposite of ==.
*/
bool Container::operator!=(const Container &obj) const
{
	return !(*this == obj);
}

/*
operator=: sets this container equal to obj.
precondition: valid this container and obj container.
postcondition: returns this container as equal to obj container.
*/
Container Container::operator=(const Container & obj)
{
	if (this->head != nullptr)
	{
		Node *del = head;
		Node *cur = head;

		while (del != nullptr)
		{
			cur = cur->next;
			delete del;
			del = nullptr;
			del = cur;
		}
	}
	//if obj is null; return this
	if (obj.head == nullptr)
	{
		return *this;
	}
	else //deep copies obj onto this
	{
		head = new Node;
		head->next = nullptr;
		head->col = obj.head->col;
		head->row = obj.head->row;
		head->p = obj.head->p;
		Node *cur = head;
		Node *curObj = obj.head;
		while (curObj->next != nullptr) {
			cur->next = new Node;
			cur->next->next = nullptr;
			cur->next->col = curObj->next->col;
			cur->next->row = curObj->next->row;
			cur->next->p = curObj->next->p;
			curObj = curObj->next;
			cur = cur->next;
		}
		return *this;
	}
}

/*
addPixel: adds pixel and coordinates to the container.
precondition: valid container, pixel, ints.
postcondition: creates a new node and adds it to the end of the container with the data.
*/
void Container::addPixel(const pixel pIn, const int rowIn, const int colIn)
{
	if (head == nullptr)
	{
		head = new Node;
		head->next = nullptr;
		head->p = pIn;
		head->row = rowIn;
		head->col = colIn;
		//it works if i dont put a return here... so does if it goes into this if statement... does the rest of the method not go?
		return;
	}
	Node *cur = head;
	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
	cur->next = new Node;
	cur->next->next = nullptr;
	cur->next->p = pIn;
	cur->next->row = rowIn;
	cur->next->col = colIn;
}

/*
merge: merges the obj container on to this container.
precondition: two valid containers.
postcondition: returns this container with obj container deep copied onto its end.
*/
Container Container::merge(const Container & obj)
{
	Node *cur;
	cur = head;
    if (obj.head == nullptr)
    {
        return *this;
    }
	if (cur == nullptr)
	{
		*this = obj;
        return *this;
	}

	while (cur->next != nullptr)
	{
		cur = cur->next;
	}
    Node *objCur;
    objCur = obj.head;
	while (objCur != nullptr)
    {
        Node *newNode = new Node;
        newNode->next = nullptr;
        newNode->p = objCur->p;
        newNode->row = objCur->row;
        newNode->col = objCur->col;
        cur->next = newNode;
        cur= cur->next;
        objCur = objCur->next;
    }
	return *this;
}

/*
averageColor: computers the average color of the container.
precondtion: valid container.
postcondition: finds the average color and sets the parameters as them.
*/
void Container::averageColor(int &averageRed, int &averageGreen, int &averageBlue)
{
    if (head == nullptr)
    {
        return;
    }
	int totalRed = 0;
	int totalBlue = 0;
	int totalGreen = 0;
    Node *cur;
    cur = head;
	int count = 0;
    while (cur != nullptr)
    {
        //get rgb
		//sum it to the ints
		totalRed += cur->p.red;
		totalBlue += cur->p.blue;
		totalGreen += cur->p.green;
        //add count
		count++;
		cur = cur->next;
    }
    //get average colors
	averageRed = totalRed / count;
	averageBlue = totalBlue / count;
	averageGreen = totalGreen / count;
    //transverse again
	cur = head;
	while (cur != nullptr)
	{
		//change colors;
		cur->p.red = averageRed;
		cur->p.blue = averageBlue;
		cur->p.green = averageGreen;
		cur = cur->next;
	}
}

/*
changeColor: changes the color on the ImageObj depending on the pixel locations,
within the container to the parameter colors.
precondition: container nodes contain valid coordinates on the ImageObj, valid int.
postcondition: changes pixels on the ImageObj that are within the container to the input parameter colors.
*/
void Container::changeColor(ImageObj &imageIn, int averageRed, int averageGreen, int averageBlue)
{
	Node *cur = head;
	while (cur != nullptr)
	{
		imageIn.SetRed(cur->row, cur->col, averageRed);
		imageIn.SetGreen(cur->row, cur->col, averageGreen);
		imageIn.SetBlue(cur->row, cur->col, averageBlue);
		cur = cur->next;
	}
}

/*
getContaingerInfo: gets the total pixels/length of the container.
precondition: valid container.
postcondition: cout total pixels, average red/green/blue of the container.
*/
void Container::getContainerInfo()
{
	if (head == nullptr)
	{
		return;
	}
	int totalRed = 0;
	int totalBlue = 0;
	int totalGreen = 0;
	Node *cur;
	cur = head;
	int count = 0;
	while (cur != nullptr)
	{
		//get rgb
		//sum it to the ints
		totalRed += cur->p.red;
		totalBlue += cur->p.blue;
		totalGreen += cur->p.green;
		//add count
		count++;
		cur = cur->next;
	}
	//get average colors
	int averageRed = totalRed / count;
	int averageBlue = totalBlue / count;
	int averageGreen = totalGreen / count;
	cout << "total pixels: " << count << endl;
	cout << "average red: " << averageRed << endl;
	cout << "average green: " << averageGreen << endl;
	cout << "average blue: " << averageBlue << endl;
}

/*
getSeed: returns the seed pixel aka first pixel of the container.
precondition: valid container that is not empty.
postcondition: returns first pixel or seed pixel.
*/
pixel Container::getSeed()
{
	return head->p;
}

/*
isEmpty: returns boolean depending on if the  container is empty.
precondition: valid container.
postcondition: returns boolean depending on if the container is empty or not.
*/
bool Container::isEmpty()
{
	if (head == nullptr)
	{
		return true;
	}
	return false;
}
