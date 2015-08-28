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
	IDXGISwapChain * swapchain;
	ID3D11Device * device;       
	ID3D11DeviceContext * context;
	ID3D11RenderTargetView *backbuffer;   
	ID3D11DepthStencilView *zbuffer;       
	ID3D11Texture2D *pDepthBuffer;


};

