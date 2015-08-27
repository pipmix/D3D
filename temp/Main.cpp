#include <iostream>
#include <d3d11_1.h>
#pragma comment (lib, "d3d11.lib")
#include <DirectXMath.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
using namespace DirectX;

void main() {


	string filename = "mesh.txt";
	

	vector<XMFLOAT3> pos;
	vector<XMFLOAT3> normal;
	vector<XMFLOAT2> uv;


	wchar_t curChar;
	float x, y, z;
	struct face {
		XMFLOAT3 v1, v2, v3;
		XMFLOAT3 n1, n2, n3;
		XMFLOAT2 u1, u2, u3;
	};
	struct VERTEX {
		XMFLOAT3 pos;
		XMFLOAT3 normal;
		XMFLOAT2 uv;
	};

	string f1, f2, f3;

	vector<face> faces;

	ifstream file("mesh.txt");
	if (file){
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
				//	curChar = file.get();
				//	while (curChar != '\n')curChar = file.get();
				//	break;
				default:
					break;
			}
		}

		for (int i = 0; i < pos.size(); i++) std::cout << pos[i].x << " " << pos[i].y << " " << pos[i].z << endl;
		for (int i = 0; i < uv.size(); i++) std::cout << uv[i].x << " " << uv[i].y << " " << endl;
		for (int i = 0; i < normal.size(); i++) std::cout << normal[i].x << " " << normal[i].y << " " << normal[i].z << endl;
		



	}
	else std::cout << "ERROR" << endl;


	int t;
	std::cin >> t;
}


