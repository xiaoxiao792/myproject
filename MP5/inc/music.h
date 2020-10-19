#ifndef _MUSIC_H_
#define _MUSIC_H_

#include  <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int music();
int send_cmd( int fd , char * cmd  );

#endif