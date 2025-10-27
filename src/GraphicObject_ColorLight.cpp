#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshMaterials = new ShaderColorLight::Material[n];
	for (int i = 0; i < n; i++)
		MeshMaterials[i] = ShaderColorLight::Material();
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{
	delete[] MeshMaterials;
}

void GraphicObject_ColorLight::SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
	{
		MeshMaterials[i].Ambient = ambient;
		MeshMaterials[i].Diffuse = diffuse;
		MeshMaterials[i].Specular = specular;
	}
}

void GraphicObject_ColorLight::SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular, int meshnum)
{
	MeshMaterials[meshnum].Ambient = ambient;
	MeshMaterials[meshnum].Diffuse = diffuse;
	MeshMaterials[meshnum].Specular = specular;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_ColorLight::Render()
{
	pModel->SetToContext(pShader->GetContext());
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshMaterials[i].Ambient, MeshMaterials[i].Diffuse, MeshMaterials[i].Specular);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}