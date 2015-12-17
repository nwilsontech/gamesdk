#ifndef GX_HEALTHBAR_H
#define GX_HEALTHBAR_H
#include "gx_primatives.h"


class THealthBar:public TPrimative
{
public:
    THealthBar(float _x = 0,float _y = 0,float _w = 0,float _h = 0,bool f = false);
public:
    virtual void Draw(void);
    virtual int GetType(void);
    virtual void MoveXY(int _x,int _y);
    virtual void Update(MouseState ms);
    virtual bool Inside();

    void SetMax(float M);
    void SetValue(float V);
    void SetColor4f(float r,float g,float b,float a);
    void SetColor3f(float r,float g,float b);
    void SetBorderColor4f(float r,float g,float b,float a);
    void SetBorderColor3f(float r,float g,float b);
    void SetBorderSize(float s);
    void SetCaption(char *newCaption);


public:
    float  x,y,w,h;
    float  max_value;
    float  cur_value;
    float  border_width;
    bool   filled;
    bool   inside;
    int    colors;
    float  slider_pos;
    string caption;
    TColorFloat line_color;
    TColorFloat fill;
    //int  xz,yz;
public:

};
THealthBar *findHealthBar(primative_list &pl,string alias);

#endif // GX_HEALTHBAR_H
