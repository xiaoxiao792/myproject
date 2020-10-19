#ifndef _BMP_H_
#define _BMP_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define   H 		480 
#define   W		  	800
#define   BMP_SIZE	H*W*3 
#define   LCD_SIZE	H*W*4 

//函数声明
int bmp_show( char * Path_Name);

#endif