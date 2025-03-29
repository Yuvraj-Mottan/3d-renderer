#pragma once
struct mat4 {
	float m[16];
};
struct vec3 {
	float x, y, z;
};
mat4 createMatrixTransform(vec3 translation);
mat4 createZrotation(float angle);
mat4 createModelMatrix(vec3 translation, float angle);

float dot(vec3 a, vec3 b);
vec3 normalize(vec3 a);
vec3 cross(vec3 a, vec3 b);
mat4 lookAt(vec3 from, vec3 to);

mat4 createProjection(float fovy, float aRatio, float n, float f);