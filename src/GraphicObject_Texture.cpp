#include "GraphicObject_Texture.h"
#include "Model.h"
#include "Texture.h"
#include "ShaderColor.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pTextures = new Texture*[n];
	for (int i = 0; i < n; i++)
		pTextures[i] = nullptr;
}

GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] pTextures;
}

void GraphicObject_Texture::SetTexture(Texture* tex)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pTextures[i] = tex;
	}
}

void GraphicObject_Texture::SetTexture(Texture* tex, int meshnum)
{
	pTextures[meshnum] = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_Texture::Render()
{
	pModel->SetToContext(pShader->GetContext());
	pShader->SendWorld(World);
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(pTextures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}