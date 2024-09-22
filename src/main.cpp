
#include "Window/Window.hpp"
#include "Render/Device.hpp"
#include "Render/Drawable/Vertex.hpp"
#include "Render/Camera.hpp"

#include "Filesystem/ObjectDeserializer.hpp"

#include <Windows.h>

int main() try
{
	auto wnd = be::Window::CreateInstance();
	wnd->OpenAsync(L"bengine Window", { 1280, 720 });

	auto dev = std::make_shared<be::render::Device>();
	auto rnd = dev->CreateRenderer(wnd, { 1280, 720 });

	auto camera = be::render::Camera();

	be::fs::ObjectDeserializer deserializer;
	auto obj = deserializer.FromFile(dev, "C:/MyProjects/bengine/build/untitled.glb");

	obj->SetPosition({ 0.0f, 0.0f, -5.0f });

	while (wnd->IsRunning())
	{
		{
			GetAsyncKeyState('W') ? camera.Move({ 0.0f, 0.0f,-0.1f }) : void();
			GetAsyncKeyState('S') ? camera.Move({ 0.0f, 0.0f, 0.1f }) : void();
			GetAsyncKeyState('A') ? camera.Move({-0.1f, 0.0f, 0.0f }) : void();
			GetAsyncKeyState('D') ? camera.Move({ 0.1f, 0.0f, 0.0f }) : void();
			GetAsyncKeyState('Q') ? camera.SetPosition({ 0.0f, 0.0f, 0.0f }) : void();
			GetAsyncKeyState('E') ? rnd->SetSize({ 800, 600 }) : void();
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
	OutputDebugStringA(e.what());
	return 1;
}
