#ifndef GXPARTICALSYS_H
#define GXPARTICALSYS_H

#include <SDL2/SDL.h>
#include <string>
using std::string;

typedef struct
{
    union
    {
        struct
        {
            float x,y;
        };
        float v[2];
    };
} BVertex2;

/* Causes warning:
 * incompatible types when assigning to type 'Foo' from type 'Bar'
 * ... the compiler optimizes away the temp var */


#endif // GXPARTICALSYS_H
