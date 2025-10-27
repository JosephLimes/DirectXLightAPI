#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	dev, heightmapFile, len, maxheight, ytrans, RepeatU, RepeatV;
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width );

	side = hgtmap->height;	// the image should be square

	int nverts = side * side;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = (side - 1) * (side - 1) * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	Vect up = Vect(0, 1, 0); // temp for normals

	// set verts
	for (int y = 0; y < side; y++) // for each vert row
	{
		for (int x = 0; x < side; x++) // for each vert in row
		{
			// find height value
			uint8_t hval = GetTexel(hgtmap, x, y);
			// find coordinates
			float offset = len / 2;
			float posY = ((hval * maxheight) / 255) + ytrans;
			float posX = offset - (x * len) / side;
			float posZ = offset - (y * len) / side;
			// find uvs
			float u = float(x) / float(side - 1) * RepeatU;
			float v = float(y) / float(side - 1) * RepeatV;
			int index = x + (y * side);
			pVerts[index].set(posX, posY, posZ, u, v, up, Colors::Aqua);
		}
	}

	// set tris
	int triIndex = 0;
	for (int triRow = 0; triRow < side - 1; triRow++) // for each triangle row
	{
		for (int t = 0; t < (side - 1) * 2; t++) // for each triangle in triangle row
		{
			int m = triIndex / (2 * (side - 1));
			if (t % 2 == 0) // even indexed triangle, top heavy
			{
				int v0 = side * m + (t / 2);
				int v1 = side * (m + 1) + (t / 2);
				int v2 = side * m + (t / 2) + 1;
				pTriList[triIndex].set(v0, v1, v2);
			}
			else // odd indexed triangle, bottom heavy
			{
				int v0 = side * m + (t / 2) + 1;
				int v1 = side * (m + 1) + (t / 2);
				int v2 = side * (m + 1) + (t / 2) + 1;
				pTriList[triIndex].set(v0, v1, v2);
			}
			triIndex++;
		}
	}
	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);
	delete[] pVerts;
	delete[] pTriList;
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}

uint8_t TerrainModel::GetTexel(const DirectX::Image* hgtmap, int x, int y)
{
	return hgtmap->pixels[pixel_width * (y * side + x)];
}
