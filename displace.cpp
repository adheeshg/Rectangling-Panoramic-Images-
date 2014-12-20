#include <windows.h>
#include <stdio.h>
#include "CGProject.h"

void displaceAbove(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
{
    int x,y;
    long newpos,newpos_nextline;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;

    for ( y = 0; y < height-1; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
			newpos_nextline = newpos + 3 * width;
			if((D[newpos]==255 && D[newpos+1]==255 && D[newpos+2]==255))
            {
                dI[newpos] = dI[newpos_nextline];
                dI[newpos+1] = dI[newpos_nextline+1];
                dI[newpos+2] = dI[newpos_nextline+2];

                Buffer[newpos] = Buffer[newpos_nextline];
                Buffer[newpos+1] = Buffer[newpos_nextline+1];
                Buffer[newpos+2] = Buffer[newpos_nextline+2];
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] = randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;


            }
		}
}


void displaceBelow(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
{
    int x,y;
    long newpos,newpos_nextline;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;

    for ( y = height-1; y>0 ; y-- )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
			newpos_nextline = newpos - 3 * width;
			if((D[newpos]==255 && D[newpos+1]==255 && D[newpos+2]==255))
            {
                dI[newpos] = dI[newpos_nextline];
                dI[newpos+1] = dI[newpos_nextline+1];
                dI[newpos+2] = dI[newpos_nextline+2];

                Buffer[newpos] = Buffer[newpos_nextline];
                Buffer[newpos+1] = Buffer[newpos_nextline+1];
                Buffer[newpos+2] = Buffer[newpos_nextline+2];
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] = randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;
            }
		}
}



void displaceLeft(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
{
    int x,y;
    long newpos,newpos_nextline;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width-3; x+=3 )
		{
			newpos = y * 3 * width + x;
			newpos_nextline = newpos + 3;
			if((D[newpos]==255 && D[newpos+1]==255 && D[newpos+2]==255))
            {
                dI[newpos] = dI[newpos_nextline];
                dI[newpos+1] = dI[newpos_nextline+1];
                dI[newpos+2] = dI[newpos_nextline+2];

                Buffer[newpos] = Buffer[newpos_nextline];
                Buffer[newpos+1] = Buffer[newpos_nextline+1];
                Buffer[newpos+2] = Buffer[newpos_nextline+2];
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] = randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;
            }
		}
}


void displaceRight(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
{
    int x,y;
    long newpos,newpos_nextline;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;

    for ( y = 0; y < height; y++ )
		for ( x= 3 * width-3; x > 0 ; x-=3 )
		{
			newpos = y * 3 * width + x;
			newpos_nextline = newpos - 3;
			if((D[newpos]==255 && D[newpos+1]==255 && D[newpos+2]==255))
            {
                dI[newpos] = dI[newpos_nextline];
                dI[newpos+1] = dI[newpos_nextline+1];
                dI[newpos+2] = dI[newpos_nextline+2];

                Buffer[newpos] = Buffer[newpos_nextline];
                Buffer[newpos+1] = Buffer[newpos_nextline+1];
                Buffer[newpos+2] = Buffer[newpos_nextline+2];
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] = randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;
            }
		}
}

