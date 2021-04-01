#pragma once

class VMatrix {
public:
	// array access
	inline float* operator[](int i) {
		return m[i];
	}

	inline const float* operator[](int i) const {
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float* Base() {
		return &m[0][0];
	}

	inline const float* Base() const {
		return &m[0][0];
	}

public:
	// The matrix.
	float		m[4][4];
};
