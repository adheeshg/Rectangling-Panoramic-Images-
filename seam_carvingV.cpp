#include <windows.h>
#include <stdio.h>
#include "CGProject.h"



BYTE* markVerticalSeamLeft( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask)
{
    int x,y,xmin,xmax;
    long newsize =3 * (width) * (height), newpos, posa,posb,posc;//newposi_1j_1, newposij_1, newposi1j_1;
    BYTE Ma, Mb, Mc, Mmin, MM;
    BYTE* M = new BYTE[newsize];

    BufCopy(M,Buffer,width, height);


    //cumulative energy calculation
    //return M;
    Mmin = 255;
    xmin=xBegin + rand()%xEnd;
    for ( y = yEnd-1; y >= yBegin; y-- )
    {
        for ( x= xBegin; x <= xEnd; x+=3 )
        {
                newpos = y * 3 * width + x;
                if(isBoundary(M,newpos)){
                    continue;
                }
                posb = newpos + 3 * width;
                posa = posb - 3 ;
                posc = posb + 3 ;

                Ma = (x==0)?255:M[posa];
                Mb = M[posb];
                Mc = (x==(width-3))?255:M[posc];

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
                if(y==yBegin)
                {
                    //printf("MM=%d,y=%d\n",MM,xmin);
                    if(MM<Mmin)
                    {
                        //printf("changing Mmin MM=%d,Mmin=%d\n",MM,Mmin);
                        Mmin = MM;
                        xmin = x;
                    }
                }
                //printf("M set = %d \n",MM);
        }

    }
    //printf("xmin=%d",xmin);
    //printf("cum energy found");
    //return M;
    BufImpose(M,M,BoundaryMask,width,height);
    //find seed to start finding the seam.
    y=yBegin;
    newpos = y * 3 * width + xmin;
    M[newpos] = 0;
    M[newpos+1] = 255;
    M[newpos+2] = 0;

    //printf("seam seed found\n");
    //return M;
    while(y<yEnd && xmin>0)
    {
        //xmax = y>1720?printf(""):
        x=xmin;
        newpos = y * 3 * width + x;

        posb = newpos + 3 * width;
        posa = posb - 3 ;
        posc = posb + 3 ;

        Ma = (y==0)?255:M[posa];
        Mb = M[posb];
        Mc = (y==(height-1))?255:M[posc];


        if(Ma<=Mb)
        {
            if(Ma<=Mc) {xmin=x?(x-3):0;}
            else {xmin = xmin%width?(xmin+3):0;}
        }
        else
        {
            if(Mb<=Mc) {xmin = xmin;}
            else {xmin = xmin%width?(xmin+3):0;}
        }
        y++;
        newpos = y * 3 * width + xmin;
        //printf("xmin= %d, y=%d\n",xmin,y);
        M[newpos] = 0;
        M[newpos+1] = 255;
        M[newpos+2] = 0;
    }
    //printf("seam carved\n");
    return M;
}

BYTE* markHorizontalSeamBelowxx (BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask)
{
    int x,y,ymin;
    long newsize =3 * (width) * (height), newpos, posa,posb,posc;//newposi_1j_1, newposij_1, newposi1j_1;
    BYTE Ma, Mb, Mc, Mmin, MM;
    BYTE* M = new BYTE[newsize];

    BufCopy(M,Buffer,width, height);


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


BYTE* getVDisplacementImage2( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
{
    BYTE* M = markVerticalSeamLeft( Buffer, width, height, xBegin, xEnd,yBegin, yEnd, BoundaryMask);
    //printf("found one seam\n");
    //return M;
    int x,y,ymin,val=255,val1=128;
    long newsize =3 * (width) * (height), newpos;
    BYTE* D = new BYTE[newsize];
    memset(D, 0 , newsize);
    bool flag=false;

    for ( y = yBegin; y <= yEnd; y++ )
    {
        flag=false;
        for (  x= xBegin ; x <= xEnd; x+=3 )
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


BYTE* getVDisplacementImage4( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
{
    BYTE* M = markVerticalSeamLeft( Buffer, width, height, xBegin, xEnd,yBegin, yEnd, BoundaryMask);
    //printf("found one seam\n");
    //return M;
    int x,y,ymin,val=255,val1=128;
    long newsize =3 * (width) * (height), newpos;
    BYTE* D = new BYTE[newsize];
    memset(D, 0 , newsize);
    bool flag=false;

    for ( y = yBegin; y <= yEnd; y++ )
    {
        flag=false;
        for (  x= xEnd ; x >= xBegin; x-=3 )
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



