#include "gx_color.h"
#include "gx_util.h"
#include <iostream>
TFloat GetColor(string name)
{
    //Makes every thing lowercase
    toLowerCaseSTD(name);
    if (ColorTable.find(name)!=ColorTable.end())
    {
        TFloat t = ColorTable[name];
        return t;
    }else
    {
        std::cout <<"UNKNOWN COLOR <"<<name<<">"<<std::endl;
        return TFloat(1.0,1.0,1.0);
    }
}
TFloat ColorHSV(float h, float s, float v)
{
    TFloat ret;
    int i = (int)floor(h/60.0) % 6;
    //int i = int(h * 6.0);
    float f = (h / 60.0) - floor(h/60.0);
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch(i)
    {
        case 0: ret.r = v, ret.g = t, ret.b = p; break;
        case 1: ret.r = q, ret.g = v, ret.b = p; break;
        case 2: ret.r = p, ret.g = v, ret.b = t; break;
        case 3: ret.r = p, ret.g = q, ret.b = v; break;
        case 4: ret.r = t, ret.g = p, ret.b = v; break;
        case 5: ret.r = v, ret.g = p, ret.b = q; break;
    }
    return ret;
}
TFloat HSLtoCol(float h,float s,float l)
{
    float r,g,b;

    if (s==0.0)
    {
        r = g = b = l;

        return TFloat(r,g,b);
        //return ((DWORD((int)(r*256)))<<16) + (DWORD(int(g*256))<<8) + DWORD(int(b*256));
    }
    float temp1=0;
    float temp2=0;
    if (l < 0.5)
     temp2=l*(1.0+s);
    if (l >= 0.5)
     temp2=l+s - l*s;
    temp1 = 2.0*l - temp2;
    float temp3,rc,gc,bc;
    ////////////////////////////////////red
    temp3=h+1.0/3.0;
    if ((6.0*temp3) < 1)
    {
        rc = temp1 + (temp2 - temp1)*6.0*temp3;
    }
    else if ((2.0*temp3) < 1)
    {
         rc=temp2;
    }
   else if ((3.0*temp3) < 2)
   {
        rc=temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0;
   }
   else rc=temp1;
   //////////////////////////////////////green
   temp3 = h;
   if ((6.0*temp3) < 1)
   {
        gc = temp1 + (temp2 - temp1)*6.0*temp3;
   }
   else if ((2.0*temp3) < 1)
   {
         gc=temp2;
   }
   else if ((3.0*temp3) < 2)
   {
        gc=temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0;
   }
   else gc=temp1;
   ///////////////////////////////////////blue
   temp3=h-1.0/3.0;
   if ((6.0*temp3) < 1)
   {
        bc = temp1 + (temp2 - temp1)*6.0*temp3;
   }
   else if ((2.0*temp3) < 1)
   {
         bc=temp2;
   }
   else if ((3.0*temp3) < 2)
   {
        bc=temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0;
   }
   else bc=temp1;
   return TFloat(rc,gc,bc);
   //return ((DWORD((int)(rc*256)))<<16) + (DWORD(int(gc*256))<<8) + DWORD(int(bc*256));
}
