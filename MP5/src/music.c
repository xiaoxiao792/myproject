#include "music.h"

int music()
{
	int x,y;
	int ret ;
	//   & 在shell命令中表示该命令在后台执行
	system("mplayer  -quiet -slave -input file=/tmp/TieDan 1.mp3 &");
	printf("MUSIC PLAY !\n");

	//判断管道文件是否存在
	if(access("/tmp/TieDan", F_OK))
	{
		//如果不存在则创建
		ret = mkfifo("/tmp/TieDan", 0666);
		if (ret == -1 )
		{
			perror("mkfifo error ");
			return -1 ;
		}

	}

	//打开管道文件
	int fd_fifo = open("/tmp/TieDan", O_RDWR);
	if (-1 == fd_fifo)
	{
		perror("open fifo error ");
		return -1 ;
	}

	while(1)
	{
		touch(&x,&y);
		  
		  if (x>0 && x<200)
		  {
		   //返回
		   if (y>0 && y<240)
		   {
		    system("killall -SIGKILL mplayer");
		    return 0;
		   }
		   //快退
		   else if (y>240 && y<480)
		   {
		    send_cmd2(fd_fifo , "seek -5\n" );
		   }
		  }
		  else if (x>200 && x<600)
		  {
		   if (y>0 && y<240)
		   {
		    if (x>200 && x<400)
		    {
		     //音量减
		     send_cmd2(fd_fifo , "volume -5\n" );
		    }
		    else if (x>400 && x<600)
		    {
		     //音量加
		     send_cmd2(fd_fifo , "volume +5\n" );
		    }
		   }
		   else if (y>240 && y<480)
		   {
		    //暂停
		    send_cmd2(fd_fifo , "pause\n" );
		   }
		    
		  }
		  else if (x>600 && x<800)
		  {
		   //快进
		   send_cmd2(fd_fifo , "seek +5\n" );
		  }

		  
	}

	return 0;
}

int send_cmd( int fd , char * cmd  )
{

	write(fd , cmd , strlen(cmd) );

	return 0 ;
}