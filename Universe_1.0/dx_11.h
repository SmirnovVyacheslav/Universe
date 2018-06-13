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

class Camera
{

	XMVECTOR eye;// = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	XMVECTOR at;// = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR up;// = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX                _view;
	XMMATRIX                _projection;

	//float xAngle = -3.0f * XM_PI / 4.0f;
	//float yAngle = -3.0f * XM_PI / 4.0f;
	float xAngle = 0.0f;
	float yAngle = -90.0f;
	float radius = 3.0f;
	float sensitivity = 0.1f;

	HWND hWnd;
	int wndWidth, wndHeight, wndX, wndY;
	int topBorder, leftBorder;

	XMMATRIX xRot;
	XMMATRIX yRot;
	XMMATRIX zRot;

	//float radius = 5.0f;
	//float horizontal = 0.0f;
	//float vertial = 1.0f;
	//float step = 0.00002f;
	//float vx = 0.0f, vy = 0.0f, vz = 1.0f;

	int x = 0;
	int y = 0;

public:

	Camera();

	void init(HWND _hWnd);

	XMMATRIX& view();

	XMMATRIX& projection();

	void move(UINT x, UINT y);

	void catchMouse();

	void releseMouse();

	void resize();
};

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
		//ID3D11Buffer*           constantBuffer = nullptr;
		Shader*                 shader = nullptr;
		int size;
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

	ID3D11InputLayout*      vertexLayout = nullptr;

	ID3D11Buffer*           constantBuffer = nullptr;
	ConstantBuffer          localConstantBuffer;


	XMMATRIX                mWorld;
	//XMMATRIX                mView;
	//XMMATRIX                mProjection;

	HWND hWnd;
	UINT wndWidth, wndHeight;

	std::shared_ptr<Geometry> geometry;
	std::shared_ptr<Camera> camera;

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

	void setCamera(std::shared_ptr<Camera> _camera);
};