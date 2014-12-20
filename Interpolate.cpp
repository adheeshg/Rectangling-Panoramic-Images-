#include <windows.h>
#include <stdio.h>
#include "CGProject.h"


void printMeshOnGuide(BYTE* Buffer, int* mesh, int rows, int cols, int width, int height)
{
    //BYTE* Buffer = new BYTE[3 * (width) * (height)];
    //memset(Buffer,0,3 * (width) * (height));

    int x,y,newpos;
    //printf("\n");
    for(int j=0;j<rows;j++)
    {

        for(int i=0;i<cols;i++)
        {
            //printf("(%d,%d)  ",mesh[(j*cols + i)*2],mesh[(j*cols + i)*2 + 1]);
            x=mesh[(j*cols + i)*2];
            y=mesh[(j*cols + i)*2 + 1];
            newpos = y * 3 * width + x;

            Buffer[newpos] = 255;
            Buffer[newpos+1] = 0;
            Buffer[newpos+2] = 0;

        }
    }

    //delete [] Buffer;
}


 bool isLeft(int bx, int by, int ax, int ay, int cx, int cy){
     by *= -1;
     ay *= -1;
     cy *= -1;
     return ((bx - ax)*(cy - ay) - (by - ay)*(cx - ax)) >= 0;
}

void fillWithT(float X[], int x1, int y1, int x2,int y2, int x3, int y3)
{
    X[0] = x1;
    X[1] = x2;
    X[2] = x3;
    X[3] = 0;

    X[4] = y1;
    X[5] = y2;
    X[6] = y3;
    X[7] = 0;

    X[8] = 1.0;
    X[9] = 1.0;
    X[10] = 1.0;
    X[11] = 0;

    X[12] = 0;
    X[13] = 0;
    X[14] = 0;
    X[15] = 1.0;

}

void getTarget(float A[16], int source[4], int target[2])
{
  int r,c,k;
  source[2] = 1;
  source[3] = 0;
  for (r=0;r<2;r++)
  {
    for (c=0;c<1;c++)
    {
      float x = 0.0;
      for (k= 0;k<4;k++)
      {
          x += A[r*4+k]*source[k]; //((float)Aq[r][k])*partB[k][c];
          //printf("\n%f X %f",A[r*4+k],source[k]);
      }
      //printf("\nx=%f\n",x);
      int x1  = (int)round(x);
      if(r==0)
      {
        x1 /= 3;
        x1 *= 3;
      }
      target[r] = x1;
      //printf ("r=%d, c=%d, x=%d \n", r,c,x );
    }

  }
}

void Affinefverify()
{
    int x1=1,x2=3,x3=6,y1=2,y2=6,y3=9;
    int xx1=21,xx2=26,xx3=31,yy1=5,yy2=10,yy3=9;

    float A1[16];
    float P1[16],Q1[16];

    fillWithT(P1,x1,y1,x2,y2,x3,y3);
    fillWithT(Q1,xx1,yy1,xx2,yy2,xx3,yy3);
    getAffine(A1,P1,Q1);
    int source[4], target[2];
    source[0] = 2;
    source[1] = 4;
    getTarget(A1,source,target);
    printf("\n %d  %d \n",target[0],target[1]);

    source[0] = 3;
    source[1] = 6;
    getTarget(A1,source,target);
    printf("\n %d  %d \n",target[0],target[1]);

}

void process_this_quad(BYTE* Buffer, BYTE* guide, int* imesh, int* dmesh, int rows, int cols, int width, int height, int i, int j)
{
    int x1,x2,x3,x4,y1,y2,y3,y4;
    int xx1,xx2,xx3,xx4,yy1,yy2,yy3,yy4;
  //*********************************************
    x1 = imesh[(j*cols + i)*2];
    y1 = imesh[(j*cols + i)*2 + 1];

    x2 = imesh[(j*cols + i+1)*2];
    y2 = imesh[(j*cols + i+1)*2 + 1];

    x3 = imesh[((j+1)*cols + i)*2];
    y3 = imesh[((j+1)*cols + i)*2 + 1];

    x4 = imesh[((j+1)*cols + i+1)*2];
    y4 = imesh[((j+1)*cols + i+1)*2 + 1];
 //*********************************************
    xx1 = dmesh[(j*cols + i)*2];
    yy1 = dmesh[(j*cols + i)*2 + 1];

    xx2 = dmesh[(j*cols + i+1)*2];
    yy2 = dmesh[(j*cols + i+1)*2 + 1];

    xx3 = dmesh[((j+1)*cols + i)*2];
    yy3 = dmesh[((j+1)*cols + i)*2 + 1];

    xx4 = dmesh[((j+1)*cols + i+1)*2];
    yy4 = dmesh[((j+1)*cols + i+1)*2 + 1];
 //*********************************************

    float A1[16], A2[16];
    float P1[16],P2[16],Q1[16],Q2[16] ;
    int source[4], target[2];
    fillWithT(P1,x1,y1,x2,y2,x3,y3);
    fillWithT(Q1,xx1,yy1,xx2,yy2,xx3,yy3);

    fillWithT(P2,x4,y4,x2,y2,x3,y3);
    fillWithT(Q2,xx4,yy4,xx2,yy2,xx3,yy3);

    getAffine(A1,P1,Q1);
    getAffine(A2,P2,Q2);

//*********************************************
    bool iL21, iL13, iL34, iL42;
    int x,y,xn1,yn1;
    long newpos,newpos1;

    for (y = 0; y < height; y++ )
    {
		for (x= 0; x < 3 * width; x+=3 )
		{
		    //(int bx, int by, int ax, int ay, int cx, int cy)
		    //printf("1 = %d %d, 2 = %d %d, 3 = %d %d, 4=%d %d, this = %d %d",x1,y1,x2,y2,x3,y3,x4,y4,x,y);
		    iL21 = isLeft(x1,y1,x2,y2,x,y);
		    iL13 = isLeft(x3,y3,x1,y1,x,y);
		    iL34 = isLeft(x4,y4,x3,y3,x,y);
		    iL42 = isLeft(x2,y2,x4,y4,x,y);
		    //printf("21 = %d, 13 = %d, 34 = %d, 42 = %d",iL21,iL13,iL34,iL42);
		    if(iL21&&iL13&&iL34&&iL42)
            {
                newpos = y * 3 * width + x;
                source[0] = x;
                source[1] = y;
                if(isLeft(x2,y2,x3,y3,x,y))
                {

                    getTarget(A1,source,target);
                    xn1 = target[0]<0?0:target[0];
                    xn1=target[0]>=(3*width)?(3*width-3):target[0];
                    yn1 = target[1]<0?0:target[1];
                    yn1=target[1]>=height?height-1:target[1];

                    newpos1 = yn1 * 3 * width + xn1;

                    guide[newpos] = Buffer[newpos1];
                    guide[newpos+1] = Buffer[newpos1+1];
                    guide[newpos+2] = Buffer[newpos1+2];

                }
                else
                {
                    getTarget(A2,source,target);
                    xn1 = target[0]<0?0:target[0];
                    xn1=target[0]>=(3*width)?(3*width-3):target[0];
                    yn1 = target[1]<0?0:target[1];
                    yn1=target[1]>=height?height-1:target[1];

                    newpos1 = yn1 * 3 * width + xn1;

                    guide[newpos] = Buffer[newpos1];
                    guide[newpos+1] = Buffer[newpos1+1];
                    guide[newpos+2] = Buffer[newpos1+2];

                }
		    }

		}
    }
}








void interpolate(BYTE* Buffer, int* imesh, int* dmesh, int rows, int cols, int width, int height, char * name)
{

    //saveAsImage(Buffer, width, height, strcat(name,"iip.bmp"));
    //name[14]='\0';
    BYTE* guide = new BYTE[3 * (width) * (height)];
    long newsize = 3 * (width) * (height);
    memset(guide,0,newsize);
    //printMeshOnGuide(guide,imesh,rows,cols,width, height);
    for(int j=0; j<rows-1; j++){
        for (int i=0; i<cols-1; i++){
            //printf("i=%d j=%d",i,j);
            process_this_quad(Buffer,guide,imesh,dmesh,rows,cols,width, height,i,j);
        }
    }


    //saveAsImage(guide, width, height, strcat(name,"z40done.bmp"));
    name[14]='\0';

    BufCopy(Buffer,guide,width,height);
    //saveAsImage(Buffer, width, height, strcat(name,"z50output.bmp"));
    //name[14]='\0';

     //Affinefverify();
}
