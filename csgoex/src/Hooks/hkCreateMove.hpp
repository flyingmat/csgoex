#pragma once

typedef bool(__thiscall* CreateMove_t) (IClientMode*, float, CUserCmd*);

bool __fastcall hkCreateMove(IClientMode* ecx, void* edx, float flInputSampleTime, CUserCmd* cmd) {
	CreateMove_t oCreateMove = hkIClientMode->GetOriginalFunction<CreateMove_t>(24);
	return oCreateMove(ecx, flInputSampleTime, cmd);
}
