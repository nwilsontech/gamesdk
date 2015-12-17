#include "gx_ex_healthbar.h"
#include <iostream>
#include "gx_engine.h"
#include "gx_experiment.hxx"
#include "font.h"
using std::cout;
using std::endl;

#define RECTX(m,x,y,w,h)             glBegin(m);\
                                      glVertex2f(x,y);\
                                      glVertex2f(x+w,y);\
                                      glVertex2f(x+w,y+h);\
                                      glVertex2f(x,y+h);\
                                   glEnd()

THealthBarEx::THealthBarEx(std::string fn,float _x,float _y,float _w,float _h):TPrimative()
{
  //  cout << __PRETTY_FUNCTION__<< "\n\tBegin\n"<<endl;
    x          = _x;
    y          = _y;
    w          = _w;
    h          = _h;
    colors     = 1;
    SetMax(100);
    SetValue(100);
    xz = 0;
    yz = 0;
    slider_pos = w;
    show_value = false;
    tex = new GXTexture(fn);
    formated = false;
    value_type = 0;


}
void THealthBarEx::MoveXY(int _x,int _y)
{
    x = _x;
    y = _y;
}

void THealthBarEx::Update(MouseState ms)
{
    xz = ms.x;
    yz = ms.y;
    slider_pos = cur_value/100.0 * w;
}

bool THealthBarEx::Inside()
{
    if ((xz>=x)&&(xz<=(x+w))&&(yz>=y)&&(yz<=(y+h)))
        return true;
    return false;
}
/// Healthbar Draw Function

void THealthBarEx::Draw(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glPushMatrix();

    glTranslated(x,y,0);
    glDisable(GL_TEXTURE_2D);
    glColor3fv(GetColor("gold"));
    glBegin(GL_QUADS);
       glVertex2f(-1.0,h+1);
       glVertex2f(w+1,h+1);
       glVertex2f(w+1,-1.0);
       glVertex2f(-1,-1.0);
    glEnd();

    glColor3fv(GetColor("black"));
    glBegin(GL_QUADS);
       glVertex2f(0.0,h);
       glVertex2f(w,h);
       glVertex2f(w,0.0);
       glVertex2f(0.0,0.0);
    glEnd();
    glColor4f(1,1,1,1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,tex->texID);

    static float inw = (float)tex->width;
    float mxx = (w/inw)/(max_value/cur_value);
    glBegin(GL_QUADS);
       glTexCoord2f(0.0,1.0); glVertex2f(0.0,h);
       glTexCoord2f(mxx,1.0); glVertex2f((w*(cur_value/max_value)),h);
       glTexCoord2f(mxx,0.0); glVertex2f((w*(cur_value/max_value)),0);
       glTexCoord2f(0.0,0.0); glVertex2f(0,0);
    glEnd();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(1.0);

    if (show_value)
    {
        /*
         * format_str_w(std::to_string(cur_value)).c_str(),format_str_w(std::to_string(max_value)).c_str()
         */
        char buffer[512];
        if (value_type==0)
            sprintf(buffer,"%.0f/%.0f",(cur_value),(max_value));
        else if (value_type==1)
            sprintf(buffer,"%.0f",(cur_value));
        else
            sprintf(buffer,"%.0f",(max_value-cur_value));
        WorldEngine->FontManager.PushSize(1);
        WorldEngine->FontManager.SetSize(1,(int)(h*0.9));
        WorldEngine->FontManager.PrintTextCenter(x+w/2,y+h*0.9,1,buffer);
        WorldEngine->FontManager.PopSize(1);
    }
}
int THealthBarEx::GetType(void)
{
    return _pr_type_health_bar_ex;
}
void THealthBarEx::SetMax(double M)
{
    max_value = M;
}
void THealthBarEx::ResetAndMax(double M)
{
    SetMax(M);
    SetValue(M);
}

void THealthBarEx::SetValue(double V)
{
    if (V<=max_value)
        cur_value = V;
    else
        cur_value = max_value;
}
void THealthBarEx::EnableValueType(bool show, int type)
{
    show_value = show;
    value_type = type;
}

double THealthBarEx::Decrement(double dec){
    bool test = (cur_value-dec)>=0.0f;
    if (!test)
        return -1.0f;
    cur_value -= dec;
    return cur_value;

}
