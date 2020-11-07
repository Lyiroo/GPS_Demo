#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "tftlcd.h"
#include "usmart.h"	
#include "usart3.h" 	
#include "key.h" 	 
#include "string.h"	 	 
#include "gps.h"	 
#include "math.h"
#include "timer.h"


/****************************************Copyright (c)****************************************************
 
**--------------File Info---------------------------------------------------------------------------------
** File name:          main.c
** Last modified Date: 2020/10/31   ���Ӻ�����ʾ������Ϣ
                                    ��ʾ֮ǰ�洢�õ�λ����Ϣ
																		��1020 1024���bug:USART3�������while(1)����������valid satelliteһֱΪ0

											 2020/10/22    �켣���ƣ������ԣ�
											 2020/10/21    ����жϷ����Ӻ�������ⰴ��״̬ ���ڹ����л�                       
                       2020/10/20    ʵ�ֶ�λ
** Created date:       2020/10/19    
** Version:            V1.0
** Descriptions:       Null
**--------------------------------------------------------------------------------------------------------*/
/*				  	 
u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//����1,���ͻ�����
nmea_msg gpsx; 											//GPS��Ϣ
__align(4) u8 dtbuf[50];   								//��ӡ������
const u8*fixmode_tbl[4]={"Fail","Fail"," 2D "," 3D "};	//fix mode�ַ��� 
*/
u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//����1,���ͻ�����
nmea_msg gpsx; 											//GPS��Ϣ

u8 key=0XFF;

u8 flag_draw=0;//���ƹ켣��־λ
u8 flag_demo=0;//��ʾ��־λ
/*
//UTCת��Ϊ������(����)ʱ��
nmea_utc_time UTCToBeijing(u16 UTCyear,u8 UTCmonth,u8 UTCday,u8 UTChour,u8 UTCminute,u8 UTCsecond)
{
	u16 year=0;
	u8 month=0,day=0,hour=0;
    u16 lastday = 0;// 
    u16 lastlastday = 0;//
	
	  year=UTCyear;
		month=UTCmonth;
	  day=UTCday;
	  hour=UTChour+8;//UTC+8
	
	  if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
		{
        lastday = 31;
        if(month == 3)
				{
            if((year%400 == 0)||(year%4 == 0 && year%100 != 0))
                lastlastday = 29;
            else
                lastlastday = 28;
        }
        if(month == 8)
            lastlastday = 31;
    }
    else 
		if(month == 4 || month == 6 || month == 9 || month == 11)
		{
        lastday = 30;
        lastlastday = 31;
    }
    else
		{
        lastlastday = 31;
        if((year%400 == 0)||(year%4 == 0 && year%100 != 0))
            lastday = 29;
        else
            lastday = 28;
    }
		if(hour >= 24)
		{
				hour -= 24;
				day += 1; 
				if(day > lastday)
				{ 
						day -= lastday;
						month += 1;

						if(month > 12)
						{
								month -= 12;
								year += 1;
						}
				}
		}	
//		Uart1_SendStr(bjttbuf);	
//		Uart1_SendStr("\r\n");
}
*/


int main(void)
{ 
	u16 i,rxlen;
	u16 lenx;

	u8 upload=0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      	//��ʼ����ʱ����
	uart_init(115200);			//��ʼ�����ڲ�����Ϊ115200 
	usart3_init(38400);			//��ʼ������3������Ϊ38400
	usmart_dev.init(84); 		//��ʼ��USMART		
	LED_Init();					//��ʼ��LED
	KEY_Init();					//��ʼ������
 	TFTLCD_Init();			 			//��ʼ��LCD
	usmart_dev.init(72); 		//��ʼ��USMART 	 
	TIM3_Init(100-1,8400-1);  //��ʱ100ms	   ͨ�ö�ʱ���ж�TIMER3
	Interface_Display();
	if(Ublox_Cfg_Rate(1000,1)!=0)	//���ö�λ��Ϣ�����ٶ�Ϊ1000ms,˳���ж�GPSģ���Ƿ���λ. 
	{
   		//LCD_ShowString(40,140,200,24,24,"NEO-6M Setting...");
		while((Ublox_Cfg_Rate(1000,1)!=0)&&key)	//�����ж�,ֱ�����Լ�鵽NEO-6M,�����ݱ���ɹ�
		{
			usart3_init(9600);				//��ʼ������3������Ϊ9600(EEPROMû�б������ݵ�ʱ��,������Ϊ9600.)
	  	Ublox_Cfg_Prt(38400);			//��������ģ��Ĳ�����Ϊ38400
			usart3_init(38400);				//��ʼ������3������Ϊ38400
			Ublox_Cfg_Tp(1000000,100000,1);	//����PPSΪ1�������1��,������Ϊ100ms	    
			key=Ublox_Cfg_Cfg_Save();		//��������  
		}	  					 
	   //LCD_ShowString(40,140,200,24,24,"NEO-6M Set Done!!");
		delay_ms(500);
	   //LCD_Fill(30,120,30+200,120+16,WHITE);//�����ʾ 
	}

	while(1) 
	{	
    //timer.c ���TIM3_IRQHandler()��Ϊ��ʱ���жϷ����Ӻ���
		delay_ms(5);
		if(USART3_RX_STA&0X8000)		//���յ�һ��������
		{
			//�������ݳɹ���D0��˸
			if((lenx%500)==0)LED0=!LED0; 	    				 
			lenx++;	
			rxlen=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
			for(i=0;i<rxlen;i++)USART1_TX_BUF[i]=USART3_RX_BUF[i];	   
 			USART3_RX_STA=0;		   	//������һ�ν���
			USART1_TX_BUF[i]=0;			//�Զ���ӽ�����
			GPS_Analysis(&gpsx,(u8*)USART1_TX_BUF);//�����ַ���
			/*  ����һ��bug
			if(flag_draw)
			{
				LCD_Clear(WHITE);
				Draw_Path();    //���ƹ켣
			}
			else
			{
				LCD_Clear(WHITE);
				//show_chinese(30,140,�",RED,WHITE);  //YELLOW
				Gps_Msg_Show();				//��ʾ��Ϣ
			*/
			if(!flag_demo) Gps_Msg_Show();				//��ʾ��Ϣ
			
	   
			//}
			//if(upload)printf("\r\n%s\r\n",USART1_TX_BUF);//���ͽ��յ������ݵ�����1
 		}


/*
		if(key==KEY0_PRES)
		{
			upload=!upload;
			FRONT_COLOR=RED;
			if(upload)LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:ON ");
			else LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:OFF");
 		}
	*/	
		



	}									    
}

