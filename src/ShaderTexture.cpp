#include "ShaderTexture.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "Texture.h"


ShaderTexture::ShaderTexture(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/Texture.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;  

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VPMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpVPBuffer);
	assert(SUCCEEDED(hr));

	// World buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WorldMatrix);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpWorldBuffer);
	assert(SUCCEEDED(hr));

}

ShaderTexture::~ShaderTexture()
{
	ReleaseAndDeleteCOMobject(mpVPBuffer);
	ReleaseAndDeleteCOMobject(mpWorldBuffer);
}

void ShaderTexture::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SaveContextPtr(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpVPBuffer);
	devcon->VSSetConstantBuffers(1, 1, &mpWorldBuffer);
}

void ShaderTexture::SetTextureResourceAndSampler(Texture* tex)
{
	tex->SetToContext(GetContext());
}

void ShaderTexture::SendViewProj(const Matrix& view, const Matrix& proj)
{
	VPMatrices vp;
	vp.view = view;
	vp.proj = proj;

	this->GetContext()->UpdateSubresource(mpVPBuffer, 0, nullptr, &vp, 0, 0);
}

void ShaderTexture::SendWorld(const Matrix& world)
{
	WorldMatrix w;
	w.world = world;

	this->GetContext()->UpdateSubresource(mpWorldBuffer, 0, nullptr, &w, 0, 0);
}


