TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
QT     += xml



OBJECTS_DIR += $$PWD/.obj

INCLUDEPATH += -I/usr/include/freetype2
INCLUDEPATH += -L/usr/lib/
INCLUDEPATH += $$PWD/

SOURCES += main.cpp \
    GXEngine/gx_engine.cpp \
    GXEngine/gx_rect.cpp \
    GXEngine/gx_util.cpp \
    GXEngine/gx_primative.cpp \
    GXEngine/gx_color.cpp \
    GXEngine/gx_types.cpp \
    GXEngine/gx_rect_adv.cpp \
    GXEngine/gx_healthbar.cpp \
    GXEngine/gx_graphic.cpp \
    GXEngine/gx_document.cpp \
    GXEngine/gx_caption.cpp \
    GXEngine/font.cpp \
    GXEngine/gx_texture.cpp \
    GXEngine/gx_ex_healthbar.cpp \
    GXShader/Shader.cpp \
    GXEngine/gx_console.cpp \
    GXEngine/gxparticalsys.cpp \
    GXEngine/gx_sprite.cpp \
    GXEngine/gx_inputhandler.cpp \
    GXEngine/gx_collisions.cpp \
    GXEngine/gx_particle.cpp \
    GXEngine/gx_group.cpp \
    GXEngine/gx_menu.cpp \
    GXEngine/gx_functions.cpp \
    GXEngine/gx_logical_engine.cpp \
    GXEngine/engine.cpp \
    GXEngine/gx_dbg.cpp \
    GXEngine/gx_experiment.cxx \
    GXEngine/gx_xml_handler.cxx \
    GXEngine/gx_expr_item_reader.cxx
# OpenGL + Glew links
LIBS += -lGLEW\
        -lGLU\
        -lGL\
        -L/usr/local/lib -lfreetype

LIBS +=            -L/usr/local/lib -lSDL2\
                   -lIL\
                   -lILU\
                   -lILUT\
                   -lftgl
LIBS += -L$$PWD/ -ltinyxml

HEADERS += \
    GXEngine/gx_engine.h \
    GXEngine/gx_logical.h \
    GXEngine/gx_primatives.h \
    GXEngine/gx_rect.h \
    GXEngine/gx_util.h \
    GXEngine/types.h \
    GXEngine/gx_color.h \
    GXEngine/gx_types.h \
    GXEngine/gx_rect_adv.h \
    GXEngine/gx_healthbar.h \
    GXEngine/gx_graphic.h \
    GXEngine/gx_document.h \
    GXEngine/gx_caption.h \
    GXEngine/font.h \
    GXEngine/binarynumbers.h \
    GXEngine/gx_texture.h \
    GXEngine/gx_variables.h \
    GXEngine/gx_ex_healthbar.h \
    GXXml/tinyxml.h \
    GXXml/tinystr.h \
    GXShader/Shader.h \
    GXEngine/gx_console.h \
    GXEngine/gxparticalsys.h \
    GXEngine/gx_sprite.h \
    GXEngine/gx_inputhandler.h \
    GXEngine/gx_collisions.h \
    GXEngine/gx_particle.h \
    GXEngine/gx_vector.hpp \
    GXEngine/gx_group.h \
    GXEngine/gx_menu.h \
    GXEngine/gx_font_manager.h \
    GXEngine/gx_simple_dbg.hxx \
    GXEngine/gx_experiment.hxx \
    GXEngine/gx_xml_handler.hxx \
    GXEngine/gx_expr_item_reader.hxx \
    GXEngine/gx_listing.hxx
