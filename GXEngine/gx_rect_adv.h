#ifndef GX_RECT_ADV_H
#define GX_RECT_ADV_H
#include "gx_primatives.h"
#include <vector>

using std::vector;

class RectXAdv:public TPrimative
{
public: // ctor and dtor + virtuals
    RectXAdv(float _x,float _y, float _w,float _h,float _t);
    virtual ~RectXAdv();
    virtual int GetType(void);
    virtual void Draw(void);
    virtual void MoveXY(int _x,int _y);
    virtual void Update(MouseState ms);
    virtual bool Inside();

public: // Utility functions
    void SetColor(TFloat sc);
    void SetBorderColors(TFloat nca,
                         TFloat ncb,
                         TFloat ncc,
                         TFloat ncd);
    void SetWidth(float w);
    void ResetBorderColor(void);
    void ResetWidth(void);

public: // Noding Functions
    RectXAdv *GetParent();
    void SetParent(RectXAdv *p);
    void UnlinkParent();
    void AddChild(RectXAdv *child);
    void RemoveChild(RectXAdv *child);
    void RemoveAllChildren(void);

private:
    void prvDraw();
public:
    void SetUpdateFunc(UpdateCallback call);

public:
    float x,y,w,h;
    float t; // type
    float bw; // border width
    float of; // offset
    int opt0,opt1;
    TFloat ca,cb,cc,cd;
    TFloat bc;
    bool fill;
    bool inside;

public:
    RectXAdv *parent;

    vector<RectXAdv *> children;
private:
    UpdateCallback _call;
    /*
     *float border; // border width for type 1
     *\
     */
};

#endif // GX_RECT_ADV_H
