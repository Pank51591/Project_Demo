#ifndef _OLEDFONT_H_
#define _OLEDFONT_H_

unsigned char BMP1[] =
{
    0x00,0x03,0x05,0x09,0x11,0xFF,0x11,0x89,0x05,0xC3,0x00,0xE0,0x00,0xF0,0x00,0xF8,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x28,0xFF,0x11,0xAA,0x44,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x83,0x01,0x38,0x44,0x82,0x92,
    0x92,0x74,0x01,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x44,0xC7,0x01,0x7D,
    0x7D,0x7D,0x7D,0x01,0x7D,0x7D,0x7D,0x7D,0x01,0x7D,0x7D,0x7D,0x7D,0x01,0xFF,0x00,
    0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,
    0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
    0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x40,0x40,0x00,0x00,
    0x6D,0x6D,0x6D,0x6D,0x6D,0x00,0x00,0x60,0x60,0x60,0x60,0x60,0x00,0x00,0x40,0x40,
    0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDB,0xDB,0xDB,0xDB,0xDB,0x00,0x00,
    0xDB,0xDB,0xDB,0xDB,0xDB,0x00,0x00,0xDB,0xDB,0xDB,0xDB,0xDB,0x00,0x00,0xDB,0xDB,
    0xDB,0xDB,0xDB,0x00,0x00,0xDA,0xDA,0xDA,0xDA,0xDA,0x00,0x00,0xD8,0xD8,0xD8,0xD8,
    0xD8,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,
    0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x80,
    0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,
    0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,
    0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0xE6,0x66,0x20,0x00,0x06,0x06,0x86,0x06,
    0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x86,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,
    0x00,0x86,0x86,0x86,0x86,0x86,0x80,0x80,0x86,0x86,0x06,0x86,0x86,0xC0,0xC0,0x86,
    0x86,0x86,0x06,0x06,0xD0,0x30,0x76,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,
    0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x06,0x06,0x06,0x06,0x06,
    0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x1C,0x00,0xFE,0x00,0x01,
    0x02,0x00,0xC4,0x18,0x20,0x02,0x9E,0x63,0xB2,0x0E,0x00,0xFF,0x81,0x81,0xFF,0x00,
    0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0xFF,0x00,0x23,0xEA,0xAA,0xBF,0xAA,
    0xEA,0x03,0x3F,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x0C,0x08,0x00,0x00,0x01,0x01,0x01,
    0x01,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x81,0x80,0x80,0x81,0x80,
    0x81,0x80,0x80,0x80,0x80,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
    0x01,0x00,0x01,0x01,0x09,0x0C,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
    0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,
    0x00,0x1E,0x21,0x40,0x40,0x50,0x21,0x5E,0x00,0x1E,0x21,0x40,0x40,0x50,0x21,0x5E,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xC1,0xC1,0xFF,
    0xFF,0xC1,0xC1,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x80,0xFC,0xF3,0xEF,0xF3,0xFC,
    0x80,0xFF,0x80,0xEE,0xEE,0xEE,0xF5,0xFB,0xFF,0x9C,0xBE,0xB6,0xB6,0x88,0xFF,0x00,/*"D:\DreamSpark\OLED\MP3_UI.bmp",0*/
};


#endif
