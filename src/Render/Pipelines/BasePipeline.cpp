
#include "BasePipeline.hpp"

#include "pch.h"

namespace be::render::pipeline
{
	BasePipeline::BasePipeline(ComPtr<ID3D11Device> device) : m_cbuffer(device)
	{
		HRESULT hr = S_OK;

		m_device = device;
		hr = m_device->CreateDeferredContext(0, &m_context) TIF;
		m_program.Load(device, L"../res/shaders/test.vs.hlsl", L"../res/shaders/test.ps.hlsl");
		m_cbuffer.Update(m_pipelineTransforms);
	}

	void BasePipeline::BeginDraw(ComPtr<ID3D11RenderTargetView> target)
	{
		m_target = target;
		m_context->OMSetRenderTargets(1, m_target.GetAddressOf(), nullptr);
		m_context->RSSetViewports(1, &m_viewport);
		m_cbuffer.BindVS(m_context, 0);
		m_program.Bind(m_context);
	}

	ComPtr<ID3D11CommandList> BasePipeline::EndDraw()
	{
		m_target.Reset();
		ComPtr<ID3D11CommandList> commandList;
		m_context->FinishCommandList(true, &commandList);
		return commandList;
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
	}

	void BasePipeline::SetCamera(Camera* camera)
	{
		m_pipelineTransforms.view = camera->GetView();
		m_pipelineTransforms.viewProj = m_pipelineTransforms.view * m_pipelineTransforms.proj;
		m_cbuffer.Update(m_pipelineTransforms);
	}

	void BasePipeline::Clear()
	{
		m_context->ClearRenderTargetView(m_target.Get(), m_clearColor);
	}

	void BasePipeline::DrawObject(Object* object)
	{
		UINT offset = 0;
		UINT stride = sizeof(drawable::Vertex);
		m_context->IASetVertexBuffers(0, 1, object->GetRawMesh()->vertexBuffer.GetAddressOf(), &stride, &offset);
		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_context->Draw(object->GetRawMesh()->vertexCount, 0);
		object->GetRawCBuffer()->BindVS(m_context, 1);
	}
}
