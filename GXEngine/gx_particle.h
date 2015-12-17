#ifndef GX_PARTICLE_H
#define GX_PARTICLE_H
#include "gx_types.h"
#include "gx_sprite.h"
#include <vector>
#include <list>

using std::list;
using std::vector;

class GXParticle{
public:
    GXParticle(int ID);
    void Update(long time);
public:
    int   id;
    long lasttime;
    Vec3  color;
    Vec3  position;
    Vec3  velocity;
    Vec3  acceleration;
    Vec3  rotation;
    float totalLife;
    float life;
    float alpha;
    float size;
    float bounciness;
    bool  active;
    float floor;
    float angle;
};

class GXEmitter{
public:
    GXEmitter();
    ~GXEmitter();
    void Update(long time);
    void SetTexture(GXSprite *texture);

protected:
    void addParticle(void);
    float frand(float start = 0,float end = 1);

public:
    list<GXParticle *> particles;

    GXSprite *tex;
    long lastTime;
    ///
    ///Attribs
    ///
    float emissionRate;
    float emissionRadius;
    float life;
    float lifeRange;
    float size;
    float sizeRange;
    float saturation;
    float alpha;
    float spread;
    float gravity;
    float floor;
    Vec3  position;
    Vec3  wind;
    Vec3  rotation;

    Vec3 emissionAngle;

};



#endif // GX_PARTICLE_H
