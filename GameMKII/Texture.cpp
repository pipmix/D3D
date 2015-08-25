#include "Texture.h"

Texture::Texture(int x, int y, int a, int b, ID3D11Device* dev, wstring n) {
	numberOfTextureTilesX = x;
	numberOfTextureTilesY = y;
	textureTileSizeX = a;
	textureTileSizeY = b;
	textureName = n;
	wstring s = L"Assets/" + textureName + L".dds";
	CreateDDSTextureFromFile(dev, s.c_str(), NULL, &textureResourceView, NULL);
}
// Single Texture
Texture::Texture(ID3D11Device* dev, wstring n) {
	textureName = n;
	wstring s = L"Assets/" + textureName + L".dds";
	CreateDDSTextureFromFile(dev, s.c_str(), NULL, &textureResourceView, NULL);
}
// Custom Source Rect
Texture::Texture(ID3D11Device* dev, wstring n, int* sR) {
	wstring s = L"Assets/" + textureName + L".dds";
	CreateDDSTextureFromFile(dev, s.c_str(), NULL, &textureResourceView, NULL);
	//TODO add source rect
}
Texture::~Texture() {
	delete textureResourceView;
	textureResourceView = nullptr;
}
int	Texture::ReturnNumberOfTextureTilesX() { return numberOfTextureTilesX; }
int	Texture::ReturnNumberOfTextureTilesY() { return numberOfTextureTilesY; }
int	Texture::ReturnTextureTileSizeX() { return textureTileSizeX; }
int	Texture::ReturnTextureTileSizeY() { return textureTileSizeY; }
ID3D11ShaderResourceView* Texture::ReturnTexture() { return textureResourceView; }
wstring Texture::ReturnName() { return textureName; }
