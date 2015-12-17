#pragma once
#ifndef GX_CAPTION_H
#define GX_CAPTION_H

#include "font.h"
#include "gx_color.h"

#include "gx_primatives.h"
#include <string>

using std::string;

class GXCaption:public TPrimative
{
public:
    GXCaption(float xx,float yy,string text);  // ctor
    ~GXCaption(); // dtor
public:
    PR_OBJECT
    void FontColor(TColorFloat c);
    void FontColor(unsigned int c);
    void SetSize(size_t size);

public:
    string Text;
    float  x,y;
    TColorFloat Color;
    size_t fs;
};
using TLabel = GXCaption;

#include "gx_rect.h"

class GXLabelBox:public TPrimative
{
public:
    GXLabelBox(float _x = 0,float _y = 0,float _w = 0,float _h = 0,string text="");  // ctor
    ~GXLabelBox(); // dtor
public:
    PR_OBJECT
    void FontColor(TColorFloat c);
    void FontColor(unsigned int c);
    void SetSize(size_t size);

public:
    string Text;
    float x,y,w,h;
    TColorFloat Color;
    size_t fs;
private:

};
using TLabelEX = GXLabelBox;

TLabel *findCaption(primative_list &pl,string alias);
TLabelEX *findLabelBox(primative_list &pl,string alias);
#endif // GX_CAPTION_H
