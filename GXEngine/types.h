#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <cmath>
#define unused(x) (void)(x)



typedef unsigned char BYTE,UInt8,UCHAR;
typedef unsigned int  WORD,UInt32,UINT;
typedef unsigned long DWORD,DWORD32;
typedef unsigned long long DWORD64;

struct MouseState
{
    int LeftButtonDown;
    int RightButtonDown;
    int MiddleButtonDown;
    int x;
    int y;
    MouseState()
    {
        LeftButtonDown   = 0;
        RightButtonDown  = 0;
        MiddleButtonDown = 0;
        x = 0;
        y = 0;
    }
};

enum TZModes
{
    tz_none     = -1,
    tz_selecting = 0,
    tz_dragging  = 1,
    tz_setAI     = 2
};
template <class T>
class TVertex4l
{
public:
    TVertex4l()
    { v0=v1=v2=v3=T();}

    TVertex4l(T nV0, T nV1, T nV2, T nV3=0.0f)
    {	v0=nV0;	v1=nV1;	v2=nV2;	v3=nV3;	}

    TVertex4l(const T * rhs)
    {	v0=*rhs;	v1=*(rhs+1);	v2=*(rhs+2); v3=*(rhs+3);}

    TVertex4l(const TVertex4l & rhs)
    {	v0=rhs.v0;	v1=rhs.v1;	v2=rhs.v2;	v3=rhs.v3;}

    ~TVertex4l() {}	//empty

    void Set(T nV0, T nV1, T nV2, T nV3)
    {	v0=nV0;	v1=nV1;	v2=nV2;	v3=nV3;	}

    //accessors kept for compatability
    void SetV0(T nV0) {v0 = nV0;}
    void SetV1(T nV1) {v1 = nV1;}
    void SetV2(T nV2) {v2 = nV2;}
    void SetV3(T nV3) {v3 = nV3;}

    T GetV0() const {return v0;}	//public accessor functions
    T GetV1() const {return v1;}	//inline, const
    T GetV2() const {return v2;}
    T GetV3() const {return v3;}

    //linear interpolate
    //multiply by a float, eg 3*

    bool operator==(const TVertex4l & rhs) const;
    bool operator!=(const TVertex4l & rhs) const
    {	return !((*this)==rhs);	}

    //unary operators
    TVertex4l operator-(void) const {return TVertex4l(-v0,-v1, -v2, -v3);}
    TVertex4l operator+(void) const {return (*this);}

    //cast to pointer to float for glColor4fv etc
    operator T* () const {return (T*) this;}
    operator const T* () const {return (const T*) this;}

    //member variables
    T v0;
    T v1;
    T v2;
    T v3;
};


class TVertex4
{
public:
    //constructors
    TVertex4()
    {	v0=v1=v2=v3=0.0f;}

    TVertex4(float nV0, float nV1, float nV2, float nV3=0.0f)
    {	v0=nV0;	v1=nV1;	v2=nV2;	v3=nV3;	}

    TVertex4(const float * rhs)
    {	v0=*rhs;	v1=*(rhs+1);	v2=*(rhs+2); v3=*(rhs+3);}

    TVertex4(const TVertex4 & rhs)
    {	v0=rhs.v0;	v1=rhs.v1;	v2=rhs.v2;	v3=rhs.v3;}

    ~TVertex4() {}	//empty

    void Set(float nV0, float nV1, float nV2, float nV3=0.0f)
    {	v0=nV0;	v1=nV1;	v2=nV2;	v3=nV3;	}

    //accessors kept for compatability
    void SetV0(float nV0) {v0 = nV0;}
    void SetV1(float nV1) {v1 = nV1;}
    void SetV2(float nV2) {v2 = nV2;}
    void SetV3(float nV3) {v3 = nV3;}

    float GetV0() const {return v0;}	//public accessor functions
    float GetV1() const {return v1;}	//inline, const
    float GetV2() const {return v2;}
    float GetV3() const {return v3;}

    //linear interpolate
    //multiply by a float, eg 3*

    bool operator==(const TVertex4 & rhs) const;
    bool operator!=(const TVertex4 & rhs) const
    {	return !((*this)==rhs);	}

    //unary operators
    TVertex4 operator-(void) const {return TVertex4(-v0,-v1, -v2, -v3);}
    TVertex4 operator+(void) const {return (*this);}

    //cast to pointer to float for glColor4fv etc
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}

    //member variables
    float v0;
    float v1;
    float v2;
    float v3;
};

class TVertex2
{
public:
    //constructors
    TVertex2()
    {	v0=v1=0.0f;}

    TVertex2(float nV0, float nV1)
    {	v0=nV0;	v1=nV1;}

    TVertex2(const float * rhs)
    {	v0=*rhs;	v1=*(rhs+1);}

    TVertex2(const TVertex2 & rhs)
    {	v0=rhs.v0;	v1=rhs.v1;}

    ~TVertex2() {}	//empty

    void Set(float nV0, float nV1)
    {	v0=nV0;	v1=nV1;	}

    //accessors kept for compatability
    void SetV0(float nV0) {v0 = nV0;}
    void SetV1(float nV1) {v1 = nV1;}

    //accessors swap
    void Swap(){float t=v0;v0=v1;v1=t;}

    float GetV0() const {return v0;}	//public accessor functions
    float GetV1() const {return v1;}	//inline, const

    float &XComponent() {return v0;}
    float &YComponent() {return v1;}

    //linear interpolate
    //multiply by a float, eg 3*
    TVertex2 operator*(const float Scalar){return TVertex2(v0*Scalar,v1*Scalar);}
    TVertex2 operator/(const float Scalar){return TVertex2(v0/Scalar,v1/Scalar);}
    TVertex2 operator+(const TVertex2 & rhs){return TVertex2(v0+rhs.v0,v1+rhs.v1);}
    void operator+=(const TVertex2 & rhs)
    {
        v0+=rhs.v0;	v1+=rhs.v1;
    }

    bool operator==(const TVertex2 & rhs) const{return  ((*this)==rhs);}
    bool operator!=(const TVertex2 & rhs) const
    {	return !((*this)==rhs);	}

    //unary operators
    TVertex2 operator-(void) const {return TVertex2(-v0,-v1);}
    TVertex2 operator+(void) const {return (*this);}

    //cast to pointer to float for glColor4fv etc
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}

    //member variables
    float v0;
    float v1;
};
class Vec2{
public:
    Vec2()
    {	x=y=0.0f;}

    Vec2(float nF0, float nF1)
    {	x = nF0; y = nF1; }

    Vec2(const float * rhs)
    {	x=*rhs;	y=*(rhs+1); }

    Vec2(const Vec2 & rhs)
    {	x=rhs.x;	y=rhs.y; }

    ~Vec2() {}	//empty
    void Set(Vec2 &v)
    {   x = v.x; y = v.y; }
    void Set(float nF0, float nF1)
    {	x = nF0; y = nF1; }

    //accessors kept for compatability
    void Setf0(float nF0) {x = nF0;}
    void Setf1(float nF1) {y = nF1;}


    //accessors swap
    void swap(){float t=x;x=y;y=t;}

    float Getf0() const {return x;}	//public accessor functions
    float Getf1() const {return y;}	//inline, const

    //linear interpolate
    //multiply by a float, eg 3*
    Vec2 operator/(const Vec2 &s){return Vec2(x/s.x,y/s.y);}
    Vec2 operator/(const float Scalar){return Vec2(x/Scalar,y/Scalar);}
    Vec2 operator/=(const float Scalar){ (*this)=(*this)/Scalar;return (*this);}
    Vec2 operator*(const float Scalar){return Vec2(x*Scalar,y*Scalar);}
    Vec2 operator*=(const float Scalar){ (*this)=(*this)*Scalar;return (*this);}
    Vec2 operator-(const Vec2 & rhs){return Vec2(x-rhs.x,y-rhs.y);}
    Vec2 operator-=(const Vec2 & rhs)
    {
        x-=rhs.x;	y-=rhs.y;
        return (*this);
    }
    Vec2 operator+(const Vec2 & rhs){return Vec2(x+rhs.x,y+rhs.y);}
    Vec2 operator+=(const Vec2 & rhs)
    {
        x+=rhs.x;	y+=rhs.y;
        return (*this);
    }


    bool operator==(const Vec2 & rhs) const;
    bool operator!=(const Vec2 & rhs) const
    {	return !((*this)==rhs);	}

    //unary operators
    Vec2 operator-(void) const {return Vec2(-x,-y);}
    Vec2 operator+(void) const {return (*this);}

    float length() { return sqrt(x * x + y * y); }
    void normalize()
    {
        float l = length();
        if ( l > 0.0)
        {
            (*this) *= 1.0 / l;
        }
    }
    //cast to pointer to float for glColor4fv etc
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}

    //member variables
    float x;
    float y;
};

class Vec3{
public:
    //constructors
    Vec3()
    {	x=y=z=0.0f;}

    Vec3(Vec2 v,float _z)
    {  x = v.x; y = v.y; z = _z; }

    Vec3(float nF0, float nF1, float nF2)
    {	x = nF0; y = nF1; z = nF2;}

    Vec3(const float * rhs)
    {	x=*rhs;	y=*(rhs+1); z=*(rhs+2);}

    Vec3(const Vec3 & rhs)
    {	x=rhs.x;	y=rhs.y; z=rhs.z;}

    ~Vec3() {}	//empty
    void Set(Vec3 &v)
    {	x = v.x; y = v.y; z = v.z;}
    void Set(float nF0, float nF1, float nF2)
    {	x = nF0; y = nF1; z = nF2;}

    //accessors kept for compatability
    void Setf0(float nF0) {x = nF0;}
    void Setf1(float nF1) {y = nF1;}
    void Setf2(float nF2) {z = nF2;}


    //accessors swap
    void Shift(){float t=x;x=y;y=z;z=t;}

    float Getf0() const {return x;}	//public accessor functions
    float Getf1() const {return y;}	//inline, const
    float Getf2() const {return z;}

    //linear interpolate
    //multiply by a float, eg 3*

    Vec3 Abs(){
        return Vec3(abs(x),abs(y),abs(z));
    }

    Vec3 operator/(const float Scalar){return Vec3(x/Scalar,y/Scalar,z/Scalar);}
    Vec3 operator/=(const float Scalar){ (*this)=(*this)/Scalar;return (*this);}
    //Vec3 operator*(const bool test){return Vec3(x*test,y*(_test,z*(float)test)}
    Vec3 operator*(const Vec3 &rhs){return Vec3(x*rhs.x,y*rhs.y,z*rhs.z);}
    Vec3 operator*=(const Vec3 &rhs){ (*this)=(*this)*rhs;return (*this);}
    Vec3 operator*(const float Scalar){return Vec3(x*Scalar,y*Scalar,z*Scalar);}
    Vec3 operator*=(const float Scalar){ (*this)=(*this)*Scalar;return (*this);}
    Vec3 operator-(const Vec3 & rhs){return Vec3(x-rhs.x,y-rhs.y,z-rhs.z);}
    Vec3 operator-=(const Vec3 & rhs)
    {
        x-=rhs.x;	y-=rhs.y; z-=rhs.z;
        return (*this);
    }
    Vec3 operator+(const Vec3 & rhs){return Vec3(x+rhs.x,y+rhs.y,z+rhs.z);}
    Vec3 operator+=(const Vec3 & rhs)
    {
        x+=rhs.x;	y+=rhs.y; z+=rhs.z;
        return (*this);
    }
    bool operator<(const Vec3 &rhs){
        return ((x<rhs.x)||(y<rhs.y)||(z<rhs.z));
    }
    bool operator>(const Vec3 &rhs){
        return ((x>rhs.x)||(y>rhs.y)||(z>rhs.z));
    }
    bool operator==(const Vec3 & rhs) const;
    bool operator!=(const Vec3 & rhs) const
    {	return !((*this)==rhs);	}

    //unary operators
    Vec3 operator-(void) const {return Vec3(-x,-y,-z);}
    Vec3 operator+(void) const {return (*this);}

    //cast to pointer to float for glColor4fv etc
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}

    //member variables
    float x;
    float y;
    float z;
};

class TFloat3
{
public:
    //constructors
    TFloat3()
    {	f0=f1=f2=0.0f;}

    TFloat3(float nF0, float nF1, float nF2)
    {	f0 = nF0; f1 = nF1; f2 = nF2;}

    TFloat3(const float * rhs)
    {	f0=*rhs;	f1=*(rhs+1); f2=*(rhs+2);}

    TFloat3(const TFloat3 & rhs)
    {	f0=rhs.f0;	f1=rhs.f1; f2=rhs.f2;}

    ~TFloat3() {}	//empty

    void Set(float nF0, float nF1, float nF2)
    {	f0 = nF0; f1 = nF1; f2 = nF2;}

    //accessors kept for compatability
    void Setf0(float nF0) {f0 = nF0;}
    void Setf1(float nF1) {f1 = nF1;}
    void Setf2(float nF2) {f2 = nF2;}


    //accessors swap
    void Shift(){float t=f0;f0=f1;f1=f2;f2=t;}

    float Getf0() const {return f0;}	//public accessor functions
    float Getf1() const {return f1;}	//inline, const
    float Getf2() const {return f2;}

    //linear interpolate
    //multiply by a float, eg 3*

    bool operator==(const TFloat3 & rhs) const;
    bool operator!=(const TFloat3 & rhs) const
    {	return !((*this)==rhs);	}

    //unary operators
    TFloat3 operator-(void) const {return TFloat3(-f0,-f1,-f2);}
    TFloat3 operator+(void) const {return (*this);}

    //cast to pointer to float for glColor4fv etc
    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}

    //member variables
    float f0;
    float f1;
    float f2;
};

typedef std::vector<TVertex2> TVecList;



#ifndef CHECK_TYPE
#ifdef __GNUC__
#define CHECK_TYPE(var, type)  {  \
    __typeof(var) *__tmp;         \
    __tmp = (type *)NULL;         \
    (void)__tmp;                  \
} (void)0
#else
#define CHECK_TYPE(var, type)
#endif
#endif

#ifndef SWAP
#  define SWAP(type, a, b)  {  \
    type sw_ap;                \
    CHECK_TYPE(a, type);       \
    CHECK_TYPE(b, type);       \
    sw_ap = (a);               \
    (a) = (b);                 \
    (b) = sw_ap;               \
} (void)0
#endif


#endif // TYPES_H
