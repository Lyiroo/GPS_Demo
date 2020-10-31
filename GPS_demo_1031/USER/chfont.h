#ifndef __CHFONT_H
#define __CHFONT_H	 
//PCtolcd2002 设置->点阵：16 ，其他设置同OLED实验。
const unsigned char tfont16[][16]=
{

{0x00,0x02,0x40,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x7F,0xFE},
{0x41,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x40,0x02,0x00,0x02,0x00,0x00},/*"?",0*/
{0x08,0x82,0x0F,0x44,0xF8,0x28,0x08,0x30,0x0F,0xCC,0x08,0x21,0x31,0xC2,0x2E,0x4C},
{0x22,0x30,0xA3,0xC0,0x60,0x00,0x23,0xFE,0x22,0x21,0x2A,0x11,0x33,0xE7,0x00,0x00},/*"?",1*/
{0x08,0x02,0x08,0x44,0x0F,0xA8,0xF8,0x10,0x08,0x68,0x0F,0x86,0x20,0xC0,0x2E,0xA0},
{0x2A,0xA2,0xAA,0xA1,0x6A,0xBE,0x2A,0xA0,0x2A,0xA0,0x2E,0xA0,0x20,0xC0,0x00,0x00},/*"?",2*/
{0x00,0x78,0x0F,0x84,0x10,0xC4,0x11,0x34,0x0E,0x98,0x00,0xE4,0x00,0x84,0x00,0x08},/*"&",3*/
{0x02,0x00,0x02,0x00,0x42,0x00,0x33,0xFE,0x00,0x04,0x00,0x08,0x04,0x80,0x18,0x80},
{0xF0,0x80,0x10,0x80,0x1F,0xFF,0x10,0x80,0x10,0x80,0x10,0x80,0x00,0x80,0x00,0x00},/*"?",4*/
{0x41,0x08,0x42,0x48,0x5C,0x50,0x55,0x50,0xFD,0x7F,0x55,0x55,0x5D,0x55,0x41,0xF5},
{0x21,0x55,0xDB,0x55,0x95,0x7F,0x94,0x50,0xDA,0x50,0x21,0x48,0x20,0x08,0x00,0x00},/*"?",5*/
{0x00,0x80,0x07,0x00,0x00,0x00,0xFF,0xFF,0x08,0x01,0x04,0x02,0x8F,0x84,0x68,0x98},
{0x08,0xE0,0x08,0x80,0x18,0xFC,0x28,0x82,0xCF,0x82,0x00,0x02,0x00,0x0E,0x00,0x00},/*"?",6*/


};
//PCtolcd2002 设置->点阵：24 ，其他设置同OLED实验。
const unsigned char tfont24[][24]=
{  


{0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x04,0x08,0x00,0x04,0x08,0x08,0x04,0x08,0x08,0x04,0x08,0x08,0x04,0x08,0x08,0x04},
{0x08,0x08,0x04,0x08,0x08,0x04,0x08,0x08,0x04,0x0F,0xFF,0xFC,0x0F,0xFF,0xFC,0x08,0x08,0x04,0x08,0x08,0x04,0x08,0x08,0x04},
{0x08,0x08,0x04,0x08,0x08,0x04,0x08,0x08,0x04,0x18,0x08,0x04,0x08,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00},/*"王",0*/
{0x00,0x00,0x00,0x02,0x00,0x02,0x02,0x1E,0x04,0x03,0xF1,0x08,0x7F,0x01,0xB0,0x62,0x01,0xC0,0x02,0x1F,0xC0,0x03,0xF8,0x62},
{0x02,0x02,0x34,0x02,0x04,0x08,0x1E,0x38,0x10,0x09,0xE6,0x20,0x0B,0x40,0xC0,0x08,0x4F,0x00,0x48,0x78,0x00,0x38,0x40,0x00},
{0x38,0x7F,0xF8,0x08,0x40,0x0C,0x08,0x40,0x84,0x08,0x40,0x44,0x0C,0x7F,0xC4,0x08,0x40,0x3C,0x00,0x00,0x0C,0x00,0x00,0x00},/*"婉",1*/
{0x00,0x00,0x00,0x02,0x00,0x02,0x02,0x0E,0x04,0x02,0xF9,0x08,0x1F,0x81,0x30,0x7A,0x00,0xE0,0x02,0x07,0xC0,0x02,0xFC,0x60},
{0x03,0xC0,0x30,0x08,0x04,0x00,0x08,0x1C,0x00,0x08,0x12,0x00,0x0B,0xF2,0x08,0x0A,0x52,0x08,0x4A,0x52,0x04,0x3A,0x52,0x0C},
{0x1A,0x53,0xF8,0x0A,0x52,0x00,0x0A,0x52,0x00,0x0B,0xF2,0x00,0x08,0x16,0x00,0x08,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*"婷",2*/
{0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x30,0x40,0x00,0x1C,0x7F,0xF8,0x08,0x40,0x30,0x00,0x00,0x20},
{0x00,0x28,0x40,0x00,0xC8,0x80,0x03,0x08,0x00,0x1E,0x08,0x00,0x7C,0x08,0x00,0x24,0x08,0x00,0x04,0x08,0x00,0x07,0xFF,0xFE},
{0x04,0x08,0x00,0x04,0x08,0x00,0x04,0x08,0x00,0x04,0x08,0x00,0x0C,0x08,0x00,0x00,0x18,0x00,0x00,0x08,0x00,0x00,0x00,0x00},/*"许",3*/
{0x00,0x00,0x00,0x00,0x02,0x10,0x10,0x04,0x10,0x10,0x3A,0x20,0x15,0xE2,0x20,0x15,0x42,0x40,0x15,0x4A,0x40,0x7D,0xCA,0xFE},
{0x35,0x4A,0xD4,0x15,0x4B,0x54,0x15,0xFA,0x54,0x15,0xDF,0xD4,0x11,0x2F,0xD4,0x03,0x2B,0x54,0x3E,0xAB,0x54,0x22,0xD2,0xD4},
{0x22,0xD2,0x7E,0x22,0x92,0x40,0x7B,0x42,0x60,0x0B,0x42,0x20,0x08,0x22,0x20,0x08,0x30,0x20,0x00,0x00,0x00,0x00,0x00,0x00},/*"馨",4*/
{0x00,0x00,0x00,0x00,0x20,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFE,0x7F,0xFF,0xFE,0x02,0x00,0x00,0x03,0x00,0x02},
{0x01,0x80,0x04,0x00,0x00,0x04,0x03,0xFC,0x08,0x22,0x08,0x30,0x3E,0x09,0xE0,0x1A,0x0F,0x80,0x02,0x08,0x00,0x02,0x08,0x00},
{0x0E,0x0F,0xFC,0x72,0x08,0x04,0x22,0x08,0x04,0x03,0xFC,0x04,0x00,0x00,0x04,0x00,0x00,0x7C,0x00,0x00,0x08,0x00,0x00,0x00},/*"悦",5*/


};
#endif
