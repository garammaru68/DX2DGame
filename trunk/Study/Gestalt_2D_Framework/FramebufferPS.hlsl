Texture2D tex : register(t0);
SamplerState sam : register(s0);

float4 FramebufferPS(
	float4 position : SV_POSITION,
	float4 color : COLOR0,
	float2 texCoord : TEXCOORD0) : SV_TARGET
{
	float4 c = tex.Sample(sam, texCoord);
	if (c.r == 1.0f && c.g == 0.0f && c.b == 1.0f ) discard;
	return c;
}