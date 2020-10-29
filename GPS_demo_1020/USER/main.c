#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "usmart.h"	
#include "usart3.h" 	
#include "key.h" 	 
#include "string.h"	 	 
#include "gps.h"	 
#include "math.h"

/****************************************Copyright (c)****************************************************
 
**--------------File Info---------------------------------------------------------------------------------
** File name:          main.c
** Last modified Date: 2020/10/20       ʵ�ֶ�λ
** Created date:       2020/10/19
** Version:            V1.0
** Descriptions:       null
**--------------------------------------------------------------------------------------------------------*/
				  	 
u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//����1,���ͻ�����
nmea_msg gpsx; 											//GPS��Ϣ
__align(4) u8 dtbuf[50];   								//��ӡ������
const u8*fixmode_tbl[4]={"Fail","Fail"," 2D "," 3D "};	//fix mode�ַ��� 
	  
//��ʾGPS��λ��Ϣ 
void Gps_Msg_Show(void)
{
 	float tp;		   
	 	POINT_COLOR=GREEN;
	LCD_ShowString(30,20,200,16,16,"STM32F4��NE0-6M GPS TEST");	
	LCD_ShowString(30,40,200,16,16,"Version��1.0");	
	LCD_ShowString(30,60,200,16,16,"Mode   :null");
	//KEY1Ҳ����KEY_DOWN���й����л���Ĭ��Ϊλ�ø߶��ٶȵ���ʾ����һ���л����˶��켣����
	LCD_ShowString(30,80,200,16,16,"KEY1   :Function Switch");
	
  LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:OFF");  
	POINT_COLOR=BLUE;  	 
	tp=gpsx.longitude;	   
	sprintf((char *)dtbuf,"Longitude:%.5f %1c   ",tp/=100000,gpsx.ewhemi);	//�õ������ַ���
 	LCD_ShowString(30,130,200,16,16,dtbuf);	 	   
	tp=gpsx.latitude;	   
	sprintf((char *)dtbuf,"Latitude:%.5f %1c   ",tp/=100000,gpsx.nshemi);	//�õ�γ���ַ���
 	LCD_ShowString(30,150,200,16,16,dtbuf);	 	 
	tp=gpsx.altitude;	   
 	sprintf((char *)dtbuf,"Altitude:%.1fm     ",tp/=10);	    			//�õ��߶��ַ���
 	LCD_ShowString(30,170,200,16,16,dtbuf);	 			   
	tp=gpsx.speed;	   
 	sprintf((char *)dtbuf,"Speed:%.3fkm/h     ",tp/=1000);		    		//�õ��ٶ��ַ���	 
 	LCD_ShowString(30,190,200,16,16,dtbuf);	 				    
	if(gpsx.fixmode<=3)														//��λ״̬
	{  
		sprintf((char *)dtbuf,"Fix Mode:%s",fixmode_tbl[gpsx.fixmode]);	
	  	LCD_ShowString(30,210,200,16,16,dtbuf);			   
	}	 	   
	sprintf((char *)dtbuf,"Valid satellite:%02d",gpsx.posslnum);	 		//���ڶ�λ��������
 	LCD_ShowString(30,230,200,16,16,dtbuf);	    

	sprintf((char *)dtbuf,"Visible satellite:%02d",gpsx.svnum%100);	 		//�ɼ�������
 	LCD_ShowString(30,250,200,16,16,dtbuf);		 
	sprintf((char *)dtbuf,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);	//��ʾUTC����
	//printf("year2:%d\r\n",gpsx.utc.year);
	LCD_ShowString(30,270,200,16,16,dtbuf);		    
	sprintf((char *)dtbuf,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);	//��ʾUTCʱ��
  	LCD_ShowString(30,290,200,16,16,dtbuf);		  
}
 double  hypot( double  x,  double  y)  {
      return sqrt(x * x + y * y);
}
//��γ���������뻻��Ϊʵ�ʴ���ϵľ���
double  distance( double  latitude1,  double  longitude1,  double latitude2,  double  longitude2) 
{
      double x, y, out;
      double PI = 3.1415926535898;
      double R = 6.371229 * 1e6;
       x = (longitude2 - longitude1) * PI * R * cos( ( (latitude1 + latitude2) / 2) * PI / 180) / 180;
       y = (latitude2 -latitude1) * PI * R / 180;
       out = hypot(x, y);
       return out;
}
//�˶��켣���ƺ���
void Draw_Path(void)
{
	u32 xt,yt,delta_x,delta_y;//gpsx.longitude latitude��u32���͵� Ҫͳһ
	delay_ms(50);
	LCD_Clear(WHITE);

	xt=lcddev.width/2;
	yt=lcddev.height/2;
	//GPS��ǰλ�ú�LCD��Ļ����λ����ͳһ
	
	while(1)
	{
		LCD_Fast_DrawPoint(xt,yt,RED);
		delta_x= gpsx.longitude-xt;     //
		delta_y= gpsx.latitude-yt;
		xt=xt+delta_x;
		yt=yt+delta_y;
	}
	
	

}


int main(void)
{ 
	u16 i,rxlen;
	u16 lenx;
	u8 key=0XFF;
	u8 upload=0;
	u8 flag_draw=0;//���ƹ켣��־λ
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      	//��ʼ����ʱ����
	uart_init(115200);			//��ʼ�����ڲ�����Ϊ115200 
	usart3_init(38400);			//��ʼ������3������Ϊ38400
	usmart_dev.init(84); 		//��ʼ��USMART		
	LED_Init();					//��ʼ��LED
	KEY_Init();					//��ʼ������
 	LCD_Init();		 			//��ʼ��LCD
	usmart_dev.init(72); 		//��ʼ��USMART 	  
 	POINT_COLOR=GREEN;
	LCD_ShowString(30,20,200,16,16,"STM32F4��NE0-6M GPS TEST");	
	LCD_ShowString(30,40,200,16,16,"Version��1.0");	
	LCD_ShowString(30,60,200,16,16,"Mode   :null");
	LCD_ShowString(30,80,200,16,16,"KEY1   :Function Switch");   	 										   	   
   	LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:OFF");   
	if(Ublox_Cfg_Rate(1000,1)!=0)	//���ö�λ��Ϣ�����ٶ�Ϊ1000ms,˳���ж�GPSģ���Ƿ���λ. 
	{
   		LCD_ShowString(30,120,200,16,16,"NEO-6M Setting...");
		while((Ublox_Cfg_Rate(1000,1)!=0)&&key)	//�����ж�,ֱ�����Լ�鵽NEO-6M,�����ݱ���ɹ�
		{
			usart3_init(9600);				//��ʼ������3������Ϊ9600(EEPROMû�б������ݵ�ʱ��,������Ϊ9600.)
	  		Ublox_Cfg_Prt(38400);			//��������ģ��Ĳ�����Ϊ38400
			usart3_init(38400);				//��ʼ������3������Ϊ38400
			Ublox_Cfg_Tp(1000000,100000,1);	//����PPSΪ1�������1��,������Ϊ100ms	    
			key=Ublox_Cfg_Cfg_Save();		//��������  
		}	  					 
	   	LCD_ShowString(30,120,200,16,16,"NEO-6M Set Done!!");
		delay_ms(500);
		LCD_Fill(30,120,30+200,120+16,WHITE);//�����ʾ 
	}
	while(1) 
	{		
		delay_ms(1);
		if(USART3_RX_STA&0X8000)		//���յ�һ��������
		{
			rxlen=USART3_RX_STA&0X7FFF;	//�õ����ݳ���
			for(i=0;i<rxlen;i++)USART1_TX_BUF[i]=USART3_RX_BUF[i];	   
 			USART3_RX_STA=0;		   	//������һ�ν���
			USART1_TX_BUF[i]=0;			//�Զ���ӽ�����
			GPS_Analysis(&gpsx,(u8*)USART1_TX_BUF);//�����ַ���
			if(flag_draw)
				Draw_Path();    //���ƹ켣
			else
				Gps_Msg_Show();				//��ʾ��Ϣ

			if(upload)printf("\r\n%s\r\n",USART1_TX_BUF);//���ͽ��յ������ݵ�����1
 		}
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
			{
				flag_draw=!flag_draw;
				POINT_COLOR=RED;


			
			}
     
		/*
		if(key==KEY0_PRES)
		{
			upload=!upload;
			POINT_COLOR=RED;
			if(upload)LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:ON ");
			else LCD_ShowString(30,100,200,16,16,"NMEA Data Upload:OFF");
 		}
		*/

		if((lenx%500)==0)LED0=!LED0; 	    				 
		lenx++;	
	}									    
}

