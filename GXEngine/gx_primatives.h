#ifndef GX_PRIMATIVES_H
#define GX_PRIMATIVES_H

#include <vector>
#include <string>
#include <functional>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gx_simple_dbg.hxx"
#include "gx_color.h"
#include "types.h"
#include "gx_types.h"
using std::string;
using std::vector;

class TPrimative;

typedef void (*UpdateCallback)(void *v,int size);
typedef std::function<void()> Callback;
//using UpdateCallBack = (*)(int *v,int size); //C++14
typedef unsigned int uint32;
typedef vector<TPrimative *> primative_list;

enum PRIMATIVE_TYPE
{
    _pr_type_none,
    _pr_type_rect,
    _pr_type_rect_adv,
    _pr_type_health_bar,
    _pr_type_caption,
    _pr_type_lb_box,
    _pr_type_graphic,
    _pr_type_health_bar_ex,
    _pr_type_group,
    _pr_type_menu
};




#define PR_OBJECT     virtual int GetType(void);\
                             virtual void Draw(void);\
                             virtual void MoveXY(int _x,int _y);\
                             virtual void Update(MouseState ms);\
                             virtual bool Inside();


class TPrimative
{
public:
    TPrimative();
    virtual ~TPrimative();
public:
    virtual int GetType(void) = 0;
    virtual void Draw(void) = 0;
    virtual void MoveXY(int _x,int _y) = 0;
    virtual void Update(MouseState ms) = 0;
    virtual bool Inside() = 0;
    void SetAlias(string al);
    void UpdateOffset(float ox, float oy);
    //variables
public:
    int xz;
    int yz;
    float _ox;
    float _oy;
    string alias;
    int layer;

};


#endif // GX_PRIMATIVES_H
