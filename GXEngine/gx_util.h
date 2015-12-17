#pragma once
#ifndef GX_UTIL_H
#define GX_UTIL_H
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <ostream>
#include <sstream>

void toLowerCaseSTD(std::string &str);

const char* formatStr();

//template<typename T, typename... Args>
//std::string tr(std::string &s, T value, Args... args)
//{
//    std::ostream sout;
//    auto *i = s.c_str();

//    while (*i) {
//        if(*i == '%' && *(++i) != '%'){
//            sout << value;
//            ++s;
//            tr(s,args...);
//            return;
//        }
//    }

//}

//{
//    while (*s) {
//      if (*s == '%' && *(++s) != '%') {
//         std::cout << value;
//         ++s;
//         printf(s, args...);
//         return;
//      }
//      std::cout << *s++;
//    }
//    throw std::logic_error("extra arguments provided to printf");
//}


#ifdef USING_SUPER_XPR
static void smash(std::ostream &out)
{
    out << "";
};

template <typename Head, typename... Tail>
static void smash(std::ostream &out, Head const& head, Tail const& ...tail){
  out << head;
  if (sizeof...(tail)){
      out << "";
  }
  smash(out, tail...);
};

template <typename...ARGS>
std::string vString(ARGS...args){
    std::stringstream ss;
    smash(ss,args...);
    return (ss.str());
};
#endif

#endif // GX_UTIL_H
