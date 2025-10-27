#include "Terrain.h"
#include "TerrainModel.h"
#include "ShaderTextureLight.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


Terrain::Terrain(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, Texture* pT, ShaderTextureLight* pS, Vect pos)
{
	pModTerrain = new TerrainModel(dev, heightmapFile, len, maxheight, ytrans, RepeatU, RepeatV);
	pTex = pT;
	pShader = pS;
	world = Matrix(TRANS, pos);
}

Terrain::~Terrain()
{
	delete pModTerrain;
}

void Terrain::SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular)
{
	amb = ambient;
	dif = diffuse;
	sp = specular;
}

void Terrain::Render()
{
	pShader->SendWorldAndMaterial(world, amb, dif, sp);
	pShader->SetTextureResourceAndSampler(pTex);
	pModTerrain->Render(pShader->GetContext());
}