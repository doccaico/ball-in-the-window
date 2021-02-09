#include <stdio.h>

#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


#define  screenWidth    800
#define  screenHeight   450
#define  ballDiameter   30
#define  skipFramerate  15

const char *top    = "top";
const char *bottom = "bottom";
const char *left   = "left";
const char *right  = "right";

typedef enum {
  topLeft,
  topRight,
  bottomLeft,
  bottomRight,
}Direction;

typedef struct  {
  Vector2   pos;
  Direction direction;
  float     speed;
}Ball;

char        collisionMsg[24];
char        speedInfo[16];
const char *label     = NULL;
int         inputWait = 0;

Ball ball = {
  (Vector2){screenWidth / 2, screenHeight / 2},
  bottomLeft,
  3.0
};

void drawInfo(void) {
  DrawText("speed up: arrow up", 10, 10, 20, DARKGRAY);
  DrawText("speed down: arrow down", 10, 30, 20, DARKGRAY);

  // lable
  if (!label) {
    DrawText("collision: ", 10, 90, 20, DARKGRAY);
  } else {
    int len = sprintf(collisionMsg, "collision: %s", label);
    collisionMsg[len] = '\0';
    DrawText(collisionMsg, 10, 90, 20, DARKGRAY);
  }

  // speed
  int len = sprintf(speedInfo, "speed: %.1f", ball.speed);

  collisionMsg[len] = '\0';
  DrawText(speedInfo, 10, 70, 20, DARKGRAY);
}

void UpdateDrawFrame(void) {
  // speed [1-6]
  if (inputWait == 0) {
    if (IsKeyDown(KEY_UP)) {
      if (ball.speed != 6.0) {
        ball.speed += 1.0;
        inputWait   = skipFramerate;
      }
    }
    if (IsKeyDown(KEY_DOWN)) {
      if (ball.speed != 1.0) {
        ball.speed -= 1.0;
        inputWait   = skipFramerate;
      }
    }
  }

  if (inputWait > 0) {
    inputWait -= 1;
  }

  // direction
  if (ball.direction == topLeft) {
    ball.pos.x -= ball.speed;
    ball.pos.y -= ball.speed;
  }
  if (ball.direction == topRight) {
    ball.pos.x += ball.speed;
    ball.pos.y -= ball.speed;
  }
  if (ball.direction == bottomLeft) {
    ball.pos.x -= ball.speed;
    ball.pos.y += ball.speed;
  }
  if (ball.direction == bottomRight) {
    ball.pos.x += ball.speed;
    ball.pos.y += ball.speed;
  }


  BeginDrawing();
  ClearBackground(RAYWHITE);

  // top collision
  if (ball.pos.y - ballDiameter <= 0) {
    if (ball.direction == topLeft) {
      ball.direction = bottomLeft;
    } else if (ball.direction == topRight) {
      ball.direction = bottomRight;
    }
    label = top;
  }
  // bottom collision
  else if (ball.pos.y + ballDiameter >= screenHeight) {
    if (ball.direction == bottomLeft) {
      ball.direction = topLeft;
    } else if (ball.direction == bottomRight) {
      ball.direction = topRight;
    }
    label = bottom;
  }
  // left collision
  else if (ball.pos.x - ballDiameter <= 0) {
    if (ball.direction == bottomLeft) {
      ball.direction = bottomRight;
    } else if (ball.direction == topLeft) {
      ball.direction = topRight;
    }
    label = left;
  }
  // right collision
  else if (ball.pos.x + ballDiameter >= screenWidth) {
    if (ball.direction == bottomRight) {
      ball.direction = bottomLeft;
    } else if (ball.direction == topRight) {
      ball.direction = topLeft;
    }
    label = right;
  }

  drawInfo();
  DrawCircleV(ball.pos, ballDiameter, MAROON);

  EndDrawing();
}

int main(void) {
  InitWindow(screenWidth, screenHeight, "ball in the window");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();

  return (0);
}
