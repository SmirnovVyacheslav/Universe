#include "dx_11.h"

Camera::Camera()
{
	eye = XMVectorSet(0.0f, 1.0f, -4.0f, 0.0f);
	at = XMVectorSet(0.0f, 3.0f, 0.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
}

void Camera::init(UINT _wndWidth, UINT _wndHeight)
{
	wndWidth = _wndWidth;
	wndHeight = _wndHeight;

	_view = XMMatrixLookAtLH(eye, at, up);
	_projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, wndWidth / (FLOAT)wndHeight, 0.01f, 100.0f);
}

XMMATRIX& Camera::view()
{
	return _view;
}

XMMATRIX& Camera::projection()
{
	return _projection;
}

void Camera::move(UINT _x, UINT _y)
{
	int xDiff = static_cast<int>(_x) - x;
	int yDiff = y - static_cast<int>(_y);

	x = static_cast<int>(_x);
	y = static_cast<int>(_y);

	if (abs(xDiff) > 200 || abs(yDiff) > 200)
	{
		return;
	}

	
	/*xAngle = (static_cast<float>(xDiff) / static_cast<float>(wndWidth)) * 2 * XM_PI * sensitivity;
	yAngle = (static_cast<float>(yDiff) / static_cast<float>(wndHeight)) * 2 * XM_PI * sensitivity;*/

	xAngle += (static_cast<float>(xDiff) / static_cast<float>(wndWidth)) * 2 * XM_PI * sensitivity;
	yAngle += (static_cast<float>(yDiff) / static_cast<float>(wndHeight)) * 2 * XM_PI * sensitivity;
	if (abs(xAngle) > XM_PI)
	{
		xAngle = xAngle > 0 ? xAngle - 2 * XM_PI : xAngle + 2 * XM_PI;
	}

	if (abs(yAngle) > XM_PI)
	{
		yAngle = yAngle > 0 ? yAngle - 2 * XM_PI : yAngle + 2 * XM_PI;
	}

	float vx = cos(xAngle) + sin(xAngle) * sin(yAngle) + sin(xAngle) * cos(yAngle);
	float vy = cos(yAngle) - sin(yAngle);
	float vz = -sin(xAngle) + cos(xAngle) * sin(yAngle) + cos(xAngle) * cos(yAngle);

	//float vx = cos(xAngle) + sin(xAngle);
	//float vy = 1;
	//float vz = -sin(xAngle) + cos(xAngle);

	/*float vx = 1;
	float vy = cos(yAngle) - sin(yAngle);
	float vz = tan(yAngle) + cos(yAngle);*/


	//eye = XMVectorSet((cos(xAngle) - sin(xAngle)) * radius, 1.0f, (sin(xAngle) + cos(xAngle)) * radius, 0.0f);
	
	/*xRot = XMMatrixRotationX(xAngle);
	yRot = XMMatrixRotationY(yAngle);
	eye = XMVector4Transform(eye, xRot * yRot);*/

	
	eye = XMVectorSet(vx * radius, vy* radius, vz * radius, 0.0f);

	/*if (xDiff > 0)
	{

	}
	else
	{

	}*/



	/*horizontal += (x - _x) * step;
	vertial += (y - _y) * step;
	x = _x;
	y = _y;*/

	//eye = XMVectorSet(cos(horizontal)*radius, 1.0f, -sin(horizontal)*radius, 0.0f);

	/*vx += _x * step;
	vy += _y * step;

	float vr = sqrt(vx * vx + vy * vy + vz * vz);

	float vtx = sin(vx) * sin(vy) * vr;
	float vty = cos(vy) * vr;
	float vtz = sin(vy) * cos(vx) * vr;
	eye = XMVectorSet(vtx * radius, 1.0f, vtz * radius, 0.0f);*/

	_view = XMMatrixLookAtLH(eye, at, up);
}

dx_11::dx_11(HWND _hWnd) : hWnd(_hWnd)
{
	setWndSize();
}

dx_11::~dx_11()
{
	if (immediateContext) immediateContext->ClearState();

	//if (g_pConstantBuffer) g_pConstantBuffer->Release();
	//if (g_pVertexBuffer) g_pVertexBuffer->Release();
	//if (g_pIndexBuffer) g_pIndexBuffer->Release();
	if (vertexLayout) vertexLayout->Release();
	//if (g_pVertexShader) g_pVertexShader->Release();
	//if (g_pPixelShader) g_pPixelShader->Release();
	if (renderTargetView) renderTargetView->Release();
	if (swapChain) swapChain->Release();
	if (immediateContext) immediateContext->Release();
	if (d3dDevice) d3dDevice->Release();
}

void dx_11::setWndSize()
{
	RECT wndSize;

	GetClientRect(hWnd, &wndSize);
	wndWidth = wndSize.right - wndSize.left;
	wndHeight = wndSize.bottom - wndSize.top;
};

bool dx_11::createDevice()
{
	HRESULT result = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	std::vector<D3D_DRIVER_TYPE> driverTypes
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	
	std::vector<D3D_FEATURE_LEVEL> featureLevels
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = wndWidth;
	swapChainDesc.BufferDesc.Height = wndHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	for (auto type: driverTypes)
	{
		driverType = type;
		if (result = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags,
			&featureLevels.front(), featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc,
			&swapChain, &d3dDevice, &featureLevel, &immediateContext) >= 0)
			break;
	}
	if (result < 0) return false;

	// Создание рендер-таргета
	ID3D11Texture2D* backBuffer = NULL;
	if (swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer) < 0)
		return false;

	result = d3dDevice->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();
	if (result < 0) return false;

	// Создание поверхности для Z-буфера
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = wndWidth;
	descDepth.Height = wndHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	if (d3dDevice->CreateTexture2D(&descDepth, NULL, &depthStencil))
		return false;

	// Создание z-буфреа
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	if (d3dDevice->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView))
		return false;

	immediateContext->OMSetRenderTargets(1, &renderTargetView, 0);

	// Setup the viewport
	D3D11_VIEWPORT viewPort;
	viewPort.Width = static_cast<float>(wndWidth);
	viewPort.Height = static_cast<float>(wndHeight);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	immediateContext->RSSetViewports(1, &viewPort);


	// Создание буфера констант шейдера
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ConstantBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	if (d3dDevice->CreateBuffer(&bufferDesc, NULL, &constantBuffer) < 0)
		return false;

	return true;
}

bool dx_11::initShader(std::wstring path, Shader* shader)
{
	// Загружаем шейдеры
	ID3DBlob* blob = NULL;
	HRESULT hr;
	if (!compileShader(path, "VS", "vs_4_0", &blob))
	{
		MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return false;
	}

	// Вершинный шейдер
	if (d3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader->vertexShader) < 0)
	{
		blob->Release();
		return false;
	}

	// Определение формата вершинного буфера
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		/*{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }*/
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	// Создание формата буфера
	hr = d3dDevice->CreateInputLayout(layout, numElements, blob->GetBufferPointer(),
		blob->GetBufferSize(), &vertexLayout);
	blob->Release();
	if (FAILED(hr))
		return false;

	// Установка формата буфера
	immediateContext->IASetInputLayout(vertexLayout);

	// Пиксельный шейдер
	blob = NULL;
	if (compileShader(path, "PS", "ps_4_0", &blob) < 0)
	{
		MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return false;
	}

	// Пиксельный шейдер
	hr = d3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader->pixelShader);
	blob->Release();
	if (FAILED(hr))
		return false;

	return true;
}

bool dx_11::compileShader(std::wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut)
{
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBlob;
	if (D3DX11CompileFromFile(path.c_str(), NULL, NULL, type, shaderModel,
		dwShaderFlags, 0, NULL, blobOut, &errorBlob, NULL) < 0)
	{
		if (errorBlob != NULL)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
		return false;
	}
	if (errorBlob) errorBlob->Release();

	return true;
}

//--------------------------------------------------------------------------------------
// Рендер
//--------------------------------------------------------------------------------------

void dx_11::render()
{
	
	//
	// Установка трансформации для куба
	//
	//mWorld = XMMatrixRotationY(3.14159f / 4.0f);

	//
	// Очистка рендер-таргета
	//
	float ClearColor[4] = { 0.0f, 0.9f, 0.5f, 1.0f }; // цвет
	immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//
	// Установка констант шейдера
	//
	localConstantBuffer.mWorld = XMMatrixTranspose(mWorld);
	localConstantBuffer.mView = XMMatrixTranspose(camera->view());
	localConstantBuffer.mProjection = XMMatrixTranspose(camera->projection());

	bool first = true;
	for (auto obj : gObjects)
	{
		//
		// Установка констант шейдера
		//

		if (first)
		{
			first = false;
			localConstantBuffer.mWorld = XMMatrixTranspose(XMMatrixTranslation(6.0f, 0, 0));
		}
		else
		{
			localConstantBuffer.mWorld = XMMatrixTranspose(mWorld);
		}

		/*ConstantBuffer cb;
		cb.mWorld = XMMatrixTranspose(mWorld);
		cb.mView = XMMatrixTranspose(camera->view());
		cb.mProjection = XMMatrixTranspose(camera->projection());*/
		immediateContext->UpdateSubresource(constantBuffer, 0, NULL, &localConstantBuffer, 0, 0);

		//
		// Установка шейдера
		//

		immediateContext->VSSetShader(obj->shader->vertexShader, NULL, 0);
		immediateContext->PSSetShader(obj->shader->pixelShader, NULL, 0);

		immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);

		//
		// Рендер куба
		//
		
		immediateContext->DrawIndexed(obj->size, 0, 0);
	}

	//
	// Вывод на экран содержимого рендер-таргета
	//
	swapChain->Present(0, 0);
}

void dx_11::setGeometry(std::shared_ptr<Geometry> _geometry)
{
	geometry =_geometry;

	for (auto it : *geometry)
	//for (std::vector<Object*>::iterator& it = geometry->begin(); it != geometry->end(); ++it)
	{
		Shader *shader;
		if (!shaders[it->shader])
		{
			shader = new Shader;
			initShader(it->shader, shader);
			shaders[it->shader] = shader;
		}
		else
		{
			shader = shaders[it->shader];
		}

		GObjects *gObject = new GObjects;
		gObjects.push_back(gObject);

		gObject->shader = shader;
		gObject->size = it->size;


		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));

		// Создание вершинного буфера
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(SimpleVertex) * it->vertices.size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;

		InitData.pSysMem = &it->vertices[0];
		if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &gObject->vertexBuffer) < 0)
			return;

		// Установка вершинного буфера
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		immediateContext->IASetVertexBuffers(0, 1, &gObject->vertexBuffer, &stride, &offset);

		// Создание индексного буфера
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(DWORD) * it->indices.size();
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;

		InitData.pSysMem = &it->indices[0];
		if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &gObject->indexBuffer) < 0)
			return;

		// Установка индексного буфера
		immediateContext->IASetIndexBuffer(gObject->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Установка типа примитив
		immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		//D3D11_BUFFER_DESC bufferDesc;
		//ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//bufferDesc.ByteWidth = sizeof(SimpleVertex) * 8;
		//bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//bufferDesc.CPUAccessFlags = 0;
		//
		//D3D11_SUBRESOURCE_DATA InitData;
		//ZeroMemory(&InitData, sizeof(InitData));
		//InitData.pSysMem = &it->vertices[0];
		//if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &gObject->vertexBuffer) < 0)
		//	return;

		//// Установка вершинного буфера
		//UINT stride = sizeof(SimpleVertex);
		//UINT offset = 0;
		//immediateContext->IASetVertexBuffers(0, 1, &gObject->vertexBuffer, &stride, &offset);

		//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//bufferDesc.ByteWidth = sizeof(WORD) * it->indices.size();        // 36 vertices needed for 12 triangles in a triangle list
		//bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//bufferDesc.CPUAccessFlags = 0;
		//InitData.pSysMem = &it->indices[0];
		//if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &gObject->indexBuffer) < 0)
		//	return;

		//// Установка индексного буфера
		//immediateContext->IASetIndexBuffer(gObject->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//// Установка типа примитив
		//immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//// Создание буфера констант шейдера
		//bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		//bufferDesc.ByteWidth = sizeof(ConstantBuffer);
		//bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//bufferDesc.CPUAccessFlags = 0;
		//if (d3dDevice->CreateBuffer(&bufferDesc, NULL, &gObject->constantBuffer) < 0)
		//	return;
	}

	// Установка матриц
	mWorld = XMMatrixIdentity();
	//XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
	//XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//mView = XMMatrixLookAtLH(Eye, At, Up);
	//mProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2, wndWidth / (FLOAT)wndHeight, 0.01f, 100.0f);
}

void dx_11::setCamera(std::shared_ptr<Camera> _camera)
{
	camera = _camera;

	camera->init(wndWidth, wndHeight);
}