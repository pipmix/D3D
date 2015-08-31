#pragma once
#include <d3d11_1.h>
#include <DirectXMath.h>
#pragma comment (lib, "d3d11.lib")
using namespace DirectX;





class Game{
public:
	Game(HWND hWnd);
	~Game();
	void Update();
	void Draw();

	ID3D11Device* ReturnDevice();
	ID3D11DeviceContext* ReturnContext();
	
private:
	IDXGISwapChain * swapchain = nullptr;
	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * context = nullptr;
	ID3D11RenderTargetView *backbuffer = nullptr;
	ID3D11DepthStencilView *zbuffer = nullptr;
	ID3D11Texture2D *pDepthBuffer = nullptr;

	ID3D11Texture2D *pBackBuffer = nullptr;


};

