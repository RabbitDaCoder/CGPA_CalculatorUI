#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>

// Define Clay implementation ONLY in main.c
#define CLAY_IMPLEMENTATION
#include "include/clay.h"
#include "app.h"

// Error handler
void MyErrorHandler(Clay_ErrorData err) {
    printf("Clay Error: %s\n", err.errorText.chars);

    switch (err.errorType) {
        case CLAY_ERROR_TYPE_DUPLICATE_ID:
            printf("Duplicate ID error.\n");
            break;
        case CLAY_ERROR_TYPE_ARENA_CAPACITY_EXCEEDED:
            printf("Arena too small.\n");
            break;
        default:
            printf("Other error.\n");
    }
}

int main() {
    const int screenWidth = 1400;
    const int screenHeight = 792;

    // Initialize Raylib
    InitWindow(screenWidth, screenHeight, "CGPA Calculator - Clay UI Test");

    // Initialize Clay
    uint64_t clayMemorySize = Clay_MinMemorySize();
    Clay_Arena memoryArena = {
        .memory = malloc(clayMemorySize),
        .capacity = clayMemorySize
    };

    Clay_Dimensions dimensions = {screenWidth, screenHeight};
    Clay_ErrorHandler errorHandler = {
        .errorHandlerFunction = MyErrorHandler,
        .userData = NULL
    };

    Clay_Initialize(memoryArena, dimensions, errorHandler);

    // Load fonts
    Font fonts[2];
    fonts[FONT_ID_BODY_24] = GetFontDefault();
    fonts[FONT_ID_BODY_16] = GetFontDefault();
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose()) {
        UpdateDrawFrame(fonts);
    }

    // Cleanup
    free(memoryArena.memory);
    CloseWindow();
    return 0;
}