#include "gx_engine.h"
#include <functional>
using namespace std::placeholders;

std::map<GX_ENGINE_MODE, size_t> GX_Engine::layer_bindings= {
    {EQUIP_MODE,0},
    {STATS_MODE,0},
    {SHOPS_MODE,0},
    {BATTL_MODE,0},
    {QUEST_MODE,0},
    {LEGIN_MODE,0},
    {ENCHT_MODE,0},
    {NAVIG_MODE,0}
};

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

    Menu.menuBack = new TGraphic("bars/menu_back.png");
    Menu.itmBack  = new TGraphic("bars/item_blk2.png");
    Menu.itmBack->SetSize(Menu.menuBack->w-40,200);
    Menu.AddItem(TGX_menu_item("test","attrib1","attrib2"));
    Menu.AddItem(TGX_menu_item("test","attrib1","attrib2"));
    Menu.AddItem(TGX_menu_item("test","attrib1","attrib2"));
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

void GX_Engine::UpdateLayers()
{

}

void GX_Engine::AssocLayerMapping(GX_ENGINE_MODE m,size_t v)
{
    layer_bindings[m] = v;
}

void GX_Engine::SetMode(GX_ENGINE_MODE mode)
{
    md = mode;
}

GX_ENGINE_MODE GX_Engine::GetMode()
{
    return md;
}

void GX_Engine::InitMenuGraphics()
{
    TGraphic *menu_back_item = new TGraphic("bars/menu_back.png",0,0);
    menu_back_item->visible = false;
    menu_back_item->SetClickable(0);
    
}
