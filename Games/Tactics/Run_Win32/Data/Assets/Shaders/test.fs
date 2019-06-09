
struct FSIn
{
	float4 position_Clip 	: SV_POSITION;
	float2 uv				: UV;
};

float4 FSMain(FSIn input) : SV_TARGET
{
	float4 outColor = float4(input.uv, 0, 1);
	
	
	
	return outColor;
}