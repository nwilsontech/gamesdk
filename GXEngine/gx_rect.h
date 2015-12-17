#ifndef GX_RECT_H
#define GX_RECT_H
#include <vector>
#include "gx_primatives.h"
#include "gx_color.h"

using std::vector;

class RectX:public TPrimative
{
public:
    RectX(float _x = 0,float _y = 0,float _w = 0,float _h = 0,bool f = false);
public:
    PR_OBJECT
    void SetLineColor(TFloat c);
    void SetFillColor(TFloat c);
    void SetLineOpacity(float o);
    void SetFillOpacity(float o);
    void SetLineWidth(float w);
    void AddInternalPrimative(TPrimative *p);
public:
    float x,y,w,h;
    QuikQuad q;
    bool filled;
    bool inside;
    int  colors;
    float line_opacity;
    float fill_opacity;
    TFloat line_color;
    TFloat fill_color;
    float lwidth;
    int  xz,yz;
private:
    vector<TPrimative *> Internal_List;
};

#endif // GX_RECT_H
