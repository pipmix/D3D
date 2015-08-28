#include "Model.h"

struct Vertex {

	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 uv;


};



Model::Model(string fileName, ID3D11Device * d, ID3D11DeviceContext * c){

	//Load();
	device = d;
	context = c;

	ID3DBlob* vertexShaderBlob;
	D3DReadFileToBlob(L"../VertexShader.cso", &vertexShaderBlob);
	device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader);


	ID3DBlob* pixelShaderBlob;
	D3DReadFileToBlob(L"../PixelShader.cso", &pixelShaderBlob);
	device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader);




	Vertex vertices[] = {
		{XMFLOAT3(-1,-1,1),XMFLOAT3(1,1,1),XMFLOAT2(1,1)},
		{XMFLOAT3(0,1,0),XMFLOAT3(1,1,1),XMFLOAT2(1,1)},
		{XMFLOAT3(1,-1,0),XMFLOAT3(1,1,1),XMFLOAT2(1,1)}
	};
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);


	

	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(ied, 3, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout);
}


Model::~Model(){
	indexBuffer->Release();
	vertexBuffer->Release();
	vertexShader->Release();
	pixelShader->Release();
	inputLayout->Release();
}

void Model::Draw(){

	context->IASetInputLayout(inputLayout);
	context->VSGetShader(&vertexShader, nullptr, 0);
	context->PSGetShader(&pixelShader, nullptr, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	context->Draw(3, 0);

}

void Model::Load() {

	ifstream file("mesh.txt");
	if (file) {
		while (file) {
			curChar = file.get();
			switch (curChar) {
			case 'v':
				curChar = file.get();
				if (curChar == ' ') {
					file >> x >> y >> z;
					pos.push_back(XMFLOAT3(x, y, z));
				}
				else if (curChar == 't') {
					curChar = file.get();
					file >> x >> y;
					uv.push_back(XMFLOAT2(x, y));
				}
				else if (curChar == 'n') {
					curChar = file.get();
					file >> x >> y >> z;
					normal.push_back(XMFLOAT3(x, y, z));
				}
				break;
			case 'f':
				curChar = file.get();
				file >> f1 >> f2 >> f3;

			default:
				break;
			}
		}

		//for (int i = 0; i < pos.size(); i++) std::cout << pos[i].x << " " << pos[i].y << " " << pos[i].z << endl;
		//for (int i = 0; i < uv.size(); i++) std::cout << uv[i].x << " " << uv[i].y << " " << endl;
		//for (int i = 0; i < normal.size(); i++) std::cout << normal[i].x << " " << normal[i].y << " " << normal[i].z << endl;


	}

}