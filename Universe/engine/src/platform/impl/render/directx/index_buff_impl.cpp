void directx::create_index_buffer() {
    /*D3D11_BUFFER_DESC buffer_data;
    ZeroMemory(&buffer_data, sizeof(buffer_data));

    buffer_data.Usage = D3D11_USAGE_DEFAULT;
    buffer_data.ByteWidth = sizeof(WORD) * 36;
    buffer_data.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer_data.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data;
    ZeroMemory(&init_data, sizeof(init_data));
    init_data.pSysMem = &(scene::inst.get_object()->get_mesh().get_indice());

    HRESULT result = device->CreateBuffer(&buffer_data, &init_data, &index_buffer);
    if (FAILED(result)) {
        throw std::invalid_argument("Failed to create index buffer");
    }

    immediate_context->IASetIndexBuffer(index_buffer, DXGI_FORMAT_R16_UINT, 0);*/
}