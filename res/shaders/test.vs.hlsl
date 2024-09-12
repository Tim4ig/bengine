
struct vsin
{
	float3 pos : POSITION;
};

struct vsout
{
	float4 pos : SV_POSITION;
};

cbuffer cb0 : register(b0)
{
	float4x4 view;
	float4x4 proj;
	float4x4 viewProj;
};

cbuffer cb1 : register(b1)
{
	float4x4 world;
};

vsout main(vsin input)
{
	vsout output;
	output.pos = mul(viewProj, mul(world, float4(input.pos, 1)));
	return output;
}
