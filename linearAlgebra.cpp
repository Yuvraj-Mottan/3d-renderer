#include"Maths.h"
#include<cmath>
#define PI 3.14159
mat4 createMatrixTransform(vec3 translation) {
	mat4 matrix;
	for (int i = 0; i < 16; i++) {
		matrix.m[i] = 0.0f;
	}
	matrix.m[0] = 1.0f;
	matrix.m[5] = 1.0f;
	matrix.m[10] = 1.0f;
	matrix.m[15] = 1.0f;

	matrix.m[12] = translation.x;
	matrix.m[13] = translation.y;
	matrix.m[14] = translation.z;
	return matrix;
}
mat4 createZrotation(float angle) {
	mat4 matrix;
	for (int i = 0; i < 16; i++) {
		matrix.m[i] = 0.0f;
	}
	float rad = angle * PI / 180.0f;
	float c = cosf(rad);
	float s = sinf(rad);

	matrix.m[0] = c;
	matrix.m[5] = c;
	matrix.m[10] = 1.0f;
	matrix.m[15] = 1.0f;
	matrix.m[1] = s;
	matrix.m[4] = -s;

	return matrix;
}
mat4 createModelMatrix(vec3 translation, float angle) {
	mat4 matrix;
	for (int i = 0; i < 16; i++) {
		matrix.m[i] = 0.0f;
	}
	float rad = angle * PI / 180.0f;
	float c = cosf(rad);
	float s = sinf(rad);

	matrix.m[0] = c;
	matrix.m[5] = c;
	matrix.m[10] = 1.0f;
	matrix.m[15] = 1.0f;
	matrix.m[1] = s;
	matrix.m[4] = -s;
	matrix.m[12] = translation.x;
	matrix.m[13] = translation.y;
	matrix.m[14] = translation.z;
	return matrix;
}


float dot(vec3 a, vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
vec3 normalize(vec3 a) {
	float mag = sqrtf(dot(a, a));
	if (!mag) {
		vec3 b = { a.x / mag,a.y / mag,a.z / mag };
		return b;
	}
	return a;
}
vec3 cross(vec3 a, vec3 b) {
	vec3 c;
	c.x = a.y * b.z - b.y * a.z;
	c.y = a.x * b.z - b.x * a.z;
	c.z = a.x * b.y - b.x * a.y;
	return c;
}

mat4 lookAt(vec3 from, vec3 to) {
	vec3 globalUp = { 0.0f,0.0f,1.0f };
	vec3 f = { to.x - from.x,to.y - from.y,to.z - from.z };
	vec3 r = normalize(cross(f, globalUp));
	vec3 u = normalize(cross(r, f));
	mat4 view;
	view.m[0] = r.x;
	view.m[1] = u.x;
	view.m[2] = -f.x;
	view.m[3] = 0.0f;

	view.m[4] = r.y;
	view.m[5] = u.y;
	view.m[6] = -f.y;
	view.m[7] = 0.0f;

	view.m[8] = r.z;
	view.m[9] = u.z;
	view.m[10] = -f.z;
	view.m[11] = 0.0f;

	view.m[12] = -dot(r, from);
	view.m[13] = -dot(u, from);
	view.m[14] = dot(f, from);
	view.m[15] = 1.0f;
	return view;
}

mat4 createProjection(float fovy, float aRatio, float n, float f) {
	mat4 matrix;
	float t = tanf(fovy * PI / 180.0f / 2.0f);
	for (int i = 0; i < 16; i++)
	{
		matrix.m[i] = 0;
	}
	matrix.m[0] = 1.0f / (aRatio * t);
	matrix.m[5] = 1.0f / t;
	matrix.m[10] = (n + f) / (f - n);
	matrix.m[14] = 2.0f * f * n / (n - f);
	matrix.m[11] = 1.0f;
	return matrix;

}