#include "CGProject.h"

bool isBoundary(BYTE * Buffer, long newpos){
if(Buffer[newpos]>249 && Buffer[newpos+1]>249 && Buffer[newpos+2]>249){
    return true;
}
else
    return false;
}

void BufCopy(BYTE* BufD, BYTE* BufS, int width, int height)
{
    int x,y;
    long newpos;

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
			BufD[newpos] = BufS[newpos];
			BufD[newpos+1] = BufS[newpos+1];
			BufD[newpos+2] = BufS[newpos+2];
		}
}


void BufAvg(BYTE* Res, BYTE* Buf1, BYTE* Buf2, int width, int height)
{
    int x,y;
    long newpos;

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
			Res[newpos] = (Buf1[newpos] + Buf2[newpos])/2;
			Res[newpos + 1] = (Buf1[newpos+1] + Buf2[newpos+1])/2;
			Res[newpos + 2] = (Buf1[newpos+2] + Buf2[newpos+2])/2;
		}
}

void BufImpose(BYTE* Res, BYTE* Buf1, BYTE* Mask, int width, int height)
{
    int x,y;
    long newpos;

    for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;
			if (isBoundary(Mask,newpos))
            {
                Res[newpos] = 255;
                Res[newpos + 1] = 255;
                Res[newpos + 2] = 255;
            }
            else
            {
                Res[newpos] = Buf1[newpos];
                Res[newpos + 1] = Buf1[newpos+1];
                Res[newpos + 2] = Buf1[newpos+2];
            }
		}
}

void removeRed( BYTE* Buffer, int width, int height )
{   int y,x;
    long newpos = 0;
	for ( y = 0; y < height; y++ )
		for ( x= 0; x < 3 * width; x+=3 )
		{
			newpos = y * 3 * width + x;

			Buffer[newpos] = Buffer[newpos]*0; //red
			Buffer[newpos + 1] = Buffer[newpos+1]; //green
			Buffer[newpos + 2] = Buffer[newpos+2]; //blue
		}
}


void markLeftBoundary( BYTE* Buffer, int width, int height )
{
    int y,x;
    long newpos = 0;

    x=0; //left bounadary
    for ( y = 0; y < height; y++ ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }
}

void getLargestLeftBoundarySegment(BYTE* Buffer, int width, int height, int *yBegin, int *yEnd, int *maxlen)
{
    int y,x, yBeginTemp=-1, yEndTemp=-1, len = 0;
    *maxlen=0;
    long newpos = 0;

    x=0; //left bounadary
    for ( y = 0; y < height; y++ ){
        newpos = y * 3 * width + x;

        if(isBoundary(Buffer,newpos)){
            if(len==0){
                yBeginTemp = y;
                yEndTemp = y;
            }
            else{
                yEndTemp = y;
            }
            len++;
        }
        else{
            len = 0;
        }

        if(len>(*maxlen)){
            *maxlen = len;
            *yBegin = yBeginTemp;
            *yEnd = yEndTemp;
        }
    }

    if(yBeginTemp==-1){
        return;
    }
    //paint it
    /*for ( y = *yBegin; y <= *yEnd; y++ ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }*/
}


void markRightBoundary( BYTE* Buffer, int width, int height )
{
    int y,x;
    long newpos = 0;

    x=3 * width - 3; //right bounadary
    for ( y = 0; y < height; y++ ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }
}


void getLargestRightBoundarySegment(BYTE* Buffer, int width, int height, int *yBegin, int *yEnd, int *maxlen)
{
    int y,x, yBeginTemp=-1, yEndTemp=-1, len = 0;
    *maxlen=0;
    long newpos = 0;

    x=3 * width - 3; //right bounadary
    for ( y = 0; y < height; y++ ){
        newpos = y * 3 * width + x;

        if(isBoundary(Buffer,newpos)){
            if(len==0){
                yBeginTemp = y;
                yEndTemp = y;
            }
            else{
                yEndTemp = y;
            }
            len++;
        }
        else{
            len = 0;
        }

        if(len>(*maxlen)){
            *maxlen = len;
            *yBegin = yBeginTemp;
            *yEnd = yEndTemp;
        }
    }

    if(yBeginTemp==-1){
        return;
    }
    //paint it
    /*for ( y = *yBegin; y <= *yEnd; y++ ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }*/
}

void markTopBoundary( BYTE* Buffer, int width, int height )
{
    int y,x;
    long newpos = 0;

    y=0; //top bounadary
    for ( x= 0; x < 3 * width; x+=3 ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }
}


void getLargestTopBoundarySegment(BYTE* Buffer, int width, int height, int *xBegin, int *xEnd, int *maxlen)
{
    int y,x, xBeginTemp=-1, xEndTemp=-1, len = 0;
    *maxlen=0;
    long newpos = 0;

    y=0;//top bounadary
    for ( x= 0; x < 3 * width; x+=3 ){
        newpos = y * 3 * width + x;

        if(isBoundary(Buffer,newpos)){
            if(len==0){
                xBeginTemp = x;
                xEndTemp = x;
            }
            else{
                xEndTemp = x;
            }
            len++;
        }
        else{
            len = 0;
        }

        if(len>(*maxlen)){
            *maxlen = len;
            *xBegin = xBeginTemp;
            *xEnd = xEndTemp;
        }
    }

    if(xBeginTemp==-1){
        return;
    }
    //paint it
    /*for ( x= *xBegin; x <= *xEnd; x+=3 ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }*/
}


void markBottomBoundary( BYTE* Buffer, int width, int height )
{
    int y,x;
    long newpos = 0;

    y=height-1; //bottom bounadary
    for ( x= 0; x < 3 * width; x+=3 ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    }
}


void getLargestBottomBoundarySegment(BYTE* Buffer, int width, int height, int *xBegin, int *xEnd, int *maxlen)
{
    int y,x, xBeginTemp=-1, xEndTemp=-1, len = 0;
    *maxlen=0;
    long newpos = 0;

    y=height-1;//top bounadary
    for ( x= 0; x < 3 * width; x+=3 ){
        newpos = y * 3 * width + x;

        if(isBoundary(Buffer,newpos)){
            if(len==0){
                xBeginTemp = x;
                xEndTemp = x;
            }
            else{
                xEndTemp = x;
            }
            len++;
        }
        else{
            len = 0;
        }

        if(len>(*maxlen)){
            *maxlen = len;
            *xBegin = xBeginTemp;
            *xEnd = xEndTemp;
        }
    }

    if(xBeginTemp==-1){
        return;
    }
    //paint it
   /* for ( x= *xBegin; x <= *xEnd; x+=3 ){
        newpos = y * 3 * width + x;
        //mark only if its empty
        if(isBoundary(Buffer,newpos)){
            Buffer[newpos] = 255; //red
            Buffer[newpos + 1] = Buffer[newpos+1]*0; //green
            Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
        }
    } */
}


void markSectionBoundary( BYTE* Buffer, int xBegin, int xEnd, int yBegin, int yEnd, int tWidth )
{   int y,x;
    long newpos = 0;
	for ( y = yBegin; y <= yEnd; y++ )
		for ( x= xBegin; x <= xEnd; x+=3 )
		{
			newpos = y * 3 * tWidth + x;

			Buffer[newpos] = 0; //red
			Buffer[newpos + 1] = 255; //green
			Buffer[newpos + 2] = Buffer[newpos+2]*0; //blue
		}
}

void markSection( BYTE* Buffer, int xBegin, int xEnd, int yBegin, int yEnd, int tWidth )
{
    markSectionBoundary( Buffer,xBegin,xEnd,yBegin,yBegin,tWidth );
    markSectionBoundary( Buffer,xBegin,xEnd,yEnd,yEnd,tWidth );
    markSectionBoundary( Buffer,xBegin,xBegin,yBegin,yEnd,tWidth );
    markSectionBoundary( Buffer,xEnd,xEnd,yBegin,yEnd,tWidth );

}
void markAllBoundaries( BYTE* Buffer, int width, int height )
{
    markTopBoundary(Buffer, width, height );
    markBottomBoundary(Buffer, width, height );
    markLeftBoundary(Buffer, width, height );
    markRightBoundary(Buffer, width, height );
}

void markSegmentforLargestBoundary( BYTE* Buffer, int width, int height )
{
    int dBegin=-1, dEnd=-1, yBegin=-1, yEnd=-1, xBegin=-1, xEnd=-1, maxlen=0,len=0;

    //left
    getLargestLeftBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len);
    if (len>maxlen){
        yBegin = dBegin;
        yEnd = dEnd;
        maxlen = len;
        xBegin = 0;
        xEnd = 3*width - 3;
    }

    //right
    dBegin=-1;
    dEnd=-1;
    getLargestRightBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len );
    if (len>maxlen){
        yBegin = dBegin;
        yEnd = dEnd;
        maxlen = len;
        xBegin = 0;
        xEnd =  3*width - 3;
    }
    //markSection(Buffer,xBegin,xEnd,yBegin,yEnd,width);

    //top
    dBegin=-1;
    dEnd=-1;
    getLargestTopBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len );
    if (len>maxlen){
        xBegin = dBegin;
        xEnd = dEnd;
        maxlen = len;
        yBegin = 0;
        yEnd = height-1;
    }

    //bottom
    dBegin=-1;
    dEnd=-1;
    getLargestBottomBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len );
    if (len>maxlen){
        xBegin = dBegin;
        xEnd = dEnd;
        maxlen = len;
        yBegin = 0;
        yEnd = height-1;
    }

    //markAllBoundaries(Buffer, width, height );
    markSection(Buffer,xBegin,xEnd,yBegin,yEnd,width);

}

void getSegmentforLargestBoundary( BYTE* Buffer, int width, int height, int *xStart, int *xFin, int *yStart, int *yFin, int *tLen, int *dir )
{
    int dBegin=-1, dEnd=-1, yBegin=-1, yEnd=-1, xBegin=-1, xEnd=-1, maxlen=0,len=0;
	*tLen = 0 ;

    //left
    getLargestLeftBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len);
    if (len>maxlen){
        yBegin = dBegin;
        yEnd = dEnd;
        maxlen = len;
        xBegin = 0;
        xEnd = 3*width - 3;
        *dir = 2;
    }

    //right
    dBegin=-1;
    dEnd=-1;
    getLargestRightBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len );
    if (len>maxlen){
        yBegin = dBegin;
        yEnd = dEnd;
        maxlen = len;
        xBegin = 0;
        xEnd =  3*width - 3;
        *dir = 4;
    }
    //markSection(Buffer,xBegin,xEnd,yBegin,yEnd,width);

    //top
    dBegin=-1;
    dEnd=-1;
    getLargestTopBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len );
    if (len>maxlen){
        xBegin = dBegin;
        xEnd = dEnd;
        maxlen = len;
        yBegin = 0;
        yEnd = height-1;
        *dir = 1;
    }

    //bottom
    dBegin=-1;
    dEnd=-1;
    getLargestBottomBoundarySegment(Buffer, width, height, &dBegin, &dEnd, &len );
    if (len>maxlen){
        xBegin = dBegin;
        xEnd = dEnd;
        maxlen = len;
        yBegin = 0;
        yEnd = height-1;
        *dir = 3;
    }

    //markAllBoundaries(Buffer, width, height );
    //markSection(Buffer,xBegin,xEnd,yBegin,yEnd,width);
	*xStart = xBegin;
	*xFin = xEnd;
	*yStart = yBegin;
	*yFin = yEnd;
	*tLen = maxlen;

}




void removeExtraLeftBoundary( BYTE* Buffer, int *width, int *height )
{
    int y,x, w=*width, h=*height;
    long newpos, newpos1;
	for ( y = 0; y < h; y++ )
		for ( x= 0; x < 3 * w - 3; x+=3 )
		{
			newpos = y * 3 * w + x;
            newpos1= y * 3 * w + x +3;
			Buffer[newpos] = Buffer[newpos1]; //red
			Buffer[newpos + 1] = Buffer[newpos1+1]; //green
			Buffer[newpos + 2] = Buffer[newpos1+2]; //blue
		}
    //*width = w-1;
}

void removeExtraTopBoundary( BYTE* Buffer, int *width, int *height )
{
    int y,x, w=*width, h=*height;
    long newpos, newpos1;
	for ( y = 0; y < h - 1; y++ )
		for ( x= 0; x < 3 * w ; x+=3 )
		{
			newpos = y * 3 * w + x;
            newpos1= (y+1) * 3 * w + x;
			Buffer[newpos] = Buffer[newpos1]; //red
			Buffer[newpos + 1] = Buffer[newpos1+1]; //green
			Buffer[newpos + 2] = Buffer[newpos1+2]; //blue
		}
    //*height = h - 1;
}


void isLargestRightBoundarySegment(BYTE* Buffer, int width, int height, int *yBegin, int *yEnd, int *maxlen, int checkAt)
{
    int y, yBeginTemp=-1, yEndTemp=-1, len = 0;
    *maxlen=0;
    long newpos = 0;


    for ( y = 0; y < height; y++ ){
        newpos = y * 3 * width + 3*checkAt;

        if(isBoundary(Buffer,newpos)){
            if(len==0){
                yBeginTemp = y;
                yEndTemp = y;
            }
            else{
                yEndTemp = y;
            }
            len++;
        }
        else{
            len = 0;
        }

        if(len>(*maxlen)){
            *maxlen = len;
            *yBegin = yBeginTemp;
            *yEnd = yEndTemp;
        }
    }
}

void removeExtraBoundaries( BYTE* Buffer, int *width, int *height )
{
    int dBegin=-1, dEnd=-1, len=0, h=*height, w=*width, i, j;

    //take it to top
    for(i=0; i<h; i++)
    {
        getLargestTopBoundarySegment(Buffer, *width, *height, &dBegin, &dEnd, &len);
        //printf("got len = %d \n", len);
        if (len==w){
            removeExtraTopBoundary(Buffer, width, height );
        }
        else{
            break;
        }
    }
    //printf("reduced height by = %d \n", i);

    //take it to left
    for(j=0; j<w; j++)
    {
        getLargestLeftBoundarySegment(Buffer, *width, *height, &dBegin, &dEnd, &len);
        //printf("got len = %d \n", len);
        if (len==h){
            removeExtraLeftBoundary(Buffer, width, height );
        }
        else{
            break;
        }
    }
    //printf("reduced width by = %d \n", j);


    //chop below
    for(i=h; i>0; i--)
    {
        getLargestBottomBoundarySegment(Buffer, *width, i, &dBegin, &dEnd, &len);
        //printf("got len = %d \n", len);
        if(len<w)
        {
            //printf("setting the height to = %d \n", i);
            *height = i;
            h=i;
            break;
        }
    }

    //chop from right
   for(j=w-1; j>0; j--)
    {
        isLargestRightBoundarySegment(Buffer, *width, *height, &dBegin, &dEnd, &len, j);
        //printf("got len = %d \n", len);
        if (len<h){
            //printf("tentatively setting the width to = %d \n", j);
            *width = j;
            w=j;
            break;
        }
    }
    /*while((*width)%4!=0){
        (*width) = (*width) - 1;
    }*/
    //(*width) = (*width) - 2;
    //printf("setting the width to = %d \n", (*width));
}


void getBoundaryMap(BYTE* Buffer, int width, int height, BYTE* newbuf)
{
    int x,y,xBegin = 0, xEnd = width, yBegin= 0 , yEnd=height;
    long newsize = 3 * (width) * (height), newpos = 0;

    //BYTE* newbuf = new BYTE[newsize];
    BYTE* newbuf1 = new BYTE[newsize];
    BYTE* newbuf2 = new BYTE[newsize];
    memset ( newbuf, 0, newsize );

    while((xBegin<xEnd) && (yBegin<yEnd))
    {
        //top
        y=yBegin;
        for(x=xBegin;x< 3 * xEnd;x+=3)
        {
            newpos = y * 3 * width + x;
            //printf("x= %d, y=%d\n",x,y);
            if(isBoundary(Buffer,newpos))
            {
                newbuf[newpos] = 255;
                newbuf[newpos+1] = 255;
                newbuf[newpos+2] = 255;
            }

        }
        yBegin++;
        //right
        x=3 * xEnd - 3;
        for(y=yBegin;y<yEnd;y++)
        {
            newpos = y * 3 * width + x;
            //printf("x= %d, y=%d\n",x,y);
            if(isBoundary(Buffer,newpos))
            {
                newbuf[newpos] = 255;
                newbuf[newpos+1] = 255;
                newbuf[newpos+2] = 255;
            }
        }
        xEnd--;
        //bottom
        y=yEnd-1;
        for(x=3 * xEnd - 3;x>=xBegin;x-=3)
        {
            newpos = y * 3 * width + x;
            //printf("x= %d, y=%d\n",x,y);
            if(isBoundary(Buffer,newpos))
            {
                newbuf[newpos] = 255;
                newbuf[newpos+1] = 255;
                newbuf[newpos+2] = 255;
            }
        }
        yEnd--;
        //left
        x=xBegin;
        for(y=yEnd-1;y>=yBegin;y--)
        {
            newpos = y * 3 * width + x;
            //printf("x= %d, y=%d\n",x,y);
            if(isBoundary(Buffer,newpos))
            {
                newbuf[newpos] = 255;
                newbuf[newpos+1] = 255;
                newbuf[newpos+2] = 255;
            }
        }
        xBegin+=3;
    }

    BufCopy(newbuf1,newbuf,width,height);
    BufCopy(newbuf2,newbuf,width,height);
    for ( y = 1; y < height-1; y++ )
		for ( x= 3; x < 3 * width-3; x+=3 )
		{
			newpos = y * 3 * width + x;
			long newpos_10 = (y-1) * 3 * width + x;
			long newpos0_1 = y* 3 * width + x-3;
			long newpos10 = (y+1) * 3 * width + x;
			long newpos01 = y* 3 * width + x+3;

			if(isBoundary(newbuf1,newpos))
            {
                int val = (isBoundary(newbuf1,newpos_10)?1:0)+(isBoundary(newbuf1,newpos0_1)?1:0)+(isBoundary(newbuf1,newpos10)?1:0)+(isBoundary(newbuf1,newpos01)?1:0);
                if(val<=2)
                {
                    newbuf1[newpos] = 0;
                    newbuf1[newpos+1] = 0;
                    newbuf1[newpos+2] = 0;
                }
            }
		}

    for ( y = height-2; y > 0 ; y-- )
		for ( x= 3 * width-6; x >0 ; x-=3 )
		{
			newpos = y * 3 * width + x;
			long newpos_10 = (y-1) * 3 * width + x;
			long newpos0_1 = y* 3 * width + x-3;
			long newpos10 = (y+1) * 3 * width + x;
			long newpos01 = y* 3 * width + x+3;

			if(isBoundary(newbuf2,newpos))
            {
                int val = (isBoundary(newbuf2,newpos_10)?1:0)+(isBoundary(newbuf2,newpos0_1)?1:0)+(isBoundary(newbuf2,newpos10)?1:0)+(isBoundary(newbuf2,newpos01)?1:0);
                if(val<=2)
                {
                    newbuf2[newpos] = 0;
                    newbuf2[newpos+1] = 0;
                    newbuf2[newpos+2] = 0;
                }
            }
		}

    BufAvg(newbuf,newbuf1,newbuf2,width,height);
    delete [] newbuf1;
    delete [] newbuf2;

    for ( y = 1; y < height-1; y++ )
		for ( x= 3; x < 3 * width-3; x+=3 )
		{
			newpos = y * 3 * width + x;
			if (!(newbuf[newpos] == 0 && newbuf[newpos+1] == 0 && newbuf[newpos+2] == 0))
            {
                    newbuf[newpos] = 255;
                    newbuf[newpos+1] = 255;
                    newbuf[newpos+2] = 255;
            }
		}


    //return newbuf;
}
