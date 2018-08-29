/*DESIGNED BY LYRIC 2016.4.29���ൺ*/
/*A9��ͼ��ݳ�����Ա������
1.�������
���һ��ͼ��ݳ�����Ա����ϵͳ��Ҫ������2����ⷢ����նԹ����ģ��ͼ��ݳ�����Ա����ϵͳ��ʹ���ܹ�ģ��ͳ��ͼ��ݳ�����Ա����,
��ʹ���������ʾ������Ϣ��
2.1 ����Ҫ��
(1) �κ�һ�Ժ�����ܹ���⵽�����߹�������������ʾ������
��2�����ϰ������δӺ��ⷢ���1��2�߹���ʱ����Ա����1��
��3����ʵ��(2)�Ļ����ϣ�ʵ�����з֣�������ܱ�֤����ͬʱʵ�֣��򲻼ӷ֡����ϰ������δӺ��ⷢ���2��1�߹���ʱ����Ա����1��
2.2 ���Ӳ���
��1����ַ������Ժ���ԹܵĹ���,ʵ�ֵ���Ա�ߵ�һ���ٷ���,��������书�ܣ�
��2��Ϊ��֤ϵͳ�ȶ��ԣ�����Ա�ӵ�1�Ժ��ⷢ��ܾ���֮��ֱ�Ӵ��м�ȡ����������������Ա���м�ֱ�Ӿ�����2������֮��
�����������ٴδӵ�1��2�Ժ���ܾ���ʱ������������*/
/*��������ܣ������ӷ�**/
#include <reg51.h>
#define DIG_SHI P0	  //����ʮλ����ܵĶ˿�
#define DIG_GE P1	  //��λ����ܵĶ˿�
unsigned char i=0;
unsigned char j=0;
unsigned char k=0;   // �����������
unsigned char q;
unsigned int a,b,c,d;
unsigned int num=15;//��������15ʱ����
sbit First=P3^2;
sbit Second=P3^3;
sbit fmq=P0^0;
/***����P2�˿�**/
sbit red0=P2^0;	//��ڵĵ�
sbit green0=P2^1;
sbit red1=P2^2;	  //������Աߵĵ�
sbit yellow1=P2^3;
sbit green1=P2^4;
sbit m=P2^5;//���뿪��1
sbit n=P2^6;//���뿪��2
sbit control=P2^7;//,���뿪��3��������ڵ���
 /*�����������ʾ0��1��2��3��4��5��6��7��8��9����ֵ */
unsigned char code DIG_CODE[10] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6} ;
void chushihua();
void delays(int x);//�����ӳٺ���
/****������ʾ����******/
void display();//��ʾ
/*********������********/
int main()
{ 
/*****����ֵ�����ó���***/
 while(m==0)
 {
 if (n!= 1)		//��ⰴ���Ƿ���
	{
		delays(1);	//��������

		if (n!= 1)	//�ٴμ�ⰴ���Ƿ���
		{
		num++;
		delays(7);
		}
	}
 else if(control!=1)
 {
 	delays(1);	//��������

		if (control!= 1)	//�ٴμ�ⰴ���Ƿ���
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
/********************��ʾ����*******************************/
void display()
{
  
if(k<100)
	{ 
	/**��ʾ������********/
	if(m==1&&n==1)
	{
     q=k;
     red1=0; //�����
     yellow1=1;
     green1=1;
	}
	/**��ʾ��������********/
	else if(m==0&&n==1)
	{
     q=i;
     red1=1; 
     yellow1=0;//�Ƶ���
     green1=1;
	}
	/**��ʾ��������********/
	else if(m==0&&n==0) 
	{
	 q=j;
	 red1=1; 
     yellow1=1;//�̵���
     green1=0;
	}
   else
	{
	  TR1=1; //����ʱ��
	  /**��̬��ʾ������********/
	  if(d%3==0) //5sһ�α任����3ȡ����������ѭ��
      {
	   q=k;
       red1=0; //�����
       yellow1=1;
       green1=1;
      }
	  else if(d%3==1)
      {
	   q=i;
       red1=1; 
       yellow1=0;//�Ƶ���
       green1=1;
	  }
	  else
	  {
	  q=j;
	  red1=1; 
      yellow1=1;//�̵���
      green1=0;
	  }
	}
	/***********��ʾ************/
		DIG_SHI=DIG_CODE[q% 100 / 10];
		DIG_GE=DIG_CODE[q%10];
	 if(control==1)		 //�ֶ�������ڵ�����
	   {
		if(k<num)
		{
		fmq=1;
		red0=1;//��ں����
		green0=0;//����̵���������ͨ��
		}
		else
		{
		fmq=0;//����������
		red0=0;//��ں����
		green0=1;//����̵��𣬽�ֹͨ��
		}
		}
	else 
	   {
	    fmq=0;//����������
		red0=0;//��ں����
		green0=1;//����̵��𣬽�ֹͨ��
	   }
	}
       else if(k>=100)
	{
		fmq=0;
		DIG_SHI=0x8e;  //F
		DIG_GE=0x8e;//F	 	
	}
}
/********************��ʼ������******************/
void chushihua()
{
    EA = 1;	    // �����ж�
	EX1=1;	  //�����ⲿ�ж�1
	IT1=1;	 //���ⲿ�ж�1
	EX0=1;
	IT0=1;
	ET1=1;//������ʱ��1�ж�
	DIG_SHI=DIG_CODE[0];
	DIG_GE=DIG_CODE[0];
	fmq=1;
   }
  /******************�ⲿ�ж�0First**************************/
void inter0() interrupt 0
{
	if((b==0)&&(a==0)&&(First==0))//�����������һ��
	{
		a+=1;
		if(a>1)
			a=0;
		EX0=0; 
	}
	if((b==1)&&(a==0)&&(First==0))//��������ȥ�ڶ���
	{
		j++;
		b=0;
		EX0=0;
	}
}
  /******************�ⲿ�ж�1Second**************************/
void inter1() interrupt 2
{
 	if((b==0)&&(a==0)&&(Second==0))//��������ȥ��һ��
	{
		b+=1;
		if(b>1)
		   b=0;
	EX1=0;
	}
	if((b==0)&&(a==1)&&(Second==0))//����������ڶ���
	{
		i++;
		a=0;
		EX1=0;
	}
}	 
/*************��ʱ��1�ж�****************/
 void Time1() interrupt 3
{  TH0=(65536-600)/256;		  //���¸�ֵ 11.0592MHZ������㣬ָ������1.09uS��
   TL0=(65536-600)%256;//1mS��aÿ�μ�1��ʱ��
   c++;	
   if(c==250) //5sһ��
    { d++;
	  c=0;
	}
}
/********�ӳٺ���**********/
void delays(int x)
{
	  int m,n;
	  for(m=30*x;m>0;m--)	//      x/10����
	  	for(n=110;n>0;n--);	 
}