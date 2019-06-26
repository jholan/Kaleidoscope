
cbuffer CCB : register(b1)
{
	float4 color;
};

Texture2D tex : register(t1);
SamplerState linearSampler : register(s1);

struct FSIn
{
	float4 position_Clip 	: SV_POSITION;
	float2 uv				: UV;
};

float4 FSMain(FSIn input) : SV_TARGET
{
	float4 outColor = float4(input.uv, 0, 1);
	
	outColor = tex.Sample(linearSampler, input.uv);// + (color * 0.7f);
	
	
	return outColor;
}