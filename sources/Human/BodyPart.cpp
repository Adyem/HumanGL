#include "../../includes/Human/BodyPart.hpp"

BodyPartRenderer::BodyPartRenderer(float r, float g, float b)
    : colorR(r), colorG(g), colorB(b), scaleX(1.0f), scaleY(1.0f), scaleZ(1.0f) {
}

void BodyPartRenderer::setColor(float r, float g, float b) {
    colorR = r;
    colorG = g;
    colorB = b;
}

void BodyPartRenderer::setScale(float sX, float sY, float sZ) {
    scaleX = sX;
    scaleY = sY;
    scaleZ = sZ;
}

void BodyPartRenderer::drawColoredCubeWithMatrix(float r, float g, float b, const MatrixStack& matrixStack) {
    // Get the transformation matrix
    const float* matrix = matrixStack.getCurrentMatrixData();

    // Set color
    glColor3f(r, g, b);

    // Define the 8 vertices of a unit cube (1x1x1 centered at origin) using proper defines
    float vertices[8][3] = {
        {HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_NEGATIVE_HALF}, // 0: left-bottom-back
        {HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_NEGATIVE_HALF}, // 1: right-bottom-back
        {HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_NEGATIVE_HALF}, // 2: right-top-back
        {HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_NEGATIVE_HALF}, // 3: left-top-back
        {HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_HALF_SIZE},     // 4: left-bottom-front
        {HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_HALF_SIZE},     // 5: right-bottom-front
        {HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_HALF_SIZE},     // 6: right-top-front
        {HUMANGL_CUBE_NEGATIVE_HALF, HUMANGL_CUBE_HALF_SIZE,     HUMANGL_CUBE_HALF_SIZE}      // 7: left-top-front
    };

    // Transform all vertices using our custom matrix
    float transformedVertices[8][3];
    for (int i = 0; i < 8; i++) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        float z = vertices[i][2];

        // Apply matrix transformation (matrix is in column-major order)
        transformedVertices[i][0] = matrix[0]*x + matrix[4]*y + matrix[8]*z  + matrix[12]; // X
        transformedVertices[i][1] = matrix[1]*x + matrix[5]*y + matrix[9]*z  + matrix[13]; // Y
        transformedVertices[i][2] = matrix[2]*x + matrix[6]*y + matrix[10]*z + matrix[14]; // Z
    }

    // Render the cube faces using transformed vertices
    glBegin(GL_QUADS);

    // Front face (4, 5, 6, 7)
    glVertex3f(transformedVertices[4][0], transformedVertices[4][1], transformedVertices[4][2]);
    glVertex3f(transformedVertices[5][0], transformedVertices[5][1], transformedVertices[5][2]);
    glVertex3f(transformedVertices[6][0], transformedVertices[6][1], transformedVertices[6][2]);
    glVertex3f(transformedVertices[7][0], transformedVertices[7][1], transformedVertices[7][2]);

    // Back face (1, 0, 3, 2)
    glVertex3f(transformedVertices[1][0], transformedVertices[1][1], transformedVertices[1][2]);
    glVertex3f(transformedVertices[0][0], transformedVertices[0][1], transformedVertices[0][2]);
    glVertex3f(transformedVertices[3][0], transformedVertices[3][1], transformedVertices[3][2]);
    glVertex3f(transformedVertices[2][0], transformedVertices[2][1], transformedVertices[2][2]);

    // Top face (3, 7, 6, 2)
    glVertex3f(transformedVertices[3][0], transformedVertices[3][1], transformedVertices[3][2]);
    glVertex3f(transformedVertices[7][0], transformedVertices[7][1], transformedVertices[7][2]);
    glVertex3f(transformedVertices[6][0], transformedVertices[6][1], transformedVertices[6][2]);
    glVertex3f(transformedVertices[2][0], transformedVertices[2][1], transformedVertices[2][2]);

    // Bottom face (0, 1, 5, 4)
    glVertex3f(transformedVertices[0][0], transformedVertices[0][1], transformedVertices[0][2]);
    glVertex3f(transformedVertices[1][0], transformedVertices[1][1], transformedVertices[1][2]);
    glVertex3f(transformedVertices[5][0], transformedVertices[5][1], transformedVertices[5][2]);
    glVertex3f(transformedVertices[4][0], transformedVertices[4][1], transformedVertices[4][2]);

    // Right face (1, 2, 6, 5)
    glVertex3f(transformedVertices[1][0], transformedVertices[1][1], transformedVertices[1][2]);
    glVertex3f(transformedVertices[2][0], transformedVertices[2][1], transformedVertices[2][2]);
    glVertex3f(transformedVertices[6][0], transformedVertices[6][1], transformedVertices[6][2]);
    glVertex3f(transformedVertices[5][0], transformedVertices[5][1], transformedVertices[5][2]);

    // Left face (0, 4, 7, 3)
    glVertex3f(transformedVertices[0][0], transformedVertices[0][1], transformedVertices[0][2]);
    glVertex3f(transformedVertices[4][0], transformedVertices[4][1], transformedVertices[4][2]);
    glVertex3f(transformedVertices[7][0], transformedVertices[7][1], transformedVertices[7][2]);
    glVertex3f(transformedVertices[3][0], transformedVertices[3][1], transformedVertices[3][2]);

    glEnd();
}
