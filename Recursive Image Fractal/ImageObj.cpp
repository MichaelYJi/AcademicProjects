/*
ImageObj.cpp
Author: Michael Ji
Description: Contains the detailed functions from the ImageObj.h file
Reads in a gif file, copies, deallocates, and outputs an image.
Contains overloaded operators for the ImageObj object.
Contains getters and setters for the ImageObj object.
Contains image modifers and a compare function.
Assumes you read in a valid gif.
*/

#include "ImageObj.h"
#include "ImageLib.h"
#include <iostream>
#include <string>
using namespace std;

/*
ImageObj(string fileName): makes a new ImageObj from a GIF file.
Precondition: fileName is a file that has a GIF image.
Postcondition: creates an ImageObj containing a picture.
*/
ImageObj::ImageObj(string fileName)
{
	picture = ReadGIF(fileName);
}

/*
ImageObj(int rowIn, int colIn): makes a new ImageObj with desired dimensions.
Precondition: row and column number you want for your new image.
Postcondition: creates an ImageObj with picture being your desired length and width.
*/
ImageObj::ImageObj(int rowIn, int colIn)
{
	picture = CreateImage(rowIn, colIn);
}

/*
ImageObj(const ImageObj & obj): makes a copy of the object.
Precondition: obj is a valid ImageObj.
Postcondition: creates an copy of obj.
*/
ImageObj::ImageObj(const ImageObj & obj)
{
	picture = CopyImage(obj.picture);
}

/*
~ImageObj(): deconstructor for ImageObj.
Precondition: none.
Postcondition: deallocates the object.
*/
ImageObj::~ImageObj()
{
	DeallocateImage(picture);
}

/*
operator <<: overloads operator to print out text for an ImageObj.
Precondition: an ImageObj needs to be present.
Postcondition: prints out dimensions of the ImageObj.
*/
ostream & operator<<(ostream &text, const ImageObj &objIn)
{
	text << "rows: " << objIn.GetRows() << " " << "cols: " << objIn.GetCols() << endl;
	return text;
}

/*
GetRows: gets number of rows image has in the ImageObj
Precondition: ImageObj contains an image
Postcondition: returns the number of rows.
*/
int ImageObj::GetRows() const
{
	return picture.rows;
}

/*
GetCols: gets number of cols image has in the ImageObj
Precondition: ImageObj contains an image
Postcondition: returns the number of columns.
*/
int ImageObj::GetCols() const
{
	return picture.cols;
}

/*
GetBlue: gets the ImageObj's image's pixel's blue number.
Precondition: put in valid dimensions.
Postcondition: returns an int representing the pixel's blue number.
*/
int ImageObj::GetBlue(int x, int y) const
{
	if (x < 0 || y < 0)
	{
		return -1;
	}
	if (x > GetRows() || y > GetCols())
	{
		return -1;
	}
	return picture.pixels[x][y].blue;
}

/*
SetBlue: sets the ImageObj's image's pixel's blue number.
Precondition: put in valid dimensions and blue number.
Postcondition: sets the pixel's blue
*/
void ImageObj::SetBlue(int x, int y, int BlueIn)
{
	picture.pixels[x][y].blue = BlueIn;
}

/*
GetRed: gets the ImageObj's image's pixel's red number.
Precondition: put in valid dimensions.
Postcondition: returns an int representing the pixel's red number.
*/
int ImageObj::GetRed(int x, int y) const
{
	if (x < 0 || y < 0)
	{
		return -1;
	}
	if (x > GetRows() || y > GetCols())
	{
		return -1;
	}
	return picture.pixels[x][y].red;
}

/*
SetRed: sets the ImageObj's image's pixel's red number.
Precondition: put in valid dimensions and red number.
Postcondition: sets the pixel's red number.
*/
void ImageObj::SetRed(int x, int y, int RedIn)
{
	picture.pixels[x][y].red = RedIn;
}

/*
GetGreen: gets the ImageObj's image's pixel's green number.
Precondition: put in valid dimensions.
Postcondition: returns an int representing the pixel's green number.
*/
int ImageObj::GetGreen(int x, int y) const
{
	if (x < 0 || y < 0)
	{
		return -1;
	}
	if (x > GetRows() || y > GetCols())
	{
		return -1;
	}
	return picture.pixels[x][y].green;
}

/*
GetGreen: gets the ImageObj's image's pixel's green number.
Precondition: put in valid dimensions.
Postcondition: returns an int representing the pixel's green number.
*/
void ImageObj::SetGreen(int x, int y, int GreenIn)
{
	picture.pixels[x][y].green = GreenIn;
}

/*
GetPixel: gets the ImageObj's image's pixel's.
Precondition: put in valid dimensions.
Postcondition: returns a pixel of the specified dimensions.
*/
pixel ImageObj::GetPixel(int x, int y) const
{
	return picture.pixels[x][y];
}

/*
SetPixel: sets the ImageObj's image's pixel at specified pixel.
Precondition: put in valid dimensions and pixel.
Postcondition: sets a pixel at the specified location.
*/
void ImageObj::SetPixel(int x, int y, pixel in)
{
	picture.pixels[x][y] = in;
}

/*
Output: outputs the current object's image out as a gif.
Precondition: filename is valid filename to store a GIF image. Valid image in the object.
Postcondition: creates a GIF of the objects image under the name of output.gif.
*/
void ImageObj::Output() const
{
	WriteGIF("output.gif", picture);
}

/*
operator==: overloaded operator for comparing equality between two ImageObj
Precondition: two valid ImageObj with valid images.
Postcondition: returns a boolean if the objects are equal or not.
*/
bool ImageObj::operator==(const ImageObj &obj) const
{
	if (picture.cols != obj.picture.cols || picture.cols != obj.picture.rows)
	{
		return false;
	}

	for (int row = 0; row < this->GetRows(); row++)
	{
		for (int col = 0; col < this->GetCols(); col++)
		{
			if (this->GetBlue(row, col) != obj.GetBlue(row, col) ||
				this->GetRed(row, col) != obj.GetRed(row, col) ||
				this->GetGreen(row, col) != obj.GetGreen(row, col))
			{
				return false;
			}
		}
	}
	return true;
}

/*
operator!=: overloaded operator for comparing inequality between two ImageObj
Precondition: two valid ImageObj with valid images.
Postcondition: returns a boolean if the objects are inequal or not.
*/
bool ImageObj::operator!=(const ImageObj &obj) const
{
	return !(*this == obj);
}

/*
operator=: makes this equal to obj
Precondition: use two valid ImageObj.
Postcondition: returns an object, this is equal to the obj as a deep copy.
*/
ImageObj & ImageObj::operator=(ImageObj &obj)
{
	if (*this != obj)
	{
		DeallocateImage(picture);
		picture = CopyImage(obj.picture);
		return *this;
	}
	return *this;
}

/*
Mirror: mirrors the image.
Precondition: valid ImageObj contain valid image.
Postcondition: returns an object with the mirrored image.
*/
ImageObj ImageObj::Mirror()
{
	for (int row = 0; row < GetRows(); row++)
	{
		for (int col = 0; col < (GetCols() / 2); col++)
		{
			pixel temp;
			temp = GetPixel(row, col);
			SetPixel(row, col, GetPixel(row, GetCols() - 1 - col));
			SetPixel(row, GetCols() - 1 - col, temp);
		}
	}
	return *this;
}

/*
PhotoNeg: photonegates the image.
Precondition: valid ImageObj with a valid image.
Postcondition: returns an ImageObj that is a photonegative.
*/
ImageObj ImageObj::PhotoNeg()
{
	for (int row = 0; row < GetRows(); row++)
	{
		for (int col = 0; col < GetCols(); col++)
		{
			SetBlue(row, col, 255 - GetBlue(row, col));
			SetRed(row, col, 255 - GetRed(row, col));
			SetGreen(row, col, 255 - GetGreen(row, col));
		}
	}
	return *this;
}

///*
//Color: modifies the red and blue of the ImageObj's image.
//Precondition: ImageObj with valid image.
//Postcondition: returns an ImageObj with the image's red and blue modified.
//*/
//ImageObj ImageObj::Color() const
//{
//	for (int row = 0; row < GetRows(); row++)
//	{
//		for (int col = 0; col < GetCols(); col++)
//		{
//
//			if (GetBlue(row, col) - (row % 7) < 0)
//			{
//				SetBlue(row, col, 0);
//			}
//			else
//				SetBlue(row, col, GetBlue(row, col) - (row % 7));
//
//			if (GetRed(row, col) + (col % 9) > 255)
//			{
//				SetRed(row, col, 255);
//			}
//			else
//				SetRed(row, col, GetRed(row, col) + (col % 9));
//		}
//	}
//	return *this;
//}

/*
Compare: compares the number of differences between two pixels.
Precondition: Use two valid ImageObj with valid images.
Postcondition: returns an int representing the number of different pixels.
*/
int ImageObj::Compare(ImageObj obj) const
{
	int differences = 0;
	if (*this == obj)
	{
		return differences;
	}

	for (int row = 0; row < GetRows(); row++)
	{
		for (int col = 0; col < GetCols(); col++)
		{
			if ((GetBlue(row, col) != obj.GetBlue(row, col)) ||
				(GetRed(row, col) != obj.GetRed(row, col)) ||
				(GetGreen(row, col) != obj.GetGreen(row, col)))
			{
				differences++;
			}
		}
	}
	return differences;
}
