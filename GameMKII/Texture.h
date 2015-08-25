#pragma once

#include <d3d11_1.h>
#include "DDSTextureLoader.h"
#include <string>
#pragma comment (lib, "d3d11.lib")
using namespace std;
using namespace DirectX;




class Texture {
public:
	Texture(ID3D11Device*, wstring);
	Texture(ID3D11Device*, wstring, int *);
	Texture(int, int, int, int, ID3D11Device*, wstring);
	~Texture();
	int		ReturnNumberOfTextureTilesX();
	int		ReturnNumberOfTextureTilesY();
	int		ReturnTextureTileSizeX();
	int		ReturnTextureTileSizeY();
	RECT*		ReturnSourceRect();
	void		SetSourceRect(RECT); // dont be lazy and make a hud class
	wstring	ReturnName();
	ID3D11ShaderResourceView* ReturnTexture();
private:
	int		numberOfTextureTilesX;
	int		numberOfTextureTilesY;
	int		textureTileSizeX;
	int		textureTileSizeY;
	void	loadAnimationXML();
	wstring	textureName;
	ID3D11ShaderResourceView* textureResourceView;
	bool	hasAnimation;
	struct Animation {
		string animeName;
		int	numberOfFrames;
		int * frameLocation;
	};
	Animation* animation;
	int numberOfAnimation;
};