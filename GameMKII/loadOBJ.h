#pragma once
#include <d3d11_1.h>
#pragma comment (lib, "d3d11.lib")
#include <string>
#include <vector>
#include <DirectXMath.h>
#include <fstream>
#include <sstream>
using namespace std;
using namespace DirectX;

class loadOBJ{


public:
	loadOBJ(wstring filename);
	~loadOBJ();

private:

	vector<unsigned long> indices;
	vector<XMFLOAT3> pos;
	vector<XMFLOAT3> normal;
	vector<XMFLOAT2> uv;

	vector<int> posIndex;
	vector<int> normalIndex;
	vector<int> uvIndex;

	vector<wstring> materials;
	wstring materialsTemp;
	wstring materialsLibrary;
	wstring face;

	void addVertex(float, float, float);
	void addVertex(XMFLOAT3);
	vector<XMFLOAT3> vertices;

	wstring vertDataString;



	ID3D11Buffer* vertBuff;
	ID3D11Buffer* indexBuff;

	wchar_t curChar;

	bool rh = false;
	bool hasUv = false;
	bool hasNormal = false;
	int vIndex = 0;
	int triangleCount;

	int groups = 0;
	vector<int> groupIndexStart;


};

