#include <windows.h>
#include <stdio.h>
#include "CGProject.h"

void displaceAbove1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Vdisp, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* SeamMask)
{
    int x,y;
    long newpos,newpos_nextline;
    //bool flag = true;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;

    //for ( y = 0; y < height-1 ; y++ )
    for ( y = yBegin; y <= yEnd ; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		//for (  x= xBegin; x <= xEnd; x+=3 )
		{
		    //flag = false;
			newpos = y * 3 * width + x;
			//randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;
			newpos_nextline = newpos + 3 * width;
			if((D[newpos]==255 && D[newpos+1]==255 && D[newpos+2]==255))
            {
                //flag = true;
                dI[newpos] = dI[newpos_nextline];
                dI[newpos+1] = dI[newpos_nextline+1];
                dI[newpos+2] = dI[newpos_nextline+2];

                Buffer[newpos] = Buffer[newpos_nextline];
                Buffer[newpos+1] = Buffer[newpos_nextline+1];
                Buffer[newpos+2] = Buffer[newpos_nextline+2];

                Vdisp[newpos] += 1;
                Vdisp[newpos+1] += 1;
                Vdisp[newpos+2] += 1;
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                //flag = true;

                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] =randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;

            }
		}
}


void displaceBelow1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Vdisp, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* SeamMask)
{
    int x,y;
    long newpos,newpos_nextline;
    //bool flag = true;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;

    for ( y = height-1; y>0 ; y-- )
		for ( x= 0; x < 3 * width; x+=3 )
		//for (  x= xBegin; x <= xEnd; x+=3 )
		{
            //flag = false;
			newpos = y * 3 * width + x;
			newpos_nextline = newpos - 3 * width;
			//randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;
			if((D[newpos]==255 && D[newpos+1]==255 && D[newpos+2]==255))
            {
                //flag=true;
                dI[newpos] = dI[newpos_nextline];
                dI[newpos+1] = dI[newpos_nextline+1];
                dI[newpos+2] = dI[newpos_nextline+2];

                Buffer[newpos] = Buffer[newpos_nextline];
                Buffer[newpos+1] = Buffer[newpos_nextline+1];
                Buffer[newpos+2] = Buffer[newpos_nextline+2];

                Vdisp[newpos] -= 1;
                Vdisp[newpos+1] -= 1;
                Vdisp[newpos+2] -= 1;
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                //flag=true;

                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] =randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;

            }
		}
}



void displaceLeft1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Hdisp, BYTE* SeamMask)
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

                Hdisp[newpos] += 3;
                Hdisp[newpos+1] += 3;
                Hdisp[newpos+2] += 3;
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] = randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;

                SeamMask[newpos] = 255;
                SeamMask[newpos+1] = 255;
                SeamMask[newpos+2] = 255;
            }
		}
}


void displaceRight1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Hdisp, BYTE* SeamMask)
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


                Hdisp[newpos] -= 3;
                Hdisp[newpos+1] -= 3;
                Hdisp[newpos+2] -= 3;
            }
            else if((D[newpos]==128 && D[newpos+1]==128 && D[newpos+2]==128)&& x%2)
            {
                dI[newpos] = randg;//(dI[newpos_nextline]);//+dI[newpos])/2;
                dI[newpos+1] = randg;//(dI[newpos_nextline+1]);//+dI[newpos+1])/2;
                dI[newpos+2] = randg;//(dI[newpos_nextline+2]);//+dI[newpos+2])/2;

                Buffer[newpos] = randr;
                Buffer[newpos+1] = randg;
                Buffer[newpos+2] = randb;

                SeamMask[newpos] = 255;
                SeamMask[newpos+1] = 255;
                SeamMask[newpos+2] = 255;
            }
		}
}



void displaceReal(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, BYTE* D)
{
    int x,y;
    long newpos,newpos_nextline;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    //int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;
    int ynew,xnew;
    //printf("width = %d, height = %d\n", width, height);
    for ( y = height-1; y>0 ; y-- )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
			//printf("width = %d, height = %d\n", width, height);
            //printf("for newpos x = %d, y = %d \n", x, y);
            ynew = (y+Vdisp[newpos])>=height?height-1:(y+Vdisp[newpos]);
            //printf("for newpos_newline x = %d, y = %d \n", (x + Hdisp[newpos]), ynew);
			newpos_nextline = ynew * 3 * width + x + Hdisp[newpos];//newpos + 3 * width * Vdisp[newpos];

                D[newpos] = Buffer[newpos_nextline];
                D[newpos+1] = Buffer[newpos_nextline+1];
                D[newpos+2] = Buffer[newpos_nextline+2];
		}
}


void displaceBack(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, BYTE* D)
{
    int x,y;
    long newpos,newpos_nextline;
    //int randg = rand()%220 + 20, rands = 10-rand()%20;
    //int randg = 64 + rand()%128, randr = 64 + rand()%128, randb = 64 + rand()%128;
    int ynew,xnew;
    //printf("width = %d, height = %d\n", width, height);
    for ( y = height-1; y>0 ; y-- )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos_nextline = y * 3 * width + x;
			//printf("width = %d, height = %d\n", width, height);
            //printf("for newpos x = %d, y = %d \n", x, y);
            ynew = (y+Vdisp[newpos])>=height?height-1:(y+Vdisp[newpos]);
            //printf("for newpos_newline x = %d, y = %d \n", (x + Hdisp[newpos]), ynew);
			newpos = ynew * 3 * width + x + Hdisp[newpos];//newpos + 3 * width * Vdisp[newpos];

                D[newpos] = (D[newpos] + Buffer[newpos_nextline]);
                D[newpos+1] = (D[newpos+1] + Buffer[newpos_nextline+1]);
                D[newpos+2] = (D[newpos+2] + Buffer[newpos_nextline+2]);
		}
}
