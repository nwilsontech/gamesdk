#include "gx_menu.h"
#include "gx_document.h"

gx_menu::gx_menu(float x, float y, float width, float height)
{
    xpos    = x;
    ypos    = y;
    wpos    = width;
    hpos    = height;
    bdrop   = QuikQuad(xpos,ypos,0.0,wpos,hpos);
    ndrop   = QuikQuad(xpos,ypos,0.0,wpos,50.0);
    visible = false;
    caption = new GXCaption(wpos/2.0,25.0,alias);
    back    = nullptr;
    _exit_btn = nullptr;
    caption->SetSize(20);
}


void gx_menu::Draw(void)
{
    if (!visible)
        return;
    //glScissor((int)xpos,(int)ypos+hpos,(int)wpos,(int)hpos);
    //glEnable(GL_SCISSOR_TEST);
    if (back!=nullptr) /// If no graphic Set use primative
    {
        back->x = xpos;
        back->y = ypos;
        back->SetSize(wpos,hpos);
        back->Draw();
    }
    else
    {
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glLineWidth(3.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    /// Draw Back Drop
    glVertexPointer(3, GL_FLOAT, 0,&bdrop);
    glColor4f(0.6,0.6,0.4,1.0);
    glDrawArrays(GL_QUADS, 0, 4);
    /// Draw Name Drop
    glVertexPointer(3, GL_FLOAT, 0,&ndrop);
    glColor4f(0.2,0.2,0.2,1.0);
    glDrawArrays(GL_QUADS, 0, 4);
    glColor4f(0.1,0.1,0.1,1.0);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    /// Draw Border
    glVertexPointer(3, GL_FLOAT, 0,&bdrop);
    glColor4f(0.1,0.1,0.1,1.0);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1.0f);
//cout<<xpos<<", "<<ypos<<", "<<wpos<<", "<<hpos<<"\n";

//    glEnable(GL_SCISSOR_BOX);
    }

    if (_exit_btn!=nullptr)
    {
        _exit_btn->Update(msx);
        _exit_btn->Draw();
    }else
    {
        cout<<"[[Pooo!]]\n";
    }

    //aption->Text = alias;
    //caption->x    = xpos;
    caption->y    = ypos+25.0;
    caption->Draw();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    int count = 0;
    for(auto &a:Items)
    {
        a.itm_box._oy = 149*count;
        a.itm_box.Draw(); /// Item Box
        a.itm_bck.Draw(); /// Item Pic
        a.itm_pic.Draw(); /// Item Back
//        a.itm_name.Draw();
//        a.itm_atk.Draw();
//        a.itm_def.Draw();
//        a.itm_per.Draw();
//        a.itm_val.Draw();
        count++;
    }
    glPopMatrix();

    glDisable(GL_SCISSOR_TEST);
//    glDisable(GL_TEXTURE_2D);

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glPushMatrix();
//    glLineWidth(2.0);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0,&bdrop);
//    glColor4f(0.7,0.7,0.2,1.0);
//    glDrawArrays(GL_LINE_LOOP, 0, 4);
//    glPopMatrix();
//    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glLineWidth(1.0f);


 //   glDisable(GL_SCISSOR_BOX);

}
int  gx_menu::GetType(void)
{
    return _pr_type_menu;
}
void gx_menu::MoveXY(int _x,int _y)
{
    unused(_x);
    unused(_y);
}
void gx_menu::Update(MouseState ms)
{
   /// If not visible no need to update
   /// just return
   if (!visible)
        return;
   msx = ms;
}
bool gx_menu::Inside()
{
    return false;
}

void gx_menu::SetAndUseBackgroundImage(string Image, float width, float height)
{
    if (Image.size()<1)
        return;
    back = new TGraphic(Image,width,height);

}


size_t gx_menu::AddMenuItem(TContext &item)
{
    Items.push_back(std::move(item));
    //Items.at(Size()-1).itm_bck.y+15;
    auto &working = Items.at(Size()-1);
    working.itm_bck.y+=9;

    //CenterWithinH(Items.at(Size()-1).itm_box,
                  //Items.at(Size()-1).itm_bck);

    CenterWithin(working.itm_bck,
                 working.itm_pic);

//    CenterWithinH(Items.at(Size()-1).itm_box,
//                  Items.at(Size()-1).itm_bck);

    return Size();
}
size_t gx_menu::Size(void)
{
    return (Items.size());
}
int    gx_menu::GetIndex(void)
{
    return 0;
}
TPrimative *gx_menu::GetIndexP(void)
{
    return nullptr;
}
void gx_menu::SetVisibility(bool ShowNo)
{
    visible = ShowNo;
}
bool gx_menu::visiblity()
{
    return visible;
}
void gx_menu::GetEXT(TGraphic *ext)
{
    _exit_btn = ext;
    cout << "[[Set Exit]]\n";
}
