#ifndef _Terrain
#define _Terrain

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class TerrainModel;
class Texture;
class ShaderTextureLight;
struct ID3D11DeviceContext;
struct ID3D11Device;

class Terrain : public Align16
{
public:
	Terrain(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV, Texture* pT, ShaderTextureLight* pS, Vect pos = Vect(0,0,0));
	Terrain() = delete;
	Terrain(const Terrain&) = default;
	Terrain& operator = (const Terrain&) = default;
	~Terrain();

	void Render();
	void SetMaterial(const Vect& ambient, const Vect& diffuse, const Vect& specular);

private:
	TerrainModel* pModTerrain;
	Texture* pTex;
	ShaderTextureLight* pShader;
	Matrix world;
	Vect amb;
	Vect dif;
	Vect sp;
};



#endif _Terrain