//
//  Renderer.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Renderer_h
#define Renderer_h

    #include "Global.h"

    #define UNUSED(x) (void)(x)

    namespace koi {
        // MARK: koi::Renderer
        // +------------------------------------------------------------------------------+
        // | koi::Renderer - Renders                                                      |
        // +------------------------------------------------------------------------------+
        class Renderer {
        public:
            virtual ~Renderer() = default;
            virtual void       PrepareDevice() = 0;
            virtual koi::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
            virtual koi::rcode DestroyDevice() = 0;
            virtual void       DisplayFrame() = 0;
            virtual void       PrepareDrawing() = 0;
            virtual void       DrawWindowQuad(const koi::Vector2f& offset, const koi::Vector2f& scale, const koi::Color tint) = 0;
            virtual uint32_t   CreateTexture(const uint32_t width, const uint32_t height) = 0;
            virtual void       UpdateTexture(uint32_t id, koi::Sprite* spr) = 0;
            virtual uint32_t   DeleteTexture(const uint32_t id) = 0;
            virtual void       ApplyTexture(uint32_t id) = 0;
            virtual void       UpdateViewport(const koi::Vector2i& pos, const koi::Vector2i& size) = 0;
            virtual void       ClearBuffer(koi::Color p, bool bDepth) = 0;
            static koi::PixelGameEngine* ptrPGE;
        };
    }
    

    // MARK: Renderer OpenGL 1.0
    // +------------------------------------------------------------------------------+
    // | START RENDERER: OpenGL 1.0 (the original, the best...)                       |
    // +------------------------------------------------------------------------------+

    #if !defined(KOI_GFX_OPENGL33) && !defined(KOI_GFX_DIRECTX10)
//    #if defined(KOI_GFX_OPENGL10)
        #if defined(_WIN32)
            #include <windows.h>
            #include <dwmapi.h>
            #include <GL/gl.h>
            #pragma comment(lib, "Dwmapi.lib")
            typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
            static wglSwapInterval_t* wglSwapInterval = nullptr;
            typedef HDC glDeviceContext_t;
            typedef HGLRC glRenderContext_t;
        #endif

        #if defined(__linux__) || defined(__FreeBSD__)
            #include <GL/gl.h>
            namespace X11 {
                #include <GL/glx.h>
                #include <X11/X.h>
                #include <X11/Xlib.h>
            }

            typedef int(glSwapInterval_t)(X11::Display* dpy, X11::GLXDrawable drawable, int interval);
            static glSwapInterval_t* glSwapIntervalEXT;
            typedef X11::GLXContext glDeviceContext_t;
            typedef X11::GLXContext glRenderContext_t;
        #endif

        #if defined(__APPLE__)
            #define GL_SILENCE_DEPRECATION
            #include <GLUT/glut.h>
            #include <OpenGL/OpenGL.h>
            #include <OpenGL/gl.h>
            #include <OpenGL/glu.h>
        #endif

        namespace koi {
            class Renderer_OGL10 : public koi::Renderer {
            private:
                #if defined(__APPLE__)
                    bool mFullScreen = false;
                #else
                    glDeviceContext_t glDeviceContext = 0;
                    glRenderContext_t glRenderContext = 0;
                #endif
            
                bool bSync = false;
            
                #if defined(__linux__) || defined(__FreeBSD__)
                    X11::Display* koi_Display = nullptr;
                    X11::Window* koi_Window = nullptr;
                    X11::XVisualInfo* koi_VisualInfo = nullptr;
                #endif
            
            public:
                void PrepareDevice() override {
                    #if defined(__APPLE__)
                        //glutInit has to be called with main() arguments, make fake ones
                        int argc = 0;
                        char* argv[1] = { (char*)"" };
                        glutInit(&argc, argv);
                        
                        glutInitWindowPosition(0, 0);
                        glutInitWindowSize(512, 512);
                        
                        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
                        
                        // Creates the window and the OpenGL context for it
                        glutCreateWindow("OneLoneCoder.com - Pixel Game Engine");
                        
                        glEnable(GL_TEXTURE_2D); // Turn on texturing
                        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
                    #endif
                }
            
                koi::rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) override {
                    #if defined(_WIN32)
                        // Create Device Context
                        glDeviceContext = GetDC((HWND)(params[0]));
                        PIXELFORMATDESCRIPTOR pfd =
                        {
                            sizeof(PIXELFORMATDESCRIPTOR), 1,
                            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                            PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                            PFD_MAIN_PLANE, 0, 0, 0, 0
                        };
                        
                        int pf = 0;
                        if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return koi::FAIL;
                        SetPixelFormat(glDeviceContext, pf, &pfd);
                        
                        if (!(glRenderContext = wglCreateContext(glDeviceContext))) return koi::FAIL;
                        wglMakeCurrent(glDeviceContext, glRenderContext);
                        
                        // Remove Frame cap
                        wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
                        if (wglSwapInterval && !bVSYNC) wglSwapInterval(0);
                        bSync = bVSYNC;
                    #endif
                
                    #if defined(__linux__) || defined(__FreeBSD__)
                        using namespace X11;
                        // Linux has tighter coupling between OpenGL and X11, so we store
                        // various "platform" handles in the renderer
                        koi_Display = (X11::Display*)(params[0]);
                        koi_Window = (X11::Window*)(params[1]);
                        koi_VisualInfo = (X11::XVisualInfo*)(params[2]);
                        
                        glDeviceContext = glXCreateContext(koi_Display, koi_VisualInfo, nullptr, GL_TRUE);
                        glXMakeCurrent(koi_Display, *koi_Window, glDeviceContext);
                        
                        XWindowAttributes gwa;
                        XGetWindowAttributes(koi_Display, *koi_Window, &gwa);
                        glViewport(0, 0, gwa.width, gwa.height);
                        
                        glSwapIntervalEXT = nullptr;
                        glSwapIntervalEXT = (glSwapInterval_t*)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");
                        
                        if (glSwapIntervalEXT == nullptr && !bVSYNC)
                        {
                            printf("NOTE: Could not disable VSYNC, glXSwapIntervalEXT() was not found!\n");
                            printf("      Don't worry though, things will still work, it's just the\n");
                            printf("      frame rate will be capped to your monitors refresh rate - javidx9\n");
                        }
                        
                        if (glSwapIntervalEXT != nullptr && !bVSYNC)
                            glSwapIntervalEXT(koi_Display, *koi_Window, 0);
                    #endif
                
                    #if defined(__APPLE__)
                        mFullScreen = bFullScreen;
                        if (!bVSYNC)
                        {
                            GLint sync = 0;
                            CGLContextObj ctx = CGLGetCurrentContext();
                            if (ctx) CGLSetParameter(ctx, kCGLCPSwapInterval, &sync);
                        }
                    #else
                        glEnable(GL_TEXTURE_2D); // Turn on texturing
                        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
                    #endif
                    return koi::rcode::OK;
                }
            
                koi::rcode DestroyDevice() override {
                    #if defined(_WIN32)
                        wglDeleteContext(glRenderContext);
                    #endif
                
                    #if defined(__linux__) || defined(__FreeBSD__)
                        glXMakeCurrent(koi_Display, None, NULL);
                        glXDestroyContext(koi_Display, glDeviceContext);
                    #endif
                
                    #if defined(__APPLE__)
                        glutDestroyWindow(glutGetWindow());
                    #endif
                    return koi::rcode::OK;
                }
            
                void DisplayFrame() override {
                    #if defined(_WIN32)
                        SwapBuffers(glDeviceContext);
                        if (bSync) DwmFlush(); // Woooohooooooo!!!! SMOOOOOOOTH!
                    #endif
                
                    #if defined(__linux__) || defined(__FreeBSD__)
                        X11::glXSwapBuffers(koi_Display, *koi_Window);
                    #endif
                
                    #if defined(__APPLE__)
                        glutSwapBuffers();
                    #endif
                }
            
                void PrepareDrawing() override {
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }
            
                void DrawWindowQuad(const koi::Vector2f& offset, const koi::Vector2f& scale, const koi::Color tint) override {
                    glBegin(GL_QUADS);
                    glColor4ub(tint.r, tint.g, tint.b, tint.a);
                    glTexCoord2f(0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
                    glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
                    glTexCoord2f(0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
                    glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
                    glTexCoord2f(1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
                    glVertex3f(1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
                    glTexCoord2f(1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
                    glVertex3f(1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
                    glEnd();
                }
            
                uint32_t CreateTexture(const uint32_t width, const uint32_t height) override {
                    UNUSED(width);
                    UNUSED(height);
                    uint32_t id = 0;
                    glGenTextures(1, &id);
                    glBindTexture(GL_TEXTURE_2D, id);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                    return id;
                }
            
                uint32_t DeleteTexture(const uint32_t id) override {
                    glDeleteTextures(1, &id);
                    return id;
                }
            
                void UpdateTexture(uint32_t id, koi::Sprite* spr) override {
                    UNUSED(id);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, spr->GetData());
                }
            
                void ApplyTexture(uint32_t id) override {
                    glBindTexture(GL_TEXTURE_2D, id);
                }
            
                void ClearBuffer(koi::Color p, bool bDepth) override {
                    glClearColor(float(p.r) / 255.0f, float(p.g) / 255.0f, float(p.b) / 255.0f, float(p.a) / 255.0f);
                    glClear(GL_COLOR_BUFFER_BIT);
                    if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
                }
            
                void UpdateViewport(const koi::Vector2i& pos, const koi::Vector2i& size) override {
                    #if defined(__APPLE__)
                        if (!mFullScreen) glutReshapeWindow(size.x, size.y);
                    #else
                        glViewport(pos.x, pos.y, size.x, size.y);
                    #endif
                }
            };
        }
    #endif
    // +------------------------------------------------------------------------------+
    // | END RENDERER: OpenGL 1.0 (the original, the best...)                         |
    // +------------------------------------------------------------------------------+

#endif /* Renderer_h */
