#include "gx_sprite.h"

int GXSprite::spriteCount = 0;

GXSprite::GXSprite():lasttime(0)
{
    texture = nullptr;
    qm       = QuikQuad(0,0,0,0,0);

    tm       = QuikTexMap(0.0,1.0,
                          1.0,1.0,
                          1.0,0.0,
                          0.0,0.0);
    xyz     = Vec3(0.0,0.0,0.0);
    dim     = Vec2(0.0,0.0);
    clip    = Vec2(0.0,0.0);
    div     = Vec2(0.0,0.0);
    idx     = 0;
    theata  = 0.0f;
    adx     = -1;
    flipped = false;
    spriteCount++;
}


GXSprite::GXSprite(GXTexture *tex,const GXSprite &g):lasttime(0)
{
    texture      = tex;
    qm           = g.qm;
    tm           = g.tm;
    xyz          = Vec3(0.0,0.0,0.0);
    dim          = Vec2(g.dim.x,g.dim.y);
    clip         = Vec2(g.clip.x,g.clip.y);
    idx          = 0;
    theata       = 0.0f;
    __Animations = g.__Animations;
    adx          = g.adx;
    flipped      = g.flipped;
    div          = g.div;
    spriteCount++;
}

GXSprite::GXSprite(/*const*/ const GXSprite &gxs):lasttime(0)
{
    std::cout<<"Create From gxsprite\n";
    (*this) = gxs;
    std::cout<<"texture "<<texture->texID<<"\n"
             <<"dim "<<dim.x<<":"<<dim.y<<"\n"
             <<"xyz "<<xyz.x<<":"<<xyz.y<<":"<<xyz.z<<"\n";
//    texture = gxs.texture;//&gxs.texture;
//    xyz     = gxs.xyz;
//    dim     = gxs.dim;
//    clip    = gxs.clip;
//    idx     = gxs.idx;
//    theata  = gxs.theata;
//    adx     = gxs.adx;
//    __Animations = gxs.__Animations;

    spriteCount++;
}

GXSprite::GXSprite(string fn, ripdef *rc):lasttime(0)
{
    texture  = new GXTexture(fn,rc);
    qm       = QuikQuad(0,0,0,texture->width,texture->height);
    tm       = QuikTexMap(0.0,1.0,
                          1.0,1.0,
                          1.0,0.0,
                          0.0,0.0);
    xyz     = Vec3(0.0,0.0,0.0);
    dim     = Vec2(texture->width,texture->height);
    clip    = Vec2(texture->width,texture->height);
    div     = dim/clip;
    idx     = 0;
    theata  = 0.0f;
    adx     = -1;
    flipped = false;

    spriteCount++;
}

GXSprite& GXSprite::operator = (const GXSprite & gxs)
{
    std::cout << "GXSprite Equate OP\n";
    texture = (GXTexture *)gxs.texture;
    xyz     = gxs.xyz;
    dim     = gxs.dim;
    clip    = gxs.clip;
    idx     = gxs.idx;
    theata  = gxs.theata;
    adx     = gxs.adx;
    __Animations = gxs.__Animations;
    lasttime = 0;
    return (*this);
}

void GXSprite::StepAn(SprAnimation &input,long time)//input
{
    if (input.Anim==false)
    {
        return;
    }

    long newTime = time;
    if (newTime-input.LastTime > input.UpdateTime)
    {

        input.Index = (input.Index+1)%input.IndexSize;
        if ((input.Index==(input.IndexSize-1))&&input.Loops==false)
            input.Anim=false;
        input.LastTime=newTime;

    }
}

void GXSprite::AddAnimation(int __index, int __index_size, long __lasttime, long __updatetime, int __base, bool __loop)
{
    __Animations.Add(SprAnimation(__index,__index_size,__lasttime,__updatetime,__base,__loop));
}

void GXSprite::SetAnim(int i)
{
    if (i<=(__Animations.Size()-1))
            adx = i;
}

void GXSprite::SetClip(Vec2 v)
{
    clip = v;
}

void GXSprite::SetClip(float w,float h)
{
    clip.Set(w,h);
}

void GXSprite::SetSize(float w, float h)
{
    dim.Set(w,h);
    qm = QuikQuad(0,0,0,w,h);
}

void GXSprite::SetCoord(float x, float y, float z)
{
    xyz.Set(x,y,z);
}

void GXSprite::Update(long t)
{
    if ((t-lasttime)>50)
    {
//        std::cout<<"v "<<velocity.x<<":"<<velocity.y<<":"<<velocity.z<<"\n";
//        xyz += velocity ;//* 0.9;
//        velocity *= Vec3(0.1,0,0);
//        if (velocity<Vec3(0.1,0,0)){
//            velocity = Vec3(0,0,0);
//        }
        lasttime = t;
    }
    if (adx>-1)
    {
        StepAn(__Animations.BigDaddy().at(adx),t);
         idx       =  __Animations.BigDaddy().at(adx).GetCurrent();
    }
}

void GXSprite::Draw(void)
{

    if (texture!=nullptr)
        glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texture->texID);
    glColor4f(1,1,1,1);
    CalculateExtTex(idx);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    QuikTexMap tmp = tm;
    if (flipped){
        //SWAP();
/*
    tm       = QuikTexMap(0.0,1.0,
                          1.0,1.0,
                          1.0,0.0,
                          0.0,0.0);
  */
        tm.LongSet(tmp.s1,tmp.r0,    tmp.s0,tmp.r1,
                   tmp.s3,tmp.r2,    tmp.s2,tmp.r3);
    }
    glTranslated(xyz.x,xyz.y,xyz.z);
    if (theata!=0.0){
        glRotated(theata,0.0,0.0,1.0);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    if (texture!=nullptr)
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0,&qm);
    if (texture!=nullptr)
        glTexCoordPointer(2,GL_FLOAT, 0,&tm);
    glDrawArrays(GL_POLYGON, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    if (texture!=nullptr)
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    tm = tmp;
}

void GXSprite::CalculateExtTex(int index)
{
    int  _tw = texture->width;
    int  _th = texture->height;

    int x = clip.x;
    int y = clip.y;
    float tDivX,tDivY;
    int eX = _tw/x;
    //int eY = _th/y;
    //int SprCount=(_tw / x)*(_th / y);


    tDivX = 1.0/(float)(_tw / x);
    tDivY = 1.0/(float)(_th / y);


    float cx =  (float)(index % (int)(eX))*tDivX;///(_tw / x);
    float cy =  (float)(index / (int)(eX/*eY/2*/))*tDivY;///((int)(_th / y));

    tm.LongSet(cx            ,cy+tDivY      ,
               cx+tDivX      ,cy+tDivY      ,
               cx+tDivX      ,cy,
               cx            ,cy);

}

void GXSprite::CalculateExtTexA(int index)
{
    index = index;

}
void GXSprite::UpdateMovement(long t)
{
    t = t;
//    static bool g = false;
//    if (!jump||g)
//    {
//        g=false;
//        return;

//    }
//    static long lasttime = t;
//    if (1&&position.YComponent()==collisonPos.YComponent())
//        lasttime =  t;
//        float delta = 1.0;//(float)(t - lasttime)*0.001f;//1000.0f;
//        //float delta = 12.0f;
//        //velocity += acceleration * change / 2;
//       // position += velocity * change;
//        velocity +=acceleration*delta;
//        if  (velocity.GetV1()>0)
//            isFalling==true;
//        //velocity += (acceleration*delta*delta);
//        position += velocity/2;//*delta;
//        printf("change<>%.2f\n",delta);
//        if (collison==true&&delta>0)//position.GetV1() > 250.0f
//        {
//            //velocity.y = velocity.y * -bounciness;
//            position.SetV1(collisonPos.GetV1()-1) ;//= 0.0f;
//            acceleration.Set(0.0,1.35);
//            velocity.Set(0,0);
//            lasttime=t;
//            isJumping=false;
//        }
//        g=collison;
//        SetCoord(position.GetV0(),position.GetV1());
//        //lasttime =  t;
}
