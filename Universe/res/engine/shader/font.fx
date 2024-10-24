// Copyright: (C) 2022 Vyacheslav Smirnov. All rights reserved.

cbuffer PerFrameBuffer
{
	float4x4 WVP;
};

struct VertexInputType
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PixelInputType
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};

cbuffer PixelBuffer
{
    float4 pixelColor;
};

struct PixelInputType
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};


PixelInputType VS(VertexInputType input)
{
    PixelInputType output;

    output.pos = mul(input.pos, WVP);    
	output.tex = input.tex;
    
    return output;
}

float4 PS(PixelInputType input) : SV_TARGET
{
	return shaderTexture.Sample(SampleType, input.tex) * pixelColor;
}
