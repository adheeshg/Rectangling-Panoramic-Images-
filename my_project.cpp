
#include <windows.h>
#include <stdio.h>
#include "CGProject.h"

BYTE* prepocess( BYTE* Buffer, int *width, int *height )
{

	int oldWidth = *width;

	removeExtraBoundaries(Buffer, width, height );

	long newsize = 3 * (*width) * (*height);
	BYTE* newbuf = new BYTE[newsize];
	memset ( newbuf, 0, newsize );

    long bufpos = 0, newpos = 0;

    //printf("buffer Created with %d, %d but old Width was %d, newsize= %l", (*width), (*height), oldWidth, newsize);
	for ( int y = 0; y < *height; y++ )
		for ( int x = 0; x < 3 * (*width); x+=3 )
		{
			bufpos = y * 3 * oldWidth + x;     // position in original buffer
			newpos = y * 3 * (*width) + x;           // position in new buffer

            //printf("x=%d, y=%d", x, y);
			newbuf[newpos] = Buffer[bufpos];       // swap r and b
			newbuf[newpos + 1] = Buffer[bufpos + 1]; // g stays
			newbuf[newpos + 2] = Buffer[bufpos + 2];     // swap b and r
		}
    //printf("preprocessing done");
	return newbuf;
}
/*
BYTE* LocalWarping1( BYTE* Buffer, int width, int height )
{
    //getGreyScale(Buffer, *width, *height );
    int xStart = -1, xFin = -1, yStart = -1, yFin = -1, tLen = 0, dir = 0;
    long newsize = 3 * (width) * (height);
    BYTE* B = new BYTE[newsize];
    BYTE* I = new BYTE[newsize];
    BYTE* dI = new BYTE[newsize];
    BYTE* D = new BYTE[newsize];
    BYTE* S = new BYTE[newsize];

    getGreyScale(Buffer, width, height, I );

    getGradient(I, width, height, dI);
    getBoundaryMap(I, width, height, B );

    BufImpose(dI,dI,B,width,height);
    //markSegmentforLargestBoundary(I, width, height );
    getSegmentforLargestBoundary( I, width, height, &xStart, &xFin, &yStart, &yFin, &tLen, &dir );
    printf("len of boundary segment =%d, dir = %d\n", tLen, dir);
    int zbc=0;
    while(tLen > 1)// && zbc<500)
    //for (int zbc=0; zbc<100; zbc++)
    {
        printf("%d, tLen=%d, dir=%d \n",zbc,tLen, dir);
        zbc++;

        if(dir==1)
        {
            //printf("reached");
            delete [] D;
            //printf("reached");
            D =  getHDisplacementImage1( dI, width, height, xStart, xFin, yStart, yFin, B, S);
            printf("found displacement");
            displaceAbove(I, D, width, height, Buffer);
            printf("displacemed");
        }
        else if(dir==3)
        {
            delete [] D;
            D =  getHDisplacementImage3( dI, width, height, xStart, xFin, yStart, yFin, B, S);
            displaceBelow(I, D, width, height, Buffer);
        }
        else if(dir==2)
        {
            delete [] D;
            D =  getVDisplacementImage2( dI, width, height, xStart, xFin, yStart, yFin, B, S);
            displaceLeft(I, D, width, height, Buffer);
            //zbc=500;
            //break;
            //displaceBelow(I, D, width, height, Buffer);
        }
        else if(dir==4)
        {
            delete [] D;
            D =  getVDisplacementImage4( dI, width, height, xStart, xFin, yStart, yFin, B, S);
            displaceRight(I, D, width, height, Buffer);
            //zbc=500;
            //break;
            //displaceBelow(I, D, width, height, Buffer);
        }
        else
        {
            printf("dir=%d\n",dir);
            break;
        }

        //getGreyScale(I,width,height,I);
        getGreyScale(Buffer, width, height, I );
        getGradient(I, width, height, dI);
        getBoundaryMap(I, width, height, B );
        BufImpose(dI,dI,B,width,height);
        xStart = -1; xFin = -1; yStart = -1; yFin = -1; tLen = 0; dir = 0;
        getSegmentforLargestBoundary( I, width, height, &xStart, &xFin, &yStart, &yFin, &tLen, &dir );
        //tLen=0;
    }


    //return
    BufCopy(I,Buffer,width,height);
    return I;
}
*/


BYTE* LocalWarping( BYTE* Buffer, int width, int height, char * output )
{
    //getGreyScale(Buffer, *width, *height );
    int xStart = -1, xFin = -1, yStart = -1, yFin = -1, tLen = 0, dir = 0;
    long newsize = 3 * (width) * (height);

    /*BYTE* tp = new BYTE[newsize];
    BufCopy(tp,Buffer,width,height);
    return tp;*/

    BYTE* forfinal = new BYTE[newsize];
    BYTE* temp = new BYTE[newsize];
    BYTE* B = new BYTE[newsize];
    BYTE* S = new BYTE[newsize];
    BYTE* I = new BYTE[newsize];
    BYTE* dI = new BYTE[newsize];
    BYTE* D = new BYTE[newsize];
    int* Vdisp =  new int[newsize];
    int* Hdisp =  new int[newsize];

//    for(int kkk=0;kkk<2;kkk++)
    {

        memset(S,0,newsize);
        memset(Vdisp,0,newsize);
        memset(Hdisp,0,newsize);
        BufCopy(temp,Buffer,width,height);
        BufCopy(forfinal,Buffer,width,height);
        BufCopy(I,Buffer,width,height);
        getGreyScale(Buffer, width, height, I );

        char suffix[10];
        getGradient(I, width, height, dI);
        getBoundaryMap(I, width, height, B );

        BufImpose(dI,dI,B,width,height);
        //markSegmentforLargestBoundary(I, width, height );
        getSegmentforLargestBoundary( I, width, height, &xStart, &xFin, &yStart, &yFin, &tLen, &dir );
        //printf("len of boundary segment =%d, dir = %d\n", tLen, dir);
        int zbc=0;
        long s2;
        while(tLen > 1)// && zbc<500)
        //for (int zbc=0; zbc<100; zbc++)
        {

            zbc++;

            if(zbc%5==0){
                tostring(suffix,zbc);
                printf("%d, tLen=%d, dir=%d \n",zbc,tLen, dir);
                strcat(strcat(strcat(output,"_sc"),suffix),".bmp");
                //saveAsImage(I, width, height, output);
                output[14]='\0';
            }


            if(dir==1)
            {
                //printf("reached");
                delete [] D;
                //printf("reached");
                D =  getHDisplacementImage1( dI, width, height, xStart, xFin, yStart, yFin, B, S);
                //printf("found displacement");
                displaceAbove1(I, D, width, height, Buffer,Vdisp, xStart, xFin, yStart, yFin, S);
                //printf("displacemed");
            }
            else if(dir==3)
            {
                delete [] D;
                D =  getHDisplacementImage3( dI, width, height, xStart, xFin, yStart, yFin, B, S);
                displaceBelow1(I, D, width, height, Buffer,Vdisp, xStart, xFin, yStart, yFin, S);
            }
            else if(dir==2)
            {
                delete [] D;
                D =  getVDisplacementImage2( dI, width, height, xStart, xFin, yStart, yFin, B, S);
                displaceLeft1(I, D, width, height, Buffer, Hdisp, S);
                //zbc=500;
                //break;
                //displaceBelow(I, D, width, height, Buffer);
            }
            else if(dir==4)
            {
                delete [] D;
                D =  getVDisplacementImage4( dI, width, height, xStart, xFin, yStart, yFin, B, S);
                displaceRight1(I, D, width, height, Buffer, Hdisp, S);
                //zbc=500;
                //break;
                //displaceBelow(I, D, width, height, Buffer);
            }
            else
            {
                printf("dir=%d\n",dir);
                break;
            }

            //getGreyScale(I,width,height,I);
            BufCopy(I,Buffer,width,height);
            getGreyScale(Buffer, width, height, I );
            getGradient(I, width, height, dI);
            getBoundaryMap(I, width, height, B );
            BufImpose(dI,dI,B,width,height);
            xStart = -1; xFin = -1; yStart = -1; yFin = -1; tLen = 0; dir = 0;
            getSegmentforLargestBoundary( I, width, height, &xStart, &xFin, &yStart, &yFin, &tLen, &dir );
            //tLen=0;
        }


        hplace_mesh(I, width, height, Vdisp,Hdisp,temp);
        //saveAsImage(I, width, height, strcat(output,"z11mp.bmp"));
        output[14]='\0';

        //saveAsImage(temp, width, height, strcat(output,"z21rb.bmp"));
        output[14]='\0';

        /*memset(temp,0,newsize);
        hplace_mesh(I, width, height, Vdisp,Hdisp,temp);
        c = ConvertRGBToBMPBuffer ( temp, width, height, &s2 );
        SaveBMP ( c, width, height, s2, strcat(output,"bm.bmp") );
        output[14]='\0';*/
        global_warping(forfinal, width, height, Vdisp,Hdisp, output);

        BufCopy(I,forfinal,width,height);

        xStart = -1; xFin = -1; yStart = -1; yFin = -1; tLen = 0; dir = 0;

    }
    delete [] forfinal;
    delete [] temp;
    delete [] Vdisp;
    delete [] Hdisp;
    delete [] B;
    delete [] S;
    delete [] dI;
    delete [] D;
    return I;
}
