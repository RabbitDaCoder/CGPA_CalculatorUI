/**
 * Simple Clay Test - To verify Clay macros are working
 */

#include "app.h"

// =============================================================================
// GLOBAL STATE
// =============================================================================
const uint32_t FONT_ID_BODY_24 = 0;
const uint32_t FONT_ID_BODY_16 = 1;

// Define color constants
const Clay_Color COLOR_LIGHT = (Clay_Color) {244, 235, 230, 255};



CGPAState appState = {
    .courseCount = 0,
    .currentCGPA = 0.0f,
    .showResults = false,
    .inputCourseName = {0},
    .inputGradeScore = "A",
    .inputUnitLoad = "3"
};

// =============================================================================
// TEXT MEASUREMENT
// =============================================================================
Clay_Dimensions Raylib_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *userData) {
    if (!text.chars || text.length == 0 || !config) {
        return (Clay_Dimensions){0, 0};
    }

    Font* fonts = (Font*)userData;
    Font font = (fonts && fonts[config->fontId].glyphs) ? fonts[config->fontId] : GetFontDefault();

    // Simple text measurement
    Vector2 textSize = MeasureTextEx(font, "Test", config->fontSize, config->letterSpacing);
    return (Clay_Dimensions){textSize.x, textSize.y};
}

// =============================================================================
// SIMPLE LAYOUT TEST
// =============================================================================
Clay_RenderCommandArray CreateLayout(void) {
    Clay_BeginLayout();

    // Test simple Clay layout
    CLAY(CLAY_ID("TestContainer"), {
        .layout = {
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)},
            .padding = {20, 20, 20, 20},
            .childGap = 20
        },
        .backgroundColor = COLOR_LIGHT
    }) {
        // Header
        CLAY(CLAY_ID("Header"), {
            .layout = {
                .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(80)},
                .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER},
                .padding = {16, 16, 16, 16}
            },
            .backgroundColor = COLOR_BLUE,
            .cornerRadius = CLAY_CORNER_RADIUS(8)
        }) {
            CLAY_TEXT(CLAY_STRING("Clay Test - Working!"), CLAY_TEXT_CONFIG({
                .fontSize = 24,
                .textColor = COLOR_LIGHT,
                .fontId = FONT_ID_BODY_24
            }));
        }

        // Simple button test
        CLAY(CLAY_ID("TestButton"), {
            .layout = {
                .sizing = {CLAY_SIZING_FIXED(200), CLAY_SIZING_FIXED(50)},
                .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER}
            },
            .backgroundColor = Clay_Hovered() ? COLOR_ORANGE : COLOR_BLUE,
            .cornerRadius = CLAY_CORNER_RADIUS(6)
        }) {
            CLAY_TEXT(CLAY_STRING("Test Button"), CLAY_TEXT_CONFIG({
                .fontSize = 16,
                .textColor = COLOR_LIGHT,
                .fontId = FONT_ID_BODY_16
            }));
        }
    }

    return Clay_EndLayout();
}
// =============================================================================
// STUB FUNCTIONS
// =============================================================================
float GradeToPoints(const char* grade) {
    return 4.0f; // Stub
}

void CalculateCGPA(void) {
    // Stub
}

void HandleButtonClick(void) {
    printf("Button clicked!\n");
}

void UpdateDrawFrame(Font* fonts) {
    if (!fonts) return;

    // Update Clay input
    Clay_SetPointerState(
        (Clay_Vector2){GetMousePosition().x, GetMousePosition().y},
        IsMouseButtonDown(MOUSE_BUTTON_LEFT)
    );

    Clay_SetLayoutDimensions(
        (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()}
    );

    // Handle clicks
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        HandleButtonClick();
    }

    // Create and render layout
    Clay_RenderCommandArray renderCommands = CreateLayout();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    Clay_Raylib_Render(renderCommands, fonts);
    EndDrawing();
}