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
private:
    GX_ENGINE_MODE md;
public:
    void SortLayers();
public: /// Singleton & Clean Up  (Will Update Clean Up Later)
    static GX_Engine *getEngine(void);
    static void Uninitialize(void);
public:
    /// Engine Functions
    void Init();
    void RunEngine();
    void FinEngine();
    /// Layer Functions
    bool LayerDisabled(size_t l);
    void ToggleLayer(size_t l);
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
