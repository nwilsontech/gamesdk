#include "gx_group.h"
#include "gx_document.h"
#include <utility>

TGroup::TGroup(std::string n,float tx,float ty):TPrimative()
{
    x = tx;
    y = ty;
    name = n;
}
void TGroup::Add(TPrimative *item)
{
    prims.push_back(item);
}

void TGroup::Draw(void)
{
    for(auto &prim:prims) /// Draw Elements, Update Offsets, Update MS
        {
            prim->UpdateOffset(x,y);
            prim->Update(_ms);
            prim->Draw();

        }
}

int  TGroup::GetType(void)
{
     return _pr_type_group;
}

void TGroup::MoveXY(int _x,int _y)
{
    unused(_x);
    unused(_y);
}

void TGroup::Update(MouseState ms)
{
    _ms = ms;
}

bool TGroup::Inside()
{
    return false;
}
