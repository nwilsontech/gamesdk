#define pragma once
#ifndef GX_FONT_MANAGER
#define GX_FONT_MANAGER

#include <FTGL/ftgl.h>
#include "gx_color.h"

/**
    "DejaVuSerif.ttf",
    "listing.txt",
    "Roboto-BoldCondensed.ttf",
    "Roboto-Bold.ttf",
    "Roboto-Condensed.ttf",
    "Roboto-Italic.ttf",
    "Roboto-Light.ttf",
    "Roboto-Medium.ttf",
    "Roboto-Regular.ttf"
 */




enum {
    FTE_DEJAVUSERIF = 0,
    FTE_ROBOTO_BOLDCONDENSED = 1,
    FTE_ROBOTO_BOLD = 2,
    FTE_ROBOTO_CONDENSED = 3,
    FTE_ROBOTO_ITALIC = 4,
    FTE_ROBOTO_LIGHT = 5,
    FTE_ROBOTO_MEDIUM = 6,
    FTE_ROBOTO_REGULAR =7
};

struct _fs_string_font_format
{
    std::string value;
    int font_number;
    TFloat color;
    _fs_string_font_format(std::string v = "", int fn = 0, TFloat c = TFloat(1.0f,1.0f,1.0f))
    {
        value = v;
        font_number = fn;
        color = c;
    }
};
class TFormatedString
{
public:
    TFormatedString(int f, std::string c,std::string s)
    {
        fontID = f;
        color  = GetColor(c);
        str    = s;
    }
   ~TFormatedString(){}

public:
    int      fontID;
    TFloat    color;
    std::string str;
};
class TFormatedStringList
{
public:
    TFormatedStringList()
    {

    }
    inline void Push(TFormatedString fs)
    {
        formatedStrings.push_back(fs);
        longStr += fs.str;
    }
    inline void Empty(void)
    {
        formatedStrings.clear();
        longStr = "";
    }

    inline size_t GetWItem(FTFont* f,size_t item_number) /// Get Item Width
    {
        if ((item_number>=formatedStrings.size()))
                return 0;
        return _gtw(f,formatedStrings.at(item_number).str);
    }

    inline std::string GetLS(void)
    {
        return longStr;
    }
private:
    int _gtw(FTFont* f,const std::string str)
    {
        return (int)f->BBox(str.c_str()).Upper().Xf();
    }
public:
    std::vector<TFormatedString> formatedStrings;
    std::string longStr;
};

class TFontManager
{
public:
    TFontManager(){}
   ~TFontManager(){}
    void Init()
    {
        fonts[0] = new FTPixmapFont("eufm10.ttf");
        if (fonts[0]->Error())
        {
            printf("shit font 1\n");
        }
        fonts[0]->FaceSize(30);

        store_size[0] = 0;
        fonts[1] = new FTPixmapFont("DejaVuSerif.ttf");
        if (fonts[1]->Error())
        {
            printf("shit font 2\n");
        }

        fonts[1]->FaceSize(17);

        store_size[1] = 0;

    }
    /// Currently only allowing 1 depth stack for each font
    void PushSize(int f /*Size to Push*/)
    {
        store_size[f] = fonts[f]->FaceSize();
    }
    void PopSize(int f)
    {
        fonts[f]->FaceSize(store_size[f]);
        store_size[f] = 0;
    }

    void SetSize(int f,int fs)
    {
        fonts[f]->FaceSize(fs);
    }
    //    void printf(const char *s, T value, Args... args)
    void PrintText(int x, int y,int f,const char *fmt,...)
    {
        //printf("Rendering Font\n");

        char    text[256];
        va_list ap;
        va_start(ap,fmt);
        vsprintf(text,fmt,ap);
        va_end(ap);


        glRasterPos2f(x,y);

        fonts[f]->Render(text);

    }
    void PrintTextCenter(int x, int y,int f,const char *fmt,...)
    {
        char    text[256];
        va_list ap;
        va_start(ap,fmt);
        vsprintf(text,fmt,ap);
        va_end(ap);

        int wd = GetTextWidth(f,text);

        glRasterPos2f(x-wd/2,y);

        fonts[f]->Render(text);
    }
    void PrintTextCenter(int x, int y, int f, TFormatedStringList &fs)
    {
        int tWidth = GetTextWidth(f,fs.GetLS().c_str());
        int offSet = 0;
        for(size_t i = 0; i < fs.formatedStrings.size(); i++)
        {
            glRasterPos2f(x-tWidth/2+offSet,y);
            glColor3f(fs.formatedStrings.at(i).color.r,fs.formatedStrings.at(i).color.g,fs.formatedStrings.at(i).color.b);
            PrintText(x-tWidth/2+offSet,y,f,fs.formatedStrings.at(i).str.c_str());
            //fonts[f]->Render(fs.formatedStrings.at(i).str.c_str());
            glColor3f(1.0f,1.0f,1.0f);
            offSet+=GetTextWidth(f,fs.formatedStrings.at(i).str.c_str());
        }
    }
    void PrintText(int x, int y, int f, TFormatedStringList &fs)
    {
        int offSet = 0;
        for(size_t i = 0; i < fs.formatedStrings.size(); i++)
        {
           // glRasterPos2f(x+offSet,y);
            glColor3f(fs.formatedStrings.at(i).color.r,fs.formatedStrings.at(i).color.g,fs.formatedStrings.at(i).color.b);
            PrintText(x+offSet,y,f,fs.formatedStrings.at(i).str.c_str());
            //fonts[f]->Render(fs.formatedStrings.at(i).str.c_str());
            glColor3f(1.0f,1.0f,1.0f);
            offSet+=GetTextWidth(f,fs.formatedStrings.at(i).str.c_str());
        }
    }



    int GetTextWidth(int f,const char *fmt,...)
    {
        char text[256];
        va_list ap;
        va_start(ap,fmt);
        vsprintf(text,fmt,ap);
        va_end(ap);
        return (int)fonts[f]->BBox(text).Upper().Xf();
    }

   // static void Uninitialize(void);
  //  static GLEngine *getEngine(void);
  //  void Initialize(GLint width, GLint height);
public:
   FTFont* fonts[2];
private: /// Make this data hidden
   size_t  store_size[2];
   //FTPixmapFont* infoFont;

};
#endif // GX_FONT_MANAGER

