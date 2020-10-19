#ifndef _VIDEO_H_
#define _VIDEO_H_

#include  <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int video();
int send_cmd2( int fd , char * cmd  );

#endif