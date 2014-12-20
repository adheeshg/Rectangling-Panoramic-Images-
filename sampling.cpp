
#include <windows.h>
#include <stdio.h>
#include "CGProject.h"
#include<math.h>

BYTE* downsampling( BYTE* Buffer, int *width, int *height, int n )
{
    //n=n*n;
    int oldwidth = *width, oldheight = *height, newwidth = floor(oldwidth/n), newheight = floor(oldheight/n);
    int x,xo=0,y,yo=0;

    long newsize = 3*newwidth*newheight, newpos, oldpos;
    BYTE* newbuf = new BYTE[newsize];
    //printf("oldwidth = %d, oldheight = %d, newwidth = %d, newheight = %d\n",oldwidth,oldheight, newwidth,newheight );

    for ( y = 0; y < newheight; y++,yo+=n )
		for ( x= 0, xo=0; x < 3 * newwidth; x+=3,xo+=(3*n) )
		{
			newpos = y * 3 * newwidth + x;
			oldpos = yo * 3 * oldwidth + xo;
            //printf("y=%d, yo=%d, x=%d, xo=%d\n",y,yo,x,xo);
            //printf("oldwidth = %d, oldheight = %d, newwidth = %d, newheight = %d\n",oldwidth,oldheight, newwidth,newheight );

			newbuf[newpos] = Buffer[oldpos];
			newbuf[newpos+1] = Buffer[oldpos+1];
			newbuf[newpos+2] = Buffer[oldpos+2];
		}
    *width = newwidth;
    *height = newheight;
    return newbuf;
}


BYTE* scaleup2( BYTE* Buffer, int *width, int *height )
{
    int oldwidth = *width, oldheight = *height, newwidth = oldwidth*2, newheight = oldheight;
    long newsize = 3*newwidth*newheight,newpos, oldpos;
    BYTE* newbuf1 = new BYTE[newsize];
    int x,xo,y,yo;

    for ( y = 0, yo = 0; y < newheight; yo++,y++ )
		for ( x= 0, xo=0; x < 3 * newwidth; xo+=3,x+=6 )
		{
			newpos = y * 3 * newwidth + x;
			oldpos = yo * 3 * oldwidth + xo;
            //printf("y=%d, yo=%d, x=%d, xo=%d\n",y,yo,x,xo);
            //printf("oldwidth = %d, oldheight = %d, newwidth = %d, newheight = %d\n",oldwidth,oldheight, newwidth,newheight );

			newbuf1[newpos] = Buffer[oldpos];
			newbuf1[newpos+1] = Buffer[oldpos+1];
			newbuf1[newpos+2] = Buffer[oldpos+2];
		}

    for ( y = 0; y < newheight; y++ )
		for ( x= 3; x < 3 * newwidth  ; x+=6 )
		{
            xo=(x>(3 * newwidth - 6))?-3:3;
			newpos = y * 3 * newwidth + x;
            //printf("y=%d, yo=%d, x=%d, xo=%d\n",y,yo,x,xo);
            //printf("oldwidth = %d, oldheight = %d, newwidth = %d, newheight = %d\n",oldwidth,oldheight, newwidth,newheight );

			newbuf1[newpos] = newbuf1[newpos+xo]/2 + newbuf1[newpos-3]/2;
			newbuf1[newpos+1] = newbuf1[newpos+xo+1]/2 + newbuf1[newpos+1-3]/2;
			newbuf1[newpos+2] = newbuf1[newpos+xo+2]/2 + newbuf1[newpos+2-3]/2;
		}

	//******************************************************************************************
	oldheight = newheight;
	newheight *= 2;
    newsize = 3*newwidth*newheight;
    BYTE* newbuf2 = new BYTE[newsize];

    for ( y = 0, yo = 0; y < newheight; yo++,y+=2 )
		for ( x= 0, xo=0; x <  3 * newwidth; xo+=3,x+=3 )
		{
			newpos = y * 3 * newwidth + x;
			oldpos = yo * 3 * newwidth + xo;
            //printf("y=%d, yo=%d, x=%d, xo=%d\n",y,yo,x,xo);
            //printf("oldwidth = %d, oldheight = %d, newwidth = %d, newheight = %d\n",oldwidth,oldheight, newwidth,newheight );

			newbuf2[newpos] = newbuf1[oldpos];
			newbuf2[newpos+1] = newbuf1[oldpos+1];
			newbuf2[newpos+2] = newbuf1[oldpos+2];
		}


    for ( y = 1; y < newheight; y+=2 )
		for ( x= 0; x < 3 * newwidth  ; x+=3 )
		{
            yo = y==(newheight-1)?-1:1;
			newpos = y * 3 * newwidth + x;
            //printf("y=%d, yo=%d, x=%d, xo=%d\n",y,yo,x,xo);
            //printf("oldwidth = %d, oldheight = %d, newwidth = %d, newheight = %d\n",oldwidth,oldheight, newwidth,newheight );

			newbuf2[newpos] = newbuf2[newpos+(3 * newwidth)*yo]/2 + newbuf2[newpos-(3 * newwidth)]/2;
			newbuf2[newpos+1] = newbuf2[newpos+(3 * newwidth)*yo+1]/2 + newbuf2[newpos+1-(3 * newwidth)]/2;
			newbuf2[newpos+2] = newbuf2[newpos+(3 * newwidth)*yo+2]/2 + newbuf2[newpos+2-(3 * newwidth)]/2;
		}

    *width = newwidth;
    *height = newheight;
    delete [] newbuf1;
    return newbuf2;
}
//copied from http://www.sanfoundry.com/c-program-integer-to-string-vice-versa/
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
