#ifndef TEXTURE_H__
#define TEXTURE_H__

#include <GL/glu.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
///////////////////////
#define USE_SUPER_DEVIL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
////////////////////////

#include <cstring>
#include <vector>
#include <fstream>
/////////////////////
//Error Handling
////////////////////
#include <stdexcept>
#include <cerrno>
#include <cstdarg>
#include <iostream>

#include "gx_types.h"
#include "FileArch.h"

#ifndef INITIALIZE_DEVIL

#define INITIALIZE_DEVIL    if (1)\
                            {\
                            ilInit();\
                            iluInit();\
            ilutRenderer(ILUT_OPENGL);\
                            }
#endif

using std::string;
using std::vector;
using std::ifstream;
typedef unsigned char *_data_stream;
//template<typename T, size_t N>
//void array_fill(T (&dest)[N],...)
//{
//    va_list ap;
//    va_start(ap,N);
//    for(size_t i=0;i<N;i++)
//    {
//             dest[i]=va_arg(ap,T);
//    }
//    va_end(ap);
//}
//void FillF(float *a,float b[])
//{
//    memmove(a,b,sizeof(b));
//}
enum ripCon
{
   RC_DEFAULTS = 0,
   RC_SPECIFIC
};
class ripdef
{
  public:
        ripdef(int xo,int yo,int bw, int bh, int rw,int rh,ripCon _rc)
        {
            rc = _rc;
            rip_width=rw;
            rip_height=rh;
            bounding_width=bw;
            bounding_height=bh;
            xoff=xo;
            yoff=yo;
        }
  public:
        ripCon rc;
        int rip_width, rip_height;
        int bounding_width, bounding_height;
        int xoff, yoff;
};
class Texture
{

      //Functions
      public:
             static vector<Texture *> textures;
             Texture(string filename,ripdef *rd=NULL,string name ="");
             Texture(void *buffer,size_t s);
             Texture(FARC::FAstream fs);
             bool CreateFromText(const Texture &sc);
             bool LoadFromStream(void *buffer,size_t s);
             bool loadImage(string filename);
             void GenerateNewID();
             ~Texture();
      //Variables
      public:
             ILubyte      *imageData;
             unsigned int  bpp;
             unsigned int  width;
             unsigned int  height;
             unsigned int  texID;
             unsigned int  format;
             int           location;
             string        name;
     private:
            void LoadImgRC(ripdef *rd,string fn);

};
#endif
