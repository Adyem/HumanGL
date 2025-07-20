#include "../../includes/Simulation/SimulationRenderer.hpp"
#include "../../includes/Menus/SettingsMenuRenderer.hpp"

SimulationRenderer::SimulationRenderer(DrawPerson& person, KeyboardHandler& kbHandler, int winWidth, int winHeight)
    : drawPerson(person), keyboardHandler(kbHandler), settingsRenderer(nullptr),
      nearPlane(HUMANGL_SIMULATION_NEAR_PLANE), farPlane(HUMANGL_SIMULATION_FAR_PLANE), fov(HUMANGL_SIMULATION_FOV),
      windowWidth(winWidth), windowHeight(winHeight) {
}

void SimulationRenderer::render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Setup the scene
    setupPerspective();
    setupLighting();
    setupScene();
    
    // Apply camera transformations
    keyboardHandler.applyCameraTransform();

    // Apply body part customizations before rendering
    applyBodyPartCustomizations();

    // Render the person using custom matrix stack
    drawPerson.render(matrixStack);
}

void SimulationRenderer::setupPerspective() {
    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Calculate aspect ratio
    float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    
    // Manual perspective calculation to avoid gluPerspective
    float top = nearPlane * tanf(DEGREES_TO_RADIANS(fov) / 2.0f);
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

    // Set background color from settings or use default
    if (settingsRenderer) {
        const Color& simBgColor = settingsRenderer->getSimulationBackgroundColor();
        glClearColor(simBgColor.r, simBgColor.g, simBgColor.b, simBgColor.a);
    } else {
        // Fallback to default
        glClearColor(HUMANGL_SIMULATION_BACKGROUND_R, HUMANGL_SIMULATION_BACKGROUND_G, HUMANGL_SIMULATION_BACKGROUND_B, HUMANGL_SIMULATION_BACKGROUND_A);
    }

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

void SimulationRenderer::setSettingsRenderer(SettingsMenuRenderer* renderer) {
    settingsRenderer = renderer;
}

void SimulationRenderer::applyBodyPartCustomizations() {
    if (settingsRenderer) {
        const std::map<BodyPart, BodyPartSettings>& settings = settingsRenderer->getAllBodyPartSettings();
        drawPerson.applyBodyPartSettings(settings);
    }
}
