#include "bmp.h"

int bmp_show( char * Path_Name)
{
	//打开文件
	int fd_lcd = open("/dev/fb0", O_RDWR);
	if (-1 == fd_lcd)
	{
		perror("open lcd error");
		return -1 ;
	}
	//内存映射
	int *p_lcd = (int *)mmap(NULL, LCD_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd , 0);
	if (MAP_FAILED == p_lcd)
	{
		perror("mmap error");
		return -1 ;
	}

	//打开图片文件
	int fd_bmp = open(Path_Name, O_RDWR);
	if (-1 == fd_bmp)
	{
		perror("open bmp error");
		return -1 ;
	}

	//文件读写位置偏移
	lseek(fd_bmp, 54 , SEEK_SET );
	
	//读取图片内容
	char buf_bmp [ BMP_SIZE ];
	int ret = read(fd_bmp, buf_bmp , BMP_SIZE);
	printf("read : %d \n",  ret  );


	//处理图片的数据 24 BGR --> 32  ARGB
	int buf_lcd [480][800];
	int x , y;

	for (y = 0; y < H; y++) 
	{
		for (x = 0; x < W; x++)
		{
			buf_lcd[479 - y][x]  =  	buf_bmp[(x + y * 800)*3 + 0] << 0 |
										buf_bmp[(x + y * 800)*3 + 1] << 8 |
										buf_bmp[(x + y * 800)*3 + 2] << 16 ;
		}
	}

	//写入内容
	for (y = 0; y < H; y++) 
	{
		for (x = 0; x < W; x++)
		{
			*(p_lcd+x+y*800) = buf_lcd[y][x] ;
		}
	}
	
	//关闭文件
	close(fd_lcd);
	close(fd_bmp);

	munmap(p_lcd , LCD_SIZE);

	return 0;
}