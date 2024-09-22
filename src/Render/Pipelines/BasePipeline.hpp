
#pragma once

#include "pch.h"

#include "Pipeline.hpp"
#include "../Shader.hpp"
#include "../CBuffer.hpp"
#include "../Camera.hpp"

namespace be::render::pipeline
{
	class BasePipeline : public Pipeline
	{
	public:
		BasePipeline(ComPtr<ID3D11Device> device);
		~BasePipeline() = default;

		void BeginDraw(ComPtr<ID3D11RenderTargetView> target) override;
		ComPtr<ID3D11CommandList> EndDraw() override;

		void ResetDeferredContext() override;
		void Resize(POINT size) override;
		void SetCamera(Camera* camera);

		void Clear() override;
		void DrawObject(Object* object) override;
	private:
		pipeline::CBuffer m_cbuffer;
		shader::ShaderProgram m_program;
		float m_clearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

		struct
		{
			dm::Matrix view;
			dm::Matrix proj;
			dm::Matrix viewProj;
		} m_pipelineTransforms;
	};
}
