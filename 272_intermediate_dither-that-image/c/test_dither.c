#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Test Floyd Steinberg dither. According the definition of this algorithm,
 * a medium 'gray' image is expected to produce a checkerboard pattern when
 * converted to black and white.
 **/

int clamp_int(int a) {
  if (a > 255) {
    a = 255;
  }
  if (a < 0) {
    a = 0;
  }
  return a;
}

uint8_t get_nearest_color(uint8_t in_color) {
  const int BLACK = 0;
  const int WHITE = 255;
  return (in_color < 128) ? BLACK : WHITE;
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


uint8_t *gen_gray_image(int w, int h) {
  int i;
  int length = w * h;
  int luminance = 128;
  uint8_t *image = (uint8_t *)malloc(sizeof(uint8_t) * length);
  uint8_t *p;
  for (i = 0, p = image; i < length; ++i, ++p) {
    *p = luminance;
  }
  return image;
}

/* Generates a checkerboard pattern */
uint8_t *gen_checkerboard_image(int w, int h) {
  int i, j;
  uint8_t *image = (uint8_t *)malloc(sizeof(uint8_t) * w * h);
  uint8_t *p = image;
  for (i = 0; i < h; ++i) {
    for (j = 0; j < w; ++j, ++p) {
      *p = ((j + i) % 2) ? 0 : 255;
    }
  }
  return image;
}


int main(int argc, char *argv[]) {
  uint8_t *gray_image = gen_gray_image(4, 4);
  uint8_t *expected_image = gen_checkerboard_image(4, 4);
  uint8_t *dithered_image = dither_image(gray_image, 4, 4);
  assert(0 == memcmp(dithered_image, expected_image, sizeof(*expected_image) * 4 * 4));
  free(dithered_image);
  free(expected_image);
  free(gray_image);
  return 0;
}
