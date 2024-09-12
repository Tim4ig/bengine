
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

		HWND GetHandle() const;
		bool IsRunning() const;
		void SetSize(POINT size) const;
		POINT GetSize() const;
	private:
		HWND m_hwnd = nullptr;
		bool m_isRunning = false;
		std::future<void> m_windowThread;

		Window() = default;
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}
