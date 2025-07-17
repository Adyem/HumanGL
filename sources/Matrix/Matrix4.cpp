#include "../../includes/Matrix/Matrix4.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Matrix4::Matrix4() {
    loadIdentity();
}

void Matrix4::loadIdentity() {
    for (int i = 0; i < HUMANGL_MATRIX_SIZE; i++) {
        m[i] = (i % HUMANGL_MATRIX_IDENTITY_STEP == 0) ? HUMANGL_OPENGL_AXIS_Y : HUMANGL_OPENGL_AXIS_NONE;
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
    float rad = DEGREES_TO_RADIANS(angle);
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
    float rad = DEGREES_TO_RADIANS(angle);
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
    float rad = DEGREES_TO_RADIANS(angle);
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
    for (int i = 0; i < HUMANGL_MATRIX_DIMENSION; i++) {
        for (int j = 0; j < HUMANGL_MATRIX_DIMENSION; j++) {
            result.m[i * HUMANGL_MATRIX_DIMENSION + j] = HUMANGL_OPENGL_AXIS_NONE;
            for (int k = 0; k < HUMANGL_MATRIX_DIMENSION; k++) {
                result.m[i * HUMANGL_MATRIX_DIMENSION + j] += m[i * HUMANGL_MATRIX_DIMENSION + k] * other.m[k * HUMANGL_MATRIX_DIMENSION + j];
            }
        }
    }
    return result;
}

void Matrix4::applyToOpenGL() const {
    glMultMatrixf(m);
}
