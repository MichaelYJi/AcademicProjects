/*
Michael Ji
CSS 342
Program 3
Fractal: Takes in a gif and makes it into a fractal using Recursion.
*/

#include "Rectangle.h"
#include "ImageLib.h"
#include "ImageObj.h"
#include <iostream>
using namespace std;

//forward declarations

/*
recurse: makes a fractal image
precondition: valid original image, holder is same image, rec is dimensions of original.
postcondition: fractal image is output.gif
*/
ImageObj recurse(ImageObj &original, Rectangle &r);

/*
recurse: makes a fractal image
precondition: valid original image, holder is same image, rec is dimensions of original.
postcondition: fractal image is output.gif
*/
void recurse(ImageObj & original, ImageObj &holder, Rectangle rec)
{
	//base case
	if (rec.getX2() - rec.getX1() <= 1 && rec.getY2() - rec.getY1() <= 1) return;

	int halfWidth = (rec.getX2() - rec.getX1()) / 2;
	int halfHeight = (rec.getY2() - rec.getY1()) / 2;

	//make sub rectanges
	Rectangle rec1 = Rectangle(); //top left
	rec1.setX1(rec.getX1());
	rec1.setY1(rec.getY1());
	rec1.setX2(rec.getX1() + halfWidth);
	rec1.setY2(rec.getY1() + halfHeight);

	Rectangle rec2 = Rectangle(); //bot right
	rec2.setX1(rec.getX1() + halfWidth);
	rec2.setY1(rec.getY1() + halfHeight);
	rec2.setX2(rec.getX2());
	rec2.setY2(rec.getY2());

	Rectangle rec3 = Rectangle(); //bot left
	rec3.setX1(rec.getX1());
	rec3.setY1(rec.getY1() + halfHeight);
	rec3.setX2(rec.getX2() - halfWidth);
	rec3.setY2(rec.getY2());

	Rectangle rec4 = Rectangle(); // top right
	rec4.setX1(rec.getX1() + halfWidth);
	rec4.setY1(rec.getY1());
	rec4.setX2(rec.getX2());
	rec4.setY2(rec.getY2() - halfHeight);

	//shrunken pixels reading from holder
	for (int x = rec1.getX1(); x < rec1.getX2(); x++)
	{
		for (int y = rec1.getY1(); y < rec1.getY2(); y++)
		{
			pixel p1 = holder.GetPixel(2 * (x - rec1.getX1()), 2 * (y - rec1.getY1()));
			pixel p2 = holder.GetPixel(2 * (x - rec1.getX1()) + 1, 2 * (y - rec1.getY1()));
			pixel p3 = holder.GetPixel(2 * (x - rec1.getX1()), 2 * (y - rec1.getY1()) + 1);
			pixel p4 = holder.GetPixel(2 * (x - rec1.getX1()) + 1, 2 * (y - rec1.getY1()) + 1);

			original.SetBlue(x, y, (p1.blue + p2.blue + p3.blue + p4.blue) / 4);
			original.SetRed(x, y, (p1.red + p2.red + p3.red + p4.red) / 4);
			original.SetGreen(x, y, (p1.green + p2.green + p3.green + p4.green) / 4);
		}
	}

	//reading from original shrunken and flipped
	for (int x = rec1.getX1(); x < rec1.getX2(); x++)
	{
		for (int y = rec1.getY1(); y < rec1.getY2(); y++)
		{
			pixel p1 = original.GetPixel(x, y);
			original.SetPixel(rec2.getX2() - 1 - x + rec1.getX1(), rec2.getY2() - 1 - y + rec1.getY1(), p1);

		}
	}

	//shrink the holder
	ImageObj newHolder = ImageObj(holder);
	for (int x = 0; x < (rec.getX2() - rec.getX1() + 1) / 2; x++)
	{
		for (int y = 0; y < (rec.getY2() - rec.getY1() + 1) / 2; y++)
		{
			pixel p1 = newHolder.GetPixel(2 * x, 2 * y);
			pixel p2 = newHolder.GetPixel(2 * x + 1, 2 * y);
			pixel p3 = newHolder.GetPixel(2 * x, 2 * y + 1);
			pixel p4 = newHolder.GetPixel(2 * x + 1, 2 * y + 1);

			newHolder.SetBlue(x, y, (p1.blue + p2.blue + p3.blue + p4.blue) / 4);
			newHolder.SetRed(x, y, (p1.red + p2.red + p3.red + p4.red) / 4);
			newHolder.SetGreen(x, y, (p1.green + p2.green + p3.green + p4.green) / 4);
		}
	}

	recurse(original, newHolder, rec3);
	recurse(original, newHolder, rec4);

}

/*
main: main function to run program.
precondition: test.gif is valid gif image
postcondition: makes output.gif fractral
*/
int main()
{
	ImageObj image = ImageObj("input.gif");

	Rectangle rec = Rectangle();
	rec.setX1(0);
	rec.setY1(0);
	rec.setX2(image.GetRows());
	rec.setY2(image.GetCols());

	ImageObj holder = ImageObj(image);
	recurse(image, holder, rec);

	image.Output();
	system("PAUSE");
	return 0;

}