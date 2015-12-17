#ifndef GX_GROUP_H
#define GX_GROUP_H

#include "gx_primatives.h"
#include <vector>
#include <string>

using std::vector;

class TGroup:public TPrimative
{
public:
    TGroup(std::string n,float tx, float ty);
public: //Virtuals
    virtual void Draw(void);
    virtual int  GetType(void);
    virtual void MoveXY(int _x,int _y);
    virtual void Update(MouseState ms);
    virtual bool Inside();
public:
    void Add(TPrimative *item);
public:
    float x,y;
    std::string name;
public:
    vector<TPrimative* > prims;
private:
    MouseState _ms;
};

#endif // GX_GROUP_H
