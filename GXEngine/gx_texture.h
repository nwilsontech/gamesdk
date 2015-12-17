#ifndef GX_Texture_H
#define GX_Texture_H

#include <GL/glu.h>
#include <GL/gl.h>
#include <cstdio>
#include <cstdlib>
/////////////////////
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
/////////////////////
#include <cstring>
#include <vector>
#include <fstream>
/////////////////////
//Error Handling
////////////////////
#include <stdexcept>
//#include <cerrno>
//#include <cstdarg>
#include <iostream>
////////////////////
using std::string;
using std::vector;
using std::ifstream;
typedef unsigned char *_data_stream;

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
class GXTexture
{
      private:
             int FindTX(string fn);
      //Functions
      public:
             static vector<GXTexture *> GXTextures;
             GXTexture(string filename, ripdef *rd=NULL);
             GXTexture(void *buffer,size_t s);

             bool CreateFromText(const GXTexture &sc);
             //bool LoadFromStream(void *buffer,size_t s);
             bool loadImage(string filename);
             void GenerateNewID();
             ~GXTexture();
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

#endif // GX_Texture_H
