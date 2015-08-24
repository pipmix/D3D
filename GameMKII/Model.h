#pragma once
#include <d3d11_1.h>
#include <vector>
#include <fstream>
#include <istream>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11_1.lib")
using namespace DirectX;
using namespace std;


class Model
{
public:
	Model();
	~Model();




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
};

