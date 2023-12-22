

void device_impl::init_vertex_layout(ID3DBlob* vertex_blob)
{
    ID3D11InputLayout* vertex_layout = nullptr;

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT layout_size = ARRAYSIZE(layout);

    HRESULT result = device->CreateInputLayout
    (
        layout,
        layout_size,
        vertex_blob->GetBufferPointer(),
        vertex_blob->GetBufferSize(),
        &vertex_layout
    );
    if (FAILED(result))
    {
        throw std::invalid_argument("Failed to create input layout");
    }

    device_context->IASetInputLayout(vertex_layout);
}