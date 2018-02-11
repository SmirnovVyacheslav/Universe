#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

#include <windows.h>

#include <vector>
#include <memory>
#include <unordered_map>

#include "geometry.h"

#include <xnamath.h>

class dx_11
{
	//--------------------------------------------------------------------------------------
	// Структуры
	//--------------------------------------------------------------------------------------
	struct ConstantBuffer
	{
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
	};

	struct Shader
	{
		ID3D11VertexShader*     vertexShader = nullptr;
		ID3D11PixelShader*      pixelShader = nullptr;
	};

	struct GObjects
	{
		ID3D11Buffer*           vertexBuffer = nullptr;
		ID3D11Buffer*           indexBuffer = nullptr;
		ID3D11Buffer*           constantBuffer = nullptr;
		Shader*                 shader = nullptr;
	};

	//--------------------------------------------------------------------------------------
	// Переменные устройства
	//--------------------------------------------------------------------------------------

	D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;
	
	ID3D11Device*           d3dDevice = nullptr;
	ID3D11DeviceContext*    immediateContext = nullptr;
	IDXGISwapChain*         swapChain = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;

	ID3D11Texture2D*        depthStencil = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	
	//ID3D11Buffer*           vertexBuffer = nullptr;
	//ID3D11Buffer*           indexBuffer = nullptr;
	//ID3D11Buffer*           constantBuffer = nullptr;

	ID3D11InputLayout*      vertexLayout = nullptr;


	XMMATRIX                mWorld;
	XMMATRIX                mView;
	XMMATRIX                mProjection;

	HWND hWnd;
	UINT wndWidth, wndHeight;

	std::shared_ptr<Geometry> geometry;

	std::unordered_map<std::wstring, Shader*> shaders;

	std::vector<GObjects*> gObjects;

	void setWndSize();

	bool initShader(std::wstring path, Shader* shader);

	bool compileShader(std::wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut);

public:

	dx_11(HWND _hWnd);

	~dx_11();

	bool createDevice();

	void render();

	void setGeometry(std::shared_ptr<Geometry> _geometry);
};