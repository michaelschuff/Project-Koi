//
//  Global.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef KOI_PGE_DEF
#define KOI_PGE_DEF

#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>
#include <streambuf>
#include <sstream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <fstream>
#include <map>
#include <functional>
#include <algorithm>
#include <array>
#include <cstring>
#include "Vector2.h"
#include "Color.h"

#define USE_EXPERIMENTAL_FS

#if defined(_WIN32)
  #if _MSC_VER >= 1920 && _MSVC_LANG >= 201703L
    #undef USE_EXPERIMENTAL_FS
  #endif
#endif

#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__) || defined(__APPLE__)
  #if __cplusplus >= 201703L
    #undef USE_EXPERIMENTAL_FS
  #endif
#endif

#if defined(__APPLE__)
  #define PGE_USE_CUSTOM_START
#endif

#if defined(USE_EXPERIMENTAL_FS) || defined(FORCE_EXPERIMENTAL_FS)
  // C++14
  #define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
  #include <experimental/filesystem>
  namespace _gfs = std::experimental::filesystem::v1;
#else
  // C++17
  #include <filesystem>
  namespace _gfs = std::filesystem;
#endif

#if defined(UNICODE) || defined(_UNICODE)
    #define koiT(s) L##s
  #else
    #define koiT(s) s
#endif

#define UNUSED(x) (void)(x)

#if !defined(KOI_GFX_OPENGL33) && !defined(KOI_GFX_DIRECTX10)
  #define KOI_GFX_OPENGL10
#endif

#if defined(_WIN32)
  #if defined(KOI_IMAGE_STB)
    #define PGE_ILOADER_STB
  #else
    #define PGE_ILOADER_GDI
  #endif
#endif

#if defined(__linux__) || defined(__APPLE__)
  #if defined(KOI_IMAGE_STB)
    #define PGE_ILOADER_STB
  #else
    #define PGE_ILOADER_LIBPNG
  #endif
#endif


#endif // KOI_PGE_DEF



#ifndef Global_h
#define Global_h

namespace koi {
    class PixelGameEngine;
    
    // Pixel Game Engine Advanced Configuration
    constexpr uint8_t  nMouseButtons = 5;
    enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };
    enum Key {
        NONE,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        UP, DOWN, LEFT, RIGHT,
        SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
        BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
        NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
        NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD
    };
    
    struct HWButton {
        bool bPressed = false;  // Set once during the frame the event occurs
        bool bReleased = false; // Set once during the frame the event occurs
        bool bHeld = false;   // Set true for all frames between pressed and released events
    };
    
    class Sprite {
    public:
        Sprite(int32_t w, int32_t h);
        ~Sprite();
        
        int32_t width = 0;
        int32_t height = 0;
        enum    Mode { NORMAL, PERIODIC };
        enum    Flip { NONE = 0, HORZ = 1, VERT = 2 };
        
        koi::Color   GetPixel(int32_t x, int32_t y) const;
        bool         SetPixel(int32_t x, int32_t y, koi::Color p);
        koi::Color   GetPixel(const Vector2i& a) const;
        bool         SetPixel(const koi::Vector2i& a, koi::Color p);
        koi::Color*  GetData();
        koi::Color*  pColData = nullptr;
        Mode    modeSample = Mode::NORMAL;
    };
    
    class Platform {
    public:
        virtual ~Platform() = default;
        virtual koi::rcode ApplicationStartUp() = 0;
        virtual koi::rcode ApplicationCleanUp() = 0;
        virtual koi::rcode ThreadStartUp() = 0;
        virtual koi::rcode ThreadCleanUp() = 0;
        virtual koi::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const koi::Vector2i& vViewPos, const koi::Vector2i& vViewSize) = 0;
        virtual koi::rcode CreateWindowPane(const koi::Vector2i& vWindowPos, koi::Vector2i& vWindowSize, bool bFullScreen) = 0;
        virtual koi::rcode SetWindowTitle(const std::string& s) = 0;
        virtual koi::rcode StartSystemEventLoop() = 0;
        virtual koi::rcode HandleSystemEvent() = 0;
        static PixelGameEngine* ptrPGE;
    };
    
    class Renderer {
    public:
//        virtual ~Renderer() = default;
        virtual void       PrepareDevice() = 0;
        virtual koi::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
        virtual koi::rcode DestroyDevice() = 0;
        virtual void       DisplayFrame() = 0;
        virtual void       PrepareDrawing() = 0;
//        virtual void       DrawWindowQuad(const koi::Vector2f& offset, const koi::Vector2f& scale, const koi::Color tint) = 0;
        virtual uint32_t   CreateTexture(const uint32_t width, const uint32_t height) = 0;
        virtual void       UpdateTexture(uint32_t id, koi::Sprite* spr) = 0;
        virtual uint32_t   DeleteTexture(const uint32_t id) = 0;
        virtual void       ApplyTexture(uint32_t id) = 0;
        virtual void       UpdateViewport(const koi::Vector2i& pos, const koi::Vector2i& size) = 0;
        virtual void       ClearBuffer(koi::Color p, bool bDepth) = 0;
        static koi::PixelGameEngine* ptrPGE;
    };
    
    class PixelGameEngine {
    public:
        PixelGameEngine();
        virtual ~PixelGameEngine();
    public:
        koi::rcode Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
                             bool full_screen = false, bool vsync = false, bool cohesion = false);
        koi::rcode Start();
        
    public: // User Override Interfaces
        virtual bool OnUserCreate();                    // Called once on application startup, use to load your resources
        virtual bool OnUserUpdate(float fElapsedTime);  // Called every frame, and provides you with a time per frame value
        virtual bool OnUserDestroy();                   // Called once on application termination, so you can be one clean coder
        
    public: // Hardware Interfaces
            
        bool IsFocused() const;                         // Returns true if window is currently in focus
        koi::HWButton GetKey(Key k) const;                   // Get the state of a specific keyboard button
        koi::HWButton GetMouse(uint32_t b) const;            // Get the state of a specific mouse button
        int32_t GetMouseX() const;                      // Get Mouse X coordinate in "pixel" space
        int32_t GetMouseY() const;                      // Get Mouse Y coordinate in "pixel" space
        int32_t GetMouseWheel() const;                  // Get Mouse Wheel Delta
        const koi::Vector2i& GetWindowMouse() const;    // Get the mouse in window space
        const koi::Vector2i& GetMousePos() const;       // Gets the mouse as a vector to keep Tarriest happy
        
    public: // Utility
        koi::Color* pColData = nullptr;
        koi::Color::Mode modeSample = koi::Color::Mode::NORMAL;
        
        int32_t ScreenWidth() const;                        // Returns the width of the screen in "pixels"
        int32_t ScreenHeight() const;                       // Returns the height of the screen in "pixels"
        int32_t GetDrawTargetWidth() const;                 // Returns the width of the currently selected drawing target in "pixels"
        int32_t GetDrawTargetHeight() const;                // Returns the height of the currently selected drawing target in "pixels"
        koi::Sprite* GetDrawTarget() const;                 // Returns the currently active draw target
        void SetScreenSize(int w, int h);                   // Resize the primary screen sprite
        uint32_t GetFPS() const;                            // Gets the current Frames Per Second
        float GetElapsedTime() const;                       // Gets last update of elapsed time
        const koi::Vector2i& GetWindowSize() const;         // Gets Actual Window size
        const koi::Vector2i& GetPixelSize() const;          // Gets pixel scale
        const koi::Vector2i& GetScreenPixelSize() const;    // Gets actual pixel scale
        
    public: // CONFIGURATION ROUTINES
        // window targeting functions
        void EnableWindow(bool b);
        void SetWindowOffset(const koi::Vector2f& offset);
        void SetWindowOffset(float x, float y);
        void SetWindowScale(const koi::Vector2f& scale);
        void SetWindowScale(float x, float y);
        void SetWindowTint(const koi::Color& tint);
        void SetWindowCustomRenderFunction(std::function<void()> f);
        
        
        // Change the pixel mode for different optimisations
        // koi::Pixel::NORMAL = No transparency
        // koi::Pixel::MASK   = Transparent if alpha is < 255
        // koi::Pixel::ALPHA  = Full transparency
        void SetPixelMode(koi::Color::Mode m);
        Color::Mode GetPixelMode();
        void SetPixelMode(std::function<koi::Color(const int x, const int y, const koi::Color& pSource, const koi::Color& pDest)> pixelMode);   // Use a custom blend function
        void SetPixelBlend(float fBlend);   // Change the blend factor form between 0.0f to 1.0f;
        
        
        
    public: // DRAWING ROUTINES
        virtual bool Draw(int32_t x, int32_t y, koi::Color p = koi::Color::WHITE);
        bool Draw(const koi::Vector2i& pos, koi::Color p = koi::Color::WHITE);
        void FillTriangle(const Vector2i& pos1, const Vector2i& pos2, const Vector2i& pos3, koi::Color p = koi::Color::WHITE);
        void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, koi::Color p = koi::Color::WHITE);
        void Clear(koi::Color p);
        void ClearBuffer(koi::Color p, bool bDepth = true);  // Clears the rendering back buffer
        
        
    public: // Branding
        std::string sAppName;
        
    private: // Inner mysterious workings
        koi::Color::Mode nColorMode = koi::Color::NORMAL;
        float            fBlendFactor = 1.0f;
        koi::Vector2i    vScreenSize = { 256, 240 };
        koi::Vector2f    vInvScreenSize = { 1.0f / 256.0f, 1.0f / 240.0f };
        koi::Vector2i    vPixelSize = { 4, 4 };
        koi::Vector2i    vScreenPixelSize = { 4, 4 };
        koi::Vector2i    vMousePos = { 0, 0 };
        int32_t          nMouseWheelDelta = 0;
        koi::Vector2i    vMousePosCache = { 0, 0 };
        koi::Vector2i    vMouseWindowPos = { 0, 0 };
        int32_t          nMouseWheelDeltaCache = 0;
        koi::Vector2i    vWindowSize = { 0, 0 };
        koi::Vector2i    vViewPos = { 0, 0 };
        koi::Vector2i    vViewSize = { 0,0 };
        bool             bFullScreen = false;
        koi::Vector2f    vPixel = { 1.0f, 1.0f };
        bool             bHasInputFocus = false;
        bool             bHasMouseFocus = false;
        bool             bEnableVSYNC = false;
        float            fFrameTimer = 1.0f;
        float            fLastElapsed = 0.0f;
        int              nFrameCount = 0;
        uint32_t         nLastFPS = 0;
        bool             bPixelCohesion = false;
        std::function<koi::Color(const int x, const int y, const koi::Color&, const koi::Color&)> funcPixelMode;
        std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
        
        // Window vars
        koi::Vector2f   vOffset = { 0, 0 };
        koi::Vector2f   vScale = { 1, 1 };
        koi::Sprite*    pDrawTarget = nullptr;
        uint32_t        nResID = 0;
        koi::Color      tint = Color::WHITE;
        std::function<void()> funcHook = nullptr;
        
        
        // State of keyboard
        bool            pKeyNewState[256] = { 0 };
        bool            pKeyOldState[256] = { 0 };
        koi::HWButton        pKeyboardState[256] = { 0 };
        
        // State of mouse
        bool            pMouseNewState[nMouseButtons] = { 0 };
        bool            pMouseOldState[nMouseButtons] = { 0 };
        koi::HWButton        pMouseState[nMouseButtons] = { 0 };
        
        
        void EngineThread(); // The main engine thread
        
        void koi_ConfigureSystem(); // At the end of this file, chooses which components to compile
        
        static std::atomic<bool> bAtomActive; // Shutdown flag
        
    public:
        void koi_UpdateMouse(int32_t x, int32_t y);
        void koi_UpdateMouseWheel(int32_t delta);
        void koi_UpdateWindowSize(int32_t x, int32_t y);
        void koi_UpdateViewport();
        void koi_ConstructFontSheet();
        void koi_CoreUpdate();
        void koi_PrepareEngine();
        void koi_UpdateMouseState(int32_t button, bool state);
        void koi_UpdateKeyState(int32_t key, bool state);
        void koi_UpdateMouseFocus(bool state);
        void koi_UpdateKeyFocus(bool state);
        void koi_Terminate();
        
    };
    
    static std::unique_ptr<Renderer> renderer;
    static std::unique_ptr<Platform> platform;
    static std::map<size_t, uint8_t> mapKeys;
    
}


#endif /* Global_h */
