/*
driver.cpp
Author: Michael Ji
Description: Contains the main function to segment an image.
Contains the segment function to find seed pixels and the recursion function.
Reads in a gif and segments it then outputs it.
Prints total number of segments, pixels, and average colors
*/

#include "Container.h"
#include "ImageLib.h"
#include"ImageObj.h"
#include <iostream>
#include <cmath>
using namespace std;

//forward declarations
void findSeed(ImageObj &imageIn, ImageObj &seedImage);
void segment(ImageObj &imageIn, ImageObj &seedImage, Container &group, int pRow, int pCol);

/*
main: reads in a gif, segments it, outputs it.
precondition: valid gif.
postcondition: gif that has been segmented and printed text on console.
*/
int main()
{
	ImageObj image1 = ImageObj("input.gif");
	ImageObj image2(image1);
	findSeed(image1, image2);
	image1.Output();
	system("pause");
}

// *output to the console the total number of segments found (don’t include the big merged group)
// *the number of pixels in the merged group
// *average color of this merged group.

/*
findSeed: takes in an image, find seed pixels, segments image.
precondition: valid ImageObj.
postcondition: segments image, makes other image black, cout merged container data.
*/
void findSeed(ImageObj &imageIn, ImageObj &seedImage)
{
	int count = 0;
	Container mergedContainer;
	//loop and find not black seed
	for (int i = 0; i < imageIn.GetRows() - 1; i++)
	{
		for (int j = 0; j < imageIn.GetCols() - 1; j++)
		{
			// if pixel is black, return
			if ((seedImage.GetRed(i, j) == 0) && (seedImage.GetGreen(i, j) == 0) &&
				(seedImage.GetBlue(i, j) == 0))
			{
				//if i put a return here... segment ends, hence only 1 seed pixel
			}
			else
			{
				count++;
				Container group;
				segment(imageIn, seedImage, group, i, j);

				int newRed;
				int newGreen;
				int newBlue;
				//change container to averaged colors
				group.averageColor(newRed, newGreen, newBlue);
				//change image with averaged colors from container coordinates
				group.changeColor(imageIn, newRed, newGreen, newBlue);
				mergedContainer.merge(group);
			}
		}
	}
	//cout total containers count
	cout << "total segments: " << count << endl;
	//cout average color & number of pixels in merged container
	mergedContainer.getContainerInfo();
}

/*
segment: takes in a seed, checks conditions adds it to container, and recurses to find similar touching pixels
precondition: valid ImageObj, valid container, valid int.
postcondition: adds pixels similar to container, changes the other image to black if pixel is used.
*/
void segment(ImageObj &imageIn, ImageObj &seedImage, Container &group, int pRow, int pCol)
{
	//out of bounds, return
	if (pRow < 0 || pCol < 0 || pRow > imageIn.GetRows() - 1 || pCol > imageIn.GetCols() - 1)
	{
		return;
	}
	//if black, return
	if ((seedImage.GetRed(pRow, pCol) == 0) && (seedImage.GetBlue(pRow, pCol) == 0) && (seedImage.GetGreen(pRow, pCol) == 0))
	{
		return;
	}
	if (!group.isEmpty())
	{
		//abs(seed.red – p.red) + abs(seed.green – p.green) + abs(seed.blue – p.blue) < 100
		if (abs(group.getSeed().red - imageIn.GetRed(pRow, pCol)) + abs(group.getSeed().green - imageIn.GetGreen(pRow, pCol)) 
			+ abs(group.getSeed().blue - imageIn.GetBlue(pRow, pCol)) < 100)
		{
			//add pixel to group
			group.addPixel(imageIn.GetPixel(pRow, pCol), pRow, pCol);
			//mark pixel as black
			seedImage.SetBlue(pRow, pCol, 0);
			seedImage.SetGreen(pRow, pCol, 0);
			seedImage.SetRed(pRow, pCol, 0);
		}
		//if no else, it crashes... if >100, ends it
		else
		{
			return;
		}
	}
	if (group.isEmpty())
	{
		group.addPixel(imageIn.GetPixel(pRow, pCol), pRow, pCol);
		seedImage.SetBlue(pRow, pCol, 0);
		seedImage.SetGreen(pRow, pCol, 0);
		seedImage.SetRed(pRow, pCol, 0);
	}
	segment(imageIn, seedImage, group, pRow, pCol - 1);
	segment(imageIn, seedImage, group, pRow, pCol + 1);
	segment(imageIn, seedImage, group, pRow - 1, pCol);
	segment(imageIn, seedImage, group, pRow + 1, pCol);
}
