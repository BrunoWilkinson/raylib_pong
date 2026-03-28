#include "raylib.h"

// --------------------------------------------------
// Types and definitions
// --------------------------------------------------

typedef enum GameScreen {
  LOGO,
  TITLE,
  GAMEPLAY,
  ENDING
} GameScreen;

// TODO: Define required structs

// --------------------------------------------------
// Program main entry point
// --------------------------------------------------
int main(void)
{
  // Initializaton
  // --------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "PROJECT: PONG");

  // TODO: load resources (textures, font, audio) after Window initialization

  GameScreen screen = LOGO; // Current game state

  int framesCounter = 0; // General purpose frames counter
  int gameResult = -1;  // Game result: 0 - Loose, 1 - Win, -1 - Not Defined
  bool gamePaused = false; // Game pause toggle state

  // TODO: Define and Initialize game variables

  SetTargetFPS(60); // Set Desired framerate (frames per seconds)
  // --------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    // --------------------------------------------------
    switch(screen)
    {
      case LOGO:
        {
          // Update LOGO screen data here!

          framesCounter++;
          if (framesCounter > 180)
          {
            screen = TITLE; // Change to TITLE screen after 3 seconds
            framesCounter = 0;
          }
        } break;
      case TITLE:
        {
          // Update TITLE screen data here!

          framesCounter++;
          // LESSON03: Inputs management (keyboard, mouse)
          if (IsKeyPressed(KEY_ENTER))
          {
            screen = GAMEPLAY;
          }
        } break;
      case GAMEPLAY:
        {
          // Update GAMEPLAY screen data here!

          if (!gamePaused)
          {
            // TODO: Gameplay Logic
          }

          // LESSON03: Inputs management (keyboard, mouse)
          if (IsKeyPressed(KEY_ENTER))
          {
            screen = ENDING;
          }
        } break;
      case ENDING:
        {
          // Update ENDING screen data here!

          framesCounter++;
          // LESSON03: Inputs management (keyboard, mouse)
          if (IsKeyPressed(KEY_ENTER))
          {
            screen = TITLE;
          }
        } break;
      default: break;
    }
    // --------------------------------------------------

    // Draw
    // --------------------------------------------------
    BeginDrawing();
      ClearBackground(RAYWHITE);
      switch(screen)
      {
        case LOGO:
        {
          // TODO: Draw LOGO screen here!
          DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
          DrawText("WAIT for 3 seconds...", 290, 220, 20, GRAY);
        } break;
        case TITLE:
        {
          // TODO: Draw TITLE screen here!
          DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
          DrawText("TITLE", 20, 20, 40, DARKGREEN);
          DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
        } break;
        case GAMEPLAY:
        {
          // TODO: Draw GAMEPLAY screen here!
          DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
          DrawText("GAMEPLAY", 20, 20, 40, MAROON);
          DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 120, 220, 20, MAROON);
        } break;
        case ENDING:
        {
          // TODO: Draw ENDING screen here!
          DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
          DrawText("ENDING", 20, 20, 40, DARKBLUE);
          DrawText("Press Enter or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
        } break;
        default: break;
      }
    EndDrawing();
    // --------------------------------------------------
  }

  // De-Initialization
  // --------------------------------------------------

  // NOTE: Unload any loaded resources (texture, fonts, audio)

  CloseWindow(); // Close window and OpenGL context
  // --------------------------------------------------

  return 0;
}
