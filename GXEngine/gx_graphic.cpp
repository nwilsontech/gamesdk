
#include "gx_shader.h"
#include "gx_graphic.h"
#include "gx_engine.h"

//#define GRAPHIC_DEBUG

#include <cmath>

//#define _PI 3.1415926535897932384626433832795f

constexpr double _PI = 3.1415926535897932384626433832795f;

const GLchar *vSource =
        "void main() {"
        "gl_Position = gl_Vertex;"
        "}";


const GLchar *fSource =
        "void main() {"
        "gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );"
        "}";

TGraphic::TGraphic(string fn, float xx, float yy):TPrimative()
{

    name     = fn;
    alias    = "";
    tex      = new GXTexture(fn);
    qm       = QuikQuad(0,0,0,tex->width,tex->height);
    tm       = QuikTexMap(0.0,1.0,
                          1.0,1.0,
                          1.0,0.0,
                          0.0,0.0);

    x        = xx;
    y        = yy;
    w        = tex->width;
    h        = tex->height;
    _clipw   = w;
    _cliph   = h;
    _index   = 0;
    theata   = 0;
    rotating = false;
    visible  = true;
    on_click = nullptr;
    center   = false;
    status   = false;
    color    = GetColor("white");
    caption  = "";
    cap_color = color;
    ///** AWESOME **///

//    VertexShader vertToon ("circ.vert");
//    FragmentShader fragToon ("circ.frag");
//    shader = new ShaderProgram ("dimple", vertToon, fragToon);



}

void TGraphic::SetClip(float cw,float ch)
{
    _clipw = cw;
    _cliph = ch;
}

void TGraphic::Draw(void)
{
    if (!visible)
        return;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    if (!((_clipw!=w)&&(_cliph!=h))){
        if (!rotating){
            CalculateExtTex(_index);
        }else
        {
            if (!((_clipw!=w/2)&&(_cliph!=h/2)))
            {
                CalculateExtTex(_index);
            }
        }

    }

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,tex->texID);
    glColor4f(color.r,color.g,color.b,1);
    //std::cout << color.r << ", " << color.b << ", " << color.g << "\n";
    glPushMatrix();
    float x0 = 0.0f,y0 = 0.0f;
    /// replacing rotating
    if (center)
    {
        x0 = w/2;
        y0 = h/2;
    }
    glTranslated(x-x0+_ox,y-y0+_oy,0);

//    if (center){
//        //glRotated(theata,0.0,0.0,1.0);
//        qm.SmallSet(-w/2, h/2,
//                     w/2, h/2,
//                     w/2,-h/2,
//                    -w/2,-h/2);
//    }else
//    {

//        qm.SmallSet(0, h,
//                    w, h,
//                    w, 0,
//                    0, 0);
//    }

    if (Inside()&&(click==1))
    {
        //ff9735
        glColor4ub(0xFF,0x97,0x35,0xFF);
        //glColor4f(1.0f,0.0f,0.0f,1.0f);
    }


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0,&qm);
    glTexCoordPointer(2,GL_FLOAT, 0,&tm);
    glDrawArrays(GL_QUADS, 0, 4);

#ifdef GRAPHIC_DEBUG
    glDisable(GL_TEXTURE_2D);
    glColor4f(1,1,1,1);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
#endif
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    if(caption!="")
    {
        //std::cout<< "rendering caption:" << caption << " \n";
        glColor3fv(cap_color);
        WorldEngine->FontManager.PrintTextCenter(x+w/2,y+h*0.6,1,caption.c_str());
        glColor3f(1.0,1.0,1.0);
    }
}


int  TGraphic::GetType(void)
{
    return _pr_type_graphic;
}

void TGraphic::MoveXY(int _x,int _y)
{
    unused(_x);unused(_y);
}

void TGraphic::Update(MouseState ms)
{

    xz=ms.x; yz=ms.y;

    if (Inside()&&(click==1))
    {
        if (ms.LeftButtonDown&&!lastMS.LeftButtonDown)
        {
            Click();
            status = true;

        }else
        {
            status = false;
        }
    }
    lastMS = ms;
    //unused(ms);
}

bool TGraphic::Inside()
{
    if ((xz>=(x+_ox))&&(xz<=((x+_ox)+w))&&
        (yz>=(y+_oy))&&(yz<=((y+_oy)+h)))
            return true;
    return false;

}
//Removed and droped down to primative class
//void TGraphic::SetAlias(string al)
//{
//    alias = al;
//}


void TGraphic::SetFocus(float xx, float yy)
{
    hot.x=xx;
    hot.y=yy;
}

void TGraphic::SetSize(float ww,float hh)
{
    w = ww;
    h = hh;    
    qm = QuikQuad(0,0,0,w,h);
}
void TGraphic::SetAngle(float angle)
{
    theata = angle;
}
void TGraphic::CalculateExtTex(int index)
{
    int  _tw = tex->width;
    int  _th = tex->height;

    float tDivX,tDivY;
    int eX = _tw/_clipw;
    tDivX = 1.0/(float)(_tw / _clipw);
    tDivY = 1.0/(float)(_th / _cliph);

    float cx =  (float)(index % (int)(eX))*tDivX;///(_tw / x);
    float cy =  (float)(index / (int)(eX))*tDivY;///((int)(_th / y));

    tm.LongSet(cx            ,cy+tDivY      ,
               cx+tDivX      ,cy+tDivY      ,
               cx+tDivX      ,cy,
               cx            ,cy);

}

void TGraphic::SetClickable(int i)
{
    click = i;
}
void TGraphic::SetOnclickFunc(UpdateCallback pass)
{
    on_click = pass;
}
void TGraphic::Click()
{

    if (on_click!=nullptr)
    {
        string args[1];
        args[0] = alias;
        on_click(args,1);
    }else{
       // fprintf(stdout,"[dbg_info](%s).(%s)\n",__FUNCTION__,alias.c_str());

        //debug_print(alias);
    }
}

///----------------------------------///

