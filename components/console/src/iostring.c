/*  
 * Display function redirect
 *
 * Copyrights 2015 @ APTCHIP
 *
 * Date             Author          Description
 * ----------       ----------      ------------
 * 2014/06/22       LuXiang         Initial release
 *
 */

/******************************************************************************
* Include Files
******************************************************************************/

#include "stdarg.h"
#include "stddef.h"
#include "stdio.h"
#include "sys_console.h"

//extern unsigned int RxDataFlag;
//extern unsigned int TxDataFlag;

//#define	DBG_PRINT2PC			//enable select console
/******************************************************************************
* Main code
******************************************************************************/
#define LDCC_DATA_P 		0xe001105c /* LDCC Register. */
#define LDCC_BIT_STATUS 	0x80000000 /* LDCC Status bit. */
/*
int fputc(int ch, FILE *f)
{
	volatile unsigned int *pdata = LDCC_DATA_P;
	//Waiting for data read.
	while (*pdata & LDCC_BIT_STATUS);
	//delay_nms(5000);
	//while (*pdata & LDCC_BIT_STATUS);
	*pdata = ch;
	return 0;
}
*/
void __putchar__ (char ch) {
	
#ifdef DBG_PRINT2PC
	//select console, uart1, PA013/PB00
	fputc(ch,(FILE *) -1);			
	
#else
	//select serial Pane
	volatile unsigned int *pdata = (unsigned int *)LDCC_DATA_P;
	while (*pdata & LDCC_BIT_STATUS);	//Waiting for data read.
	//delay_nms(5000);
	*pdata = ch;
#endif

}


//char *myitoa(int value, char* string, int radix)
char *myitoa(int value, int* string, int radix)
{

		//char tmp[33];
		int tmp[33];
		//char* tp = tmp;
		int* tp = tmp;
		int i;
		unsigned v;
		int sign;
		//char* sp;
		int* sp;
		
		if (radix > 36 || radix <= 1)
		{
			return 0;
		}
		
		sign = (radix == 10 && value < 0);
		if (sign)
		v = -value;
		else
		v = (unsigned)value;
		while (v || tp == tmp)
		{
			i = v % radix;
			v = v / radix;
			if (i < 10) {
			*tp++ = i+'0';
			
			//dummy write for committing SRAM_BRIDGE buffer
			//*(volatile unsigned int *)(0x20001000) =  0x00000000 ;
			} else {
			*tp++ = i + 'a' - 10;
			
			//dummy write for committing SRAM_BRIDGE buffer
			//*(volatile unsigned int *)(0x20001000) =  0x00000000 ;
			}
					
		}
		
	//	if (string == 0)
		//	string = (char*)malloc((tp-tmp)+sign+1);
		sp = string;
		
		if (sign)
		*sp++ = '-';
		while (tp > tmp)
		*sp++ = *--tp;
		*sp = 0;
		return (char *)string;
}


void my_printf(const char *fmt, ...)
{

	const char *s;
	const int *str;
	//const int *s;
	int d;
    //char ch, *pbuf, buf[16];
	char ch, *pbuf;
	int buf[16];
    va_list ap;
    va_start(ap, fmt);
    while (*fmt) {
        if (*fmt != '%') {
              __putchar__(*fmt++);
            continue;
        }
        switch (*++fmt) {
            case 's':
                s = va_arg(ap, const char *);
                for ( ; *s; s++) {
                 __putchar__(*s);
                }
                break;
            case 'd':
                d = va_arg(ap, int);
                myitoa(d, buf, 10);
                for (str = buf; *str; str++) {
                 __putchar__(*str);
                }
                break;
                
            case 'x':
            case 'X':
                d = va_arg(ap, int);
                myitoa(d, buf, 16);
                for (str = buf; *str; str++) {
                 __putchar__(*str);
                }
                break;                
            // Add other specifiers here...
            case 'c':
            case 'C':
            	ch = (unsigned char)va_arg(ap, int);
        	    pbuf = &ch;
            	__putchar__(*pbuf);
                break;
            default:  
                __putchar__(*fmt);
                break;
        }
        fmt++;
    }
    va_end(ap);

}

