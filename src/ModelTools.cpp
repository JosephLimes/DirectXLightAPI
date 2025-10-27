#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	Vect up = Vect(0, 1, 0);
	Vect right = Vect(-1, 0, 0);
	Vect forward = Vect(0, 0, 1);
	//Vect back = -forward;

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, forward, Colors::Blue);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, forward, Colors::Blue);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, forward, Colors::Blue);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, forward, Colors::Blue);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, -forward, Colors::Yellow);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, -forward, Colors::Yellow);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, -forward, Colors::Yellow);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -forward, Colors::Yellow);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, -right, Colors::Cyan);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, -right, Colors::Cyan);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, -right, Colors::Cyan);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -right, Colors::Cyan);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, right, Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, right, Colors::Red);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, right, Colors::Red);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, right, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, up, Colors::Green);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, up, Colors::Green);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, up, Colors::Green);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, up, Colors::Green);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, -up, Colors::Magenta);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, -up, Colors::Magenta);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, -up, Colors::Magenta);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -up, Colors::Magenta);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.25, 0.625, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.25, 0.375, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 0.375, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0, 0.625, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5, 0.625, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5, 0.375, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75, 0.375, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75, 0.625, 0, 0, -1);
	/*
	// used to demo texture address modes
	pVerts[vind].set(0.5f, 0.5f, -0.5f, -3, -3);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 3, -3);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 3, 3);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, -3, 3);
	//*/
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5, 0.625, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.25, 0.625, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.25, 0.875, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.5, 0.875, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.25, 0.375, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5, 0.375, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.5, 0.125, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.25, 0.125, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.5, 0.375, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.5, 0.625, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.25, 0.625, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.25, 0.375, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0.625, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 1, 0.375, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.75, 0.375, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.75, 0.625, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	Vect bot = Vect(0, -1, 0);
	Vect l = Vect(-0.707107, 0.707107, 0);
	Vect b = Vect(0, 0.707107, 0.707107);
	Vect r = Vect(0.707107, 0, 0.707107);
	Vect f = Vect(0.707107, 0, -0.707107);\

	// bottom face
	pVerts[0].set(-0.5f, -0.5f, -0.5f, bot, Colors::Black);
	pVerts[1].set(-0.5f, -0.5f, +0.5f, bot, Colors::Black);
	pVerts[2].set(+0.5f, -0.5f, -0.5f, bot, Colors::Black);
	pVerts[3].set(+0.5f, -0.5f, +0.5f, bot, Colors::Black);
	pTriList[0].set(2, 1, 0);
	pTriList[1].set(3, 1, 2);

	// left face
	pVerts[4].set(-0.5f, -0.5f, +0.5f, l, Colors::Red);
	pVerts[5].set(+0.0f, +0.5f, +0.0f, l, Colors::Red);
	pVerts[6].set(-0.5f, -0.5f, -0.5f, l, Colors::Red);
	pTriList[2].set(4, 5, 6);

	// back face
	pVerts[7].set(+0.5f, -0.5f, +0.5f, b, Colors::Blue);
	pVerts[8].set(+0.0f, +0.5f, +0.0f, b, Colors::Blue);
	pVerts[9].set(-0.5f, -0.5f, +0.5f, b, Colors::Blue);
	pTriList[3].set(7, 8, 9);

	// right face
	pVerts[10].set(+0.0f, +0.5f, +0.0f, r, Colors::Green);
	pVerts[11].set(+0.5f, -0.5f, +0.5f, r, Colors::Green);
	pVerts[12].set(+0.5f, -0.5f, -0.5f, r, Colors::Green);
	pTriList[4].set(10, 11, 12);


	// front face
	pVerts[13].set(+0.0f, +0.5f, +0.0f, f, Colors::Yellow);
	pVerts[14].set(+0.5f, -0.5f, -0.5f, f, Colors::Yellow);
	pVerts[15].set(-0.5f, -0.5f, -0.5f, f, Colors::Yellow);
	pTriList[5].set(13, 14, 15);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// bottom face
	pVerts[0].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pVerts[1].set(-0.5f, -0.5f, +0.5f, 1, 0, 0, -1, 0);
	pVerts[2].set(+0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[3].set(+0.5f, -0.5f, +0.5f, 0, 0, 0, -1, 0);
	pTriList[0].set(2, 1, 0);
	pTriList[1].set(3, 1, 2);

	//Vect normal;
	//Vect p1;
	//Vect p2;
	//Vect p3;
	//Vect e1;
	//Vect e2;
	//p1 = Vect(+0.0f, +0.5f, +0.0f);
	//p2 = Vect(+0.5f, -0.5f, +0.5f);
	//p2 = Vect (+0.5f, -0.5f, -0.5f);
	//e1 = p1 - p2;
	//e2 = p2 - p3;
	//normal = e2.cross(e1);
	//normal.norm();

	// left face
	pVerts[4].set(-0.5f, -0.5f, +0.5f, 1, 1, -0.707107, 0.707107, 0);
	pVerts[5].set(+0.0f, +0.5f, +0.0f, 0.5, 0, -0.707107, 0.707107, 0);
	pVerts[6].set(-0.5f, -0.5f, -0.5f, 0, 1, -0.707107, 0.707107, 0);
	pTriList[2].set(4, 5, 6);
	
	// back face
	pVerts[7].set(+0.5f, -0.5f, +0.5f, 1, 1, 0, 0.707107, 0.707107);
	pVerts[8].set(+0.0f, +0.5f, +0.0f, 0.5, 0, 0, 0.707107, 0.707107);
	pVerts[9].set(-0.5f, -0.5f, +0.5f, 0, 1, 0, 0.707107, 0.707107);
	pTriList[3].set(7, 8, 9);

	// right face
	pVerts[10].set(+0.0f, +0.5f, +0.0f, 0.5, 0, 0.707107, 0, 0.707107);
	pVerts[11].set(+0.5f, -0.5f, +0.5f, 0, 1, 0.707107, 0, 0.707107);
	pVerts[12].set(+0.5f, -0.5f, -0.5f, 1, 1, 0.707107, 0, 0.707107);
	pTriList[4].set(10, 11, 12);


	// front face
	pVerts[13].set(+0.0f, +0.5f, +0.0f, 0.5, 0, 0.707107, 0, -0.707107);
	pVerts[14].set(+0.5f, -0.5f, -0.5f, 0, 1, 0.707107, 0, -0.707107);
	pVerts[15].set(-0.5f, -0.5f, -0.5f, 1, 1, 0.707107, 0, -0.707107);
	pTriList[5].set(13, 14, 15);
}