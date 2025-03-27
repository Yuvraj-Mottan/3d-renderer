#include"Maths.h"

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


