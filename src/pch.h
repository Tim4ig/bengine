
#pragma once

#ifndef UNICODE
#define UNICODE 1
#endif // !UNICODE

#include "Shared.hpp"
#include "Exception.hpp"

#include "SimpleMath.h"
#include "SimpleMath.inl"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <memory>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using Microsoft::WRL::ComPtr;
namespace dm = DirectX::SimpleMath;
