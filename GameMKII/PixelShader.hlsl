


struct Input {
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float3 texcoord : texcoord;

};


float4 main(Input input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

