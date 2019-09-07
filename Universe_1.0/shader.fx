//--------------------------------------------------------------------------------------
// File: shader.fx
//--------------------------------------------------------------------------------------

//static const float PI = 3.14159265f;
//for PI you can also use acos(-1), works fine too.

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer //: register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
    float4 light_color;
    float4 light_pos;
	//float4 plane_def[80];
    //float4 plane_color[80];
    //float4 plane_num; //num, curr_obj, tmp_1, tmp_2
}

cbuffer ConstantBuffer //: register(b1)
{
	float4 color;
	//float4 plane_num; //num, curr_obj, tmp_1, tmp_2
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//bool is_shaded(float3 src, float3 dst)
//{
//    for (int i = 1; i < plane_num.x; ++i)
//    {
//        if ((float)i == plane_num.y)
//            continue;
//
//        float3 a = plane_def[i * 4 + 0].xyz;
//        float3 b = plane_def[i * 4 + 1].xyz;
//        float3 c = plane_def[i * 4 + 2].xyz;
//        float3 d = plane_def[i * 4 + 3].xyz;
//      
//        //Normal to plane
//        float3 normal = normalize(cross(b - a, c - a));
//        float3 v_to_p = a - src;
//      
//        //dst to plane using normal
//        float dist = dot(normal, v_to_p);
//        float3 src_v = dst - src;
//      
//        //Approx to plane with interseption
//        float e_res = dot(normal, src_v);
//      
//        if (e_res != 0.0f) //one point
//        {
//            float3 cross_p = src + src_v * dist / e_res;
//
//            float3 vec_a = normalize(a - cross_p);
//            float3 vec_b = normalize(b - cross_p);
//            float3 vec_c = normalize(c - cross_p);
//            float3 vec_d = normalize(d - cross_p);
//
//            float ab = dot(vec_a, vec_b);
//            float bc = dot(vec_b, vec_c);
//            float cd = dot(vec_c, vec_d);
//            float da = dot(vec_d, vec_a);
//
//            float angle_sum = acos(ab) + acos(bc) + acos(cd) + acos(da);
//			if (abs(angle_sum - 2.0f * acos(-1.0f)) < 0.01f)
//            {
//				if (distance(src, dst) > distance(src, cross_p))
//					return true;
//            }
//        }
//    }
//
//    return false;
//}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Normal: NORMAL)
{
    VS_OUTPUT output;
    
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

	//output.Color = light_color * plane_color[(int)plane_num.y];

    //if (is_shaded(light_pos.xyz, Pos.xyz))
    //{
    //    output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //}
    
	//output.Color = light_color * color;
	output.Color = dot(Normal, normalize(light_pos.xyz - Pos.xyz)) * light_color * color;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
