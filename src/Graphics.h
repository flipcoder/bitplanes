#ifndef _GRAPHICS_H
#define _GRAPHICS_H

//#include "GfxAPI.h"
#include "Util.h"
#include "math/common.h"

class Color
{
    float saturate(float f){
        if(f>1.0f)
            f=1.0f;
        else if(f<0.0f)
            f=0.0f;
        return f;
    }

    void parseHex(const char* p) {
        assert(p);
        // TODO: hex string -> color parsing
    }

public:

    union {
        struct { float r, g, b, a; };
        float c[4];
    };

    Color():
        r(1.0f),
        g(1.0f),
        b(1.0f),
        a(1.0f) {}

    Color(const Color& c){
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }
    explicit Color(float s, float _a = 1.0f):
        r(s),
        g(s),
        b(s),
        a(_a) {}
    Color(float _r, float _g, float _b, float _a = 1.0f):
        r(_r),
        g(_g),
        b(_b),
        a(_a)
    {}
    explicit Color(unsigned char s, unsigned char _a = 255):
        r(s/255.0f),
        g(s/255.0f),
        b(s/255.0f),
        a(_a/255.0f)
    {}
    Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255):
        r(_r/255.0f),
        g(_g/255.0f),
        b(_b/255.0f),
        a(_a/255.0f)
    {}
    Color(std::string hex):r(1.0f),
        g(1.0f),
        b(1.0f),
        a(1.0f) 
    {
        //hex
        //if(hex.legnth()==6 || hex.length()==8)
        //{
        //    unsigned int len = 0;
        //    for(int i=0; i<hex.length(); i+=2)
        //    {
        //        hex[i]
        //    }
        //}
    }

    Color& operator+=(float f) {
        r+=f;
        b+=f;
        g+=f;
        saturate();
        return *this;
    }

    Color& operator-=(float f) {
        r-=f;
        b-=f;
        g-=f;
        saturate();
        return *this;
    }

    Color operator*=(float f) {
        r*=f;
        b*=f;
        g*=f;
        a*=f;
        saturate();
        return *this;
    }
    Color operator*=(Color& c) {
        r*=c.r;
        b*=c.b;
        g*=c.g;
        a*=c.a;
        saturate();
        return *this;
    }
    
    void saturate() {
        r = saturate(r);
        b = saturate(b);
        g = saturate(g);
        a = saturate(a);
    }

    void set(float _c) { r=g=b=saturate(_c); }
    void set(float _c, float _a) { r=g=b=saturate(_c); a=saturate(_a); }
    void set(float _r, float _g, float _b) {
        r=_r; b=_b; g=_g; saturate();
    }
    void set(float _r, float _g, float _b, float _a) {
        r=_r; b=_b; g=_g; a=_a; saturate();
    }
    void white() { r=g=b=1.0f; }
    void black() { r=g=b=0.0f; }
    void white(float _a) { r=g=b=1.0f; a=saturate(_a); }
    void black(float _a) { r=g=b=0.0f; a=saturate(_a); }
    unsigned char getRedUB() const { return (unsigned char)round_int(255*r); }
    unsigned char getGreenUB() const { return (unsigned char)round_int(255*g); }
    unsigned char getBlueUB() const { return (unsigned char)round_int(255*b); }
    float* array() const { return (float*)&c[0]; }

    void allegro(const ALLEGRO_COLOR& ac) {
        al_unmap_rgba_f(ac,&r,&g,&b,&a);
    }
    ALLEGRO_COLOR allegro() const {
        return al_map_rgba_f(r,g,b,a);
    }

    //void glColor() const { glColor4fv(array()); }
    //void glColor(float _a) const { glColor4f(r, g, b, _a); }
    //void apply() const { glColor4fv(array()); }
    //void apply(float _a) const { glColor4f(r, g, b, _a); }
    //static void apply(Color c) {
    //    glColor4fv(c.array());
    //}
};

#endif


