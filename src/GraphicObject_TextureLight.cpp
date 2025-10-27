#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "Texture.h"
#include <assert.h>

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderTextureLight* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pTextures = new Texture * [n];
	MeshMaterials = new ShaderTextureLight::Material[n];
	// set default params
	ShaderTextureLight::Material defaultMeshMat = ShaderTextureLight::Material();
	defaultMeshMat.Ambient = Vect(0.5f, 0.5f, 0.5f);
	defaultMeshMat.Diffuse = Vect(0.5f, 0.5f, 0.5f);
	defaultMeshMat.Specular = Vect(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < n; i++)
	{
		pTextures[i] = nullptr;
		MeshMaterials[i] = defaultMeshMat;
	}
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] pTextures;
	delete[] MeshMaterials;
}

void GraphicObject_TextureLight::SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		MeshMaterials[i].Ambient = ambient;
		MeshMaterials[i].Diffuse = diffuse;
		MeshMaterials[i].Specular = specular;
	}
}

void GraphicObject_TextureLight::SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular, int meshnum)
{
	MeshMaterials[meshnum].Ambient = ambient;
	MeshMaterials[meshnum].Diffuse = diffuse;
	MeshMaterials[meshnum].Specular = specular;
}

void GraphicObject_TextureLight::SetTexture(Texture* tex)
{
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pTextures[i] = tex;
	}
}

void GraphicObject_TextureLight::SetTexture(Texture* tex, int meshnum)
{
	pTextures[meshnum] = tex;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_TextureLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshMaterials[i].Ambient, MeshMaterials[i].Diffuse, MeshMaterials[i].Specular);
		pShader->SetTextureResourceAndSampler(pTextures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}