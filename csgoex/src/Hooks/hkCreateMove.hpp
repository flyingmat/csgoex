#pragma once

typedef bool(__thiscall* CreateMove_t) (IClientMode*, float, CUserCmd*);

bool __fastcall hkCreateMove(IClientMode* ecx, void* edx, float flInputSampleTime, CUserCmd* cmd) {
	CreateMove_t oCreateMove = hkIClientMode->GetOriginalFunction<CreateMove_t>(24);

	vr::TrackedDevicePose_t device_poses[1];
	vr_ptr->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseSeated, 0, device_poses, 1);

	vr::TrackedDevicePose_t dp = device_poses[0];
	vr::HmdMatrix34_t matrix = dp.mDeviceToAbsoluteTracking;

	HmdMatrixToEngineAngles(matrix.m, cmd->viewangles);

	return oCreateMove(ecx, flInputSampleTime, cmd);
}
