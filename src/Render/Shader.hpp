
#pragma once

#include "pch.h"

namespace be::render::shader
{
	class ShaderProgram
	{
	public:
		void Bind(ComPtr<ID3D11DeviceContext> context);
		void Load(ComPtr<ID3D11Device> device, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
		void LoadBinary(ComPtr<ID3D11Device> device, std::wstring vertexShaderPath, std::wstring pixelShaderPath);
		void LoadBinary(ComPtr<ID3D11Device> device, ComPtr<ID3DBlob> vertexShaderBlob, ComPtr<ID3DBlob> pixelShaderBlob);
	private:
		ComPtr<ID3D11VertexShader> m_vertexShader;
		ComPtr<ID3D11PixelShader> m_pixelShader;
		ComPtr<ID3D11InputLayout> m_inputLayout;
	};
}
