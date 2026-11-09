#include <stdio.h>
#include <stdlib.h>

int main(void) {
    for (int i = 0; i < 256; ++i) {
        int angle = ((i * 360) + 180) / 256;
        int bytes_conv = (angle * 256) / 360;


        printf("Byte %d -> angle: %d ; angle %d -> byte: %d\n", i, angle, angle, bytes_conv);
        if (i != bytes_conv) {
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
