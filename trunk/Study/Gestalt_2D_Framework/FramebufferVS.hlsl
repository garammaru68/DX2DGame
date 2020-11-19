cbuffer cb : register(b0)
{
	float4 Color : packoffset(c0);

	float x : packoffset(c1.x);
	float y : packoffset(c1.y);
	float z : packoffset(c1.z);
	float delta : packoffset(c1.w);
};

struct VIn
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD0;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD0;
};

VOut FramebufferVS(VIn input)
{
	VOut output;

	output.position = float4(input.position, 1.0f);

	float rDelta = radians(delta);
	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}