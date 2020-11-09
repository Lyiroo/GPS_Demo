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
#include "stdlib.h"
/****************************************Copyright (c)****************************************************
 
**--------------File Info---------------------------------------------------------------------------------
** File name:          main.c
** Last modified Date: 2020/11/07
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

u32 xt,yt,delta_x,delta_y,longitude1,latitude1,longitude2,latitude2;//gpsx.longitude latitude��u32���͵� Ҫͳһ

int main(void)
{ 
	u16 i,rxlen;
	u16 lenx;
	struct pos
	{
		u32 x;
		u32 y;
		u32 n;
	};
	//u8 upload=0;
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
   	LCD_ShowString(40,160,200,24,24,"NEO-6M Setting...");
		while((Ublox_Cfg_Rate(1000,1)!=0)&&key)	//�����ж�,ֱ�����Լ�鵽NEO-6M,�����ݱ���ɹ�
		{
			usart3_init(9600);				//��ʼ������3������Ϊ9600(EEPROMû�б������ݵ�ʱ��,������Ϊ9600.)
	  	Ublox_Cfg_Prt(38400);			//��������ģ��Ĳ�����Ϊ38400
			usart3_init(38400);				//��ʼ������3������Ϊ38400
			Ublox_Cfg_Tp(1000000,100000,1);	//����PPSΪ1�������1��,������Ϊ100ms	    
			key=Ublox_Cfg_Cfg_Save();		//��������  
		}	  					 
	   LCD_ShowString(40,160,200,24,24,"NEO-6M Set Done!!");
		delay_ms(500);
	   LCD_Fill(0,160,30+200,160+24,WHITE);//�����ʾ 
	}

	xt=tftlcd_data.width/2;
	yt=tftlcd_data.height/2;
	while(1) 
	{	
		u16 Res=1;//�ֱ���  ��
			u16 K;//����ϵ��
		//u16 n=0;
		static u32 t=0;
		/*
		u32* x = (u32 *) malloc ( sizeof(u32) * 300 );
		u32* y = (u32 *) malloc ( sizeof(u32) * 300 );
		*/
    //timer.c ���TIM3_IRQHandler()��Ϊ��ʱ���жϷ����Ӻ���
		K=5*1.0/Res;
		delay_ms(1);
		if(USART3_RX_STA&0X8000)		//���յ�һ��������
		{
			rxlen=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
			for(i=0;i<rxlen;i++)USART1_TX_BUF[i]=USART3_RX_BUF[i];	   
 			USART3_RX_STA=0;		   	//������һ�ν���
			USART1_TX_BUF[i]=0;			//�Զ���ӽ�����
			GPS_Analysis(&gpsx,(u8*)USART1_TX_BUF);//�����ַ���
			if(flag_draw)
			{
				/*
				if((n%10)==0)
				{
           x=gpsx.longitude;
					 y=gpsx.latitude;
				}//���1s��¼��ǰλ������
				n++;	
				*/
				//���ƹ켣
			 // LCD_DrawFRONT_COLOR(xt,yt,RED);
				LCD_Draw_Circle(xt,yt,1);
		    longitude2=gpsx.longitude;
		    latitude2=gpsx.latitude;
				delta_x=-1*(longitude2-longitude1)*K;
				delta_y=(latitude2-latitude1)*K;
				xt=xt+delta_x;
				yt=yt+delta_y;
				longitude1=longitude2;
				latitude1=latitude2; 
        //draw_message_show()			
			}
			else
			{
				//show_chinese(30,140,�",RED,WHITE);  //YELLOW
				Gps_Msg_Show();				//��ʾ��Ϣ
			}
			
			//if(!flag_demo) Gps_Msg_Show();				//��ʾ��Ϣ
			//if(upload)printf("\r\n%s\r\n",USART1_TX_BUF);//���ͽ��յ������ݵ�����1
 		}
		//�������ݳɹ���D1��˸
		if((lenx%100)==0)LED0=!LED0; 	    				 
		lenx++;	
	}
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
								    


