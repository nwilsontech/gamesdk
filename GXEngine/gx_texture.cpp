#include "gx_texture.h"



#define GEN_TEX(t,d)            glGenTextures(1, &t);\
                                glBindTexture(GL_TEXTURE_2D, t);\
                                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);\
                                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);\
                                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);\
                                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);\
                                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, d);



#define high(x) ((unsigned int) (((x>>16) & 0xffffffff)))

vector<GXTexture *> GXTexture::GXTextures;

static bool StrEqu(const char * s1,const char * s2)
{
    return ( s1 && s2 && strcmp( s1, s2 ) == 0 );
}

GXTexture::GXTexture(string in_filename,ripdef *rd)
{
  bool rdl = false;
  int __id = FindTX(in_filename);
  imageData = nullptr;
  if (rd==nullptr)
  {
      rdl  = false;
  }
  else
      rdl =  true;
  if (!StrEqu(in_filename.data(),""))
  {
      if (__id==-1){//If Texture is not already in the list;
          if (rdl==false)
          {
              //std::cout<<"Creating New Texture "<<in_filename<<"\n";
              loadImage(in_filename);
          }
          else
          {
              //std::cout<<"Creating From Resource Texture\n";
              LoadImgRC(rd,in_filename);
          }
      }else{

          //std::cout<<"Creating From Previous Texture\n";
          width  = GXTextures[__id]->width;
          height = GXTextures[__id]->height;
          bpp    = GXTextures[__id]->bpp;
          name   = GXTextures[__id]->name;
          texID  = GXTextures[__id]->texID;
          //glGetTexImage(GXTextures[__id]->texID,0,GL_RGBA,GL_RGBA,imageData);
          //GEN_TEX(texID,imageData)
          //delete imageData;
      }
  }

  //name = in_name;
  if (__id==-1){
      name = in_filename;
      //std::cout<<"lmx "<<name<<std::endl;
      GXTextures.push_back(this);

  }
  //location = (int)GXTextures.size()-1;
}
//GXTexture::GXTexture(void *buffer,size_t s)//Load From Stream
//{

//      LoadFromStream(buffer,s);
//      name = "";
//      GXTextures.push_back(this);
//      location = (int)GXTextures.size()-1;
//}

//bool GXTexture::LoadFromStream(void *buffer,size_t s)
//{
//       ILuint ilGXTexture;
//       //printf("filename %s\n",filename.data());
//       ilGenImages(1, &ilGXTexture);
//       ilBindImage(ilGXTexture);
//       bool loadI = ilLoadL(IL_PNG,buffer,s);
//       if (!loadI)
//       {
//           const char *ret = iluErrorString(ilGetError());
//           fprintf(stdout,"fail Load ret = %s\n",ret);
//           exit(41);
//       }

//       //iluSharpen(1.5,5);
//        if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
//        {

//            width = ilGetInteger(IL_IMAGE_WIDTH);
//            height = ilGetInteger(IL_IMAGE_HEIGHT);
//            printf("w:%d h:%d\n",width,height);
//            glGenTextures(1, &texID);
//            glBindTexture(GL_TEXTURE_2D, texID);
//            format =  ilGetInteger(IL_IMAGE_FORMAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// nullptred 6.15.2011 GL_CLAMP);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP);
//            #ifdef ELLIS_MAKO
//            glTexParameterf(GL_TEXTURE_2D,GL_GXTexture_MIN_FILTER,GL_NEAREST);
//            glTexParameterf(GL_TEXTURE_2D,GL_GXTexture_MAG_FILTER,GL_NEAREST);
//            glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
//            #else

//            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );// Trilinear filtering (�vite le scintillement des petites GXTextures)
//            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//            gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
//            #endif	// Bilinear filtering
//            //gluBuild2DMipmaps(GL_TEXTURE_2D, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
//            //glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
//            //gluBuild2Dmipmaps(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
//           // printf("texID %d\n",texID);gluBuild2Dmipmaps//glTexImage2D
//        }else
//        {
//            fprintf(stdout,"failed\n");
//            exit(7);
//        }
//        ilDeleteImages(1, &ilGXTexture);
//        free(buffer);
//}
int GXTexture::FindTX(string s)
{
    for(int i = 0; i < (int)GXTextures.size();i++)
    {
        if (StrEqu(GXTextures.at(i)->name.data(),s.data()))
            return i;
    }
    return -1;
}

bool GXTexture::CreateFromText(const GXTexture &sc)
{
    imageData = nullptr;
    width = sc.width;
    height = sc.height;
    bpp=sc.bpp;
    name=sc.name;
    glGetTexImage(sc.texID,0,GL_RGBA,GL_RGBA,imageData);
    GEN_TEX(texID,imageData)
    delete imageData;
    return true;
}
void GXTexture::GenerateNewID()
{
            #ifdef DEBUG_GXTexture
            printf("Making new id\n");
            printf("old id:%d\n",texID);
            #endif
            glGetTexImage(texID,0,GL_RGBA,GL_RGBA,imageData);
            GEN_TEX(texID,ilGetData())
            #ifdef DEBUG_GXTexture
            printf("new id:%d\n\n",texID);
            #endif
            delete imageData;
}

GXTexture::~GXTexture()
{
  for(vector<GXTexture *>::iterator it = GXTextures.begin(); it != GXTextures.end(); it++)
    if ((*it)==this)
       GXTextures.erase(it);
}
//#define length(x) (sizeof(x) / sizeof(*(x)))
bool  GXTexture::loadImage(string filename)
{
       ILuint ilGXTexture;
       ilGenImages(1, &ilGXTexture);
       ilBindImage(ilGXTexture);
       if (!ilLoadImage((const char*)filename.data()))
       {
           const char *ret = iluErrorString(ilGetError());
           fprintf(stdout,"fail Load ret = %s\n",ret);
       }
       if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
       {
            width  =  ilGetInteger(IL_IMAGE_WIDTH);
            height =  ilGetInteger(IL_IMAGE_HEIGHT);
            format =  ilGetInteger(IL_IMAGE_FORMAT);
            GEN_TEX(texID,ilGetData())
        }else
        {
            fprintf(stdout,"failed\n");
        }
        ilDeleteImages(1, &ilGXTexture);
        //printf("returning\n");
    return true;
}
void GXTexture::LoadImgRC(ripdef *rd,string fn)
{
        ILuint ilGXTexture, w, h;
//        int cwidth = 0,cheight = 0;
        ilGenImages(1, &ilGXTexture);
        ilBindImage(ilGXTexture);
        ILboolean loaded = ilLoadImage(fn.data());
        if (loaded == IL_FALSE)
            throw std::runtime_error ("Failed to load image");
        int x = -1;
        int y = -1;
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        ripdef *rapid7 = rd;//ripdef(0,0,-1, -1, 96,192,RC_DEFAULTS);
        w = rapid7->bounding_width;
        h = rapid7->bounding_height;

        //cwidth = rapid7->rip_width;
        //cheight = rapid7->rip_height;
        x = rapid7->xoff;
        y = rapid7->yoff;
        iluCrop(x,y,0,w,h,1);
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        fprintf(stdout,": w:%d h:%d\n",w,h);
        GEN_TEX(texID,ilGetData())
        ilDeleteImages(1, &ilGXTexture);
    return;
}
