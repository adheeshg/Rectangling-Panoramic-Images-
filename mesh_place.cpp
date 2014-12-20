#include "CGProject.h"
#include <math.h>

void hplace_mesh_v0(BYTE* Buffer, int width, int height)
{
    int hmesh_beg,hmesh_end,hmesh_delta;
    int vmesh_beg,vmesh_end,vmesh_delta;
    int margin = 5;
    width = width - 2*margin;
    height = height - 2*margin;

    hmesh_delta = (sqrt(height)*sqrt(width))/20;
    vmesh_delta = (sqrt(height)*sqrt(width))/20;

    width = width + 2*margin;
    height = height + 2*margin;
    hmesh_beg = margin;
    hmesh_end = height - margin;
    //vmesh_beg = margin*3;
    vmesh_end = width - margin;

    int x=1000,y,newpos;

    for ( y = hmesh_beg; y <= hmesh_end ; y+= hmesh_delta ){}
    hmesh_beg += (hmesh_end - (y-hmesh_delta))/2;
    hmesh_end = (hmesh_end + (y-hmesh_delta))/2;


    for ( x= margin; x <= vmesh_end; x+=vmesh_delta){}
    vmesh_beg = (margin + (vmesh_end - (x-vmesh_delta))/2)*3;
    vmesh_end = (vmesh_end + (x-vmesh_delta))/2;

    //hmesh_end = y-hmesh_delta;
    //vmesh_end = x-(3*vmesh_delta);


    for ( y = hmesh_beg; y <= hmesh_end ; y+= hmesh_delta )
        //for ( x= 0; x < 3 * width; x+=3 )
		for ( x= vmesh_beg; x <= (3 * vmesh_end); x+=3 )
		{

            newpos = y * 3 * width + x;
            Buffer[newpos] = 0;
            Buffer[newpos+1] = 255;
            Buffer[newpos+2] = 0;
		}

    for ( y = hmesh_beg; y <= hmesh_end ; y+= 1 )
        //for ( x= 0; x < 3 * width; x+=3 )
		for ( x= vmesh_beg; x <= (3 * vmesh_end); x+=(3*vmesh_delta) )
		{

            newpos = y * 3 * width + x;
            Buffer[newpos] = 0;
            Buffer[newpos+1] = 255;
            Buffer[newpos+2] = 0;
		}

    for ( y = hmesh_beg; y <= hmesh_end ; y+= hmesh_delta )
        //for ( x= 0; x < 3 * width; x+=3 )
		for ( x= vmesh_beg; x <= (3 * vmesh_end); x+=(3*vmesh_delta) )
		{

            newpos = y * 3 * width + x;
            Buffer[newpos] = 255;
            Buffer[newpos+1] = 0;
            Buffer[newpos+2] = 0;
		}
}


void hplace_mesh(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp,  BYTE* temp)
{
    int hmesh_beg,hmesh_end,hmesh_delta;
    int vmesh_beg,vmesh_end,vmesh_delta;
    int margin = 0;
    width = width - 2*margin;
    height = height - 2*margin;

    hmesh_delta = (sqrt(height)*sqrt(width))/9;
    vmesh_delta = (sqrt(height)*sqrt(width))/9;

    width = width + 2*margin;
    height = height + 2*margin;
    hmesh_beg = margin;
    hmesh_end = height - margin;
    //vmesh_beg = margin*3;
    vmesh_end = width - margin;

    int x=1000,y,ynew,newpos, newpos_nextline;

    for ( y = hmesh_beg; y <= hmesh_end ; y+= hmesh_delta ){}
    hmesh_beg += (hmesh_end - (y-hmesh_delta))/2;
    hmesh_end = (hmesh_end + (y-hmesh_delta))/2;


    for ( x= margin; x <= vmesh_end; x+=vmesh_delta){}
    vmesh_beg = (margin + (vmesh_end - (x-vmesh_delta))/2)*3;
    vmesh_end = (vmesh_end + (x-vmesh_delta))/2;

    //hmesh_end = y-hmesh_delta;
    //vmesh_end = x-(3*vmesh_delta);


    for ( y = hmesh_beg; y <= hmesh_end ; y+= hmesh_delta )
        //for ( x= 0; x < 3 * width; x+=3 )
		for ( x= vmesh_beg; x <= (3 * vmesh_end); x+=3 )
		{

            newpos = y * 3 * width + x;

            ynew = (y+Vdisp[newpos])>=height?height-1:(y+Vdisp[newpos]);
            //printf("width = %d, height = %d\n", width, height);
            //printf("for newpos_newline x = %d, y = %d \n", (x + Hdisp[newpos]), ynew);
			newpos_nextline = ynew * 3 * width + x + Hdisp[newpos];

            /*Buffer[newpos] =  128*y/(hmesh_end) + 64;
            Buffer[newpos+1] = 50*y/(hmesh_end);
            Buffer[newpos+2] = 50*y/(hmesh_end);

            temp[newpos_nextline] = 128*y/(hmesh_end) + 64;
            temp[newpos_nextline+1] = 50*y/(hmesh_end);
            temp[newpos_nextline+2] = 50*y/(hmesh_end);*/

            Buffer[newpos] =  0;
            Buffer[newpos+1] = 255;
            Buffer[newpos+2] = 0;

            temp[newpos_nextline] = 0;
            temp[newpos_nextline+1] = 255;
            temp[newpos_nextline+2] = 0;
		}

    for ( y = hmesh_beg; y <= hmesh_end ; y+= 1 )
        //for ( x= 0; x < 3 * width; x+=3 )
		for ( x= vmesh_beg; x <= (3 * vmesh_end); x+=(3*vmesh_delta) )
		{

            newpos = y * 3 * width + x;
            ynew = (y+Vdisp[newpos])>=height?height-1:(y+Vdisp[newpos]);
            //printf("width = %d, height = %d\n", width, height);
            //printf("for newpos_newline x = %d, y = %d \n", (x + Hdisp[newpos]), ynew);
			newpos_nextline = ynew * 3 * width + x + Hdisp[newpos];

            /*Buffer[newpos] = 120;
            Buffer[newpos+1] = 128*x/(3*vmesh_end) + 64;
            Buffer[newpos+2] = 0;

            temp[newpos_nextline] = 120;
            temp[newpos_nextline+1] = 128*x/(3*vmesh_end) + 64;
            temp[newpos_nextline+2] = 0;*/

            Buffer[newpos] =  0;
            Buffer[newpos+1] = 255;
            Buffer[newpos+2] = 0;

            temp[newpos_nextline] = 0;
            temp[newpos_nextline+1] = 255;
            temp[newpos_nextline+2] = 0;
		}

    for ( y = hmesh_beg; y <= hmesh_end ; y+= hmesh_delta )
        //for ( x= 0; x < 3 * width; x+=3 )
		for ( x= vmesh_beg; x <= (3 * vmesh_end); x+=(3*vmesh_delta) )
		{

            newpos = y * 3 * width + x;
            ynew = (y+Vdisp[newpos])>=height?height-1:(y+Vdisp[newpos]);
            //printf("width = %d, height = %d\n", width, height);
            //printf("for newpos_newline x = %d, y = %d \n", (x + Hdisp[newpos]), ynew);
			newpos_nextline = ynew * 3 * width + x + Hdisp[newpos];

            Buffer[newpos] = 255;
            Buffer[newpos+1] = 0;
            Buffer[newpos+2] = 0;

            temp[newpos_nextline] = 255;
            temp[newpos_nextline+1] = 0;
            temp[newpos_nextline+2] = 0;
		}
}

