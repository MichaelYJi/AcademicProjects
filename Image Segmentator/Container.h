/*
Container.h
Author: Michael Ji
Description: Contains the declarations of functions to be used for the container class
Purpose of the container class is to hold a linked list of pixels and its coordinates.
The container is supposed to contain pixels/coordinates of a pixel similar to the first/seed pixel.
Contains bool for equality and inequality between containers.
Contains functions to add pixels to a container and check if the container is empty.
Can get seed pixel. Can merge containers together. Can change colors of the pixels in the container.
*/

#pragma once
#include "ImageLib.h"
#include"ImageObj.h"
#include <iostream>

/*
Container: purpose of this class is to hold nodes containing pixel, int row, int col, next pointer, and head pointer.
We are to manipulate what goes in the container. Check for equality, and find average colors.
*/
class Container
{
public:
	/*
	Container: default constructor.
	precondtion: none.
	postcondition: creates empty container.
	*/
	Container();

	/*
	~Container: destructs the container.
	precondtion: none.
	postcondition: deletes all nodes and sets their pointers to null, with head being null.
	*/
	~Container();

	/*
	Container: constructs a container with following data as the first node.
	precondtion: valid pixel and int.
	postcondition: creates a container with the first node containing the data entered.
	*/
	Container(const pixel seed, const int row, const int col);
	
	/*
	container: copy constructor that copies obj over to this.
	precondtion: valid obj container.
	postcondition: deep copies obj over onto this.
	*/
	Container(const Container &obj);
	
	/*
	operator==: boolean to check equality.
	precondition: two valid containers.
	postcondition: returns boolean depending on if they are equal or not
	*/
	bool operator==(const Container &obj) const;
	
	/*
	operator!=: boolean to check inequality.
	precondition: two valid containers.
	postcondition: returns boolean opposite of ==.
	*/
	bool operator!=(const Container &obj) const;
	
	/*
	operator=: sets this container equal to obj.
	precondition: valid this container and obj container.
	postcondition: returns this container as equal to obj container.
	*/
	Container operator=(const Container &obj);

	/*
	addPixel: adds pixel and coordinates to the container.
	precondition: valid container, pixel, ints.
	postcondition: creates a new node and adds it to the end of the container with the data.
	*/
	void addPixel(const pixel p, const int rowIn, const int colIn);
	
	/*
	merge: merges the obj container on to this container.
	precondition: two valid containers.
	postcondition: returns this container with obj container deep copied onto its end.
	*/
	Container merge(const Container &obj);
	
	/*
	averageColor: computers the average color of the container.
	precondtion: valid container.
	postcondition: finds the average color and sets the parameters as them.
	*/
	void averageColor(int &averageRed, int &averageGreen, int &averageBlue);
	
	/*
	changeColor: changes the color on the ImageObj depending on the pixel locations,
		within the container to the parameter colors.
	precondition: container nodes contain valid coordinates on the ImageObj, valid int.
	postcondition: changes pixels on the ImageObj that are within the container to the input parameter colors.
	*/
	void changeColor(ImageObj &imageIn, int averageRed, int averageGreen, int averageBlue);
	
	/*
	getContaingerInfo: gets the total pixels/length of the container.
	precondition: valid container.
	postcondition: cout total pixels, average red/green/blue of the container.
	*/
	void getContainerInfo();

	/*
	getSeed: returns the seed pixel aka first pixel of the container.
	precondition: valid container that is not empty.
	postcondition: returns first pixel or seed pixel.
	*/
	pixel getSeed();

	/*
	isEmpty: returns boolean depending on if the  container is empty.
	precondition: valid container.
	postcondition: returns boolean depending on if the container is empty or not.
	*/
	bool isEmpty();

private:
	/*
	Node: contains pixel, row, col, next pointer, and head node pointer
	*/
	struct Node
	{
		pixel p;
		int row;
		int col;
		Node *next;
	};
	Node *head; 
};

