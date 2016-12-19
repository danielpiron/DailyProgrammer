#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

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

int greyscale(int r, int g, int b) {
  return (r * 0.2126 + g * 0.7152 + b * 0.0722);
}

SDL_Surface *greyscale_surface(SDL_Surface *surface) {
  SDL_Surface *grey_surface = NULL;
  Uint8 *src_scanline;
  Uint8 *dest_scanline;
  Uint8 *src_pixels = NULL;
  Uint8 *dest_pixels = NULL;
  int i, j;
  grey_surface = SDL_CreateRGBSurface(0, surface->w, surface->h,
                                         surface->format->BitsPerPixel,
                                         surface->format->Rmask,
                                         surface->format->Gmask,
                                         surface->format->Bmask,
                                         surface->format->Amask);

  if (grey_surface == NULL) {
    return NULL;
  }

  SDL_LockSurface(surface);
  SDL_LockSurface(grey_surface);

  src_scanline = (Uint8 *)surface->pixels;
  dest_scanline = (Uint8 *)grey_surface->pixels;

  for (i = 0; i < surface->h; i++) {
    src_pixels = src_scanline;
    dest_pixels = dest_scanline;
    for (j = 0; j < surface->w; j++) {
      Uint8 r, g, b;
      int intensity;
      r = src_pixels[0];
      g = src_pixels[1];
      b = src_pixels[2];
      intensity = greyscale(r, g, b);
      dest_pixels[0] = intensity;
      dest_pixels[1] = intensity;
      dest_pixels[2] = intensity;
      src_pixels += 3;
      dest_pixels += 3;
    }
    src_scanline += surface->pitch;
    dest_scanline += grey_surface->pitch;
  }

  SDL_UnlockSurface(surface);
  SDL_UnlockSurface(grey_surface);
  return grey_surface;
}

uint8_t get_nearest_color(uint8_t in_color) {
  const int BLACK = 0;
  const int WHITE = 255;

  /* return (in_color < 128) ? BLACK : WHITE; */
  return in_color >> 6 << 6;
}

int clamp_int(int a) {
  if (a > 255) {
    a = 255;
  }
  if (a < 0) {
    a = 0;
  }
  return a;
}

uint8_t *dither_image(uint8_t *image, int w, int h) {
  /* Let's start off by allocating memory to represent the error distribution
   * of the entire image. */
  uint8_t *dithered = (uint8_t *)malloc(sizeof(uint8_t) * w * h);
  int *error_table = (int *)calloc(w * h, sizeof(int));
  int i, j;
  /* - * 7
   * 3 5 1 [/16] */
  for (i = 0; i < h; ++i) {
    for (j = 0; j < w; ++j) {
      int pixel_index = i * w + j;
      int oldpixel = clamp_int(image[pixel_index] + error_table[pixel_index]);
      int newpixel = get_nearest_color(oldpixel);
      int quant_error = oldpixel - newpixel;
      dithered[pixel_index] = newpixel;
      if (j < (w - 1)) {
        error_table[pixel_index + 1] +=  quant_error * 7 / 16;
      }
      if (i < (h - 1)) {
        if (j > 0) {
          error_table[pixel_index + w - 1] += quant_error * 3 / 16;
        }
        error_table[pixel_index + w] += quant_error * 5 / 16;
        if (j < (w - 1)) {
          error_table[pixel_index + w + 1] += quant_error * 1 / 16;
        } 
      }
    }
  }
  free(error_table);
  return dithered;
}

SDL_Surface *dithered_surface(SDL_Surface *surface) {
  SDL_Surface *dithered_surface = NULL;
  Uint8 *dest_scanline;
  Uint8 *src_scanline;
  uint8_t *dithered_image;
  uint8_t *gray_image;
  uint8_t *pixel;
  int i, j;

  gray_image = (uint8_t *)malloc(sizeof(uint8_t) * surface->w * surface->h);

  SDL_LockSurface(surface);
  src_scanline = (Uint8 *)surface->pixels;
  pixel = gray_image;
  for (i = 0; i < surface->h; i++) {
    Uint8 *src_pixels = src_scanline;
    for (j = 0; j < surface->w; j++) {
      Uint8 r, g, b;
      r = src_pixels[0];
      g = src_pixels[1];
      b = src_pixels[2];
      *pixel = greyscale(r, g, b);
      pixel++;
      src_pixels += 3;
    }
  src_scanline += surface->pitch;
  }
  SDL_UnlockSurface(surface);

  dithered_image =  dither_image(gray_image, surface->w, surface->h);
   free(gray_image);

  dithered_surface = SDL_CreateRGBSurface(0, surface->w, surface->h,
                                          surface->format->BitsPerPixel,
                                          surface->format->Rmask,
                                          surface->format->Gmask,
                                          surface->format->Bmask,
                                          surface->format->Amask);
  if (dithered_surface == NULL) {
    return NULL;
  }

  pixel = dithered_image;
  dest_scanline = (Uint8 *)dithered_surface->pixels;
  SDL_LockSurface(dithered_surface);
  for (i = 0; i < surface->h; i++) {
    Uint8 *dest_pixels = dest_scanline;
    for (j = 0; j < surface->w; j++) {
      int intensity = *pixel;
      dest_pixels[0] = intensity;
      dest_pixels[1] = intensity;
      dest_pixels[2] = intensity;
      pixel++;
      dest_pixels += 3;
    }
  dest_scanline += dithered_surface->pitch;
  }
  SDL_UnlockSurface(dithered_surface);
  free(dithered_image);
  return dithered_surface;
}


int main(int argc, char *argv[]) {
  SDL_RWops *rwop;
  SDL_Rect rect;
  SDL_Renderer *renderer;
  SDL_Surface *grey_image;
  SDL_Surface *image;
  SDL_Texture *texture;
  SDL_Window *window;
  int quit = 0;
  int real_width, real_height;
  int w, h;

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_GL_GetDrawableSize(window, &real_width, &real_height);

  renderer = SDL_CreateRenderer(window, -1, 0);
  /* SDL_RWops *rwop = SDL_RWFromFile("../data/Portal_Companion_Cube.jpg", "rb"); */
  rwop = SDL_RWFromFile("../data/alex_at_2.jpg", "rb");
  image = IMG_LoadJPG_RW(rwop);
  if (!image) {
    printf("IMG_LoadJPG_RW: %s\n", IMG_GetError());
  }
  grey_image = dithered_surface(image);

  SDL_SaveBMP(grey_image, "dithered.bmp");

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  texture = SDL_CreateTextureFromSurface(renderer, grey_image);

  while (!quit) {
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
      quit = 1;
      break;
    }

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    make_fit(&rect, w, h, real_width, real_height);
    rect.x = (real_width - rect.w) / 2;
    rect.y = (real_height - rect.h) / 2;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(grey_image);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
