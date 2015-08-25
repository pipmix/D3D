#pragma once
#include <string>
#include <vector>
#include <DirectXMath.h>
using namespace std;
using namespace DirectX;

class loadOBJ{


public:
	loadOBJ(string filename);
	~loadOBJ();

private:


	void addVertex(float, float, float);
	void addVertex(XMFLOAT3);
	vector<XMFLOAT3> vertices;




};

