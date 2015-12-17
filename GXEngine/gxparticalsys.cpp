#include "gxparticalsys.h"

//GXParticalSys::GXParticalSys(int TYPE)
//{
//    /// Need to add type Emitter and Attracter

//}


//GXParticalSys::GXParticalSys::GXParticalSys(float x,float y,float life)
//{
//    pos.x = x;
//    pos.y = y;
//   _life  = life;
//    h     = 0;
//    s     = 0;
//    l     = 1.0;
//    angle = 0.0f;
//    id    = 0;
//}
//void GXParticalSys::GXParticalSys::SetDirection(float x, float y)
//{
//    dir.x = x;
//    dir.y = y;
//}
//void GXParticalSys::GXParticalSys::SetColor(float dcr, float dcg, float dcb, float dca)
//{
//    //color.Set(dcr,dcg,dcb,dca);
//}

//void GXParticalSys::GXParticalSys::Update()
//{
//    pos.x += dir.x;
//    pos.y += dir.y;
//    _life--;
//}
//rect GXParticalSys::GXParticalSys::GetBox()
//{
//    return rect(pos.x,pos.y,10,27);
//}
//void GXParticalSys::GXParticalSys::Kill()
//{
//    _life = 0;
//}


//GXParticalSys::GXParticalSys(std::string part_sprTex,int SetMaxSize){
//part_spr = new GSprite(part_sprTex);
//part_spr->SetSize(0,0,10,27);
//part_spr->SetClip(50,50);
//part_spr->CalcExtendedTex(0);
//MaxSize = SetMaxSize;
//Index   = 0;
//Count   = 0;
//lower_sat = 0.f;
//upper_sat = 0.f;
//}
//GXParticalSys::GXParticalSys(GSprite *tex, int SetMaxSize)
//{
//    part_spr = new GSprite(*tex);
//    part_spr->SetSize(0,0,10,27);
//    part_spr->SetClip(50,50);
//    part_spr->CalcExtendedTex(0);
//    MaxSize = SetMaxSize;
//    Index   = 0;
//    Count   = 0;
//    lower_sat = 0.f;
//    upper_sat = 0.f;
//}

//void GXParticalSys::SetClip(int c_width, int c_height)
//{
//    part_spr->SetClip(c_width,c_height);
//    part_spr->CalcExtendedTex(0);

//}
//void GXParticalSys::SetIndex(int i_dex)
//{
//    Index = i_dex;
//    part_spr->CalcExtendedTex(Index);
//}

//void GXParticalSys::Addpart_spr(float x,float y,float dx,float dy,float life)
//{
//    static int Louxt = 0;
//    if (Count>=MaxSize)
//        return;
//    part_sprs.push_back(GXParticalSys(x,y,life));


////    float Hue = 180,
////          Sat = (float)((30*((Louxt)))%360),
////          Lit = 1.;
////   // printf("hue: %f Sat:%f Lit: %f\n",Hue,Sat,Lit);
////    part_sprs.at((int)part_sprs.size()-1).h = Hue;
////    part_sprs.at((int)part_sprs.size()-1).s = Sat;
////    part_sprs.at((int)part_sprs.size()-1).l = Lit;
//    part_sprs.at((int)part_sprs.size()-1).angle = 180*atan(dy/dx)/_PI-90;

//    part_sprs.at((int)part_sprs.size()-1).SetDirection(dx,dy);
//    part_sprs.at((int)part_sprs.size()-1).id = Index;
//    Count++;
//    Louxt++;
//    Louxt%=13;
//}
//void GXParticalSys::Update()
//{
//if (Count<=0)
//{
//    return;

//}
//for(int idx = 0; idx < (int)part_sprs.size(); idx++)
//{
//    part_sprs.at(idx).Update();
//    if (part_sprs.at(idx)._life<0.0f)
//    {
//        part_sprs.erase(part_sprs.begin()+idx);
//        Count--;
//        if (idx!=0)
//        {
//            idx--;
//        }
//    }
//}
//}

////inline float randf()
////{
////    return ((float)(rand()%256)/256.0);
////}

//void GXParticalSys::Render()
//{

//    for(int idx = 0; idx < (int)part_sprs.size();idx++)
//    {

//        part_spr->CalcExtendedTex(part_sprs.at(idx).id);
////        part_spr->__dw_color = part_sprs.at(idx).color;
//        part_spr->theata = part_sprs.at(idx).angle;
//        //part_spr->motionblur = true;
//        part_spr->SetColorHSL(part_sprs.at(idx).h,part_sprs.at(idx).s,part_sprs.at(idx).l);
//        //part_spr->SetColorHSL(randf(),1,1);
//        part_spr->SetCoord(part_sprs.at(idx).pos.x,part_sprs.at(idx).pos.y);

//        part_spr->Render();
//        //part_spr->motionblur = false;

//    }
//   // glEnd();
//}
//bool GXParticalSys::IsEmpty()
//{
//    return ((int)part_sprs.size()>0) ? true : false;
//}
