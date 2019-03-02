//--------------------------------------------------------------------------------------
// File: shader.fx
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float3 Normal: NORMAL, float4 Color: COLOR)
{
    //VS_OUTPUT output = (VS_OUTPUT)0;
    VS_OUTPUT output;
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

    output.Color = Color;

    //output.Color=float4(0.0f,0.0f,0.0f,0.0f);

    //for (int i=0; i<1; i++)
    //output.Color+=max(0,dot(normalize(Normal),normalize((float3)vLightPos[i]-(float3)Pos) ))*vLightColor[i]*1.25f;


    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
