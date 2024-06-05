#include "drawing.h"
#include "constants.h"
#include <algorithm>

void DrawPoint(Uint32 x, Uint32 y, Uint32 color) {
  GlobalState.pixels[(y * W_WIDTH + x)] = color;
}

void DrawRect(Uint32 x, Uint32 y, Uint32 w, Uint32 h, Uint32 color) {
  for (int r = y; r < y + h && r < W_HEIGHT; r++) {
    memset(&(GlobalState.pixels[r * W_WIDTH + x]), color, sizeof(Uint32) * w);
  }
}

void DrawCircle(int x, int y, int r, Uint32 color) {
  int low = y - r + 1 >= 0 ? -r + 1 : -y;
  int high = y + r < W_HEIGHT ? r : W_HEIGHT - y - 1;
  for (int i = low; i < high; i++) {
    int row = y + i;
    int halfw = sqrt(r * r - i * i);
    int s = std::max(x - halfw, 0);
    int w =
        std::min(x - halfw >= 0 ? 2 * halfw : halfw + x, halfw + W_WIDTH - x);
    memset(&(GlobalState.pixels[row * W_WIDTH + s]), color, sizeof(Uint32) * w);
  }
}

void ClearCanvas() {
  memset(GlobalState.pixels, 255, sizeof(Uint32) * W_WIDTH * W_HEIGHT);
}
