/*
  License (KOI-3)
  ~~~~~~~~~~~~~~~

  Copyright 2018 - 2020 OneLoneCoder.com

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  1. Redistributions or derivations of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions or derivative works in binary form must reproduce the above
  copyright notice. This list of conditions and the following disclaimer must be
  reproduced in the documentation and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may
  be used to endorse or promote products derived from this software without specific
  prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.
*/

#ifndef KOI_PGE_DEF
#define KOI_PGE_DEF

    // MARK: Standard Includes
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
    #include "Sprite.h"
    #include "Renderer.h"
    #include "Platform.h"
    #include "Global.h"
    #include "PixelGameEngine.h"
    #include "WindowsPlatform.h"
    #include "LinuxPlatform.h"
    #include "MacintoshPlatform.h"


    // MARK: Compiler Configuration
    // +------------------------------------------------------------------------------+
    // | COMPILER CONFIGURATION ODDITIES                                              |
    // +------------------------------------------------------------------------------+
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

    #if defined(USE_EXPERIMENTAL_FS) || defined(FORCE_EXPERIMENTAL_FS) // C++14
        #define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
        #include <experimental/filesystem>
        namespace _gfs = std::experimental::filesystem::v1;
    #else // C++17
        #include <filesystem>
        namespace _gfs = std::filesystem;
    #endif

    #if defined(UNICODE) || defined(_UNICODE)
        #define koiT(s) L##s
    #else
        #define koiT(s) s
    #endif

    

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



// MARK: KOI_PGE_APPLICATION
// +------------------------------------------------------------------------------+
// | START OF KOI_PGE_APPLICATION                                                 |
// +------------------------------------------------------------------------------+
#ifdef KOI_PGE_APPLICATION
#undef KOI_PGE_APPLICATION

    // MARK: koi::PixelGameEngine impl;
    namespace koi {
        // Need a couple of statics as these are singleton instances
        // read from multiple locations
        std::atomic<bool> PixelGameEngine::bAtomActive{ false };
        koi::PixelGameEngine* koi::Platform::ptrPGE = nullptr;
        koi::PixelGameEngine* koi::Renderer::ptrPGE = nullptr;
    };

    // MARK: Platform Specifics;
    // +------------------------------------------------------------------------------+
    // | koiPixelGameEngine PLATFORM SPECIFIC IMPLEMENTATIONS                         |
    // +------------------------------------------------------------------------------+


    // MARK: Renderer OpenGL 1.0
    // +------------------------------------------------------------------------------+
    // | START RENDERER: OpenGL 1.0 (the original, the best...)                       |
    // +------------------------------------------------------------------------------+
    #if defined(KOI_GFX_OPENGL10)
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
    #endif

    // MARK: WINDOWS
    // +------------------------------------------------------------------------------+
    // | START PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                        |
    // +------------------------------------------------------------------------------+
    #if defined(_WIN32)
        #if !defined(__MINGW32__)
            #pragma comment(lib, "user32.lib")    // Visual Studio Only
            #pragma comment(lib, "gdi32.lib")     // For other Windows Compilers please add
            #pragma comment(lib, "opengl32.lib")  // these libs to your linker input

        #else
            // In Code::Blocks
            #if !defined(_WIN32_WINNT)
                #ifdef HAVE_MSMF
                    #define _WIN32_WINNT 0x0600 // Windows Vista
                #else
                    #define _WIN32_WINNT 0x0500 // Windows 2000
                #endif
            #endif
        #endif

        // Include WinAPI
        #if !defined(__MINGW32__)
            #define NOMINMAX
        #endif

        #define VC_EXTRALEAN
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
    #endif
    // +------------------------------------------------------------------------------+
    // | END PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                          |
    // +------------------------------------------------------------------------------+

    namespace koi {
        void PixelGameEngine::koi_ConfigureSystem() {
            #if defined(_WIN32)
                platform = std::make_unique<koi::Platform_Windows>();
            #endif
                    
            #if defined(__linux__) || defined(__FreeBSD__)
                platform = std::make_unique<koi::Platform_Linux>();
            #endif
                    
            #if defined(__APPLE__)
                platform = std::make_unique<koi::Platform_GLUT>();
            #endif
                    
                    
                    
            #if defined(KOI_GFX_OPENGL10)
                renderer = std::make_unique<koi::Renderer_OGL10>();
            #endif
                    
            #if defined(KOI_GFX_OPENGL33)
                renderer = std::make_unique<koi::Renderer_OGL33>();
            #endif
                    
            #if defined(KOI_GFX_DIRECTX10)
                renderer = std::make_unique<koi::Renderer_DX10>();
            #endif
                
            // Associate components with PGE instance
            platform->ptrPGE = this;
            renderer->ptrPGE = this;
        }
    }

#endif // KOI_PGE_APPLICATION

// +------------------------------------------------------------------------------+
// | END OF KOI_PGE_APPLICATION                                                   |
// +------------------------------------------------------------------------------+
