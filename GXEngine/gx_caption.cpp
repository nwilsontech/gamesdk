#include "gx_caption.h"

/// Enables access to Engine Font Manager
#include "gx_engine.h"

GXCaption::GXCaption(float xx, float yy, std::string text):TPrimative()
{
    x    = xx;
    y    = yy;
    Text = text;
    Color = TColorFloat(1.0f,1.0f,1.0f,1.0f);
    fs   = 13;
}
GXCaption::~GXCaption()
{

}

void GXCaption::Draw(void)
{
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    //glColor4f(Color.red,Color.green,Color.blue,Color.alpha);
    //FontDraw((char *)Text.c_str(),x+_ox,y+_oy);
    WorldEngine->FontManager.PushSize(1);
    WorldEngine->FontManager.SetSize(1,fs);
    int ofX;
    ofX = WorldEngine->FontManager.fonts[1]->BBox(Text.c_str()).Upper().X();

    WorldEngine->FontManager.PrintText(x+_ox-ofX/2,y+_oy,1,Text.c_str());
    WorldEngine->FontManager.PopSize(1);
    glColor4f(1.0,1.0,1.0,1.0);
}

int GXCaption::GetType(void)
{
    return _pr_type_caption;
}

void GXCaption::MoveXY(int _x,int _y)
{
    x = _x;
    y = _y;
}

void GXCaption::Update(MouseState ms)
{
    unused(ms);
}

bool GXCaption::Inside()
{
    return false;
}
void GXCaption::FontColor(TColorFloat c)
{
    Color = c;
}

void GXCaption::FontColor(unsigned int c)
{
    unused(c);
//    ColorGrid CG = glColor2Grid(c);
//    Color.red   = CG.col[0];
//    Color.green = CG.col[1];
//    Color.blue  = CG.col[2];
   // SetColor3f(CG.col[0],CG.col[1],CG.col[2]);
}

void GXCaption::SetSize(size_t size)
{
    fs = size;
}

//////////////////////////////////////

GXLabelBox::GXLabelBox(float _x,float _y,float _w,float _h,string text):TPrimative()
{
    x    = _x;
    y    = _y;
    w    = _w;
    h    = _h;

    Text = text;
    Color = TColorFloat(1.0f,1.0f,1.0f,1.0f);
    fs   = 20;
    _alg = GX_LB_ALIGN_CENTER;
}
GXLabelBox::~GXLabelBox()
{

}

void GXLabelBox::Draw(void)
{
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    //glColor4f(Color.red,Color.green,Color.blue,Color.alpha);
    //FontDraw((char *)Text.c_str(),x+_ox,y+_oy);
    WorldEngine->FontManager.PushSize(1);
    WorldEngine->FontManager.SetSize(1,fs);
    if (_alg==GX_LB_ALIGN_CENTER)
        WorldEngine->FontManager.PrintTextCenter(x+_ox+w/2,y+_oy+h/2,1,Text.c_str());
    if (_alg==GX_LB_ALIGN_LEFT)
        WorldEngine->FontManager.PrintText(x+_ox,y+_oy+h/2,1,Text.c_str());
    if (_alg==GX_LB_ALIGN_RIGHT)
        WorldEngine->FontManager.PrintTextRight(x+w+_ox,y+h+_oy,1,Text.c_str());
    WorldEngine->FontManager.PopSize(1);
    glColor4f(1.0,1.0,1.0,1.0);
}

int GXLabelBox::GetType(void)
{
    return _pr_type_lb_box;
}

void GXLabelBox::MoveXY(int _x,int _y)
{
    x = _x;
    y = _y;
}

void GXLabelBox::Update(MouseState ms)
{
    unused(ms);
}

bool GXLabelBox::Inside()
{
    return false;
}
void GXLabelBox::FontColor(TColorFloat c)
{
    Color = c;
}

void GXLabelBox::FontColor(unsigned int c)
{
    unused(c);
//    ColorGrid CG = glColor2Grid(c);
//    Color.red   = CG.col[0];
//    Color.green = CG.col[1];
//    Color.blue  = CG.col[2];
   // SetColor3f(CG.col[0],CG.col[1],CG.col[2]);
}

void GXLabelBox::SetSize(size_t size)
{
    fs = size;
}
void GXLabelBox::SetAlignment(LBL_BOX_ALIGN a)
{
    _alg = a;
}

///////////
