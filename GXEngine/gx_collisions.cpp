#include "gx_collisions.h"

//QuikQuad

static void SortRect(QuikQuad &A)
{
    A = A;
//    int x,y,
//        w,h;
//    x = A.x;
//    y = A.y;
//    w = A.width;
//    h = A.height;
//    if (w<0)
//    {
//        x+=w;
//        w*=(-1);
//    }
//    if (h<0)
//    {
//        y+=h;
//        h*=(-1);
//    }
//    A.x = x;
//    A.y = y;
//    A.width  = w;
//    A.height = h;
}
static bool Within(float Begin,float End,float Test){
    return (Test>=Begin&&Test<=End);
}

bool rectOverlap2(QuikQuad aA,Vec3 aOff, QuikQuad bB,Vec3 bOff)
{
    bool kl,lk;
    QuikQuad A(aOff.x,aOff.y,0,aA.x1,aA.y0);
    QuikQuad B(bOff.x,bOff.y,0,bB.x1,bB.y0);
//    SortRect(A);///Fixes Errors
//    SortRect(B);///Fixes Errors
//    kl = ((A.x>=B.x&&A.x<=(B.x+B.width))||
//          (B.x>=A.x&&B.x<=(A.x+A.width)));
//    lk = ((A.y>=B.y&&A.y<=(B.y+B.height))||
//          (B.y>=A.y&&B.y<=(A.y+A.height)));
    kl = Within(B.x0,B.x1,A.x0)||Within(B.x0,B.x1,A.x1);
    lk = Within(B.y2,B.y1,A.y2)||Within(B.y2,B.y1,A.y1);
    return kl && lk;
}
