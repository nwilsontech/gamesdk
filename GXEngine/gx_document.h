#ifndef GX_DOCUMENT_H
#define GX_DOCUMENT_H


#include "gx_primatives.h"
#include "gx_rect.h"
#include "gx_rect_adv.h"
#include "gx_healthbar.h"
#include "gx_caption.h"
#include "gx_graphic.h"
#include "gx_ex_healthbar.h"
#include "gx_group.h"
#include "gx_menu.h"

//void LoadPrimativesFromDocument(string Doc, vector<TPrimative *> &loadout);
bool LoadPrimativesFromXMLDocument(string Doc, vector<TPrimative *> &loadout);
bool LoadPrimativesXT(string Doc, vector<TPrimative *> &loadout);
#endif // GX_DOCUMENT_H
