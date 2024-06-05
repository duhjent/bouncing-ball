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

typedef struct Ball {
  int x;
  int y;
  int r;

  int velX;
  int velY;
  int accX;
  int accY;
} Ball;

int main() {
  Ball ball = {
      .x = 50, .y = 50, .r = 50, .velX = 0, .velY = 0, .accX = 0, .accY = 1};

  int initResult = InitSdl();

  if (initResult != 0) {
    return initResult;
  }

  GlobalState.timeLeft = SDL_GetTicks() + TICK_INTERVAL;

  int peak = W_HEIGHT - (W_HEIGHT - ball.y) * .9;

  while (GlobalState.running) {
    // Poll events
    SDL_Event event;
    if (SDL_PollEvent(&event) > 0) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        GlobalState.running = false;
        break;
      }
    }

    // Whatever logic to execute each new frame
    if (ball.accY < 0 && (W_HEIGHT - ball.y) >= peak) {
      ball.accY = 1;
      peak = peak * .9;
    }
    if (ball.y + ball.r >= W_HEIGHT && ball.accY > 0) {
      ball.accY = -5;
      ball.velY = 0;
    }
    if (peak <= ball.r && ball.accY != 0 && ball.velY != 0) {
      ball.accY = 0;
      ball.velY = 0;
    }

    ball.velY += ball.accY;
    ball.velX += ball.accX;

    ball.y += ball.velY;
    ball.x += ball.velX;

    // ball.y = std::min(std::max(ball.y, ball.r), W_HEIGHT - ball.r);
    // ball.x = std::min(std::max(ball.x, ball.r), W_WIDTH - ball.r);

    // Each time we start with a new canvas
    ClearCanvas();

    // And draw things on it
    DrawCircle(ball.x, ball.y, ball.r, 0);

    // Rendering
    SDL_UpdateTexture(GlobalState.texture, NULL, GlobalState.pixels,
                      W_WIDTH * sizeof(Uint32));
    SDL_RenderClear(GlobalState.renderer);
    SDL_RenderTexture(GlobalState.renderer, GlobalState.texture, NULL, NULL);
    SDL_RenderPresent(GlobalState.renderer);

    // Delay to maintain stable FPS
    Uint64 now = SDL_GetTicks();
    SDL_Delay(GlobalState.timeLeft <= now ? 0 : GlobalState.timeLeft - now);
    GlobalState.timeLeft += TICK_INTERVAL;
  }

  CleanupSdl();

  return 0;
}
