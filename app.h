#ifndef APP_H
#define APP_H

// =============================================================================
// INCLUDES
// =============================================================================
#include "include/clay.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// =============================================================================
// CONSTANTS
// =============================================================================
#define MAX_COURSES 10

// Font IDs
extern const uint32_t FONT_ID_BODY_24;
extern const uint32_t FONT_ID_BODY_16;

// =============================================================================
// COLOR DEFINITIONS
// =============================================================================
#define COLOR_BLUE (Clay_Color) {70, 130, 180, 255}
#define COLOR_GREEN (Clay_Color) {46, 204, 113, 255}
#define COLOR_RED (Clay_Color) {231, 76, 60, 255}
#define COLOR_ORANGE (Clay_Color) {241, 196, 15, 255}
#define COLOR_LIGHT_GRAY (Clay_Color) {245, 245, 250, 255}
#define COLOR_WHITE (Clay_Color) {255, 255, 255, 255}
#define COLOR_BORDER (Clay_Color) {220, 220, 220, 255}

// =============================================================================
// DATA STRUCTURES
// =============================================================================

// Course data structure
typedef struct {
    char courseName[50];
    char gradeScore[10];
    int unitLoad;
    bool hasData;
} CourseData;

// Application state
typedef struct {
    CourseData courses[MAX_COURSES];
    int courseCount;
    float currentCGPA;
    bool showResults;
    char inputCourseName[50];
    char inputGradeScore[10];
    char inputUnitLoad[10];
} CGPAState;

// =============================================================================
// GLOBAL STATE
// =============================================================================
extern CGPAState appState;

// =============================================================================
// FUNCTION DECLARATIONS
// =============================================================================

// Core functions
Clay_RenderCommandArray CreateLayout(void);
float GradeToPoints(const char* grade);
void CalculateCGPA(void);
void HandleButtonClick(void);
void UpdateDrawFrame(Font* fonts);

// Raylib text measurement function
Clay_Dimensions Raylib_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *userData);

// Clay Raylib Renderer
void Clay_Raylib_Render(Clay_RenderCommandArray renderCommands, Font* fonts);

#endif // APP_H