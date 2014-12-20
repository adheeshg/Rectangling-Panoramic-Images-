This folder contains the C files and header for the project - "Rectangling the panorama " implemented by Adheesh Gokhale (109293558). 
CSE528Final.zip : this contains the CodeBlocks project.

Although the files are stored in CPP format, most of this, is a C code. The code inlcudes calls to these libraries: <windows.h>,<stdio.h>,<stdlib.h> and <math.h>. Since <windows.h> is used, this needs windows to compile.
Some functions have been described as "written for dev./testing purpose". They have not been called.


Following is the list of files(in alphabetical order of names) and functions implented. First those files are mentione which contain some code copied from internet. For such files, each function has been mentioned separately, if written by me or taken from internet.


1. main.cpp 550 lines. Contains code copied from http://tipsandtricks.runicsoft.com/Cpp/BitmapTutorial.html. the copied code is used to read and save bitmap images

function	 BYTE* ConvertRGBToBMPBuffer ( BYTE* Buffer, int width, int height, long* newsize )
description	 save image to a buffer. copied from the reference mentioned above

function 	BYTE* ConvertRGBToBMPBuffer1 ( BYTE* Buffer, int width, int height, long* newsize, int oldWidth )
description	for dev. purpose, not used anymore. saves image to a buffer. written by me

function 	BYTE* ConvertBMPToRGBBuffer ( BYTE* Buffer, int width, int height )
description	converts bmp buffer to rgb 3-color 2D array. copied from the reference mentioned above


function 	bool LoadBMPIntoDC ( HDC hDC, LPCTSTR bmpfile )
description	Takes in a device context and the name of a bitmap to load. copied from the reference mentioned above

function 	bool SaveBMP ( BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile )
description	saves the file onto the disk by reading bmp buffer. copied from the reference mentioned above

function 	BYTE* LoadBMP ( int* width, int* height, long* size, LPCTSTR bmpfile )
description	loads the bmp buffer by reading the bmp file from disk.  copied from the reference mentioned above

function 	void TestBMPCopy (LPCTSTR input, LPCTSTR output)
description	for test purpose, not used anymore. written by me

function 	void TestBMPCopy2(LPCTSTR input, char* output)
description	process each image. written by me

function 	int main ()
description	process all the images. code submitted processes only 1 images. to increase, change the test condition in for loop. written by me

function 	int mainxx ()	
description	for test purpose, not used anymore. written by me 





/**************************************************************************************************************************************************************/

2. matrix4.cpp  360 lines Contains code copied from http://rodolphe-vaillant.fr/?e=7 and http://dev.tplanet.net/Matrix2D/


function 	formAq(int A[8], int Aq[8][4], int AqT[4][8])
description	given quad pixel locations, form the Aq(8x4) and AqT(4X8) matrices. written by me

function 	void displayAq(int Aq[8][4])
description	display on console. written by me

function 	void displayAqF(float Aq[8][4])
description	display on console for float type. written by me

function 	void displayAqT(int Aq[4][8])
description	display on console. written by me

function 	void displayA(int A[8])
description	display on console. written by me

function 	void display44(int A[4][4])	
description	display on console. written by me

function 	void mat4mulB(int AqTAq[4][4], int Aq[8][4], int AqT[4][8])
description	matrix multiply. copied from the reference mentioned above, with minor modifications to suit my requirement

function 	void mat4mulA(float partA[8][4], int Aq[8][4], float partB[4][4])
description	matrix multiply. copied from the reference mentioned above, with minor modifications to suit my requirement

function 	void mat4mulC(float partC[8][8], float partA[8][4], int AqT[4][8])
description	matrix multiply. copied from the reference mentioned above, with minor modifications to suit my requirement

function 	bool invertColumnMajor(float m[16], float invOut[16])
description	matrix inverse. copied from the reference mentioned above.

function 	void mat4mulFloat(float A[16], float P_1[16], float Q[16])
description	matrix multiply. copied from the reference mentioned above, with minor modifications to suit my requirement

function 	void display16float(float A[16])
description	display on console. written by me

function 	void getAffine(float A[16], float P[16], float Q[16])
description	get Affine transformation matrix. written by me

function 	void display44float(float A[4][4])
description	display on console. written by me

function 	void display88float(float A[8][8])
description	display on console. written by me

function 	void getInv(int a[4][4], float i[4][4])
description	wrapper for matrix inversion.  written by me

function 	void testformAq()
description	for test purpose, not used anymore. written by me

function 	void formAq(int a[8], float aqi[8][8])
description	calculate the BIG term for the energy calculation


/**************************************************************************************************************************************************************/

3. sampling.cpp 120 lines. contains code copied from http://www.sanfoundry.com/c-program-integer-to-string-vice-versa/

function 	BYTE* downsampling( BYTE* Buffer, int *width, int *height, int n )	
description	downsample the image, by a factor of n in both the dimensions. written by me

function 	BYTE* scaleup2( BYTE* Buffer, int *width, int *height )
description	scale using linear interpolation, by a factor of 2. written by me

function 	void tostring(char str[], int num)
description	convert an int to string. copied from the reference mentioned above











/**************************************************************************************************************************************************************/
All the code described below is completely written by me.
/**************************************************************************************************************************************************************/







4. boundaries_sections.cpp  760 lines

function 	bool isBoundary(BYTE * Buffer, long newpos) 
description 	Tells if a given pixel location is inside the panorama or outside, in the white boundary.

 
function 	void BufCopy(BYTE* BufD, BYTE* BufS, int width, int height)
description	copy one image arrays

function 	void BufAvg(BYTE* Res, BYTE* Buf1, BYTE* Buf2, int width, int height)
description	find average of two images. mainly used to average the energies in different images. 

function 	void BufImpose(BYTE* Res, BYTE* Buf1, BYTE* Mask, int width, int height)
description	impose the white boundary on the energy map

function 	void removeRed( BYTE* Buffer, int width, int height )
description	written for testing purpose. removes the red component of each pixel

function 	void markLeftBoundary( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks the left boundary

function 	void getLargestLeftBoundarySegment(BYTE* Buffer, int width, int height, int *yBegin, int *yEnd, int *maxlen)
description	gets the end points of the largest white boundary left edge. 

function 	void markRightBoundary( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks the right boundary

function 	void getLargestRightBoundarySegment(BYTE* Buffer, int width, int height, int *yBegin, int *yEnd, int *maxlen)
description	gets the end points of the largest white boundary right edge.

function 	void markTopBoundary( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks the top boundary

function 	void getLargestTopBoundarySegment(BYTE* Buffer, int width, int height, int *xBegin, int *xEnd, int *maxlen)
description	gets the end points of the largest white boundary top edge.


function 	void markBottomBoundary( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks the top boundary bottom edge.


function 	void getLargestBottomBoundarySegment(BYTE* Buffer, int width, int height, int *xBegin, int *xEnd, int *maxlen)
description	gets the end points of the largest white boundary bottom edge.


function 	void markSectionBoundary( BYTE* Buffer, int xBegin, int xEnd, int yBegin, int yEnd, int tWidth )
description	written for testing purpose.marks the rectangular section boundary


function 	void markSection( BYTE* Buffer, int xBegin, int xEnd, int yBegin, int yEnd, int tWidth )
description	written for testing purpose.marks the rectangular section



function 	void markAllBoundaries( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks all the boundary edges

function 	void markSegmentforLargestBoundary( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks the top boundary


function 	void markSegmentforLargestBoundary( BYTE* Buffer, int width, int height )
description	written for testing purpose.marks the rectangular section with largest white boundary


function 	void getSegmentforLargestBoundary( BYTE* Buffer, int width, int height, int *xStart, int *xFin, int *yStart, int *yFin, int *tLen, int *dir )
description	get the end points of the largest white boundary 

function 	void removeExtraLeftBoundary( BYTE* Buffer, int *width, int *height )
description	used in pre-processing, to remove the extra boundary on left hand side.

function 	void removeExtraTopBoundary( BYTE* Buffer, int *width, int *height )
description	used in pre-processing, to remove the extra boundary on top.


function 	void removeExtraBoundaries( BYTE* Buffer, int *width, int *height )
description	used in pre-processing, to remove the extra boundary

function 	void getBoundaryMap(BYTE* Buffer, int width, int height, BYTE* newbuf)
description	used segmentation-like technique to separate image and the white boundary



/**************************************************************************************************************************************************************/



5. displace.cpp  150 lines


function 	void displaceAbove(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
description	Displace the region above the seam, one pixel up. old version, not used now


function 	void displaceBelow(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
description	Displace the region below the seam, one pixel down.  old version, not used now


function 	void displaceLeft(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
description	Displace the region left of the seam, one pixel left.  old version, not used now
	
function	void displaceRight(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer) 
description	Displace the region right of the seam, one pixel right.  old version, not used now

/**************************************************************************************************************************************************************/

6. displace1.cpp 240 lines


function 	void displaceAbove1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
description	Displace the region above the seam, one pixel up.


function 	void displaceBelow1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
description	Displace the region below the seam, one pixel down.  


function 	void displaceLeft1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer)
description	Displace the region left of the seam, one pixel left.  
	
function	void displaceRight1(BYTE* dI,BYTE* D, int width, int height, BYTE* Buffer) 
description	Displace the region right of the seam, one pixel right. 


function 	void displaceReal(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, BYTE* D)
description	displace directly, by using displacement map.

function 	void displaceBack(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, BYTE* D)
description	used for reverse displacement 

/**************************************************************************************************************************************************************/

7. Global_warping 710 lines

function 	void displayMesh(int* mesh, int rows, int cols)
description	display the mesh-pixel locations on console

function 	void printMesh(int* mesh, int rows, int cols, int width, int height, char * name)
description	print the mesh to a bmp image

function 	void global_warping(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp, char* output)
description	wrapper for the energy based warping

function 	void imposeBoundary(int* mesh, int rows, int cols, int width, int height)
description	push the mesh boundary to the rectangle. this is the implementation of boundary constraints

function 	float matEi(float Cpi[8][8], int Vi[8])
description	find energy value for ith quad

function 	float getEnregyi(int i, int j, int* imesh, int* dmesh, int cols)
description	wrapper for above function

function 	float getEnregyq(int j, int i, int* imesh, int* dmesh, int cols)
description	get quad energies for 4 quads surrounding i,j

function 	float getEnregyqtop(int j, int i, int* imesh, int* dmesh, int cols)
description	get quad energies for the 2 quads below i,j. this is for mesh points on top boundary

function 	void getBetterPositiontop(int j, int i, int* imesh, int* dmesh, int cols)
description	get energy optimal position for i,j mesh point which lies on top boundary

function 	float getEnregyqbottom(int j, int i, int* imesh, int* dmesh, int cols)
description	get quad energies for the 2 quads above i,j. this is for mesh points on bottom boundary

function 	void getBetterPositionbottom(int j, int i, int* imesh, int* dmesh, int cols)
description	get energy optimal position for i,j mesh point which lies on bottom boundary

function 	float getEnregyqleft(int j, int i, int* imesh, int* dmesh, int cols)
description	get quad energies for the 2 quads right of i,j. this is for mesh points on left boundary

function 	void getBetterPositionleft(int j, int i, int* imesh, int* dmesh, int cols)
description	get energy optimal position for i,j mesh point which lies on left boundary

function 	void managethisleftCol(int i, int* imesh, int* dmesh, int rows, int cols)
description	getBetter positions for all the pixels on left boundary

function 	float getEnregyqright(int j, int i, int* imesh, int* dmesh, int cols)
description	get quad energies for the 2 quads right of i,j. this is for mesh points on right boundary

function 	void getBetterPositionright(int j, int i, int* imesh, int* dmesh, int cols)
description	get energy optimal position for i,j mesh point which lies on right boundary

function 	void managethisrightCol(int i, int* imesh, int* dmesh, int rows, int cols)
description	getBetter positions for all the pixels on right boundary

function 	void getBetterPosition(int j, int i, int* imesh, int* dmesh, int cols)
description	getBetter positions for the interior pixel at i,j

function 	void managethistopRow(int j, int* imesh, int* dmesh, int cols)
description	getBetter positions for all the pixels on top boundary

function 	void managethisbottomRow(int j, int* imesh, int* dmesh, int cols)
description	getBetter positions for all the pixels on bottom boundary

function 	void managethisRow(int j, int* imesh, int* dmesh, int cols)
description	getBetter positions for all the interior pixels

function 	void getNewMesh(int* imesh, int* dmesh, int rows, int cols, int width, int height)
description	wrapper for calling managethisRow iteratively



/**************************************************************************************************************************************************************/

8. image_representations.cpp 260 lines

function 	void getGreyScale( BYTE* Buffer, int width, int height, BYTE* newbuf )
description	convert to grey scale image
	
function 	BYTE* getYGradient( BYTE* I, int width, int height )
description	get the gradient in vertical direction

function 	BYTE* getYGradientColor( BYTE* I, int width, int height )
description	get the gradient in vertical direction for a colored image

function 	BYTE* getXGradient( BYTE* I, int width, int height )
description	get the gradient in horizontal direction

function 	BYTE* getXGradientColor( BYTE* I, int width, int height )
description	get the gradient in horizontal direction for a colored image

function 	void getGradient( BYTE* I, int width, int height, BYTE* newbuf )
description	get the gradient (wrapper for x&Y gradient functions)

function 	void saveAsImage(BYTE* Buffer, int width, int height, char* name)
description	save image as .bmp file (a wrapper)
	

/**************************************************************************************************************************************************************/

9. mesh_place.cpp 180 lines

function 	void hplace_mesh_v0(BYTE* Buffer, int width, int height)
description	old versio,not used anymore.

function 	void hplace_mesh(BYTE* Buffer, int width, int height, int* Vdisp, int* Hdisp,  BYTE* temp)
description	place the initial rectangular mesh on the images.


/**************************************************************************************************************************************************************/

10. my_project.cpp 250 lines

function 	BYTE* prepocess( BYTE* Buffer, int *width, int *height )
description	preprocessing -> removing the extra boundaries

function 	BYTE* LocalWarping( BYTE* Buffer, int width, int height, char * output )
description	perform local warping using seam carving. calls to sema placement and global warping


/**************************************************************************************************************************************************************/

11. seam_carvingH.cpp 310 lines

function 	BYTE* markHorizontalSeamAbove( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	mark a seam, by finding the first seam seed from the top.

function 	BYTE* markHorizontalSeamBelow (BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	mark a seam, by finding the first seam seed from the bottom.

function 	BYTE* getHDisplacementImage1( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	get displacement map above the seam

function 	BYTE* getHDisplacementImage3( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	get displacement map below the seam


/**************************************************************************************************************************************************************/

12. seam_carvingV.cpp 310 lines

function 	BYTE* markVerticalSeamLeft( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	mark a seam, by finding the first seam seed from the left.

function 	BYTE* markHorizontalSeamBelowxx  (BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	not used anymore.

function 	BYTE* getVDisplacementImage2( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	get displacement map left of the seam

function 	BYTE* getVDisplacementImage4( BYTE* Buffer, int width, int height, int xBegin, int xEnd, int yBegin, int yEnd, BYTE* BoundaryMask, BYTE* SeamMask)
description	get displacement map right of the seam

