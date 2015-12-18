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

inline void EXIT_BTN_STAT(std::string _btn)
{
    if (findGraphic(boxes,_btn)!=nullptr)
    {
       if (findGraphic(boxes,_btn)->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[STATS_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = false;
           findGraphic(boxes,_btn)->status = !findGraphic(boxes,_btn)->status;
       }
    }

}
inline void ENTR_BTN_STAT(std::string _btn)
{
    if (findGraphic(boxes,_btn)!=nullptr)
    {
       if (findGraphic(boxes,_btn)->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[STATS_MODE]] = false;
           findGraphic(boxes,_btn)->status = !findGraphic(boxes,_btn)->status;
       }
    }

}
inline void ENTR_BTN_BATTLE(std::string _btn)
{
    if (findGraphic(boxes,_btn)!=nullptr)
    {
       if (findGraphic(boxes,_btn)->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = true;
           WorldEngine->elayers[WorldEngine->layer_bindings[BATTL_MODE]] = false;
           findGraphic(boxes,_btn)->status = !findGraphic(boxes,_btn)->status;
       }
    }

}
inline void EXIT_BTN_BATTLE(std::string _btn)
{
    if (findGraphic(boxes,_btn)!=nullptr)
    {
       if (findGraphic(boxes,_btn)->status)
       {
           std::cout<<__PRETTY_FUNCTION__<<"\n";
           WorldEngine->elayers[WorldEngine->layer_bindings[EQUIP_MODE]] = false;
           WorldEngine->elayers[WorldEngine->layer_bindings[BATTL_MODE]] = true;
           findGraphic(boxes,_btn)->status = !findGraphic(boxes,_btn)->status;
       }
    }

}

inline void STAT_BTN_PLUS_AND_MINUS(std::string _bt1,std::string _bt2,std::string _cp1,std::string _hdr1,std::string _tg1,double &working_stats,double &target)
{
    if (findGraphic(boxes,_bt1)!=nullptr)
    {
        auto *button =  findGraphic(boxes,_bt1);

        if (button->status)
        {
            //std::cout<<"Clicked\n";
            if (working_stats>0){
                working_stats--;
                target++;
                 if (findLabelBox(boxes,_cp1)!=nullptr)
                 {
                     findLabelBox(boxes,_cp1)->Text = _tg1+" "+std::to_string((long long int)target);
                 }
                 if (findLabelBox(boxes,_hdr1)!=nullptr)
                 {
                     findLabelBox(boxes,_hdr1)->Text = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);
                 }
            }
        }
    }
    if (findGraphic(boxes,_bt2)!=nullptr)
    {
        auto *button =  findGraphic(boxes,_bt2);
        if (button->status)
        {
           // std::cout<<"Clicked\n";
            if (target>0){
                working_stats++;
                target--;
                if (findLabelBox(boxes,_cp1)!=nullptr)
                {
                    findLabelBox(boxes,_cp1)->Text = _tg1+" "+std::to_string((long long int)target);
                }
                if (findLabelBox(boxes,_hdr1)!=nullptr)
                {
                    findLabelBox(boxes,_hdr1)->Text = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);
                }
            }
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

long long int enemy_health = 100000000000;
long long int phase_1 = enemy_health / 4;
long long int phase_2 = phase_1 * 2;
long long int phase_3 = phase_1 * 3;
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

    /// Initalize local
    std::string blinkingCursor = "|";
    //vector<string> console_prev;
    vector<TFormatedStringList> console_prev;
    static bool KYS[400] = {false,};
    //console_prev.push_back("");
    const int prev_limit = 10;
          int prev_item  = 0;


    Champion.hero_stats.Attack  = 130000;
    Champion.hero_stats.Defense = 60000;
    Champion.hero_stats.Honor   = 10000;
    Champion.hero_stats.Energy  = 10000;
    Champion.hero_stats.Stamina = 10000;
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

            long long int xp_gained = u+rollD(u);
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
    if(in_raid){
    findGraphic(boxes,"boss1")->visible = true;
    findGraphic(boxes,"boss2")->visible = false;
    findGraphic(boxes,"boss3")->visible = false;
    findGraphic(boxes,"boss4")->visible = false;
    findHealthBarEx(boxes,"health_bar")->max_value  = enemy_health;
    findHealthBarEx(boxes,"health_bar")->cur_value  = enemy_health;
    findHealthBarEx(boxes,"health_bar")->show_value = true;
    }
    //Champion.hero_stats.
    findHealthBarEx(boxes,"hbar")->ResetAndMax(Champion.hero_stats.Honor);
    findHealthBarEx(boxes,"sbar")->ResetAndMax(Champion.hero_stats.Stamina);
    findHealthBarEx(boxes,"ebar")->ResetAndMax(Champion.hero_stats.Energy);
    findHealthBarEx(boxes,"hbar")->EnableValueType(true,1);
    findHealthBarEx(boxes,"sbar")->EnableValueType(true,1);
    findHealthBarEx(boxes,"ebar")->EnableValueType(true,1);

    Champion.hero_stats.ToNextLevel = 4;
    findHealthBarEx(boxes,"xbar")->ResetAndMax(Champion.hero_stats.ToNextLevel);
    findHealthBarEx(boxes,"xbar")->EnableValueType(true,2);
    findHealthBarEx(boxes,"hpbar")->ResetAndMax(Champion.hero_stats.Health);
    findHealthBarEx(boxes,"hpbar")->EnableValueType(true,1);
    Champion.hero_stats.AvailableStat = 100;
    double pendingStats = 0;
    findLabelBox(boxes,"[HDR_CP]")->Text      = "Remaining Stat Points: "+std::to_string((long long int)Champion.hero_stats.AvailableStat);
    findLabelBox(boxes,"[ATK_STAT_CP]")->Text = "Attack "+std::to_string((long long int)Champion.hero_stats.Attack);
    findLabelBox(boxes,"[DEF_STAT_CP]")->Text = "Defense "+std::to_string((long long int)Champion.hero_stats.Defense);
    findLabelBox(boxes,"[HLT_STAT_CP]")->Text = "Health "+std::to_string((long long int)Champion.hero_stats.Health);
    findLabelBox(boxes,"[ENG_STAT_CP]")->Text = "Energy "+std::to_string((long long int)Champion.hero_stats.Energy);
    findLabelBox(boxes,"[STM_STAT_CP]")->Text = "Stamina "+std::to_string((long long int)Champion.hero_stats.Stamina);
    findLabelBox(boxes,"[PER_STAT_CP]")->Text = "Perception "+std::to_string((long long int)Champion.hero_stats.Perception);
    //std::function<void()> dx = Damage;
    std::cout <<  "Entering Render Loop" << std::endl;
    for(;;)
    {
        if (done)
            break;

    //// Really should add error checking here.
    SDL_GL_MakeCurrent(hWindow,context);
    //std::cout << rest << std::endl;
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
                /// Commenting Line Seems Redundant
                /// glColor4f(1.0f,1.0f,1.0f,1.0f);
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
                        /// glColor3f(1,1,1);
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
        DrawConPrev();
    }
    else
    {
        fprintf(stdout,"no render content\n");
    }



    if (in_raid) {
/// Update Stuff
///   added delta check
    if (enemy_health<phase_3){
        if(enemy_health<phase_2)
        {
            if (enemy_health<phase_1)
            {
                findGraphic(boxes,"boss1")->visible = false;
                findGraphic(boxes,"boss2")->visible = false;
                findGraphic(boxes,"boss3")->visible = false;
                findGraphic(boxes,"boss4")->visible = true;
            }
            findGraphic(boxes,"boss1")->visible = false;
            findGraphic(boxes,"boss2")->visible = false;
            findGraphic(boxes,"boss3")->visible = true;
        }
        findGraphic(boxes,"boss1")->visible = false;
        findGraphic(boxes,"boss2")->visible = true;

    }else{
        findGraphic(boxes,"boss1")->visible = true;
        findGraphic(boxes,"boss2")->visible = false;

    }
    Update();
    if (findGraphic(boxes,"slot_swap")->status)
    {
        usage_state+=1;
        if (usage_state>2)
            usage_state = 0;
        switch (usage_state)
        {
            case 0:
            {
                findGraphic(boxes,"slot_swap")->caption ="Stamina";
                auto_state = 0;
                break;
            }
            case 1:
            {
                findGraphic(boxes,"slot_swap")->caption ="Energy";
                auto_state = 1;
                break;
            }
            case 2:
            {
                findGraphic(boxes,"slot_swap")->caption ="Honor";
                auto_state = 2;
                break;
            }
            default:
                break;
        }


    }
    if (findGraphic(boxes,"restore1")->status)
    {
        findHealthBarEx(boxes,"hbar")->cur_value = findHealthBarEx(boxes,"hbar")->max_value;
        findHealthBarEx(boxes,"ebar")->cur_value = findHealthBarEx(boxes,"ebar")->max_value;
        findHealthBarEx(boxes,"sbar")->cur_value = findHealthBarEx(boxes,"sbar")->max_value;
    }
    if (findGraphic(boxes,"[20_ATK]")->status)
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
    if (findGraphic(boxes,"[5_ATK]")->status)
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
    if (findGraphic(boxes,"[1_ATK]")->status)
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
    if (findGraphic(boxes,"auto_swap")->status)
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


    THealthBarEx *hbx = findHealthBarEx(boxes,"health_bar");
    if (hbx!=nullptr)
    {
        hbx->cur_value=enemy_health;
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


    /*
     *
     *
     *
     * BEGIN event handler for status stats update
     *
     *
     *
     *
     */


    STAT_BTN_PLUS_AND_MINUS("[ATK_STAT_AD]","[ATK_STAT_MN]","[ATK_STAT_CP]","[HDR_CP]","Attack",Champion.hero_stats.AvailableStat,Champion.hero_stats.Attack);
    STAT_BTN_PLUS_AND_MINUS("[DEF_STAT_AD]","[DEF_STAT_MN]","[DEF_STAT_CP]","[HDR_CP]","Defense",Champion.hero_stats.AvailableStat,Champion.hero_stats.Defense);
    STAT_BTN_PLUS_AND_MINUS("[HLT_STAT_AD]","[HLT_STAT_MN]","[HLT_STAT_CP]","[HDR_CP]","Health",Champion.hero_stats.AvailableStat,Champion.hero_stats.Health);
    STAT_BTN_PLUS_AND_MINUS("[ENG_STAT_AD]","[ENG_STAT_MN]","[ENG_STAT_CP]","[HDR_CP]","Energy",Champion.hero_stats.AvailableStat,Champion.hero_stats.Energy);
    STAT_BTN_PLUS_AND_MINUS("[STM_STAT_AD]","[STM_STAT_MN]","[STM_STAT_CP]","[HDR_CP]","Stamina",Champion.hero_stats.AvailableStat,Champion.hero_stats.Stamina);
    STAT_BTN_PLUS_AND_MINUS("[PER_STAT_AD]","[PER_STAT_MN]","[PER_STAT_CP]","[HDR_CP]","Perception",Champion.hero_stats.AvailableStat,Champion.hero_stats.Perception);

    EXIT_BTN_STAT("[STAT_EXIT_BTN]");
    ENTR_BTN_STAT("[STAT_ENTER]");
    EXIT_BTN_BATTLE("[EXIT_RAID]");
    ENTR_BTN_BATTLE("[RAID_ENTER]");

    /*
     *
     *
     *
     *
     *
     *
     *
     *
     */


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
    WorldEngine->FontManager.SetSize(1,12);
    WorldEngine->FontManager.PrintTextCenter(30,60,1,std::to_string((long long int)Champion.hero_stats.Level).c_str());
    WorldEngine->FontManager.PopSize(1);

    std::string p_gold = "Gold:" +std::to_string((long long int)Champion.hero_stats.Money);
    WorldEngine->FontManager.PrintText(window_w-200,20,1,p_gold.c_str());



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
