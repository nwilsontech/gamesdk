#ifndef GX_ENGINE_H
#define GX_ENGINE_H

#include "gx_variables.h"
#include "gx_logical.h"
#include "gx_graphic.h"
#include "gx_font_manager.h"

/* Note - 2.28.15 Started working on turning engine into a sigleton class
 * rather that the following functions:  RunEngine(); FinEngine();
 *
 */


class TGX_menu_item
{
public:
    TGX_menu_item(std::string t,std::string at1,std::string at2){
        text = t;
        attrib1 = at1;
        attrib2 = at2;
        itm_image = nullptr;
        bt1_image = nullptr;
        bt2_image = nullptr;
        stack = 1;
    }
   ~TGX_menu_item(){}
public:
    std::string text;
    std::string attrib1;
    std::string attrib2;
    TGraphic *itm_image;
    TGraphic *bt1_image;
    TGraphic *bt2_image;
    size_t stack;

};

class TGX_menu
{
public:
    TGX_menu(){
        menuBack = nullptr;
        itmBack  = nullptr;
        visible  = false;
        lastX = lastY = 0;
    }
    ~TGX_menu(){}
public:
    void AddItem(TGX_menu_item itm)
    {
        items.push_back(itm);
    }
    void SetVisible(bool ShowNo){
        visible  = ShowNo;
    }
    void Update(MouseState ms);


public:
    void Draw();


public:
    std::vector<TGX_menu_item> items;
public:
    int lastX,lastY;
    TGraphic *menuBack;
    TGraphic *itmBack;

    bool      visible;
    int yOffset;

};






#define USING_DBG_INFO









enum GX_ENGINE_MODE
{
    EQUIP_MODE,
    STATS_MODE,
    SHOPS_MODE,
    BATTL_MODE,
    QUEST_MODE,
    LEGIN_MODE,
    ENCHT_MODE,
    NAVIG_MODE
};
class GX_Engine
{
private: /// CTOR & DTOR
    GX_Engine();
    virtual ~GX_Engine();
public:
    static std::map<GX_ENGINE_MODE, size_t> layer_bindings;
private:
    GX_ENGINE_MODE md;
public:
    void SortLayers();
public: /// Singleton & Clean Up  (Will Update Clean Up Later)
    static GX_Engine *getEngine(void);
    static void Uninitialize(void);
public:
    void InitMenuGraphics();
public:
    /// Engine Functions
    void Init();
    void RunEngine();
    void FinEngine();
    /// Layer Functions
    bool LayerDisabled(size_t l);
    void ToggleLayer(size_t l);
    void UpdateLayers();
    ///
    void AssocLayerMapping(GX_ENGINE_MODE m,size_t v);
    /// Game Mode Functions
    void SetMode(GX_ENGINE_MODE mode);
    GX_ENGINE_MODE GetMode();

public:
//    void &PrintText(int x, int y,int f,const char *fmt,...);
    void *Print;
    long ticks();
public:
    void DBG_msg(const char *msg);
public:
    TGX_menu Menu;
    TFontManager FontManager;
    vector< vector<TPrimative *> > layers;
    vector<bool> elayers;
    vector<std::string> layers_alias;

};


/// Made this a static to correct redefinition error during
/// compilation.
static const auto& WorldEngine = GX_Engine::getEngine();


/// Encapsulated inside engine class
//void RunEngine(void);
//void FinEngine(void);

#endif // GX_ENGINE_H
