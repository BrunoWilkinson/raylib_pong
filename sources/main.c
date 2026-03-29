#include "raylib.h"

// --------------------------------------------------
// Useful values definitions
// --------------------------------------------------
#define VICTORY_SCORE 10

// --------------------------------------------------
// Types and definitions
// --------------------------------------------------

typedef enum GameScreen {
  LOGO,
  TITLE,
  GAMEPLAY,
  ENDING
} GameScreen;

// Paddle structure
typedef struct Player {
  Vector2 position;
  Vector2 size;
  Vector2 speed;
  Rectangle bounds;
  int score;
} Player;

// Ball structure
typedef struct Ball {
  Vector2 position;
  Vector2 speed;
  float radius;
} Ball;

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

  // NOTE: Check defined structs on top
  Player player1 = { 0 };
  Player player2 = { 0 };
  Ball ball = { 0 };

  // Initialize players
  player1.size = (Vector2){ 24.0f, 100.0f };
  player1.position = (Vector2){ 20, (screenHeight / 2) - (player1.size.y / 2) };
  player1.speed = (Vector2){ 0.0f, 8.0f };

  player2.size = (Vector2){ 24.0f, 100.0f };
  player2.position = (Vector2){ screenWidth - (player2.size.x + 20), (screenHeight / 2) - (player2.size.y / 2) };
  player2.speed = (Vector2){ 0.0f, 8.0f };

  // Initialize ball
  ball.radius = 10.0f;
  ball.position = (Vector2){ screenWidth / 2 - (ball.radius + 10), screenHeight / 2 };
  ball.speed = (Vector2){ 4.0f, 4.0f };

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
          if ((framesCounter / 30) % 2 == 0)
          {
            const char *startText = "Press [ENTER] to START";
            const int startTextFontSize = 20;
            DrawText(startText, GetScreenWidth() / 2 - MeasureText(startText, startTextFontSize) / 2, 
                     GetScreenHeight() / 2 + 60, startTextFontSize, DARKGRAY);
          }
        } break;
        case GAMEPLAY:
        {
          // TODO: Draw GAMEPLAY screen here!

          DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2, RED);
          DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, RED);

          // LESSON 02: Draw basic shapes (circle, rectangle)
          DrawRectangle(player1.position.x, player1.position.y, player1.size.x, player1.size.y, BLACK);
          DrawRectangle(player2.position.x, player2.position.y, player2.size.x, player2.size.y, BLACK);
          DrawCircleV(ball.position, ball.radius, MAROON);

          // Draw Net
          for (int i = 0; i < screenHeight; i = i + 20)
          {
            DrawRectangle(screenWidth / 2 - 5, i, 10, 10, BLACK);
          }

          // Draw GUI
          const char *scoreText = "%02i";
          const int scoreTextFontSize = 50;

          const char *scoreTextPlayer1 = TextFormat(scoreText, player1.score);
          const char *scoreTextPlayer2 = TextFormat(scoreText, player2.score);
          DrawText(scoreTextPlayer1, (screenWidth / 2 - MeasureText(scoreTextPlayer1, scoreTextFontSize)) - 100, 
                   50, scoreTextFontSize, BLACK);
          DrawText(scoreTextPlayer2, screenWidth / 2 + 100, 50, scoreTextFontSize, BLACK);

          if (gamePaused)
          {
            const char *pauseText = "GAME PAUSED";
            const int pauseTextFontSize = 40;
            DrawText(pauseText, screenWidth / 2 - MeasureText(pauseText, pauseTextFontSize) / 2, 
                     screenHeight / 2 + 60, pauseTextFontSize, GRAY);
          }
        } break;
        case ENDING:
        {
          // TODO: Draw ENDING screen here!
          DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
          DrawText("ENDING", 20, 20, 40, DARKBLUE);
          DrawText("Press Enter or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
          if ((framesCounter / 30) % 2 == 0)
          {
            const char *startText = "Press [ENTER] to PLAY AGAIN";
            const int startTextFontSize = 20;
            DrawText(startText, GetScreenWidth() / 2 - MeasureText(startText, startTextFontSize) / 2, 
                     GetScreenHeight() / 2 + 60, startTextFontSize, DARKGRAY);
          }
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
