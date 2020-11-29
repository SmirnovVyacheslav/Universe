#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include <windows.h>

#include <vector>
#include <memory>
#include <unordered_map>
#include <xnamath.h>

#include "camera.h"
#include "geometry.h"

using std::vector;
using std::wstring;
using std::shared_ptr;
using std::unordered_map;
using std::pair;

class DX_11
{
	//--------------------------------------------------------------------------------------
	// Структуры
	//--------------------------------------------------------------------------------------
	struct ConstantBuffer
	{
		XMMATRIX mWorld;//0
		XMMATRIX mView;//64
		XMMATRIX mProjection;//128
		XMFLOAT4 light_color;//144
		XMFLOAT4 light_pos;//160
		//XMFLOAT4 plane_def[80];//1120
		//XMFLOAT4 plane_color[80];//2080
		//XMFLOAT4 plane_num;//2096 num, curr_obj, tmp_1, tmp_2
	};

	struct ConstantBuffer_2
	{
		XMFLOAT4 color;//obj color
		//XMFLOAT4 plane_num;//2096 num, curr_obj, tmp_1, tmp_2
	};

	struct Shader
	{
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11PixelShader*  pixelShader = nullptr;
	};

	struct GPUData
	{
		int           size;
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;
		Math_3d::Vector_4d color;
	};

	//--------------------------------------------------------------------------------------
	// Переменные устройства
	//--------------------------------------------------------------------------------------

	D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;

	ID3D11Device*           d3dDevice = nullptr;
	ID3D11DeviceContext*    immediateContext = nullptr;
	IDXGISwapChain*         swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;

	ID3D11Texture2D*        depthStencil = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;

	ID3D11InputLayout*      vertexLayout = nullptr;

	ID3D11Buffer*           constantBuffer = nullptr;
	ID3D11Buffer*           constantBuffer_2 = nullptr;
	ConstantBuffer          localConstantBuffer;
	ConstantBuffer_2          localConstantBuffer_2;

	D3D11_VIEWPORT viewPort;

	//============Создание поверхности для Z-буфера============
	ID3D11DepthStencilState*      pDSState;
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

	//================D3D11_RASTERIZER_DESC rasterDesc;==========
	D3D11_RASTERIZER_DESC rasterDesc;
	ID3D11RasterizerState *m_rasterState;

	HWND hWnd;
	int  wndWidth;
	int  wndHeight;

	shared_ptr<Camera>   camera;
	shared_ptr<Geometry::Geometry> geometry;

	// Shaders
	Shader* main_shader;
	Shader* shadow_map_shader;

	XMMATRIX                mWorld;

	vector<pair<Geometry::Object_Data*, GPUData*>>           objects;

	
	// Shadow_map
	//=============================================================================
	ID3D11Texture2D* m_shadowMap;
	ID3D11DepthStencilView* m_shadowDepthView;
	ID3D11ShaderResourceView* m_shadowResourceView;
	// Shadow_map
	//=============================================================================

	bool createShader(std::wstring path, Shader* shader);

	bool compileShader(std::wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut);

	bool createDevice();

	bool create_shaders();

	// Shadow_map
	//=============================================================================
	bool create_shadow_map_texture(int m_shadowMapDimension);
	bool create_depth_stencil_view();
	bool create_shader_resource_view();
	// Shadow_map
	//=============================================================================

public:

	DX_11(HWND _hWnd);

	~DX_11();

	bool init();

	void render();

	void setGeometry(std::shared_ptr<Geometry::Geometry> _geometry);

	void setCamera(std::shared_ptr<Camera> _camera);

	void updateGeometry();
};
