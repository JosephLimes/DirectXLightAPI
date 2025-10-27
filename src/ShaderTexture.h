#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
#include "Matrix.h"

class Texture;

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(const ShaderTexture&) = delete;
	ShaderTexture(ShaderTexture&&) = default;
	ShaderTexture& operator=(const ShaderTexture&) & = default;
	ShaderTexture& operator=(ShaderTexture&&) & = default;
	~ShaderTexture();

	ShaderTexture(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);

	void SendViewProj(const Matrix& view, const Matrix& proj);
	void SendWorld(const Matrix& world);

private:
	struct VPMatrices
	{
		Matrix view;
		Matrix proj;
	};

	ID3D11Buffer* mpVPBuffer;

	struct WorldMatrix
	{
		Matrix world;
	};

	ID3D11Buffer* mpWorldBuffer;

	Matrix					m_vp;
	Matrix					m_w;
};

#endif _ShaderTexture
