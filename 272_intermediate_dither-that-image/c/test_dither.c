#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Test Floyd Steinberg dither. According the definition of this algorithm,
 * a medium 'gray' image is expected to produce a checkerboard pattern when
 * converted to black and white.
 **/

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
  free(expected_image);
  free(gray_image);
  return 0;
}
