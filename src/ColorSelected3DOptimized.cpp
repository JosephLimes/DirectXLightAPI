#include "ColorSelected3DOptimized.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>


ColorSelected3DOptimized::ColorSelected3DOptimized(ID3D11Device* device)
	: ShaderBase(device, L"../Assets/Shaders/ColorSelected3DOptimized.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);  
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;  

	// World View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WVPMatrix);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpMatrixBuffer);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ColorData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpColorBuffer);
	assert(SUCCEEDED(hr));

}

ColorSelected3DOptimized::~ColorSelected3DOptimized()
{
	ReleaseAndDeleteCOMobject(mpMatrixBuffer);
	ReleaseAndDeleteCOMobject(mpColorBuffer);
}

void ColorSelected3DOptimized::SendMatrices()
{
	WVPMatrix wvp;
	wvp.WVPmatrix = m_world * m_vp;

	this->GetContext()->UpdateSubresource(mpMatrixBuffer, 0, nullptr, &wvp, 0, 0);
}

void ColorSelected3DOptimized::SendMatrices(const Matrix& world, const Matrix& view, const Matrix& proj)
{
	WVPMatrix wvp;
	wvp.WVPmatrix = world * view * proj;

	this->GetContext()->UpdateSubresource(mpMatrixBuffer, 0, nullptr, &wvp, 0, 0);
}

void ColorSelected3DOptimized::SendColor(const Vect& col)
{
	ColorData cd;
	cd.Color = col;

	this->GetContext()->UpdateSubresource(mpColorBuffer, 0, nullptr, &cd, 0, 0);
}

void ColorSelected3DOptimized::UpdateWorld(const Matrix& world)
{
	m_world = world;
}

void ColorSelected3DOptimized::UpdateVP(const Matrix& view, const Matrix& proj)
{
	m_vp = view * proj;
}

void ColorSelected3DOptimized::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SaveContextPtr(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpMatrixBuffer);
	devcon->VSSetConstantBuffers(1, 1, &mpColorBuffer);
}


