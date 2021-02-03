//
//  Color.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Color_h
#define Color_h


namespace koi {
    
    constexpr uint8_t  nDefaultAlpha = 0xFF;
    constexpr uint32_t nDefaultColor = (nDefaultAlpha << 24);
    struct Color {
        static const Color GREY,    DARK_GREY,    VERY_DARK_GREY;
        static const Color RED,     DARK_RED,     VERY_DARK_RED;
        static const Color YELLOW,  DARK_YELLOW,  VERY_DARK_YELLOW;
        static const Color GREEN,   DARK_GREEN,   VERY_DARK_GREEN;
        static const Color CYAN,    DARK_CYAN,    VERY_DARK_CYAN;
        static const Color BLUE,    DARK_BLUE,    VERY_DARK_BLUE;
        static const Color MAGENTA, DARK_MAGENTA, VERY_DARK_MAGENTA;
        static const Color WHITE,   BLACK,        BLANK;
        
        union {
            uint32_t n = nDefaultColor;
            struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
        };
        
        enum Mode { NORMAL, MASK, ALPHA, CUSTOM };
        
        Color() : r(0), g(0), b(0), a(nDefaultAlpha) {}
        Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = nDefaultAlpha) : n(_r | (_g << 8) | (_b << 16) | (_a << 24)) {}
        Color(uint32_t p) : n(p) {}
        bool operator==(const Color& p) const;
        bool operator!=(const Color& p) const;
    };
    
    const Color Color::GREY   (192, 192, 192), Color::DARK_GREY   (128, 128, 128), Color::VERY_DARK_GREY   ( 64,  64,  64);
    const Color Color::RED    (255,   0,   0), Color::DARK_RED    (128,   0,   0), Color::VERY_DARK_RED    ( 64,   0,   0);
    const Color Color::YELLOW (255, 255,   0), Color::DARK_YELLOW (128, 128,   0), Color::VERY_DARK_YELLOW ( 64,  64,   0);
    const Color Color::GREEN  (  0, 255,   0), Color::DARK_GREEN  (  0, 128,   0), Color::VERY_DARK_GREEN  (  0,  64,   0);
    const Color Color::CYAN   (  0, 255, 255), Color::DARK_CYAN   (  0, 128, 128), Color::VERY_DARK_CYAN   (  0,  64,  64);
    const Color Color::BLUE   (  0,   0, 255), Color::DARK_BLUE   (  0,   0, 128), Color::VERY_DARK_BLUE   (  0,   0,  64);
    const Color Color::MAGENTA(255,   0, 255), Color::DARK_MAGENTA(128,   0, 128), Color::VERY_DARK_MAGENTA( 64,   0,  64);
    const Color Color::WHITE  (255, 255, 255), Color::BLACK       (  0,   0,   0), Color::BLANK            (  0,   0,   0,   0);
    
    
    
    
    bool Color::operator==(const Color& p) const { return n == p.n; }
    bool Color::operator!=(const Color& p) const { return n != p.n; }
    
    Color ColorF(float  _r, float  _g, float  _b, float  _a = nDefaultAlpha) { return Color(uint8_t(_r * 255), uint8_t(_g * 255), uint8_t(_b * 255), uint8_t(_a * 255)); }
    Color ColorD(double _r, double _g, double _b, double _a = nDefaultAlpha) { return Color(uint8_t(_r * 255), uint8_t(_g * 255), uint8_t(_b * 255), uint8_t(_a * 255)); }
}

#endif /* Color_h */
