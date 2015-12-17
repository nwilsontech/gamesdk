#ifndef GX_TYPES_H
#define GX_TYPES_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>
#include <math.h>
#include <cmath>
#include <string>
#include "types.h"

//#include "vec_math.h"
#include <iostream>



#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))


float fclip(float a,float upper,float lower);
//#define flox(a) float x##a; float y##a;float z##a
//#define pout(a) std::cout << "x"<<a<<":"<<x##a<<" y"<<a<<":"<<y##a<<" z"<<a<<":"<< z##a<<"\n";
//#undef flox


class QuikQuad
{
public:
    QuikQuad(){
        LongSet(0.0,0.0,0.0,
                0.0,0.0,0.0,
                0.0,0.0,0.0,
                0.0,0.0,0.0);
    }
    QuikQuad(float x, float y, float z, float w, float h)
    {
        LongSet(x  ,y+h,z,
                x+w,y+h,z,
                x+w,y  ,z,
                x  ,y  ,z);
    }

public:
    void SmallSet(float a0,float b0,
                  float a1,float b1,
                  float a2,float b2,
                  float a3,float b3)
    {
        x0 = a0;y0 = b0;
        x1 = a1;y1 = b1;
        x2 = a2;y2 = b2;
        x3 = a3;y3 = b3;
    }

    void LongSet(float a0,float b0, float c0,
                 float a1,float b1, float c1,
                 float a2,float b2, float c2,
                 float a3,float b3, float c3)
    {
        x0 = a0;y0 = b0;z0 = c0;
        x1 = a1;y1 = b1;z1 = c1;
        x2 = a2;y2 = b2;z2 = c2;
        x3 = a3;y3 = b3;z3 = c3;
    }
public:
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}
public:
    float x0,y0,z0;
    float x1,y1,z1;
    float x2,y2,z2;
    float x3,y3,z3;
};

class QuikTexMap
{
public:
    QuikTexMap(){
        LongSet(0.0,0.0,
                0.0,0.0,
                0.0,0.0,
                0.0,0.0);
    }
    QuikTexMap(float x0, float y0,
               float x1, float y1,
               float x2, float y2,
               float x3, float y3)
    {
        LongSet(x0,y0,
                x1,y1,
                x2,y2,
                x3,y3);
    }

public:
    void LongSet(float a0,float b0,
                 float a1,float b1,
                 float a2,float b2,
                 float a3,float b3)
    {
        s0 = a0;r0 = b0;
        s1 = a1;r1 = b1;
        s2 = a2;r2 = b2;
        s3 = a3;r3 = b3;
    }
public:
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}
public:
    float s0,r0;
    float s1,r1;
    float s2,r2;
    float s3,r3;
};

class TColorFloat
{
public: // ctor dtor
    TColorFloat(){red = 0.0f;green = 0.0f; blue = 0.0f; alpha = 1.0f;}
    TColorFloat(float r, float g, float b){red = r;green = g; blue = b; alpha = 1.0f;}
    TColorFloat(float r,float g,float b, float a){red = r;green = g; blue = b; alpha = a;}
    TColorFloat(const TColorFloat &pass)
    {
        red = pass.red;  green = pass.green; blue  = pass.blue; alpha = pass.alpha;
    }
    TColorFloat(const float * pass)
    {
        red =*pass; green=*(pass+1);blue=*(pass+2);alpha=*(pass+3);
    }
public: // regular functions
    void Set(float r,float g,float b,float a){red = r;green = g; blue = b; alpha = a;}
    void Set(float r, float g, float b){red = r;green = g; blue = b;}
    void Set4f(float * pass){red =*pass; green=*(pass+1);blue=*(pass+2);alpha=*(pass+3);}
    void Set3f(float * pass){red =*pass; green=*(pass+1);blue=*(pass+2);}
public: // operator overloads
    TColorFloat& operator = (const TColorFloat & pass){
        this->red   = pass.red;
        this->green = pass.green;
        this->blue  = pass.blue;
        this->alpha = pass.alpha;
        return *this;
    }

    //unary operators
    TColorFloat operator*(TColorFloat pass){
        return TColorFloat(this->red*pass.red,this->green*pass.green,
                           this->blue*pass.blue,this->alpha*pass.alpha);
    }
    TColorFloat operator/(TColorFloat pass){
        return TColorFloat(this->red/pass.red,this->green/pass.green,
                           this->blue/pass.blue,this->alpha/pass.alpha);
    }
    TColorFloat operator *(float scale){
        return TColorFloat(this->red*scale,this->green*scale,this->blue*scale,this->alpha*scale);
    }
    TColorFloat operator /(float scale){
        return TColorFloat(this->red/scale,this->green/scale,this->blue/scale,this->alpha/scale);
    }
    TColorFloat operator -( TColorFloat pass) {
        //return TColorFloat(this->red-pass.red,this->green-pass.green,this->blue-pass.blue,this->alpha*-pass.alpha);
        return TColorFloat(
        CLAMP(red  -pass.red  ,1.0f,0.0f),
        CLAMP(green-pass.green,1.0f,0.0f),
        CLAMP(blue -pass.blue ,1.0f,0.0f),
        CLAMP(alpha-pass.alpha,1.0f,0.0f));
    }
    TColorFloat operator +( TColorFloat pass) {
        //return TColorFloat(this->red-pass.red,this->green-pass.green,this->blue-pass.blue,this->alpha*-pass.alpha);
        return TColorFloat(
        CLAMP(red  +pass.red  ,1.0f,0.0f),
        CLAMP(green+pass.green,1.0f,0.0f),
        CLAMP(blue +pass.blue ,1.0f,0.0f),
        CLAMP(alpha+pass.alpha,1.0f,0.0f));
    }
    TColorFloat& operator += (const TColorFloat & pass){
        *this = (*this + pass);
        return *this;
    }
    TColorFloat& operator -= (const TColorFloat & pass){
        *this = (*this - pass);
        return *this;
    }
    //unary operators
    TColorFloat operator -(void) const {return TColorFloat(-red,-green, -blue, -alpha);}
    TColorFloat operator +(void) const {return (*this);}

    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}
public: // variables
    float red;
    float green;
    float blue;
    float alpha;

};

//class TPoint2
//{
//   public:
//       TPoint2(int x = 0, int y = 0)
//       {
//           X=x;
//           Y=y;
//       }
//       TPoint2 operator+(const TPoint2 &p)
//       {
//          return TPoint2(p.X+X,p.Y+Y);
//       }
//       TPoint2 operator-(const TPoint2 &p)
//       {
//          return TPoint2(X-p.X,Y-p.Y);
//       }
//       TPoint2 operator*(const int num)
//       {
//          return TPoint2(X*num,Y*num);
//       }
//   public:
//         int X,Y;
//};
//struct rect
//{
//    int x;
//    int y;
//    int width;
//    int height;
//    rect(int xx = 0,int yy = 0,int ww = 0,int hh = 0)//Initializer
//    {
//        x=xx;y=yy;
//        width=ww;
//        height=hh;
//    }
//};


/*
** Hardware color macros
*/
#define ARGB(a,r,g,b)	((DWORD(a)<<24) + (DWORD(r)<<16) + (DWORD(g)<<8) + DWORD(b))
#define GETA(col)		((col)>>24)
#define GETR(col)		(((col)>>16) & 0xFF)
#define GETG(col)		(((col)>>8) & 0xFF)
#define GETB(col)		((col) & 0xFF)
#define SETA(col,a)		(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#define SETR(col,r)		(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SETG(col,g)		(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SETB(col,b)		(((col) & 0xFFFFFF00) + DWORD(b))



#endif // GX_TYPES_H
