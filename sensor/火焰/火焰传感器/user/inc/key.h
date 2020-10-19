#ifndef  _KEY_H_
#define  _KEY_H_


#define   KEY_UP    4
#define   KEY_DOWN  2
#define   KEY_LEFT  1
#define   KEY_RIGHT 3


#define  KEY0   (GPIOE->IDR &(1<<4))
#define  KEY1   (GPIOE->IDR &(1<<3))
#define  KEY2   (GPIOE->IDR &(1<<2))
#define  WK_UP  (GPIOA->IDR &(1<<0))
void key_init(void);
int key_scan(void);

#endif


