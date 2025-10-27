#ifndef _ColorSelected3DOptimized
#define _ColorSelected3DOptimized

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ColorSelected3DOptimized : public ShaderBase
{
public:
	ColorSelected3DOptimized(const ColorSelected3DOptimized&) = delete;				 
	ColorSelected3DOptimized(ColorSelected3DOptimized&&) = default;                  
	ColorSelected3DOptimized& operator=(const ColorSelected3DOptimized&) & = default;
	ColorSelected3DOptimized& operator=(ColorSelected3DOptimized&&) & = default;     
	~ColorSelected3DOptimized();		  							         

	ColorSelected3DOptimized(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SendMatrices();
	void SendMatrices(const Matrix& world, const Matrix& view, const Matrix& proj);
	void SendColor(const Vect& col);

	void UpdateWorld(const Matrix& world);
	void UpdateVP(const Matrix& view, const Matrix& proj);

private:
	struct WVPMatrix
	{
		Matrix WVPmatrix;
	};

	ID3D11Buffer*           mpMatrixBuffer;

	struct ColorData
	{
		Vect Color;
	};

	ID3D11Buffer*           mpColorBuffer;

	Matrix					m_world;
	Matrix					m_vp;
};

#endif _ColorSelected3DOptimized
