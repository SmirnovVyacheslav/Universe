void directx::create_vertex_buffer() {
    /*D3D11_BUFFER_DESC buffer_data;
    ZeroMemory(&buffer_data, sizeof(buffer_data));

    buffer_data.Usage = D3D11_USAGE_DEFAULT;
    buffer_data.ByteWidth = sizeof(vertex) * 8;
    buffer_data.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_data.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data;
    ZeroMemory(&init_data, sizeof(init_data));
    init_data.pSysMem = &(scene::inst.get_object()->get_mesh().get_vertex());
    HRESULT result = device->CreateBuffer(&buffer_data, &init_data, &vertex_buffer);
    if (FAILED(result)) {
        throw std::invalid_argument("Failed to create vertex buffer");
    }

    UINT stride = sizeof(vertex);
    UINT offset = 0;
    immediate_context->IASetVertexBuffers(0, 1, &vertex_buffer, &stride, &offset);*/
}