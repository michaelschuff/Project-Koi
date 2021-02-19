//
//  Sprite.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Sprite_h
#define Sprite_h

#include "Color.h"
#include "Vector2.h"

namespace koi {
    class Sprite {
    public:
        Sprite(int32_t w, int32_t h);
        ~Sprite();
        
        int32_t width  = 0;
        int32_t height = 0;
        enum    Mode { NORMAL, PERIODIC };
        enum    Flip { NONE = 0, HORZ = 1, VERT = 2 };
        
        Color   GetPixel(const Vector2i& a   ) const;
        Color   GetPixel(int32_t x, int32_t y) const;
        bool    SetPixel(const Vector2i& a   , Color p);
        bool    SetPixel(int32_t x, int32_t y, Color p);
        Color*  GetData ();
        Color*  pColData   = nullptr;
        Mode    modeSample = Mode::NORMAL;
    };
    
    Sprite::Sprite(int32_t w, int32_t h) {
        if (pColData) delete[] pColData;
        width = w; height = h;
        pColData = new Color[width * height];
        for (int32_t i = 0; i < width * height; i++) pColData[i] = Color::BLANK;
    }
    
    Sprite::~Sprite() { if (pColData) delete[] pColData; }
    
    Color* Sprite::GetData ()                           { return pColData;              }
    Color  Sprite::GetPixel(const Vector2i& a) const    { return GetPixel(a.x, a.y   ); }
    bool   Sprite::SetPixel(const Vector2i& a, Color p) { return SetPixel(a.x, a.y, p); }
    
    Color Sprite::GetPixel(int32_t x, int32_t y) const {
        if (modeSample == Sprite::Mode::NORMAL) {
            if (x >= 0 && x < width && y >= 0 && y < height) return pColData[y * width + x];
            else                                             return Color::BLANK;
        } else return pColData[abs(y % height) * width + abs(x % width)];
    }
    
    bool Sprite::SetPixel(int32_t x, int32_t y, Color p) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pColData[y * width + x] = p; return true;
        } else return false;
    }
    
}

#endif /* Sprite_h */
