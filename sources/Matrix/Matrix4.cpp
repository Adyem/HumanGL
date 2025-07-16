#include "../../includes/Matrix/Matrix4.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Matrix4::Matrix4() {
    loadIdentity();
}

void Matrix4::loadIdentity() {
    for (int i = 0; i < 16; i++) {
        m[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
}

void Matrix4::translate(float x, float y, float z) {
    Matrix4 translation;
    translation.m[12] = x;
    translation.m[13] = y;
    translation.m[14] = z;
    *this = *this * translation;
}

void Matrix4::rotateX(float angle) {
    float rad = angle * M_PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);
    
    Matrix4 rotation;
    rotation.m[5] = c;
    rotation.m[6] = s;
    rotation.m[9] = -s;
    rotation.m[10] = c;
    
    *this = *this * rotation;
}

void Matrix4::rotateY(float angle) {
    float rad = angle * M_PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);
    
    Matrix4 rotation;
    rotation.m[0] = c;
    rotation.m[2] = -s;
    rotation.m[8] = s;
    rotation.m[10] = c;
    
    *this = *this * rotation;
}

void Matrix4::rotateZ(float angle) {
    float rad = angle * M_PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);
    
    Matrix4 rotation;
    rotation.m[0] = c;
    rotation.m[1] = s;
    rotation.m[4] = -s;
    rotation.m[5] = c;
    
    *this = *this * rotation;
}

void Matrix4::scale(float x, float y, float z) {
    Matrix4 scaling;
    scaling.m[0] = x;
    scaling.m[5] = y;
    scaling.m[10] = z;
    *this = *this * scaling;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i * 4 + j] += m[i * 4 + k] * other.m[k * 4 + j];
            }
        }
    }
    return result;
}

void Matrix4::applyToOpenGL() const {
    glMultMatrixf(m);
}
