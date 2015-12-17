#ifndef GX_EX_HEALTHBAR_H
#define GX_EX_HEALTHBAR_H

#include "gx_primatives.h"
#include "gx_texture.h"
#include <string>

class THealthBarEx:public TPrimative
{
public:
    THealthBarEx(std::string fn,float _x = 0,float _y = 0,float _w = 0,float _h = 0);
public:
    virtual void Draw(void);
    virtual int GetType(void);
    virtual void MoveXY(int _x,int _y);
    virtual void Update(MouseState ms);
    virtual bool Inside();
    void SetMax(double M);
    void SetValue(double V);
    void ResetAndMax(double M);
    void EnableValueType(bool show, int type);
    double Decrement(double dec);


public:
    bool formated;
    bool show_value;
    int value_type;
    float x,y,w,h;
    bool  inside;
    int   colors;
    double slider_pos;
    double cur_value;
    double max_value;
    int  xz,yz;
public:
    GXTexture *tex;

};
THealthBarEx *findHealthBarEx(primative_list &pl,string alias);
#endif // GX_EX_HEALTHBAR_H
