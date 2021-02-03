//
//  Sprite.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Sprite_h
#define Sprite_h

#include "Global.h"


#ifdef OLC_PGE_APPLICATION
#undef OLC_PGE_APPLICATION
namespace koi {
    Sprite::Sprite(int32_t w, int32_t h) {
        if (pColData) delete[] pColData;
        width = w;
        height = h;
        pColData = new Color[width * height];
        for (int32_t i = 0; i < width * height; i++) pColData[i] = Color();
    }

    Sprite::~Sprite() { if (pColData) delete[] pColData; }


    Color* Sprite::GetData() { return pColData; }
    Color  Sprite::GetPixel(const koi::Vector2i& a) const    { return GetPixel(a.x, a.y   ); }
    bool   Sprite::SetPixel(const koi::Vector2i& a, Color p) { return SetPixel(a.x, a.y, p); }

    Color Sprite::GetPixel(int32_t x, int32_t y) const {
        if (modeSample == koi::Sprite::Mode::NORMAL) {
            if (x >= 0 && x < width && y >= 0 && y < height) return pColData[y * width + x];
            else                                             return Color::BLANK;
        } else return pColData[abs(y % height) * width + abs(x % width)];
    }

    bool Sprite::SetPixel(int32_t x, int32_t y, Color p) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pColData[y * width + x] = p;
            return true;
        }
        return false;
    }
}
#endif

#endif /* Sprite_h */
