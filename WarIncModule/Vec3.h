#pragma once
#include <math.h>

class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float data[3];
	};

	Vec3::Vec3() {}

	Vec3::Vec3(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	Vec3 operator *= (float const &o) { this->x *= o; this->y *= o; this->z *= o; return *this; }
	Vec3 operator /= (float const &o) { this->x /= o; this->y /= o; this->z /= o; return *this; }

	Vec3 operator * (float const &o) { Vec3 v = *this; v *= o; return v; }
	Vec3 operator / (float const &o) { Vec3 v = *this; v /= o; return v; }

	Vec3 operator += (Vec3 const &o) { this->x += o.x; this->y += o.y; this->z += o.z; return *this; }
	Vec3 operator -= (Vec3 const &o) { this->x -= o.x; this->y -= o.y; this->z -= o.z; return *this; }

	Vec3 operator + (Vec3 const &o) { Vec3 v = *this; v += o; return v; }
	Vec3 operator - (Vec3 const &o) { Vec3 v = *this; v -= o; return v; }

	float magnitude() { return sqrt(x*x + y*y + z*z); }
	float magnitude2d() { return sqrt(x*x + y*y); }

	float magnitude2d_2() { return sqrt(x*x + z*z); }

	void normalize() { *this /= magnitude(); }

	float dot(Vec3 Vec) { return this->x * Vec.x + this->y * Vec.y + this->z * Vec.z; }
	float Distance(Vec3 const &other) { Vec3 Difference = *this - other; return Difference.magnitude(); }
};

typedef Vec3 Vector3;