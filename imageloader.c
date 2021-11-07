/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	Image *IG = (Image *)malloc(sizeof(Image));
	FILE *fp;
	if((fp = fopen(filename, "r")) == NULL) {
		printf("File open error!\n");
		exit(0);
	}
	char head[3];
	fscanf(fp, "%s ", head);
	int rows, cols;
	int scale;
	fscanf(fp, "%d %d ", &cols, &rows);
	fscanf(fp, "%d ", &scale);
	IG->cols = cols;
	IG->rows = rows;
	IG->image = (Color **) malloc(sizeof(Color*) * rows * cols); 
	for(int i=0; i<rows; i++) {
		for(int j=0; j<cols; j++) {
			IG->image[i*cols + j] = (Color *) malloc(sizeof(Color));
			int red, green, blue;
			fscanf(fp, "%d %d %d ", &red, &green, &blue);
			IG->image[i*cols + j]->R = red;
			IG->image[i*cols + j]->G = green;
			IG->image[i*cols + j]->B = blue;
		}
	}

	fclose(fp);
	return IG;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	int rows = image->rows;
	int cols = image->cols;
	printf("P3\n");
	printf("%d %d\n%d\n", cols, rows, 255);
	Color *p;
	for(int i=0; i<image->rows; i++) {
		for(int j=0; j<cols-1; j++) {
			p = image->image[i*cols + j];
			printf("%3d %3d %3d   ", p->R, p->G, p->B);
		}
		p = image->image[i*cols + cols -1];
		printf("%3d %3d %3d\n", p->R, p->G, p->B);
	}
	// printf("\n");
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	// step 1: free each Colors
	int rows = image->rows;
	int cols = image->cols;
	for(int i=0; i<rows; i++) {
		for(int j=0; j<cols; j++) {
			free(image->image[i*cols + j]);
		}
	}
	free(image->image);
	// step 2: free Image
	free(image);
}