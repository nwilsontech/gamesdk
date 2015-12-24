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
    Menu.AddItem(TGX_menu_item("Heavy Stat Bag","attrib1","attrib2"));
    Menu.items.at(0).itm_image = new TGraphic("consumables/heavy_stat_bag.png");
    Menu.items.at(0).itm_image->SetSize(96,96);
    Menu.items.at(0).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(0).bt1_image->SetSize(110,35);
    Menu.items.at(0).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(0).bt2_image->SetSize(110,35);
    Menu.items.at(0).bt2_image->SetClickable(1);
    Menu.items.at(0).bt1_image->SetClickable(1);
    Menu.AddItem(TGX_menu_item("Volitile Stamina","attrib1","attrib2"));
    Menu.items.at(1).itm_image = new TGraphic("consumables/percentpot_energy.png");
    Menu.items.at(1).itm_image->SetSize(96,96);
    Menu.items.at(1).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(1).bt1_image->SetSize(110,35);
    Menu.items.at(1).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(1).bt2_image->SetSize(110,35);
    Menu.AddItem(TGX_menu_item("Volitale Stamina","attrib1","attrib2"));
    Menu.items.at(2).itm_image = new TGraphic("consumables/percentpot_stamina.png");
    Menu.items.at(2).itm_image->SetSize(96,96);
    Menu.items.at(2).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(2).bt1_image->SetSize(110,35);
    Menu.items.at(2).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(2).bt2_image->SetSize(110,35);
    Menu.AddItem(TGX_menu_item("Volitale Honor","attrib1","attrib2"));
    Menu.items.at(3).itm_image = new TGraphic("consumables/percentpot_honor.png");
    Menu.items.at(3).itm_image->SetSize(96,96);
    Menu.items.at(3).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(3).bt1_image->caption = "Use";
    Menu.items.at(3).bt1_image->SetSize(110,35);
    Menu.items.at(3).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(3).bt2_image->caption = "Info";
    Menu.items.at(3).bt2_image->SetSize(110,35);
    Menu.items.at(2).bt1_image->caption = "Use";
    Menu.items.at(2).bt1_image->cap_color = GetColor("black");
    Menu.items.at(2).bt2_image->caption = "Info";
    Menu.items.at(2).bt2_image->cap_color = GetColor("black");
    Menu.items.at(1).bt1_image->caption = "Use";
    Menu.items.at(1).bt1_image->cap_color = GetColor("black");
    Menu.items.at(1).bt2_image->caption = "Info";
    Menu.items.at(1).bt2_image->cap_color = GetColor("black");
    Menu.items.at(0).bt1_image->caption = "Use";
    Menu.items.at(0).bt2_image->caption = "Info";
    Menu.items.at(1).bt2_image->SetClickable(1);
    Menu.items.at(1).bt1_image->SetClickable(1);
    Menu.items.at(2).bt2_image->SetClickable(1);
    Menu.items.at(2).bt1_image->SetClickable(1);
    Menu.items.at(3).bt2_image->SetClickable(1);
    Menu.items.at(3).bt1_image->SetClickable(1);



    Menu.AddItem(TGX_menu_item("Assassins Lockbox Key","attrib1","attrib2"));
    Menu.items.at(4).itm_image = new TGraphic("consumables/assassins_lockbox_key.png");
    Menu.items.at(4).itm_image->SetSize(96,96);
    Menu.items.at(4).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(4).bt1_image->caption = "Use";
    Menu.items.at(4).bt1_image->SetSize(110,35);
    Menu.items.at(4).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(4).bt2_image->caption = "Info";
    Menu.items.at(4).bt2_image->SetSize(110,35);

    Menu.AddItem(TGX_menu_item("Liquid Rage Silver","attrib1","attrib2"));
    Menu.items.at(5).itm_image = new TGraphic("consumables/liquid_rage_silver.png");
    Menu.items.at(5).itm_image->SetSize(96,96);
    Menu.items.at(5).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(5).bt1_image->caption = "Use";
    Menu.items.at(5).bt1_image->SetSize(110,35);
    Menu.items.at(5).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(5).bt2_image->caption = "Info";
    Menu.items.at(5).bt2_image->SetSize(110,35);

    Menu.AddItem(TGX_menu_item("Liquid Rage Bronze","attrib1","attrib2"));
    Menu.items.at(6).itm_image = new TGraphic("consumables/liquid_rage_bronze.png");
    Menu.items.at(6).itm_image->SetSize(96,96);
    Menu.items.at(6).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(6).bt1_image->caption = "Use";
    Menu.items.at(6).bt1_image->SetSize(110,35);
    Menu.items.at(6).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(6).bt2_image->caption = "Info";
    Menu.items.at(6).bt2_image->SetSize(110,35);

    Menu.AddItem(TGX_menu_item("test 3","attrib1","attrib2"));
    Menu.items.at(7).itm_image = new TGraphic("consumables/book_of_knowledge_platinum.png");
    Menu.items.at(7).itm_image->SetSize(96,96);
    Menu.items.at(7).bt1_image = new TGraphic("bars/boxx_green2.png");
    Menu.items.at(7).bt1_image->caption = "Use";
    Menu.items.at(7).bt1_image->SetSize(110,35);
    Menu.items.at(7).bt2_image = new TGraphic("bars/boxx_blue2.png");
    Menu.items.at(7).bt2_image->caption = "Info";
    Menu.items.at(7).bt2_image->SetSize(110,35);


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
#include "gx_collisions.h"
void TGX_menu::Update(MouseState ms)
{
    if (ms.LeftButtonDown){
        yOffset-=(ms.y-lastY);
        lastY=ms.y;
       // std::cout << "[dbg_y] " << yOffset << std::endl;
    }else {
        lastY = ms.y;
    }

    int OffsetYMax = 165+(items.size()-4)*203;
//        std::cout << "[dbg_a] " << OffsetYMax << std::endl;
//        std::cout << "[dbg_b] " << 165*((int)items.size()) << std::endl;

//        std::cout << "[dbg_c] " << OffsetYMax << std::endl;
    if (yOffset>OffsetYMax)
        yOffset=OffsetYMax;
    if (yOffset<0)
        yOffset=0;
   for(auto &a:items)
    {
        a.bt1_image->Update(ms);
        a.bt2_image->Update(ms);
    }
}

void TGX_menu::Draw()
{
    if (visible==false)
        return;

    if (menuBack==nullptr)
    {
        std::cerr<<"Menu Background Not Initialized"<<std::endl;
        return;
    }

    if (itmBack==nullptr)
    {
        std::cerr<<"Item Background Not Initialized"<<std::endl;
        return;
    }

    menuBack->x = 0.0;
    menuBack->y = 67.0;

    menuBack->Draw();
//45;
    glScissor(20, 23-5,menuBack->w-40,menuBack->h-100);
    glEnable(GL_SCISSOR_TEST);
    for (size_t idx = 0; idx < items.size(); idx++)
    {
        itmBack->x = 20;
        itmBack->y = menuBack-> y + 90 + idx*itmBack->h+3*idx - yOffset;
        itmBack->Draw();
        items.at(idx).itm_image->x = itmBack->x + 30;
        items.at(idx).itm_image->y = itmBack->y + 30;
        items.at(idx).itm_image->Draw();
        WorldEngine->FontManager.PrintTextRight(items.at(idx).itm_image->x+90,items.at(idx).itm_image->y+96,1,std::to_string(items.at(idx).stack).c_str());
        TFormatedStringList tmp;
        tmp.Push(TFormatedString(1,"greenyellow",items.at(idx).text));
        WorldEngine->FontManager.PrintText(150+15,itmBack->y+35,1,tmp);
        if (items.at(idx).bt1_image!=nullptr)
        {
            items.at(idx).bt1_image->x = menuBack->w - 150;
            items.at(idx).bt1_image->y = itmBack->y+100;
            items.at(idx).bt1_image->Draw();
        }
        if (items.at(idx).bt2_image!=nullptr)
        {
            items.at(idx).bt2_image->x = menuBack->w - 150;
            items.at(idx).bt2_image->y = itmBack->y+140;
            items.at(idx).bt2_image->Draw();
        }
    }
    glDisable(GL_SCISSOR_TEST);
//        for (size_t idx = 0; idx < items.size(); i++)
//        {
//            items.at(idx).itm_image->x = 0;
//            items.at(idx).itm_image->y = 0 + idx*45;
//            items.at(idx).itm_image->Draw();
//        }
}
