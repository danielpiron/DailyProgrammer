#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

float get_aspect_ratio(int w, int h) { return (float)w / h; }

void make_fit(SDL_Rect *rect, int w, int h, int fit_w, int fit_h) {
  float aspect = get_aspect_ratio(w, h);
  float fit_aspect = get_aspect_ratio(fit_w, fit_h);
  float scale;

  rect->x = rect->y = 0;
  if (aspect > fit_aspect) {
    scale = (float)fit_w / w;
    rect->w = fit_w;
    rect->h = (int)(h * scale);
  } else {
    scale = (float)fit_h / h;
    rect->w = (int)(w * scale);
    rect->h = fit_h;
  }
}

void test_exact_fit() {
  SDL_Rect result;
  SDL_Rect expected = {0, 0, 10, 10};
  make_fit(&result, 10, 10, 10, 10);
  assert(memcmp(&result, &expected, sizeof(result)) == 0);
}

void test_inner_has_wider_aspect() {
  SDL_Rect result;
  SDL_Rect expected = {0, 0, 10, 8};
  make_fit(&result, 20, 16, 10, 10);
  assert(memcmp(&result, &expected, sizeof(result)) == 0);
}

void test_inner_has_taller_aspect() {
  SDL_Rect result;
  SDL_Rect expected = {0, 0, 8, 10};
  make_fit(&result, 16, 20, 10, 10);
  assert(memcmp(&result, &expected, sizeof(result)) == 0);
}

void test_runner() {
  test_exact_fit();
  test_inner_has_wider_aspect();
  test_inner_has_taller_aspect();
}

int main(int argc, char **argv) {
  bool quit = false;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  SDL_RWops *rwop = SDL_RWFromFile("../data/Portal_Companion_Cube.jpg", "rb");
  SDL_Surface *image = IMG_LoadJPG_RW(rwop);
  if (!image) {
    printf("IMG_LoadJPG_RW: %s\n", IMG_GetError());
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

  while (!quit) {
    SDL_WaitEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
      quit = true;
      break;
    }
    int w, h;
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    make_fit(&rect, w, h, 640, 480);
    rect.x = (640 - rect.w) / 2;
    rect.y = (480 - rect.h) / 2;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
