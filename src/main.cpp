
#include "Window/Window.hpp"
#include "Render/Device.hpp"
#include "Render/Drawable/Vertex.hpp"
#include "Render/Camera.hpp"

int main() try
{
	auto wnd = be::Window::CreateInstance();
	wnd->OpenAsync(L"bengine Window", { 1280, 720 });

	auto dev = std::make_shared<be::render::Device>();
	auto rnd = dev->CreateRenderer(wnd, { 1280, 720 });
	auto obj = dev->CreateObject();

	auto camera = be::render::Camera();

	be::render::drawable::Vertex vertices[] =
	{
		{ 0.0f, 0.5f, 0.0f }, 
		{ 0.5f,-0.5f, 0.0f },
		{-0.5f,-0.5f, 0.0f },
		{ 0.0f,-0.5f, 0.0f },
		{-0.5f, 0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
	};

	obj->SetVertices(vertices, 6);
	obj->SetPosition({ 0.0f, 0.0f, -5.0f });

	while (wnd->IsRunning())
	{
		rnd->SetCamera(&camera);
		rnd->BeginDraw();
		rnd->Clear();
		rnd->DrawObject(obj.get());
		rnd->EndDraw();
	}

	return 0;
}
catch (std::exception& e)
{
	return 1;
}
