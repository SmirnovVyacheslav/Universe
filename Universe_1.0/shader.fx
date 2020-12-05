//--------------------------------------------------------------------------------------
// File: shader.fx
//--------------------------------------------------------------------------------------

//static const float PI = 3.14159265f;

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer
{
	matrix world;
	matrix view;
	matrix projection;
    matrix light_view;
    matrix light_projection;
    float4 light_color;
    float4 light_pos;
}

cbuffer ConstantBuffer
{
	float4 object_color;
}

//--------------------------------------------------------------------------------------
// Typedefs
//--------------------------------------------------------------------------------------
struct VS_Input
{
    float4 pos    : POSITION;
    float3 normal : NORMAL;
};

struct PS_Input
{
    float4 pos            : SV_POSITION;
    float3 normal         : NORMAL;
    float4 light_view_pos : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Textures
//--------------------------------------------------------------------------------------
Texture2D depth_map : register(t0);

//--------------------------------------------------------------------------------------
// Sample states
//--------------------------------------------------------------------------------------
SamplerState SampleTypeClamp : register(s0);

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_Input VS(VS_Input input)
{
    PS_Input vs_output;
    
    // Change the position vector to be 4 units for proper matrix calculations.
    input.pos.w = 1.0f;

    vs_output.pos = mul(input.pos, world);
    vs_output.pos = mul(vs_output.pos, view);
    vs_output.pos = mul(vs_output.pos, projection);

    // Calculate the position of the vertice as viewed by the light source.
    vs_output.light_view_pos = mul(input.pos, world);
    vs_output.light_view_pos = mul(vs_output.light_view_pos, light_view);
    vs_output.light_view_pos = mul(vs_output.light_view_pos, light_projection);

    // Calculate the normal vector against the world matrix only.
    vs_output.normal = normalize(mul(input.normal, (float3x3)world));
    // vs_output.normal = input.normal;

    return vs_output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_Input input): SV_TARGET
{
    // Ambient (background) color
    float ambientStrength = 0.4f;
    float4 ambient_color = ambientStrength * light_color;

    // Set the bias value for fixing the floating point precision issues.
    float bias = 0.001f;
    // Set the default output color to the ambient light value for all pixels.
    float4 color = ambient_color;

    // Calculate the projected texture coordinates.
    float2 project_tex_coord;
    project_tex_coord.x = input.light_view_pos.x / input.light_view_pos.w / 2.0f + 0.5f;
    project_tex_coord.y = -input.light_view_pos.y / input.light_view_pos.w / 2.0f + 0.5f;

    float depth_value;
    float light_depth_value;
    float light_intensity;

    // Vars for diffuse color calc
    float3 light_dir = light_pos.xyz - input.pos.xyz;
    light_dir = normalize(light_dir);
    light_dir = -light_dir;

    // Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
    if ((saturate(project_tex_coord.x) == project_tex_coord.x) && (saturate(project_tex_coord.y) == project_tex_coord.y))
    {
        // Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
        depth_value = depth_map.Sample(SampleTypeClamp, project_tex_coord).r;

        // Calculate the depth of the light.
        light_depth_value = input.light_view_pos.z / input.light_view_pos.w;

        // Subtract the bias from the lightDepthValue.
        light_depth_value = light_depth_value - bias;

        // Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
        // If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
        if (light_depth_value < depth_value)
        {
            // Calc color
            //float diff = max(dot(normal, light_vec), 0.0);
            //float3 diffuse = diff * light_color;

            // Calculate the amount of light on this pixel.
            // light_intensity = saturate(dot(input.normal, light_dir));
            light_intensity = max(dot(input.normal, light_dir), 0.0);
            color += light_color * light_intensity;
            //if (light_intensity > 0.0f)
            //{
            //    // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
            //    color += (light_color * light_intensity);

            //    // Saturate the final light color.
            //    color = saturate(color);
            //}
        }
    }
    else
    {
        // If this is outside the area of shadow map range then draw things normally with regular lighting.
        // light_intensity = saturate(dot(input.normal, light_dir));
        light_intensity = max(dot(input.normal, light_dir), 0.0);
        color += light_color * light_intensity;
        /*if (light_intensity > 0.0f)
        {
            color += (light_color * light_intensity);
            color = saturate(color);
        }*/
    }

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    // textureColor = shaderTexture.Sample(SampleTypeWrap, input.tex);

    // Combine the light and texture color.
    // color = color * textureColor;
    color = color * object_color;

    return color;
}