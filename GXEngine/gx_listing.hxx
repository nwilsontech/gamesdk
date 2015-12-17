#pragma once
#ifndef GX_LISTING_HXX
#define GX_LISTING_HXX

#include <string>
#include <vector>
#include "gx_font_manager.h"

using std::string;
using std::vector;


struct ConsoleItem
{

    ConsoleItem()
    {

    }
};


class Console
{
public:
    Console(){}
   ~Console(){}
public:
    void Draw(){}

public:
    vector<string> console_items;
public:
    int console_limit;
    int current_item;
};

#endif // GX_LISTING_HXX

