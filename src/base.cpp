#include "base.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "constants.h"
#include <iostream>
#include <ostream>

extern AppState GlobalState;

int InitSdl() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << SDL_GetError() << std::endl;
    SDL_Log("SDL Failed to init");
    return -1;
  }

  GlobalState.window = SDL_CreateWindow("Game", W_WIDTH, W_HEIGHT, 0);
  if (GlobalState.window == NULL) {
    std::cerr << SDL_GetError() << std::endl;
    return -1;
  }

  GlobalState.renderer = SDL_CreateRenderer(GlobalState.window, NULL);
  GlobalState.texture =
      SDL_CreateTexture(GlobalState.renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STATIC, W_WIDTH, W_HEIGHT);

  GlobalState.pixels = new Uint32[W_WIDTH * W_HEIGHT];
  memset(GlobalState.pixels, 255, sizeof(Uint32) * W_WIDTH * W_HEIGHT);

  GlobalState.running = true;

  return 0;
}

void CleanupSdl() {
  delete[] GlobalState.pixels;
  SDL_DestroyTexture(GlobalState.texture);
  SDL_DestroyRenderer(GlobalState.renderer);
  SDL_DestroyWindow(GlobalState.window);
  SDL_Quit();
}
