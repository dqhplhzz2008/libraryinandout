/*DESIGNED BY LYRIC 2016.4.29于青岛*/
/*A9、图书馆出入人员计数器
1.设计任务
设计一个图书馆出入人员计数系统，要求利用2组红外发射接收对管组成模拟图书馆出入人员计数系统，使其能够模拟统计图书馆出入人员计数,
并使用数码管显示计数信息。
2.1 基本要求
(1) 任何一对红外管能够检测到有人走过，并将计数显示出来；
（2）当障碍物依次从红外发射管1到2走过的时候，人员数加1；
（3）在实现(2)的基础上，实现则有分，如果不能保证两个同时实现，则不加分。当障碍物依次从红外发射管2到1走过的时候，人员数减1；
2.2 发挥部分
（1）充分发挥两对红外对管的功能,实现当人员走到一半再返回,则计数不变功能；
（2）为保证系统稳定性，当人员从第1对红外发射管经过之后，直接从中间取出，不计数；当人员从中间直接经过第2个管子之后，
不计数；待再次从第1、2对红外管经过时，正常计数。*/
/*发光二极管，共阳接法**/
#include <reg51.h>
#define DIG_SHI P0	  //定义十位数码管的端口
#define DIG_GE P1	  //个位数码管的端口
unsigned char i=0;
unsigned char j=0;
unsigned char k=0;   // 定义计数变量
unsigned char q;
unsigned int a,b,c,d;
unsigned int num=15;//人数超过15时报警
sbit First=P3^2;
sbit Second=P3^3;
sbit fmq=P0^0;
/***定义P2端口**/
sbit red0=P2^0;	//入口的灯
sbit green0=P2^1;
sbit red1=P2^2;	  //数码管旁边的灯
sbit yellow1=P2^3;
sbit green1=P2^4;
sbit m=P2^5;//拨码开关1
sbit n=P2^6;//拨码开关2
sbit control=P2^7;//,拨码开关3，控制入口灯亮
 /*定义数码管显示0、1、2、3、4、5、6、7、8、9的数值 */
unsigned char code DIG_CODE[10] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6} ;
void chushihua();
void delays(int x);//定义延迟函数
/****定义显示函数******/
void display();//显示
/*********主函数********/
int main()
{ 
/*****报警值的设置程序***/
 while(m==0)
 {
 if (n!= 1)		//检测按键是否按下
	{
		delays(1);	//消除抖动

		if (n!= 1)	//再次检测按键是否按下
		{
		num++;
		delays(7);
		}
	}
 else if(control!=1)
 {
 	delays(1);	//消除抖动

		if (control!= 1)	//再次检测按键是否按下
		{
		if(num>=0)
		{
		num--;
		delays(1);
		}
		else num=0;
		delays(7);
		}
 }
 DIG_SHI=DIG_CODE[num% 100 / 10];
 DIG_GE=DIG_CODE[num%10];
 }
 chushihua();
 while(1)
 {
	EX1=1;
	EX0=1;
	k=i-j;
	display();
 }
}
/********************显示函数*******************************/
void display()
{
  
if(k<100)
	{ 
	/**显示总人数********/
	if(m==1&&n==1)
	{
     q=k;
     red1=0; //红灯亮
     yellow1=1;
     green1=1;
	}
	/**显示进入人数********/
	else if(m==0&&n==1)
	{
     q=i;
     red1=1; 
     yellow1=0;//黄灯亮
     green1=1;
	}
	/**显示出来人数********/
	else if(m==0&&n==0) 
	{
	 q=j;
	 red1=1; 
     yellow1=1;//绿灯亮
     green1=0;
	}
   else
	{
	  TR1=1; //开定时器
	  /**动态显示总人数********/
	  if(d%3==0) //5s一次变换，对3取余数，三次循环
      {
	   q=k;
       red1=0; //红灯亮
       yellow1=1;
       green1=1;
      }
	  else if(d%3==1)
      {
	   q=i;
       red1=1; 
       yellow1=0;//黄灯亮
       green1=1;
	  }
	  else
	  {
	  q=j;
	  red1=1; 
      yellow1=1;//绿灯亮
      green1=0;
	  }
	}
	/***********显示************/
		DIG_SHI=DIG_CODE[q% 100 / 10];
		DIG_GE=DIG_CODE[q%10];
	 if(control==1)		 //手动控制入口灯亮灭
	   {
		if(k<num)
		{
		fmq=1;
		red0=1;//入口红灯灭
		green0=0;//入口绿灯亮，可以通行
		}
		else
		{
		fmq=0;//蜂鸣器报警
		red0=0;//入口红灯亮
		green0=1;//入口绿灯灭，禁止通行
		}
		}
	else 
	   {
	    fmq=0;//蜂鸣器报警
		red0=0;//入口红灯亮
		green0=1;//入口绿灯灭，禁止通行
	   }
	}
       else if(k>=100)
	{
		fmq=0;
		DIG_SHI=0x8e;  //F
		DIG_GE=0x8e;//F	 	
	}
}
/********************初始化函数******************/
void chushihua()
{
    EA = 1;	    // 开总中断
	EX1=1;	  //允许外部中断1
	IT1=1;	 //打开外部中断1
	EX0=1;
	IT0=1;
	ET1=1;//允许定时器1中断
	DIG_SHI=DIG_CODE[0];
	DIG_GE=DIG_CODE[0];
	fmq=1;
   }
  /******************外部中断0First**************************/
void inter0() interrupt 0
{
	if((b==0)&&(a==0)&&(First==0))//人正常进入第一步
	{
		a+=1;
		if(a>1)
			a=0;
		EX0=0; 
	}
	if((b==1)&&(a==0)&&(First==0))//人正常出去第二步
	{
		j++;
		b=0;
		EX0=0;
	}
}
  /******************外部中断1Second**************************/
void inter1() interrupt 2
{
 	if((b==0)&&(a==0)&&(Second==0))//人正常出去第一步
	{
		b+=1;
		if(b>1)
		   b=0;
	EX1=0;
	}
	if((b==0)&&(a==1)&&(Second==0))//人正常进入第二步
	{
		i++;
		a=0;
		EX1=0;
	}
}	 
/*************定时器1中断****************/
 void Time1() interrupt 3
{  TH0=(65536-600)/256;		  //重新赋值 11.0592MHZ晶振计算，指令周期1.09uS，
   TL0=(65536-600)%256;//1mS，a每次加1的时间
   c++;	
   if(c==250) //5s一次
    { d++;
	  c=0;
	}
}
/********延迟函数**********/
void delays(int x)
{
	  int m,n;
	  for(m=30*x;m>0;m--)	//      x/10毫秒
	  	for(n=110;n>0;n--);	 
}
