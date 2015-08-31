#pragma once
#include <d3d11_1.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <DirectXMath.h>


#pragma comment (lib, "d3d11.lib")
using namespace DirectX;
using namespace std;

struct ModelViewProjectionConstantBuffer
{
	DirectX::XMFLOAT4X4 model;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
};


class Model{
public:
	Model(string fileName, ID3D11Device*, ID3D11DeviceContext*);
	~Model();

	void Update();
	void Draw();
private:

	
	void LoadModel();
	void LoadShader();
	void CreateVertexBuffer();
	void CreateConstantBuffer();
	

	ID3D11Buffer*   cb = nullptr;

	struct ConstantBuffer {
		XMFLOAT4X4 model;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
	};

	// SHADERS
	ID3D11VertexShader*		vertexShader = nullptr;
	ID3D11PixelShader*		pixelShader = nullptr;
	vector<byte>			vertexShaderByte;
	vector<byte>			pixelShaderByte;
	// BUFFERS
	ID3D11Buffer*			indexBuffer;
	ID3D11Buffer*			vertexBuffer;
	// CONTEXTS
	ID3D11Device *			device;
	ID3D11DeviceContext *	context;


	uint32_t                                                indexCount;
	uint32_t                                                startIndex;
	uint32_t                                                vertexOffset;
	uint32_t                                                vertexStride;
	D3D_PRIMITIVE_TOPOLOGY                                  primitiveType;
	DXGI_FORMAT                                             indexFormat;



	//std::shared_ptr<IEffect>                                effect;
	vector<D3D11_INPUT_ELEMENT_DESC>  vbDecl;
	bool                                                    isAlpha;

	ID3D11InputLayout* inputLayout = nullptr;


	struct VERTEX {
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 uv;
		VERTEX(XMFLOAT3 p, XMFLOAT3 n, XMFLOAT2 u) {
			pos = p;
			normal = n;
			uv = u;
		}
		VERTEX() {

		}
	};

	vector<VERTEX> faces;
	VERTEX * ar = nullptr;

	int numberOfVerts = 0;

};

