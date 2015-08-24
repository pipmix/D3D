#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11_1.lib")
using namespace DirectX;





class Game{
public:
	Game(HWND hWnd);
	~Game();
	void Update();
	void Draw();
private:
	IDXGISwapChain * swapchain;
	ID3D11Device * device;       
	ID3D11DeviceContext * context;
	ID3D11RenderTargetView *backbuffer;   

};

