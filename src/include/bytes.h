#ifndef _BYTES_H
#define _BYTES_H

#include <stdint.h>

int b2i(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
void i2b(int i, uint8_t* b1, uint8_t* b2, uint8_t* b3, uint8_t* b4);

#endif
