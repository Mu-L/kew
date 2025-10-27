#ifndef AUDIOTYPES_H
#define AUDIOTYPES_H

#include <miniaudio.h>
#include <stdbool.h>
#include <stdint.h>

enum AudioImplementation {
        PCM,
        BUILTIN,
        VORBIS,
        OPUS,
        M4A,
        WEBM,
        NONE
};

struct m4a_decoder;
typedef struct m4a_decoder m4a_decoder;

typedef void (*uninit_func)(void *decoder);

#endif
