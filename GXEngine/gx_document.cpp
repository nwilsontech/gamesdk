#include <iostream>
#include <fstream>
#include <sstream>

/// XML Support
#include "GXXml/tinyxml.h"
#include "gx_document.h"

#include "gx_color.h"
#include <typeinfo>
#include <functional>
#include <vector>

using namespace std;

struct dmax
{
    string          s;
    unsigned int word;
};

static bool StrEqual( const char* s1, const char* s2 )
{
    return ( s1 && s2 && strcmp( s1, s2 ) == 0 );
}

using namespace std;

#ifdef ANTIQUATED_USE

void LoadPrimativesFromDocument(string Doc, vector<TPrimative *> &loadout)
{
    //cout << "Loading Document\n";
    ifstream istr(Doc.data());

    if (!istr)
    {
        cout <<"No Document\n";
        return;
    }

    /*
     *
    _pr_type_none,
    _pr_type_rect,
    _pr_type_rect_adv,
    _pr_type_health_bar,
    _pr_type_caption,
    _pr_type_graphic
     *
     */

    char line[256];
    while(istr.getline(line,256))
    {
        istringstream newLine(line, istringstream::in);
        string firstWord;
        string fn,col;
        int a,b,c,d,e;
        float ef;
        newLine >> firstWord;
        if (firstWord=="#")
        {

        }
        else if (firstWord=="Rect")
        {
            RectX *r;
            newLine >> a >> b >> c >> d >> ef >> e >> col;
            r = new RectX(a,b,c,d);
            r->SetLineWidth(ef);
            if (e==0)
                r->filled = false;
            else
                r->filled = true;
            r->line_color = GetColor(col);
            loadout.push_back(r);

        }else if (firstWord=="RectAdv")
        {
            RectXAdv *rx;
            newLine >> a >> b >> c >> d >> e;
            rx = new RectXAdv(a,b,c,d,e);
            loadout.push_back(rx);
        }else if (firstWord=="HealthBar")
        {
            THealthBar *hb;
            newLine >> a >> b >> c >> d >> col;
            hb = new THealthBar(a,b,c,d);
            TFloat t = GetColor(col);
            hb->SetColor3f(t.r,t.g,t.b);
            loadout.push_back(hb);
        }else if (firstWord=="HealthBarEx")
        {
            THealthBarEx *hb;
            newLine >> fn >> a >> b >> c >> d;
            hb = new THealthBarEx(fn,a,b,c,d);
            loadout.push_back(hb);
        }
        else if (firstWord=="Caption")
        {
            GXCaption *cp;
            newLine >> a >> b >> fn;
            cp = new GXCaption(a,b,fn);
            loadout.push_back(cp);
        }else if (firstWord=="Graphic")
        {
            TGraphic *gc;
            newLine >> fn >> a >> b >> c >> d;
            gc = new TGraphic(fn,a,b);
            gc->SetSize(c,d);
            loadout.push_back(gc);
        }
    }

}
#endif

struct prim_key
{
   string text;
   int    key;
   prim_key(string s,int k)
   {
       text = s;
       key  = k;
   }
};
template<typename T>
struct primative_key
{
    string id;
    T val;
};

struct basic_primative
{
    string TYPE;
    string fn;
    string al;
    int   click;
    float w;
    float h;
    basic_primative(string t,string f, string s,int c,float i,float j)
    {
        TYPE = t;
        fn = f;
        al = s;
        click = c;
        w = i;
        h = j;

    }
};
struct monsta_key
{
    string fn;
    string val;
    string id;

    monsta_key(string pass = "",std::string name = "",string _id = "")
    {
        id  = _id;
        val = pass;
        fn  = name;
    }

};

class secondary_stack
{
public:
    secondary_stack(){}
    void Add(string val,string name,string id){
        monsta_key key;
        key.fn = name;
        key.val = val;
        key.id = id;
        //cout << "key:"<<key.fn<<":"<<key.val<<":"<<key.id<<endl;
        keys.push_back(key);

    }
    int Size()
    {
        return (int)keys.size();
    }

    void Debug()
    {
        for(int i = 0; i < (int)keys.size(); i++)
        {

            cout << i << ": " << keys.at(i).fn << ":" << keys.at(i).val <<":"<<keys.at(i).id<<endl;

        }
    }

public:
    vector<monsta_key> keys;
};



vector<basic_primative    >  load_list;
//vector<basic_primative_alt>  load_list_alt;
vector<secondary_stack> load_list_alt;

int Find(string s)
{
    for(int idx = 0; idx < (int)load_list.size(); idx++)
    {
        if (load_list.at(idx).al==s)
        {

            return idx;
        }
    }
    return (-1);
}


monsta_key find_key(std::string name,vector<monsta_key> keys)
{
    for(int i = 0; i <  (int)keys.size(); i++)
    {
        if (keys.at(i).fn==name)
        {
            return (keys.at(i));
        }
    }
        return monsta_key();
}

void CreatePrimative(vector<TPrimative *> &loadout,basic_primative one,secondary_stack/*basic_primative_alt*/ duo,float x,float y)
{
    string t = one.TYPE;
    if (t=="Graphic")
    {
        TGraphic *g;
        g = new TGraphic(one.fn,x,y);
        g->SetSize(one.w,one.h);
        g->SetClickable(one.click);
        g->SetAlias(one.al);
        monsta_key f = find_key("center",duo.keys);
        monsta_key xt = find_key("caption",duo.keys);
        if (xt.fn!=""){
            g->caption = xt.val;
            printf("setting caption: %s\n",g->caption.c_str());
        }

        monsta_key c = find_key("color",duo.keys);
        if (c.fn!="")
            g->color = GetColor(c.val);
        if (atof(f.val.c_str())==1)
        {
           // cout<<"cVal:"<<atof(f.val.c_str())<<endl;
            g->center=true;
            cout << "center enabled\n";

        }else
        {
            g->center=false;
        }
        loadout.push_back(g);
        return;
    }else if (t=="Rect")
    {
        RectX *g;
        g = new RectX(x,y,one.w,one.h);
        monsta_key f = find_key("color",duo.keys);
        monsta_key s = find_key("filled",duo.keys);
        g->filled = (bool)atoi(s.val.c_str());
        //cout<<"color val: "<<f.fn<<":"<<f.id<<":"<<f.val<<"\n";
        g->SetLineColor(GetColor(f.val));
        loadout.push_back(g);
        return;
    }else if (t=="Caption")
    {
        GXCaption *g;
        monsta_key f = find_key("text",duo.keys);
        if (one.al!="")
            f.val = one.al;
        g = new GXCaption(x,y,f.val);
        loadout.push_back(g);
       // std::cout<<"Created Caption\n";
        return;
    }else if (t=="LabelBox")
    {
        GXLabelBox *g;
        monsta_key f = find_key("text",duo.keys);
        if (one.al!=""){
            f.val = one.al;

        }
        g = new GXLabelBox(x,y,one.w,one.h,f.val);
        if (one.al!=""){
            g->SetAlias(one.al);
        }
        loadout.push_back(g);
       // std::cout<<"Created Caption\n";
        return;
    }else if (t=="HealthBar")
    {
        THealthBar *g;
        g = new THealthBar(x,y,one.w,one.h);
        g->SetAlias(one.al);
        loadout.push_back(g);
        return;
    }else if (t=="HealthBarEx")
    {
        THealthBarEx *h;
        h = new THealthBarEx(one.fn,x,y,one.w,one.h);
        h->SetAlias(one.al);
        loadout.push_back(h);
        return;
    }else if (t=="Group")
    {
        TGroup *h;
        h = new TGroup(one.fn,x,y);
        loadout.push_back(h);
        return;
    }

}

void ProcessDataSection(const TiXmlElement* rootChild, vector<TPrimative *> &loadout)
{
    for(const TiXmlElement* action = rootChild->FirstChildElement( "data" );
     action;
     action = action->NextSiblingElement( "data" ) )
     {
        string ln,alt;
        int x=0,y=0;
         for(const TiXmlAttribute* node = action->FirstAttribute();
         node;
         node = node->Next() )
         {
            if (StrEqual(node->Name(),"ID")){ln = node->Value();}
            if (StrEqual(node->Name(),"alt")){alt = node->Value();}
            if (StrEqual(node->Name(),"x")){x=atoi(node->Value());}
            if (StrEqual(node->Name(),"y")){y=atoi(node->Value());}
         }
         int lkl = Find(ln);
         if (lkl!=-1)
         {
             /// Adding the following two lines to override alt alias
             basic_primative bp = load_list.at(lkl);
             secondary_stack ss = load_list_alt.at(lkl);
             if (alt!="")
                bp.al = alt;



             CreatePrimative(loadout,bp,ss,x,y);
         }
     }
}

void ProcessGroupSection(const TiXmlElement* rootChild, vector<TPrimative *> &loadout)
{

    TGroup *tempgrp = nullptr;
    vector<TPrimative *> groupList;
    for(const TiXmlElement* action = rootChild->FirstChildElement( "group" );
     action;
     action = action->NextSiblingElement( "group" ) )
     {
        groupList.clear();
        groupList.empty();

        string ln="";

        int x=0,y=0;
         for(const TiXmlAttribute* node = action->FirstAttribute();
         node;
         node = node->Next() )
         {
            if (StrEqual(node->Name(),"ID")){ln = node->Value();}
            if (StrEqual(node->Name(),"x")){x=atoi(node->Value());}
            if (StrEqual(node->Name(),"y")){y=atoi(node->Value());}
         }

         if (ln!="")
         {

             tempgrp = new TGroup(ln,x,y);
             ProcessDataSection(action,groupList);
             for(size_t i = 0; i < groupList.size(); i++)
             {
                 //cout<<"["<<tempgrp->name<<"]\t Adding Element\n";
                 tempgrp->Add(groupList.at(i));
             }
             loadout.push_back(tempgrp);
         }

     }
}


bool LoadPrimativesFromXMLDocument(string Doc, vector<TPrimative *> &loadout)
{
    TiXmlDocument doc( Doc.c_str() );
    bool loadOkay = doc.LoadFile();
    if (!loadOkay)
    {

        fprintf(stderr,"Map_Name: %s\n",Doc.c_str());
        fprintf(stderr,"ML::File does not exsist or Poorly formatted\n");
        throw std::runtime_error ("Failed to load");
        return false;
    }
    const TiXmlElement*      root      = 0;
    root = doc.FirstChildElement( "ARCM" );
    for(const TiXmlElement* rootChild = root->FirstChildElement();
         rootChild;
         rootChild = rootChild->NextSiblingElement() )
    {
        if ( StrEqual( rootChild->Value(), "map_items" ) )
                    {

                    for(const TiXmlElement* action = rootChild->FirstChildElement( "map_obj" );
                     action;
                     action = action->NextSiblingElement( "map_obj" ) )
                     {
                        //int curr = -1;

                        for(const TiXmlElement* action2 = action->FirstChildElement( "obj_def" );
                          action2;
                          action2 = action2->NextSiblingElement( "obj_def" ) )
                          {
                             //Variables
                             string ln="";
                             string al="";
                             string az="";

                             float  sc = 1.0f; //Ratio Scale
                             int x =-1,
                                 y =-1,
                             click = 0;

                             //Variables
                             for(const TiXmlAttribute* node = action2->FirstAttribute();
                             node;
                             node = node->Next() )
                             {

                                if (StrEqual(node->Name(),"type"))  {al    = node->Value();}
                                if (StrEqual(node->Name(),"name"))  {ln    = node->Value();}
                                if (StrEqual(node->Name(),"alias")) {az    = node->Value();}
                                if (StrEqual(node->Name(),"solid")) {click = atoi(node->Value());}
                                if (StrEqual(node->Name(),"scale")) {sc    = atof(node->Value());}
                                if (StrEqual(node->Name(),"width")) {x     = atoi(node->Value());}
                                if (StrEqual(node->Name(),"height")){y     = atoi(node->Value());}


                             }

                                 if (az=="")
                                     az=ln;

                                 if (sc!=1.0f)
                                 {
                                     /// Setup Test X / Y
                                     int tx = x;
                                     int ty = y;



                                     auto max = [tx,ty]()->int{
                                        if (tx>ty)
                                            return 0;
                                        return 1;
                                     };
                                     int test = max();
                                     if (test==1){
                                         float tsc = 74.0/(float)y;

                                         x = (int)((float)x*tsc);
                                         y = (int)((float)y*tsc);
                                     }else
                                     {
                                         float tsc = 74.0/(float)x;

                                         x = (int)((float)x*tsc);
                                         y = (int)((float)y*tsc);
                                     }
                                 }

                                 load_list.push_back(basic_primative(al,ln,az,click,x,y));
                                 load_list_alt.push_back(secondary_stack());

                          }

                         for(const TiXmlElement* action2 = action->FirstChildElement( "obj_add" );
                          action2;
                          action2 = action2->NextSiblingElement( "obj_add" ) )
                          {

                             for(const TiXmlAttribute* node = action2->FirstAttribute();
                             node;
                             node = node->Next() )
                             {
                                 if (StrEqual(node->Name(),"text")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"text","Ss");

                                 }
                                 if (StrEqual(node->Name(),"opacity")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"opacity","f");

                                 }
                                 if (StrEqual(node->Name(),"border")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"border","f");
                                 }
                                 if (StrEqual(node->Name(),"filled")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"filled","f");
                                 }
                                 if (StrEqual(node->Name(),"center")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"center","f");
                                 }
                                 if (StrEqual(node->Name(),"color")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"color","Ss");

                                 }
                                 if (StrEqual(node->Name(),"caption")){
                                     load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"caption","Ss");

                                 }
                             }

                          }

                     }


                    }
              if ( StrEqual( rootChild->Value(), "map_data" ) )
                   {

                              ProcessDataSection(rootChild,loadout);
                              ProcessGroupSection(rootChild,loadout);

                   }
    }

    /////End
    ///
    doc.Clear();

    printf("map_loaded\n");
    return true;
}


bool LoadPrimativesXT(string Doc, vector<TPrimative *> &loadout)
{
    TiXmlDocument doc( Doc.c_str() );
    bool loadOkay = doc.LoadFile();
    if (!loadOkay)
    {

        fprintf(stderr,"Map_Name: %s\n",Doc.c_str());
        fprintf(stderr,"ML::File does not exsist\n");
        throw std::runtime_error ("Failed to load");
        return false;
    }
    const TiXmlElement*      root      = 0;
    root = doc.FirstChildElement( "ARCM" );
    for(const TiXmlElement* rootChild = root->FirstChildElement();
         rootChild;
         rootChild = rootChild->NextSiblingElement() )
    {
        if ( StrEqual( rootChild->Value(), "map_items" ) )
                    {
                        //int curr = -1;

                        for(const TiXmlElement* action = rootChild->FirstChildElement( "obj_def" );
                          action;
                          action = action->NextSiblingElement( "obj_def" ) )
                          {
                             //Variables
                             string ln="";
                             string al="";
                             string az="";

                             float  sc = 1.0f; //Ratio Scale
                             int x =-1,
                                 y =-1,
                             click = 0;

                             //Variables
                             for(const TiXmlAttribute* node = action->FirstAttribute();
                             node;
                             node = node->Next() )
                             {

                                if (StrEqual(node->Name(),"type"))  {al    = node->Value();}
                                if (StrEqual(node->Name(),"name"))  {ln    = node->Value();}
                                if (StrEqual(node->Name(),"alias")) {az    = node->Value();}
                                if (StrEqual(node->Name(),"solid")) {click = atoi(node->Value());}
                                if (StrEqual(node->Name(),"scale")) {sc    = atof(node->Value());}
                                if (StrEqual(node->Name(),"width")) {x     = atoi(node->Value());}
                                if (StrEqual(node->Name(),"height")){y     = atoi(node->Value());}


                             }

                                 if (az=="")
                                     az=ln;

                                 if (sc!=1.0f)
                                 {
                                     /// Setup Test X / Y
                                     int tx = x;
                                     int ty = y;



                                     auto max = [tx,ty]()->int{
                                        if (tx>ty)
                                            return 0;
                                        return 1;
                                     };
                                     int test = max();
                                     if (test==1){
                                         float tsc = 74.0/(float)y;

                                         x = (int)((float)x*tsc);
                                         y = (int)((float)y*tsc);
                                     }else
                                     {
                                         float tsc = 74.0/(float)x;

                                         x = (int)((float)x*tsc);
                                         y = (int)((float)y*tsc);
                                     }
                                 }

                                 load_list.push_back(basic_primative(al,ln,az,click,x,y));
                                 load_list_alt.push_back(secondary_stack());
                                 for(const TiXmlElement* action2 = action->FirstChildElement( "obj_add" );
                                  action2;
                                  action2 = action2->NextSiblingElement( "obj_add" ) )
                                  {

                                     for(const TiXmlAttribute* node = action2->FirstAttribute();
                                     node;
                                     node = node->Next() )
                                     {
                                         if (StrEqual(node->Name(),"text")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"text","Ss");

                                         }
                                         if (StrEqual(node->Name(),"opacity")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"opacity","f");

                                         }
                                         if (StrEqual(node->Name(),"border")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"border","f");
                                         }
                                         if (StrEqual(node->Name(),"filled")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"filled","f");
                                         }
                                         if (StrEqual(node->Name(),"center")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"center","f");
                                         }
                                         if (StrEqual(node->Name(),"color")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"color","Ss");

                                         }
                                         if (StrEqual(node->Name(),"caption")){
                                             load_list_alt.at((int)load_list_alt.size()-1).Add((string)node->Value(),"caption","Ss");

                                         }
                                     }

                                  }

                          }





                    }
              if ( StrEqual( rootChild->Value(), "map_data" ) )
                   {

                              ProcessDataSection(rootChild,loadout);
                              ProcessGroupSection(rootChild,loadout);

                   }
    }

    /////End
    ///
    doc.Clear();

    printf("map_loaded\n");
    return true;
}
