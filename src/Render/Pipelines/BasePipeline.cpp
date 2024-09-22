
#include "BasePipeline.hpp"

#include "pch.h"

namespace be::render::pipeline
{
	BasePipeline::BasePipeline(ComPtr<ID3D11Device> device) : m_cbuffer(device)
	{
		HRESULT hr = S_OK;

		m_device = device;
		m_program.Load(device, L"../res/shaders/test.vs.hlsl", L"../res/shaders/test.ps.hlsl");
		m_cbuffer.Update(m_pipelineTransforms);
	}

	void BasePipeline::BeginDraw(ComPtr<ID3D11RenderTargetView> target)
	{
		HRESULT hr = S_OK;
		if (!m_context) { hr = m_device->CreateDeferredContext(0, &m_context) TIF; }

		m_target = target.Get();
		m_context->OMSetRenderTargets(1, &m_target, nullptr);
		m_context->RSSetViewports(1, &m_viewport);
		m_cbuffer.BindVS(m_context, 0);
		m_program.Bind(m_context);
	}

	ComPtr<ID3D11CommandList> BasePipeline::EndDraw()
	{
		ComPtr<ID3D11CommandList> commandList;
		m_context->FinishCommandList(true, &commandList);
		return commandList;
	}

	void BasePipeline::ResetDeferredContext()
	{
		m_context.Reset();
	}

	void BasePipeline::Resize(POINT size)
	{
		m_viewport = {};
		m_viewport.Width = static_cast<float>(size.x);
		m_viewport.Height = static_cast<float>(size.y);
		m_viewport.MaxDepth = 1.0f;
		m_pipelineTransforms.proj = dm::Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PIDIV4, m_viewport.Width / m_viewport.Height, 0.1f, 100.0f);
		m_pipelineTransforms.viewProj = m_pipelineTransforms.view * m_pipelineTransforms.proj;
		m_cbuffer.Update(m_pipelineTransforms);
		this->ResetDeferredContext();
	}

	void BasePipeline::SetCamera(Camera* camera)
	{
		m_pipelineTransforms.view = camera->GetView();
		m_pipelineTransforms.viewProj = m_pipelineTransforms.view * m_pipelineTransforms.proj;
		m_cbuffer.Update(m_pipelineTransforms);
	}

	void BasePipeline::Clear()
	{
		m_context->ClearRenderTargetView(m_target, m_clearColor);
	}

	void BasePipeline::DrawObject(Object* object)
	{
		UINT offset = 0;
		UINT stride = sizeof(drawable::Vertex);
		ID3D11Buffer* buffers[] = { object->GetVertexBuffer() };
		m_context->IASetVertexBuffers(0, 1, buffers, &stride, &offset);
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_context->Draw(object->GetVertexCount(), 0);
		object->GetRawCBuffer()->BindVS(m_context, 1);
	}
}
