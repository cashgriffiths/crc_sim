#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

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
    long long g = atoll(argv[1]);
    g = convert(g);
    long k = atol(argv[2]);
    int iter = atoi(argv[3]);

    long n = k + strlen(argv[1]) - 1;

    srand(time(NULL));
    long m = ((long) rand() * rand()) % ((long long) (1 << k));

    long long c = (long long) m * g;
    printf("m: %ld\nc: %lld\n", m, c);

    printf("g: %lld\nk: %ld\niter: %d\nn: %ld\n", g, k, iter, n);

    int sum = 0; 
    for (int i = 0; i < iter; i++) {
        long long e = ((long) rand() * rand());
        e %= (long) 1 << n;
        // printf("e: %lld\n1 << n: %ld\nc + e: %lld\n", e, (unsigned long) 1 << n, c + e);
        if ((long long) ((c + e) % g) != 0) sum++;   
    }
    printf("sum: %d\n", sum);
    printf("%Lf\n", (long double) sum / iter);
    return 0;
}