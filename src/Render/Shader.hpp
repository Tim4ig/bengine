
#pragma once

#include "pch.h"

namespace be::render::shader
{
	struct ShaderProgram
	{
		void Load(ComPtr<ID3D11Device> device, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
		void LoadBinary(ComPtr<ID3D11Device> device, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
		void LoadBinary(ComPtr<ID3D11Device> device, ComPtr<ID3DBlob> vertexShaderBlob, ComPtr<ID3DBlob> pixelShaderBlob);
		void Bind(ComPtr<ID3D11DeviceContext> context);
		ComPtr<ID3D11VertexShader> vertexShader;
		ComPtr<ID3D11PixelShader> pixelShader;
		ComPtr<ID3D11InputLayout> inputLayout;
	};
}
