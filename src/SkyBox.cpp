#include "SkyBox.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderTexture.h"

SkyBox::~SkyBox()
{
	delete m_pBox;
}

SkyBox::SkyBox(ID3D11Device* dev, int dimension, Texture* pTex, ShaderTexture* pShader)
	: m_pDevice(dev), m_pSky(pTex), m_pShader(pShader)
{
	// set up model
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float dimensionf = (float)dimension / 2.0f;
	float onethird = 1.0f / 3.0f;
	float twothirds = 2.0f / 3.0f;

	// faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(dimensionf, dimensionf, dimensionf, 0.25, onethird);
	pVerts[vind + 1].set(-dimensionf, dimensionf, dimensionf, 0.5, onethird);
	pVerts[vind + 2].set(-dimensionf, -dimensionf, dimensionf, 0.5, twothirds);
	pVerts[vind + 3].set(dimensionf, -dimensionf, dimensionf, 0.25, twothirds);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(dimensionf, dimensionf, -dimensionf, 1, onethird);
	pVerts[vind + 1].set(-dimensionf, dimensionf, -dimensionf, 0.75, onethird);
	pVerts[vind + 2].set(-dimensionf, -dimensionf, -dimensionf, 0.75, twothirds);
	pVerts[vind + 3].set(dimensionf, -dimensionf, -dimensionf, 1, twothirds);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(dimensionf, dimensionf, -dimensionf, 0, onethird);
	pVerts[vind + 1].set(dimensionf, dimensionf, dimensionf, 0.25, onethird);
	pVerts[vind + 2].set(dimensionf, -dimensionf, dimensionf, 0.25, twothirds);
	pVerts[vind + 3].set(dimensionf, -dimensionf, -dimensionf, 0, twothirds);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-dimensionf, dimensionf, dimensionf, 0.5, onethird);
	pVerts[vind + 1].set(-dimensionf, dimensionf, -dimensionf, 0.75, onethird);
	pVerts[vind + 2].set(-dimensionf, -dimensionf, -dimensionf, 0.75, twothirds);
	pVerts[vind + 3].set(-dimensionf, -dimensionf, dimensionf, 0.5, twothirds);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(dimensionf, dimensionf, -dimensionf, 0.25, 0);
	pVerts[vind + 1].set(-dimensionf, dimensionf, -dimensionf, 0.5, 0);
	pVerts[vind + 2].set(-dimensionf, dimensionf, dimensionf, 0.5, onethird);
	pVerts[vind + 3].set(dimensionf, dimensionf, dimensionf, 0.25, onethird);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(dimensionf, -dimensionf, dimensionf, 0.25, twothirds);
	pVerts[vind + 1].set(-dimensionf, -dimensionf, dimensionf, 0.5, twothirds);
	pVerts[vind + 2].set(-dimensionf, -dimensionf, -dimensionf, 0.5, 1);
	pVerts[vind + 3].set(dimensionf, -dimensionf, -dimensionf, 0.25, 1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// model
	m_pBox = new Model(m_pDevice, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

void SkyBox::Render()
{
	m_pShader->SendWorld(m_world);
	m_pShader->SetTextureResourceAndSampler(m_pSky);
	m_pBox->SetToContext(m_pShader->GetContext());
	m_pBox->Render(m_pShader->GetContext());
}

void SkyBox::SetWorld(const Matrix& world)
{
	m_world = world;
}