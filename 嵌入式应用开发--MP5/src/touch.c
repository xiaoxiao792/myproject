#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int touch(int * x , int * y)
{
	int cont = 0 ;
	printf("%s__%d\n", __FUNCTION__ , __LINE__ );
	// 1.  打开触摸屏的设备文件/dev/input/event0
	//        open()
	int fd_ts = open("/dev/input/event0", O_RDWR);
	if (-1 == fd_ts)
	{
		perror("open /dev/input/event0 error");
		return -1 ;
	}
	// 2.  读取文件内容
	//        read()
	//          int     a       ;
	
	struct input_event ts_event ;

	while(1)
	{	
		read(fd_ts, &ts_event, sizeof(struct input_event));
		
		
		// 3.  分析数据
		if (EV_ABS == ts_event.type)
		{
			if (ABS_X == ts_event.code)
			{
				*x = ts_event.value;
				cont ++ ;
			}
			else if (ABS_Y == ts_event.code)
			{
				*y = ts_event.value;
				cont ++ ;
			}
		}  
		// 4.  为所欲为
		// printf("Time:%d:%d \t Type:%d \t Code:%d \t Value:%d \n",
		// 		ts_event.time.tv_sec ,
		// 		ts_event.time.tv_usec ,
		// 		ts_event.type,
		// 		ts_event.code,
		// 		ts_event.value); 
		if (cont == 2)
		{
			printf("%s---%d(%d,%d)\n",__FUNCTION__, __LINE__ ,*x, *y);
			cont = 0 ;
			break ;
		}
		
	}
	// 5.  关闭文件
	//       close()
	close(fd_ts);


	return 0;
}