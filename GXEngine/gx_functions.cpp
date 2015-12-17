#include "gx_document.h"

TGraphic *findGraphic(primative_list &pl,string alias)
{
    for(auto &item: pl)
    {
        if (item->GetType()==_pr_type_graphic)
        {
            auto tmp = (TGraphic *)item;
            if (tmp->alias==alias)
               return tmp;
        }else if (item->GetType()==_pr_type_group)
        {
            auto grp = (TGroup *)item;
            for(auto &gItem:grp->prims)
            {
                if (gItem->GetType()==_pr_type_graphic)
                {
                    auto tmp = (TGraphic *)gItem;
                    if (tmp->alias==alias)
                        return tmp;

                }
            }
        }
    }
    return nullptr;
}


TLabel *findCaption(primative_list &pl,string alias)
{
    for(auto &item: pl)
    {
        if (item->GetType()==_pr_type_caption)
        {
            auto tmp = (TLabel *)item;
            if (tmp->alias==alias)
               return tmp;
        }else if (item->GetType()==_pr_type_group)
        {
            auto grp = (TGroup *)item;
            for(auto &gItem:grp->prims)
            {
                if (gItem->GetType()==_pr_type_caption)
                {
                    auto tmp = (TLabel *)gItem;
                    if (tmp->alias==alias)
                        return tmp;

                }
            }
        }
    }
    return nullptr;
}

TLabelEX *findLabelBox(primative_list &pl,string alias)
{
    for(auto &item: pl)
    {
        if (item->GetType()==_pr_type_lb_box)
        {
            auto tmp = (TLabelEX *)item;
            if (tmp->alias==alias)
               return tmp;
        }else if (item->GetType()==_pr_type_group)
        {
            auto grp = (TGroup *)item;
            for(auto &gItem:grp->prims)
            {
                if (gItem->GetType()==_pr_type_lb_box)
                {
                    auto tmp = (TLabelEX *)gItem;
                    if (tmp->alias==alias)
                        return tmp;

                }
            }
        }
    }

    return nullptr;
}




THealthBar *findHealthBar(primative_list &pl,string alias)
{
    printf(" find health called!!!\n");
    for(auto &item: pl)
    {
        printf("[]]]]] alias: %s\n",alias.c_str());
        if (item->GetType()==_pr_type_health_bar)
        {
            printf("[]]]]] loop\n");
            auto tmp = (THealthBar *)item;
            if (tmp->alias==alias){
                printf("found!!!\n");
               return tmp;
            }else{
                printf("alias: %s\n",tmp->alias.c_str());
            }
        }else if (item->GetType()==_pr_type_group)
        {
            auto grp = (TGroup *)item;
            for(auto &gItem:grp->prims)
            {
                if (gItem->GetType()==_pr_type_health_bar)
                {
                    auto tmp = (THealthBar *)gItem;
                    if (tmp->alias==alias)
                        return tmp;

                }
            }
        }

    }
    return nullptr;
}
THealthBarEx *findHealthBarEx(primative_list &pl,string alias)
{

    for(auto &item: pl)
    {

        if (item->GetType()==_pr_type_health_bar_ex)
        {

            auto tmp = (THealthBarEx *)item;
            if (tmp->alias==alias){

               return tmp;
            }
        }else if (item->GetType()==_pr_type_group)
        {
            auto grp = (TGroup *)item;
            for(auto &gItem:grp->prims)
            {
                if (gItem->GetType()==_pr_type_health_bar_ex)
                {
                    auto tmp = (THealthBarEx *)gItem;
                    if (tmp->alias==alias)
                        return tmp;

                }
            }
        }

    }
    return nullptr;
}


gx_menu *findMenu(primative_list &pl,string alias)
{
    for(auto &item: pl)
    {
        if (item->GetType()==_pr_type_menu)
        {
            auto tmp = (gx_menu *)item;
            if (tmp->alias.compare(alias)==0)
               return tmp;
        }
    }
    return nullptr;
}

void CenterWithin(TGraphic &ref,TGraphic &target)
{
    float ref_h = ref.h;
    float ref_w = ref.w;

    float dX = 0.0f;
    float dY = 0.0f;

    /// Diff
    if (target.w>ref_w)
        dX = target.w - ref_w;
    else
        dX = ref_w - target.w;
    dX /= 2;

    /// Diff
    if (target.h>ref_h)
        dY = target.h - ref_h;
    else
        dY = ref_h - target.h;
    dY /= 2;
    cout << "[[" << dX << ", " << dY << "]]\n";
    target.x += dX;
    target.y += dY+9;

    cout << "[[" << target.x << ", " << target.y << "]]\n";
    //target.qm = QuikQuad(target.x + dX,target.y + dY,0.0f,target.w - 0,target.h - 0);

}
void CenterWithinW(TGraphic &ref,TGraphic &target)
{
    float ref_w = ref.w;

    float dX = 0.0f;

    /// Diff
    if (target.w>ref_w)
        dX = target.w - ref_w;
    else
        dX = ref_w - target.w;
    dX /= 2;
    target.x += dX;
}

void CenterWithinH(TGraphic &ref,TGraphic &target)
{
    float ref_h = ref.h;

    float dY = 0.0f;

     /// Diff
    if (target.h>ref_h)
        dY = target.h - ref_h;
    else
        dY = ref_h - target.h;
    dY /= 2;
    cout << "[[" << ref_h << ", "<< target.h<<", " <<dY << "]]\n";
    target.y += dY/2;
}
