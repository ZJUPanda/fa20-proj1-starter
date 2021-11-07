/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color * color = (Color *)malloc(sizeof(Color));
	int dr[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
	int dc[8] = {-1,  0,  1, -1, 1, -1, 0, 1};
	uint32_t rows = image->rows;
	uint32_t cols = image->cols;
	
	color->R = 0;
	color->G = 0;
	color->B = 0;
	for(int k = 1, j=0; k<=0x80; k <<= 1, j++) {
		int onesR = 0;
		int onesG = 0;
		int onesB = 0;
		for(int i=0; i<8; i++) {
			int newRow = (rows + row + dr[i]) % rows;
			int newCol = (cols + col + dc[i]) % cols;
			if((image->image[newRow*cols + newCol]->R) & k) {
				onesR++;
			}
			if((image->image[newRow*cols + newCol]->G) & k) {
				onesG++;
			}
			if((image->image[newRow*cols + newCol]->B) & k) {
				onesB++;
			}
		}


		if((image->image[row*cols + col]->R) & k ) { 
			color->R |= (( rule>>(9+onesR) ) & 1) << j;
		} // alive
		else { 
			color->R |= (( rule>>(onesR) ) & 1) << j;
		} // dead

		if((image->image[row*cols + col]->G) & k ) { 
			color->G |= (( rule>>(9+onesG) ) & 1) << j;
		} // alive
		else { 
			color->G |= (( rule>>(onesG) ) & 1) << j;
		} // dead

		if((image->image[row*cols + col]->B) & k ) { 
			color->B |= (( rule>>(9+onesB) ) & 1) << j;
		} // alive
		else { 
			color->B |= (( rule>>(onesB) ) & 1) << j;
		} // dead

	}
	return color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	uint32_t rows = image->rows;
	uint32_t cols = image->cols;
	Image *new_image = (Image *)malloc(sizeof(Image));
	new_image->image = (Color **) malloc(sizeof(Color*) * rows * cols); 

	new_image->rows = rows;
	new_image->cols = cols;

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++) {
			new_image->image[i*cols + j] = evaluateOneCell(image, i, j, rule);
		}
	}
	return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 3) {
		printf("usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with maximum value 255.\nrule is a hex number beginning with 0x; Life is 0x1808.");
		return 1;
	}
	Image *img = readData(argv[1]);
	uint32_t rule = strtol(argv[2], NULL, 16);
	Image *nextImg = life(img, rule);
	writeData(nextImg);
	freeImage(img);
	freeImage(nextImg);
	return 0;
}
