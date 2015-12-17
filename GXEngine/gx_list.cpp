#include "gx_list.h"

Tlist::Tlist()
{

}

Tlist::~Tlist()
{

}

void Tlist::Draw(void)
{
    for(auto &a:items)
    {
        a.itm_box.Draw(); /// Item Box
        a.itm_pic.Draw(); /// Item Pic
        a.itm_bck.Draw(); /// Item Back
        a.itm_name.Draw();
        a.itm_atk.Draw();
        a.itm_def.Draw();
        a.itm_per.Draw();
        a.itm_val.Draw();
    }
}
void Tlist::AddItem(TContext &itm)
{
    items.push_back(std::move(itm));
}
