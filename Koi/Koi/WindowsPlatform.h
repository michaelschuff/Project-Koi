//
//  WindowsPlatform.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef WindowsPlatform_h
#define WindowsPlatform_h

    #include "Global.h"
    #include "Platform.h"

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

        namespace koi {
            class Platform_Windows : public koi::Platform {
            private:
                HWND koi_hWnd = nullptr;
                std::wstring wsAppName;
                
                std::wstring ConvertS2W(std::string s) {
                    #ifdef __MINGW32__
                        wchar_t* buffer = new wchar_t[s.length() + 1];
                        mbstowcs(buffer, s.c_str(), s.length());
                        buffer[s.length()] = L'\0';
                    #else
                        int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
                        wchar_t* buffer = new wchar_t[count];
                        MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);
                    #endif
                    std::wstring w(buffer);
                    delete[] buffer;
                    return w;
                }
                
            public:
                virtual koi::rcode ApplicationStartUp() override { return koi::rcode::OK; }
                virtual koi::rcode ApplicationCleanUp() override { return koi::rcode::OK; }
                virtual koi::rcode ThreadStartUp() override { return koi::rcode::OK; }
                
                virtual koi::rcode ThreadCleanUp() override {
                    renderer->DestroyDevice();
                    PostMessage(koi_hWnd, WM_DESTROY, 0, 0);
                    return koi::OK;
                }
                
                virtual koi::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const koi::Vector2i& vViewPos, const koi::Vector2i& vViewSize) override {
                    if (renderer->CreateDevice({ koi_hWnd }, bFullScreen, bEnableVSYNC) == koi::rcode::OK) {
                        renderer->UpdateViewport(vViewPos, vViewSize);
                        return koi::rcode::OK;
                    } else {
                        return koi::rcode::FAIL;
                    }
                }
                
                virtual koi::rcode CreateWindowPane(const koi::Vector2i& vWindowPos, koi::Vector2i& vWindowSize, bool bFullScreen) override {
                    WNDCLASS wc;
                    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
                    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
                    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
                    wc.hInstance = GetModuleHandle(nullptr);
                    wc.lpfnWndProc = koi_WindowEvent;
                    wc.cbClsExtra = 0;
                    wc.cbWndExtra = 0;
                    wc.lpszMenuName = nullptr;
                    wc.hbrBackground = nullptr;
                    wc.lpszClassName = koiT("KOI_PIXEL_GAME_ENGINE");
                    RegisterClass(&wc);
                    
                    // Define window furniture
                    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
                    DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;
                    
                    koi::Vector2i vTopLeft = vWindowPos;
                    
                    // Handle Fullscreen
                    if (bFullScreen) {
                        dwExStyle = 0;
                        dwStyle = WS_VISIBLE | WS_POPUP;
                        HMONITOR hmon = MonitorFromWindow(koi_hWnd, MONITOR_DEFAULTTONEAREST);
                        MONITORINFO mi = { sizeof(mi) };
                        if (!GetMonitorInfo(hmon, &mi)) return koi::rcode::FAIL;
                        vWindowSize = { mi.rcMonitor.right, mi.rcMonitor.bottom };
                        vTopLeft.x = 0;
                        vTopLeft.y = 0;
                    }
                    
                    // Keep client size as requested
                    RECT rWndRect = { 0, 0, vWindowSize.x, vWindowSize.y };
                    AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
                    int width = rWndRect.right - rWndRect.left;
                    int height = rWndRect.bottom - rWndRect.top;
                    
                    koi_hWnd = CreateWindowEx(dwExStyle, koiT("KOI_PIXEL_GAME_ENGINE"), koiT(""), dwStyle,
                                              vTopLeft.x, vTopLeft.y, width, height, NULL, NULL, GetModuleHandle(nullptr), this);
                    
                    // Create Keyboard Mapping
                    mapKeys[0x00] = Key::NONE;
                    mapKeys[0x41] = Key::A; mapKeys[0x42] = Key::B; mapKeys[0x43] = Key::C; mapKeys[0x44] = Key::D; mapKeys[0x45] = Key::E;
                    mapKeys[0x46] = Key::F; mapKeys[0x47] = Key::G; mapKeys[0x48] = Key::H; mapKeys[0x49] = Key::I; mapKeys[0x4A] = Key::J;
                    mapKeys[0x4B] = Key::K; mapKeys[0x4C] = Key::L; mapKeys[0x4D] = Key::M; mapKeys[0x4E] = Key::N; mapKeys[0x4F] = Key::O;
                    mapKeys[0x50] = Key::P; mapKeys[0x51] = Key::Q; mapKeys[0x52] = Key::R; mapKeys[0x53] = Key::S; mapKeys[0x54] = Key::T;
                    mapKeys[0x55] = Key::U; mapKeys[0x56] = Key::V; mapKeys[0x57] = Key::W; mapKeys[0x58] = Key::X; mapKeys[0x59] = Key::Y;
                    mapKeys[0x5A] = Key::Z;
                    
                    mapKeys[VK_F1] = Key::F1; mapKeys[VK_F2] = Key::F2; mapKeys[VK_F3] = Key::F3; mapKeys[VK_F4] = Key::F4;
                    mapKeys[VK_F5] = Key::F5; mapKeys[VK_F6] = Key::F6; mapKeys[VK_F7] = Key::F7; mapKeys[VK_F8] = Key::F8;
                    mapKeys[VK_F9] = Key::F9; mapKeys[VK_F10] = Key::F10; mapKeys[VK_F11] = Key::F11; mapKeys[VK_F12] = Key::F12;
                    
                    mapKeys[VK_DOWN] = Key::DOWN; mapKeys[VK_LEFT] = Key::LEFT; mapKeys[VK_RIGHT] = Key::RIGHT; mapKeys[VK_UP] = Key::UP;
                    mapKeys[VK_RETURN] = Key::ENTER; //mapKeys[VK_RETURN] = Key::RETURN;
                    
                    mapKeys[VK_BACK] = Key::BACK; mapKeys[VK_ESCAPE] = Key::ESCAPE; mapKeys[VK_RETURN] = Key::ENTER; mapKeys[VK_PAUSE] = Key::PAUSE;
                    mapKeys[VK_SCROLL] = Key::SCROLL; mapKeys[VK_TAB] = Key::TAB; mapKeys[VK_DELETE] = Key::DEL; mapKeys[VK_HOME] = Key::HOME;
                    mapKeys[VK_END] = Key::END; mapKeys[VK_PRIOR] = Key::PGUP; mapKeys[VK_NEXT] = Key::PGDN; mapKeys[VK_INSERT] = Key::INS;
                    mapKeys[VK_SHIFT] = Key::SHIFT; mapKeys[VK_CONTROL] = Key::CTRL;
                    mapKeys[VK_SPACE] = Key::SPACE;
                    
                    mapKeys[0x30] = Key::K0; mapKeys[0x31] = Key::K1; mapKeys[0x32] = Key::K2; mapKeys[0x33] = Key::K3; mapKeys[0x34] = Key::K4;
                    mapKeys[0x35] = Key::K5; mapKeys[0x36] = Key::K6; mapKeys[0x37] = Key::K7; mapKeys[0x38] = Key::K8; mapKeys[0x39] = Key::K9;
                    
                    mapKeys[VK_NUMPAD0] = Key::NP0; mapKeys[VK_NUMPAD1] = Key::NP1; mapKeys[VK_NUMPAD2] = Key::NP2; mapKeys[VK_NUMPAD3] = Key::NP3; mapKeys[VK_NUMPAD4] = Key::NP4;
                    mapKeys[VK_NUMPAD5] = Key::NP5; mapKeys[VK_NUMPAD6] = Key::NP6; mapKeys[VK_NUMPAD7] = Key::NP7; mapKeys[VK_NUMPAD8] = Key::NP8; mapKeys[VK_NUMPAD9] = Key::NP9;
                    mapKeys[VK_MULTIPLY] = Key::NP_MUL; mapKeys[VK_ADD] = Key::NP_ADD; mapKeys[VK_DIVIDE] = Key::NP_DIV; mapKeys[VK_SUBTRACT] = Key::NP_SUB; mapKeys[VK_DECIMAL] = Key::NP_DECIMAL;
                    return koi::OK;
                }
                
                virtual koi::rcode SetWindowTitle(const std::string& s) override {
                    #ifdef UNICODE
                        SetWindowText(koi_hWnd, ConvertS2W(s).c_str());
                    #else
                        SetWindowText(koi_hWnd, s.c_str());
                    #endif
                    return koi::OK;
                }
                
                virtual koi::rcode StartSystemEventLoop() override {
                    MSG msg;
                    while (GetMessage(&msg, NULL, 0, 0) > 0) {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                    return koi::OK;
                }
                
                virtual koi::rcode HandleSystemEvent() override { return koi::rcode::FAIL; }
                
                // Windows Event Handler - this is statically connected to the windows event system
                static LRESULT CALLBACK koi_WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
                    switch (uMsg) {
                        case WM_MOUSEMOVE: {
                            // Thanks @ForAbby (Discord)
                            uint16_t x = lParam & 0xFFFF; uint16_t y = (lParam >> 16) & 0xFFFF;
                            int16_t ix = *(int16_t*)&x;   int16_t iy = *(int16_t*)&y;
                            ptrPGE->koi_UpdateMouse(ix, iy);
                            return 0;
                        }
                        case WM_SIZE:       ptrPGE->koi_UpdateWindowSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF); return 0;
                        case WM_MOUSEWHEEL: ptrPGE->koi_UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));           return 0;
                        case WM_MOUSELEAVE: ptrPGE->koi_UpdateMouseFocus(false);                                    return 0;
                        case WM_SETFOCUS: ptrPGE->koi_UpdateKeyFocus(true);                                       return 0;
                        case WM_KILLFOCUS:  ptrPGE->koi_UpdateKeyFocus(false);                                      return 0;
                        case WM_KEYDOWN:  ptrPGE->koi_UpdateKeyState(mapKeys[wParam], true);                      return 0;
                        case WM_KEYUP:    ptrPGE->koi_UpdateKeyState(mapKeys[wParam], false);                     return 0;
                        case WM_LBUTTONDOWN:ptrPGE->koi_UpdateMouseState(0, true);                                  return 0;
                        case WM_LBUTTONUP:  ptrPGE->koi_UpdateMouseState(0, false);                                 return 0;
                        case WM_RBUTTONDOWN:ptrPGE->koi_UpdateMouseState(1, true);                                  return 0;
                        case WM_RBUTTONUP:  ptrPGE->koi_UpdateMouseState(1, false);                                 return 0;
                        case WM_MBUTTONDOWN:ptrPGE->koi_UpdateMouseState(2, true);                                  return 0;
                        case WM_MBUTTONUP:  ptrPGE->koi_UpdateMouseState(2, false);                                 return 0;
                        case WM_CLOSE:    ptrPGE->koi_Terminate();                                                return 0;
                        case WM_DESTROY:  PostQuitMessage(0); DestroyWindow(hWnd);                return 0;
                    }
                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
                }
            };
        }
    #endif
    // +------------------------------------------------------------------------------+
    // | END PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                          |
    // +------------------------------------------------------------------------------+
#endif /* WindowsPlatform_h */
