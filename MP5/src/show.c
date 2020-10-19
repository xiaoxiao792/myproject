#include "show.h"

int welcome_show(){
	int x=0,y;
	bmp_show("welcome.bmp");
	touch(&x,&y);
	if(x!=0){
		func_show();
	}
	return 0;
}

int func_show(){
	int x=0,y;
	bmp_show("func.bmp");
	touch(&x,&y);
	if (x>188 && x<342 && y>108 && y<372)		
	{
		camera_show();
	}else if (x>358 && x<613)
	{
		if (y>108 && y<232)
		{
			music_show();
		}else if (y>248 && y<372)
		{
			video_show();
		}
	}
	return 0;
}

int camera_show(){
	bmp_show("photo.bmp");
	sleep(1);
	camera();
	return 0;
}

int music_show(){
	bmp_show("music.bmp");
	music();
	return 0;
}

int video_show(){
	video();
	return 0;
}