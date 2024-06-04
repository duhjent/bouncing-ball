#include "SDL3/SDL_events.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "base.h"
#include "constants.h"
#include "drawing.h"
#include <SDL3/SDL.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>

AppState GlobalState;

int main() {
  int r = 50;

  int initResult = InitSdl();

  if (initResult != 0) {
    return initResult;
  }

  GlobalState.timeLeft = SDL_GetTicks() + TICK_INTERVAL;

  while (GlobalState.running) {
    memset(GlobalState.pixels, 255, sizeof(Uint32) * W_WIDTH * W_HEIGHT);

    DrawCircle(GlobalState.circleX, GlobalState.circleY, r, 0);

    SDL_UpdateTexture(GlobalState.texture, NULL, GlobalState.pixels,
                      W_WIDTH * sizeof(Uint32));

    SDL_Event event;
    if (SDL_PollEvent(&event) > 0) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        GlobalState.running = false;
        break;
      }
    }

    GlobalState.circleX += GlobalState.circleVelX;
    GlobalState.circleY += GlobalState.circleVelY;

    SDL_RenderClear(GlobalState.renderer);
    SDL_RenderTexture(GlobalState.renderer, GlobalState.texture, NULL, NULL);
    SDL_RenderPresent(GlobalState.renderer);

    Uint64 now = SDL_GetTicks();
    SDL_Delay(GlobalState.timeLeft <= now ? 0 : GlobalState.timeLeft - now);
    GlobalState.timeLeft += TICK_INTERVAL;
  }

  CleanupSdl();

  return 0;
}
