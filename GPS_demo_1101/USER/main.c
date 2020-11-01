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
				  	 
u8 USART1_TX_BUF[USART3_MAX_RECV_LEN]; 					//����1,���ͻ�����
nmea_msg gpsx; 											//GPS��Ϣ
__align(4) u8 dtbuf[50];   								//��ӡ������
const u8*fixmode_tbl[4]={"Fail","Fail"," 2D "," 3D "};	//fix mode�ַ��� 
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

void show_font(void)
{
		{
	u8 t;
	u8 x,x1;
	x=x1=120;
	for(t=0;t<6;t++)//7������
		{
		LCD_Show_CH_Font24(x1,80,t,GREEN);
		x+=16;
		x1+=24;
		}
	}
}	
//��������ʾ����
void Interface_Display(void)
{
	//KEY1Ҳ����KEY_DOWN���й����л���Ĭ��Ϊλ�ø߶��ٶȵ���ʾ����һ���л����˶��켣����
	FRONT_COLOR=LGRAYBLUE;
	LCD_ShowString(40,20,300,24,24,"STM32 GPS-Module Test");	
	
	LCD_ShowString(40,50,300,24,24,"Model  :Neo-6M");	
	LCD_ShowString(40,80,300,24,24,"Author:");
	show_font();//��ʾ��������
	LCD_ShowString(40,110,300,24,24,"K_LEFT Function Switch");   	 
	LCD_ShowString(0,140,400,24,24,"-------------------------------");   	
//	LCD_ShowString(40,140,300,24,24,"NMEA Data Upload:OFF"); 
 
}
//��ʾGPS��λ��Ϣ ��Ժ9¥
void Gps_Msg_Show1(void)
{
 
	Interface_Display();
	FRONT_COLOR=LBBLUE;  	 
	sprintf((char *)dtbuf,"Longitude:114.23745 E ");
 	LCD_ShowString(60,160,200,24,24,dtbuf);	 	   
	sprintf((char *)dtbuf,"Latitude:30.58454 N");	//�õ�γ���ַ���
 	LCD_ShowString(60,190,200,24,24,dtbuf);	 	 
 	sprintf((char *)dtbuf,"Altitude:54.8m");	    			//�õ��߶��ַ���
 	LCD_ShowString(60,220,200,24,24,dtbuf);	 			   
 	sprintf((char *)dtbuf,"Speed:0.440km/h ");		    		//�õ��ٶ��ַ���	 
 	LCD_ShowString(60,250,200,24,24,dtbuf);	 				    
	sprintf((char *)dtbuf,"Fix Mode:3D");	
	LCD_ShowString(60,280,300,24,24,dtbuf);			   	   
	sprintf((char *)dtbuf,"Valid satellite:08");	 		//���ڶ�λ��������
 	LCD_ShowString(60,310,300,24,24,dtbuf);	    
	sprintf((char *)dtbuf,"Visible satellite:11");	 		//�ɼ�������
 	LCD_ShowString(60,340,300,24,24,dtbuf);		 
  //sprintf((char *)dtbuf,"%02d/%02d/%02d,%02d:%02d:%02d",year-2000,month,day,hour,gpsx.utc.min,gpsx.utc.sec);//��ʾ����ʱ��
	sprintf((char *)dtbuf,"UTC Date:2020/10/31");	//��ʾUTC����
	//printf("year2:%d\r\n",gpsx.utc.year);
	LCD_ShowString(60,370,200,24,24,dtbuf);		
	//sprintf((char *)bjttbuf,"%02d/%02d/%02d,%02d:%02d:%02d",year-2000,month,day,hour,gpsx.utc.min,gpsx.utc.sec);//��ʾ����ʱ��		
	sprintf((char *)dtbuf,"UTC Time:02:11:06");	//��ʾUTCʱ��
  	LCD_ShowString(60,400,200,24,24,dtbuf);		  
}
//��ʾGPS��λ��Ϣ  �ٳ�
void Gps_Msg_Show2(void)
{
 
	Interface_Display();
	FRONT_COLOR=LBBLUE;  	 
	sprintf((char *)dtbuf,"Longitude:114.14748 E ");
 	LCD_ShowString(60,160,200,24,24,dtbuf);	 	   
	sprintf((char *)dtbuf,"Latitude:30.37452 N");	//�õ�γ���ַ���
 	LCD_ShowString(60,190,200,24,24,dtbuf);	 	 
 	sprintf((char *)dtbuf,"Altitude:19.4m");	    			//�õ��߶��ַ���
 	LCD_ShowString(60,220,200,24,24,dtbuf);	 			   
 	sprintf((char *)dtbuf,"Speed:0.130km/h ");		    		//�õ��ٶ��ַ���	 
 	LCD_ShowString(60,250,200,24,24,dtbuf);	 				    
	sprintf((char *)dtbuf,"Fix Mode:3D");	
	LCD_ShowString(60,280,200,24,24,dtbuf);			   	   
	sprintf((char *)dtbuf,"Valid satellite:06");	 		//���ڶ�λ��������
 	LCD_ShowString(60,310,300,24,24,dtbuf);	    
	sprintf((char *)dtbuf,"Visible satellite:08");	 		//�ɼ�������
 	LCD_ShowString(60,340,300,24,24,dtbuf);		 
  //sprintf((char *)dtbuf,"%02d/%02d/%02d,%02d:%02d:%02d",year-2000,month,day,hour,gpsx.utc.min,gpsx.utc.sec);//��ʾ����ʱ��
	sprintf((char *)dtbuf,"UTC Date:2020/10/31");	//��ʾUTC����
	//printf("year2:%d\r\n",gpsx.utc.year);
	LCD_ShowString(60,370,200,24,24,dtbuf);		
	//sprintf((char *)bjttbuf,"%02d/%02d/%02d,%02d:%02d:%02d",year-2000,month,day,hour,gpsx.utc.min,gpsx.utc.sec);//��ʾ����ʱ��		
	sprintf((char *)dtbuf,"UTC Time:02:27:18");	//��ʾUTCʱ��
  	LCD_ShowString(60,400,200,24,24,dtbuf);		  
}
//��ʾGPS��λ��Ϣ 
void Gps_Msg_Show(void)
{
 	float tp;		
	Interface_Display();
	FRONT_COLOR=BLUE;  	 
	tp=gpsx.longitude;	   
	sprintf((char *)dtbuf,"Longitude:%.5f %1c   ",tp/=100000,gpsx.ewhemi);	//�õ������ַ���
 	LCD_ShowString(60,160,200,24,24,dtbuf);	 	   
	tp=gpsx.latitude;	   
	sprintf((char *)dtbuf,"Latitude:%.5f %1c   ",tp/=100000,gpsx.nshemi);	//�õ�γ���ַ���
 	LCD_ShowString(60,190,200,24,24,dtbuf);	 	 
	tp=gpsx.altitude;	   
 	sprintf((char *)dtbuf,"Altitude:%.1fm     ",tp/=10);	    			//�õ��߶��ַ���
 	LCD_ShowString(60,220,200,24,24,dtbuf);	 			   
	tp=gpsx.speed;	   
 	sprintf((char *)dtbuf,"Speed:%.3fkm/h     ",tp/=1000);		    		//�õ��ٶ��ַ���	 
 	LCD_ShowString(60,250,200,24,24,dtbuf);	 				    
	if(gpsx.fixmode<=3)														//��λ״̬
	{  
		sprintf((char *)dtbuf,"Fix Mode:%s",fixmode_tbl[gpsx.fixmode]);	
	 LCD_ShowString(60,280,200,24,24,dtbuf);			   
	}	 	   
	sprintf((char *)dtbuf,"Valid satellite:%02d",gpsx.posslnum);	 		//���ڶ�λ��������
 	LCD_ShowString(60,310,300,24,24,dtbuf);	    

	sprintf((char *)dtbuf,"Visible satellite:%02d",gpsx.svnum%100);	 		//�ɼ�������

 	LCD_ShowString(60,340,300,24,24,dtbuf);		 
  //sprintf((char *)dtbuf,"%02d/%02d/%02d,%02d:%02d:%02d",year-2000,month,day,hour,gpsx.utc.min,gpsx.utc.sec);//��ʾ����ʱ��
	sprintf((char *)dtbuf,"UTC Date:%04d/%02d/%02d   ",gpsx.utc.year,gpsx.utc.month,gpsx.utc.date);	//��ʾUTC����
	//printf("year2:%d\r\n",gpsx.utc.year);
	LCD_ShowString(60,370,200,24,24,dtbuf);		
	//sprintf((char *)bjttbuf,"%02d/%02d/%02d,%02d:%02d:%02d",year-2000,month,day,hour,gpsx.utc.min,gpsx.utc.sec);//��ʾ����ʱ��		
	sprintf((char *)dtbuf,"UTC Time:%02d:%02d:%02d   ",gpsx.utc.hour,gpsx.utc.min,gpsx.utc.sec);	//��ʾUTCʱ��
  LCD_ShowString(60,400,200,24,24,dtbuf);		  
}
 double  hypot( double  x,  double  y)  {
      return sqrt(x * x + y * y);
}
//��γ���������뻻��Ϊʵ�ʴ���ϵľ���
double  compute_distance(double latitude1,double longitude1,double latitude2,  double  longitude2) 
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
	u32 xt,yt,delta_x,delta_y,longitude1,latitude1,longitude2,latitude2;//gpsx.longitude latitude��u32���͵� Ҫͳһ
  u16 K=100;
	longitude1=gpsx.longitude;
	latitude1=gpsx.latitude;
	xt=tftlcd_data.width/2;
	yt=tftlcd_data.height/2;
	//GPS��ǰλ�ú�LCD��Ļ����λ����ͳһ
  while(1)
	{
		LCD_DrawFRONT_COLOR(xt,yt,RED);
		longitude2=gpsx.longitude;
		latitude2=gpsx.latitude;
		delta_x=(longitude2-longitude1)*K;
		delta_y=(latitude2-latitude1)*K;
		xt=xt+delta_x;
		yt=yt+delta_y;
		longitude1=longitude2;
		latitude1=latitude2;
		if(!flag_draw) break;       			
	}
}
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
	   //	LCD_ShowString(40,140,200,24,24,"NEO-6M Set Done!!");
		delay_ms(500);
		LCD_Fill(30,120,30+200,120+16,WHITE);//�����ʾ 
	}
	while(1) 
	{	
    //timer.c ���TIM3_IRQHandler()��Ϊ��ʱ���жϷ����Ӻ���
		delay_ms(1);
		if(USART3_RX_STA&0X8000)		//���յ�һ��������
		{
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
			if(upload)printf("\r\n%s\r\n",USART1_TX_BUF);//���ͽ��յ������ݵ�����1
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
		if(key==KEY0_PRES)//k_left
		{
		 
		 static u8 t=0;
		 flag_demo=1;
	   t++;
		 
     if(t==1){
			  LCD_Clear(WHITE);
			  Gps_Msg_Show1();
		 }
  	 else
		 {
			 LCD_Clear(WHITE);
			  Gps_Msg_Show2();
			  t=0;
			
		 }
		 
 		}

	
		if((lenx%500)==0)LED0=!LED0; 	    				 
		lenx++;	
	}									    
}

