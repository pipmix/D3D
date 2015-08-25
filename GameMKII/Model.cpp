#include "Model.h"



Model::Model(string fileName, ID3D11Device * d){

	wifstream fileIn(fileName.c_str());
	device = d;





	const D3D11_INPUT_ELEMENT_DESC ied[] ={
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	struct ConstantBuffer {
		XMFLOAT4X4 model;
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
	};


	
	device->CreateInputLayout(
		ied,
		ARRAYSIZE(ied),
		vertexShaderBytecode->Data,
		vertexShaderBytecode->Length,
		&inputLayout)
		);

	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(SimpleCubeVertex) * ARRAYSIZE(cubeVertices);
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	vertexBufferData.pSysMem = cubeVertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	
	device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);





	ComPtr<ID3D11Buffer> m_constantBuffer;
	ConstantBuffer m_constantBufferData;

	// ...

	// Create a constant buffer for passing model, view, and projection matrices
	// to the vertex shader.  This  allows us to rotate the cube and apply
	// a perspective projection to it.

	D3D11_BUFFER_DESC constantBufferDesc = { 0 };
	constantBufferDesc.ByteWidth = sizeof(m_constantBufferData);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;
	m_d3dDevice->CreateBuffer(
		&constantBufferDesc,
		nullptr,
		&m_constantBuffer
		);

	m_constantBufferData.model = float4x4( // identity matrix, since you are not animating the object
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	);
	// Specify the view (camera) transform corresponding to a camera position of
	// X = 0, Y = 1, Z = 2.  

	m_constantBufferData.view = float4x4(
		-1.00000000f, 0.00000000f, 0.00000000f, 0.00000000f,
		0.00000000f, 0.89442718f, 0.44721359f, 0.00000000f,
		0.00000000f, 0.44721359f, -0.89442718f, -2.23606800f,
		0.00000000f, 0.00000000f, 0.00000000f, 1.00000000f);

	// Finally, update the constant buffer perspective projection parameters
	// to account for the size of the application window.  In this sample,
	// the parameters are fixed to a 70-degree field of view, with a depth
	// range of 0.01 to 100.  

	float xScale = 1.42814801f;
	float yScale = 1.42814801f;
	if (backBufferDesc.Width > backBufferDesc.Height)
	{
		xScale = yScale *
			static_cast<float>(backBufferDesc.Height) /
			static_cast<float>(backBufferDesc.Width);
	}
	else
	{
		yScale = xScale *
			static_cast<float>(backBufferDesc.Width) /
			static_cast<float>(backBufferDesc.Height);
	}
	m_constantBufferData.projection = float4x4(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, -0.01f,
		0.0f, 0.0f, -1.0f, 0.0f
		);

	// Set the vertex and index buffers, and specify the way they define geometry.
	UINT stride = sizeof(SimpleCubeVertex);
	UINT offset = 0;
	m_d3dDeviceContext->IASetVertexBuffers(
		0,
		1,
		vertexBuffer.GetAddressOf(),
		&stride,
		&offset);

	m_d3dDeviceContext->IASetIndexBuffer(
		indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT,
		0);

	m_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);




	// Set the vertex and pixel shader stage state.
	m_d3dDeviceContext->VSSetShader(
		vertexShader.Get(),
		nullptr,
		0);


	m_d3dDeviceContext->VSSetConstantBuffers(
		0,
		1,
		m_constantBuffer.GetAddressOf());


	m_d3dDeviceContext->PSSetShader(
		pixelShader.Get(),
		nullptr,
		0
		);



}


Model::~Model()
{

	indexBuffer->Release();
	vertexBuffer->Release();
}

void Model::Draw()
{

	context->DrawIndexed(
		ARRAYSIZE(cubeIndices),
		0,
		0
		);
}

