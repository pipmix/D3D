#include "Game.h"

Game::Game(HWND hWnd){

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;                                    
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
	scd.OutputWindow = hWnd;                                
	scd.SampleDesc.Count = 1;                               
	scd.Windowed = TRUE;                                    

	D3D11CreateDeviceAndSwapChain(0,D3D_DRIVER_TYPE_HARDWARE,0,0,0,0,D3D11_SDK_VERSION,&scd,&swapchain,&device,NULL,&context);


	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);


	device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();
	context->OMSetRenderTargets(1, &backbuffer, NULL);


	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 720;
	viewport.Height = 480;
	context->RSSetViewports(1, &viewport);


}

Game::~Game(){
	swapchain->Release();
	backbuffer->Release();
	device->Release();
	context->Release();
}

void Game::Update()
{
}

void Game::Draw()
{
	float fill[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	context->ClearRenderTargetView(backbuffer,fill);


	swapchain->Present(0, 0);
}
