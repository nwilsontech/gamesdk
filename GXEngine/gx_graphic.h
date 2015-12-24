#ifndef GX_GRAPHIC_H
#define GX_GRAPHIC_H

//#include "texture.h"
#include "gx_texture.h"
#include "gx_primatives.h"

//#define GRAPHIC_DEBUG 0
struct FPoint
{
    float x;
    float y;
    FPoint()
    {
        x = 0.0f;
        y = 0.0f;
    }
};


class TGraphic : public TPrimative
{
public:
    TGraphic(string fn = "",float xx=0,float yy=0);
public:
    void SetClip(float cw,float ch);
public:
    virtual void Draw(void);
    virtual int  GetType(void);
    virtual void MoveXY(int _x,int _y);
    virtual void Update(MouseState ms);
    virtual bool Inside();

    void SetFocus(float xx, float yy);
    void SetSize(float ww,float hh);
    void SetAngle(float angle);
    void CalculateExtTex(int index);
    void SetClickable(int i);
    void SetOnclickFunc(UpdateCallback pass);

public:
    bool  rotating;
    bool  visible;
    bool  center;
    bool  status;
private:
    void DrawRotated(void);
    void Click();


public: //temp moved to public for testing
    float x;
    float y;
    FPoint hot;

public: //temp moved to public for testing 2.20.15
    QuikQuad   qm;
    QuikTexMap tm;
    int click;
    float w;
    float h;
    float _clipw;
    float _cliph;
    float _index;
    float theata;
    TFloat color;
    TFloat cap_color;
public:
    GXTexture *tex;

public:
    string name;
    string caption;
private:
    UpdateCallback on_click;

    MouseState lastMS; // Might move to base class;
};

TGraphic *findGraphic(primative_list &pl,string alias);

void CenterWithin(TGraphic &ref, TGraphic &target);
void CenterWithinW(TGraphic &ref,TGraphic &target);
void CenterWithinH(TGraphic &ref,TGraphic &target);

#endif // GX_GRAPHIC_H
