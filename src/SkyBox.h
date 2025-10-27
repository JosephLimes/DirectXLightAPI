#ifndef _SkyBox
#define _SkyBox

#include "Matrix.h"

class Model;
class Texture;
class ShaderTexture;
struct ID3D11DeviceContext;
struct ID3D11Device;

class SkyBox : public Align16
{
private:
	ID3D11Device*	m_pDevice;

	Model*			m_pBox;
	Texture*		m_pSky;
	ShaderTexture*	m_pShader;

	Matrix			m_world;

public:
	SkyBox(const SkyBox&) = delete;
	SkyBox(Model&&) = delete;
	SkyBox& operator=(const SkyBox&) & = delete;
	SkyBox& operator=(SkyBox&&) & = delete;
	~SkyBox();

	SkyBox(ID3D11Device* dev, int dimension, Texture* pTex, ShaderTexture* pShader);

	void Render();

	void SetWorld(const Matrix& world);

};

#endif _SkyBox