#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "donut.h"
#include "codec.h"

unsigned char donut_frames[NUM_BYTES][RESX * RESY];

enum OPCODES {ENCODE, DECODE};

struct settings {
    int operation;

    char in[PATH_MAX];
    int in_set;

    char out[PATH_MAX];
    int out_set;
};

struct settings s = {
    .in_set = 0,
    .out_set = 0,
    .operation = ENCODE
};

void parse_flags(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "i:o:dh")) != -1) {
        switch(opt) {
            case 'i':
                strcpy(s.in, optarg);
                s.in_set = 1;
                break;
            case 'o':
                strcpy(s.out, optarg);
                s.out_set = 1;
                break;
            case 'd':
                s.operation = DECODE;
                break;
            case 'h':
                fprintf(stderr, "Usage %s [-i input_file]\n [-o output_file] [-d decoding instead of encoding] [-h help]\n", argv[0]);
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "Usage %s [-i input_file]\n [-o output_file] [-d decoding instead of encoding] [-h help]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {

    parse_flags(argc, argv);

    if (s.in_set && ! s.out_set) {
        snprintf(s.out, PATH_MAX, "%s.y4m", s.in);
    }

    if (!s.in_set) {
        fprintf(stderr, "No input file provided\n");
        exit(EXIT_FAILURE);
    }

    init_donut_frames();
    if (s.operation == ENCODE) {
        encode_file(s.in, s.out);
    } else {
        decode_file(s.in, s.out);
    }
    
    return 0;
}
