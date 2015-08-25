#include "loadOBJ.h"





loadOBJ::loadOBJ(wstring filename)
{

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
						float x, y, z;
						fileIn >> x >> y >> z;
						if (rh)	pos.push_back(XMFLOAT3(x, y, z * -1.0f));	
						else pos.push_back(XMFLOAT3(x, y, z));
					}
					if (curChar == 't') {
						float u, v;
						fileIn >> u >> v;
						if (rh)	uv.push_back(XMFLOAT2(u, 1.0f - v));
						else uv.push_back(XMFLOAT2(u,v));
						hasUv = true;
					}
					if (curChar == 'n') {
						float x, y, z;
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


			}



		}




	}

}

loadOBJ::~loadOBJ()
{
}

void loadOBJ::addVertex(float x, float y, float z){



		vertices.push_back(
			XMFLOAT3(
			(vertices[x], vertices[x + 1], vertices[x + 2]),
			vertices[y], vertices[y + 1], vertices[y + 2],
			vertices[z], vertices[z + 1], vertices[z + 2]
				)
			);







}
