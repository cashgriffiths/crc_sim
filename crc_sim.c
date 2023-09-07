#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: crc_sim <g> <k> <iter>");
        return 1;
    }
    unsigned long g = strtoll(argv[1], NULL, 16);
    int r = 31 - __builtin_clz(g);
    printf("g: %lu\nr: %d\n", g, r);
    unsigned long k = atol(argv[2]);
    int iter = atoi(argv[3]);

    unsigned long long n = k + r;

    uint8_t codeword[n], error_word[n], received_word[n];

    unsigned long enc_reg = 0, dec_reg = 0;
    
    srand(time(NULL));
    int sum = 0; 
    for (int j = 0; j < iter; j++) {
      enc_reg = 0;
      dec_reg = 0;
      for (int i = 0; i < n; i++) {
        // generate arbitrary message bit
        uint8_t m = (rand() >> 5) & 0b1;
        // grab next shift register bit
        uint8_t data_out = enc_reg & 0b1;
        // xor with message bit
        uint8_t f = data_out ^ m;
        // update encoding register
        enc_reg ^= (f ? g : 0);
        enc_reg >>= 1;
        // get next codeword bit
        // first k bits are message bits, next n-k bits are parity
        codeword[i] = i < k ? m : data_out;
        // generate error word
        error_word[i] = (rand() >> 5) & 0b1;
        // received word is addition of codeword and error
        received_word[i] = codeword[i] ^ error_word[i];
      }
      for (int i = 0; i < n; i++) {
        // grab next shift register bit
        uint8_t data_out = dec_reg & 0b1;
        // xor with received bit
        uint8_t f = data_out ^ received_word[i];
        // update decoding register
        dec_reg ^= (f ? g : 0);
        dec_reg >>= 1;
      }
      // if an error is not detected register contents are zero
      if (!dec_reg) sum++;
    }
    printf("sum: %d\n", sum);
    printf("%Lf\n", (long double) sum / iter);
    return 0;
}