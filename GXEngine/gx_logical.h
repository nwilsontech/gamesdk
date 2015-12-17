#ifndef MAIN_H
#define MAIN_H
#include "gx_variables.h"
#ifdef UNREAL
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>
    #include <SDL2/SDL_thread.h>
#else
    #include <SDL/SDL.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
using std::vector;
const int window_w = 640;
const int window_h = 820;
static std::string base_location = "";

void setOrtho(int width=0, int height=0,int s__x =0,int s__y =0);
int RenderScene(void *data);

#endif // MAIN_H
