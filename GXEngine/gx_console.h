#ifndef GX_CONSOLE_H
#define GX_CONSOLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_thread.h>
#include <string>
using std::string;

class GXConsoleDebug{
public:
    GXConsoleDebug(){enabled = true;str_limit = 120;mod = NULL;}
    ~GXConsoleDebug(){}
    void SetStringMod(string *s){mod = s;}
public:
    void UpdateKeyboard(SDL_Event event);
    string *mod;
    int    str_limit;
    bool   enabled;
};


#endif // GX_CONSOLE_H
