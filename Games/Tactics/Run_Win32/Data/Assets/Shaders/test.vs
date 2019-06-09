
struct VSIn
{
	float3 position_World 	: POSITION;
	float4 color 			: COLOR;
	//float3 normal_Local		: NORMAL;
	float2 uv				: UV;
	//float4 tangent_Local	: TANGENT;
};

struct VSOut
{
	float4 position_Clip 	: SV_POSITION;
	float2 uv				: UV;
};

VSOut VSMain(VSIn input)
{
	VSOut output;
	
	output.position_Clip = float4(input.position_World, 1.0f);
	output.uv = input.uv;
	
	return output;
}