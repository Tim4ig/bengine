
#include "Window.hpp"

namespace be
{
	Window::~Window()
	{
		m_isRunning = false;
	}

	std::shared_ptr<Window> Window::CreateInstance()
	{
		return std::shared_ptr<Window>(new Window());
	} 

	void be::Window::OpenAsync(const wchar_t* title, POINT size)
	{

		if (m_isRunning) return;
		if (m_windowThread.valid()) m_windowThread.wait();

		auto OpenSync = [this, title, size]()
			{
				WNDCLASS wc = {};
				wc.lpfnWndProc = WindowProc;
				wc.hInstance = GetModuleHandle(nullptr);
				wc.lpszClassName = L"bengineWindowClass";
				wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
				RegisterClass(&wc);

				m_hwnd = CreateWindow(
					wc.lpszClassName,
					title,
					(WS_OVERLAPPEDWINDOW) & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
					CW_USEDEFAULT, CW_USEDEFAULT,
					size.x, size.y,
					nullptr,
					nullptr,
					wc.hInstance,
					nullptr
				);

				SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
				ShowWindow(m_hwnd, SW_SHOWDEFAULT);
				m_isRunning = true;

				MSG msg = {};
				while (GetMessage(&msg, nullptr, 0, 0) && m_isRunning)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				m_isRunning = false;
			};

		m_windowThread = std::async(std::launch::async, OpenSync);
		while (m_isRunning) std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	HWND be::Window::GetHandle() const
	{
		return m_hwnd;
	}

	bool Window::IsRunning() const
	{
		return m_isRunning;
	}

	POINT Window::GetSize() const
	{
		RECT client;
		GetClientRect(m_hwnd, &client);
		return { client.right, client.bottom };
	}

	void Window::SetSize(POINT size) const
	{
		if (!m_isRunning) return;

		RECT rect = {};
		GetWindowRect(m_hwnd, &rect);
		MoveWindow(m_hwnd, rect.left, rect.top, size.x, size.y, TRUE);
	}

	LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* self = nullptr;

		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		self = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (!self) return DefWindowProc(hwnd, msg, wParam, lParam);

		switch (msg)
		{
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
