struct VertexInputType
{
    float3 position 	: POSITION;
	unorm float4 color 	: COLOR;
	float2 uvs			: UV;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType VSMain(VertexInputType input)
{
    PixelInputType output;
	output.position = float4(input.position, 1.0f);
    return output;
}