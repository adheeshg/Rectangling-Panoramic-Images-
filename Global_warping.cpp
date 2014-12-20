

#include <windows.h>
#include <stdio.h>
#include "CGProject.h"

void displayMesh(int* mesh, int rows, int cols)
{
    printf("\n");
    for(int j=0;j<rows;j++)
    {
        for(int i=0;i<cols;i++)
        {
            printf("(%d,%d)  ",mesh[(j*cols + i)*2],mesh[(j*cols + i)*2 + 1]);
        }
        printf("\n");
    }
}


void printMesh(int* mesh, int rows, int cols, int width, int height, char * name)
{
    BYTE* Buffer = new BYTE[3 * (width) * (height)];
    memset(Buffer,0,3 * (width) * (height));

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
    saveAsImage(Buffer, width, height, name);
    delete [] Buffer;
}


void global_warping(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, char* output)
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
    hmesh_end = height - margin;
    vmesh_end = width - margin;

    int x,y,ynew,newpos, newpos_nextline,rows=0,cols=0;

    for ( y = margin; y <= hmesh_end ; y+= hmesh_delta, rows++ ){}
    hmesh_beg = margin + (hmesh_end - (y-hmesh_delta))/2;
    hmesh_end = (hmesh_end + (y-hmesh_delta))/2;


    for ( x= margin; x <= vmesh_end; x+=vmesh_delta, cols++){}
    vmesh_beg = (margin + (vmesh_end - (x-vmesh_delta))/2)*3;
    vmesh_end = (vmesh_end + (x-vmesh_delta))/2;

    printf("rows=%d, cols=%d",rows,cols);
    int dmesh[rows*cols*2], imesh[rows*cols*2],i,j;
    for ( y = hmesh_beg,j=0 ; y <= hmesh_end ; y+= hmesh_delta,j++ )
		for ( x= vmesh_beg, i=0; x <= (3 * vmesh_end); x+=(3*vmesh_delta), i++ )
		{

            newpos = y * 3 * width + x;
            ynew = (y+Vdisp[newpos])>=height?height-1:(y+Vdisp[newpos]);
			newpos_nextline = ynew * 3 * width + x + Hdisp[newpos];
            imesh[(j*cols + i)*2] = x;
            imesh[(j*cols + i)*2 + 1] = y;

            dmesh[(j*cols + i)*2] =  x + Hdisp[newpos];
            dmesh[(j*cols + i)*2 + 1] = ynew;
		}

    //printMesh(imesh,rows,cols,width, height, strcat(output,"z12init.bmp"));
    output[14]='\0';
    //displayMesh(imesh,rows,cols);
    //printMesh(dmesh,rows,cols,width, height, strcat(output,"z22dist.bmp"));
    output[14]='\0';
    //displayMesh(dmesh,rows,cols);
    for(int x=0;x<50;x++)
    {
        //printf("\niteration=%x",x);
        getNewMesh(imesh,dmesh,rows,cols,width, height);
    }

    //printMesh(imesh,rows,cols,width, height, strcat(output,"z30fin.bmp"));
    //displayMesh(imesh,rows,cols);
    output[14]='\0';


    interpolate(Buffer, imesh, dmesh, rows, cols, width, height, output);

}

void imposeBoundary(int* mesh, int rows, int cols, int width, int height)
{
    int j=0,i=0;
    for(i=0;i<cols;i++)
    {
       mesh[(j*cols + i)*2 + 1] = 0;
    }
    j=rows-1;
    for(i=0;i<cols;i++)
    {
       mesh[(j*cols + i)*2 + 1] = height-1;
    }

    i=0;
    for(j=0;j<rows;j++)
    {
       mesh[(j*cols + i)*2] = 0;
    }

    i=cols-1;
    for(j=0;j<rows;j++)
    {
       mesh[(j*cols + i)*2] = (width-1)*3;
    }


}

float matEi(float Cpi[8][8], int Vi[8])
{
  int r,c,k;
  float res=0.0;

  //printf("\nCpi\n");
  //display88float(Cpi);
  for (r=0;r<8;r++)
  {
    Cpi[r][r] -= 1.0;
  }
  //printf("\nCpi\n");
  //display88float(Cpi);

   /*printf("\nVi\n");
    for (int i=0;i<8;i++)
    {
        printf("\t%d",Vi[i]);
    }*/


  for (r=0;r<8;r++)
  {
      float x = 0.0;

      for (k= 0;k<8;k++)
      {
          //printf("\nr=%d k=%d Cpi=%f V=%d",r,k,Cpi[r][k],Vi[k]);
          x += Cpi[r][k]*((float)Vi[k]);
          //printf("\nx=%f\n",x);
      }
      res += x*x;
  }

  return res;
}

float getEnregyi(int i, int j, int* imesh, int* dmesh, int cols)
{
    int Cpi[8],Vi[8] ;
    float op[8][8];
            //this-(left-top)
            Cpi[0] = dmesh[(j*cols + i)*2];
            Cpi[1] = dmesh[(j*cols + i)*2 + 1];
            //right-top
            Cpi[2] = dmesh[(j*cols + i+1)*2];
            Cpi[3] = dmesh[(j*cols + i+1)*2 + 1];
            //bottom-left
            Cpi[4] = dmesh[((j+1)*cols + i)*2];
            Cpi[5] = dmesh[((j+1)*cols + i)*2 + 1];
            //bottom-right
            Cpi[6] = dmesh[((j+1)*cols + i+1)*2];
            Cpi[7] = dmesh[((j+1)*cols + i+1)*2 + 1];
            //printf("in loop1 j=%d, i =%d",j,i);
            formAq(Cpi,op);
            Vi[0] = imesh[(j*cols + i)*2];
            Vi[1] = imesh[(j*cols + i)*2 + 1];
            //right-top
            Vi[2] = imesh[(j*cols + i+1)*2];
            Vi[3] = imesh[(j*cols + i+1)*2 + 1];
            //bottom-left
            Vi[4] = imesh[((j+1)*cols + i)*2];
            Vi[5] = imesh[((j+1)*cols + i)*2 + 1];
            //bottom-right
            Vi[6] = imesh[((j+1)*cols + i+1)*2];
            Vi[7] = imesh[((j+1)*cols + i+1)*2 + 1];

    return(matEi(op, Vi));
}


float getEnregyq(int j, int i, int* imesh, int* dmesh, int cols)
{
    float xo = getEnregyi(i-1,j-1,imesh, dmesh,cols);
    float x1 = getEnregyi(i-1,j,imesh, dmesh,cols);
    float x2 = getEnregyi(i,j-1,imesh, dmesh,cols);
    float x3 = getEnregyi(i,j,imesh, dmesh,cols);
    //printf("\ngot energies x0= %f, x1= %f, x2= %f, x3= %f\n",xo,x1,x2,x3);
    return xo+x1+x2+x3;

}

float getEnregyqtop(int j, int i, int* imesh, int* dmesh, int cols)
{
    float x2 = getEnregyi(i-1,j,imesh, dmesh,cols);
    float x3 = getEnregyi(i,j,imesh, dmesh,cols);
    //printf("\ngot energies x0= %f, x1= %f, x2= %f, x3= %f\n",xo,x1,x2,x3);
    return x2+x3;
}


void getBetterPositiontop(int j, int i, int* imesh, int* dmesh, int cols)
{
    int min_case,org_x,org_y;
    float min_en,m;
    for(int c=0;c<3;c++)
    {
        if(c==0)
        {
            org_x = imesh[((j)*cols + i)*2];
            org_y = imesh[((j)*cols + i)*2 + 1];
        }
        else if(c==1)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x-3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        else if(c==2)
        {
            //right
            imesh[((j)*cols + i)*2] = org_x+3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        //printf("\nwhere the location is %d,%d,j=%d,i=%d",imesh[((j)*cols + i)*2], imesh[((j)*cols + i)*2 + 1],j,i);
        m=getEnregyqtop(j, i, imesh, dmesh, cols);
        //printf("\nCumulative energy for case=%d is %f",c,m);

        if(c==0||m<min_en)
        {
            min_en=m;
            min_case = c;
            //printf("\nCumulative energy for min-case, case=%d is %f",c,m);
        }
    }


        if(min_case==0)
        {
            imesh[((j)*cols + i)*2]=org_x;
            imesh[((j)*cols + i)*2 + 1]=org_y;
        }
        else if(min_case==1)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x-3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        else if(min_case==2)
        {
            //right
            imesh[((j)*cols + i)*2] = org_x+3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        //printf("\nCumulative energy for min-case, case=%d is %f",min_case,m);
}

float getEnregyqbottom(int j, int i, int* imesh, int* dmesh, int cols)
{
    float xo = getEnregyi(i-1,j-1,imesh, dmesh,cols);
    float x1 = getEnregyi(i,j-1,imesh, dmesh,cols);
    //printf("\ngot energies x0= %f, x1= %f, x2= %f, x3= %f\n",xo,x1,x2,x3);
    return xo+x1;

}

void getBetterPositionbottom(int j, int i, int* imesh, int* dmesh, int cols)
{
    int min_case,org_x,org_y;
    float min_en,m;
    for(int c=0;c<3;c++)
    {
        if(c==0)
        {
            org_x = imesh[((j)*cols + i)*2];
            org_y = imesh[((j)*cols + i)*2 + 1];
        }
        else if(c==1)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x-3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        else if(c==2)
        {
            //right
            imesh[((j)*cols + i)*2] = org_x+3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        m=getEnregyqbottom(j, i, imesh, dmesh, cols);
        //printf("\nCumulative energy for case=%d is %f",c,m);
        //printf("\nwhere the location is %d,%d",imesh[((j)*cols + i)*2], imesh[((j+1)*cols + i)*2 + 1]);
        if(c==0||m<min_en)
        {
            min_en=m;
            min_case = c;
            //printf("\nCumulative energy for min-case, case=%d is %f",c,m);
        }
    }


        if(min_case==0)
        {
            imesh[((j)*cols + i)*2]=org_x;
            imesh[((j)*cols + i)*2 + 1]=org_y;
        }
        else if(min_case==1)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x-3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        else if(min_case==2)
        {
            //right
            imesh[((j)*cols + i)*2] = org_x+3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        //printf("\nCumulative energy for min-case, case=%d is %f",min_case,m);
}

float getEnregyqleft(int j, int i, int* imesh, int* dmesh, int cols)
{
    float x2 = getEnregyi(i,j-1,imesh, dmesh,cols);
    float x3 = getEnregyi(i,j,imesh, dmesh,cols);
    //printf("\ngot energies x0= %f, x1= %f, x2= %f, x3= %f\n",x2,x3);
    return x2+x3;
}

void getBetterPositionleft(int j, int i, int* imesh, int* dmesh, int cols)
{
    int min_case,org_x,org_y;
    float min_en,m;
    for(int c=0;c<3;c++)
    {
        if(c==0)
        {
            org_x = imesh[((j)*cols + i)*2];
            org_y = imesh[((j)*cols + i)*2 + 1];
        }
        else if(c==1)
        {
            //top
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y-1;
        }
        else if(c==2)
        {
            //bottom
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y+1;
        }
        m=getEnregyqleft(j, i, imesh, dmesh, cols);
        //printf("\nwhere the location is %d,%d",imesh[((j)*cols + i)*2], imesh[((j)*cols + i)*2 + 1]);
        //printf("\nCumulative energy for case=%d is %f",c,m);
        if(c==0||m<min_en)
        {
            min_en=m;
            min_case = c;
            //printf("\nCumulative energy for min-case, case=%d is %f",c,m);
        }
    }


        if(min_case==0)
        {
            imesh[((j)*cols + i)*2]=org_x;
            imesh[((j)*cols + i)*2 + 1]=org_y;
        }
        else if(min_case==1)
        {
            //top
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y-1;
        }
        else if(min_case==2)
        {
            //bottom
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y+1;
        }
        //printf("\nCumulative energy for min-case, case=%d is %f",min_case,m);
}

void managethisleftCol(int i, int* imesh, int* dmesh, int rows, int cols)
{
	int j,jbp=1,jep=rows-2,way=1;
    while(jbp<=jep)
    {
        if(way==1)
        {
            j=jbp;
            jbp++;
        }
        else
        {
            j=jep;
            jep--;
        }
        //printf("\nj=%d,i=%d\n",j,i);
             for(int x=0;x<5;x++)
            {
                getBetterPositionleft(j, i, imesh, dmesh, cols);
            }
        way*=-1;
    }
}



float getEnregyqright(int j, int i, int* imesh, int* dmesh, int cols)
{
    float xo = getEnregyi(i-1,j-1,imesh, dmesh,cols);
    float x1 = getEnregyi(i-1,j,imesh, dmesh,cols);
    //printf("\ngot energies x0= %f, x1= %f, x2= %f, x3= %f\n",xo,x1,x2,x3);
    return xo+x1;

}


void getBetterPositionright(int j, int i, int* imesh, int* dmesh, int cols)
{
    int min_case,org_x,org_y;
    float min_en,m;
    for(int c=0;c<3;c++)
    {
        if(c==0)
        {
            org_x = imesh[((j)*cols + i)*2];
            org_y = imesh[((j)*cols + i)*2 + 1];
        }
        else if(c==1)
        {
            //top
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y-1;
        }
        else if(c==2)
        {
            //bottom
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y+1;
        }
        m=getEnregyqright(j, i, imesh, dmesh, cols);
        //printf("\nwhere the location is %d,%d",imesh[((j)*cols + i)*2], imesh[((j)*cols + i)*2 + 1]);
        //printf("\nCumulative energy for case=%d is %f",c,m);
        if(c==0||m<min_en)
        {
            min_en=m;
            min_case = c;
            //printf("\nCumulative energy for min-case, case=%d is %f",c,m);
        }
    }


        if(min_case==0)
        {
            imesh[((j)*cols + i)*2]=org_x;
            imesh[((j)*cols + i)*2 + 1]=org_y;
        }
        else if(min_case==1)
        {
            //top
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y-1;
        }
        else if(min_case==2)
        {
            //bottom
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y+1;
        }
        //printf("\nCumulative energy for min-case, case=%d is %f",min_case,m);
}

void managethisrightCol(int i, int* imesh, int* dmesh, int rows, int cols)
{
	int j,jbp=1,jep=rows-2,way=1;
    while(jbp<=jep)
    {
        if(way==1)
        {
            j=jbp;
            jbp++;
        }
        else
        {
            j=jep;
            jep--;
        }
        //printf("\nj=%d,i=%d\n",j,i);
             for(int x=0;x<5;x++)
            {
                getBetterPositionright(j, i, imesh, dmesh, cols);
            }
        way*=-1;
    }
}

void getBetterPosition(int j, int i, int* imesh, int* dmesh, int cols)
{
    int min_case,org_x,org_y;
    float min_en,m;
    for(int c=0;c<5;c++)
    {
        if(c==0)
        {
            org_x = imesh[((j)*cols + i)*2];
            org_y = imesh[((j)*cols + i)*2 + 1];
        }
        else if(c==1)
        {
            //top
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y-1;
        }
        else if(c==2)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x-3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        else if(c==3)
        {
            //bottom
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y+1;
        }
        else if(c==4)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x+3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        m=getEnregyq(j, i, imesh, dmesh, cols);
        //printf("\nCumulative energy for case=%d is %f",c,m);
        //printf("\nwhere the location is %d,%d",imesh[((j)*cols + i)*2], imesh[((j+1)*cols + i)*2 + 1]);
        if(c==0||m<min_en)
        {
            min_en=m;
            min_case = c;
            //printf("\nCumulative energy for min-case, case=%d is %f",c,m);
        }
    }


        if(min_case==0)
        {
            imesh[((j)*cols + i)*2]=org_x;
            imesh[((j)*cols + i)*2 + 1]=org_y;
        }
        else if(min_case==1)
        {
            //top
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y-1;
        }
        else if(min_case==2)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x-3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        else if(min_case==3)
        {
            //bottom
            imesh[((j)*cols + i)*2] = org_x;
            imesh[((j)*cols + i)*2 + 1] = org_y+1;
        }
        else if(min_case==4)
        {
            //left
            imesh[((j)*cols + i)*2] = org_x+3;
            imesh[((j)*cols + i)*2 + 1] = org_y;
        }
        //printf("\nCumulative energy for min-case, case=%d is %f",min_case,m);
}

void managethistopRow(int j, int* imesh, int* dmesh, int cols)
{
    int ibp=1,iep=cols-2,way=1,i;
    while(ibp<=iep)
    {
        if(way==1)
        {
            i=ibp;
            ibp++;
        }
        else
        {
            i=iep;
            iep--;
        }
        //printf("\nj=%d,i=%d\n",j,i);
             for(int x=0;x<5;x++)
            {
                getBetterPositiontop(j, i, imesh, dmesh, cols);
            }
        way*=-1;
    }
}




void managethisbottomRow(int j, int* imesh, int* dmesh, int cols)
{
    int ibp=1,iep=cols-2,way=1,i;
    while(ibp<=iep)
    {
        if(way==1)
        {
            i=ibp;
            ibp++;
        }
        else
        {
            i=iep;
            iep--;
        }
        //printf("\nj=%d,i=%d\n",j,i);
             for(int x=0;x<5;x++)
            {
                getBetterPositionbottom(j, i, imesh, dmesh, cols);
            }
        way*=-1;
    }
}

void managethisRow(int j, int* imesh, int* dmesh, int cols)
{
    int ibp=1,iep=cols-2,way=1,i;
    while(ibp<=iep)
    {
        if(way==1)
        {
            i=ibp;
            ibp++;
        }
        else
        {
            i=iep;
            iep--;
        }
        //printf("\nj=%d,i=%d\n",j,i);
             for(int x=0;x<5;x++)
            {
                getBetterPosition(j, i, imesh, dmesh, cols);
            }
        way*=-1;
    }
}

void getNewMesh(int* imesh, int* dmesh, int rows, int cols, int width, int height)
{
    imposeBoundary(imesh,rows,cols,width, height);

    int j,jbp=1,jep=rows-2,way=1;
    while(jbp<=jep)
    {
        if(way==1)
        {
            j=jbp;
            jbp++;
        }
        else
        {
            j=jep;
            jep--;
        }
        managethisRow(j, imesh, dmesh, cols);
        way*=-1;
    }
    managethistopRow(0, imesh, dmesh, cols);
    managethisleftCol(0, imesh, dmesh, rows, cols);
    managethisbottomRow(rows-1, imesh, dmesh, cols);
    managethisrightCol(cols-1, imesh, dmesh, rows, cols);

}
