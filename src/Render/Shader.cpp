
#include "Shader.hpp"

namespace be::render::shader
{
	void ShaderProgram::Load(ComPtr<ID3D11Device> device, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
	{
		HRESULT hr = S_OK;

		ComPtr<ID3DBlob> vertexShaderBlob;
		ComPtr<ID3DBlob> pixelShaderBlob;

		hr = D3DCompileFromFile(vertexShaderPath.c_str(), nullptr, nullptr, "main", "vs_5_0", 0, 0, &vertexShaderBlob, nullptr) TIF;
		hr = D3DCompileFromFile(pixelShaderPath.c_str(), nullptr, nullptr, "main", "ps_5_0", 0, 0, &pixelShaderBlob, nullptr) TIF;

		this->LoadBinary(device, vertexShaderBlob, pixelShaderBlob);
	}

	void ShaderProgram::LoadBinary(ComPtr<ID3D11Device> device, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
	{
		ComPtr<ID3DBlob> vertexShaderBlob;
		ComPtr<ID3DBlob> pixelShaderBlob;

		D3DReadFileToBlob(vertexShaderPath.c_str(), &vertexShaderBlob);
		D3DReadFileToBlob(pixelShaderPath.c_str(), &pixelShaderBlob);

		this->LoadBinary(device, vertexShaderBlob, pixelShaderBlob);
	}

	void ShaderProgram::LoadBinary(ComPtr<ID3D11Device> device, ComPtr<ID3DBlob> vertexShaderBlob, ComPtr<ID3DBlob> pixelShaderBlob)
	{
		HRESULT hr = S_OK;
		hr = device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, &vertexShader) TIF;
		hr = device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, &pixelShader) TIF;

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		hr = device->CreateInputLayout(layout, 1, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &inputLayout) TIF;
	}

	void ShaderProgram::Bind(ComPtr<ID3D11DeviceContext> context)
	{
		if (!vertexShader || !pixelShader) return;
		context->VSSetShader(vertexShader.Get(), nullptr, 0);
		context->PSSetShader(pixelShader.Get(), nullptr, 0);
		context->IASetInputLayout(inputLayout.Get());
	}
}
