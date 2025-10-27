#pragma pack_matrix( row_major )

cbuffer WVPMatrix : register(b0)
{
    float4x4 WVPMatrix;
	//float4x4 View;
	//float4x4 Projection;
}

cbuffer ColorData : register(b1)
{
	//float4x4 World;
	float4 SelectedColor;
};

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION )
{
    VS_OUTPUT output;
    //output.Pos = mul( Pos, World );
    //output.Pos = mul( output.Pos, View );
    //output.Pos = mul( output.Pos, Projection );
    output.Pos = mul(Pos, WVPMatrix);
    output.Color = SelectedColor;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
