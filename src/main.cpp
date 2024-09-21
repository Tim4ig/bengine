
#include "Window/Window.hpp"
#include "Render/Device.hpp"
#include "Render/Drawable/Vertex.hpp"
#include "Render/Camera.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

using namespace tinygltf;

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
		{ 0.0f,-1.5f, 0.0f },
		{-0.5f, 0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
	};

	obj->SetVertices(vertices, 9);
	obj->SetPosition({ 0.0f, 0.0f, -5.0f });

	while (wnd->IsRunning())
	{
		{
			GetAsyncKeyState('W') ? camera.Move({ 0.0f, 0.0f,-0.1f }) : void();
			GetAsyncKeyState('S') ? camera.Move({ 0.0f, 0.0f, 0.1f }) : void();
			GetAsyncKeyState('A') ? camera.Move({-0.1f, 0.0f, 0.0f }) : void();
			GetAsyncKeyState('D') ? camera.Move({ 0.1f, 0.0f, 0.0f }) : void();
			GetAsyncKeyState('Q') ? camera.SetPosition({ 0.0f, 0.0f, 0.0f }) : void();
		}

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
