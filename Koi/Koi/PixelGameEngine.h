//
//  PixelGameEngine.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef PixelGameEngine_h
#define PixelGameEngine_h

#include "Global.h"
#include "Vector2.h"
#include "Color.h"
#include "Sprite.h"
#include "Renderer.h"
#include "MacPlatform.h"

namespace koi {
//    class PixelGameEngine {
//    public:
//        PixelGameEngine();
//        virtual ~PixelGameEngine();
//    public:
//        koi::rcode Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
//                             bool full_screen = false, bool vsync = false, bool cohesion = false);
//        koi::rcode Start();
//
//    public: // User Override Interfaces
//        virtual bool OnUserCreate();                    // Called once on application startup, use to load your resources
//        virtual bool OnUserUpdate(float fElapsedTime);  // Called every frame, and provides you with a time per frame value
//        virtual bool OnUserDestroy();                   // Called once on application termination, so you can be one clean coder
//
//    public: // Hardware Interfaces
//
//        bool IsFocused() const;                         // Returns true if window is currently in focus
//        koi::HWButton GetKey(Key k) const;                   // Get the state of a specific keyboard button
//        koi::HWButton GetMouse(uint32_t b) const;            // Get the state of a specific mouse button
//        int32_t GetMouseX() const;                      // Get Mouse X coordinate in "pixel" space
//        int32_t GetMouseY() const;                      // Get Mouse Y coordinate in "pixel" space
//        int32_t GetMouseWheel() const;                  // Get Mouse Wheel Delta
//        const koi::Vector2i& GetWindowMouse() const;    // Get the mouse in window space
//        const koi::Vector2i& GetMousePos() const;       // Gets the mouse as a vector to keep Tarriest happy
//
//    public: // Utility
//        koi::Color* pColData = nullptr;
//        koi::Color::Mode modeSample = koi::Color::Mode::NORMAL;
//
//        int32_t ScreenWidth() const;                        // Returns the width of the screen in "pixels"
//        int32_t ScreenHeight() const;                       // Returns the height of the screen in "pixels"
//        int32_t GetDrawTargetWidth() const;                 // Returns the width of the currently selected drawing target in "pixels"
//        int32_t GetDrawTargetHeight() const;                // Returns the height of the currently selected drawing target in "pixels"
//        koi::Sprite* GetDrawTarget() const;                 // Returns the currently active draw target
//        void SetScreenSize(int w, int h);                   // Resize the primary screen sprite
//        uint32_t GetFPS() const;                            // Gets the current Frames Per Second
//        float GetElapsedTime() const;                       // Gets last update of elapsed time
//        const koi::Vector2i& GetWindowSize() const;         // Gets Actual Window size
//        const koi::Vector2i& GetPixelSize() const;          // Gets pixel scale
//        const koi::Vector2i& GetScreenPixelSize() const;    // Gets actual pixel scale
//
//    public: // CONFIGURATION ROUTINES
//        // window targeting functions
//        void EnableWindow(bool b);
//        void SetWindowOffset(const koi::Vector2f& offset);
//        void SetWindowOffset(float x, float y);
//        void SetWindowScale(const koi::Vector2f& scale);
//        void SetWindowScale(float x, float y);
//        void SetWindowTint(const koi::Color& tint);
//        void SetWindowCustomRenderFunction(std::function<void()> f);
//
//
//        // Change the pixel mode for different optimisations
//        // koi::Pixel::NORMAL = No transparency
//        // koi::Pixel::MASK   = Transparent if alpha is < 255
//        // koi::Pixel::ALPHA  = Full transparency
//        void SetPixelMode(koi::Color::Mode m);
//        Color::Mode GetPixelMode();
//        void SetPixelMode(std::function<koi::Color(const int x, const int y, const koi::Color& pSource, const koi::Color& pDest)> pixelMode);   // Use a custom blend function
//        void SetPixelBlend(float fBlend);   // Change the blend factor form between 0.0f to 1.0f;
//
//
//
//    public: // DRAWING ROUTINES
//        virtual bool Draw(int32_t x, int32_t y, koi::Color p = koi::Color::WHITE);
//        bool Draw(const koi::Vector2i& pos, koi::Color p = koi::Color::WHITE);
//        void FillTriangle(const Vector2i& pos1, const Vector2i& pos2, const Vector2i& pos3, koi::Color p = koi::Color::WHITE);
//        void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, koi::Color p = koi::Color::WHITE);
//        void Clear(koi::Color p);
//        void ClearBuffer(koi::Color p, bool bDepth = true);  // Clears the rendering back buffer
//
//
//    public: // Branding
//        std::string sAppName;
//
//    private: // Inner mysterious workings
//        koi::Color::Mode nColorMode = koi::Color::NORMAL;
//        float            fBlendFactor = 1.0f;
//        koi::Vector2i    vScreenSize = { 256, 240 };
//        koi::Vector2f    vInvScreenSize = { 1.0f / 256.0f, 1.0f / 240.0f };
//        koi::Vector2i    vPixelSize = { 4, 4 };
//        koi::Vector2i    vScreenPixelSize = { 4, 4 };
//        koi::Vector2i    vMousePos = { 0, 0 };
//        int32_t          nMouseWheelDelta = 0;
//        koi::Vector2i    vMousePosCache = { 0, 0 };
//        koi::Vector2i    vMouseWindowPos = { 0, 0 };
//        int32_t          nMouseWheelDeltaCache = 0;
//        koi::Vector2i    vWindowSize = { 0, 0 };
//        koi::Vector2i    vViewPos = { 0, 0 };
//        koi::Vector2i    vViewSize = { 0,0 };
//        bool             bFullScreen = false;
//        koi::Vector2f    vPixel = { 1.0f, 1.0f };
//        bool             bHasInputFocus = false;
//        bool             bHasMouseFocus = false;
//        bool             bEnableVSYNC = false;
//        float            fFrameTimer = 1.0f;
//        float            fLastElapsed = 0.0f;
//        int              nFrameCount = 0;
//        uint32_t         nLastFPS = 0;
//        bool             bPixelCohesion = false;
//        std::function<koi::Color(const int x, const int y, const koi::Color&, const koi::Color&)> funcPixelMode;
//        std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
//
//        // Window vars
//        koi::Vector2f   vOffset = { 0, 0 };
//        koi::Vector2f   vScale = { 1, 1 };
//        koi::Sprite*    pDrawTarget = nullptr;
//        uint32_t        nResID = 0;
//        koi::Color      tint = Color::WHITE;
//        std::function<void()> funcHook = nullptr;
//
//
//        // State of keyboard
//        bool            pKeyNewState[256] = { 0 };
//        bool            pKeyOldState[256] = { 0 };
//        koi::HWButton        pKeyboardState[256] = { 0 };
//
//        // State of mouse
//        bool            pMouseNewState[nMouseButtons] = { 0 };
//        bool            pMouseOldState[nMouseButtons] = { 0 };
//        koi::HWButton        pMouseState[nMouseButtons] = { 0 };
//
//
//        void EngineThread(); // The main engine thread
//
//        void koi_ConfigureSystem(); // At the end of this file, chooses which components to compile
//
//        static std::atomic<bool> bAtomActive; // Shutdown flag
//
//    public:
//        void koi_UpdateMouse(int32_t x, int32_t y);
//        void koi_UpdateMouseWheel(int32_t delta);
//        void koi_UpdateWindowSize(int32_t x, int32_t y);
//        void koi_UpdateViewport();
//        void koi_ConstructFontSheet();
//        void koi_CoreUpdate();
//        void koi_PrepareEngine();
//        void koi_UpdateMouseState(int32_t button, bool state);
//        void koi_UpdateKeyState(int32_t key, bool state);
//        void koi_UpdateMouseFocus(bool state);
//        void koi_UpdateKeyFocus(bool state);
//        void koi_Terminate();
//
//    };
    
    PixelGameEngine::PixelGameEngine() {
        sAppName = "Undefined";
        
        // Bring in relevant Platform & Rendering systems depending
        // on compiler parameters
        koi_ConfigureSystem();
    }
    
    PixelGameEngine::~PixelGameEngine() { }
    
    
    koi::rcode PixelGameEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync, bool cohesion) {
        bPixelCohesion = cohesion;
        vScreenSize = { screen_w, screen_h };
        vInvScreenSize = { 1.0f / float(screen_w), 1.0f / float(screen_h) };
        vPixelSize = { pixel_w, pixel_h };
        vWindowSize = vScreenSize * vPixelSize;
        bFullScreen = full_screen;
        bEnableVSYNC = vsync;
        vPixel = 2.0f / vScreenSize;
        
        if (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0)
            return koi::FAIL;
        
        
        return koi::OK;
    }
    
    
    void PixelGameEngine::SetScreenSize(int w, int h) {
        vScreenSize = { w, h };
        vInvScreenSize = { 1.0f / float(w), 1.0f / float(h) };
        delete pDrawTarget; // Erase existing window sprites
        pDrawTarget = new Sprite(vScreenSize.x, vScreenSize.y);
        
        renderer->ClearBuffer(koi::BACK, true);
        renderer->DisplayFrame();
        renderer->ClearBuffer(koi::BACK, true);
        renderer->UpdateViewport(vViewPos, vViewSize);
    }
    
#if !defined(PGE_USE_CUSTOM_START)
    koi::rcode PixelGameEngine::Start() {
        if (platform->ApplicationStartUp() != koi::OK) return koi::FAIL;
        
        // Construct the window
        if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != koi::OK) return koi::FAIL;
        koi_UpdateWindowSize(vWindowSize.x, vWindowSize.y);
        
        // Start the thread
        bAtomActive = true;
        std::thread t = std::thread(&PixelGameEngine::EngineThread, this);
        
        // Some implementations may form an event loop here
        platform->StartSystemEventLoop();
        
        // Wait for thread to be exited
        t.join();
        
        if (platform->ApplicationCleanUp() != koi::OK) return koi::FAIL;
        
        return koi::OK;
    }
#endif
    
    
    void PixelGameEngine::SetWindowOffset(const koi::Vector2f& offset) { SetWindowOffset(offset.x, offset.y); }
    void PixelGameEngine::SetWindowOffset(float x, float y) { vOffset = { x, y }; }
    void PixelGameEngine::SetWindowScale(const koi::Vector2f& scale) { SetWindowScale(scale.x, scale.y); }
    void PixelGameEngine::SetWindowScale(float x, float y) { vScale = { x, y }; }
    void PixelGameEngine::SetWindowTint(const koi::Color& t_tint) { tint = t_tint; }
    void PixelGameEngine::SetWindowCustomRenderFunction(std::function<void()> f) { funcHook = f; }
    
    Sprite* PixelGameEngine::GetDrawTarget() const { return pDrawTarget; }
    int32_t PixelGameEngine::GetDrawTargetWidth() const { return pDrawTarget ? pDrawTarget->width : 0; }
    int32_t PixelGameEngine::GetDrawTargetHeight() const { return pDrawTarget ? pDrawTarget->height : 0; }
    
    uint32_t PixelGameEngine::GetFPS() const { return nLastFPS; }
    bool PixelGameEngine::IsFocused() const { return bHasInputFocus; }
    koi::HWButton PixelGameEngine::GetKey(Key k) const { return pKeyboardState[k]; }
    koi::HWButton PixelGameEngine::GetMouse(uint32_t b) const { return pMouseState[b]; }
    int32_t PixelGameEngine::GetMouseX() const { return vMousePos.x; }
    int32_t PixelGameEngine::GetMouseY() const { return vMousePos.y; }
    const koi::Vector2i& PixelGameEngine::GetMousePos() const { return vMousePos; }
    int32_t PixelGameEngine::GetMouseWheel() const { return nMouseWheelDelta; }
    int32_t PixelGameEngine::ScreenWidth() const { return vScreenSize.x; }
    int32_t PixelGameEngine::ScreenHeight() const { return vScreenSize.y; }
    float PixelGameEngine::GetElapsedTime() const { return fLastElapsed; }
    const koi::Vector2i& PixelGameEngine::GetWindowSize() const { return vWindowSize; }
    const koi::Vector2i& PixelGameEngine::GetPixelSize() const { return vPixelSize; }
    const koi::Vector2i& PixelGameEngine::GetScreenPixelSize() const { return vScreenPixelSize; }
    const koi::Vector2i& PixelGameEngine::GetWindowMouse() const { return vMouseWindowPos; }
    
    bool PixelGameEngine::Draw(const koi::Vector2i& pos, koi::Color p) { return Draw(pos.x, pos.y, p); }
    
    // This is it, the critical function that plots a pixel
    bool PixelGameEngine::Draw(int32_t x, int32_t y, koi::Color p) {
        if (!pDrawTarget) return false;
        if (nColorMode == koi::Color::NORMAL) return pDrawTarget->SetPixel(x, y, p);
        if (nColorMode == koi::Color::MASK) if (p.a == 255) return pDrawTarget->SetPixel(x, y, p);
        if (nColorMode == koi::Color::ALPHA) {
            koi::Color d = pDrawTarget->GetPixel(x, y);
            float a = (float)(p.a / 255.0f) * fBlendFactor;
            float c = 1.0f - a;
            float r = a * (float)p.r + c * (float)d.r;
            float g = a * (float)p.g + c * (float)d.g;
            float b = a * (float)p.b + c * (float)d.b;
            return pDrawTarget->SetPixel(x, y, koi::Color((uint8_t)r, (uint8_t)g, (uint8_t)b/*, (uint8_t)(p.a * fBlendFactor)*/));
        }
        if (nColorMode == koi::Color::CUSTOM) return pDrawTarget->SetPixel(x, y, funcPixelMode(x, y, p, pDrawTarget->GetPixel(x, y)));
        return false;
    }
    
    void PixelGameEngine::FillTriangle(const koi::Vector2i& pos1, const koi::Vector2i& pos2, const koi::Vector2i& pos3, koi::Color p) { FillTriangle(pos1.x, pos1.y, pos2.x, pos2.y, pos3.x, pos3.y, p); }
    
    void PixelGameEngine::FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, koi::Color p) {
        auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) Draw(i, ny, p); };

        int t1x, t2x, y, minx, maxx, t1xp, t2xp;
        bool changed1 = false;
        bool changed2 = false;
        int signx1, signx2, dx1, dy1, dx2, dy2;
        int e1, e2;
        
        // Sort vertices
        if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
        if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
        if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

        t1x = t2x = x1; y = y1;                             // Starting points
        dx1 = (int)(x2 - x1);
        if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
        else signx1 = 1;
        dy1 = (int)(y2 - y1);

        dx2 = (int)(x3 - x1);
        if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
        else signx2 = 1;
        dy2 = (int)(y3 - y1);

        if (dy1 > dx1) { std::swap(dx1, dy1); changed1 = true; }
        if (dy2 > dx2) { std::swap(dy2, dx2); changed2 = true; }

        e2 = (int)(dx2 >> 1);
        
        // Flat top, just process the second half
        if (y1 == y2) goto next;
        e1 = (int)(dx1 >> 1);

        for (int i = 0; i < dx1;) {
            t1xp = 0; t2xp = 0;
            if (t1x < t2x) { minx = t1x; maxx = t2x; }
            else { minx = t2x; maxx = t1x; }
            
            while (i < dx1) {                               // process first line until y value is about to change
                i++;
                e1 += dy1;
                while (e1 >= dx1) {
                    e1 -= dx1;
                    if (changed1) t1xp = signx1;            //t1x += signx1;
                    else          goto next1;
                }
                if (changed1) break;
                else t1x += signx1;
            }
            
            // Move line
            next1:
            while (1) {                                     // process second line until y value is about to change
                e2 += dy2;
                while (e2 >= dx2) {
                    e2 -= dx2;
                    if (changed2) t2xp = signx2;            //t2x += signx2;
                    else          goto next2;
                }
                if (changed2)     break;
                else              t2x += signx2;
            }
            
            next2:
            if (minx > t1x) minx = t1x;
            if (minx > t2x) minx = t2x;
            if (maxx < t1x) maxx = t1x;
            if (maxx < t2x) maxx = t2x;
            drawline(minx, maxx, y);                        // Draw line from min to max points found on the y
                                                            // Now increase y
            if (!changed1) t1x += signx1;
            t1x += t1xp;
            if (!changed2) t2x += signx2;
            t2x += t2xp;
            y += 1;
            if (y == y2) break;

        }
        
        // Second half
        next:
        dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
        else signx1 = 1;
        dy1 = (int)(y3 - y2);
        t1x = x2;

        // swap values
        if (dy1 > dx1) {
            std::swap(dy1, dx1);
            changed1 = true;
        }
        else changed1 = false;

        e1 = (int)(dx1 >> 1);

        for (int i = 0; i <= dx1; i++) {
            t1xp = 0; t2xp = 0;
            if (t1x < t2x) { minx = t1x; maxx = t2x; }
            else { minx = t2x; maxx = t1x; }
            
            while (i < dx1) {                               // process first line until y value is about to change
                e1 += dy1;
                while (e1 >= dx1) {
                    e1 -= dx1;
                    if (changed1) { t1xp = signx1; break; } // t1x += signx1;
                    else          goto next3;
                }
                if (changed1) break;
                else          t1x += signx1;
                if (i < dx1) i++;
            }
            
            next3:
            
            while (t2x != x3) {                             // process second line until y value is about to change
                e2 += dy2;
                while (e2 >= dx2) {
                    e2 -= dx2;
                    if (changed2) t2xp = signx2;
                    else          goto next4;
                }
                if (changed2)     break;
                else              t2x += signx2;
            }
            next4:

            if (minx > t1x) minx = t1x;
            if (minx > t2x) minx = t2x;
            if (maxx < t1x) maxx = t1x;
            if (maxx < t2x) maxx = t2x;
            drawline(minx, maxx, y);
            if (!changed1) t1x += signx1;
            t1x += t1xp;
            if (!changed2) t2x += signx2;
            t2x += t2xp;
            y += 1;
            if (y > y3) return;
        }
    }
    
    void PixelGameEngine::Clear(koi::Color p) {
        int pixels = GetDrawTargetWidth() * GetDrawTargetHeight();
        koi::Color* m = GetDrawTarget()->GetData();
        for (int i = 0; i < pixels; i++) m[i] = p;
    }
    
    void PixelGameEngine::ClearBuffer(koi::Color p, bool bDepth) { renderer->ClearBuffer(p, bDepth); }
    void PixelGameEngine::SetPixelMode(koi::Color::Mode m) { nColorMode = m; }
    koi::Color::Mode PixelGameEngine::GetPixelMode() { return nColorMode; }
    
    void PixelGameEngine::SetPixelMode(std::function<koi::Color(const int x, const int y, const koi::Color&, const koi::Color&)> pixelMode) {
        funcPixelMode = pixelMode;
        nColorMode = koi::Color::Mode::CUSTOM;
    }
    
    void PixelGameEngine::SetPixelBlend(float fBlend) {
        fBlendFactor = fBlend;
        if (fBlendFactor < 0.0f) fBlendFactor = 0.0f;
        if (fBlendFactor > 1.0f) fBlendFactor = 1.0f;
    }
    
    // User must override these functions as required. I have not made
    // them abstract because I do need a default behaviour to occur if
    // they are not overwritten
    bool PixelGameEngine::OnUserCreate() { return false; }
    bool PixelGameEngine::OnUserUpdate(float fElapsedTime) { UNUSED(fElapsedTime);  return false; }
    bool PixelGameEngine::OnUserDestroy() { return true; }
    
    void PixelGameEngine::koi_UpdateViewport() {
        int32_t ww = vScreenSize.x * vPixelSize.x;
        int32_t wh = vScreenSize.y * vPixelSize.y;
        float wasp = (float)ww / (float)wh;
        
        if (bPixelCohesion) {
            vScreenPixelSize = (vWindowSize / vScreenSize);
            vViewSize = (vWindowSize / vScreenSize) * vScreenSize;
        } else {
            vViewSize.x = (int32_t)vWindowSize.x;
            vViewSize.y = (int32_t)((float)vViewSize.x / wasp);
            
            if (vViewSize.y > vWindowSize.y) {
                vViewSize.y = vWindowSize.y;
                vViewSize.x = (int32_t)((float)vViewSize.y * wasp);
            }
        }
        
        vViewPos = (vWindowSize - vViewSize) / 2;
    }
    
    void PixelGameEngine::koi_UpdateWindowSize(int32_t x, int32_t y) {
        vWindowSize = { x, y };
        koi_UpdateViewport();
    }
    
    void PixelGameEngine::koi_UpdateMouseWheel(int32_t delta) { nMouseWheelDeltaCache += delta; }
    
    void PixelGameEngine::koi_UpdateMouse(int32_t x, int32_t y) {
        // Mouse coords come in screen space
        // But leave in pixel space
        bHasMouseFocus = true;
        vMouseWindowPos = { x, y };
        // Full Screen mode may have a weird viewport we must clamp to
        x -= vViewPos.x;
        y -= vViewPos.y;
        vMousePosCache.x = (int32_t)(((float)x / (float)(vWindowSize.x - (vViewPos.x * 2)) * (float)vScreenSize.x));
        vMousePosCache.y = (int32_t)(((float)y / (float)(vWindowSize.y - (vViewPos.y * 2)) * (float)vScreenSize.y));
        if (vMousePosCache.x >= (int32_t)vScreenSize.x) vMousePosCache.x = vScreenSize.x - 1;
        if (vMousePosCache.y >= (int32_t)vScreenSize.y) vMousePosCache.y = vScreenSize.y - 1;
        if (vMousePosCache.x < 0) vMousePosCache.x = 0;
        if (vMousePosCache.y < 0) vMousePosCache.y = 0;
    }
    
    void PixelGameEngine::koi_UpdateMouseState(int32_t button, bool state) { pMouseNewState[button] = state; }
    void PixelGameEngine::koi_UpdateKeyState(int32_t key, bool state) { pKeyNewState[key] = state; }
    void PixelGameEngine::koi_UpdateMouseFocus(bool state) { bHasMouseFocus = state; }
    void PixelGameEngine::koi_UpdateKeyFocus(bool state) { bHasInputFocus = state; }
    void PixelGameEngine::koi_Terminate() { bAtomActive = false; }
    
    void PixelGameEngine::EngineThread() {
        // Allow platform to do stuff here if needed, since its now in the
        // context of this thread
        if (platform->ThreadStartUp() == koi::FAIL) return;
        
        // Do engine context specific initialisation
        koi_PrepareEngine();
        
        // Create user resources as part of this thread
        if (!OnUserCreate()) bAtomActive = false;
        
        while (bAtomActive) {
            // Run as fast as possible
            while (bAtomActive) { koi_CoreUpdate(); }
            
            // Allow the user to free resources if they have overrided the destroy function
            if (!OnUserDestroy()) {
                // User denied destroy for some reason, so continue running
                bAtomActive = true;
            }
        }
        
        platform->ThreadCleanUp();
    }
    
    void PixelGameEngine::koi_PrepareEngine() {
        // Start OpenGL, the context is owned by the game thread
        if (platform->CreateGraphics(bFullScreen, bEnableVSYNC, vViewPos, vViewSize) == koi::FAIL) return;
        
        
        // Create Primary window "0"
        pDrawTarget = new koi::Sprite(vScreenSize.x, vScreenSize.y);
        nResID = renderer->CreateTexture(vScreenSize.x, vScreenSize.y);
        renderer->UpdateTexture(nResID, pDrawTarget);
        
        
        
        m_tp1 = std::chrono::system_clock::now();
        m_tp2 = std::chrono::system_clock::now();
    }
    
    
    void PixelGameEngine::koi_CoreUpdate() {
        // Handle Timing
        m_tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
        m_tp1 = m_tp2;
        
        // Our time per frame coefficient
        float fElapsedTime = elapsedTime.count();
        fLastElapsed = fElapsedTime;
        
        // Some platforms will need to check for events
        platform->HandleSystemEvent();
        
        // Compare hardware input states from previous frame
        auto ScanHardware = [&](koi::HWButton* pKeys, bool* pStateOld, bool* pStateNew, uint32_t nKeyCount) {
            for (uint32_t i = 0; i < nKeyCount; i++) {
                pKeys[i].bPressed = false;
                pKeys[i].bReleased = false;
                if (pStateNew[i] != pStateOld[i]) {
                    if (pStateNew[i]) {
                        pKeys[i].bPressed = !pKeys[i].bHeld;
                        pKeys[i].bHeld = true;
                    } else {
                        pKeys[i].bReleased = true;
                        pKeys[i].bHeld = false;
                    }
                }
                pStateOld[i] = pStateNew[i];
            }
        };
        
        ScanHardware(pKeyboardState, pKeyOldState, pKeyNewState, 256);
        ScanHardware(pMouseState, pMouseOldState, pMouseNewState, nMouseButtons);
        
        // Cache mouse coordinates so they remain consistent during frame
        vMousePos = vMousePosCache;
        nMouseWheelDelta = nMouseWheelDeltaCache;
        nMouseWheelDeltaCache = 0;
        
        // renderer->ClearBuffer(koi::BLACK, true);
        
        // Handle Frame Update
        if (!OnUserUpdate(fElapsedTime))
            bAtomActive = false;
        
        // Display Frame
        renderer->UpdateViewport(vViewPos, vViewSize);
        renderer->ClearBuffer(koi::Color::BLACK, true);
        
        renderer->PrepareDrawing();
        
        if (funcHook == nullptr) {
            renderer->ApplyTexture(nResID);
            renderer->UpdateTexture(nResID, pDrawTarget);
            
            renderer->DrawWindowQuad(vOffset, vScale, tint);
            
        } else {
            // Mwa ha ha.... Have Fun!!!
            funcHook();
        }
        
        // Present Graphics to screen
        renderer->DisplayFrame();
        
        // Update Title Bar
        fFrameTimer += fElapsedTime;
        nFrameCount++;
        if (fFrameTimer >= 1.0f) {
            nLastFPS = nFrameCount;
            fFrameTimer -= 1.0f;
            std::string sTitle = sAppName + " - FPS: " + std::to_string(nFrameCount);
            platform->SetWindowTitle(sTitle);
            nFrameCount = 0;
        }
    }
    
    // Need a couple of statics as these are singleton instances
    // read from multiple locations
    std::atomic<bool> PixelGameEngine::bAtomActive{ false };
    koi::PixelGameEngine* koi::Platform::ptrPGE = nullptr;
    koi::PixelGameEngine* koi::Renderer::ptrPGE = nullptr;
}


#endif /* PixelGameEngine_h */
