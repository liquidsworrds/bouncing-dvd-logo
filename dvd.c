#include "raylib.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define LOGO_WIDTH 200
#define LOGO_HEIGHT 100

#define LOGO_VELOCITY_X 200
#define LOGO_VELOCITY_Y 200

typedef struct DVDLogo {
  Rectangle srcRect;
  Rectangle dstRect;
  Vector2 originCoords;
  Vector2 velocity;
  Color dvdColor;
} DVDLogo;

Texture InitDVDLogoTexture(const char *path) {
  Image image = LoadImage(path);
  Texture texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return texture;
}

DVDLogo InitDVDLogo(Texture texture) {

  DVDLogo dvdLogo = {
      .srcRect =
          (Rectangle){
              .x = 0,
              .y = 0,
              .width = texture.width,
              .height = texture.height,
          },

      .dstRect =
          (Rectangle){
              .x = GetRandomValue(LOGO_WIDTH, SCREEN_WIDTH - LOGO_WIDTH),
              .y = GetRandomValue(LOGO_HEIGHT, SCREEN_HEIGHT - LOGO_HEIGHT),
              .width = LOGO_WIDTH,
              .height = LOGO_HEIGHT,
          },

      .originCoords =
          (Vector2){
              .x = 0,
              .y = 0,
          },

      .velocity =
          (Vector2){
              .x = LOGO_VELOCITY_X,
              .y = LOGO_VELOCITY_Y,
          },

      .dvdColor = WHITE,

  };

  return dvdLogo;
}

void ChangeDVDColor(DVDLogo *dvdLogo) {
  dvdLogo->dvdColor = (Color){
      .r = GetRandomValue(100, 255),
      .g = GetRandomValue(100, 255),
      .b = GetRandomValue(100, 255),
      .a = 255,
  };
}

void HorizontalCollision(DVDLogo *dvdLogo) {
  // Horizontal Collision Detection
  if (dvdLogo->dstRect.x >= SCREEN_WIDTH - dvdLogo->dstRect.width) {
    dvdLogo->dstRect.x = SCREEN_WIDTH - dvdLogo->dstRect.width;
    dvdLogo->velocity.x *= -1;
    ChangeDVDColor(dvdLogo);
  } else if (dvdLogo->dstRect.x <= 0) {
    dvdLogo->dstRect.x = 0;
    dvdLogo->velocity.x *= -1;
    ChangeDVDColor(dvdLogo);
  }
}

void VerticalCollison(DVDLogo *dvdLogo) {
  // Vertical Collision Detection
  if (dvdLogo->dstRect.y >= (SCREEN_HEIGHT - dvdLogo->dstRect.height)) {
    dvdLogo->dstRect.y = SCREEN_HEIGHT - dvdLogo->dstRect.height;
    ChangeDVDColor(dvdLogo);
    dvdLogo->velocity.y *= -1;
  } else if (dvdLogo->dstRect.y <= 0) {
    dvdLogo->dstRect.y = 0;
    ChangeDVDColor(dvdLogo);
    dvdLogo->velocity.y *= -1;
  }
}

void UpdateDVDLogo(DVDLogo *dvdLogo) {
  float dt = GetFrameTime();

  dvdLogo->dstRect.x += dvdLogo->velocity.x * dt;
  dvdLogo->dstRect.y += dvdLogo->velocity.y * dt;

  HorizontalCollision(dvdLogo);
  VerticalCollison(dvdLogo);
}

int main(int argc, char *argv[]) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DVD LOGO");

  Texture texture = InitDVDLogoTexture("./DVD_VIDEO_logo.png");

  int logoCount = 10;

  DVDLogo dvdLogos[logoCount];

  for (int i = 0; i < logoCount; i++) {
     dvdLogos[i] = InitDVDLogo(texture);
  }

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

      BeginDrawing();

        ClearBackground(BLACK);

      for (int i = 0; i < logoCount; i++){

        UpdateDVDLogo(&dvdLogos[i]);

        DrawTexturePro(texture, dvdLogos[i].srcRect, dvdLogos[i].dstRect,
                      dvdLogos[i].originCoords, 0, dvdLogos[i].dvdColor);

        DrawFPS(10, 10);
      }

      EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
  return 0;
}
