#pragma once
#ifndef GX_EXPERIMENT_HXX
#define GX_EXPERIMENT_HXX



#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <math.h>

using std::vector;
using std::string;
using std::map;

#define LSIZE(a) (int)a.size()
#define CLEAN(a)    a.clear();\
                    a.empty()

struct _pz_proc_info
{
    string name;
    double proc_rate;
    double proc_amt;
};

static vector<_pz_proc_info> TProcs = {
  {"Adandon hit", 0.125, 500000},
  {"Adandon hit", 0.125, 500000},
  {"Adandon hit", 0.125, 500000}
};




struct _pz_class_info
{
    string title;
    float energy_time;
    float stamina_time;
    float requirment;
};

static vector<_pz_class_info> TClass=
{
    {"Peon",180.0f,180.0f,0.0f},
    {"Battlemaster",120.0f,100.0f,6.0f},
    {"Wanderer",100.0f,120.0f,6.0f},
    {"Adventurer",110.0f,110.0f,6.0f},
    {"Warlord",110.0f,90.0f,100.0f},
    {"World-Strider",90.0f,110.0f,100.0f},
    {"Champion",100.0f,100.0f,100.0f},
    {"Warmaster",100.0f,80.0f,500.0f},
    {"Realm-Walker",80.0f,100.0f,500.0f},
    {"Hero",90.0f,90.0f,500.0f},
    {"Luminary",75.0f,75.0f,1000.0f},
    {"Immortal",45.0f,45.0f,2500.0f},
    {"Immortal Drake Slayer",35.0f,35.0f,5000.0f},
    {"God Slayer",20.0f,20.0f,10000.0f}

};



class TStats
{
public: // ctor & dtor
    TStats()
    {
        Init();
    }
    ~TStats(){}
public:
    void Init()
    {
        Health     = 100.0f;
        Experience = 0.0f;
        ToNextLevel= 4.0f;
        Attack     = 1.0f;
        Defense    = 1.0f;
        Perception = 0.0f;
        Energy     = 30.0f;
        Stamina    = 5.0f;
        Honor      = 0.0f;
        PC         = 0.0f;
        Money      = 0.0f;
        Level      = 1.0f;
        Class      = 0;
        AvailableStat = 0.0f;
    }

    void Print()
    {
        printf("Health %f\n"
               "Attack %f\n"
               "Defense %f\n"
               "Perception %f\n"
               "Energy %f\n"
               "Stamina %f\n"
               "Honor %f\n"
               "Level %f\n"
               "Class <%s>\n"
               ,Health,Attack,Defense,Perception,Energy,Stamina,Honor,Level,TClass[Class].title.c_str());
    }

public: //Variables
    double Health;
    double Experience;
    double ToNextLevel;
    //---------------
    double Attack;
    double Defense;
    double Perception;
    //---------------
    double Energy;
    double Stamina;
    double Honor;
    //---------------
    double PC;
    double Money;
    //---------------
    double Level;
    double AvailableStat;
    int   Class;
};

/*
    race:
        1 - Human
        2 - Elf
        3 - Oroc
        4 - Goblin
        5 - Gnome
        6 - Halfelf
        7 - Felpuur
        8 - Undead
        9 - Construct
        10 - Dwarf
        11 - Angel
        12 - Orc

    role:
        0 - Any
        1 - Tank
        2 - Melee
        3 - Ranged
        4 - Healer
        5 - Special

    source:
        0 - Any
        1 - Strength
        2 - Agility
        3 - Intellect
        4 - Wisdom
        5 - Special

 */



class TTroop
{
public:
    TTroop(string nm,int rc,int rl, int src)
    {
        name   = nm;
        race   = rc;
        role   = rl;
        source = src;
    }

public:
    string name;
    string image_url;
public:
    int race;
    int role;
    int source;
};

class TGeneral
{
public:
    TGeneral(string nm,int rc,int rl, int src)
    {
        name   = nm;
        race   = rc;
        role   = rl;
        source = src;
    }
public:
    string name;
    string image_url;
public:
    int race;
    int role;
    int source;

};


class TLegion
{
public:

public:

};
/** Begin Equip Info **/
/**
 * @brief The TEquip class
 *
 * equipType Values
 *
     MAINHAND = 1
     OFFHAND  = 2
     HELM     = 3
     CHEST    = 4
     GLOVES   = 5
     PANTS    = 6
     BOOTS    = 7
     RING     = 8
     SHIELD   = 9
 *
 *
 */

class TEquip
{
public:
    TEquip()
    {
        name = "";
        image_url = "";
        proc_name = "";
        proc_desc = "";
        lore = "";
        atk = 0;
        def = 0;
        per = 0;
        sta = 0;
        eng = 0;
        hnr = 0;
        hlt = 0;
        equipType = 0;
        value_gold = 0;
        value_credits = 0;
        questReq = 0;
        rarity = 0;
        unique = 0;
        canEnchant = 0;
        proc_type = 0;
        proc_rate = 0;
    }
    void Print()
    {
std::cout<<"\t"<<name<<","<<
           image_url<<","<<
           proc_name<<","<<
           proc_desc<<","<<
           lore<<","<<
           atk<<","<<
           def<<","<<
           per<<","<<
           sta<<","<<
           eng<<","<<
           hnr<<","<<
           hlt<<","<<
           equipType<<","<<
           value_gold<<","<<
           value_credits<<","<<
           questReq<<","<<
           rarity<<","<<
           unique<<","<<
           canEnchant<<","<<
           proc_type<<","<<
           proc_rate<<std::endl;
    }

public:
    string name;
    string image_url;
    string proc_name;
    string proc_desc;
    string lore;
public:
    int atk; //Attack
    int def; //Defense
    int per; //Perception
    int sta; //Stamina
    int eng; //Energy
    int hnr; //Honor
    int hlt; //Health
    int equipType;
    int value_gold;    //Gold Cost
    int value_credits; //Premium Currency Cost
    int questReq;
    int rarity;
    int unique;
    int canEnchant;
    int proc_type;
    int proc_rate;

};

//struct _pz_equip_inv
//{
//    union{
//        struct{
//        TEquip *actMain;
//        TEquip *actOff;
//        TEquip *actHelm;
//        TEquip *actChest;
//        TEquip *actGloves;
//        TEquip *actPants;
//        TEquip *actBoots;
//        TEquip *actRing;
//        TEquip *actShield;
//        };
//        TEquip i[9];
//    };
//};

class TEquipInv
{
public:
    TEquipInv();
    void ShowEquipment();
    void AddItem(TEquip *add);
public:
    void SetMainhand(int i);
    void SetOffhand(int i);
    void SetHelm(int i);
    void SetChest(int i);
    void SetGloves(int i);
    void SetPants(int i);
    void SetBoots(int i);
    void SetRing(int i);
    void SetShield(int i);

public:
    long long int equTotal();
    double CalcEquip();
public:
    TEquip *actMain;
    TEquip *actOff;
    TEquip *actHelm;
    TEquip *actChest;
    TEquip *actGloves;
    TEquip *actPants;
    TEquip *actBoots;
    TEquip *actRing;
    TEquip *actShield;

public:
    vector<TEquip *> inv; //Change to a pointer 2/3/15
    vector<TEquip *> active;
};



long long int rollD(int diesides);

int getDamage(TStats &s, float LegionValue, float mod, float usd);
uint_fast64_t getDamageL(TStats &s, double lmod, double umod, double usd);
long long int getDamageX(const TStats &s,TEquipInv &iv, double LegionValue, double mod, double usd, std::string &ret);





/*
 *
 *
 *  Begin Hero Class
 *
 *
 *
 *
 */

class THero
{
public:
    THero(string HeroName="")
    {
        hero_stats.Init();
        SurName = HeroName;
        ID = 0x00;
    }
    void SetName(string HeroName="")
    {
        SurName = HeroName;
    }
    void PrintEquip()
    {
        std::cout<<"|||||||||||||||||||||||||\n";
        double res_atk = 0.0;
        double res_def = 0.0;
        for(size_t a = 0; a < 9; a++)
        {
            if (invent.active.at(a)!=NULL)
            {
                std::cout<<invent.active.at(a)->name<<std::endl;
                res_atk+=invent.active.at(a)->atk;
                res_def+=invent.active.at(a)->def;
            }
        }
        std::cout<<3*res_atk<<"::"<<res_def<<std::endl;
        std::cout<<"|||||||||||||||||||||||||\n";
    }
    double CalculateEquip(void)
    {
        double res_atk = 0.0;
        double res_def = 0.0;
        for(size_t a = 0; a < 9; a++)
        {
            if (invent.active.at(a)!=NULL)
            {
                res_atk+=invent.active.at(a)->atk;
                res_def+=invent.active.at(a)->def;
            }
        }
        return (3*res_atk+res_def);
    }

public:
    TStats hero_stats;
    TEquipInv invent;
    string SurName;
    int    ID;
};


/*
 *
 *
 *
 *
 *
 */
namespace std {
    std::string format_str_w(std::string s = "",std::string notation = ",");
}
namespace gtx {
    std::string format_str_hulk(std::string s);
}

#undef LSIZE
#undef CLEAN

#endif // GX_EXPERIMENT_HXX

