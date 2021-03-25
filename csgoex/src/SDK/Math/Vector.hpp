#pragma once

class Vector {
public:
	float x, y, z;

	Vector(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector() : Vector(0, 0, 0) {}

	__forceinline float LengthSqr() const {
		return (x * x + y * y + z * z);
	}

	__forceinline float Length() const {
		return sqrtf(LengthSqr());
	}

	__forceinline Vector operator+(const Vector& v) const {
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	__forceinline Vector operator-(const Vector& v) const {
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	__forceinline Vector operator*(float fl) const {
		return Vector(x * fl, y * fl, z * fl);
	}

	__forceinline Vector& operator+=(const Vector& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	__forceinline Vector& operator-=(const Vector& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	__forceinline Vector& operator*=(float fl) {
		x *= fl; y *= fl; z *= fl;
		return *this;
	}

	__forceinline float operator[](const size_t i) const {
		return ((float*)this)[i];
	}

	__forceinline float& operator[](const size_t i) {
		return ((float*)this)[i];
	}
};

inline void VectorClear(Vector& a) {
	a.x = a.y = a.z = 0.0f;
}

inline void VectorCopy(const Vector& src, Vector& dst) {
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void VectorAdd(const Vector& a, const Vector& b, Vector& c) {
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c) {
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

class _declspec(align(16)) VectorAligned : public Vector {
public:
	float w;

	VectorAligned(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	VectorAligned() : VectorAligned(0, 0, 0, 0) {}

	VectorAligned& operator=(const Vector& v) {
		this->x = v.x, this->y = v.y, this->z = v.z, this->w = 0.0f;
		return *this;
	}
};
