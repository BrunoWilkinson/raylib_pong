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
  bool active;
} Ball;

// --------------------------------------------------
// Program main entry point
// --------------------------------------------------
int main(void)
{
  // Initializaton
  // --------------------------------------------------
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "PROJECT: PONG");

  // TODO: load resources (textures, font, audio) after Window initialization
  Texture2D texBall = LoadTexture(ASSETS_PATH"ball.png");

  GameScreen screen = LOGO; // Current game state

  int framesCounter = 0; // General purpose frames counter
  int ballFramesCounter = 0; // Frames counter for the ball
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
  ball.active = false;
  ball.position = (Vector2){ screenWidth / 2 - ball.radius, screenHeight / 2 };
  ball.speed = (Vector2){ 1.0f, 0 };

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
          if (IsKeyPressed('P'))
          {
            gamePaused = !gamePaused;
          }

          if (!gamePaused)
          {
            if (IsKeyDown(KEY_UP))
            {
              player1.position.y -= player1.speed.y;
            }
            if (IsKeyDown(KEY_DOWN))
            {
              player1.position.y += player1.speed.y;
            }

            if (player1.position.y <= 0)
            {
              player1.position.y = 0;
            }
            if (player1.position.y + player1.size.y >= screenHeight)
            {
              player1.position.y = screenHeight - player1.size.y;
            }
            player1.bounds = (Rectangle){ player1.position.x, player1.position.y, player1.size.x, player1.size.y };

            if (ball.active)
            {
              ballFramesCounter = 0;
              ball.position.x += ball.speed.x;
              ball.position.y += ball.speed.y;

              if ((ball.position.y + ball.radius) >= screenHeight || (ball.position.y - ball.radius) <= 0)
              {
                ball.speed.y *= -1;
              }
              if ((ball.position.x - ball.radius) <= 0)
              {
                ball.speed.x *= -1;
              }

              if (CheckCollisionCircleRec(ball.position, ball.radius, player1.bounds))
              {
                ball.speed.y = (ball.position.y - (player1.position.y + player1.size.y / 2)) / player1.size.y * 5.0f;
                ball.speed.x *= -1;
              }

              // Game ending logic
              if ((ball.position.x - ball.radius) <= 0 || (ball.position.x + ball.radius) >= screenWidth)
              {
                ball.speed = (Vector2){ 0, 0 };
                ball.active = false;

                if ((ball.position.x - ball.radius) <= 0)
                {
                  player2.score++;
                }
                else
                {
                  player1.score++;
                }
              }

              if (player1.score >= 10 || player2.score >= 10)
              {
                screen = ENDING;
                player1.score = 0;
                player2.score = 0;
                framesCounter = 0;
              }
            }
            else
            {
              ballFramesCounter++;

              // Reset ball position
              ball.position.x = screenWidth / 2 - ball.radius;
              ball.position.y = screenHeight / 2;

              if (ballFramesCounter > 90)
              {
                // Activated ball
                ball.active = true;
                ball.speed = (Vector2){ -4.0f, 0 };
              }
            }
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
          const char *waitText = "WAIT for 3 seconds...";
          const int waitTextFontSize = 20;
          DrawText(waitText, GetScreenWidth() / 2 - MeasureText(waitText, waitTextFontSize) / 2, 
                   GetScreenHeight() / 2 + 60, waitTextFontSize, GRAY);
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
          DrawTexture(texBall, ball.position.x - ball.radius / 2, ball.position.y - ball.radius / 2, WHITE);

          // Draw Net
          for (int i = 0; i < screenHeight; i = i + 20)
          {
            DrawRectangle(screenWidth / 2 - 5, i, 10, 10, BLACK);
          }

          // Draw GUI
          const char *scoreText = "%02i";
          const int scoreTextFontSize = 50;
          const int scoreTextSpacing = 100;

          const char *scoreTextPlayer1 = TextFormat(scoreText, player1.score);
          const char *scoreTextPlayer2 = TextFormat(scoreText, player2.score);
          DrawText(scoreTextPlayer1, screenWidth / 2 - MeasureText(scoreTextPlayer1, scoreTextFontSize) - scoreTextSpacing,
                   50, scoreTextFontSize, BLACK);
          DrawText(scoreTextPlayer2, screenWidth / 2 + scoreTextSpacing, 50, scoreTextFontSize, BLACK);

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
  UnloadTexture(texBall);

  CloseWindow(); // Close window and OpenGL context
  // --------------------------------------------------

  return 0;
}
