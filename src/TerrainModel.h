#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{
public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainModel() = delete;
	TerrainModel(const TerrainModel&) = default;
	TerrainModel& operator = (const TerrainModel&) = default;
	~TerrainModel();

	void Render(ID3D11DeviceContext* context);

private:
	Model* pModTerrain;
	size_t side;
	const size_t pixel_width = 4;

	uint8_t GetTexel(const DirectX::Image* hgtmap, int x, int y);

};



#endif _TerrainModel