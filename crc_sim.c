#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

// shamelessly stolen from programiz.com to convert binary to decimal
long convert(long long n) {

  int dec = 0, i = 0, rem;

  while (n != 0) {

    // get remainder of n divided by 10
    rem = n % 10;

    // divide n by 10
    n /= 10;

    // multiply rem by (2 ^ i)
    // add the product to dec
    dec += rem * pow(2, i);

    // increment i
    ++i;
  }

  return dec;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: crc_sim <g> <k> <iter>");
        return 1;
    }
    unsigned long long g = atoll(argv[1]);
    g = convert(g);
    unsigned long long k = atol(argv[2]);
    int iter = atoi(argv[3]);

    unsigned long long n = k + strlen(argv[1]) - 1;

    unsigned long long enc_reg = 0, dec_reg = 0;
    
    srand(time(NULL));
    int sum = 0; 
    for (int j = 0; j < iter; j++) {
      for (int i = 0; i < n; i++) {
        // generate arbitrary message bit
        uint8_t m = rand() > 0.5 ? 1 : 0;
        // grab next shift register bit
        uint8_t data_out = enc_reg & 1;
        // xor with message bit
        uint8_t f = data_out ^ m;
        // update encoding register
        enc_reg = (enc_reg >> 1) ^ (f ? g : 0);
        // get next codeword bit
        // first k bits are message bits, next n-k bits are parity
        uint8_t c = i < k ? m : data_out;
        // add noise - could probably just be a random bit, it would be the same
        c ^= rand() > INT_MAX / 2 ? 1 : 0;
        // update decoding register
        dec_reg = (dec_reg >> 1) ^ ((c ^ (dec_reg & 1)) ? g : 0);
      }
      // if an error is detected register contents are nonzero
      if (dec_reg) sum++;
    }
    printf("sum: %d\n", sum);
    printf("%Lf\n", (long double) sum / iter);
    return 0;
}