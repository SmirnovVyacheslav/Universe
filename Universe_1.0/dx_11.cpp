#include "dx_11.h"

DX_11::DX_11(HWND _hWnd) : hWnd(_hWnd)
{
	RECT wndSize;
	GetClientRect(hWnd, &wndSize);
	wndWidth  = static_cast<int>(wndSize.right - wndSize.left);
	wndHeight = static_cast<int>(wndSize.bottom - wndSize.top);
}

DX_11::~DX_11()
{
	if (immediateContext) immediateContext->ClearState();
	if (vertexLayout) vertexLayout->Release();
	if (renderTargetView) renderTargetView->Release();
	if (swapChain) swapChain->Release();
	if (immediateContext) immediateContext->Release();
	if (d3dDevice) d3dDevice->Release();

	if (depthStencil) depthStencil->Release();
	if (depthStencilView) depthStencilView->Release();

	if (constantBuffer) constantBuffer->Release();
	if (constantBuffer_2) constantBuffer_2->Release();

	if (pDSState) pDSState->Release();

	if (m_rasterState) m_rasterState->Release();
}

bool DX_11::init()
{

	if (!createDevice())
	{
		return false;
	}

	if (!create_shaders())
	{
		return false;
	}

	create_shadow_map_texture();
	create_depth_stencil_view();
	create_shader_resource_view();

	return true;
}

bool DX_11::create_shadow_map_texture()
{
	D3D11_TEXTURE2D_DESC shadowMapDesc;
	ZeroMemory(&shadowMapDesc, sizeof(D3D11_TEXTURE2D_DESC));
	shadowMapDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	shadowMapDesc.MipLevels = 1;
	shadowMapDesc.ArraySize = 1;
	shadowMapDesc.SampleDesc.Count = 1;
	shadowMapDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	shadowMapDesc.Height = static_cast<UINT>(wndHeight);
	shadowMapDesc.Width = static_cast<UINT>(wndWidth);

	HRESULT hr = d3dDevice->CreateTexture2D(
		&shadowMapDesc,
		nullptr,
		&m_shadowMap
	);

	return true;
}

bool DX_11::create_depth_stencil_view()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	HRESULT hr = d3dDevice->CreateDepthStencilView(
		m_shadowMap,
		&depthStencilViewDesc,
		&m_shadowDepthView
	);

	return true;
}

bool DX_11::create_shader_resource_view()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	HRESULT hr = d3dDevice->CreateShaderResourceView(
		m_shadowMap,
		&shaderResourceViewDesc,
		&m_shadowResourceView
	);

	return true;
}

//bool DX_11::create_render_target()
//{
//	HRESULT result = S_OK;
//
//	DXGI_SWAP_CHAIN_DESC swapChainDesc;
//	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
//	swapChainDesc.BufferCount = 1;
//	swapChainDesc.BufferDesc.Width = wndWidth;
//	swapChainDesc.BufferDesc.Height = wndHeight;
//	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
//	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
//	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	swapChainDesc.OutputWindow = hWnd;
//	swapChainDesc.SampleDesc.Count = 1;
//	swapChainDesc.SampleDesc.Quality = 0;
//	swapChainDesc.Windowed = TRUE;
//
//	// Создание рендер-таргета
//	ID3D11Texture2D* backBuffer = NULL;
//	if (swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer) < 0)
//		return false;
//
//	result = d3dDevice->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
//	backBuffer->Release();
//	if (result < 0) return false;
//
//	return true;
//}

bool DX_11::create_shaders()
{
	main_shader = new Shader;
	if (!createShader(L"shader.fx", main_shader))
	{
		return false;
	}

	shadow_map_shader = new Shader;
	if (!createShader(L"shadow_map.fx", shadow_map_shader))
	{
		return false;
	}

	return true;
}

bool DX_11::createDevice()
{
	HRESULT result = S_OK;

	UINT createDeviceFlags = 0;
//#ifdef _DEBUG
//	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif

	//vector<D3D_DRIVER_TYPE> driverTypes
	//{
	//	D3D_DRIVER_TYPE_HARDWARE,
	//	D3D_DRIVER_TYPE_WARP,
	//	D3D_DRIVER_TYPE_REFERENCE
	//};
	//
	//vector<D3D_FEATURE_LEVEL> featureLevels
	//{
	//	D3D_FEATURE_LEVEL_11_0,
	//	D3D_FEATURE_LEVEL_10_1,
	//	D3D_FEATURE_LEVEL_10_0
	//};

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

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

	//if (D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags,
	//	&featureLevels.front(), featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc,
	//	&swapChain, &d3dDevice, &featureLevel, &immediateContext) < 0)
	//	return false;
	//	//if (result == S_OK)
	//	//if (result = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags,
	//	//	&featureLevels.front(), featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc,
	//	//	&swapChain, &d3dDevice, &featureLevel, &immediateContext) >= 0)
	//	//	break;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType = driverTypes[driverTypeIndex];
		result = D3D11CreateDeviceAndSwapChain(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &d3dDevice, &featureLevel, &immediateContext);
		if (SUCCEEDED(result))
			break;
		if (FAILED(result))
		{
			MessageBox(hWnd, L"Failed to create directX device and swapchain!",
				L"Error", MB_ICONERROR);
		}
	}

	if (result < 0) return false;

	// Создание рендер-таргета
	ID3D11Texture2D* backBuffer = NULL;
	if (swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer) < 0)
		return false;

	result = d3dDevice->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();
	if (result < 0) return false;

	//============Создание поверхности для Z-буфера============
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = wndWidth;
	descDepth.Height = wndHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	if (d3dDevice->CreateTexture2D(&descDepth, NULL, &depthStencil))
		return false;


	D3D11_DEPTH_STENCIL_DESC dsDesc;

	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	d3dDevice->CreateDepthStencilState(&dsDesc, &pDSState);

	// Bind depth stencil state
	immediateContext->OMSetDepthStencilState(pDSState, 1);

	
	descDSV.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	// Create the depth stencil view
	if (d3dDevice->CreateDepthStencilView(depthStencil, // Depth stencil texture
		&descDSV, // Depth stencil desc
		&depthStencilView))  // [out] Depth stencil view
		return false;

	// Bind the depth stencil view
	immediateContext->OMSetRenderTargets(1,          // One rendertarget view
		&renderTargetView,      // Render target view, created earlier
		depthStencilView);     // Depth stencil view for the render target

	//============Создание поверхности для Z-буфера============

	//================D3D11_RASTERIZER_DESC rasterDesc;==========
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = d3dDevice->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result)) return false;
	immediateContext->RSSetState(m_rasterState);
	//================D3D11_RASTERIZER_DESC rasterDesc;==========

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

	// Создание буфера констант шейдера
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ConstantBuffer_2);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	if (d3dDevice->CreateBuffer(&bufferDesc, NULL, &constantBuffer_2) < 0)
		return false;

	return true;
}

bool DX_11::createShader(wstring path, Shader* shader)
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
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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

bool DX_11::compileShader(wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut)
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
void DX_11::render()
{
	// Shadow_map
	//=============================================================================
	//
	// https://docs.microsoft.com/ru-ru/windows/uwp/gaming/implementing-depth-buffers-for-shadow-mapping
	// https://takinginitiative.wordpress.com/2011/05/15/directx10-tutorial-10-shadow-mapping/
	// http://www.rastertek.com/dx11tut48.html

	// The light_eye should not be like {0.0f, 1.0f, 0.0f} or some like vectors with 2 zeros
	// It cause incorrect computation of light_view = XMMatrixLookAtLH(eye, at, up)
	Math_3d::Vector_3d light_eye = { 0.01f, 7.0f, 0.01f };
	XMFLOAT4 light_pos = { light_eye.x, light_eye.y, light_eye.z, 0.0f };
	XMVECTOR light_pos_eye = { light_eye.x, light_eye.y, light_eye.z, 0.0f };
	XMFLOAT4 light_color = { 1.0f, 1.0f, 1.0f, 1.0f };

	immediateContext->OMSetRenderTargets(
		0,
		nullptr,
		m_shadowDepthView
	);

	//
	// Очистка рендер-таргета
	//
	float ClearColor[4] = { 0.0f, 0.9f, 0.5f, 1.0f }; // цвет
	immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
	immediateContext->ClearDepthStencilView(m_shadowDepthView, D3D11_CLEAR_DEPTH, 1.0f, 0.0f);

	//
	// Установка констант шейдера
	//
	// Light pos
	XMVECTOR eye = light_pos_eye;
	XMVECTOR at = XMVectorSet(0.0f, -0.5f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX light_view = XMMatrixLookAtLH(eye, at, up);
	XMMATRIX light_projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)wndWidth / (FLOAT)wndHeight, 1.0f, 100.0f);
	localConstantBuffer.mWorld = XMMatrixTranspose(mWorld);
	localConstantBuffer.mView = XMMatrixTranspose(light_view);
	localConstantBuffer.mProjection = XMMatrixTranspose(light_projection);

	// Light pos
	localConstantBuffer.light_pos = light_pos;
	localConstantBuffer.light_color = light_color;

	immediateContext->UpdateSubresource(constantBuffer, 0, NULL, &localConstantBuffer, 0, 0);

	//
	// Установка шейдера
	//
	immediateContext->VSSetShader(shadow_map_shader->vertexShader, NULL, 0);
	immediateContext->PSSetShader(shadow_map_shader->pixelShader, NULL, 0);

	for (auto it : objects)
	{
		//
		// Установка констант шейдера
		//
		immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
		immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);

		// Установка вершинного буфера
		UINT stride = sizeof(Geometry::Vertex);
		UINT offset = 0;
		immediateContext->IASetVertexBuffers(0, 1, &it.second->vertexBuffer, &stride, &offset);

		// Установка индексного буфера
		immediateContext->IASetIndexBuffer(it.second->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Установка типа примитив
		immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//
		// Рендер
		//

		immediateContext->DrawIndexed(it.second->size, 0, 0);
	}
	// Shadow_map
	//=============================================================================



	immediateContext->OMSetRenderTargets(1,          // One rendertarget view
		&renderTargetView,      // Render target view, created earlier
		depthStencilView);     // Depth stencil view for the render target

	//
	// Очистка рендер-таргета
	//
	immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0.0f);

	//
	// Установка констант шейдера
	//
	localConstantBuffer.mWorld = XMMatrixTranspose(mWorld);
	localConstantBuffer.mView = XMMatrixTranspose(camera->view());
	localConstantBuffer.mProjection = XMMatrixTranspose(camera->projection());
	// Light pos
	localConstantBuffer.light_view = XMMatrixTranspose(light_view);
	localConstantBuffer.light_projection = XMMatrixTranspose(light_projection);

	localConstantBuffer.light_pos = light_pos;
	localConstantBuffer.light_color = light_color;

	immediateContext->UpdateSubresource(constantBuffer, 0, NULL, &localConstantBuffer, 0, 0);
	immediateContext->UpdateSubresource(constantBuffer_2, 0, NULL, &localConstantBuffer_2, 0, 0);

	ID3D11Buffer* cbarr[2] = { constantBuffer , constantBuffer_2 };

	//
	// Установка шейдера
	//
	immediateContext->VSSetShader(main_shader->vertexShader, NULL, 0);
	immediateContext->PSSetShader(main_shader->pixelShader, NULL, 0);

	for (auto it : objects)
	{
		localConstantBuffer_2.color.x = it.second->color.x;
		localConstantBuffer_2.color.y = it.second->color.y;
		localConstantBuffer_2.color.z = it.second->color.z;
		localConstantBuffer_2.color.w = it.second->color.w;
		immediateContext->UpdateSubresource(constantBuffer_2, 0, NULL, &localConstantBuffer_2, 0, 0);

		//
		// Установка констант шейдера
		//
		immediateContext->VSSetConstantBuffers(0, 2, cbarr);
		immediateContext->PSSetConstantBuffers(0, 2, cbarr);

		// Set shader texture resource in the pixel shader.
		immediateContext->PSSetShaderResources(0, 1, &m_shadowResourceView);

		// Установка вершинного буфера
		UINT stride = sizeof(Geometry::Vertex);
		UINT offset = 0;
		immediateContext->IASetVertexBuffers(0, 1, &it.second->vertexBuffer, &stride, &offset);

		// Установка индексного буфера
		immediateContext->IASetIndexBuffer(it.second->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		// Установка типа примитив
		immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//
		// Рендер
		//
		
		immediateContext->DrawIndexed(it.second->size, 0, 0);
	}

	//
	// Вывод на экран содержимого рендер-таргета
	//
	swapChain->Present(0, 0);
}

void DX_11::setGeometry(shared_ptr<Geometry::Geometry> _geometry)
{
	geometry =_geometry;

	for (auto obj : *geometry)
	{
		Geometry::Object_Data* objData = obj->get_data();

		GPUData *gpuData = new GPUData;
		objects.push_back(std::make_pair(objData, gpuData));

		gpuData->size = objData->size;
		gpuData->color = objData->color;

		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));

		// Создание вершинного буфера
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(Geometry::Vertex) * objData->vertices.size();
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		InitData.pSysMem = &objData->vertices[0];
		if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &gpuData->vertexBuffer) < 0)
			return;

		// Создание индексного буфера
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(DWORD) * objData->indices.size();
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;

		InitData.pSysMem = &objData->indices[0];
		if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &gpuData->indexBuffer) < 0)
			return;
	}

	// Установка типа примитив
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Установка матриц
	mWorld = XMMatrixIdentity();
}

void DX_11::updateGeometry()
{
	for (auto it : objects)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		immediateContext->Map(it.second->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &it.first->vertices[0], it.first->vertices.size() * sizeof(Geometry::Vertex));
		immediateContext->Unmap(it.second->vertexBuffer, 0);
	}
}

void DX_11::setCamera(shared_ptr<Camera> _camera)
{
	camera = _camera;
}