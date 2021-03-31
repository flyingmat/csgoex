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
