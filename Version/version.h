#ifndef _VERSION_H_
#define _VERSION_H_


#include <stdint.h>


typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} const Version;


#define version() (Version) {        \
    .major = 0                       \
    , .minor = 1                     \
    , .patch = 0                     \
}


#endif
