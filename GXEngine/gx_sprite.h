#ifndef GX_SPRITE_H
#define GX_SPRITE_H
#include <vector>

#include "gx_texture.h"
#include "gx_primatives.h"
using std::vector;

class SprMovement{
public:
    SprMovement(){
        ltm = -1;
        g   = false;
        jmp = false;
        fll = false;

    }

    ~SprMovement();
public:
    void Update(long t, Vec3 &p)
    {
        p = p;
        if (ltm==-1)
            ltm = t;
        if ((t-ltm)>30)
        {
            if (!jmp||g)
            {
                g=false;
                return;
            }
            if (pos.y==1)
            {
                float delta = (t - ltm)*0.001f;//1000.0f;
                vel += acc * delta;
                if (vel.y>0)
                    fll = true;
                pos += vel/2;

            }


            ltm = t;
        }
    }

public:
    bool jmp;//jumping
    bool fll;//falling
    bool g;  //tmp
    Vec3 pos;//position
    Vec3 acc;//acceleration
    Vec3 vel;//velocity
    long ltm;//last time

};

class SprAnimation
{
  public:
        SprAnimation(int __index=0,int __index_size=3,long __lasttime=0,long __updatetime=125,int __base=0,bool __loop=true)
        {
             LastTime=__lasttime;
             UpdateTime=__updatetime;
             Index=__index;
             IndexSize=__index_size;
             Base=__base;
             CurBase=Base;
             Loops=__loop;
             Anim=true;

        }
        SprAnimation(const SprAnimation &pass)
        {
            LastTime   = pass.LastTime;
            UpdateTime = pass.UpdateTime;
            Index      = pass.Index;
            IndexSize  = pass.IndexSize;
            Base       = pass.Base;
            CurBase    = pass.CurBase;
            Loops      = pass.Loops;
            Anim       = pass.Anim;
            Name       = pass.Name;
        }

        void Reset()
        {
            Index=0;
        }
        void SetName(string newname){Name=newname;}
        int GetCurrent(){return Base+Index;}
  public:
        long LastTime;
        long UpdateTime;
  public:
        int  Index;
        int  IndexSize;
        int  Base;
        int  CurBase;
  public:
        bool Loops;
        bool Anim;
  public:
        string Name;
};


class  TSprAnimList
{
public:
    TSprAnimList(const  TSprAnimList& in){
        Animations = in.Animations;
        ___cur = in.___cur;
    }

   TSprAnimList(){}
   TSprAnimList& operator=(const TSprAnimList& in) {
       Animations = in.Animations;
   //    Animations.clear();
  //     Animations.insert(Animations.begin(),in.Animations.begin(),in.Animations.end());
       ___cur = in.___cur;
       return (*this);
   }
   TSprAnimList& operator=(const TSprAnimList* in) {
       Animations = in->Animations;
 //      Animations.clear();
 //      Animations.insert(Animations.end(),in->Animations.begin(),in->Animations.end());
       ___cur = in->___cur;
       return (*this);
   }


   ~TSprAnimList(){Animations.empty();}

public:
   void Add(SprAnimation A)
   {
       Animations.push_back(A);
   }
   int Size()
   {
       return (int)Animations.size();
   }
   int LookUpViaName(string check)
   {
       for(int li=0;li<Size();li++)
       {
           if (GetCur(li).Name==check)
           {
               return li;
           }
       }
       return -1;
   }
   void SetCur(int C)
   {
       ___cur = C;
   }
   bool GetAnim(int c){
       return Animations.at(c).Anim;
   }

   SprAnimation &GetCur(int Index)
   {
       return Animations.at(Index);
   }
   vector<SprAnimation> &BigDaddy()
   {
       return Animations;
   }
private:
   int ___cur;
   vector<SprAnimation> Animations;
};

class GXSprite
{
public:
    GXSprite();
//    GXSprite(GXSprite *gxs);
    GXSprite(const GXSprite &gxs);
    GXSprite(string fn = "",ripdef *rc=NULL);
    GXSprite(GXTexture *tex, const GXSprite &g);
public: // Op Overload
    GXSprite& operator = (const GXSprite & gxs);
private:
    void StepAn(SprAnimation &input,long time);
public:
    void AddAnimation(int __index=0,int __index_size=3,long __lasttime=0,long __updatetime=125,int __base=0,bool __loop=true);
    void SetAnim(int i);
    void SetClip(Vec2 v);
    void SetClip(float w,float h);
    void SetSize(float w,float h);
    void SetCoord(float x,float y,float z);
    void Update(long t);
    void Draw(void);
    void CalculateExtTex(int index);
    void CalculateExtTexA(int index);
/**         Variables                 **/
private:
    void UpdateMovement(long t);
public:
    GXTexture *texture;
    TSprAnimList __Animations;
public:// Was Private
    QuikQuad   qm;
    QuikTexMap tm;
    Vec3 xyz;
    Vec3 velocity;
    Vec3 acceleration;
    float friction;
    Vec2 dim; // Width Height
    Vec2 clip;// Clip Width Height
    Vec2 div;
    int adx; // Current Animation
    int idx;
    bool flipped;
    bool jump;
    bool fall;
    float theata;
public:
    static int spriteCount;
private:
    long lasttime;

};

#endif // GX_SPRITE_H
