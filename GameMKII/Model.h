#pragma once
#include <d3d11_1.h>
#include <vector>
#include <fstream>
#include <istream>
#include <string>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#pragma comment (lib, "d3d11.lib")
using namespace DirectX;
using namespace std;


class Model{
public:
	Model(string fileName, ID3D11Device*, ID3D11DeviceContext*);
	~Model();
private:
	void Draw();
	void Load();
	void Update();


	vector<XMFLOAT3> pos;
	vector<XMFLOAT3> normal;
	vector<XMFLOAT2> uv;

	wchar_t curChar;
	float x, y, z;
	string f1, f2, f3;



	ID3D11Buffer* vertBuff;
	ID3D11Buffer* indexBuff;



	struct ConstantBuffer {
		XMFLOAT4X4 model;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
	};

	


	uint32_t                                                indexCount;
	uint32_t                                                startIndex;
	uint32_t                                                vertexOffset;
	uint32_t                                                vertexStride;
	D3D_PRIMITIVE_TOPOLOGY                                  primitiveType;
	DXGI_FORMAT                                             indexFormat;

	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* vertexBuffer;
	//std::shared_ptr<IEffect>                                effect;
	vector<D3D11_INPUT_ELEMENT_DESC>  vbDecl;
	bool                                                    isAlpha;
	ID3D11Device * device;
	ID3D11DeviceContext * context;

	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;

	ID3D11InputLayout* inputLayout = nullptr;


	struct VERTEX{
		XMFLOAT3 pos;      
		XMFLOAT3 normal;    
		XMFLOAT2 uv;    
	};


};

