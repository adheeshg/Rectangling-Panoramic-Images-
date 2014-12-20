#include <windows.h>
#include <stdio.h>
#include "CGProject.h"



BYTE* markHorizontalSeamAbove( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
{
    //printf("reached");
    int x,y,ymin,ymax;
    long newsize =3 * (width) * (height), newpos, posa,posb,posc;//newposi_1j_1, newposij_1, newposi1j_1;
    BYTE Ma, Mb, Mc, Mmin, MM;
    BYTE* M = new BYTE[newsize];

    BufCopy(M,Buffer,width, height);


    //cumulative energy calculation
    //return M;
    BufImpose(M,M,SeamMask,width,height);
    Mmin = 255;
    ymin=yBegin + rand()%yEnd;
    for ( x= xBegin + 3; x <= xEnd; x+=3 )
    {
        for ( y = yEnd; y >= yBegin; y-- )
        {
                newpos = y * 3 * width + x;
                if(isBoundary(M,newpos)){
                    continue;
                }
                posb = newpos - 3;
                posa = posb - 3 * width;
                posc = posb + 3 * width;
                //printf("width = %d, height = %d x = %d, y=%d\n",width,height,x,y);
                //printf("posa=%ld, posb=%ld, posc=%ld\n", posa,posb,posc);
                Ma = (y==0)?255:M[posa];
                Mb = M[posb];
                Mc = (y==(height-1))?255:M[posc];

                if(Ma<Mb)
                {
                    if(Ma<Mc) {MM = Ma;}
                    else {MM = Mc;}
                }
                else
                {
                    if(Mb<Mc) {MM = Mb;}
                    else {MM = Mc;}
                }
                //printf("MM= %d, Ma= %d, Mb= %d, Mc= %d,Mnewpos=%d \n",MM,Ma,Mb,Mc,M[newpos]);

                int mm = MM, mnewpos = M[newpos];
                if ((mm==255)||(mnewpos==255)){MM=255;}
                else
                {
                 mm=0.95*mm;
                 mm=(mm+mnewpos);
                 MM=(mm<255)?mm:255;
                }
                M[newpos] = MM;
                M[newpos+1] = MM;
                M[newpos+2] = MM;
                if(x==xEnd)
                {
                    //printf("MM=%d,y=%d\n",MM,ymin);
                    if(MM<Mmin)
                    {
                        //printf("changing Mmin MM=%d,Mmin=%d\n",MM,Mmin);
                        Mmin = MM;
                        ymin = y;
                    }
                }
                //printf("M set = %d \n",MM);
        }

    }
    //printf("ymin=%d",ymin);
    //printf("cum energy found");
    //return M;
    BufImpose(M,M,BoundaryMask,width,height);

    //find seed to start finding the seam.
    x=xEnd;
    //printf("width = %d, height = %d x = %d, ymin=%d\n",width,height,x,ymin);
    newpos = ymin * 3 * width + x;
    M[newpos] = 0;
    M[newpos+1] = 255;
    M[newpos+2] = 0;

    //printf("seam seed found");
    //return M;
    while(x>xBegin && ymin>0)
    {

        y=ymin;
        newpos = y * 3 * width + x;

        posb = newpos - 3;
        posa = posb - 3 * width;
        posc = posb + 3 * width;
        //printf("width = %d, height = %d x = %d, y=%d\n",width,height,x,y);
        //printf("posa=%ld, posb=%ld, posc=%ld\n", posa,posb,posc);
        Ma = (y==0)?255:M[posa];
        Mb = M[posb];
        Mc = (y==(height-1))?255:M[posc];


        if(Ma<=Mb)
        {
            if(Ma<=Mc) {ymin=y?(y-1):0;}
            else {ymin = ymin%height?(ymin+1):0;}
        }
        else
        {
            if(Mb<=Mc) {ymin = ymin;}
            else {ymin = ymin%height?(ymin+1):0;}
        }
        x-=3;
        newpos = ymin * 3 * width + x;
        //printf("x= %d, y=%d\n",x,y);
        M[newpos] = 0;
        M[newpos+1] = 255;
        M[newpos+2] = 0;
    }
    //printf("seam carved");
    return M;
}

BYTE* markHorizontalSeamBelow (BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
{
    int x,y,ymin;
    long newsize =3 * (width) * (height), newpos, posa,posb,posc;//newposi_1j_1, newposij_1, newposi1j_1;
    BYTE Ma, Mb, Mc, Mmin, MM;
    BYTE* M = new BYTE[newsize];

    BufCopy(M,Buffer,width, height);

    BufImpose(M,M,SeamMask,width,height);
    //cumulative energy calculation
    //return M;
    Mmin = 255;
    for ( x= xBegin + 3; x <= xEnd; x+=3 )
    {
        for ( y = yBegin; y <= yEnd; y++ )
        {
                newpos = y * 3 * width + x;

                if(x<xEnd-3 && isBoundary(M,newpos)){
                    continue;
                }
                posb = newpos - 3;
                posa = posb - 3 * width;
                posc = posb + 3 * width;

                Ma = (y==0)?255:M[posa];
                Mb = M[posb];
                Mc = (y==(height-1))?255:M[posc];

                if(Ma<Mb)
                {
                    if(Ma<Mc) {MM = Ma;}
                    else {MM = Mc;}
                }
                else
                {
                    if(Mb<Mc) {MM = Mb;}
                    else {MM = Mc;}
                }
                //printf("MM= %d, Ma= %d, Mb= %d, Mc= %d,Mnewpos=%d \n",MM,Ma,Mb,Mc,M[newpos]);

                int mm = MM, mnewpos = M[newpos];
                if ((mm==255)||(mnewpos==255)){MM=255;}
                else
                {
                 mm=0.95*mm;
                 mm=(mm+mnewpos);
                 MM=(mm<255)?mm:255;
                }
                M[newpos] = MM;
                M[newpos+1] = MM;
                M[newpos+2] = MM;
                if(x==xEnd||MM<Mmin)
                {
                    Mmin = MM;
                    ymin = y;
                }
                //printf("M set = %d \n",MM);
        }

    }
    //printf("cum energy found");
    //return M;
    BufImpose(M,M,BoundaryMask,width,height);
    //find seed to start finding the seam.
    x=xEnd;
    newpos = ymin * 3 * width + x;
    M[newpos] = 0;
    M[newpos+1] = 255;
    M[newpos+2] = 0;

    //printf("seam seed found");
    //return M;
    while(x>xBegin && ymin>0)
    {

        y=ymin;
        newpos = y * 3 * width + x;

        posb = newpos - 3;
        posa = posb - 3 * width;
        posc = posb + 3 * width;

        Ma = (y==0)?255:M[posa];
        Mb = M[posb];
        Mc = (y==(height-1))?255:M[posc];


        if(Ma<=Mb)
        {
            if(Ma<=Mc) {ymin=y?(y-1):0;}
            else {ymin = ymin%height?(ymin+1):0;}
        }
        else
        {
            if(Mb<=Mc) {ymin = ymin;}
            else {ymin = ymin%height?(ymin+1):0;}
        }
        x-=3;
        newpos = ymin * 3 * width + x;
        //printf("x= %d, y=%d\n",x,y);
        M[newpos] = 0;
        M[newpos+1] = 255;
        M[newpos+2] = 0;
    }
    //printf("seam carved");
    return M;
}


BYTE* getHDisplacementImage1( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
{
    //printf("reached");
    BYTE* M = markHorizontalSeamAbove( Buffer, width, height, xBegin, xEnd,yBegin, yEnd, BoundaryMask, SeamMask);
    //return M;
    int x,y,ymin,val=255,val1=128;
    long newsize =3 * (width) * (height), newpos;
    BYTE* D = new BYTE[newsize];
    memset(D, 0 , newsize);
    bool flag=false;

    for (  x= xBegin; x <= xEnd; x+=3 )
    {
        flag=false;
        for ( y = yBegin; y <= yEnd; y++ )
        {
            newpos = y * 3 * width + x;
            if(flag||(M[newpos]==0 && M[newpos+1]==255 && M[newpos+2]==0))
            {
                flag=true;

                D[newpos]= val1;
                D[newpos+1]= val1;
                D[newpos+2]= val1;
                break;
            }
            else
            {
                D[newpos]= val;
                D[newpos+1]= val;
                D[newpos+2]= val;
            }
        }
    }
    delete [] M;
    return D;

}



BYTE* getHDisplacementImage3( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
{
    BYTE* M = markHorizontalSeamAbove( Buffer, width, height, xBegin, xEnd,yBegin, yEnd, BoundaryMask, SeamMask);
    //return M;
    int x,y,ymin,val=255, val1=128;
    long newsize =3 * (width) * (height), newpos;
    BYTE* D = new BYTE[newsize];
    memset(D, 0 , newsize);
    bool flag=false;

    for (  x= xBegin; x <= xEnd; x+=3 )
    {
        flag=false;
        for ( y = yEnd; y >= yBegin; y-- )
        {
            newpos = y * 3 * width + x;
            if(flag||(M[newpos]==0 && M[newpos+1]==255 && M[newpos+2]==0))
            {
                flag=true;
                D[newpos]= val1;
                D[newpos+1]= val1;
                D[newpos+2]= val1;

                break;
            }
            else
            {
                D[newpos]= val;
                D[newpos+1]= val;
                D[newpos+2]= val;
            }
        }
    }
    delete [] M;
    return D;

}
