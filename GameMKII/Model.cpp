#include "Model.h"


Model::Model(string fileName, ID3D11Device * d, ID3D11DeviceContext * c){


	device = d;
	context = c;
	LoadModel();

	// LOAD SHADERS
	ifstream vsFile("VertexShader.cso", ios::binary);
	vector<char> vsData = { istreambuf_iterator<char>(vsFile), istreambuf_iterator<char>() };
	ifstream psFile("PixelShader.cso", ios::binary);
	vector<char> psData = { istreambuf_iterator<char>(psFile), istreambuf_iterator<char>() };
	device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &vertexShader);
	device->CreatePixelShader(psData.data(), psData.size(), nullptr, &pixelShader);

	// CREATE INPUT LAYOUT
	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	device->CreateInputLayout(ied, ARRAYSIZE(ied), vsData.data(), vsData.size(), &inputLayout);
	context->IASetInputLayout(inputLayout);

	// CREATE VERTEX BUFFER
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX) * faces.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	ZeroMemory(&vertexData, sizeof(vertexData));
	vertexData.pSysMem = ar;
	device->CreateBuffer(&bd, &vertexData, &vertexBuffer);
	
	// SET VERTEX BUFFER
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



	// CONSTANT BUFFER


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, NULL, &constantBuffer);
		



	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &VsConstData;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	device->CreateBuffer(&cbDesc, &InitData,&cb);
	context->VSSetConstantBuffers(0, 1, &cb);




	


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

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//set index buffer
	//deviceContext->IASetPrimitiveTopology(primitiveType);
	//deviceContext->DrawIndexed(indexCount, startIndex, vertexOffset);
	context->Draw(numberOfVerts, 0);


}

void Model::LoadModel() {

	ifstream file("mesh.txt");

	vector<XMFLOAT3> pos;
	vector<XMFLOAT3> normal;
	vector<XMFLOAT2> uv;
	vector<string> listOfVerts;
	wchar_t curChar;
	float x, y, z;
	string f1, f2, f3;

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
				listOfVerts.push_back(f1);
				listOfVerts.push_back(f2);
				listOfVerts.push_back(f3);
				break;
			default:
				break;
			}
		}
		//USE THE STRINGS TO MAKE THE VERTEXS
		int a, b, c;
		char c1, c2;
		numberOfVerts = listOfVerts.size();

		//VERTEX * ar = new VERTEX[numberOfVerts];
		ar = new VERTEX[numberOfVerts];
		for (int i = 0; i < listOfVerts.size();i++) {
			istringstream buf(listOfVerts[i]);
			if (buf >> a >> c1 >> b >> c2 >> c && c1 == '/' && c2 == '/')faces.push_back(VERTEX(pos[a - 1], normal[c - 1], uv[b - 1]));
		}
		for (int i = 0; i < faces.size(); i++)ar[i] = faces[i];
	}
}