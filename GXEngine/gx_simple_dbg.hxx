#pragma once

#ifndef GX_SIMPLE_DBG_HXX
#define GX_SIMPLE_DBG_HXX

//#define USING_DBG_INFO_XTRA
#define USING_DBG_INFO

#ifdef USING_DBG_INFO
    #define debug_print(x) fprintf(stdout,"[dbg_info](%s).(%s)\n",__PRETTY_FUNCTION__,x.c_str())
#else
    #ifdef USING_DBG_INFO_XTRA
       #define debug_print(x) fprintf(stdout,"[dbg_info](%s)[%s].(%s)\n",__PRETTY_FUNCTION__,__FILE__ ,x.c_str())
    #else
       #define debug_print(x)
    #endif
#endif



#endif // GX_SIMPLE_DBG_HXX

