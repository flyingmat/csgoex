#pragma once

#include <intrin.h>
#pragma intrinsic(_ReturnAddress)



//void HmdMatrixAngles(const float matrix[3][4], float* angles) {
//	float forward[3];
//	float left[3];
//	float up[3];
//
//	// openvr adjustments
//	forward[0] = -matrix[2][2];
//	forward[1] = -matrix[0][2];
//	forward[2] = matrix[1][2];
//	left[0] = -matrix[2][0];
//	left[1] = -matrix[0][0];
//	left[2] = matrix[1][0];
//	up[2] = matrix[1][1];
//
//	float xyDist = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);
//
//	// enough here to get angles?
//	if (xyDist > 0.001f)
//	{
//		// (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
//		angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));
//
//		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
//		angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));
//
//		// (roll)	z = ATAN( left.z, up.z );
//		angles[2] = RAD2DEG(atan2f(left[2], up[2]));
//	}
//	else	// forward is mostly Z, gimbal lock-
//	{
//		// (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
//		angles[1] = RAD2DEG(atan2f(-left[0], left[1]));
//
//		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
//		angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));
//
//		// Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
//		angles[2] = 0;
//	}
//}

typedef HRESULT(__stdcall* EndScene_t) (IDirect3DDevice9*);

HRESULT __stdcall hkEndScene(IDirect3DDevice9* thisptr) {
	EndScene_t oEndScene = hkIDirect3DDevice9->GetOriginalFunction<EndScene_t>(42);
	uintptr_t rtn = reinterpret_cast<uintptr_t>(_ReturnAddress());

	if ((rtn & 0xFFFF) != 0xFAD3)
		return oEndScene(thisptr);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	vr::TrackedDevicePose_t device_poses[1];
	vr_ptr->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseSeated, 0, device_poses, 1);

	vr::TrackedDevicePose_t dp = device_poses[0];
	vr::HmdMatrix34_t matrix = dp.mDeviceToAbsoluteTracking;

	QAngle a;
	HmdMatrixToEngineAngles(matrix.m, a);

	ImGui::SetNextWindowSize(ImVec2(600, 300));
	ImGui::Begin("Debug");

	if (ImGui::BeginTable("matrix", 4)) {
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("X");
		ImGui::TableNextColumn();
		ImGui::Text("Y");
		ImGui::TableNextColumn();
		ImGui::Text("Z");
		ImGui::TableNextColumn();
		ImGui::Text("P");
		for (size_t i = 0; i < 3; i++) {
			ImGui::TableNextRow();
			for (size_t k = 0; k < 4; k++) {
				ImGui::TableNextColumn();
				ImGui::Text("%.2f", matrix.m[i][k]);
			}
		}
		ImGui::TableNextRow();
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text("%.2f", a.x);
		ImGui::TableNextColumn();
		ImGui::Text("%.2f", a.y);
		ImGui::TableNextColumn();
		ImGui::Text("%.2f", a.z);

		ImGui::EndTable();
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(thisptr);
}
