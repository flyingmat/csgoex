#pragma once

#include "Utils/FindPattern.hpp"
#include "Utils/CaptureInterface.hpp"
#include "Utils/VmtHook.hpp"

#include "SDK/Math/Vector.hpp"
#include "SDK/Math/QAngle.hpp"
#include "SDK/Math/matrix3x4_t.hpp"

#include "SDK/CUserCmd.hpp"

#include "SDK/IBaseClientDLL.hpp"
#include "SDK/IClientMode.hpp"

IBaseClientDLL* pIBaseClientDLL;
IClientMode* pIClientMode;
IDirect3DDevice9* pIDirect3DDevice9;

VmtHook* hkIClientMode;
VmtHook* hkIDirect3DDevice9;

vr::IVRSystem* vr_ptr;

#include "Features/OpenVR.hpp"

#include "Menu/menu.hpp"
Menu* menu;

#include "Hooks/hkD3D9.hpp"
#include "Hooks/hkCreateMove.hpp"
