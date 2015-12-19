#include "gx_experiment.hxx"
#include <iostream>
#include <cmath>
using namespace std;

#define NEW_ITEM_LIST *new vector<_pz_class_info>


std::random_device rd;

long long GenRandomNumber(std::random_device &in,int sz);

long long int rollD (int diesides)
{
    return GenRandomNumber(rd,diesides)+1;
}

long long int GenRandomNumber(std::random_device &in,int sz)
{

        std::mt19937 mt(in());
        std::uniform_int_distribution<int> dist(0, sz);
        return (dist(mt));
}

long long int GenRanXR(std::random_device &in,long long int   lo,long long int  hi)
{
    std::mt19937_64 mt(in());
    std::uniform_int_distribution<long long int> dist(lo, hi);
    return (dist(mt));
}

long long int getDamageX(const TStats &s,TEquipInv &iv, double LegionValue, double mod, double usd, std::string &ret)
{
    long long int vA=5,vD=2;
    long long int raid_lo,raid_hi;
    double equ = iv.CalcEquip();
    raid_lo = (long long int)((s.Attack*vA+s.Defense*vD+LegionValue+equ)*usd*(1.00));
    raid_hi = (long long int)((s.Attack*vA+s.Defense*vD+LegionValue+equ)*usd*(1.00 + mod));
    /// std::cout << "dbg_raid_lo\t" << raid_lo << "\tdbg_raid_hi\t" << raid_hi << "\n";
    long long int x = GenRanXR(rd,raid_lo,raid_hi);
    long long int pD = 0;
    long long int rX = 0;
    for(size_t a = 0; a < 9; a++)
    {
        pD = rollD(100);
        if (iv.active.at(a)!=NULL)
        {
            if (pD>(100-10)){
                rX+=GenRanXR(rd,100,500);;
                //std::cout<<iv.active.at(a)->proc_type<<std::endl;
            }
        }
    }
    x+=rX;
    long long int rD = rollD(100000);
    if (rD>99500)
    {
        if (rD>99750)
        {
            if (rD>99900)
            {
                x *= GenRanXR(rd,300,450);
                ret = "godlike";
                std::cout<<"godlike: "<<x<<"\n";
                return (x);
            }
            x *= GenRanXR(rd,50,100);

            std::cout<<"grevious\n";
            ret = "grevious";
            return (x);

        }
        x *= GenRanXR(rd,10,20);
        std::cout<<"critical\n";
        ret = "critical";
        return (x);
    }
    return x;
}


void TEquipInv::ShowEquipment()
{
    for(size_t i = 0; i < active.size(); i++)
        std::cout<<"-> "<<active.at(i)->name<<std::endl;
}

void TEquipInv::AddItem(TEquip *add)
{
    inv.push_back(add);
}

TEquipInv::TEquipInv()
{
    // Nothing to be done.
    actMain   = NULL;
    actOff    = NULL;
    actHelm   = NULL;
    actChest  = NULL;
    actGloves = NULL;
    actPants  = NULL;
    actBoots  = NULL;
    actRing   = NULL;
    actShield = NULL;
    active = std::vector<TEquip *>{actMain,actOff,actHelm,actChest,actGloves,actPants,actBoots,actRing,actShield};
}

void TEquipInv::SetMainhand(int i)
{
    actMain = inv.at(i);
    active.at(0)=actMain;
}
void TEquipInv::SetOffhand(int i)
{
    /** Note: cannot have both Offhand and sheild equiped **/
    actOff = inv.at(i);
    active.at(1)=actOff;
}
void TEquipInv::SetHelm(int i)
{
    actHelm = inv.at(i);
    active.at(2)=actHelm;
}
void TEquipInv::SetChest(int i)
{
    actChest = inv.at(i);
    active.at(3)=actChest;
}
void TEquipInv::SetGloves(int i)
{
    actGloves = inv.at(i);
    active.at(4)=actGloves;
}
void TEquipInv::SetPants(int i)
{
    actPants = inv.at(i);
    active.at(5)=actPants;
}
void TEquipInv::SetBoots(int i)
{
    actBoots = inv.at(i);
    active.at(6)=actBoots;
}
void TEquipInv::SetRing(int i)
{
    actRing = inv.at(i);
    active.at(7)=actRing;
}
void TEquipInv::SetShield(int i)
{
    actShield = inv.at(i);
    active.at(8)=actShield;
}

long long int TEquipInv::equTotal()
{   /// AV = attack + defence/4
    long long int ret = 0;
    for(size_t i = 0; i < active.size(); i++)
    {
        ret += active.at(i)->atk + active.at(i)->def;
    }
    return ret;
}

double TEquipInv::CalcEquip()
{
    double res_atk = 0.0;
    double res_def = 0.0;
    for(size_t i = 0; i < active.size(); i++)
    {
        if (active.at(i)!=NULL)
        {
            res_atk+=active.at(i)->atk;
            res_def+=active.at(i)->def;
        }
    }
    return (double)(3*res_atk+res_def);
}

namespace std {
    std::string format_str_w(std::string s,std::string notation)
    {
        std::string ret = s;
        size_t idc = s.size();
        size_t ddc = (size_t)ceil(((float)idc/3.0f)-1);
        size_t mdc = 1;
        if (idc>3){
            while (ddc>0)
            {
                ret = ret.substr(0,idc-3*mdc)+notation+ret.substr(idc-3*mdc,ret.length());
                mdc+=1;
                ddc--;
            }
        }
        return ret;
    }

}
namespace gtx {
    std::string format_str_hulk(std::string s)
    {
        if (s=="")
            return "";
        std::string ret = s;
        std::string char_list = "kmbtqqqqq";
        int size = (int)ret.size();
        int mag  = (size-1) / 3;
        ret = s.substr(0,((size-1) % 3)+1);
        if (mag>0){
            ret = ret + "." + s.substr(((size-1) % 3)+1,2);
            ret = ret + char_list.substr(mag-1,1);
        }
        //std::cout<<s<<"\t"<<(size-1)/3<<"\n";
        return ret;
    }
}
