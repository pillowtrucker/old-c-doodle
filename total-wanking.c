#include <nmmintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
uint32_t calc_crc32(uint8_t *bytes, size_t len) {
  uint32_t hash = 0;
  size_t i = 0;
  
  for (i = 0; i < len; i++) {
    hash = _mm_crc32_u8(hash, bytes[i]);
  }
return hash;
}
int main(int argc, char **argv) {
  uint32_t hash = calc_crc32((uint8_t *) argv[1],strlen(argv[1]));
  printf("%x",hash);
}
