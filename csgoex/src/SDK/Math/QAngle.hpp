#pragma once

#define M_PI_F		3.14159265358979323846f
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )

class QAngle {
public:
	float x, y, z;

	QAngle(float x, float y, float z) : x(x), y(y), z(z) {}
	QAngle() : QAngle(0, 0, 0) {}

	QAngle operator+(const QAngle& v) const {
		return QAngle(x + v.x, y + v.y, z + v.z);
	}

	QAngle operator-(const QAngle& v) const {
		return QAngle(x - v.x, y - v.y, z - v.z);
	}

	QAngle operator*(float fl) const {
		return QAngle(x * fl, y * fl, z * fl);
	}

	__forceinline QAngle& operator+=(const QAngle& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	__forceinline QAngle& operator-=(const QAngle& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	__forceinline QAngle& operator*=(float fl) {
		x *= fl; y *= fl; z *= fl;
		return *this;
	}
};

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
