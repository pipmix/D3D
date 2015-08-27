#include "loadOBJ.h"

loadOBJ::loadOBJ(wstring filename){
	float x, y, z;

	wifstream file(filename.c_str());
	if (file) {

		while (file) {
			curChar = file.get();

			switch (curChar) {
				case 'v':
					curChar = file.get();
					if (curChar == ' '){
						file >> x >> y >> z;
						pos.push_back(XMFLOAT3(x, y, z));
					}
					if (curChar == 't') {
						file >> x >> y;
						uv.push_back(XMFLOAT2(x,y));
					}
					if (curChar == 'n') {
						file >> x >> y >> z;
						normal.push_back(XMFLOAT3(x, y, z));
					}
				break;
				case 'f':
					curChar = file.get();
					file >> vertDataString;
					wstring delimiter = L"/";
					wstring token = vertDataString.substr(0, vertDataString.find(delimiter));
					token = 

					//for (int i = 0; i < vertDataString.length(); i++) {


					
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
