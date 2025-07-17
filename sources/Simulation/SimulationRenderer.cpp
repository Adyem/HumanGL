#include "../../includes/Simulation/SimulationRenderer.hpp"

SimulationRenderer::SimulationRenderer(MatrixStack& stack, DrawPerson& person, KeyboardHandler& kbHandler, int winWidth, int winHeight)
    : matrixStack(stack), drawPerson(person), keyboardHandler(kbHandler),
      nearPlane(1.0f), farPlane(100.0f), fov(45.0f),
      windowWidth(winWidth), windowHeight(winHeight) {
}

void SimulationRenderer::render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup the scene
    setupPerspective();
    setupLighting();
    setupScene();
    
    // Build view matrix from camera parameters
    Matrix4 view = keyboardHandler.getViewMatrix();
    matrixStack.setViewMatrix(view);
    matrixStack.loadIdentity();

    // Render the person
    drawPerson.render(matrixStack);
}

void SimulationRenderer::setupPerspective() {
    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Calculate aspect ratio
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    
    // Manual perspective calculation to avoid gluPerspective
    float top = nearPlane * tanf(fov * static_cast<float>(M_PI) / 360.0f);
    float bottom = -top;
    float right = top * aspectRatio;
    float left = -right;
    
    glFrustum(left, right, bottom, top, nearPlane, farPlane);
    
    // Switch to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SimulationRenderer::setupLighting() {
    // Disable lighting to ensure colors show properly (like the original working version)
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    // Enable color material for proper color rendering
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void SimulationRenderer::setupScene() {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Set background color (dark blue)
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    
    // Enable smooth shading
    glShadeModel(GL_SMOOTH);
    
    // Set viewport
    glViewport(0, 0, windowWidth, windowHeight);
}

void SimulationRenderer::updateWindowSize(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    // Update viewport
    glViewport(0, 0, windowWidth, windowHeight);
}
