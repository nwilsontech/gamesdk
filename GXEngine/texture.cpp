#include "texture.h"
#define high(x) ((unsigned int) (((x>>16) & 0xffffffff)))
vector<Texture *> Texture::textures;
Texture::Texture(string in_filename,ripdef *rd,string in_name)
{
  bool rdl = false;
  imageData = NULL;
  if (rd==NULL)
  {
      printf("not using ripdef function\n");
      rdl  = false;
  }
  else
    rdl =  true;
  printf("loading %s",(char *)in_filename.data());
  if (in_filename.data()!="")
  {
      if (rdl==false)
      {
          loadImage(in_filename);
      }
      else
      {
          LoadImgRC(rd,in_filename);
      }
  }

  name = in_name;
  textures.push_back(this);
  location = (int)textures.size()-1;
}
Texture::Texture(void *buffer,size_t s)//Load From Stream
{

      LoadFromStream(buffer,s);
      name = "";
      textures.push_back(this);
      location = (int)textures.size()-1;
}
Texture::Texture(FARC::FAstream fs)
{
      //INITIALIZE_DEVIL
      LoadFromStream(fs.buffer,fs.size);
      name = "";
      textures.push_back(this);
      location = (int)textures.size()-1;
}
bool Texture::LoadFromStream(void *buffer,size_t s)
{
       ILuint ilTexture;
       //printf("filename %s\n",filename.data());
       ilGenImages(1, &ilTexture);
       ilBindImage(ilTexture);
       bool loadI = ilLoadL(IL_PNG,buffer,s);
       if (!loadI)
       {
           const char *ret = iluErrorString(ilGetError());
           fprintf(stdout,"fail Load ret = %s\n",ret);
           exit(41);
       }

       //iluSharpen(1.5,5);
        if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
        {

            width = ilGetInteger(IL_IMAGE_WIDTH);
            height = ilGetInteger(IL_IMAGE_HEIGHT);
            printf("w:%d h:%d\n",width,height);
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);
            format =  ilGetInteger(IL_IMAGE_FORMAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// NULLed 6.15.2011 GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_CLAMP);
            #ifdef ELLIS_MAKO
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
            #else

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );// Trilinear filtering (�vite le scintillement des petites textures)
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
            #endif	// Bilinear filtering
            //gluBuild2DMipmaps(GL_TEXTURE_2D, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
            //glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
            //gluBuild2Dmipmaps(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
           // printf("texID %d\n",texID);gluBuild2Dmipmaps//glTexImage2D
        }else
        {
            fprintf(stdout,"failed\n");
            exit(7);
        }
        ilDeleteImages(1, &ilTexture);
        free(buffer);
}
bool Texture::CreateFromText(const Texture &sc)
{
    imageData = NULL;
    width = sc.width;
    height = sc.height;
    bpp=sc.bpp;
    name="";
    glGetTexImage(sc.texID,0,GL_RGBA,GL_RGBA,imageData);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    delete imageData;
    //printf("texID %d\n",texID);
}
void Texture::GenerateNewID()
{
            #ifdef DEBUG_TEXTURE
            printf("Making new id\n");
            printf("old id:%d\n",texID);
            #endif
            glGetTexImage(texID,0,GL_RGBA,GL_RGBA,imageData);
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            #ifdef DEBUG_TEXTURE
            printf("new id:%d\n\n",texID);
            #endif
            delete imageData;
}

Texture::~Texture()
{
  for(vector<Texture *>::iterator it = textures.begin(); it != textures.end(); it++)
    if ((*it)==this)
       textures.erase(it);
}
//#define length(x) (sizeof(x) / sizeof(*(x)))
bool  Texture::loadImage(string filename)
{
       ILuint ilTexture;
       ilGenImages(1, &ilTexture);
       ilBindImage(ilTexture);
       printf("=>>loading image called: %s\n",filename.data());
       if (!ilLoadImage((const char*)filename.data()))
       {
           const char *ret = iluErrorString(ilGetError());
           fprintf(stdout,"fail Load ret = %s\n",ret);
       }
      // printf("image called\n");
       if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
       {

            width = ilGetInteger(IL_IMAGE_WIDTH);
            height = ilGetInteger(IL_IMAGE_HEIGHT);
            fprintf(stdout,": w:%d h:%d\n",width,height);
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            format =  ilGetInteger(IL_IMAGE_FORMAT);
            glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
           // printf("texID %d\n",texID);
        }else
        {
            fprintf(stdout,"failed\n");
        }
        ilDeleteImages(1, &ilTexture);
        //printf("returning\n");
    return true;
}
void Texture::LoadImgRC(ripdef *rd,string fn)
{
        ILuint ilTexture, w, h;
        int cwidth,cheight;
        ilGenImages(1, &ilTexture);
        ilBindImage(ilTexture);
        ILboolean loaded = ilLoadImage(fn.data());
        if (loaded == IL_FALSE)
            throw std::runtime_error ("Failed to load image");
        int x = -1;
        int y = -1;
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        ripdef *rapid7 = rd;//ripdef(0,0,-1, -1, 96,192,RC_DEFAULTS);
        w = rapid7->bounding_width;
        h = rapid7->bounding_height;

        cwidth = rapid7->rip_width;
        cheight = rapid7->rip_height;
        x = rapid7->xoff;
        y = rapid7->yoff;
        int ac = w/cwidth;
        int bc = h/cheight;
        iluCrop(x,y,0,w,h,1);
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        fprintf(stdout,": w:%d h:%d\n",w,h);
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        format =  ilGetInteger(IL_IMAGE_FORMAT);
        glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), width, height, 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
           // printf("texID %d\n",texID);
        ilDeleteImages(1, &ilTexture);
        //printf("returning\n");
    return;
}
//_XQuad Texture::GetBox(void)
//{
//    return box;
//}
