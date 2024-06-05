#pragma once
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

struct AppState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Uint32 *pixels;
  bool running;

  Uint64 timeLeft;
};

extern AppState GlobalState;

int InitSdl();

void CleanupSdl();
