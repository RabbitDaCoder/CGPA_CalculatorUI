#include "include/raylib.h"
#include "stdio.h"
#include "stdlib.h"

// Define Clay implementation before including (ONLY in ONE source file)
#define CLAY_IMPLEMENTATION
#include "include/clay.h"

typedef struct {
    const char *appName;
    int instanceId;
} MyAppContext;

void MyErrorHandler(Clay_ErrorData err) {
    // cast back to pointer - now userData is already a void*
    MyAppContext *ctx = (MyAppContext*)(err.userData);

    if (ctx) {
        printf("[%s #%d] Clay Error: %s\n",
               ctx->appName, ctx->instanceId, err.errorText.chars);
    } else {
        printf("Clay Error: %s\n", err.errorText.chars);
    }

    switch (err.errorType) {
        case CLAY_ERROR_TYPE_DUPLICATE_ID:
            printf("Duplicate ID error occurred.\n");
            break;
        case CLAY_ERROR_TYPE_ARENA_CAPACITY_EXCEEDED:
            printf("Arena too small, increase memory.\n");
            break;
        default:
            printf("Other error.\n");
    }
}

const float ScreenWidth = 1400.0f;
const float ScreenHeight = 792.0f;

int main() {
    MyAppContext ctx = { "CGPA Calculator", 1 };

    // Init RayLib
    InitWindow((int) ScreenWidth, (int) ScreenHeight, "CGPA Calculator In C UI");

    // Init Clay
    int64_t clayMemorySize = Clay_MinMemorySize();
    Clay_Arena memoryArena = {
        .memory = malloc(clayMemorySize),
        .capacity = clayMemorySize
    };

    Clay_Dimensions dimensions = {
        .width = ScreenWidth,
        .height = ScreenHeight
    };

    Clay_ErrorHandler error = {
        .errorHandlerFunction = MyErrorHandler,
        .userData = (void*)&ctx   // Direct cast to void* instead of intptr_t
    };

    Clay_Initialize(memoryArena, dimensions, error);

    // Set target FPS
    SetTargetFPS(144);

    // Main Application Loop
    while (!WindowShouldClose()) {
        // Logic Code
        BeginDrawing();
        ClearBackground(YELLOW);

        // Rendered Stuff
        // Clay UI usage will go here

        DrawText("Clay UI is loaded!", 250, 300, 20, BLACK);

        EndDrawing();
    }

    // Cleanup
    free(memoryArena.memory);
    CloseWindow();
    return 0;
}