#ifndef GX_MENU_H
#define GX_MENU_H


#include "gx_primatives.h"
#include "gx_caption.h"
#include "gx_graphic.h"

#include <vector>
#include <string>

using std::vector;

struct TContext
{
    TGraphic itm_box; /// Item Box
    TGraphic itm_bck; /// Item Pic
    TGraphic itm_pic; /// Item Back
    TLabel   itm_name;
    TLabel   itm_atk;
    TLabel   itm_def;
    TLabel   itm_per;
    TLabel   itm_val;
};
/*
    for(auto &a:items)
    {
        a.itm_box.Draw(); /// Item Box
        a.itm_pic.Draw(); /// Item Pic
        a.itm_bck.Draw(); /// Item Back
        a.itm_name.Draw();
        a.itm_atk.Draw();
        a.itm_def.Draw();
        a.itm_per.Draw();
        a.itm_val.Draw();
    }
 */

class gx_menu:public TPrimative
{
public: //ctor & dtor
    gx_menu(float x, float y, float width, float height);
public: //Virtuals
    virtual void Draw(void);
    virtual int  GetType(void);
    virtual void MoveXY(int _x,int _y);
    virtual void Update(MouseState ms);
    virtual bool Inside();

public: //Functional Operators
    void SetAndUseBackgroundImage(string Image, float width, float height);
    size_t AddMenuItem(TContext &item);
    size_t Size(void);
    int    GetIndex(void);
    TPrimative *GetIndexP(void);
    void SetVisibility(bool ShowNo);
    bool visiblity();
public:
    float xpos;
    float ypos;
    float wpos;
    float hpos;
public:
    vector<TContext> Items;
public:
    void GetEXT(TGraphic *ext);
    //vector<TPrimative *> Items;
public:
    bool  visible;
    string alias;
public:
    QuikQuad bdrop; /// Back Drop
    QuikQuad ndrop; /// Name Drop
    MouseState msx;
public:
    GXCaption *caption;
    TGraphic  *back;
    TGraphic  *_exit_btn;

};

gx_menu *findMenu(primative_list &pl,string alias);

#endif // GX_MENU_H
