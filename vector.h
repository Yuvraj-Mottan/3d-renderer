#pragma once
#include<iostream>
#include<cmath>

class vec3 {
public:
	float x, y, z;
	vec3(float i) {
		this->x = this->y = this->z = i;
	}
	vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	vec3 operator +(const vec3& v) {
		return vec3(x + v.x, y + v.y, z + v.z);
	}
	vec3 operator -(const vec3& v) {
		return vec3(x - v.x, y - v.y, z - v.z);
	}
	vec3 operator *(float s) {
		return vec3(x*s, y*s, z*s);
	}
	vec3 operator /(float s) {
		if (s != 0) {
			return vec3(x/s, y/s, z/s);
		}
	}

	float len() {
		return sqrt(x * x + y * y + z * z);
	}
	vec3 normalize() {
		float l = len();
		if (len != 0) {
			return *this / l;
		}
		return *this;
	}
	vec3 cross(const vec3& a, const vec3& b) {
		return vec3(a.y * b.z - b.y * a.z, a.x * b.z - b.x * a.z, a.x * b.y - b.x * a.y);
	}

};



