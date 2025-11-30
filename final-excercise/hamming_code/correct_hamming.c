#include <stdio.h>
#include <string.h>

void correctHamming(const char *bits, int data[4]) {
    // bits: k7 k6 k5 k4 k3 k2 k1 (index 0..6)

    int b[7];
    for (int i = 0; i < 7; i++)
        b[i] = bits[i] - '0';

    // mapping: b[0]=d3, b[1]=d2, b[2]=d1, b[3]=p2, b[4]=d0, b[5]=p1, b[6]=p0

    int d3 = b[0];
    int d2 = b[1];
    int d1 = b[2];
    int p2 = b[3];
    int d0 = b[4];
    int p1 = b[5];
    int p0 = b[6];

    // parity groups
    int g1 = (d3 + d1 + d0 + p0) % 2;  // group 1
    int g2 = (d3 + d2 + d0 + p1) % 2;  // group 2
    int g4 = (d3 + d2 + d1 + p2) % 2;  // group 4

    int k = 4 * g4 + 2 * g2 + g1;      // wrong-bit position (1..7), 0 = no error

    if (k != 0) {
        int idx = 7 - k;              // bit index to flip
        b[idx] ^= 1;
        printf("Corrected bit at position %d\n", k);
    }

    // extract corrected data bits d3 d2 d1 d0
    data[3] = b[0];   // d3 (MSB)(Most Significant Bit)
    data[2] = b[1];   // d2
    data[1] = b[2];   // d1
    data[0] = b[4];   // d0 (LSB)(Least Significant Bit)
}

int main() {
    char s[200001];
    scanf("%s", s);
    //printf("Received: %s",s);

    int n = strlen(s);
    char output[200001];
    int outIndex = 0;

    for (int i = 0; i < n; i += 14) {
        int d1[4], d2[4];
        correctHamming(s + i, d1);       // first 7 bits
        correctHamming(s + i + 7, d2);   // next 7 bits

        // Form 8-bit ASCII: d1[3..0], d2[3..0]
        int value = (d1[3] << 7) |
                    (d1[2] << 6) |
                    (d1[1] << 5) |
                    (d1[0] << 4) |
                    (d2[3] << 3) |
                    (d2[2] << 2) |
                    (d2[1] << 1) |
                     d2[0];

        output[outIndex++] = (char)(value);
    }

    output[outIndex] = '\0';
    printf("%s\n", output);
    return 0;
}