
#include <stdlib.h>
#include <stdint.h>

#include "models.h"

typedef struct filedata {
    uint64_t length;
    uint8_t *data;
} filedata;

static filedata
read_entire_file(const char *filename) {
    filedata result = {};

    return result;
}
