#include "gx_engine.h"
#include <functional>
using namespace std::placeholders;

GX_Engine::GX_Engine()
{

}
GX_Engine::~GX_Engine()
{
    /// nada
}

GX_Engine *GX_Engine::getEngine(void)
{
    static GX_Engine *engine = new GX_Engine();
    return engine;
}

/// Clean up engine
void GX_Engine::Uninitialize(void)
{
    delete GX_Engine::getEngine();
}

void GX_Engine::Init()
{
    elayers = {
        false, false, false, false, false,
        false, false, false, false, false
    };
    layers_alias={
        "","","","","",
        "","","","",""
    };
    md = NAVIG_MODE;
    FontManager.Init();
    //Print =std::bind(&FontManager.PrintText,_1,_2,_3,_4,_5);
}

long GX_Engine::ticks()
{
    return (SDL_GetTicks());
}

bool GX_Engine::LayerDisabled(size_t l)
{
    return elayers.at(l);
}
void GX_Engine::ToggleLayer(size_t l)
{
    elayers[l] = !elayers[l];
}

void GX_Engine::SetMode(GX_ENGINE_MODE mode)
{
    md = mode;
}

GX_ENGINE_MODE GX_Engine::GetMode()
{
    return md;
}
