
#include <windows.h>
#include <stdio.h>
#include "CGProject.h"

void getGreyScale( BYTE* Buffer, int width, int height, BYTE* newbuf )
{
    int x,y;
    long newsize = 3 * (width) * (height), newpos = 0;
    //BYTE* newbuf = new BYTE[newsize];
    BYTE I;
    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
            I= 0.2989*Buffer[newpos] + 0.5870*Buffer[newpos+1] + 0.1140*Buffer[newpos+2];

			newbuf[newpos] = I; //red
			newbuf[newpos + 1] = I; //green
			newbuf[newpos + 2] = I; //blue
		}
    //return newbuf;
}




BYTE* getYGradient( BYTE* I, int width, int height )
{
    int x,y;
    long newsize = 3 * (width) * (height), newpos,newpos_b,newpos_a;
    BYTE* newbuf = new BYTE[newsize];
    BYTE I_b, I_a, dIy;
    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{

			newpos = y * 3 * width + x;
			newpos_b = (y-1) * 3 * width + x;
			newpos_a = (y+1) * 3 * width + x;
            //I= 0.2989*Buffer[newpos] + 0.5870*Buffer[newpos+1] + 0.1140*Buffer[newpos+2];

            //get Ib
            if (y==0){
                I_b = 0;
            }
            else{
                I_b = I[newpos_b];
            }

            //get Ib
            if (y==height-1){
                I_a = 0;
            }
            else{
                I_a = I[newpos_a];
            }

            dIy = abs((I_a-I_b));
			newbuf[newpos] = dIy; //red
			newbuf[newpos + 1] = dIy; //green
			newbuf[newpos + 2] = dIy; //blue
		}
    return newbuf;
}




BYTE* getYGradientColor( BYTE* I, int width, int height )
{
    int x,y;
    long newsize = 3 * (width) * (height), newpos,newpos_b,newpos_a;
    BYTE* newbuf = new BYTE[newsize];
    BYTE I_br, I_bg, I_bb, I_ar, I_ag, I_ab, dIy;
    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{

			newpos = y * 3 * width + x;
			newpos_b = (y-1) * 3 * width + x;
			newpos_a = (y+1) * 3 * width + x;
            //I= 0.2989*Buffer[newpos] + 0.5870*Buffer[newpos+1] + 0.1140*Buffer[newpos+2];

            //get Ib
            if (y==0){
                I_br = 0;
                I_bg = 0;
                I_bb = 0;
            }
            else{
                I_br = I[newpos_b];
                I_bg = I[newpos_b+1];
                I_bb = I[newpos_b+2];
            }

            //get Ib
            if (y==height-1){
                I_ar = 0;
                I_ag = 0;
                I_ab = 0;
            }
            else{
                I_ar = I[newpos_a];
                I_ag = I[newpos_a+1];
                I_ab = I[newpos_a+2];
            }

            I_ar = abs((I_ar-I_br));
            I_ag = abs((I_ag-I_bg));
            I_ab = abs((I_ab-I_bb));

            dIy = I_ar/3 + I_ag/3 + I_ab/3 ;
			newbuf[newpos] = dIy; //red
			newbuf[newpos + 1] = dIy; //green
			newbuf[newpos + 2] = dIy; //blue
		}
    return newbuf;
}



BYTE* getXGradient( BYTE* I, int width, int height )
{
    int x,y;
    long newsize = 3 * (width) * (height), newpos,newpos_b,newpos_a;
    BYTE* newbuf = new BYTE[newsize];
    BYTE I_b, I_a, dIx;
    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{

			newpos = y * 3 * width + x;
			newpos_b = y * 3 * width + x-3;
			newpos_a = y * 3 * width + x+3;
            //I= 0.2989*Buffer[newpos] + 0.5870*Buffer[newpos+1] + 0.1140*Buffer[newpos+2];

            //get Ib
            if (x==0){
                I_b = 0;
            }
            else{
                I_b = I[newpos_b];
            }

            //get Ib
            if (x==width-3){
                I_a = 0;
            }
            else{
                I_a = I[newpos_a];
            }

            dIx = abs((I_a-I_b)) ;

			newbuf[newpos] = dIx; //red
			newbuf[newpos + 1] = dIx; //green
			newbuf[newpos + 2] = dIx; //blue
		}
    return newbuf;
}


BYTE* getXGradientColor( BYTE* I, int width, int height )
{
    int x,y;
    long newsize = 3 * (width) * (height), newpos,newpos_b,newpos_a;
    BYTE* newbuf = new BYTE[newsize];
    BYTE I_br, I_bg, I_bb, I_ar, I_ag, I_ab, dIx;
    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{

			newpos = y * 3 * width + x;
			newpos_b = y * 3 * width + x-3;
			newpos_a = y * 3 * width + x+3;
            //I= 0.2989*Buffer[newpos] + 0.5870*Buffer[newpos+1] + 0.1140*Buffer[newpos+2];

            //get Ib
            if (x==0){
                I_br = 0;
                I_bg = 0;
                I_bb = 0;
            }
            else{
                I_br = I[newpos_b];
                I_bg = I[newpos_b+1];
                I_bb = I[newpos_b+2];
            }

            //get Ib
            if (x==width-3){
                I_ar = 0;
                I_ag = 0;
                I_ab = 0;
            }
            else{
                I_ar = I[newpos_a];
                I_ag = I[newpos_a+1];
                I_ab = I[newpos_a+2];
            }

            I_ar = abs((I_ar-I_br));
            I_ag = abs((I_ag-I_bg));
            I_ab = abs((I_ab-I_bb));

            dIx = I_ar/3 + I_ag/3 + I_ab/3 ;

			newbuf[newpos] = dIx; //red
			newbuf[newpos + 1] = dIx; //green
			newbuf[newpos + 2] = dIx; //blue
		}
    return newbuf;
}


void getGradient( BYTE* I, int width, int height, BYTE* newbuf )
{
    long newsize = 3 * (width) * (height), newpos;
    BYTE* dIx = getXGradient(I, width, height);
    BYTE* dIy = getYGradient(I, width, height);
    //BYTE* newbuf = new BYTE[newsize];

    BYTE dI;
    int y,x;
	for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
            dI = (dIx[newpos] + dIy[newpos])/2;

			newbuf[newpos] = dI; //red
			newbuf[newpos + 1] = dI; //green
			newbuf[newpos + 2] = dI; //blue
		}
    delete [] dIx;
    delete [] dIy;
    //return newbuf;
}


void saveAsImage(BYTE* Buffer, int width, int height, char* name){
    long s2;
    BYTE* c = ConvertRGBToBMPBuffer ( Buffer, width, height, &s2 );
    SaveBMP ( c, width, height, s2, name );
    delete [] c;


}








/*
BYTE* getIntensity( BYTE* Buffer, int width, int height )
{
    int x,y;
    long newsize = (width) * (height), newpos, buffpos;
    BYTE* newbuf = new BYTE[newsize];
    BYTE I;

    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < width; x++ )
		{
			buffpos = y * 3 * width + x*3;
			newpos = y * width + x;
            I= 0.2989*Buffer[buffpos] + 0.5870*Buffer[buffpos+1] + 0.1140*Buffer[buffpos+2];

			newbuf[newpos] = I;
		}
    return newbuf;
}

void printIntensity( BYTE* newbuff, int width, int height, BYTE* Buffer )
{
    int x,y;
    //long newsize = (width) * (height),
    long newpos, buffpos;
    BYTE I;

    //0.2989, 0.5870, 0.1140

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < width; x++ )
		{
			buffpos = y * width + x;
			newpos = y * 3 * width + x*3;
            //I= 0.2989*Buffer[buffpos] + 0.5870*Buffer[buffpos+1] + 0.1140*Buffer[buffpos+2];
            I = Buffer[buffpos];

			newbuff[newpos] = I;
			newbuff[newpos+1] = I;
			newbuff[newpos+2] = I;
		}
}
*/
