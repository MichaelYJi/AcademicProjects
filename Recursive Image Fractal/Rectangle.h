#pragma once
#include <string>
#include <iostream>
#include "Rectangle.h"
using namespace std;

class Rectangle
{

	/*
	operator <<: overloads operator to print out text for an ImageObj.
	Precondition: an ImageObj needs to be present.
	Postcondition: prints out dimensions of the ImageObj.
	*/
	friend ostream& operator<<(ostream&, const Rectangle&);

public:
	/*
	Rectangle(): overloaded operator for comparing equality between two rectangles
	Precondition: none
	Postcondition: creates new rectangle object.
	*/
	Rectangle();

	/*
	~Rectangle: default destructor
	Precondition: valid rectangle.
	Postcondition: destructs object.
	*/
	~Rectangle();

	/*
	operator==: overloaded operator for comparing equality between two rectangles
	Precondition: needs two rectangles.
	Postcondition: returns a boolean if the objects are equal or not.
	*/
	bool operator==(const Rectangle &obj) const;

	/*
	operator!=: overloaded operator for comparing inequality between two rectangles
	Precondition:
	Postcondition: returns a boolean if the objects are inequal or not.
	*/
	bool operator!=(const Rectangle &obj) const;

	/*
	getX1: returns x1 of the rectangle.
	precondition: rectangle has valid x1 value.
	postcondition: returns an int of x1.
	*/
	int getX1() const;

	/*
	setX1: sets x1 value of rectangle.
	precondition: rectangle needs to exist, valid x1 int input.
	postcondition: sets x1 value to corresponding int.
	*/
	void setX1(int startRowIn);

	/*
	getY1: returns Y1 of the rectangle.
	precondition: rectangle has valid Y1 value.
	postcondition: returns an int of Y1.
	*/
	int getY1() const;

	/*
	setY1: sets Y1 value of rectangle.
	precondition: rectangle needs to exist, valid Y1 int input.
	postcondition: sets Y1 value to corresponding int.
	*/
	void setY1(int startColIn);

	/*
	getX1: returns x2 of the rectangle.
	precondition: rectangle has valid x2 value.
	postcondition: returns an int of x2.
	*/
	int getX2() const;

	/*
	setX1: sets x2 value of rectangle.
	precondition: rectangle needs to exist, valid x2 int input.
	postcondition: sets x2 value to corresponding int.
	*/
	void setX2(int endRowIn);

	/*
	getY1: returns Y2 of the rectangle.
	precondition: rectangle has valid Y2 value.
	postcondition: returns an int of Y2.
	*/
	int getY2() const;

	/*
	setY1: sets Y2 value of rectangle.
	precondition: rectangle needs to exist, valid Y2 int input.
	postcondition: sets Y2 value to corresponding int.
	*/
	void setY2(int endColIn);

private:
	int X1;
	int Y1;
	int X2;
	int Y2;
};
