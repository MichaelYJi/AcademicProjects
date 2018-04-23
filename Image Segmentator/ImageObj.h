/*
ImageObj.h
Author: Michael Ji
Description: Contains the declarations of functions to be used.
Reads in a gif file, copies, deallocates, and outputs an image.
Contains overloaded operators for the ImageObj object.
Contains getters and setters for the ImageObj object.
Contains image modifers and a compare function.
Assumes you read in a valid gif.
*/
#pragma once
#include <string>
#include <iostream>
#include "ImageLib.h"
using namespace std;

class ImageObj
{

	/*
	operator <<: overloads operator to print out text for an ImageObj.
	Precondition: an ImageObj needs to be present.
	Postcondition: prints out dimensions of the ImageObj.
	*/
	friend ostream& operator<<(ostream&, const ImageObj&);

public:

	/*
	ImageObj(string fileName): makes a new ImageObj from a GIF file.
	Precondition: fileName is a file that has a GIF image.
	Postcondition: creates an ImageObj containing a picture.
	*/
	ImageObj(string fileName);

	/*
	ImageObj(int rowIn, int colIn): makes a new ImageObj with desired dimensions.
	Precondition: row and column number you want for your new image.
	Postcondition: creates an ImageObj with picture being your desired length and width.
	*/
	ImageObj(int rowIn, int colIn);

	/*
	ImageObj(const ImageObj & obj): makes a copy of the object.
	Precondition: obj is a valid ImageObj.
	Postcondition: creates an copy of obj.
	*/
	ImageObj(const ImageObj &obj);

	/*
	~ImageObj(): deconstructor for ImageObj.
	Precondition: none.
	Postcondition: deallocates the object.
	*/
	~ImageObj();

	/*
	GetRows: gets number of rows image has in the ImageObj
	Precondition: ImageObj contains an image
	Postcondition: returns the number of rows.
	*/
	int GetRows() const;

	/*
	GetCols: gets number of cols image has in the ImageObj
	Precondition: ImageObj contains an image
	Postcondition: returns the number of columns.
	*/
	int GetCols() const;

	/*
	GetBlue: gets the ImageObj's image's pixel's blue number.
	Precondition: put in valid dimensions.
	Postcondition: returns an int representing the pixel's blue number.
	*/
	int GetBlue(int x, int y) const;

	/*
	SetBlue: sets the ImageObj's image's pixel's blue number.
	Precondition: put in valid dimensions and blue number.
	Postcondition: sets the pixel's blue
	*/
	void SetBlue(int x, int y, int BlueIn);

	/*
	GetRed: gets the ImageObj's image's pixel's red number.
	Precondition: put in valid dimensions.
	Postcondition: returns an int representing the pixel's red number.
	*/
	int GetRed(int x, int y) const;

	/*
	SetRed: sets the ImageObj's image's pixel's red number.
	Precondition: put in valid dimensions and red number.
	Postcondition: sets the pixel's red number.
	*/
	void SetRed(int x, int y, int RedIn);

	/*
	GetGreen: gets the ImageObj's image's pixel's green number.
	Precondition: put in valid dimensions.
	Postcondition: returns an int representing the pixel's green number.
	*/
	int GetGreen(int x, int y) const;

	/*
	GetGreen: gets the ImageObj's image's pixel's green number.
	Precondition: put in valid dimensions.
	Postcondition: returns an int representing the pixel's green number.
	*/
	void SetGreen(int x, int y, int GreenIn);

	/*
	GetPixel: gets the ImageObj's image's pixel's.
	Precondition: put in valid dimensions.
	Postcondition: returns a pixel of the specified dimensions.
	*/
	pixel GetPixel(int x, int y) const;

	/*
	SetPixel: sets the ImageObj's image's pixel at specified pixel.
	Precondition: put in valid dimensions and pixel.
	Postcondition: sets a pixel at the specified location.
	*/
	void SetPixel(int x, int y, pixel in);

	/*
	Output: outputs the current object's image out as a gif.
	Precondition: filename is valid filename to store a GIF image. Valid image in the object.
	Postcondition: creates a GIF of the objects image under the name of output.gif.
	*/
	void Output() const;

	/*
	operator==: overloaded operator for comparing equality between two ImageObj
	Precondition: two valid ImageObj with valid images.
	Postcondition: returns a boolean if the objects are equal or not.
	*/
	bool operator==(const ImageObj &obj) const;

	/*
	operator!=: overloaded operator for comparing inequality between two ImageObj
	Precondition: two valid ImageObj with valid images.
	Postcondition: returns a boolean if the objects are inequal or not.
	*/
	bool operator!=(const ImageObj &obj) const;

	/*
	operator=: makes this equal to obj
	Precondition: use two valid ImageObj.
	Postcondition: returns an object, this is equal to the obj as a deep copy.
	*/
	ImageObj & operator=(ImageObj &obj);

	/*
	Mirror: mirrors the image.
	Precondition: valid ImageObj contain valid image.
	Postcondition: returns an object with the mirrored image.
	*/
	ImageObj Mirror();

	/*
	PhotoNeg: photonegates the image.
	Precondition: valid ImageObj with a valid image.
	Postcondition: returns an ImageObj that is a photonegative.
	*/
	ImageObj PhotoNeg();

	///*
	//Color: modifies the red and blue of the ImageObj's image.
	//Precondition: ImageObj with valid image.
	//Postcondition: returns an ImageObj with the image's red and blue modified.
	//*/
	//   ImageObj Color() const;

	/*
	Compare: compares the number of differences between two pixels.
	Precondition: Use two valid ImageObj with valid images.
	Postcondition: returns an int representing the number of different pixels.
	*/
	int Compare(ImageObj obj) const;

private:
	image picture;

};

