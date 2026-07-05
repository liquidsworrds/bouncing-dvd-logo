#include "raylib.h"

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

#define LOGO_WIDTH  200
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

Texture InitDVDLogoTexture() {
  Image image = LoadImage("./DVD_VIDEO_logo.png");
  Texture texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return texture;
}

DVDLogo InitDVDLogo(Texture texture) {

    DVDLogo dvdLogo;

    dvdLogo.srcRect = (Rectangle){
        .x = 0,
        .y = 0,
        .width = texture.width,
        .height = texture.height,
    };

    dvdLogo.dstRect = (Rectangle){
        .x = GetRandomValue(LOGO_WIDTH, SCREEN_WIDTH - LOGO_WIDTH),
        .y = GetRandomValue(LOGO_HEIGHT, SCREEN_HEIGHT - LOGO_HEIGHT),
        .width = LOGO_WIDTH,
        .height = LOGO_HEIGHT,
    };

    dvdLogo.originCoords = (Vector2){
        .x = 0,
        .y = 0,
    };

    dvdLogo.velocity = (Vector2) {
        .x = LOGO_VELOCITY_X,
        .y = LOGO_VELOCITY_Y,
    };

    dvdLogo.dvdColor = WHITE;

    return dvdLogo;
}

void ChangeDVDColor(DVDLogo *dvdLogo) {
  dvdLogo->dvdColor.r = GetRandomValue(100, 255);
  dvdLogo->dvdColor.g = GetRandomValue(100, 255);
  dvdLogo->dvdColor.b = GetRandomValue(100, 255);
  dvdLogo->dvdColor.a = 255;
}

void BounceBackDVD_X(DVDLogo *dvdLogo) {
    dvdLogo->velocity.x *= -1;
}

void BounceBackDVD_Y(DVDLogo *dvdLogo) {
    dvdLogo->velocity.y *= -1;
}

void UpdateDVDLogo(DVDLogo *dvdLogo) {
  float dt = GetFrameTime();

  dvdLogo->dstRect.x += dvdLogo->velocity.x * dt;
  dvdLogo->dstRect.y += dvdLogo->velocity.y * dt;

  // Horizontal Collision Detection
  if (dvdLogo->dstRect.x >= SCREEN_WIDTH - dvdLogo->dstRect.width) {
    ChangeDVDColor(dvdLogo);
    BounceBackDVD_X(dvdLogo);
  }

  if (dvdLogo->dstRect.x <= 0) {
    ChangeDVDColor(dvdLogo);
    BounceBackDVD_X(dvdLogo);
  }

  // Vertical Collision Detection
  if (dvdLogo->dstRect.y >= (SCREEN_HEIGHT - dvdLogo->dstRect.height)) {
    ChangeDVDColor(dvdLogo);
    BounceBackDVD_Y(dvdLogo);
  }

  if (dvdLogo->dstRect.y <= 0) {
    ChangeDVDColor(dvdLogo);
    BounceBackDVD_Y(dvdLogo);
  }
}

int main(int argc, char *argv[]) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DVD LOGO");

  Texture texture = InitDVDLogoTexture();

  DVDLogo dvdLogo = InitDVDLogo(texture);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    UpdateDVDLogo(&dvdLogo);

    BeginDrawing();

    ClearBackground(BLACK);
    DrawTexturePro(texture, dvdLogo.srcRect, dvdLogo.dstRect,
                   dvdLogo.originCoords, 0, dvdLogo.dvdColor);
    DrawFPS(10, 10);

    EndDrawing();
  }

  UnloadTexture(texture);
  CloseWindow();
  return 0;
}
