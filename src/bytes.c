#include <stdint.h>

#include "bytes.h"

int b2i(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {
  return (b1) | (b2 << 8) | (b3 << 16) | (b4 << 24);
}

void i2b(int i, uint8_t* b1, uint8_t* b2, uint8_t* b3, uint8_t* b4) {
  *b1 = (i >> 0) & 0xFF;
  *b2 = (i >> 8) & 0xFF;
  *b3 = (i >> 16) & 0xFF;
  *b4 = (i >> 24) & 0xFF;
}
