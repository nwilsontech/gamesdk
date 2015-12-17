#include "gx_particle.h"
#include <GL/gl.h>
#include <GL/glu.h>

GXParticle::GXParticle(int ID){
    id = ID;
    totalLife = 1.0f;
    life = 1.0f;
    alpha = 1.0f;
    size = 1.0f;
    bounciness = 0.9f;
    active = true;
    lasttime = -1;
    angle = 0.0f;
}
void GXParticle::Update(long time)
{
    if (!active)
        return;
    if (lasttime == -1)
        lasttime = time;
    float change = (float)(time-lasttime)/1000.0f;

    velocity -= acceleration * change;//+
    position -= velocity * change;//+

//    float x = position.x;
//    float y = position.y;
//    float z = position.z;
    if (position.y<0.0f){
        velocity.y = velocity.y * -bounciness;
        position.y = 0.0f;
    }

    const float fadeTime = 0.2f;
    if (totalLife-life<fadeTime)
    {
        //glColor4f()
        //change alpha
        // ((totallife - life)/fadetime *alpha);
    }else if (life < 1.0f){
        /*
         *(life *alpha);
         *
         */
    }else
    {
        // normal color;
    }

    glTranslatef(position.x,position.y,position.z);

    life -= change;
    if (life<0.0f)
        active = false;
    lasttime = time;
}





/***********************
 *   Emitter Class
 ***********************/

GXEmitter::GXEmitter(){
    lastTime        = -1;
    tex             = nullptr;
    emissionRate    = 10.0f;
    emissionRadius  = 0.0f;
    life            = 1.0f;
    lifeRange       = 0.5f;
    size            = 5.0f;
    sizeRange       = 2.0f;
    saturation      = 1.0f;
    alpha           = 0.5f;
    spread          = 1.0f;
    gravity         = 0.0f;
    floor           = 0.0f;

}

GXEmitter::~GXEmitter()
{
    for(list<GXParticle *>::iterator it = particles.begin(); it!=particles.end(); it++){
        delete (*it);
    }
}

void GXEmitter::Update(long time){

    if (tex==nullptr)
        return;
    if (lastTime==-1)
        lastTime = time;
    int numEmission = (int)((float)(time-lastTime)/1000.0 * emissionRate);

    for(int i = 0; i < numEmission; i++)
        addParticle();
    if (numEmission > 0)
        lastTime = time;
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    /**
     * @brief Draw Sprites
     */
    for(list<GXParticle *>::iterator it = particles.begin();it!=particles.end(); it++){
        GXParticle *part = (*it);
        part->floor = floor;
        part->acceleration.y = -gravity;// -
        //part->acceleration -= wind;     // +
        part->alpha = alpha;
        part->rotation = rotation;

        part->Update(time);
        if ( part->active==false)
        {
            std::cout<<"\tdying\n";
            delete part;
            list<GXParticle *>::iterator pTemp = it--;
            particles.erase(pTemp);
        }
        tex->theata = part->angle;
        tex->SetCoord(part->position.x,
                      part->position.y,
                      part->position.z);
        tex->SetSize(part->size,part->size);
        tex->Draw();
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    tex->theata = 0.0f;
}

void GXEmitter::SetTexture(GXSprite *texture){
    tex = texture;
}

float GXEmitter::frand(float start, float end)
{
    float num = (float)rand()/(float)RAND_MAX;
    return (start + (end - start) * num);
}

void GXEmitter::addParticle(){
    GXParticle *part = new GXParticle((int)particles.size());
    // GenRandom Color
//    float r = frand()*saturation+(1-saturation);
//    float g = frand()*saturation+(1-saturation);
//    float b = frand()*saturation+(1-saturation);
   // part->color = Vec3(r,g,b);
    part->angle = frand(0,360);
    part->life = frand(life - lifeRange,life + lifeRange);
    part->totalLife = part->life;
    part->velocity = Vec3(frand(-spread,0),/*frand(-spread,spread)*/1,/*frand(-spread,spread)*/0);//Vec3(frand(-spread,spread),frand(3,20),frand(-spread,spread));
    part->acceleration = Vec3(19*frand((-spread),0),-gravity,0);
    part->size = frand(size-sizeRange,size+sizeRange);
    part->position.x = position.x+frand(0,10);
    part->position.y = position.y;//+frand(-emissionRadius,emissionRadius);
    part->position.z = position.z;//+frand(-emissionRadius,emissionRadius);
    particles.push_back(part);
}

