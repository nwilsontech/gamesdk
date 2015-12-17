#ifndef GX_COLOR_H
#define GX_COLOR_H

#include <map>
#include <string>
#include "gx_util.h"
using namespace std;

class TFloat
{
public:
    TFloat(const TFloat &pass)
    {
        r = pass.r;  g = pass.g; b  = pass.b;
    }
    TFloat(float i,float j,float k)
    {
        r = i;
        g = j;
        b = k;
    }
    TFloat()
    {
        r = 1.0;
        g = 1.0;
        b = 1.0;
    }

    operator float* () const {return (float*) this;}
    operator const float* () const {return (const float*) this;}
public:
    float r;
    float g;
    float b;
};
/// Want to know if changing this from a static to constexpr will work
static std::map<string, TFloat> ColorTable = {{"aliceblue", TFloat(0.941f, 0.973f, 1.000f)},
                                       {"antiquewhite", TFloat(0.980f, 0.922f, 0.843f)},
                                       {"aqua", TFloat(0.000f, 1.000f, 1.000f)},
                                       {"aquamarine", TFloat(0.498f, 1.000f, 0.831f)},
                                       {"azure", TFloat(0.941f, 1.000f, 1.000f)},
                                       {"beige", TFloat(0.961f, 0.961f, 0.863f)},
                                       {"bisque", TFloat(1.000f, 0.894f, 0.769f)},
                                       {"black", TFloat(0.000f, 0.000f, 0.000f)},
                                       {"blanchedalmond", TFloat(1.000f, 0.922f, 0.804f)},
                                       {"blue", TFloat(0.000f, 0.000f, 1.000f)},
                                       {"blueviolet", TFloat(0.541f, 0.169f, 0.886f)},
                                       {"brown", TFloat(0.647f, 0.165f, 0.165f)},
                                       {"burlywood", TFloat(0.871f, 0.722f, 0.529f)},
                                       {"cadetblue", TFloat(0.373f, 0.620f, 0.627f)},
                                       {"chartreuse", TFloat(0.498f, 1.000f, 0.000f)},
                                       {"chocolate", TFloat(0.824f, 0.412f, 0.118f)},
                                       {"coral", TFloat(1.000f, 0.498f, 0.314f)},
                                       {"cornflowerblue", TFloat(0.392f, 0.584f, 0.929f)},
                                       {"cornsilk", TFloat(1.000f, 0.973f, 0.863f)},
                                       {"crimson", TFloat(0.863f, 0.078f, 0.235f)},
                                       {"cyan", TFloat(0.000f, 1.000f, 1.000f)},
                                       {"darkblue", TFloat(0.000f, 0.000f, 0.545f)},
                                       {"darkcyan", TFloat(0.000f, 0.545f, 0.545f)},
                                       {"darkgoldenrod", TFloat(0.722f, 0.525f, 0.043f)},
                                       {"darkgray", TFloat(0.663f, 0.663f, 0.663f)},
                                       {"darkgreen", TFloat(0.000f, 0.392f, 0.000f)},
                                       {"darkgrey", TFloat(0.663f, 0.663f, 0.663f)},
                                       {"darkkhaki", TFloat(0.741f, 0.718f, 0.420f)},
                                       {"darkmagenta", TFloat(0.545f, 0.000f, 0.545f)},
                                       {"darkolivegreen", TFloat(0.333f, 0.420f, 0.184f)},
                                       {"darkorange", TFloat(1.000f, 0.549f, 0.000f)},
                                       {"darkorchid", TFloat(0.600f, 0.196f, 0.800f)},
                                       {"darkred", TFloat(0.545f, 0.000f, 0.000f)},
                                       {"darksalmon", TFloat(0.914f, 0.588f, 0.478f)},
                                       {"darkseagreen", TFloat(0.561f, 0.737f, 0.561f)},
                                       {"darkslateblue", TFloat(0.282f, 0.239f, 0.545f)},
                                       {"darkslategray", TFloat(0.184f, 0.310f, 0.310f)},
                                       {"darkslategrey", TFloat(0.184f, 0.310f, 0.310f)},
                                       {"darkturquoise", TFloat(0.000f, 0.808f, 0.820f)},
                                       {"darkviolet", TFloat(0.580f, 0.000f, 0.827f)},
                                       {"deeppink", TFloat(1.000f, 0.078f, 0.576f)},
                                       {"deepskyblue", TFloat(0.000f, 0.749f, 1.000f)},
                                       {"dimgray", TFloat(0.412f, 0.412f, 0.412f)},
                                       {"dimgrey", TFloat(0.412f, 0.412f, 0.412f)},
                                       {"dodgerblue", TFloat(0.118f, 0.565f, 1.000f)},
                                       {"firebrick", TFloat(0.698f, 0.133f, 0.133f)},
                                       {"floralwhite", TFloat(1.000f, 0.980f, 0.941f)},
                                       {"forestgreen", TFloat(0.133f, 0.545f, 0.133f)},
                                       {"fuchsia", TFloat(1.000f, 0.000f, 1.000f)},
                                       {"gainsboro", TFloat(0.863f, 0.863f, 0.863f)},
                                       {"ghostwhite", TFloat(0.973f, 0.973f, 1.000f)},
                                       {"gold", TFloat(1.000f, 0.843f, 0.000f)},
                                       {"goldenrod", TFloat(0.855f, 0.647f, 0.125f)},
                                       {"gray", TFloat(0.502f, 0.502f, 0.502f)},
                                       {"green", TFloat(0.000f, 0.502f, 0.000f)},
                                       {"greenyellow", TFloat(0.678f, 1.000f, 0.184f)},
                                       {"grey", TFloat(0.502f, 0.502f, 0.502f)},
                                       {"honeydew", TFloat(0.941f, 1.000f, 0.941f)},
                                       {"hotpink", TFloat(1.000f, 0.412f, 0.706f)},
                                       {"indianred", TFloat(0.804f, 0.361f, 0.361f)},
                                       {"indigo", TFloat(0.294f, 0.000f, 0.510f)},
                                       {"ivory", TFloat(1.000f, 1.000f, 0.941f)},
                                       {"khaki", TFloat(0.941f, 0.902f, 0.549f)},
                                       {"lavender", TFloat(0.902f, 0.902f, 0.980f)},
                                       {"lavenderblush", TFloat(1.000f, 0.941f, 0.961f)},
                                       {"lawngreen", TFloat(0.486f, 0.988f, 0.000f)},
                                       {"lemonchiffon", TFloat(1.000f, 0.980f, 0.804f)},
                                       {"lightblue", TFloat(0.678f, 0.847f, 0.902f)},
                                       {"lightcoral", TFloat(0.941f, 0.502f, 0.502f)},
                                       {"lightcyan", TFloat(0.878f, 1.000f, 1.000f)},
                                       {"lightgoldenrodyellow", TFloat(0.980f, 0.980f, 0.824f)},
                                       {"lightgray", TFloat(0.827f, 0.827f, 0.827f)},
                                       {"lightgreen", TFloat(0.565f, 0.933f, 0.565f)},
                                       {"lightgrey", TFloat(0.827f, 0.827f, 0.827f)},
                                       {"lightpink", TFloat(1.000f, 0.714f, 0.757f)},
                                       {"lightsalmon", TFloat(1.000f, 0.627f, 0.478f)},
                                       {"lightseagreen", TFloat(0.125f, 0.698f, 0.667f)},
                                       {"lightskyblue", TFloat(0.529f, 0.808f, 0.980f)},
                                       {"lightslategray", TFloat(0.467f, 0.533f, 0.600f)},
                                       {"lightslategrey", TFloat(0.467f, 0.533f, 0.600f)},
                                       {"lightsteelblue", TFloat(0.690f, 0.769f, 0.871f)},
                                       {"lightyellow", TFloat(1.000f, 1.000f, 0.878f)},
                                       {"lime", TFloat(0.000f, 1.000f, 0.000f)},
                                       {"limegreen", TFloat(0.196f, 0.804f, 0.196f)},
                                       {"linen", TFloat(0.980f, 0.941f, 0.902f)},
                                       {"magicgreen",TFloat(0.0f,0.9f,0.0f)},
                                       {"magenta", TFloat(1.000f, 0.000f, 1.000f)},
                                       {"maroon", TFloat(0.502f, 0.000f, 0.000f)},
                                       {"mediumaquamarine", TFloat(0.400f, 0.804f, 0.667f)},
                                       {"mediumblue", TFloat(0.000f, 0.000f, 0.804f)},
                                       {"mediumorchid", TFloat(0.729f, 0.333f, 0.827f)},
                                       {"mediumpurple", TFloat(0.576f, 0.439f, 0.859f)},
                                       {"mediumseagreen", TFloat(0.235f, 0.702f, 0.443f)},
                                       {"mediumslateblue", TFloat(0.482f, 0.408f, 0.933f)},
                                       {"mediumspringgreen", TFloat(0.000f, 0.980f, 0.604f)},
                                       {"mediumturquoise", TFloat(0.282f, 0.820f, 0.800f)},
                                       {"mediumvioletred", TFloat(0.780f, 0.082f, 0.522f)},
                                       {"midnightblue", TFloat(0.098f, 0.098f, 0.439f)},
                                       {"mintcream", TFloat(0.961f, 1.000f, 0.980f)},
                                       {"mistyrose", TFloat(1.000f, 0.894f, 0.882f)},
                                       {"moccasin", TFloat(1.000f, 0.894f, 0.710f)},
                                       {"navajowhite", TFloat(1.000f, 0.871f, 0.678f)},
                                       {"navy", TFloat(0.000f, 0.000f, 0.502f)},
                                       {"oldlace", TFloat(0.992f, 0.961f, 0.902f)},
                                       {"olive", TFloat(0.502f, 0.502f, 0.000f)},
                                       {"olivedrab", TFloat(0.420f, 0.557f, 0.137f)},
                                       {"orange", TFloat(1.000f, 0.647f, 0.000f)},
                                       {"orangered", TFloat(1.000f, 0.271f, 0.000f)},
                                       {"orchid", TFloat(0.855f, 0.439f, 0.839f)},
                                       {"palegoldenrod", TFloat(0.933f, 0.910f, 0.667f)},
                                       {"palegreen", TFloat(0.596f, 0.984f, 0.596f)},
                                       {"paleturquoise", TFloat(0.686f, 0.933f, 0.933f)},
                                       {"palevioletred", TFloat(0.859f, 0.439f, 0.576f)},
                                       {"papayawhip", TFloat(1.000f, 0.937f, 0.835f)},
                                       {"peachpuff", TFloat(1.000f, 0.855f, 0.725f)},
                                       {"peru", TFloat(0.804f, 0.522f, 0.247f)},
                                       {"pink", TFloat(1.000f, 0.753f, 0.796f)},
                                       {"plum", TFloat(0.867f, 0.627f, 0.867f)},
                                       {"powderblue", TFloat(0.690f, 0.878f, 0.902f)},
                                       {"purple", TFloat(0.502f, 0.000f, 0.502f)},
                                       {"red", TFloat(1.000f, 0.000f, 0.000f)},
                                       {"rosybrown", TFloat(0.737f, 0.561f, 0.561f)},
                                       {"royalblue", TFloat(0.255f, 0.412f, 0.882f)},
                                       {"saddlebrown", TFloat(0.545f, 0.271f, 0.075f)},
                                       {"salmon", TFloat(0.980f, 0.502f, 0.447f)},
                                       {"sandybrown", TFloat(0.957f, 0.643f, 0.376f)},
                                       {"seagreen", TFloat(0.180f, 0.545f, 0.341f)},
                                       {"seashell", TFloat(1.000f, 0.961f, 0.933f)},
                                       {"sienna", TFloat(0.627f, 0.322f, 0.176f)},
                                       {"silver", TFloat(0.753f, 0.753f, 0.753f)},
                                       {"skyblue", TFloat(0.529f, 0.808f, 0.922f)},
                                       {"slateblue", TFloat(0.416f, 0.353f, 0.804f)},
                                       {"slategray", TFloat(0.439f, 0.502f, 0.565f)},
                                       {"slategrey", TFloat(0.439f, 0.502f, 0.565f)},
                                       {"snow", TFloat(1.000f, 0.980f, 0.980f)},
                                       {"springgreen", TFloat(0.000f, 1.000f, 0.498f)},
                                       {"steelblue", TFloat(0.275f, 0.510f, 0.706f)},
                                       {"tan", TFloat(0.824f, 0.706f, 0.549f)},
                                       {"teal", TFloat(0.000f, 0.502f, 0.502f)},
                                       {"thistle", TFloat(0.847f, 0.749f, 0.847f)},
                                       {"tomato", TFloat(1.000f, 0.388f, 0.278f)},
                                       {"turquoise", TFloat(0.251f, 0.878f, 0.816f)},
                                       {"violet", TFloat(0.933f, 0.510f, 0.933f)},
                                       {"wheat", TFloat(0.961f, 0.871f, 0.702f)},
                                       {"white", TFloat(1.000f, 1.000f, 1.000f)},
                                       {"whitesmoke", TFloat(0.961f, 0.961f, 0.961f)},
                                       {"yellow", TFloat(1.000f, 1.000f, 0.000f)},
                                       {"yellowgreen", TFloat(0.604f, 0.804f, 0.196f)}};
TFloat GetColor(string name);
TFloat ColorHSV(float h, float s, float v);
TFloat HSLtoCol(float h,float s,float l);

#endif // GX_COLOR_H
