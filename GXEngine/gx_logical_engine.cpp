//#include "../GXShader/Shader.h"
#include "gx_shader.h"
#include "gx_logical.h"
#include <functional>

#define LXXX
#ifdef UNREAL
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>
    #include <SDL2/SDL_thread.h>
#else
    #include <SDL/SDL.h>
#endif
#include "gx_sprite.h"
#include "gx_inputhandler.h"
#include "gx_collisions.h"
#include "gx_particle.h"
#include "gx_group.h"
#include <sstream>
#include "gx_document.h"

#include "gx_engine.h"
#include "gx_experiment.hxx"

extern TGraphic *Graph;
vector<TPrimative *> boxes;
extern volatile bool done;
extern volatile bool loaded;
extern SDL_GLContext  context;
extern SDL_Window    *hWindow;
extern MouseState   msx;
extern ShaderProgram *shader;
extern string text_input;
extern const uint8_t *keys;
extern THero Champion;
extern GXEmitter Emitter;

extern vector<GXSprite *> CheckList;

long long int enemy_health = 100000000000;
long long int enemy_hlt_mx = 100000000000;
long long int phase_1 = enemy_health / 4;
long long int phase_2 = phase_1 * 2;
long long int phase_3 = phase_1 * 3;

double pendingStats = 0;

void setOrtho(int width, int height,int s__x,int s__y)
{
       glViewport(s__x,s__y,width,height);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluOrtho2D(s__x,width,height,s__y);
}


static void Update()
{
//global_font.PrintText(10,10,1,"ooooooooooooo");
}

inline void InitateRaid(THealthBarEx *h,TGraphic *b0,TGraphic *b1,TGraphic *b2,TGraphic *b3)
{
    b0->visible = true;
    b1->visible = false;
    b2->visible = false;
    b3->visible = false;
    h->max_value  = enemy_hlt_mx;
    h->cur_value  = enemy_health;
    h->show_value = true;
}

inline void EXIT_BTN_STAT(TGraphic *_btn)
{
       if (_btn->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[STATS_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = false;
           Champion.hero_stats.EmptyPending();
           _btn->status = !_btn->status;
       }
}

inline void CONF_BTN_STAT(TGraphic *_btn)
{

       if (_btn->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[STATS_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = false;
           _btn->status = !_btn->status;
       }

}

inline void ENTR_BTN_STAT(TGraphic *_btn, TLabelEX *cpt)
{

       if (_btn->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           cpt->Text      = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[STATS_MODE]] = false;
           _btn->status = !_btn->status;
       }

}
inline void ENTR_BTN_BATTLE(TGraphic *_btn,THealthBarEx *h,TGraphic *b0,TGraphic *b1,TGraphic *b2,TGraphic *b3)
{

       if (_btn->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[BATTL_MODE]] = false;
           _btn->status = !_btn->status;
           InitateRaid(h,b0,b1,b2,b3);
       }

}
inline void EXIT_BTN_BATTLE(TGraphic *_btn)
{
       if (_btn->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = false;
           WorldEngine->elayers[WorldEngine->layer_bindings[BATTL_MODE]] = true;
           _btn->status = !_btn->status;
       }

}

inline void UpdateStats(){

    findHealthBarEx(boxes,"hbar")->AdjValMax(Champion.hero_stats.Honor, Champion.hero_stats.HonorMax);
    findHealthBarEx(boxes,"sbar")->AdjValMax(Champion.hero_stats.Stamina, Champion.hero_stats.StaminaMax);
    findHealthBarEx(boxes,"ebar")->AdjValMax(Champion.hero_stats.Energy, Champion.hero_stats.EnergyMax);
    findHealthBarEx(boxes,"hpbar")->AdjValMax(Champion.hero_stats.Health, Champion.hero_stats.HealthMax);
}


inline void STAT_BTN_PLUS_AND_MINUS(TGraphic *_bt1,TGraphic *_bt2,TLabelEX *_cp1,TLabelEX *_hdr1,std::string _tg1,double &working_stats,double &target,double &pending, double mod_gain=1.0, double mod_take=1.0)
{

        if (_bt1->status)
        {

            if (working_stats>0){
                working_stats-=1*mod_take;
                pending+=1*mod_gain;
                 std::string tp =  _tg1+" "+std::to_string((long long int)target);
                 if (pending>0.0)
                     tp+=" + ("+std::to_string((long long int)pending)+")";
                 _cp1->Text = tp;
                 _hdr1->Text = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);

            }
        }

        if (_bt2->status)
        {

            if (target>0){
                working_stats+=1*mod_take;
                pending-=1*mod_gain;
                    std::string tp =  _tg1+" "+std::to_string((long long int)target);
                    if (pending>0.0)
                        tp+=" + ("+std::to_string((long long int)pending)+")";
                _cp1->Text = tp;
                _hdr1->Text = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);

            }
        }
}

std::string get_usage_state(int us)
{
    switch (us) {
    case 0:
        return "sbar";
        break;
    case 1:
        return "ebar";
        break;
    case 2:
        return "hbar";
        break;
    default:
        break;
    }
    return "";
}


bool auto_engage = false;
std::string auto_target = "";
int auto_status = 0;
int auto_state = 0;
int disabled = -1;
bool in_raid = false;
int RenderScene(void *data)
{


    unused(data);

    int usage_state = 0;

    vector<TFormatedStringList> console_prev;
    static bool KYS[400] = {false,};
    //console_prev.push_back("");
    const int prev_limit = 10;
          int prev_item  = 0;


    Champion.hero_stats.Attack  = 130000;
    Champion.hero_stats.Defense = 60000;

    auto AddToConPrev = [&console_prev,&prev_item](TFormatedStringList s)->void
    {

        if ((int)console_prev.size()>=prev_limit){
            console_prev.erase(console_prev.end());
        }
        console_prev.insert(console_prev.begin(),s);
        prev_item = 0;
        //console_prev.push_back(s);
    };

    auto AddConExtention = [AddToConPrev](TFormatedStringList f)->void {
         const int lim = 564; //584
         TFormatedStringList list;
         int count = 0;
         for(size_t idx = 0; idx < f.formatedStrings.size(); idx++)
         {
             count += f.GetWItem(WorldEngine->FontManager.fonts[1],idx);
             if (count < lim)
             {
                 list.Push(f.formatedStrings.at(idx));
             }else
             {
                 AddToConPrev(list);
                 count = 0;
                 list.Empty();
                 list.Push(f.formatedStrings.at(idx));
             }
         }
         AddToConPrev(list);

    };

    auto DrawConPrev = [&console_prev]()->void
    {
        for(int i = 0; i < (int)console_prev.size(); i++){
            WorldEngine->FontManager.PrintText(35,window_h+1-80-(i)*17,1,console_prev[i]);
            //WorldEngine->FontManager.PrintText(35,window_h+1-80-(i)*17,1,"%s",console_prev[i].c_str());
        }
    };
    double lV = 1000000;

    auto Damage = [Champion,lV,AddConExtention](int u)->long long int{
            std::string ret;
            long long int res = getDamageX(Champion.hero_stats,Champion.invent,lV,0.05,u,ret);

            //cout<<"You dealt "<<format_str_w(std::to_string(res))<<" damage!\n";
            TFormatedStringList fsl;
            fsl.Push(TFormatedString(1,"cornflowerblue",Champion.SurName));
            fsl.Push(TFormatedString(1,"white"," dealt"));//" dealt  "
            fsl.Push(TFormatedString(1,"greenyellow"," "+format_str_w(std::to_string(res))+" dmg"));

            long long int xp_gained = u+rollD(u+(u==20)*60);
            long long int gd_gained = u*100;
            fsl.Push(TFormatedString(1,"white","! Lost 99 health. Gained"));
            fsl.Push(TFormatedString(1,"gold"," "+format_str_w(std::to_string(gd_gained))+" gold "));
            fsl.Push(TFormatedString(1,"white"," and"));
            fsl.Push(TFormatedString(1,"teal"," "+format_str_w(std::to_string(xp_gained))+" xp"));
            fsl.Push(TFormatedString(1,"white","!"));
            Champion.hero_stats.Money += gd_gained;
            Champion.hero_stats.Experience += (double)xp_gained;
            if (Champion.hero_stats.Experience>=Champion.hero_stats.ToNextLevel)
            {
                Champion.hero_stats.Experience = 0;
                Champion.hero_stats.ToNextLevel+=Champion.hero_stats.Stamina*2+Champion.hero_stats.Energy-29+Champion.hero_stats.Level;
                findHealthBarEx(boxes,"xbar")->SetMax(Champion.hero_stats.ToNextLevel);
                Champion.hero_stats.Level++;
                Champion.hero_stats.Honor++;
                findHealthBarEx(boxes,"sbar")->ResetAndMax(Champion.hero_stats.Stamina);
                findHealthBarEx(boxes,"ebar")->ResetAndMax(Champion.hero_stats.Energy);
                findHealthBarEx(boxes,"hbar")->ResetAndMax(Champion.hero_stats.Honor);
                Champion.hero_stats.AvailableStat += 7;

            }
            findHealthBarEx(boxes,"xbar")->SetValue(Champion.hero_stats.Experience);
            //ret = "You dealt " + format_str_w(std::to_string(res)) + " "  + ret + " dmg";
            //AddToConPrev(fsl);
            AddConExtention(fsl);
            return res;
    };


    while(!loaded)
    {
        SDL_Delay( 100 );
    }

    float hue = 250.0f;
    float sat = 1.0f;
    std::cout << "==Registering Components==\n";

    TLabelEX *gold_caption    = findLabelBox(boxes,"gold_cap");
    THealthBarEx *honor_bar   = findHealthBarEx(boxes,"hbar");
    THealthBarEx *stamina_bar = findHealthBarEx(boxes,"sbar");
    THealthBarEx *energy_bar  = findHealthBarEx(boxes,"ebar");
    THealthBarEx *xp_bar      = findHealthBarEx(boxes,"xbar");
    THealthBarEx *hp_bar      = findHealthBarEx(boxes,"hpbar");
    THealthBarEx *enemy_bar   = findHealthBarEx(boxes,"health_bar");
    /// Stat Caption
    TLabelEX *hd_stat_cap     = findLabelBox(boxes,"[HDR_CP]");
    TLabelEX *ak_stat_cap     = findLabelBox(boxes,"[ATK_STAT_CP]");
    TLabelEX *df_stat_cap     = findLabelBox(boxes,"[DEF_STAT_CP]");
    TLabelEX *hl_stat_cap     = findLabelBox(boxes,"[HLT_STAT_CP]");
    TLabelEX *en_stat_cap     = findLabelBox(boxes,"[ENG_STAT_CP]");
    TLabelEX *st_stat_cap     = findLabelBox(boxes,"[STM_STAT_CP]");
    TLabelEX *pr_stat_cap     = findLabelBox(boxes,"[PER_STAT_CP]");
    /// Battle Buttons
    TGraphic *bt_20_usage     = findGraphic(boxes,"[20_ATK]");
    TGraphic *bt_05_usage     = findGraphic(boxes,"[5_ATK]");
    TGraphic *bt_01_usage     = findGraphic(boxes,"[1_ATK]");
    TGraphic *bt_auto_swp     = findGraphic(boxes,"auto_swap");
    /// Stat Add Button Collection
    TGraphic *ak_stat_add     = findGraphic(boxes,"[ATK_STAT_AD]");
    TGraphic *df_stat_add     = findGraphic(boxes,"[DEF_STAT_AD]");
    TGraphic *hl_stat_add     = findGraphic(boxes,"[HLT_STAT_AD]");
    TGraphic *en_stat_add     = findGraphic(boxes,"[ENG_STAT_AD]");
    TGraphic *st_stat_add     = findGraphic(boxes,"[STM_STAT_AD]");
    TGraphic *pr_stat_add     = findGraphic(boxes,"[PER_STAT_AD]");
    /// Stat Minus Button Collection
    TGraphic *ak_stat_dec     = findGraphic(boxes,"[ATK_STAT_MN]");
    TGraphic *df_stat_dec     = findGraphic(boxes,"[DEF_STAT_MN]");
    TGraphic *hl_stat_dec     = findGraphic(boxes,"[HLT_STAT_MN]");
    TGraphic *en_stat_dec     = findGraphic(boxes,"[ENG_STAT_MN]");
    TGraphic *st_stat_dec     = findGraphic(boxes,"[STM_STAT_MN]");
    TGraphic *pr_stat_dec     = findGraphic(boxes,"[PER_STAT_MN]");
    /// Misc Buttons
    TGraphic *stat_ext_bt     = findGraphic(boxes,"[STAT_EXIT_BTN]");
    TGraphic *stat_ent_bt     = findGraphic(boxes,"[STAT_ENTER]");
    TGraphic *stat_cnf_bt     = findGraphic(boxes,"[STAT_CONFIRM]");
    TGraphic *raid_ent_bt     = findGraphic(boxes,"[RAID_ENTER]");
    ///
    TGraphic *raid_tgt_01     = findGraphic(boxes,"boss1");
    TGraphic *raid_tgt_02     = findGraphic(boxes,"boss2");
    TGraphic *raid_tgt_03     = findGraphic(boxes,"boss3");
    TGraphic *raid_tgt_04     = findGraphic(boxes,"boss4");
    ///
    TGraphic *raid_swp_bt     = findGraphic(boxes,"slot_swap");
    TGraphic *raid_rst_bt     = findGraphic(boxes,"restore1");
    std::cout << "==Registered  Components==\n";
    gold_caption->SetSize((size_t)(20*0.8));
    gold_caption->Text = "0";
    gold_caption->SetAlignment(GX_LB_ALIGN_LEFT);
    honor_bar->ResetAndMax(Champion.hero_stats.Honor);
    stamina_bar->ResetAndMax(Champion.hero_stats.Stamina);
    energy_bar->ResetAndMax(Champion.hero_stats.Energy);
    honor_bar->EnableValueType(true,1);
    stamina_bar->EnableValueType(true,1);
    energy_bar->EnableValueType(true,1);

    Champion.hero_stats.ToNextLevel = 4;
    xp_bar->ResetAndMax(Champion.hero_stats.ToNextLevel);
    xp_bar->cur_value = Champion.hero_stats.Experience;
    xp_bar->EnableValueType(true,2);
    hp_bar->ResetAndMax(Champion.hero_stats.Health);
    hp_bar->EnableValueType(true,1);
    Champion.hero_stats.AvailableStat = 100;
    double pendingStats = 0;
    hd_stat_cap->Text      = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);
    ak_stat_cap->Text = "Attack "+std::to_string((long long int)Champion.hero_stats.Attack);
    df_stat_cap->Text = "Defense "+std::to_string((long long int)Champion.hero_stats.Defense);
    hl_stat_cap->Text = "Health "+std::to_string((long long int)Champion.hero_stats.Health);
    en_stat_cap->Text = "Energy "+std::to_string((long long int)Champion.hero_stats.Energy);
    st_stat_cap->Text = "Stamina "+std::to_string((long long int)Champion.hero_stats.Stamina);
    pr_stat_cap->Text = "Perception "+std::to_string((long long int)Champion.hero_stats.Perception);

    auto UpdateStatLabel = [&hd_stat_cap,&ak_stat_cap,&df_stat_cap,&hl_stat_cap,&en_stat_cap,&st_stat_cap,&pr_stat_cap]()->void
    {
        hd_stat_cap->Text = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);
        ak_stat_cap->Text = "Attack "+std::to_string((long long int)Champion.hero_stats.Attack);
        df_stat_cap->Text = "Defense "+std::to_string((long long int)Champion.hero_stats.Defense);
        hl_stat_cap->Text = "Health "+std::to_string((long long int)Champion.hero_stats.Health);
        en_stat_cap->Text = "Energy "+std::to_string((long long int)Champion.hero_stats.Energy);
        st_stat_cap->Text = "Stamina "+std::to_string((long long int)Champion.hero_stats.Stamina);
        pr_stat_cap->Text = "Perception "+std::to_string((long long int)Champion.hero_stats.Perception);

    };


    std::cout <<  "Entering Render Loop" << std::endl;
    for(;;)
    {
    if (done)
        break;
    SDL_GL_MakeCurrent(hWindow,context);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glViewport(0,0,window_w,window_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,window_w,window_h,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

#ifdef EXTRA
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
#endif

    glPushMatrix();
    /**
      This CAN be optimized
    **/
    if (loaded){
        for(auto &_layers:WorldEngine->layers)
        {
            for(auto &primative:_layers)
            {
                if (!WorldEngine->LayerDisabled(primative->layer)){
                    if (primative->GetType()==_pr_type_rect)
                    {
                        RectX *tmp = (RectX *)primative;
                        tmp->Update(msx);
                        tmp->Draw();

                    }else if (primative->GetType()==_pr_type_rect_adv)
                    {
                        RectXAdv *tmp = (RectXAdv *)primative;
                        tmp->Update(msx);
                        tmp->Draw();
                    }else if (primative->GetType()==_pr_type_health_bar)
                    {
                        THealthBar *tmp = (THealthBar *)primative;
                        tmp->Update(msx);
                        tmp->Draw();

                    }else if (primative->GetType()==_pr_type_health_bar_ex)
                    {
                        THealthBarEx *tmp = (THealthBarEx *)primative;
                        tmp->Update(msx);
                        tmp->Draw();

                    }
                    else if(primative->GetType()==_pr_type_caption)
                    {
                        GXCaption *tcap = (GXCaption *)primative;
                        tcap->Update(msx);
                        tcap->Draw();
                    }
                    else if(primative->GetType()==_pr_type_lb_box)
                    {
                        GXLabelBox *tcap = (GXLabelBox *)primative;
                        tcap->Update(msx);
                        tcap->Draw();
                    }
                    else if(primative->GetType()==_pr_type_graphic)
                    {
                        TGraphic *tcap = (TGraphic *)primative;
                        tcap->Update(msx);
                        tcap->Draw();
                    }
                    else if(primative->GetType()==_pr_type_group)
                    {
                        TGroup *tcap = (TGroup *)primative;
                        tcap->Update(msx);
                        tcap->Draw();
                    }
                    else if(primative->GetType()==_pr_type_menu)
                    {
                        gx_menu *tcap = (gx_menu *)primative;
                        tcap->Update(msx);
                        tcap->Draw();
                    }
                }
            }
        }

        /// Render Console Output
        if (!WorldEngine->elayers[WorldEngine->layer_bindings[BATTL_MODE]]) {
            DrawConPrev();
        }
    }
    else
    {
        fprintf(stdout,"no render content\n");
    }



    if (!WorldEngine->elayers[WorldEngine->layer_bindings[BATTL_MODE]]) {
/// Update Stuff
///   added delta check
    if (enemy_health<phase_3){
        if(enemy_health<phase_2)
        {
            if (enemy_health<phase_1)
            {
                raid_tgt_01->visible = false;
                raid_tgt_02->visible = false;
                raid_tgt_03->visible = false;
                raid_tgt_04->visible = true;
            }
            raid_tgt_01->visible = false;
            raid_tgt_02->visible = false;
            raid_tgt_03->visible = true;
        }
        raid_tgt_01->visible = false;
        raid_tgt_02->visible = true;

    }else{
        raid_tgt_01->visible = true;
        raid_tgt_02->visible = false;

    }
    Update();
    if (raid_swp_bt->status)
    {
        usage_state+=1;
        if (usage_state>2)
            usage_state = 0;
        switch (usage_state)
        {
            case 0:
            {
                raid_swp_bt->caption ="Stamina";
                auto_state = 0;
                break;
            }
            case 1:
            {
                raid_swp_bt->caption ="Energy";
                auto_state = 1;
                break;
            }
            case 2:
            {
                raid_swp_bt->caption ="Honor";
                auto_state = 2;
                break;
            }
            default:
                break;
        }


    }
    if (raid_rst_bt->status)
    {
        honor_bar->cur_value   = honor_bar->max_value;
        energy_bar->cur_value  = energy_bar->max_value;
        stamina_bar->cur_value = stamina_bar->max_value;
    }
    if (bt_20_usage->status)
    {
        if (auto_engage)
        {
            auto_target = "[20_ATK]";
            auto_status = 20;
        }else{

        THealthBarEx *hb = findHealthBarEx(boxes,get_usage_state(usage_state));
        if (hb!=nullptr)
        {
            int ixi = hb->Decrement(20.0f);
            if (ixi!=-1)
            {
                enemy_health-=Damage(20);
                if (enemy_health<0)
                    enemy_health=0;
                std::cout <<" decrement\n";
            }else
            {
                std::cout << "Not Enough\n";
            }

            //hb->cur_value-=20;
        }
        }
    }
    if (bt_05_usage->status)
    {
        if (auto_engage)
        {
            auto_target = "[5_ATK]";
            auto_status = 5;
        }else
        {

        THealthBarEx *hb = findHealthBarEx(boxes,get_usage_state(usage_state));
        if (hb!=nullptr)
        {
            int ixi = hb->Decrement(5.0f);
            if (ixi!=-1)
            {
                enemy_health-=Damage(5);
                if (enemy_health<0)
                    enemy_health=0;
                std::cout <<" decrement\n";
            }else
            {
                std::cout << "Not Enough\n";
            }

            //hb->cur_value-=20;
        }
        }
    }
    if (bt_01_usage->status)
    {
        if (auto_engage)
        {
            auto_target = "[1_ATK]";
            auto_status = 1;
        }else
        {

        THealthBarEx *hb = findHealthBarEx(boxes,get_usage_state(usage_state));

        if (hb!=nullptr)
        {
            int ixi = hb->Decrement(1.0f);
            if (ixi!=-1)
            {
                enemy_health-=Damage(1);
                if (enemy_health<0)
                    enemy_health=0;
                std::cout <<" decrement\n";
            }else
            {
                std::cout << "Not Enough\n";
            }

            //hb->cur_value-=20;
        }
        }
    }
    if (bt_auto_swp->status)
    {
        auto_engage ^= true;
    }

    if (auto_engage)
    {
        //std::cout<< "aengage__\n";
        if (auto_target!="")
        {
            THealthBarEx *hb = findHealthBarEx(boxes,get_usage_state(auto_state));
            //std::cout<< "target__\t" << auto_target <<":"<<auto_status<< "\n";


            if (hb!=nullptr)
            {
                int ixi = hb->Decrement(auto_status);
                if (ixi!=-1)
                {
                    enemy_health-=Damage(auto_status);
                    if (enemy_health<0)
                        enemy_health=0;
                    //std::cout <<" decrement\n";
                }else
                {
                    //std::cout << "Not Enough\n";
                    auto_engage = false;
                }

                //hb->cur_value-=20;
            }else
            {
                std::cout<<"unable to locate\n";
            }
        }
        //else
            //std::cout<< "no target__\n";
    }

    if (enemy_bar!=nullptr)
    {
        enemy_bar->cur_value=enemy_health;
    }


    /*
    *
    *
    *
    *
    *
    */
    }
        else
    {

    }



    STAT_BTN_PLUS_AND_MINUS(ak_stat_add,ak_stat_dec,ak_stat_cap,hd_stat_cap,"Attack",Champion.hero_stats.AvailableStat,Champion.hero_stats.Attack,Champion.hero_stats.AtkPending);
    STAT_BTN_PLUS_AND_MINUS(df_stat_add,df_stat_dec,df_stat_cap,hd_stat_cap,"Defense",Champion.hero_stats.AvailableStat,Champion.hero_stats.Defense,Champion.hero_stats.AtkPending);
    STAT_BTN_PLUS_AND_MINUS(hl_stat_add,hl_stat_dec,hl_stat_cap,hd_stat_cap,"Health",Champion.hero_stats.AvailableStat,Champion.hero_stats.Health,Champion.hero_stats.HltPending,5.0);
    STAT_BTN_PLUS_AND_MINUS(en_stat_add,en_stat_dec,en_stat_cap,hd_stat_cap,"Energy",Champion.hero_stats.AvailableStat,Champion.hero_stats.Energy,Champion.hero_stats.EngPending);
    STAT_BTN_PLUS_AND_MINUS(st_stat_add,st_stat_dec,st_stat_cap,hd_stat_cap,"Stamina",Champion.hero_stats.AvailableStat,Champion.hero_stats.Stamina,Champion.hero_stats.StmPending,1.0,2.0);
    STAT_BTN_PLUS_AND_MINUS(pr_stat_add,pr_stat_dec,pr_stat_cap,hd_stat_cap,"Perception",Champion.hero_stats.AvailableStat,Champion.hero_stats.Perception,Champion.hero_stats.PerPending);

    EXIT_BTN_STAT(stat_ext_bt);
    ENTR_BTN_STAT(stat_ent_bt,hd_stat_cap);
    EXIT_BTN_BATTLE(stat_ent_bt);
    ENTR_BTN_BATTLE(raid_ent_bt,enemy_bar,raid_tgt_01,raid_tgt_02,raid_tgt_03,raid_tgt_04);
    if (stat_cnf_bt->status)
    {
        Champion.hero_stats.ApplyPending();
        UpdateStatLabel();
        honor_bar->AdjValMax(Champion.hero_stats.Honor, Champion.hero_stats.HonorMax);
        stamina_bar->AdjValMax(Champion.hero_stats.Stamina, Champion.hero_stats.StaminaMax);
        energy_bar->AdjValMax(Champion.hero_stats.Energy, Champion.hero_stats.EnergyMax);
        hp_bar->AdjValMax(Champion.hero_stats.Health, Champion.hero_stats.HealthMax);
    }



    if (keys!=nullptr){


    if (keys[SDL_SCANCODE_RETURN]&&!KYS[SDL_SCANCODE_RETURN])
    {

        hue+=1.0f;
        if (hue>360)
            hue = 0.0f;
        std::cout << "]>>" << hue << "\n";
        //findGraphic(boxes,"[20_ATK]")->color=ColorHSV(hue,1,1);
        KYS[SDL_SCANCODE_RETURN] = true;
    }else if (!keys[SDL_SCANCODE_RETURN]&&KYS[SDL_SCANCODE_RETURN])
    {
        KYS[SDL_SCANCODE_RETURN] = false;
    }
    if (keys[SDL_SCANCODE_A]&&!KYS[SDL_SCANCODE_A])
    {
        sat-=0.01;
        if (sat<-1.0)
            sat = 1.0f;
        std::cout << "]>>" << sat << "\n";
        //findGraphic(boxes,"[20_ATK]")->color=ColorHSV(hue,1,1);
        KYS[SDL_SCANCODE_A] = true;
    }else if (!keys[SDL_SCANCODE_A]&&KYS[SDL_SCANCODE_A])
    {
        KYS[SDL_SCANCODE_A] = false;
    }


    if (keys[SDL_SCANCODE_1]&&!KYS[SDL_SCANCODE_1])
    {
        WorldEngine->ToggleLayer(1);
        cout<<"\t"<<WorldEngine->elayers.at(1)<<endl;
        //findGraphic(boxes,"[20_ATK]")->color=ColorHSV(hue,1,1);
        KYS[SDL_SCANCODE_1] = true;
    }else if (!keys[SDL_SCANCODE_1]&&KYS[SDL_SCANCODE_1])
    {
        KYS[SDL_SCANCODE_1] = false;
    }
    if (keys[SDL_SCANCODE_2]&&!KYS[SDL_SCANCODE_2])
    {
        WorldEngine->ToggleLayer(2);
        cout<<"\t"<<WorldEngine->elayers.at(2)<<endl;
        //findGraphic(boxes,"[20_ATK]")->color=ColorHSV(hue,1,1);
        KYS[SDL_SCANCODE_2] = true;
    }else if (!keys[SDL_SCANCODE_2]&&KYS[SDL_SCANCODE_2])
    {
        KYS[SDL_SCANCODE_2] = false;
    }
    if (keys[SDL_SCANCODE_3]&&!KYS[SDL_SCANCODE_3])
    {
        WorldEngine->ToggleLayer(3);
        cout<<"\t"<<WorldEngine->elayers.at(3)<<endl;
        //findGraphic(boxes,"[20_ATK]")->color=ColorHSV(hue,1,1);
        KYS[SDL_SCANCODE_3] = true;
    }else if (!keys[SDL_SCANCODE_3]&&KYS[SDL_SCANCODE_3])
    {
        KYS[SDL_SCANCODE_3] = false;
    }




    }
    //Update_Cursor(WorldEngine->ticks());

    glPopMatrix();

    if(in_raid){
    WorldEngine->FontManager.PushSize(1);
    WorldEngine->FontManager.SetSize(1,25);
    glColor3f(0.0f,1.0f,0.0f);
    WorldEngine->FontManager.PrintTextCenter(window_w/2,92,1,"Old Foes");
    glColor3f(1.0f,1.0f,1.0f);
    WorldEngine->FontManager.PopSize(1);
    }

    WorldEngine->FontManager.PushSize(1);
    WorldEngine->FontManager.SetSize(1,15);
    WorldEngine->FontManager.PrintTextCenter(30,60,1,std::to_string((long long int)Champion.hero_stats.Level).c_str());
    WorldEngine->FontManager.PopSize(1);

    std::string p_gold = std::to_string((long long int)Champion.hero_stats.Money);
    gold_caption->Text = gtx::format_str_hulk(p_gold);
    //WorldEngine->FontManager.PrintText(window_w-200,20,1,p_gold.c_str());



    glMatrixMode(GL_MODELVIEW);
    SDL_GL_SwapWindow(hWindow);
    SDL_GL_MakeCurrent(hWindow,nullptr);
    //std::cout << rest << std::endl;
    KYS[SDL_SCANCODE_RETURN] = false;
    }
    SDL_Quit();

    exit(0);
    return 0;

}
