#include <GL/glew.h>
#include "GXShader/Shader.h"
//#include "Glext.h"
#include "gx_variables.h"
/// Include SDL2 stuff
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_thread.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include <qfile.h>

#include "gx_engine.h"
#include "gx_document.h"
#include "gx_sprite.h"
#include "gx_inputhandler.h"
#include "gx_particle.h"
#include "gx_experiment.hxx"
#include "gx_xml_handler.hxx"
#include "gx_expr_item_reader.hxx"
//vector<TPrimative *> boxes;
#define _SR(x) std::string(x)

extern vector<TPrimative *> boxes;
ShaderProgram *shader;
volatile bool done   = false;
volatile bool loaded = false;
bool enable_text_input = false;  /// debug only !!!
const uint8_t *keys      = nullptr;
string      text_input;
SDL_Thread*     thread;
SDL_GLContext  context;
SDL_Window    *hWindow;
SDL_mutex         *pud;
THero Champion;
MouseState         msx;
//GXEmitter Emitter;

//vector<GXSprite *> CheckList;
//GXSprite *flame; // 22x38

void TextHandle(SDL_Event event)
{
    static string str = "";

    if (enable_text_input==false)
    {
        str = "";
        return;
    }
        if (str!=text_input)
            str = text_input;


    if( event.type == SDL_KEYDOWN )
    {
        debug_print(std::string("KeyEvent"));
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if( str.length() <= 128 )
        {
            //isprint is character printable
            if (isprint(event.key.keysym.sym)){
                str += (char)event.key.keysym.sym ;
                //debug_print(_SR((char)event.key.keysym.sym));
            }
        if( str != temp )
        {
            //std::cout<<str<<std::endl;
            text_input = str;
            //Free the old surface
           // SDL_FreeSurface( text );

            //Render a new text surface
           // text = TTF_RenderText_Solid( font, str.c_str(), textColor );
        }
    }
    }
    // SDL_EnableUNICODE( SDL_DISABLE );

}

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{

    WorldEngine->FinEngine();
    SDL_Quit();
    exit(rc);
}

void GX_Engine::FinEngine(void)
{
    SDL_WaitThread(thread,nullptr);
}



/*
//void switchHelm(void *n,int l)
//{
//    (void)n; (void)l;
//    static int count = 0;
//    static TGraphic *working = findGraphic(boxes,"helm");
//    static string helm1 = "bars/equip/helm_glorious_dawn.png";
//    static string helm2 = "bars/equip/helm_runemaster.png";
//    if (working==nullptr)
//    {
//        fprintf(stderr,"_event_[SWITCH_HELM] working = nullptr\n");
//        //working = findGraphic(boxes,"helm");
//        return;
//    }
//    if (count==0)
//    {
//        working->tex = new GXTexture(helm2);
//    }else if (count==1)
//    {
//        working->tex = new GXTexture(helm1);
//    }
//    count = (count+1)%2;

//}

//void testFunc(void *n,int l)
//{
//    (void)n; (void)l;
//    static TGraphic *working = findGraphic(boxes,"helm");
//    if (working==nullptr)
//    {
//        // nada
//    }else
//    {
//        working->visible ^= true;
//    }
//}
*/
void ToggleMenu(void *n,int l)
{
    //
    //(void)n;
    static bool vis = true;
    static gx_menu *working = findMenu(boxes,"[WEAPON]");
    if (working==nullptr)
        return;
    if (l>0){

    string *pass = (string *)n;
    working->caption->Text=(*pass);

    }
    working->SetVisibility(vis);
    vis = vis ^ true;
}

std::vector<TEquip> equipment;


void LoadEquipment(void)
{
    QXmlSimpleReader reader;
    XmlHandler nuke;
    nuke.link(&equipment);
    reader.setContentHandler(&nuke);
    reader.setErrorHandler(&nuke);
    QFile file("equip_data.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    if (file.exists())
        std::cout<<"Cha, Cha\n";
    else
        std::cout<<"Does not exsist\n";

    QXmlInputSource xmlInputSource(&file);
    if (reader.parse(xmlInputSource))
        std::cout<<"File Loaded\n";
    else
        std::cout<<"Failed\n";


    Champion.SetName("MwKz");
    for(size_t i = 0; i < 8; i++)
        Champion.invent.AddItem(&equipment[equipment.size()-(8-i)]);
    Champion.invent.SetMainhand(0);
    Champion.invent.SetOffhand(1);
    Champion.invent.SetHelm(2);
    Champion.invent.SetChest(3);
    Champion.invent.SetGloves(4);
    Champion.invent.SetPants(5);
    Champion.invent.SetBoots(6);
    Champion.invent.SetRing(7);
    Champion.hero_stats.Print();
    Champion.PrintEquip();

}

std::vector<std::string> game_arc = {
    "Scenes/armor/armor.xml",
//    "Scenes/battle/load.xml",
    "Scenes/stats/stats.xml",
    "Scenes/base/base.rxl"
};

void GX_Engine::RunEngine(void)
{
    LoadEquipment();

    ilInit();
    iluInit();
    ilutRenderer(ILUT_OPENGL);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL video subsystem: %s\n", SDL_GetError());
        return;
    }

    /* Test showing a message box with a parent window */

        //SDL_Event event;
        hWindow = SDL_CreateWindow("Game Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   window_w, window_h, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);


        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        glEnable(GL_MULTISAMPLE);

        context = SDL_GL_CreateContext(hWindow);
        // Has to be after context is created
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            return;
        }
        if (context==nullptr)
        {
            printf("failed context\n");
            return;
        }
        if( SDL_GL_SetSwapInterval( 1 ) < 0 )
        {
            printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
        }
        pud = SDL_CreateMutex();
        if (pud==nullptr)
        {
            printf("error could not create mutex\n");

        }
        if (SDL_LockMutex(pud) == 0) {
          /* Do stuff while mutex is locked */
            SDL_UnlockMutex(pud);
        } else {
          fprintf(stderr, "Couldn't lock mutex\n");
        }
        WorldEngine->Init();
        thread = SDL_CreateThread(&RenderScene, "Render_Window", nullptr);
        if (thread==NULL){
            std::cout<<"FUCK A Duck \n";
            printf("SDL_Init failed: %s\n", SDL_GetError());
        }
#ifdef USE_MISC_SHADER
//    VertexShader vertToon ("shaders/test.vert");
//    FragmentShader fragToon ("shaders/test.frag");
//    shader = new ShaderProgram ("test", vertToon, fragToon);
#endif
#ifdef USE_FALLBACK_FONT
        FontInit();
#endif

//#pragma message "This is Where the  Sprite Is Init " __line__
    //cout<<__PRETTY_FUNCTION__<<" Cool\n";'
    int success_load = 0;
    int success_last = 0;
    vector<TPrimative *> working;
    for(auto item:game_arc)
    {
        success_load += LoadPrimativesXT(item,working);
        if (success_load!=success_last)
        {
            WorldEngine->layers.push_back(working);
            for(auto *t:working)
            {
                t->layer = success_load;

                boxes.push_back(t);
            }

            std::cout << "Loaded [" << success_load << "]" << item << " successfully!\n";
            success_last = success_load;
        }else
        {
            std::cout << "Failed! to load " << item << " map!\n";
        }
        working.clear();

    }
    if ((size_t)success_load!=game_arc.size())
    {
        DBG_msg("Failed to load assets!");
    }else
        loaded = true;
//    bool ld = LoadPrimativesXT("Scenes/armor/armor.xml",boxes);
//    ld |=  LoadPrimativesXT("Scenes/base/base.rxl",boxes);
//    loaded = ld;
    //loaded = LoadPrimativesFromXMLDocument("Scenes/battle/load.xml",boxes);
  //  gx_menu *menu = new gx_menu(0,100,window_w,window_h-100);
  //  menu->alias = "[WEAPON]";

    /*** Begin Adding Elements ***/

//    TContext cntx = {TGraphic("panel.png",15,175),
//                     TGraphic("bars/item_slot.png",25,175),
//                     TGraphic("bars/dogs.jpg",25,175),
//                     TLabel(40, 0,"[NAME]"),
//                     TLabel(40,20,"[BLAH]"),
//                     TLabel(40,40,"[BLAH]"),
//                     TLabel(40,60,"[BLAH]"),
//                     TLabel(40,80,"[BLAH]")};
//    cntx.itm_bck.SetSize(110,110);
//    cntx.itm_pic.SetSize(96,96);
//    cntx.itm_box.SetSize(window_w-32,148);
//    TContext zntx = cntx;
//    menu->AddMenuItem(cntx);
//    menu->AddMenuItem(zntx);

//   TGraphic *grp = new TGraphic("bars/menu_exit.png",window_w-48-13,110);
//    grp->SetSize(48,48);
//    grp->SetClickable(1);
//    grp->SetOnclickFunc(ToggleMenu);
//    menu->GetEXT(grp);

   // _exit_btn;
//    TGraphic *grap = new TGraphic("bars/dogs.jpg",0,0);
//    grap->SetSize(96,96);
//    grap->SetClickable(1);
//    grap->SetOnclickFunc(testFunc);
//    menu->AddMenuItem(grap);

//    TGraphic *grp = new TGraphic("bars/immortal.jpg",0,0);
//    grp->SetSize(96,96);
//    grp->SetClickable(1);
//    grp->SetOnclickFunc(switchHelm);

//    menu->AddMenuItem(grp);

//    findGraphic(boxes,"[HELM_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[MAIN_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[OFFH_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[CHES_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[PANT_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[GLOV_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[BOOT_SLOT]")->SetOnclickFunc(ToggleMenu);
//    findGraphic(boxes,"[RING_SLOT]")->SetOnclickFunc(ToggleMenu);

//    //grap->SetOnclickFunc(testFunc);

//    menu->SetAndUseBackgroundImage("bars/menu_back.png",window_w,window_h-100);
    /// Add Menu to display list;

//    boxes.push_back(menu);


//    if (loaded==true)
//    {
//        std::cout<<"Loaded Primatives\n";
//    }




    while (!done)
    {
        // message processing loop
        TheInputHandler::Instance()->update();
        SDL_GetMouseState(&msx.x,&msx.y);
        msx.LeftButtonDown   = SDL_GetMouseState(nullptr,nullptr) & SDL_BUTTON(1);
        msx.MiddleButtonDown = SDL_GetMouseState(nullptr,nullptr) & SDL_BUTTON(2);
        msx.RightButtonDown  = SDL_GetMouseState(nullptr,nullptr) & SDL_BUTTON(3);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            TextHandle(event);
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    //printf("key: %d\n",event.key.keysym.scancode);
                    if (event.key.keysym.scancode == SDL_SCANCODE_F2)
                    {

                        fprintf(stdout,"[dbg_info] reloading file\n");
                        loaded = false;
                        fprintf(stdout,"[dbg_info] empty boxes\n");
                        boxes.empty();
                        boxes.clear();
                        while (!loaded)
                        {
                            loaded = LoadPrimativesFromXMLDocument("Scenes/battle/load.xml",boxes);
                        }
                        fprintf(stdout,"[dbg_info] finished reloading file\n");
                        break;
                    }
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;

                }
            } // end switch
            keys = SDL_GetKeyboardState(NULL);
        } // end of message processing
    } // end main loop

#ifdef UNREAL
    quit(0);
#endif
    done = true;
}
