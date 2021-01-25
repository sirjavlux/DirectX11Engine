#include "SDXEngine.h"

/*////////////////////////////////
* Graphics class functions
*/////////////////////////////////

// consrtuctor
Graphics::Graphics() {
	//set variables
	hWnd = NULL;
	wcex = NULL;
	swapchainPntr = NULL;
	devicePntr = NULL;
	deviceContextPntr = NULL;
	swapchainPntr = NULL;
	renderTargetViewPntr = NULL;

	inputLayoutPntr = NULL;
	vertexShaderPntr = NULL;
	pixelShaderPntr = NULL;

	vertexStride = 0;
	vertexOffset = 0;
	vertexCount = 0;

	vertexBufferPntr = NULL;
}

Graphics::Graphics(HWND* hWnd, WNDCLASSEX* wcex) {
	//set variables
	Graphics::hWnd = hWnd;
	Graphics::wcex = wcex;
	DXGI_SWAP_CHAIN_DESC swapchainDesc;

	swapchainPntr = NULL;
	devicePntr = NULL;
	deviceContextPntr = NULL;
	swapchainPntr = NULL;
	renderTargetViewPntr = NULL;

	inputLayoutPntr = NULL;
	vertexShaderPntr = NULL;
	pixelShaderPntr = NULL;

	vertexStride = 0;
	vertexOffset = 0;
	vertexCount = 0;

	vertexBufferPntr = NULL;

	//setup swap chain
	ZeroMemory(&swapchainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapchainDesc.BufferDesc.Width = 0;
	swapchainDesc.BufferDesc.Height = 0;
	swapchainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapchainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
	swapchainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
	swapchainDesc.SampleDesc.Count = 8;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount = 4;
	swapchainDesc.OutputWindow = *hWnd;
	swapchainDesc.Windowed = true;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.Flags = 0;

	// create
	D3D_FEATURE_LEVEL feature_level;
	UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
	flags |= D3D11_CREATE_DEVICE_DEBUG;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapchainDesc,
		&swapchainPntr,
		&devicePntr,
		&feature_level,
		&deviceContextPntr);
	assert(S_OK == hr && swapchainPntr && devicePntr && deviceContextPntr);

	// create frame buffer
	ID3D11Texture2D* framebuffer;
	hr = swapchainPntr->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&framebuffer); assert(SUCCEEDED(hr));
	hr = devicePntr->CreateRenderTargetView(framebuffer, 0, &renderTargetViewPntr); assert(SUCCEEDED(hr));
	framebuffer->Release();

	// build shader
	flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG; // add more debug output
#endif
	ID3DBlob* vsBlobPntr = NULL, * psBlobPntr = NULL, * error_blob = NULL;

	// COMPILE VERTEX SHADER
	hr = D3DCompileFromFile(
		L"shaders.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"vs_main",
		"vs_5_0",
		flags,
		0,
		&vsBlobPntr,
		&error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			OutputDebugStringA((char*)error_blob->GetBufferPointer());
			error_blob->Release();
		}
		if (vsBlobPntr) { vsBlobPntr->Release(); }
		assert(false);
	}

	// COMPILE PIXEL SHADER
	hr = D3DCompileFromFile(
		L"shaders.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"ps_main",
		"ps_5_0",
		flags,
		0,
		&psBlobPntr,
		&error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			OutputDebugStringA((char*)error_blob->GetBufferPointer());
			error_blob->Release();
		}
		if (psBlobPntr) { psBlobPntr->Release(); }
		assert(false);
	}

	// create vertex and pixel shader
	vertexShaderPntr = NULL;
	pixelShaderPntr = NULL;

	hr = devicePntr->CreateVertexShader(
		vsBlobPntr->GetBufferPointer(),
		vsBlobPntr->GetBufferSize(),
		NULL,
		&vertexShaderPntr);
	assert(SUCCEEDED(hr));

	hr = devicePntr->CreatePixelShader(
		psBlobPntr->GetBufferPointer(),
		psBlobPntr->GetBufferSize(),
		NULL,
		&pixelShaderPntr);
	assert(SUCCEEDED(hr));

	// create input layout
	inputLayoutPntr = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
	  { "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  { "COL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  //{ "NOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  //{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	hr = devicePntr->CreateInputLayout(
		inputElementDesc,
		ARRAYSIZE(inputElementDesc),
		vsBlobPntr->GetBufferPointer(),
		vsBlobPntr->GetBufferSize(),
		&inputLayoutPntr);
	assert(SUCCEEDED(hr));
}

// get swap chain
IDXGISwapChain* Graphics::getSwapChain() {
	return swapchainPntr;
}

ID3D11Device* Graphics::getDevice() {
	return devicePntr;
}

ID3D11DeviceContext* Graphics::getDeviceContext() {
	return deviceContextPntr;
}

ID3D11RenderTargetView* Graphics::getRenderTargetView() {
	return renderTargetViewPntr;
}

ID3D11VertexShader* Graphics::getVertexShader() {
	return vertexShaderPntr;
}

/*////////////////////////////////
* Render frame
*/////////////////////////////////

void Graphics::render() {
	/* clear the back buffer to cornflower blue for the new frame */
	float background_colour[4] = { 0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f };
	deviceContextPntr->ClearRenderTargetView(renderTargetViewPntr, background_colour);

	/**** Rasteriser state - set viewport area *****/
	RECT winRect;
	GetClientRect(*hWnd, &winRect);
	D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top), 0.0f, 1.0f };
	deviceContextPntr->RSSetViewports(1, &viewport);

	/**** Output Merger *****/
	deviceContextPntr->OMSetRenderTargets(1, &renderTargetViewPntr, NULL);

	/***** Input Assembler (map how the vertex shader inputs should be read from vertex buffer) ******/
	deviceContextPntr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContextPntr->IASetInputLayout(inputLayoutPntr);
	deviceContextPntr->IASetVertexBuffers(0, 1, &vertexBufferPntr, &vertexStride, &vertexOffset);

	/*** set vertex shader to use and pixel shader to use, and constant buffers for each ***/
	deviceContextPntr->VSSetShader(vertexShaderPntr, NULL, 0);
	deviceContextPntr->PSSetShader(pixelShaderPntr, NULL, 0);

	/*** draw the vertex buffer with the shaders ****/
	deviceContextPntr->Draw(vertexCount, 0);

	/**** swap the back and front buffers (show the frame we just drew) ****/
	swapchainPntr->Present(1, 0);
}

/*////////////////////////////////
* Update frame triangles
*/////////////////////////////////

void Graphics::update() {
	// triangle data <----------- test
	Vertex vert[] =
	{
		// test triangle
		Vertex(0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // center
		Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // right
		Vertex(-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // left

		// test triangle 2
		Vertex(0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // center
		Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // right
		Vertex(-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // left
	};

	vertexStride = sizeof(Vertex);
	vertexOffset = 0;
	vertexCount = sizeof(vert)/sizeof(*vert);

	// create vertex buffer
	vertexBufferPntr = NULL;
	{ /*** load mesh data into vertex buffer **/
		D3D11_BUFFER_DESC vertexBuffDescr = {};
		vertexBuffDescr.ByteWidth = sizeof(vert);
		vertexBuffDescr.Usage = D3D11_USAGE_DEFAULT;
		vertexBuffDescr.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA srData = { 0 };
		srData.pSysMem = vert;
		HRESULT hr = devicePntr->CreateBuffer(
			&vertexBuffDescr,
			&srData,
			&vertexBufferPntr);
		assert(SUCCEEDED(hr));
	}
}

// vertex
Vertex::Vertex() {
	pos = DirectX::XMFLOAT3(0, 0, 0);
	color = DirectX::XMFLOAT4(0, 0, 0, 0);
}
Vertex::Vertex(float x, float y, float z, float r, float g, float b, float a) {
	pos = DirectX::XMFLOAT3(x, y, z);
	color = DirectX::XMFLOAT4(r, g, b, a);
}