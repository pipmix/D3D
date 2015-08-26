#include "loadOBJ.h"

loadOBJ::loadOBJ(wstring filename){
	float x, y, z;

	wifstream fileIn(filename.c_str());
	if (fileIn) {

		while (fileIn) {
			curChar = fileIn.get();

			switch (curChar) {
				case '#':
					curChar = fileIn.get();
					while(curChar != '\n') curChar = fileIn.get();
					break;
				case 'v':
					curChar = fileIn.get();
					if (curChar == ' ') {
						fileIn >> x >> y >> z;
						if (rh)	pos.push_back(XMFLOAT3(x, y, z * -1.0f));	
						else pos.push_back(XMFLOAT3(x, y, z));
					}
					if (curChar == 't') {
						fileIn >> x >> y;
						if (rh)	uv.push_back(XMFLOAT2(x, 1.0f - y));
						else uv.push_back(XMFLOAT2(x,y));
						hasUv = true;
					}
					if (curChar == 'n') {
						fileIn >> x >> y >> z;
						if (rh)normal.push_back(XMFLOAT3(x,y,z * -1.0f));
						else normal.push_back(XMFLOAT3(x, y, z));
						hasNormal = true;
					}
				break;
				case 'g':
					curChar = fileIn.get();
					if (curChar == ' ') {
						posIndex.push_back(vIndex);
						groupCount++;
					}
				break;
				case 'm':
					for (int i = 0; i < 7; i++)curChar = fileIn.get();
					if (curChar == ' ') fileIn >> materialsLibrary;
				break;
				case 'u':
					for (int i = 0; i < 7; i++)curChar = fileIn.get();
					if (curChar == ' ') {
						materialsTemp = L"";
						fileIn >> materialsTemp;
						materials.push_back(materialsTemp);
					}
				break;
				default:
				break;
			}
		}
	}
}

loadOBJ::~loadOBJ()
{
}

void loadOBJ::addVertex(float x, float y, float z){



}
