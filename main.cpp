//#define UNREAL
//#define GLEW_STATIC

//#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

#include "GXEngine/gx_engine.h"

using namespace std;

int main(int argc,char **argv)
{
    (void)argc;
    base_location = argv[0];
    std::cout << base_location << std::endl;

    WorldEngine->RunEngine();
    WorldEngine->FinEngine();
    return 0;
}

