#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int main(int argc, char** argv) {
  bool quit = false;
  SDL_Event event;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window =
      SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RWops* rwop = SDL_RWFromFile("../data/Portal_Companion_Cube.jpg", "rb");
  SDL_Surface* image = IMG_LoadJPG_RW(rwop);
  if (!image) {
    printf("IMG_LoadJPG_RW: %s\n", IMG_GetError());
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

  while (!quit) {
    SDL_WaitEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        quit = true;
        break;
    }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
