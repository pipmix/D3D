cbuffer mvpConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};



struct Input {
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct Output {
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};





Output main(Input input) {
	Output output;
	output.position = float4(input.position.x, input.position.y, input.position.z, 1);
	output.normal = input.normal;
	output.texcoord = input.texcoord;

	return output;
}

