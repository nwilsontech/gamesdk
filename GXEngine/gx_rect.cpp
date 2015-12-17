#include "gx_rect.h"

RectX::RectX(float _x,float _y,float _w,float _h,bool f):TPrimative()
{
    x          = _x;
    y          = _y;
    w          = _w;
    h          = _h;
    q          = QuikQuad(_x,_y,0,_w,_h);
    filled     =  f;
    line_color = TFloat(1.0,1.0,1.0);
    fill_color = TFloat(1.0,1.0,1.0);
    colors     = 1;
    lwidth     = 2.0f;
}
void RectX::MoveXY(int _x,int _y)
{
    x = _x;
    y = _y;
}

void RectX::Update(MouseState ms)
{
    for(int i = 0; i <  (int)Internal_List.size(); i++)
    {
        Internal_List.at(i)->Update(ms);
    }
}

bool RectX::Inside()
{
    return true;
}

void RectX::Draw(void)
{

    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLineWidth(lwidth);
    glEnableClientState(GL_VERTEX_ARRAY);
    for(int i = 0; i < (colors); i++)
    {
        switch (i) {
        case 0:
            glColor4f(line_color.r,line_color.g,line_color.b,line_opacity);
            break;
        default:
            glColor4f(fill_color.r,fill_color.g,fill_color.b,fill_opacity);
            break;
        }

        glVertexPointer(3, GL_FLOAT, 0,&q);
        if (filled)
            glDrawArrays(GL_QUADS, 0, 4);
        else
            glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glLineWidth(1.0f);
    for(int i = 0; i <  (int)Internal_List.size(); i++)
    {
        Internal_List.at(i)->Draw();
    }
}
int RectX::GetType(void)
{
    return 1;
}
void RectX::SetLineWidth(float w)
{
    lwidth = w;
}
void RectX::AddInternalPrimative(TPrimative *p)
{
    Internal_List.push_back(p);
}
void RectX::SetLineColor(TFloat c)
{
    line_color = c;
}

void RectX::SetFillColor(TFloat c)
{
    fill_color = c;
}
void RectX::SetLineOpacity(float o)
{
    line_opacity = o;
}

void RectX::SetFillOpacity(float o)
{
    fill_opacity = o;
}
