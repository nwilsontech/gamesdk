#ifndef GX_VECTOR_HPP
#define GX_VECTOR_HPP 1

#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif
/**
 *
 *  Vector Template Modifier to allow << passing of data
 *  Created 7.2.2014
 * __attribute__(packed)
 *
 **/

using std::vector;
template <typename T>
vector<T>& operator<<(vector<T>& a, const vector<T>& b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
template <typename T,typename Y>
vector<T>& operator<<(vector<T>& a, const Y &b)
{
    a.push_back(b);
    return a;
}

#endif // GX_VECTOR_HPP
