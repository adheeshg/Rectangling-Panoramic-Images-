#ifndef CGPROJECT_H_INCLUDED
#define CGPROJECT_H_INCLUDED
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//boundaries_sections
void removeRed( BYTE* Buffer, int width, int height );

void markLeftBoundary( BYTE* Buffer, int width, int height );
void getLargestLeftBoundarySegment( BYTE* Buffer, int width, int height, int *yBegin, int *yEnd);
void markRightBoundary( BYTE* Buffer, int width, int height );
void getLargestRightBoundarySegment( BYTE* Buffer, int width, int height, int *yBegin, int *yEnd);
void markTopBoundary( BYTE* Buffer, int width, int height );
void getLargestTopBoundarySegment( BYTE* Buffer, int width, int height, int *yBegin, int *yEnd);
void markBottomBoundary( BYTE* Buffer, int width, int height );
void getLargestBottomBoundarySegment(BYTE* Buffer, int width, int height, int *xBegin, int *xEnd);

void markSegmentforLargestBoundary( BYTE* Buffer, int width, int height );
void getSegmentforLargestBoundary( BYTE* Buffer, int width, int height, int *xStart, int *xFin, int *yStart, int *yFin, int *tLen, int *dir );
void markSection( BYTE* Buffer, int xBegin, int xEnd, int yBegin, int yEnd, int tWidth );
void removeExtraBoundaries( BYTE* Buffer, int *width, int *height );
void getBoundaryMap(BYTE* Buffer, int width, int height, BYTE* newbuf);
bool isBoundary(BYTE * Buffer, long newpos);

//my_project.cpp
BYTE* prepocess( BYTE* Buffer, int *width, int *height );
BYTE* LocalWarping( BYTE* Buffer, int width, int height, char * output );



//image_representations.cpp
void saveAsImage(BYTE* Buffer, int width, int height, char* name);
void getGreyScale( BYTE* Buffer, int width, int height, BYTE* newbuf);
//BYTE* getYGradient( BYTE* I, int width, int height );
//BYTE* getXGradient( BYTE* I, int width, int height );
void getGradient( BYTE* I, int width, int height, BYTE* newbuf  );
//BYTE* getIntensity( BYTE* Buffer, int width, int height );
//void printIntensity( BYTE* newbuff, int width, int height, BYTE* Buffer );

//seam_carvingH.cpp
//BYTE*  markHorizontalSeamAbove( BYTE* Buffer, int width, int height, int xStart, int xFin, int yStart, int yFin, BYTE* BoundaryMask);
BYTE* getHDisplacementImage1(BYTE* Buffer, int width, int height, int xStart, int xFin, int yStart, int yFin, BYTE* BoundaryMask, BYTE* SeamMask);
BYTE* getHDisplacementImage3(BYTE* Buffer, int width, int height, int xStart, int xFin, int yStart, int yFin, BYTE* BoundaryMask, BYTE* SeamMask);
BYTE* getVDisplacementImage2(BYTE* Buffer, int width, int height, int xStart, int xFin, int yStart, int yFin, BYTE* BoundaryMask, BYTE* SeamMask);
BYTE* getVDisplacementImage4(BYTE* Buffer, int width, int height, int xStart, int xFin, int yStart, int yFin, BYTE* BoundaryMask, BYTE* SeamMask);



//basic_oper.c
void BufCopy(BYTE* BufD, BYTE* BufS, int width, int height);
void BufAvg(BYTE* Res, BYTE* Buf1, BYTE* Buf2, int width, int height);
void BufImpose(BYTE* Res, BYTE* Buf1, BYTE* Buf2, int width, int height);

//displace
void displaceAbove(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, BYTE* SeamMask);
void displaceBelow(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, BYTE* SeamMask);
void displaceLeft(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer);
void displaceRight(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer);

void displaceAbove1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Hdisp,int xBegin, int xEnd, int yBegin, int yEnd, BYTE* SeamMask);
void displaceBelow1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Hdisp,int xBegin, int xEnd, int yBegin, int yEnd, BYTE* SeamMask);
void displaceLeft1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Hdisp, BYTE* SeamMask);
void displaceRight1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer, int* Hdisp, BYTE* SeamMask);

void displaceReal(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, BYTE* D);
void displaceBack(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, BYTE* D);

void hplace_mesh(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp,  BYTE* temp);




BYTE* scaleup2( BYTE* Buffer, int *width, int *height );
BYTE* downsampling( BYTE* Buffer, int *width, int *height, int n );
void tostring(char str[], int num);

BYTE* ConvertRGBToBMPBuffer ( BYTE* Buffer, int width, int height, long* newsize );
bool SaveBMP ( BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile );

void interpolate(BYTE* Buffer, int* imesh, int* dmesh, int rows, int cols, int width, int height, char * name);
void global_warping(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, char* output);
void getNewMesh(int* imesh, int* dmesh, int rows, int cols, int width, int height);

void testformAq();
void formAq(int a[8], float aqi[8][8]);
void display88float(float A[8][8]);

void getAffine(float A[16], float P[16], float Q[16]);
void Affinefverify();
#endif // CGPROJECT_H_INCLUDED


