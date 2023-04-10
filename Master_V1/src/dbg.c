/*
 * uartstdio2.c
 *
 *  Created on: Nov 3, 2020
 *      Author: Admin
 */


/**
 * dbg.c
 *
 *  Created on: 10-Oct-2016
 *      Author: Jayanth S. Moodliar
 *
 * (c) TechnoConfluence, 2016
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#define TARGET_IS_TM4C129_RA1
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "inc/dbg.h"


static void uart_putc(char c);


static char* bf;
static char buf[12];
static unsigned int num;
static char uc;
static char zs;

static void out(char c) {
    *bf++ = c;
    }

static void outDgt(char dgt) {
    out(dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10));
    zs=1;
    }

static void divOut(unsigned int div) {
    unsigned char dgt=0;
    num &= 0xffff; // just for testing the code  with 32 bit ints
    while (num>=div) {
        num -= div;
        dgt++;
        }
    if (zs || dgt>0)
        outDgt(dgt);
    }

void dbg_printf(char *fmt, ...)
{
    va_list va;
    char ch;
    char* p;

    va_start(va,fmt);

    while ((ch=*(fmt++))) {
        if (ch!='%') {
            uart_putc(ch);
            }
        else {
            char lz=0;
            char w=0;
            ch=*(fmt++);
            if (ch=='0') {
                ch=*(fmt++);
                lz=1;
                }
            if (ch>='0' && ch<='9') {
                w=0;
                while (ch>='0' && ch<='9') {
                    w=(((w<<2)+w)<<1)+ch-'0';
                    ch=*fmt++;
                    }
                }
            bf=buf;
            p=bf;
            zs=0;
            switch (ch) {
                case 0:
                    goto abort;
                case 'u':
                case 'd' :
                    num=va_arg(va, unsigned int);
                    if (ch=='d' && (int)num<0) {
                        num = -(int)num;
                        out('-');
                        }
                    divOut(10000);
                    divOut(1000);
                    divOut(100);
                    divOut(10);
                    outDgt(num);
                    break;
                case 'x':
                case 'X' :
                    uc= ch=='X';
                    num=va_arg(va, unsigned int);
                    divOut(0x1000);
                    divOut(0x100);
                    divOut(0x10);
                    outDgt(num);
                    break;
                case 'c' :
                    out((char)(va_arg(va, int)));
                    break;
                case 's' :
                    p=va_arg(va, char*);
                    break;
                case '%' :
                    out('%');
                default:
                    break;
                }
            *bf=0;
            bf=p;
            while (*bf++ && w > 0)
                w--;
            while (w-- > 0)
                uart_putc(lz ? '0' : ' ');
            while ((ch= *p++))
                uart_putc(ch);
            }
        }
    abort:;
    va_end(va);
}

static void uart_putc(char c)
{
    ROM_UARTCharPut(UART0_BASE, c);
}

