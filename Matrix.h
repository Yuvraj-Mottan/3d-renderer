#pragma once
#include "vector.h"
#include <cstring>
#include <cmath>

class Mat4 {
public:
    float m[16];

    Mat4() {
        std::memset(m, 0, sizeof(m));
        m[0] = m[5] = m[10] = m[15] = 1.0f;
    }

    static Mat4 translate(const vec3& v) {
        Mat4 result;
        result.m[12] = v.x;
        result.m[13] = v.y;
        result.m[14] = v.z;
        return result;
    }

    static Mat4 perspective(float fov, float aspect, float near, float far) {
        Mat4 result;
        float tanHalfFov = tan(fov / 2.0f);
        result.m[0] = 1.0f / (aspect * tanHalfFov);
        result.m[5] = 1.0f / tanHalfFov;
        result.m[10] = -(far + near) / (far - near);
        result.m[11] = -1.0f;
        result.m[14] = -(2.0f * far * near) / (far - near);
        result.m[15] = 0.0f;
        return result;
    }

    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i + j * 4] =
                    m[i] * other.m[j * 4] +
                    m[i + 4] * other.m[j * 4 + 1] +
                    m[i + 8] * other.m[j * 4 + 2] +
                    m[i + 12] * other.m[j * 4 + 3];
            }
        }
        return result;
    }
};
