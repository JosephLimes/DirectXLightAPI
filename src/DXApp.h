// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderTextureLight.h"
#include "ShaderTexture.h"
#include "ShaderTextureLight.h"
#include "GraphicObject_TextureLight.h"
#include "SkyBox.h"
#include "FlatPlane.h"

class Model;
class Texture;
class FlatPlane;
class Terrain;
class SkyBox;

class DXApp : public Align16
{
private:
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 1;  // 1 for sync to monitor refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	SkyBox* pSky;
	Matrix skyWorld;
	Terrain* pTerrain;
	Terrain* pOutsideTerrain;

	Model* pModLanternTall;
	Model* pModTorii;
	Model* pModTree;
	Model* pModWall;
	Model* pModPlank;
	Model* pModRock05;
	Model* pModTemple;
	Model* pModLanternHanging;

	Texture* pTexSky;
	Texture* pTexGround;
	Texture* pTexLanternTall;
	Texture* pTexTorii;
	Texture* pTexTree;
	Texture* pTexWall;
	Texture* pTexPlank;
	Texture* pTexRock05;
	Texture* pTexTemple;
	Texture* pTexLanternHanging;

	ShaderTexture* pShaderTex;
	ShaderTextureLight* pShaderTexLight;

	GraphicObject_TextureLight* pGOTL_lantern_tall;
	GraphicObject_TextureLight* pGOTL_torii;
	GraphicObject_TextureLight* pGOTL_tree;
	GraphicObject_TextureLight* pGOTL_wall;
	GraphicObject_TextureLight* pGOTL_plank;
	GraphicObject_TextureLight* pGOTL_rock_05;
	GraphicObject_TextureLight* pGOTL_temple;
	GraphicObject_TextureLight* pGOTL_lantern_hanging;

	float lantern_hanging_swing_speed;
	float lantern_cycle_length;
	float lantern_curr_cycle;
	Matrix lantern_rot_offset;
	Matrix lantern_hanging_rot;
	Matrix lantern_hanging_trans;
	Matrix lantern_hanging_world;
	Vect lantern_light_pos;
	Vect lantern_light_att;
	Vect lantern_light_dir;
	Vect lantern_light_amb;
	Vect lantern_light_dif;
	Vect lantern_light_sp;

public:
	DXApp(HWND hwnd);
	virtual ~DXApp();

	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp
