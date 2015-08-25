#pragma once
#include <d3d11_1.h>
#include <vector>
#include <fstream>
#include <istream>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
using namespace DirectX;
using namespace std;


class Model
{
public:
	Model(string fileName, ID3D11Device* d);
	~Model();
private:
	void Draw();

	


	uint32_t                                                indexCount;
	uint32_t                                                startIndex;
	uint32_t                                                vertexOffset;
	uint32_t                                                vertexStride;
	D3D_PRIMITIVE_TOPOLOGY                                  primitiveType;
	DXGI_FORMAT                                             indexFormat;
	ID3D11InputLayout* inputLayout;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	//std::shared_ptr<IEffect>                                effect;
	vector<D3D11_INPUT_ELEMENT_DESC>  vbDecl;
	bool                                                    isAlpha;
	ID3D11Device * device;



	struct VERTEX{
		XMFLOAT3 pos;      
		XMFLOAT3 normal;    
		XMFLOAT2 uv;    
	};

	//VERTEX vertices[];

	VERTEX vertices[] =
	{
		{ XMFLOAT3( -3.0f, -3.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(3.0f, -3.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-3.0f, 3.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(3.0f, 3.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f),  XMFLOAT2(1.0f, 1.0f) },
	}
};

