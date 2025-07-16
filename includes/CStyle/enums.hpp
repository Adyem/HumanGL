#pragma once

// ============================================================================
// CORE APPLICATION ENUMS
// ============================================================================

// Application state enumeration
enum AppState {
    MAIN_MENU,
    SIMULATION,
    SETTINGS,
    CREDITS,
    INSTRUCTIONS
};

// Menu action enumeration
enum MenuAction {
    MENU_ACTION_NONE,
    MENU_ACTION_START_SIMULATION,
    MENU_ACTION_SETTINGS,
    MENU_ACTION_CREDITS,
    MENU_ACTION_INSTRUCTIONS,
    MENU_ACTION_EXIT,
    MENU_ACTION_BACK_TO_MENU,
    MENU_ACTION_RETURN_TO_MENU
};

// ============================================================================
// ANIMATION ENUMS
// ============================================================================

// Animation mode enumeration
enum AnimationMode {
    NONE,
    WALKING,
    JUMPING,
    DANCING,
    KUNGFU
};

// ============================================================================
// MENU SYSTEM ENUMS
// ============================================================================

// Menu state enumeration (for menu system internal use)
enum MenuState {
    MAIN_MENU_STATE,
    SETTINGS_STATE,
    CREDITS_STATE,
    INSTRUCTIONS_STATE,
    SIMULATION_STATE
};

// Settings page enumeration (from MenuSystem)
enum SettingsPage {
    SETTINGS_MAIN,
    BODY_CUSTOMIZATION,
    RESOLUTION_SETTINGS
};

// ============================================================================
// BODY PART AND ANIMATION ENUMS
// ============================================================================

// Body part enumeration (for customization and animation)
enum BodyPart {
    BODY_PART_HEAD,
    BODY_PART_TORSO,
    BODY_PART_LEFT_ARM,
    BODY_PART_RIGHT_ARM,
    BODY_PART_LEFT_LEG,
    BODY_PART_RIGHT_LEG,
    BODY_PART_NECK,
    BODY_PART_LEFT_SHOULDER,
    BODY_PART_RIGHT_SHOULDER,
    BODY_PART_LEFT_UPPER_ARM,
    BODY_PART_LEFT_FOREARM,
    BODY_PART_RIGHT_UPPER_ARM,
    BODY_PART_RIGHT_FOREARM,
    BODY_PART_LEFT_THIGH,
    BODY_PART_LEFT_LOWER_LEG,
    BODY_PART_RIGHT_THIGH,
    BODY_PART_RIGHT_LOWER_LEG,
    BODY_PART_EYES,
    BODY_PART_COUNT  // Keep this last for counting
};

// ============================================================================
// INPUT AND INTERACTION ENUMS
// ============================================================================

// Input key enumeration (for keyboard handling)
enum InputKey {
    INPUT_KEY_NONE,
    INPUT_KEY_ESCAPE,
    INPUT_KEY_SPACE,
    INPUT_KEY_RETURN,
    INPUT_KEY_W, INPUT_KEY_A, INPUT_KEY_S, INPUT_KEY_D,
    INPUT_KEY_Q, INPUT_KEY_E,
    INPUT_KEY_P, INPUT_KEY_J, INPUT_KEY_K, INPUT_KEY_M,
    INPUT_KEY_1, INPUT_KEY_2, INPUT_KEY_3,
    INPUT_KEY_4, INPUT_KEY_5, INPUT_KEY_6,
    INPUT_KEY_7, INPUT_KEY_8, INPUT_KEY_9, INPUT_KEY_0
};

// Mouse button enumeration
enum MouseButton {
    MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE
};

// ============================================================================
// RENDERING AND GRAPHICS ENUMS
// ============================================================================

// Rendering mode enumeration (for future expansion)
enum RenderMode {
    RENDER_MODE_WIREFRAME,
    RENDER_MODE_SOLID,
    RENDER_MODE_TEXTURED
};

// Quality settings enumeration
enum QualityLevel {
    QUALITY_LOW,
    QUALITY_MEDIUM,
    QUALITY_HIGH,
    QUALITY_ULTRA
};
