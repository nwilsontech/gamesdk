#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "gx_util.h"

void toLowerCaseSTD(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
