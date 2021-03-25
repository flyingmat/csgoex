#pragma once

#include "Utils/CaptureInterface.hpp"
#include "Utils/VmtHook.hpp"

#include "SDK/Math/Vector.hpp"
#include "SDK/Math/QAngle.hpp"

#include "SDK/CUserCmd.hpp"

#include "SDK/IBaseClientDLL.hpp"
#include "SDK/IClientMode.hpp"

IBaseClientDLL* pIBaseClientDLL;
IClientMode* pIClientMode;

std::unique_ptr<VmtHook> hkIClientMode;

#include "Hooks/hkCreateMove.hpp"
