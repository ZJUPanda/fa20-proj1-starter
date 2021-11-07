/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *color = (Color *) malloc(sizeof(Color));
	Color *p = image->image[row*image->cols + col];
	color->R = p->R;
	color->G = p->G;
	color->B = p->B;
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	uint32_t rows = image->rows;
	uint32_t cols = image->cols;
	Image *new_image = (Image *)malloc(sizeof(Image));
	new_image->image = (Color **) malloc(sizeof(Color) * rows * cols); 

	new_image->rows = rows;
	new_image->cols = cols;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++) {
			Color *p = evaluateOnePixel(image, i, j);
			int new_val = (p->B & 1) ? (uint8_t)255 : (uint8_t)0;
			p->B = new_val;
			p->G = new_val;
			p->R = new_val;
			new_image->image[i*cols + j] = p;
		}
	}
	return new_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	Image *image = readData(argv[1]);
	Image *new_image = steganography(image);
	freeImage(image);
	writeData(new_image);
	freeImage(new_image);
	return 0;
}
