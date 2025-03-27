#pragma once
struct mat4 {
	float m[16];
};
struct vec3 {
	float x, y, z;
};
mat4 createMatrixTransform(mat4 matrix,vec3 translation);
