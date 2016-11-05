#ifndef __TFT_DRIVER_H
#define __TFT_DRIVER_H

#define H_VIEW
//#define USB_HARDWARE_SPI

#ifdef H_VIEW
#define X_MAX_PIXEL         320
#define Y_MAX_PIXEL         240
#else
#define X_MAX_PIXEL         240
#define Y_MAX_PIXEL         320
#endif

#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D//ç�°è‰²0 3165 00110 001011 00101
#define GRAY1   0x8410//ç�°è‰²1      00000 000000 00000
#define GRAY2   0x4208//ç�°è‰²2      11111 111110 11111
//çº¢5ä½�(0-31) ç»¿6ä½�(0-63) è“�5ä½�(0-31)

//#define TFT_CTRL        P1OUT    //å®šä¹‰TFTæ•°æ�®ç«¯å�£ä¸ºPBç»„
#define TFT_CS          BIT3     //å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --CS
#define TFT_RST         BIT2     //å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --RST
#define TFT_RS          BIT4     //å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --RS/DC
#define TFT_SDI         BIT7     //MOSI å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --SDI 
#define TFT_SCK         BIT5     //å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --SCK
#define TFT_SDO         BIT6     //MISO å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --SDO
//#define TFT_LED         //å¯¹åº”æŽ¥æ¶²æ™¶å±�(æˆ–è€…æ¨¡å�—)TFT --PIN_LEDèƒŒå…‰æ­£æž�

//æ¶²æ™¶æŽ§åˆ¶å�£ç½®1æ“�ä½œè¯­å�¥å®�å®šä¹‰
#define TFT_CS_SET      P1OUT |= TFT_CS
#define TFT_RS_SET      P1OUT |= TFT_RS
#define TFT_SDI_SET     P1OUT |= TFT_SDI
#define TFT_SCK_SET     P1OUT |= TFT_SCK
#define TFT_RST_SET     P1OUT |= TFT_RST
//#define TFT_LED_SET     P1OUT |= TFT_LED

//æ¶²æ™¶æŽ§åˆ¶å�£ç½®0æ“�ä½œè¯­å�¥å®�å®šä¹‰
#define TFT_CS_CLR      P1OUT &= ~TFT_CS
#define TFT_RS_CLR      P1OUT &= ~TFT_RS
#define TFT_SDI_CLR     P1OUT &= ~TFT_SDI
#define TFT_SCK_CLR     P1OUT &= ~TFT_SCK
#define TFT_RST_CLR     P1OUT &= ~TFT_RST
//#define TFT_LED_CLR     P1OUT &= ~TFT_LED

typedef unsigned int u16;
typedef unsigned char u8;

void TFT_Init(void);
void TFT_Clear(u16 Color);
void TFT_SetXY(u16 x, u16 y);
void TFT_DrawPoint(u16 x, u16 y, u16 Data);
u16  TFT_ReadPoint(u16 x, u16 y);

void TFT_Circle(u16 X, u16 Y, u16 R, u16 fc);
void TFT_DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 Color);
void TFT_Box(u16 x, u16 y, u16 w, u16 h, u16 bc);
void TFT_Box2(u16 x, u16 y, u16 w, u16 h, u8 mode);
void DisplayButtonDown(u16 x1, u16 y1, u16 x2, u16 y2);
void DisplayButtonUp(u16 x1, u16 y1, u16 x2, u16 y2);
void TFT_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void TFT_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void TFT_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num) ;

void Color_Test(void);
void Println(u8 *s);
#endif
