#include "gx_engine.h"

void GX_Engine::DBG_msg(const char* msg)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "[[DEBUG_ERROR]]",
                             msg,
                             nullptr);
}
