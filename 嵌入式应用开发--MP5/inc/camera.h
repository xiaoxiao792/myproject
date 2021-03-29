#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <stdio.h>
#include "jpeglib.h"
#include "yuyv.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <linux/input.h>
#include <pthread.h>

//函数声明
int camera();
void * func(void * arg );

#endif