
#pragma once

#include "pch.h"

#include <future>

namespace be
{
	class Window
	{
	public:
		~Window();

		static std::shared_ptr<Window> CreateInstance();
		void OpenAsync(const wchar_t* title, POINT size);

		void SetSize(POINT size) const;

		HWND GetHandle() const;
		bool IsRunning() const;
		POINT GetSize() const;
	private:
		Window() = default;

		HWND m_hwnd = nullptr;
		bool m_isRunning = false;
		std::future<void> m_windowThread;

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}
