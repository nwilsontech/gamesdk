
#include "gx_primatives.h"

TPrimative::TPrimative():
    xz(0),    yz(0),   _ox(0.0f),
    _oy(0.0f), layer(0)
{

}
TPrimative::~TPrimative()
{

}
void TPrimative::SetAlias(string al)
{

    alias = std::move(al);
}

void TPrimative::UpdateOffset(float ox, float oy)
{
    _ox = std::move(ox);
    _oy = std::move(oy);
}
