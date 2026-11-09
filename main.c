#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 256 values -> 0..2pi values
 * byte * (2pi / 256) step
 */

const float TWO_PI = 2.0f * (float)M_PI;
const float step = TWO_PI / 256.0f;
const float inverse_step = 1.0f / step;
const float epsilon = 10e-6f;

void encode_file(char* in, char* out) {
    FILE* fptr_in = fopen(in, "rb");
    FILE* fptr_out = fopen(out, "wb");

    int byte;

    while (fread(&byte, sizeof(unsigned char), 1, fptr_in)) {
        float angle = (float)byte * step;

        fwrite(&angle, sizeof(float), 1, fptr_out);
    }

    fclose(fptr_in);
    fclose(fptr_out);
}

void decode_file(char* in, char* out) {
    FILE* fptr_in = fopen(in, "rb");
    FILE* fptr_out = fopen(out, "wb");

    float angle;

    while (fread(&angle, sizeof(float), 1, fptr_in)) {
        unsigned char byte = angle * inverse_step;

        fwrite(&byte, sizeof(unsigned char), 1, fptr_out);
    }

    fclose(fptr_in);
    fclose(fptr_out);
}

int main(void) {

    encode_file("test_in.txt", "angles_out.txt");
    decode_file("angles_out.txt", "test_out.txt");
    return 0;
}
