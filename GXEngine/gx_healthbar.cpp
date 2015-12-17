#include "gx_healthbar.h"
#include <iostream>
#include "font.h"
using std::cout;
using std::endl;

#define RECTX(m,x,y,w,h)             glBegin(m);\
                                      glVertex2f(x,y);\
                                      glVertex2f(x+w,y);\
                                      glVertex2f(x+w,y+h);\
                                      glVertex2f(x,y+h);\
                                   glEnd()

THealthBar::THealthBar(float _x,float _y,float _w,float _h,bool f):TPrimative()
{
    cout << __PRETTY_FUNCTION__<< "\n\tBegin\n"<<endl;
    x          = _x;
    y          = _y;
    w          = _w;
    h          = _h;
    filled     =  f;
    colors     = 1;
    SetMax(100);
    SetValue(100);
    SetBorderColor4f(1.0f,1.0f,1.0f,1.0f);
    SetColor4f(1.0f,1.0f,1.0f,1.0f);
    border_width = 2.2f;
 //   cout << __PRETTY_FUNCTION__<< "\n\tFinished\n"<<endl;
    caption = "";
    xz = 0;
    yz = 0;
    slider_pos = w;


}
void THealthBar::MoveXY(int _x,int _y)
{
    x = _x;
    y = _y;
}

void THealthBar::Update(MouseState ms)
{
    xz = ms.x;
    yz = ms.y;
    slider_pos = cur_value/100.0 * w;
}

bool THealthBar::Inside()
{
    if ((xz>=x)&&(xz<=(x+w))&&(yz>=y)&&(yz<=(y+h)))
        return true;
    return false;
}
/// Healthbar Draw Function

void THealthBar::Draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glColor3f(0,0,0);
    RECTX(GL_QUADS,x,y,w,h);
    glColor3f(fill.red,fill.green,fill.blue);
    RECTX(GL_QUADS,x,y,(w*(cur_value/max_value)),h);
    glColor3f(fill.red*0.92,fill.green*0.92,fill.blue*0.92);
    RECTX(GL_QUADS,x,y,(w*(cur_value/max_value)),(h/2));

   // glSetDrawColor(CL_PURPLE);
  //  RECTX(GL_QUADS,x+slider_pos-2,y,1+2,h);


    glLineWidth(border_width);
    glColor3fv(GetColor("gold"));

    //Inside()
    //if ()
//    if (1){
//        //glSetDrawColor(CL_PURPLE);
//        //RECTX(GL_LINE_LOOP,xz,y,1,h);

//        glSetDrawColor(CL_GOLD);

//    }else{
//        glSetDrawColor(CL_GREEN);
//    }
   // glSetDrawColor(CL_GOLD);
    RECTX(GL_LINE_LOOP,x,y,w,h);
    glLineWidth(1.0);
 //   glSetDrawColor(CL_PURPLE);
 //   RECTX(GL_QUADS,x+slider_pos-2,y,1+2,h);
    glColor3f(1,1,1);
    std::string sh = "caption";

    //int off = GetTextWidth("caption");
    //       FontDraw((char *)sh.c_str(),x+w/2+off,y+14);

    //printf("%d\n",off);
    glPopMatrix();
}
int THealthBar::GetType(void)
{
    return _pr_type_health_bar;
}
void THealthBar::SetMax(float M)
{
    max_value = M;
}

void THealthBar::SetValue(float V)
{
    if (V<=max_value)
        cur_value = V;
    else
        cur_value = max_value;
}
void THealthBar::SetColor4f(float r,float g,float b,float a)
{
      fill.Set(r,g,b,a);
}

void THealthBar::SetColor3f(float r,float g,float b)
{
    fill.Set(r,g,b,fill.alpha);
}

void THealthBar::SetBorderColor4f(float r,float g,float b,float a)
{
     fill.Set(r,g,b,a);
}

void THealthBar::SetBorderColor3f(float r,float g,float b)
{
    SetBorderColor4f(r,g,b,line_color.alpha);
}

void THealthBar::SetBorderSize(float s)
{
    border_width = s;
}
void THealthBar::SetCaption(char *newCaption)
{
   caption = newCaption;
}
