#include "gx_color.h"
#include "gx_types.h"



float fclip(float a,float upper,float lower)
{
    if (a>upper)
    {
        return upper;
    }
    if (a<lower)
    {
        return lower;
    }
    return a;

}


double round(double i)
{
    int tk = (int)floor(i);
    if (i>((float)tk+0.5))
    {
        return (double)(tk + 1);
    }
    else
    {
        return (double)(tk);
    }

}

