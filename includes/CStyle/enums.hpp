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
    MENU_ACTION_RETURN_TO_MENU,
    MENU_ACTION_BODY_CUSTOMIZATION,
    MENU_ACTION_BACKGROUND_CUSTOMIZATION,
    MENU_ACTION_BODY_PART_DETAIL
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

// Settings page enumeration (from MenuSystem)
enum SettingsPage {
    SETTINGS_MAIN,
    BODY_CUSTOMIZATION,
    BODY_PART_DETAIL,
    BACKGROUND_CUSTOMIZATION,
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




