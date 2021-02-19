//
//  KoiEngine.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef KoiEngine_h
#define KoiEngine_h

    
    #define UNUSED(x) (void)(x)

    #include "Global.h"

    // MARK: KoiEngine
    // +------------------------------------------------------------------------------+
    // | KoiEngine - The main BASE class for your application              |
    // +------------------------------------------------------------------------------+
    namespace koi {
        class KoiEngine {
        public:
            KoiEngine();
            virtual ~KoiEngine();
        
            
            
            rcode Construct(int32_t screen_w, int32_t screen_h,
                            int32_t pixel_w,  int32_t pixel_h,
                            bool full_screen = false,
                            bool vsync = false,
                            bool cohesion = false);
            
            rcode Start();
            
            
            
            // User Override Interfaces
            virtual bool OnUserCreate ();                           // Called once on application startup, use to load your resources
            virtual bool OnUserUpdate (float fElapsedTime);         // Called every frame, and provides you with a time per frame value
            virtual bool OnUserDestroy();                           // Called once on application termination
            
            
            
            // Hardware Interfaces
            bool            IsFocused           ()           const; // Returns true if window is currently in focus
            HWButton        GetKey              (Key k)      const; // Get the state of a specific keyboard button
            HWButton        GetMouse            (uint32_t b) const; // Get the state of a specific mouse button
            int32_t         GetMouseX           ()           const; // Get Mouse X coordinate in "pixel" space
            int32_t         GetMouseY           ()           const; // Get Mouse Y coordinate in "pixel" space
            int32_t         GetMouseWheel       ()           const; // Get Mouse Wheel Delta
            const Vector2i& GetWindowMouse      ()           const; // Get the mouse in window space
            const Vector2i& GetMousePos         ()           const; // Gets the mouse as a vector
            
            
            
            // Utility
            int32_t         ScreenWidth         ()           const; // Returns the width of the screen in "pixels"
            int32_t         ScreenHeight        ()           const; // Returns the height of the screen in "pixels"
            int32_t         GetDrawTargetWidth  ()           const; // Returns the width of the currently selected drawing target in "pixels"
            int32_t         GetDrawTargetHeight ()           const; // Returns the height of the currently selected drawing target in "pixels"
            Sprite*         GetDrawTarget       ()           const; // Returns the currently active draw target
            void            SetScreenSize       (int w, int h);     // Resize the primary screen sprite
            uint32_t        GetFPS              ()           const; // Gets the current Frames Per Second
            float           GetElapsedTime      ()           const; // Gets last update of elapsed time
            const Vector2i& GetWindowSize       ()           const; // Gets Actual Window size
            const Vector2i& GetPixelSize        ()           const; // Gets pixel scale
            const Vector2i& GetScreenPixelSize  ()           const; // Gets actual pixel scale
            
            
            
            // CONFIGURATION ROUTINES
            
            // window targeting functions
            void EnableWindow       (bool b);
            void SetWindowOffset    (const Vector2f& offset);
            void SetWindowOffset    (float x, float y);
            void SetWindowScale     (const Vector2f& scale);
            void SetWindowScale     (float x, float y);
            void SetWindowTint      (const Color& tint);
            void SetWindowCustomRenderFunction(std::function<void()> f);
            
            
            // Pixel modes:
            // Color::NORMAL = No transparency
            // Color::MASK   = Transparent if alpha is < 255
            // Color::ALPHA  = Full transparency
            void        SetPixelMode(Color::Mode m);
            Color::Mode GetPixelMode();
            void        SetPixelMode(std::function<Color(const int x, const int y, const Color& pSource, const Color& pDest)> pixelMode); // Custom blend function
            void        SetPixelBlend(float fBlend);   // Change the blend factor form between 0.0f to 1.0f;
            
            
            
            // DRAWING ROUTINES
            virtual bool Draw     (int32_t x, int32_t y,   Color p = Color::WHITE);
                    bool Draw     (const Vector2i& pos,    Color p = Color::WHITE);
            
            void DrawLine         (int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color p = Color::WHITE, uint32_t pattern = 0xFFFFFFFF);
            void DrawLine         (const Vector2i& p1,     const Vector2i& p2,     Color p = Color::WHITE, uint32_t pattern = 0xFFFFFFFF);
            
            void DrawCircle       (int32_t x, int32_t y,   int32_t radius, Color c = Color::WHITE, uint8_t mask = 0xFF);
            void DrawCircle       (const Vector2i& p,      int32_t radius, Color c = Color::WHITE, uint8_t mask = 0xFF);
            void FillCircle       (int32_t x, int32_t y,   int32_t radius, Color c = Color::WHITE);
            void FillCircle       (const Vector2i& p,      int32_t radius, Color c = Color::WHITE);
            
            void DrawRect         (int32_t x, int32_t y,   int32_t w, int32_t h,   Color c = Color::WHITE);
            void DrawRect         (const Vector2i& p,      const Vector2i& size,   Color c = Color::WHITE);
            void FillRect         (int32_t x, int32_t y,   int32_t w, int32_t h,   Color c = Color::WHITE);
            void FillRect         (const Vector2i& p,      const Vector2i& size,   Color c = Color::WHITE);
            
            void DrawTriangle     (int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color c = Color::WHITE);
            void DrawTriangle     (const Vector2i& p1,     const Vector2i& p2,     const Vector2i& p3,     Color c = Color::WHITE);
            void FillTriangle     (int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color c = Color::WHITE);
            void FillTriangle     (const Vector2i& p1,     const Vector2i& p2,     const Vector2i& p3,     Color c = Color::WHITE);
            
            void DrawSprite       (int32_t x, int32_t y,   Sprite* sprite, uint32_t scale = 1, uint8_t flip = Sprite::NONE);
            void DrawSprite       (const Vector2i& p,      Sprite* sprite, uint32_t scale = 1, uint8_t flip = Sprite::NONE);
            void DrawPartialSprite(int32_t x, int32_t y,   Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale = 1, uint8_t flip = Sprite::NONE);
            void DrawPartialSprite(const Vector2i& p,      Sprite* sprite, const Vector2i& origin, const Vector2i& size, uint32_t scale = 1, uint8_t flip = Sprite::NONE);
            void Clear(Color c);
            void ClearBuffer(Color c, bool bDepth = true);  // Clears the rendering back buffer
            
            
            // Branding
            std::string sAppName;
            
            // Inner workings
            Color::Mode nColorMode              = Color::NORMAL;
            float       fBlendFactor            = 1.0f;
            Vector2i    vScreenSize             = { 256, 240 };
            Vector2f    vInvScreenSize          = { 1.0f / 256.0f, 1.0f / 240.0f };
            Vector2i    vPixelSize              = { 4, 4 };
            Vector2i    vScreenPixelSize        = { 4, 4 };
            Vector2i    vMousePos               = { 0, 0 };
            int32_t     nMouseWheelDelta        = 0;
            Vector2i    vMousePosCache          = { 0, 0 };
            Vector2i    vMouseWindowPos         = { 0, 0 };
            int32_t     nMouseWheelDeltaCache   = 0;
            Vector2i    vWindowSize             = { 0, 0 };
            Vector2i    vViewPos                = { 0, 0 };
            Vector2i    vViewSize               = { 0, 0 };
            bool        bFullScreen             = false;
            Vector2f    vPixel                  = { 1.0f, 1.0f };
            bool        bHasInputFocus          = false;
            bool        bHasMouseFocus          = false;
            bool        bEnableVSYNC            = false;
            float       fFrameTimer             = 1.0f;
            float       fLastElapsed            = 0.0f;
            int         nFrameCount             = 0;
            uint32_t    nLastFPS                = 0;
            bool        bPixelCohesion = false;
            
            std::function<Color(const int x, const int y, const Color&, const Color&)> funcPixelMode;
            std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
            
            // Window vars
            Vector2f    vOffset              = { 0, 0 };
            Vector2f    vScale               = { 1, 1 };
            Sprite*     pDrawTarget          = nullptr;
            uint32_t    nResID               = 0;
            Color       tint                 = Color::WHITE;
            std::function<void()> funcHook  = nullptr;
            
            
            // Keyboard state
            bool        pKeyNewState  [256]           = { 0 };
            bool        pKeyOldState  [256]           = { 0 };
            HWButton    pKeyboardState[256]           = { 0 };
            
            // Mouse state
            bool        pMouseNewState[nMouseButtons] = { 0 };
            bool        pMouseOldState[nMouseButtons] = { 0 };
            HWButton    pMouseState   [nMouseButtons] = { 0 };
            
            
            void EngineThread();                  // The main engine thread
            void koi_ConfigureSystem();           // At the end of this file, chooses which components to compile
            
            static std::atomic<bool> bAtomActive; // Shutdown flag
            
        public:
            void koi_UpdateMouse        (int32_t x, int32_t y);
            void koi_UpdateMouseWheel   (int32_t delta);
            void koi_UpdateWindowSize   (int32_t x, int32_t y);
            void koi_UpdateViewport     ();
            void koi_ConstructFontSheet ();
            void koi_CoreUpdate         ();
            void koi_PrepareEngine      ();
            void koi_UpdateMouseState   (int32_t button, bool state);
            void koi_UpdateKeyState     (int32_t key,    bool state);
            void koi_UpdateMouseFocus   (bool state);
            void koi_UpdateKeyFocus     (bool state);
            void koi_Terminate          ();
            
        };
        
        KoiEngine::KoiEngine() {
            sAppName = "";
            koi_ConfigureSystem(); // Bring in relevant Platform & Rendering systems depending on compiler parameters
        }
        
        KoiEngine::~KoiEngine() { }
        
        rcode KoiEngine::Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync, bool cohesion) {
            bPixelCohesion  = cohesion;
            vScreenSize     = { screen_w, screen_h };
            vInvScreenSize  = { 1.0f / screen_w, 1.0f / screen_h };
            vPixelSize      = { pixel_w, pixel_h };
            vWindowSize     = vScreenSize * vPixelSize;
            bFullScreen     = full_screen;
            bEnableVSYNC    = vsync;
            vPixel          = 2.0f / vScreenSize;
            
            return (vPixelSize.x <= 0 || vPixelSize.y <= 0 || vScreenSize.x <= 0 || vScreenSize.y <= 0) ? OK : FAIL;
        }
        
        void KoiEngine::SetScreenSize(int w, int h) {
            vScreenSize    = { w, h };
            vInvScreenSize = { 1.0f / float(w), 1.0f / float(h) };
            delete pDrawTarget; // Erase existing window sprites
            pDrawTarget = new Sprite(vScreenSize.x, vScreenSize.y);
            
            renderer->ClearBuffer(BACK, true);
            renderer->DisplayFrame();
            renderer->ClearBuffer(BACK, true);
            renderer->UpdateViewport(vViewPos, vViewSize);
        }
        
        #if !defined(__APPLE__)
            rcode KoiEngine::Start() {
                if (platform->ApplicationStartUp() != OK) return FAIL;
                
                // Construct the window
                if (platform->CreateWindowPane({ 30, 30 }, vWindowSize, bFullScreen) != OK) return FAIL;
                koi_UpdateWindowSize(vWindowSize.x, vWindowSize.y);
                
                // Start the thread
                bAtomActive = true;
                std::thread t = std::thread(&KoiEngine::EngineThread, this);
                
                // Some implementations may form an event loop here
                platform->StartSystemEventLoop();
                
                // Wait for thread to be exited
                t.join();
                
                if (platform->ApplicationCleanUp() != OK) return FAIL;
                
                return OK;
            }
        #endif
        
        void            KoiEngine::SetWindowOffset  (const Vector2f& offset)  { SetWindowOffset(offset.x, offset.y); }
        void            KoiEngine::SetWindowOffset  (float x, float y)        { vOffset = { x, y };                  }
        void            KoiEngine::SetWindowScale   (const Vector2f& scale)   { SetWindowScale(scale.x, scale.y);    }
        void            KoiEngine::SetWindowScale   (float x, float y)        { vScale = { x, y };                   }
        void            KoiEngine::SetWindowTint    (const Color& t_tint)     { tint = t_tint;                       }
        
        void            KoiEngine::SetWindowCustomRenderFunction(std::function<void()> f) { funcHook = f; }
        
        Sprite*         KoiEngine::GetDrawTarget        ()              const { return pDrawTarget;                           }
        int32_t         KoiEngine::GetDrawTargetWidth   ()              const { return pDrawTarget ? pDrawTarget->width : 0;  }
        int32_t         KoiEngine::GetDrawTargetHeight  ()              const { return pDrawTarget ? pDrawTarget->height : 0; }
        
        uint32_t        KoiEngine::GetFPS               ()              const { return nLastFPS;                              }
        bool            KoiEngine::IsFocused            ()              const { return bHasInputFocus;                        }
        HWButton        KoiEngine::GetKey               (Key k)         const { return pKeyboardState[k];                     }
        HWButton        KoiEngine::GetMouse             (uint32_t b)    const { return pMouseState[b];                        }
        int32_t         KoiEngine::GetMouseX            ()              const { return vMousePos.x;                           }
        int32_t         KoiEngine::GetMouseY            ()              const { return vMousePos.y;                           }
        const Vector2i& KoiEngine::GetMousePos          ()              const { return vMousePos;                             }
        int32_t         KoiEngine::GetMouseWheel        ()              const { return nMouseWheelDelta;                      }
        int32_t         KoiEngine::ScreenWidth          ()              const { return vScreenSize.x;                         }
        int32_t         KoiEngine::ScreenHeight         ()              const { return vScreenSize.y;                         }
        float           KoiEngine::GetElapsedTime       ()              const { return fLastElapsed;                          }
        const Vector2i& KoiEngine::GetWindowSize        ()              const { return vWindowSize;                           }
        const Vector2i& KoiEngine::GetPixelSize         ()              const { return vPixelSize;                            }
        const Vector2i& KoiEngine::GetScreenPixelSize   ()              const { return vScreenPixelSize;                      }
        const Vector2i& KoiEngine::GetWindowMouse       ()              const { return vMouseWindowPos;                       }
        
        bool KoiEngine::Draw(const Vector2i& p, Color c)    { return Draw(p.x, p.y, c); }
        bool KoiEngine::Draw(int32_t x, int32_t y, Color c) {
            if (!pDrawTarget) return false;
            if (nColorMode == Color::NORMAL) return pDrawTarget->SetPixel(x, y, c);
            if (nColorMode == Color::MASK) if (c.a == 255) return pDrawTarget->SetPixel(x, y, c);
            if (nColorMode == Color::ALPHA) {
                Color d = pDrawTarget->GetPixel(x, y);
                float a = (float)(c.a / 255.0f) * fBlendFactor;
                float k = 1.0f - a;
                uint8_t r = a * (float)c.r + k * (float)d.r;
                uint8_t g = a * (float)c.g + k * (float)d.g;
                uint8_t b = a * (float)c.b + k * (float)d.b;
                return pDrawTarget->SetPixel(x, y, Color(r, g, b/*, (uint8_t)(p.a * fBlendFactor)*/));
            }
            if (nColorMode == Color::CUSTOM) return pDrawTarget->SetPixel(x, y, funcPixelMode(x, y, c, pDrawTarget->GetPixel(x, y)));
            return false;
        }
        
        void KoiEngine::DrawLine(const Vector2i& p1,     const Vector2i& p2,     Color c, uint32_t pattern) { DrawLine(p1.x, p1.y, p2.x, p2.y, c, pattern); }
        void KoiEngine::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Color c, uint32_t pattern) {
            int x, y, dx = x2 - x1, dy = y2 - y1, dx1, dy1, px, py, xe, ye, i;
            
            auto rol = [&](void) { pattern = (pattern << 1) | (pattern >> 31); return pattern & 1; };
            
            if (dx == 0) {
                if (y2 < y1) std::swap(y1, y2);
                for (y = y1; y <= y2; y++) if (rol()) Draw(x1, y, c);
                return;
            }

            if (dy == 0) {
                if (x2 < x1) std::swap(x1, x2);
                for (x = x1; x <= x2; x++) if (rol()) Draw(x, y1, c);
                return;
            }

            
            dx1 = abs(dx); dy1 = abs(dy);
            px = 2 * dy1 - dx1;    py = 2 * dx1 - dy1;
            if (dy1 <= dx1) {
                if (dx >= 0) { x = x1; y = y1; xe = x2; }
                else         { x = x2; y = y2; xe = x1; }
                
                if (rol()) Draw(x, y, c);

                for (i = 0; x < xe; i++) {
                    x++;
                    if (px < 0) px += 2 * dy1;
                    else        { y += ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) ? 1 : -1; px += 2 * (dy1 - dx1); }
                    if (rol()) Draw(x, y, c);
                }
            } else {
                if (dy >= 0) { x = x1; y = y1; ye = y2; }
                else         { x = x2; y = y2; ye = y1; }

                if (rol()) Draw(x, y, c);

                for (i = 0; y < ye; i++) {
                    y++;
                    if (py <= 0) py = py + 2 * dx1;
                    else         { x += ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) ? 1 : -1; py += 2 * (dx1 - dy1); }
                    if (rol()) Draw(x, y, c);
                }
            }
        }
        
        void KoiEngine::DrawCircle(const Vector2i& p,    int32_t radius, Color c, uint8_t mask) { DrawCircle(p.x, p.y, radius, c, mask); }
        void KoiEngine::DrawCircle(int32_t x, int32_t y, int32_t radius, Color c, uint8_t mask) {
            if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius) return;
            if (radius == 0) { Draw(x, y, c); return; }
            int x0 = 0, y0 = radius;
            int d = 3 - 2 * radius;

            while (y0 >= x0) {
                if (mask & 0x01) Draw(x + x0, y - y0, c);     // Q6 - upper right right
                if (mask & 0x04) Draw(x + y0, y + x0, c);     // Q4 - lower lower right
                if (mask & 0x10) Draw(x - x0, y + y0, c);     // Q2 - lower left left
                if (mask & 0x40) Draw(x - y0, y - x0, c);     // Q0 - upper upper left
                if (x0 != 0 && x0 != y0) {
                    if (mask & 0x02) Draw(x + y0, y - x0, c); // Q7 - upper upper right
                    if (mask & 0x08) Draw(x + x0, y + y0, c); // Q5 - lower right right
                    if (mask & 0x20) Draw(x - y0, y + x0, c); // Q3 - lower lower left
                    if (mask & 0x80) Draw(x - x0, y - y0, c); // Q1 - upper left left
                }

                if (d < 0) d += 4 * x0++ + 6;
                else d += 4 * (x0++ - y0--) + 10;
            }
        }
        
        void KoiEngine::FillCircle(const Vector2i& p,    int32_t radius, Color c) { FillCircle(p.x, p.y, radius, c); }
        void KoiEngine::FillCircle(int32_t x, int32_t y, int32_t radius, Color c) {
            if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius) return;

            if (radius == 0) { Draw(x, y, c); return; }
            
            int x0 = 0, y0 = radius;
            int d = 3 - 2 * radius;

            auto drawline = [&](int sx, int ex, int y) { for (int x = sx; x <= ex; x++) Draw(x, y, c); };

            while (y0 >= x0) {
                drawline(x - y0, x + y0, y - x0);
                if (x0 > 0) drawline(x - y0, x + y0, y + x0);

                if (d < 0) d += 4 * x0++ + 6;
                else {
                    if (x0 != y0) {
                        drawline(x - x0, x + x0, y - y0);
                        drawline(x - x0, x + x0, y + y0);
                    }
                    d += 4 * (x0++ - y0--) + 10;
                }
            }
                
        }
        
        void KoiEngine::DrawRect(const Vector2i& p,    const Vector2i& size, Color c) { DrawRect(p.x, p.y, size.x, size.y, c); }
        void KoiEngine::DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Color c) {
            DrawLine(x, y, x + w, y, c);
            DrawLine(x + w, y, x + w, y + h, c);
            DrawLine(x + w, y + h, x, y + h, c);
            DrawLine(x, y + h, x, y, c);
        }
        
        void KoiEngine::FillRect(const Vector2i& p,    const Vector2i& size, Color c) { FillRect(p.x, p.y, size.x, size.y, c);}
        void KoiEngine::FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Color c) {
            int32_t x2 = x + w, y2 = y + h;

            if (x < 0) x = 0;
            if (x >= (int32_t)GetDrawTargetWidth()) x = (int32_t)GetDrawTargetWidth();
            if (y < 0) y = 0;
            if (y >= (int32_t)GetDrawTargetHeight()) y = (int32_t)GetDrawTargetHeight();

            if (x2 < 0) x2 = 0;
            if (x2 >= (int32_t)GetDrawTargetWidth()) x2 = (int32_t)GetDrawTargetWidth();
            if (y2 < 0) y2 = 0;
            if (y2 >= (int32_t)GetDrawTargetHeight()) y2 = (int32_t)GetDrawTargetHeight();

            for (int i = x; i < x2; i++) for (int j = y; j < y2; j++) Draw(i, j, c);
        }

        void KoiEngine::DrawTriangle(const Vector2i& p1,     const Vector2i& p2,     const Vector2i& p3,     Color c) { DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, c); }
        void KoiEngine::DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color c) {
            DrawLine(x1, y1, x2, y2, c);
            DrawLine(x2, y2, x3, y3, c);
            DrawLine(x3, y3, x1, y1, c);
        }
        
        void KoiEngine::FillTriangle(const Vector2i& p1,     const Vector2i& p2,     const Vector2i& p3,     Color c) { FillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, c); }
        void KoiEngine::FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Color c) {
            auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) Draw(i, ny, c); };

            int t1x, t2x, y, minx, maxx, t1xp, t2xp;
            bool changed1 = false, changed2 = false;
            int signx1, signx2, dx1, dy1, dx2, dy2;
            int e1, e2;
            
            // Sort vertices
            if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); }
            if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); }
            if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); }

            t1x = t2x = x1; y = y1;
            dx1 = (int)(x2 - x1);
            if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
            else         signx1 = 1;
            dy1 = (int)(y2 - y1);

            dx2 = (int)(x3 - x1);
            if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
            else         signx2 = 1;
            dy2 = (int)(y3 - y1);

            if (dy1 > dx1) { std::swap(dx1, dy1); changed1 = true; }
            if (dy2 > dx2) { std::swap(dy2, dx2); changed2 = true; }

            e2 = (int)(dx2 >> 1);
            
            if (y1 == y2) goto next;
            e1 = (int)(dx1 >> 1);

            for (int i = 0; i < dx1;) {
                t1xp = 0; t2xp = 0;
                if (t1x < t2x) { minx = t1x; maxx = t2x; }
                else           { minx = t2x; maxx = t1x; }
                
                while (i < dx1) {
                    i++;
                    e1 += dy1;
                    while (e1 >= dx1) {
                        e1 -= dx1;
                        if (changed1) t1xp = signx1;
                        else          goto next1;
                    }
                    if (changed1) break;
                    else          t1x += signx1;
                }
                
                next1:
                while (1) {
                    e2 += dy2;
                    while (e2 >= dx2) {
                        e2 -= dx2;
                        if (changed2) t2xp = signx2;
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
                drawline(minx, maxx, y);
                
                if (!changed1) t1x += signx1;
                t1x += t1xp;
                if (!changed2) t2x += signx2;
                t2x += t2xp;
                y += 1;
                if (y == y2) break;

            }
            
            next:
            dx1 = (int)(x3 - x2);
            if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
            else         signx1 = 1;
            dy1 = (int)(y3 - y2);
            t1x = x2;

            if (dy1 > dx1) { std::swap(dy1, dx1); changed1 = true; }
            else           changed1 = false;

            e1 = (int)(dx1 >> 1);

            for (int i = 0; i <= dx1; i++) {
                t1xp = 0; t2xp = 0;
                if (t1x < t2x) { minx = t1x; maxx = t2x; }
                else           { minx = t2x; maxx = t1x; }
                
                while (i < dx1) {
                    e1 += dy1;
                    while (e1 >= dx1) {
                        e1 -= dx1;
                        if (changed1) { t1xp = signx1; break; }
                        else          goto next3;
                    }
                    if (changed1) break;
                    else          t1x += signx1;
                    if (i < dx1) i++;
                }
                
                next3:
                
                while (t2x != x3) {
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
        
        void KoiEngine::DrawSprite(const Vector2i& p,    Sprite* sprite, uint32_t scale, uint8_t flip) { DrawSprite(p.x, p.y, sprite, scale, flip); }
        void KoiEngine::DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale, uint8_t flip) {
            if (sprite == nullptr) return;

            int32_t fxs = 0, fxm = 1, fx = 0;
            int32_t fys = 0, fym = 1, fy = 0;
            if (flip & Sprite::Flip::HORZ) { fxs = sprite->width - 1; fxm = -1; }
            if (flip & Sprite::Flip::VERT) { fys = sprite->height - 1; fym = -1; }
            
            fx = fxs;
            if (scale > 1) {
                for (int32_t i = 0; i < sprite->width; i++, fx += fxm) {
                    fy = fys;
                    for (int32_t j = 0; j < sprite->height; j++, fy += fym)
                        for (uint32_t is = 0; is < scale; is++)
                            for (uint32_t js = 0; js < scale; js++)
                                Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx, fy));
                }
            } else {
                for (int32_t i = 0; i < sprite->width; i++, fx += fxm) {
                    fy = fys;
                    for (int32_t j = 0; j < sprite->height; j++, fy += fym)
                        Draw(x + i, y + j, sprite->GetPixel(fx, fy));
                }
            }
        }

        void KoiEngine::DrawPartialSprite(const Vector2i& p,    Sprite* sprite, const Vector2i& origin, const Vector2i& size, uint32_t scale, uint8_t flip) { DrawPartialSprite(p.x, p.y, sprite, origin.x, origin.y, size.x, size.y, scale, flip); }
        void KoiEngine::DrawPartialSprite(int32_t x, int32_t y, Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip) {
            if (sprite == nullptr) return;

            int32_t fxs = 0, fxm = 1, fx = 0;
            int32_t fys = 0, fym = 1, fy = 0;
            if (flip & Sprite::Flip::HORZ) { fxs = w - 1; fxm = -1; }
            if (flip & Sprite::Flip::VERT) { fys = h - 1; fym = -1; }
            
            fx = fxs;
            if (scale > 1) {
                for (int32_t i = 0; i < w; i++, fx += fxm) {
                    fy = fys;
                    for (int32_t j = 0; j < h; j++, fy += fym)
                        for (uint32_t is = 0; is < scale; is++)
                            for (uint32_t js = 0; js < scale; js++)
                                Draw(x + (i * scale) + is, y + (j * scale) + js, sprite->GetPixel(fx + ox, fy + oy));
                }
            } else {
                for (int32_t i = 0; i < w; i++, fx += fxm) {
                    fy = fys;
                    for (int32_t j = 0; j < h; j++, fy += fym)
                        Draw(x + i, y + j, sprite->GetPixel(fx + ox, fy + oy));
                }
            }
        }
        
        void KoiEngine::Clear(Color p) {
            int pixels = GetDrawTargetWidth() * GetDrawTargetHeight();
            Color* m = GetDrawTarget()->GetData();
            for (int i = 0; i < pixels; i++) m[i] = p;
        }
        
        void        KoiEngine::ClearBuffer (Color p, bool bDepth)   { renderer->ClearBuffer(p, bDepth); }
        void        KoiEngine::SetPixelMode(Color::Mode m)          { nColorMode = m;                   }
        Color::Mode KoiEngine::GetPixelMode()                       { return nColorMode;                }
        
        void KoiEngine::SetPixelMode(std::function<Color(const int x, const int y, const Color&, const Color&)> pixelMode) {
            funcPixelMode = pixelMode;
            nColorMode = Color::Mode::CUSTOM;
        }
        
        void KoiEngine::SetPixelBlend(float fBlend) {
            fBlendFactor = fBlend;
            if (fBlendFactor < 0.0f) fBlendFactor = 0.0f;
            if (fBlendFactor > 1.0f) fBlendFactor = 1.0f;
        }
        
        bool KoiEngine::OnUserCreate()                      { return false;                        }
        bool KoiEngine::OnUserUpdate(float fElapsedTime)    { UNUSED(fElapsedTime);  return false; }
        bool KoiEngine::OnUserDestroy()                     { return true;                         }
        
        void KoiEngine::koi_UpdateViewport() {
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
        
        void KoiEngine::koi_UpdateWindowSize(int32_t x, int32_t y) { vWindowSize = { x, y }; koi_UpdateViewport(); }
        
        void KoiEngine::koi_UpdateMouseWheel(int32_t delta) { nMouseWheelDeltaCache += delta; }
        
        void KoiEngine::koi_UpdateMouse(int32_t x, int32_t y) {
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
        
        void KoiEngine::koi_UpdateMouseState    (int32_t button, bool state)    { pMouseNewState[button] = state; }
        void KoiEngine::koi_UpdateKeyState      (int32_t key, bool state)       { pKeyNewState[key] = state;      }
        void KoiEngine::koi_UpdateMouseFocus    (bool state)                    { bHasMouseFocus = state;         }
        void KoiEngine::koi_UpdateKeyFocus      (bool state)                    { bHasInputFocus = state;         }
        void KoiEngine::koi_Terminate           ()                              { bAtomActive = false;            }
        
        void KoiEngine::EngineThread() {
            if (platform->ThreadStartUp() == FAIL) return;  // Allow platform to do stuff here if needed, since its now in the context of this thread
            
            koi_PrepareEngine();                            // Do engine context specific initialisation
            
            if (!OnUserCreate()) bAtomActive = false;       // Create user resources as part of this thread
            
            while (bAtomActive) {
                while (bAtomActive) { koi_CoreUpdate(); }   // Run as fast as possible
                
                if (!OnUserDestroy()) {                     // Allow the user to free resources if they have overrided the destroy function
                    bAtomActive = true;                     // User denied destroy for some reason, so continue running
                }
            }
            
            platform->ThreadCleanUp();
        }
        
        void KoiEngine::koi_PrepareEngine() {
            // Start OpenGL, the context is owned by the game thread
            if (platform->CreateGraphics(bFullScreen, bEnableVSYNC, vViewPos, vViewSize) == FAIL) return;
            
            // Create Primary window "0"
            pDrawTarget = new Sprite(vScreenSize.x, vScreenSize.y);
            nResID = renderer->CreateTexture(vScreenSize.x, vScreenSize.y);
            renderer->UpdateTexture(nResID, pDrawTarget);
            
            m_tp1 = std::chrono::system_clock::now();
            m_tp2 = std::chrono::system_clock::now();
        }
        
        void KoiEngine::koi_CoreUpdate() {
            // Handle Timing
            m_tp2 = std::chrono::system_clock::now();
            std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
            m_tp1 = m_tp2;
            
            // Our time per frame coefficient
            float fElapsedTime = elapsedTime.count();
            fLastElapsed = fElapsedTime;
            
            
            platform->HandleSystemEvent(); // Some platforms will need to check for events
            
            // Compare hardware input states from previous frame
            auto ScanHardware = [&](HWButton* pKeys, bool* pStateOld, bool* pStateNew, uint32_t nKeyCount) {
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
            
            
            if (!OnUserUpdate(fElapsedTime)) bAtomActive = false; // Handle Frame Update
            
            // Display Frame
            renderer->UpdateViewport(vViewPos, vViewSize);
            renderer->ClearBuffer(Color::BLACK, true);
            
            renderer->PrepareDrawing();
            
            if (funcHook == nullptr) {
                renderer->ApplyTexture(nResID);
                renderer->UpdateTexture(nResID, pDrawTarget);
                renderer->DrawWindowQuad(vOffset, vScale, tint);
                
            } else funcHook();
            
            
            renderer->DisplayFrame(); // Present Graphics to screen
            
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
    }

#endif /* KoiEngine_h */
