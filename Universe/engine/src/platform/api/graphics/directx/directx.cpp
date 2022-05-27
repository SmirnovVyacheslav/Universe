// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#include "directx.h"

#ifdef WINDOWS


namespace engine
{
    void directx::create_window()
    {
        platform::window::create_window();
        window_handler = reinterpret_cast<HWND>(platform::window::id());
    }


    void directx::create_device()
    {
        create_window();

        DXGI_SWAP_CHAIN_DESC swap_chain_desription;
        ZeroMemory(&swap_chain_desription, sizeof(swap_chain_desription));
        swap_chain_desription.BufferCount = 1;
        swap_chain_desription.BufferDesc.Width = window_width;
        swap_chain_desription.BufferDesc.Height = window_height;
        swap_chain_desription.BufferDesc.Format = dxgi_format;
        swap_chain_desription.BufferDesc.RefreshRate.Numerator = refresh_rate;
        swap_chain_desription.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_desription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desription.OutputWindow = window_handler;
        swap_chain_desription.SampleDesc.Count = 1;
        swap_chain_desription.SampleDesc.Quality = 0;
        swap_chain_desription.Windowed = TRUE;

        D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;

        HRESULT hr = S_OK;
        D3D_FEATURE_LEVEL FeatureLevel;

        if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL,
            D3D_DRIVER_TYPE_REFERENCE,
            NULL,
            0,
            &FeatureLevels,
            1,
            D3D11_SDK_VERSION,
            &swap_chain_desription,
            &swapChain,
            &d3dDevice,
            &FeatureLevel,
            &immediateContext)))
        {
            return;
        }
    }


    D3D_DRIVER_TYPE         driverType = D3D_DRIVER_TYPE_HARDWARE;
    D3D_FEATURE_LEVEL       featureLevel = D3D_FEATURE_LEVEL_11_0;

    ID3D11Device* d3dDevice = nullptr;
    ID3D11DeviceContext* immediateContext = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* renderTargetView = nullptr;

    ID3D11Texture2D* depthStencil = nullptr;
    ID3D11DepthStencilView* depthStencilView = nullptr;

    ID3D11InputLayout* vertexLayout = nullptr;

    ID3D11Buffer* constantBuffer = nullptr;
    ConstantBuffer          localConstantBuffer;


    ID3D11Buffer* g_pVertexBuffer = NULL;
    ID3D11Buffer* g_pIndexBuffer = NULL;


    //============Создание поверхности для Z-буфера============
    ID3D11DepthStencilState* pDSState;
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;

    //================D3D11_RASTERIZER_DESC rasterDesc;==========
    D3D11_RASTERIZER_DESC rasterDesc;
    ID3D11RasterizerState* m_rasterState;

    // HWND hWnd;
    int  wndWidth = 800;
    int  wndHeight = 600;

    XMMATRIX                g_World;
    XMMATRIX                g_View;
    XMMATRIX                g_Projection;

    ID3D11VertexShader* g_pVertexShader = NULL;
    ID3D11PixelShader* g_pPixelShader = NULL;


    void createDevice()
    {
        platform::window::create_window();
        HWND hWnd = reinterpret_cast<HWND>(platform::window::id());

        HRESULT result = S_OK;

        RECT wndSize;
        GetClientRect(hWnd, &wndSize);
        wndWidth = static_cast<int>(wndSize.right - wndSize.left);
        wndHeight = static_cast<int>(wndSize.bottom - wndSize.top);

        UINT createDeviceFlags = 0;

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

        // Создание рендер-таргета
        ID3D11Texture2D* backBuffer = NULL;
        if (swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer) < 0)
            return;

        result = d3dDevice->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
        backBuffer->Release();

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
            return;


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
            return;

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
        if (FAILED(result));
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
            return;
    }


    bool createShader()
    {
        // Загружаем шейдеры
        ID3DBlob* blob = NULL;
        HRESULT hr;
        if (!compileShader(L"C:\\Private\\Projects\\Universe\\Universe\\engine\\src\\shader\\shader.fx", "VS", "vs_4_0", &blob))
        {
            MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return false;
        }

        // Вершинный шейдер
        if (d3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &g_pVertexShader) < 0)
        {
            blob->Release();
            return false;
        }

        // Определение формата вершинного буфера
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
        if (compileShader(L"C:\\Private\\Projects\\Universe\\Universe\\engine\\src\\shader\\shader.fx", "PS", "ps_4_0", &blob) < 0)
        {
            MessageBox(NULL, L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
            return false;
        }

        // Пиксельный шейдер
        hr = d3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &g_pPixelShader);
        blob->Release();
        if (FAILED(hr))
            return false;

        return true;
    }


    bool compileShader(std::wstring path, LPCSTR type, LPCSTR shaderModel, ID3DBlob** blobOut)
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


    void setGeometry()
    {
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));

        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));

        // Создание вершинного буфера
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(vertex) * 8;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;

        InitData.pSysMem = &scene::inst.get_object()->get_mesh().get_vertex();
        if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &g_pVertexBuffer) < 0)
            return;

        // Создание индексного буфера
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(WORD) * scene::inst.get_object()->get_mesh().get_size();
        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0;

        InitData.pSysMem = &scene::inst.get_object()->get_mesh().get_indice();
        if (d3dDevice->CreateBuffer(&bufferDesc, &InitData, &g_pIndexBuffer) < 0)
            return;

        // Установка типа примитив
        immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // Установка матриц
        g_World = XMMatrixIdentity();
        XMVECTOR Eye = XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
        XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        g_View = XMMatrixLookAtLH(Eye, At, Up);
        g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, wndWidth / (FLOAT)wndHeight, 0.01f, 100.0f);
    }


    void do_render()
    {
        //
        // Установка трансформации для куба
        //
        g_World = XMMatrixRotationY(3.14159f / 4.0f);

        //
        // Очистка рендер-таргета
        //
        float ClearColor[4] = { 0.0f, 0.9f, 0.5f, 1.0f }; // цвет
        immediateContext->ClearRenderTargetView(renderTargetView, ClearColor);
        immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0.0f);

        //
        // Установка констант шейдера
        //
        localConstantBuffer.mWorld = XMMatrixTranspose(g_World);
        localConstantBuffer.mView = XMMatrixTranspose(g_View);
        localConstantBuffer.mProjection = XMMatrixTranspose(g_Projection);
        immediateContext->UpdateSubresource(constantBuffer, 0, NULL, &localConstantBuffer, 0, 0);


        //
        // Установка шейдера
        //
        immediateContext->VSSetShader(g_pVertexShader, NULL, 0);
        immediateContext->PSSetShader(g_pPixelShader, NULL, 0);

        //
        // Установка констант шейдера
        //
        immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
        immediateContext->PSSetConstantBuffers(0, 1, &constantBuffer);


        // Установка вершинного буфера
        UINT stride = sizeof(vertex);
        UINT offset = 0;
        immediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

        // Установка индексного буфера
        immediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

        // Установка типа примитив
        immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        //
        // Рендер куба
        //
        immediateContext->DrawIndexed(36, 0, 0);       // 36 вершин образуют 12 полигонов, по три вершины на полигон

        //
        // Вывод на экран содержимого рендер-таргета
        //
        swapChain->Present(0, 0);
    }
}
#endif
