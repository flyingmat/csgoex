#pragma once

bool openvr_init = false;

// Adapted from Source Engine's MatrixAngles - conversion required
// from OpenVR to engine coordinate system
inline void HmdMatrixToEngineAngles(const float m[3][4], QAngle& a) {
	float zx = sqrtf(m[2][2] * m[2][2] + m[0][2] * m[0][2]);
	if (zx > 0.001f) {
		a.x = RAD2DEG(atan2f(m[1][2], zx));
		a.y = RAD2DEG(atan2f(-m[0][2], -m[2][2]));
		a.z = RAD2DEG(atan2f(-m[1][0], m[1][1]));
	}
	else {
		a.x = RAD2DEG(atan2f(m[1][2], zx));
		a.y = RAD2DEG(atan2f(-m[2][0], m[0][0]));
		a.z = 0.0f;
	}
}

vr::HmdError OpenVR_Init() {
	vr::HmdError result;
	vr_ptr = vr::VR_Init(&result, vr::VRApplication_Other);
	if (result == vr::VRInitError_None)
		openvr_init = true;

	return result;
}
