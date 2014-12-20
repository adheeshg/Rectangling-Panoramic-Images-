
//code in this section is largely copied from http://rodolphe-vaillant.fr/?e=7 and http://dev.tplanet.net/Matrix2D/
#include <windows.h>
#include <stdio.h>
#include "CGProject.h"


void formAq(int A[8], int Aq[8][4], int AqT[4][8])
{

    for(int i=0;i<8;i++)
    {
            if (i%2==0)
            {
                Aq[i][0] = A[i];
                Aq[i][1] = -A[i+1];
                Aq[i][2] = 1;
                Aq[i][3] = 0;

                AqT[0][i] = A[i];
                AqT[1][i] = -A[i+1];
                AqT[2][i] = 1;
                AqT[3][i] = 0;
            }
            else
            {
                Aq[i][0] = A[i];
                Aq[i][1] = A[i-1];
                Aq[i][2] = 0;
                Aq[i][3] = 1;

                AqT[0][i] = A[i];
                AqT[1][i] = A[i-1];
                AqT[2][i] = 0;
                AqT[3][i] = 1;
            }
    }

}

void displayAq(int Aq[8][4])
{
  int  i,j;
  for (i= 0;i<8;i++)
  {
    printf("\n[\t");
    for (j= 0;j<4;j++)
    {
      printf("%d\t",Aq[i][j]);
    }
    printf("]\n");
  }
}

void displayAqF(float Aq[8][4])
{
  int  i,j;
  for (i= 0;i<8;i++)
  {
    printf("\n[\t");
    for (j= 0;j<4;j++)
    {
      printf("%f\t",Aq[i][j]);
    }
    printf("]\n");
  }
}

void displayAqT(int Aq[4][8])
{
  int  i,j;
  for (i= 0;i<4;i++)
  {
    printf("\n[\t");
    for (j= 0;j<8;j++)
    {
      printf("%d\t",Aq[i][j]);
    }
    printf("]\n");
  }
}

void displayA(int A[8])
{
    int  i,j;

    printf("\n[\t");
    for (j= 0;j<8;j++)
    {
      printf("%d\t",A[j]);
    }
    printf("]\n");

}

void display44(int A[4][4])
{
  int  i,j;
  for (i= 0;i<4;i++)
  {
    printf("\n[\t");
    for (j= 0;j<4;j++)
    {
      printf("%d\t",A[i][j]);
    }
    printf("]\n");
  }

}
void mat4mulB(int AqTAq[4][4], int Aq[8][4], int AqT[4][8])
{
  int r,c,k;
  for (r=0;r<4;r++)
  {
    for (c=0;c<4;c++)
    {
      int x = 0;
      for (k= 0;k<8;k++)
      {
          x += AqT[r][k]*Aq[k][c];
      }
      AqTAq[r][c] = x;
      //printf ("r=%d, c=%d, x=%d \n", r,c,x );
    }

  }
}


void mat4mulA(float partA[8][4], int Aq[8][4], float partB[4][4])
{
  int r,c,k;
  for (r=0;r<8;r++)
  {
    for (c=0;c<4;c++)
    {
      float x = 0.0;
      for (k= 0;k<4;k++)
      {
          x += ((float)Aq[r][k])*partB[k][c];
      }
      partA[r][c] = x;
      //printf ("r=%d, c=%d, x=%d \n", r,c,x );
    }

  }
}


void mat4mulC(float partC[8][8], float partA[8][4], int AqT[4][8])
{
  int r,c,k;
  for (r=0;r<8;r++)
  {
    for (c=0;c<8;c++)
    {
      float x = 0.0;
      for (k= 0;k<4;k++)
      {
          x += partA[r][k]*((float)AqT[k][c]);
      }
      partC[r][c] = x;
      //printf ("r=%d, c=%d, x=%d \n", r,c,x );
    }

  }
}

bool invertColumnMajor(float m[16], float invOut[16])
{
    float inv[16], det;
    int i;

    inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
    inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
    inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
    inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
    inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
    inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
    inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
    inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
    inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
    inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
    inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
    inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if(det == 0)
        return false;

    det = 1.f / det;

    for(i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

void mat4mulFloat(float A[16], float P_1[16], float Q[16])
{
  int r,c,k;
  for (r=0;r<4;r++)
  {
    for (c=0;c<4;c++)
    {
      float x = 0.0;
      for (k= 0;k<4;k++)
      {
          x += Q[r*4+k]*P_1[k*4+c]; //((float)Aq[r][k])*partB[k][c];
      }
      A[r*4+c] = x;
      //printf ("r=%d, c=%d, x=%d \n", r,c,x );
    }

  }
}





void display16float(float A[16])
{
  int  i,j;
  for (i= 0;i<4;i++)
  {
    printf("\n[\t");
    for (j= 0;j<4;j++)
    {
      printf("%f\t",A[i*4 + j]);
    }
    printf("]\n");
  }

}


void getAffine(float A[16], float P[16], float Q[16])
{
    float P_1[16];
    invertColumnMajor(P,P_1);
    mat4mulFloat(A,P_1,Q);
    //printf("\nAffine:\n");
    //display16float(A);
}


void display44float(float A[4][4])
{
  int  i,j;
  for (i= 0;i<4;i++)
  {
    printf("\n[\t");
    for (j= 0;j<4;j++)
    {
      printf("%f\t",A[i][j]);
    }
    printf("]\n");
  }

}

void display88float(float A[8][8])
{
  int  i,j;
  for (i= 0;i<8;i++)
  {
    printf("\n[\t");
    for (j= 0;j<8;j++)
    {
      printf("%f\t",A[i][j]);
    }
    printf("]\n");
  }

}

void getInv(int a[4][4], float i[4][4])
{
    float m[16], im[16];
    int r,c;
    for (r=0;r<4;r++)
    {
        for (c=0;c<4;c++)
        {
            m[r*4 + c] = a[r][c];
        }
    }
    invertColumnMajor(m, im);
    for (r=0;r<4;r++)
    {
        for (c=0;c<4;c++)
        {
            i[r][c] = im[r*4 + c];
        }
    }
    //display44float(i);

}

void testformAq()
{
    int a[8] = {1,2,3,4,5,6,7,8};
    int aq[8][4];
    int aqt[4][8];
    int aqtaq[4][4];
    float ib[4][4], pa[8][4],pc[8][8];

    formAq(a, aq, aqt);
    displayA(a);
    displayAq(aq);
    displayAqT(aqt);
    mat4mulB(aqtaq, aq, aqt);
    printf("\npartB\n");
    display44(aqtaq);
    printf("\npartIB\n");
    getInv(aqtaq,ib);
    mat4mulA(pa, aq, ib);
    printf("\npartA\n");
    displayAqF(pa);
    mat4mulC(pc, pa, aqt);
    printf("\npartC\n");
    display88float(pc);
}


void formAq(int a[8], float aqi[8][8])
{
    //int a[8] = {1,2,3,4,5,6,7,8};
    int aq[8][4];
    int aqt[4][8];
    int aqtaq[4][4];
    float ib[4][4], pa[8][4],pc[8][8];

    formAq(a, aq, aqt);
    //displayA(a);
    //displayAq(aq);
    //displayAqT(aqt);
    mat4mulB(aqtaq, aq, aqt);
    //printf("\npartB\n");
    //display44(aqtaq);
    //printf("\npartIB\n");
    getInv(aqtaq,ib);
    mat4mulA(pa, aq, ib);
    //printf("\npartA\n");
    //displayAqF(pa);
    mat4mulC(pc, pa, aqt);
    //printf("\npartC\n");
    //display88float(pc);
    for(int x=0;x<8;x++)
    {
        for(int y=0;y<8;y++)
        {
            aqi[x][y] = pc[x][y];
        }
    }

}
