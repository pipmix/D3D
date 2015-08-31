#include "Game.h"

Game::Game(HWND hWnd){

	//SWAPCHAIN
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount = 1;
	scd.BufferDesc.Width = 720;
	scd.BufferDesc.Height = 480;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
	scd.OutputWindow = hWnd;                                
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;                                    
	D3D11CreateDeviceAndSwapChain(0,D3D_DRIVER_TYPE_HARDWARE,0,0,0,0,D3D11_SDK_VERSION,&scd,&swapchain,&device,NULL,&context);

	//DEPTH STENCIL
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	device->CreateDepthStencilView(pDepthBuffer, &dsvd, &zbuffer);

	//BACKBUFFER
	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();
	context->OMSetRenderTargets(1, &backbuffer, zbuffer);


	//VIEWPORT
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 720;
	viewport.Height = 480;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	//DEPTH BUFFER
	D3D11_TEXTURE2D_DESC texd;
	ZeroMemory(&texd, sizeof(texd));
	texd.Width = 720;
	texd.Height = 480;
	texd.ArraySize = 1;
	texd.MipLevels = 1;
	texd.SampleDesc.Count = 4;
	texd.Format = DXGI_FORMAT_D32_FLOAT;
	texd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&texd, NULL, &pDepthBuffer);








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

	//context->OMSetRenderTargets(1, &backbuffer, zbuffer );


	swapchain->Present(0, 0);
}

ID3D11Device * Game::ReturnDevice()
{
	return device;
}

ID3D11DeviceContext * Game::ReturnContext()
{
	return context;
}

