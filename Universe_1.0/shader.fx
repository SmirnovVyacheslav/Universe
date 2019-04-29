//--------------------------------------------------------------------------------------
// File: shader.fx
//--------------------------------------------------------------------------------------

static const float PI = 3.14159265f;

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
    float4 light_color;
    float4 light_pos;
    float4 plane_def[80];
    float4 plane_color[80];
    float4 plane_num; //num, curr_obj, tmp_1, tmp_2
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

bool is_shaded(float4 src, float4 dst)
{
    for (float i = 1.0f; i < plane_num.x; i++)
    {
        if (i == plane_num.y)
            continue;

        //float3 cross_point;

        float3 a = (float3)plane_def[(int)i * 4 + 0];
        float3 b = (float3)plane_def[(int)i * 4 + 1];
        float3 c = (float3)plane_def[(int)i * 4 + 2];
        float3 d = (float3)plane_def[(int)i * 4 + 3];


        /* Calculate the parameters for the plane */
        float3 normal = normalize(cross(b - a, c - a));
        //float d_plane = - normal.x * a.x - normal.y * a.y - normal.z * a.z;

        float t = -dot((float3)src - a, normal) / dot((float3)src - (float3)dst, normal);

        float3 cross_point = (float3)src + ((float3)src - (float3)dst) * t;

        float3 mid = float3(a.x + abs(a.x - b.x), a.y + abs(a.y - c.y), a.z);
        if (distance(cross_point, mid) > 15.0f)
            return true;

        float3 vec_a = normalize(a - cross_point);
        float3 vec_b = normalize(b - cross_point);
        float3 vec_c = normalize(c - cross_point);
        float3 vec_d = normalize(d - cross_point);

        float angle_tmp = degrees(acos(dot(vec_a, vec_b)) + acos(dot(vec_b, vec_c)) + acos(dot(vec_c, vec_a)));
        if (abs(angle_tmp - 360.0f) < 1.0f)
            return true;

        angle_tmp = degrees(acos(dot(vec_a, vec_c)) + acos(dot(vec_c, vec_d)) + acos(dot(vec_d, vec_a)));
        if (abs(angle_tmp - 360.0f) < 1.0f)
            return true;
//
//
//        /* Calculate the parameters for the plane */
//        float3 normal = normalize(cross(b - a, c - a));
//        float d_plane = - normal.x * a.x - normal.y * a.y - normal.z * a.z;
//
//        /* Calculate the position on the line that intersects the plane */
//        float denom = normal.x * ((float3)src.x - (float3)dst.x) + normal.y * ((float3)src.y - (float3)dst.y) + normal.z * ((float3)src.z - (float3)dst.z);
//        /* Line and plane don't intersect */
//        if (abs(denom) < 0.001f)
//            continue;
//
//        float mu = (d_plane + normal.x * (float3)src.x + normal.y * (float3)src.y + normal.z * (float3)src.z) / denom;
//
//        cross_point = (float3)src + mu * ((float3)dst - (float3)src);
//
//        float3 color_tmp = (float3)plane_color[1];
//        if (color_tmp.x == 1.0f && color_tmp.y == 1.0f && color_tmp.z == 0.1f)
//            return true;
//      
//        //Normal to plane
//        float3 normal = normalize(cross(b - a, c - a));
//        float3 vector_to_plane = a - (float3)src;
//      
//        //dst to plane using normal
//        float dist = dot(normal, vector_to_plane);
//        float3 src_vec = (float3)dst - (float3)src;
//      
//        //Approx to plane with interseption
//        float e_res = dot(normal, src_vec);
//      
//        if (e_res != 0.0f) //one point
//        {
//            cross_point = (float3)src + src_vec * dist / e_res;
//
//            float3 vec_a = normalize(a - cross_point);
//            float3 vec_b = normalize(b - cross_point);
//            float3 vec_c = normalize(c - cross_point);
//            float3 vec_d = normalize(d - cross_point);
//
//            float angle_tmp = degrees(acos(dot(vec_a, vec_b)) + acos(dot(vec_b, vec_c)) + acos(dot(vec_c, vec_a)));
//            if (abs(angle_tmp - 360.0f) < 1.0f)
//                return true;
//
//            angle_tmp = degrees(acos(dot(vec_a, vec_c)) + acos(dot(vec_c, vec_d)) + acos(dot(vec_d, vec_a)));
//            if (abs(angle_tmp - 360.0f) < 1.0f)
//                return true;
//
//            //float angle_sum = degrees(acos(dot(vec_a, vec_b)) + acos(dot(vec_b, vec_c)) + acos(dot(vec_c, vec_d)) + acos(dot(vec_d, vec_a)));
//            ////if (abs(angle_sum - 2.0f * PI) < 1.0)
//            //if (abs(angle_sum - 360.0f) < 1.0)
//            //    return true;
//        }
    }

    return false;
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float3 Normal: NORMAL)
{
    VS_OUTPUT output;
    
    output.Pos = mul( Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

    //output.Color = float4(1.0f, 0.0f, 0.0f, 0.0f);
    output.Color = light_color;

    //float3 tmp_pos = float3(Pos.x, Pos.y, Pos.z);
    //float3 tmp_light_pos = float3(light_pos.x, light_pos.y, light_pos.z);

    //if (is_shaded(tmp_pos, tmp_light_pos))
    if (is_shaded(light_pos, Pos))
    {
        output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
