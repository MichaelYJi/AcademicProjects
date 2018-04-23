#include "Rectangle.h"
#include "ImageLib.h"
#include <iostream>
#include <string>
using namespace std;

/*
Rectangle(): overloaded operator for comparing equality between two rectangles
Precondition: none
Postcondition: creates new rectangle object.
*/
Rectangle::Rectangle()
{
}

/*
~Rectangle: default destructor
Precondition: valid rectangle.
Postcondition: destructs object.
*/
Rectangle::~Rectangle()
{
}

/*
operator <<: overloads operator to print out text for a rectangle.
Precondition: an rectangle needs to be present.
Postcondition: prints out dimensions of the rectangle.
*/
ostream & operator<<(ostream &text, const Rectangle &recIn)
{
	text << "start X: " << recIn.getX1() << " , start Y: " << recIn.getY1() <<
		" , end X: " << recIn.getX2() << ", end Y: " << recIn.getY2();
	return text;

}

/*
operator==: overloaded operator for comparing equality between two rectangles
Precondition: needs two rectangles.
Postcondition: returns a boolean if the objects are equal or not.
*/
bool Rectangle::operator==(const Rectangle & obj) const
{
	if (this->getX1() == obj.getX1() && this->getY1() == obj.getY1() &&
		this->getX2() == obj.getX2() && this->getY2() == obj.getY2())
	{
		return true;
	}
	return false;
}

/*
operator!=: overloaded operator for comparing inequality between two rectangles
Precondition:
Postcondition: returns a boolean if the objects are inequal or not.
*/
bool Rectangle::operator!=(const Rectangle & obj) const
{
	return !(*this == obj);
}

/*
getX1: returns x1 of the rectangle.
precondition: rectangle has valid x1 value.
postcondition: returns an int of x1.
*/
int Rectangle::getX1() const
{
	return X1;
}

/*
setX1: sets x1 value of rectangle.
precondition: rectangle needs to exist, valid x1 int input.
postcondition: sets x1 value to corresponding int.
*/
void Rectangle::setX1(int startRowIn)
{
	X1 = startRowIn;
}

/*
getY1: returns Y1 of the rectangle.
precondition: rectangle has valid Y1 value.
postcondition: returns an int of Y1.
*/
int Rectangle::getY1() const
{
	return Y1;
}

/*
setY1: sets Y1 value of rectangle.
precondition: rectangle needs to exist, valid Y1 int input.
postcondition: sets Y1 value to corresponding int.
*/
void Rectangle::setY1(int startColIn)
{
	Y1 = startColIn;
}

/*
getX1: returns x2 of the rectangle.
precondition: rectangle has valid x2 value.
postcondition: returns an int of x2.
*/
int Rectangle::getX2() const
{
	return X2;
}

/*
setX1: sets x2 value of rectangle.
precondition: rectangle needs to exist, valid x2 int input.
postcondition: sets x2 value to corresponding int.
*/
void Rectangle::setX2(int endRowIn)
{
	X2 = endRowIn;
}

/*
getY1: returns Y2 of the rectangle.
precondition: rectangle has valid Y2 value.
postcondition: returns an int of Y2.
*/
int Rectangle::getY2() const
{
	return Y2;
}

/*
setY1: sets Y2 value of rectangle.
precondition: rectangle needs to exist, valid Y2 int input.
postcondition: sets Y2 value to corresponding int.
*/
void Rectangle::setY2(int endColIn)
{
	Y2 = endColIn;
}
