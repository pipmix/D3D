#pragma once
#include <string>
#include <vector>
#include <DirectXMath.h>
#include <fstream>
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


	void addVertex(float, float, float);
	void addVertex(XMFLOAT3);
	vector<XMFLOAT3> vertices;



	ID3D11Buffer* vertBuff;
	ID3D11Buffer* indexBuff;

	wchar_t curChar;

	bool rh = false;
	bool hasUv = false;
	bool hasNormal = false;
	int vIndex = 0;

	int groups = 0;
	vector<int> groupIndexStart;


};

