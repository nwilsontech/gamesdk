#include "gx_rect_adv.h"
#include "gx_util.h"

/*

  +----------------------+
  | .................... |
  | .                  . |
  | .................... |
  +----------------------+
            |||(
            | |.\
            |...|
            \...\
             |..|
             |..|
             |..|
            /....\
            |....|
            \____/

    0)()0))()()()()()()()()())(()()(


*/

void RectXAdv::MoveXY(int _x,int _y)
{
    static int last_x = x;
    static int last_y = y;
    int dX = last_x - _x;
    int dY = last_y - _y;

    x = _x;
    y = _y;
    for(vector<RectXAdv *>::iterator it = children.begin();it!=children.end();it++)
    {

        (*it)->MoveXY((*it)->x-dX,(*it)->y-dY);

    }
    last_x = _x;
    last_y = _y;

}

RectXAdv::~RectXAdv()
{
    UnlinkParent();
    RemoveAllChildren();
}

RectXAdv::RectXAdv(float _x,float _y, float _w,float _h,float _t):TPrimative()
{
    x  = _x;
    y  = _y;
    w  = _w;
    h  = _h;
    t  = _t;
    bw = 1.0f;
    of = 5.0f;
    bc = GetColor("beige");//CL_BEIGE;
    _call = nullptr;
    switch ((int)t)
    {
        case 1:
        {
            ca = GetColor("white");
            cb = GetColor("white");
            cc = GetColor("lightgray");
            cd = GetColor("grey");
            break;
        }
        default:
        {
            ca = GetColor("white");;
            cb = GetColor("whitesmoke");
            cc = GetColor("lightgrey");
            cd = GetColor("grey");
            break;
        }
    }

    fill = true;
    parent = nullptr;
}

int RectXAdv::GetType()
{
    return 2;
}

void RectXAdv::SetUpdateFunc(UpdateCallback call)
{
    _call = call;
}

void RectXAdv::Update(MouseState ms)
{
    static int _f = 1;
    if (_call!=nullptr)
    {
        int tmp[5] = {0,};
        tmp[0] = x;
        tmp[1] = y;
        tmp[2] = w;
        tmp[3] = h;
        tmp[4] = _f;
        _call(tmp,5);
        x = tmp[0];
        y = tmp[1];
        w = tmp[2];
        h = tmp[3];
        _f = tmp[4];

    }
    for(vector<RectXAdv *>::iterator it = children.begin();it!=children.end();it++)
    {
        (*it)->Update(ms);
    }
//    if (ms.x>=x&&(ms.x<(x+w))&&(ms.y>=y)&&(ms.y<(y+h)))
//        inside = true;
//    else
//        inside = false;
}

bool RectXAdv::Inside()
{
    return inside;
}


void RectXAdv::SetColor(TFloat sc)
{
    bc = sc;
}
void RectXAdv::SetBorderColors(TFloat nca,
    TFloat ncb,
    TFloat ncc,
    TFloat ncd)
{
    ca = nca;
    cb = ncb;
    cc = ncc;
    cd = ncd;
}


RectXAdv *RectXAdv::GetParent()
{
    return parent;
}

void RectXAdv::SetWidth(float w)
{
    bw = w;
}

void RectXAdv::ResetBorderColor()
{
    switch ((int)t)
    {
        case 1:
        {
            ca = GetColor("white");
            cb = GetColor("white");
            cc = GetColor("lightgray");
            cd = GetColor("grey");
            break;
        }
        default:
        {
            ca = GetColor("white");;
            cb = GetColor("whitesmoke");
            cc = GetColor("lightgrey");
            cd = GetColor("grey");
            break;
        }
    }
}

void RectXAdv::ResetWidth()
{
    bw = 1.0f;
}

void RectXAdv::prvDraw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    if (t==1)
    {
        glColor3fv(bc);
        glBegin(GL_QUADS);
           glVertex2f(x+w+of ,y-of  );
           glVertex2f(x+w+of ,y+h+of);
           glVertex2f(x-of   ,y+h+of);
           glVertex2f(x-of   ,y-of  );
        glEnd();
        glColor3f(0,0,0);
        glBegin(GL_LINE_LOOP);
           glVertex2f(x+w+of ,y-of  );
           glVertex2f(x+w+of ,y+h+of);
           glVertex2f(x-of   ,y+h+of);
           glVertex2f(x-of   ,y-of  );
        glEnd();
        glLineWidth(bw);
        glBegin(GL_LINE_LOOP);
           glColor3fv(cb); glVertex2f(x+w,y);
           glColor3fv(cd); glVertex2f(x+w,y+h);
           glColor3fv(cc); glVertex2f(x,y+h);
           glColor3fv(ca); glVertex2f(x,y);
        glEnd();
        glLineWidth(1.0f);
    }else
    {
    if (fill)
        glBegin(GL_QUADS);
    else
        glBegin(GL_LINE_LOOP);
           glColor3fv(cb); glVertex2f(x+w,y);
           glColor3fv(cd); glVertex2f(x+w,y+h);
           glColor3fv(cc); glVertex2f(x,y+h);

           glColor3fv(ca); glVertex2f(x,y);
        glEnd();
    }
    glPopMatrix();
}

void RectXAdv::Draw()
{
    prvDraw();
    for(vector<RectXAdv *>::iterator it = children.begin();it!=children.end();it++)
    {
        (*it)->Draw();
    }
}
void RectXAdv::SetParent(RectXAdv *p)
{
    parent = p;
}

void RectXAdv::UnlinkParent()
{
    // If no parent is set return, because there is no point to unlink
    if (parent==nullptr)
        return;
    // we need to unlink our selves from the parent list
    parent->RemoveChild(this);
    // then set the parent back to nullptr
    SetParent(nullptr);
}

void RectXAdv::AddChild(RectXAdv *child)
{
    // First we need to add ourselves as the parent
    child->SetParent(this);
    // Next we push back the child into our list
    children.push_back(child);
}
void RectXAdv::RemoveChild(RectXAdv *child)
{
    // Here we loop through all the children
    for(vector<RectXAdv *>::iterator it = children.begin();it!=children.end();it++)
    {
        // once the target child matches an element in the list
        if (*it==child)
        {
            // we delete it and break from the loop
            delete *it;
            break;
        }
    }
}

void RectXAdv::RemoveAllChildren(void)
{
    for(vector<RectXAdv *>::iterator it = children.begin();it!=children.end();it++)
    {

            // First we unlink us from being the child
            (*it)->UnlinkParent();
            // Finally we delete the child from the list
            delete *it;

    }
}
