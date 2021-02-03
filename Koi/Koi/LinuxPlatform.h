//
//  LinuxPlatform.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef LinuxPlatform_h
#define LinuxPlatform_h

    #include "Global.h"
    #include "Platform.h"

    // MARK: LINUX
    // +------------------------------------------------------------------------------+
    // | START PLATFORM: LINUX                                                        |
    // +------------------------------------------------------------------------------+
    #if defined(__linux__) || defined(__FreeBSD__)
        namespace koi {
            class Platform_Linux : public koi::Platform {
            private:
                X11::Display* koi_Display = nullptr;
                X11::Window          koi_WindowRoot;
                X11::Window          koi_Window;
                X11::XVisualInfo* koi_VisualInfo;
                X11::Colormap                koi_ColourMap;
                X11::XSetWindowAttributes    koi_SetWindowAttribs;
                
            public:
                virtual koi::rcode ApplicationStartUp() override { return koi::rcode::OK; }
                
                virtual koi::rcode ApplicationCleanUp() override { return koi::rcode::OK; }
                
                virtual koi::rcode ThreadStartUp() override { return koi::rcode::OK; }
                
                virtual koi::rcode ThreadCleanUp() override {
                    renderer->DestroyDevice();
                    return koi::OK;
                }
                
                virtual koi::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const koi::Vector2i& vViewPos, const koi::Vector2i& vViewSize) override {
                    if (renderer->CreateDevice({ koi_Display, &koi_Window, koi_VisualInfo }, bFullScreen, bEnableVSYNC) == koi::rcode::OK) {
                        renderer->UpdateViewport(vViewPos, vViewSize);
                        return koi::rcode::OK;
                    } else {
                        return koi::rcode::FAIL;
                    }
                }
                
                virtual koi::rcode CreateWindowPane(const koi::Vector2i& vWindowPos, koi::Vector2i& vWindowSize, bool bFullScreen) override {
                    using namespace X11;
                    XInitThreads();
                    
                    // Grab the deafult display and window
                    koi_Display = XOpenDisplay(NULL);
                    koi_WindowRoot = DefaultRootWindow(koi_Display);
                    
                    // Based on the display capabilities, configure the appearance of the window
                    GLint koi_GLAttribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
                    koi_VisualInfo = glXChooseVisual(koi_Display, 0, koi_GLAttribs);
                    koi_ColourMap = XCreateColormap(koi_Display, koi_WindowRoot, koi_VisualInfo->visual, AllocNone);
                    koi_SetWindowAttribs.colormap = koi_ColourMap;
                    
                    // Register which events we are interested in receiving
                    koi_SetWindowAttribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                    ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;
                    
                    // Create the window
                    koi_Window = XCreateWindow(koi_Display, koi_WindowRoot, vWindowPos.x, vWindowPos.y,
                                               vWindowSize.x, vWindowSize.y,
                                               0, koi_VisualInfo->depth, InputOutput, koi_VisualInfo->visual,
                                               CWColormap | CWEventMask, &koi_SetWindowAttribs);
                    
                    Atom wmDelete = XInternAtom(koi_Display, "WM_DELETE_WINDOW", true);
                    XSetWMProtocols(koi_Display, koi_Window, &wmDelete, 1);
                    
                    XMapWindow(koi_Display, koi_Window);
                    XStoreName(koi_Display, koi_Window, "OneLoneCoder.com - Pixel Game Engine");
                    
                    if (bFullScreen) { // Thanks DragonEye, again :D
                        Atom wm_state;
                        Atom fullscreen;
                        wm_state = XInternAtom(koi_Display, "_NET_WM_STATE", False);
                        fullscreen = XInternAtom(koi_Display, "_NET_WM_STATE_FULLSCREEN", False);
                        XEvent xev{ 0 };
                        xev.type = ClientMessage;
                        xev.xclient.window = koi_Window;
                        xev.xclient.message_type = wm_state;
                        xev.xclient.format = 32;
                        xev.xclient.data.l[0] = (bFullScreen ? 1 : 0);   // the action (0: off, 1: on, 2: toggle)
                        xev.xclient.data.l[1] = fullscreen;             // first property to alter
                        xev.xclient.data.l[2] = 0;                      // second property to alter
                        xev.xclient.data.l[3] = 0;                      // source indication
                        XMapWindow(koi_Display, koi_Window);
                        XSendEvent(koi_Display, DefaultRootWindow(koi_Display), False,
                                   SubstructureRedirectMask | SubstructureNotifyMask, &xev);
                        XFlush(koi_Display);
                        XWindowAttributes gwa;
                        XGetWindowAttributes(koi_Display, koi_Window, &gwa);
                        vWindowSize.x = gwa.width;
                        vWindowSize.y = gwa.height;
                    }
                    
                    // Create Keyboard Mapping
                    mapKeys[0x00] = Key::NONE;
                    mapKeys[0x61] = Key::A; mapKeys[0x62] = Key::B; mapKeys[0x63] = Key::C; mapKeys[0x64] = Key::D; mapKeys[0x65] = Key::E;
                    mapKeys[0x66] = Key::F; mapKeys[0x67] = Key::G; mapKeys[0x68] = Key::H; mapKeys[0x69] = Key::I; mapKeys[0x6A] = Key::J;
                    mapKeys[0x6B] = Key::K; mapKeys[0x6C] = Key::L; mapKeys[0x6D] = Key::M; mapKeys[0x6E] = Key::N; mapKeys[0x6F] = Key::O;
                    mapKeys[0x70] = Key::P; mapKeys[0x71] = Key::Q; mapKeys[0x72] = Key::R; mapKeys[0x73] = Key::S; mapKeys[0x74] = Key::T;
                    mapKeys[0x75] = Key::U; mapKeys[0x76] = Key::V; mapKeys[0x77] = Key::W; mapKeys[0x78] = Key::X; mapKeys[0x79] = Key::Y;
                    mapKeys[0x7A] = Key::Z;
                    
                    mapKeys[XK_F1] = Key::F1; mapKeys[XK_F2] = Key::F2; mapKeys[XK_F3] = Key::F3; mapKeys[XK_F4] = Key::F4;
                    mapKeys[XK_F5] = Key::F5; mapKeys[XK_F6] = Key::F6; mapKeys[XK_F7] = Key::F7; mapKeys[XK_F8] = Key::F8;
                    mapKeys[XK_F9] = Key::F9; mapKeys[XK_F10] = Key::F10; mapKeys[XK_F11] = Key::F11; mapKeys[XK_F12] = Key::F12;
                    
                    mapKeys[XK_Down] = Key::DOWN; mapKeys[XK_Left] = Key::LEFT; mapKeys[XK_Right] = Key::RIGHT; mapKeys[XK_Up] = Key::UP;
                    mapKeys[XK_KP_Enter] = Key::ENTER; mapKeys[XK_Return] = Key::ENTER;
                    
                    mapKeys[XK_BackSpace] = Key::BACK; mapKeys[XK_Escape] = Key::ESCAPE; mapKeys[XK_Linefeed] = Key::ENTER; mapKeys[XK_Pause] = Key::PAUSE;
                    mapKeys[XK_Scroll_Lock] = Key::SCROLL; mapKeys[XK_Tab] = Key::TAB; mapKeys[XK_Delete] = Key::DEL; mapKeys[XK_Home] = Key::HOME;
                    mapKeys[XK_End] = Key::END; mapKeys[XK_Page_Up] = Key::PGUP; mapKeys[XK_Page_Down] = Key::PGDN; mapKeys[XK_Insert] = Key::INS;
                    mapKeys[XK_Shift_L] = Key::SHIFT; mapKeys[XK_Shift_R] = Key::SHIFT; mapKeys[XK_Control_L] = Key::CTRL; mapKeys[XK_Control_R] = Key::CTRL;
                    mapKeys[XK_space] = Key::SPACE; mapKeys[XK_period] = Key::PERIOD;
                    
                    mapKeys[XK_0] = Key::K0; mapKeys[XK_1] = Key::K1; mapKeys[XK_2] = Key::K2; mapKeys[XK_3] = Key::K3; mapKeys[XK_4] = Key::K4;
                    mapKeys[XK_5] = Key::K5; mapKeys[XK_6] = Key::K6; mapKeys[XK_7] = Key::K7; mapKeys[XK_8] = Key::K8; mapKeys[XK_9] = Key::K9;
                    
                    mapKeys[XK_KP_0] = Key::NP0; mapKeys[XK_KP_1] = Key::NP1; mapKeys[XK_KP_2] = Key::NP2; mapKeys[XK_KP_3] = Key::NP3; mapKeys[XK_KP_4] = Key::NP4;
                    mapKeys[XK_KP_5] = Key::NP5; mapKeys[XK_KP_6] = Key::NP6; mapKeys[XK_KP_7] = Key::NP7; mapKeys[XK_KP_8] = Key::NP8; mapKeys[XK_KP_9] = Key::NP9;
                    mapKeys[XK_KP_Multiply] = Key::NP_MUL; mapKeys[XK_KP_Add] = Key::NP_ADD; mapKeys[XK_KP_Divide] = Key::NP_DIV; mapKeys[XK_KP_Subtract] = Key::NP_SUB; mapKeys[XK_KP_Decimal] = Key::NP_DECIMAL;
                    
                    return koi::OK;
                }
                
                virtual koi::rcode SetWindowTitle(const std::string& s) override {
                    X11::XStoreName(koi_Display, koi_Window, s.c_str());
                    return koi::OK;
                }
                
                virtual koi::rcode StartSystemEventLoop() override { return koi::OK; }
                
                virtual koi::rcode HandleSystemEvent() override {
                    using namespace X11;
                    // Handle Xlib Message Loop - we do this in the
                    // same thread that OpenGL was created so we dont
                    // need to worry too much about multithreading with X11
                    XEvent xev;
                    while (XPending(koi_Display)) {
                        XNextEvent(koi_Display, &xev);
                        if (xev.type == Expose) {
                            XWindowAttributes gwa;
                            XGetWindowAttributes(koi_Display, koi_Window, &gwa);
                            ptrPGE->koi_UpdateWindowSize(gwa.width, gwa.height);
                        } else if (xev.type == ConfigureNotify) {
                            XConfigureEvent xce = xev.xconfigure;
                            ptrPGE->koi_UpdateWindowSize(xce.width, xce.height);
                        } else if (xev.type == KeyPress) {
                            KeySym sym = XLookupKeysym(&xev.xkey, 0);
                            ptrPGE->koi_UpdateKeyState(mapKeys[sym], true);
                            XKeyEvent* e = (XKeyEvent*)&xev; // Because DragonEye loves numpads
                            XLookupString(e, NULL, 0, &sym, NULL);
                            ptrPGE->koi_UpdateKeyState(mapKeys[sym], true);
                        } else if (xev.type == KeyRelease) {
                            KeySym sym = XLookupKeysym(&xev.xkey, 0);
                            ptrPGE->koi_UpdateKeyState(mapKeys[sym], false);
                            XKeyEvent* e = (XKeyEvent*)&xev;
                            XLookupString(e, NULL, 0, &sym, NULL);
                            ptrPGE->koi_UpdateKeyState(mapKeys[sym], false);
                        } else if (xev.type == ButtonPress) {
                            switch (xev.xbutton.button) {
                                case 1: ptrPGE->koi_UpdateMouseState(0, true); break;
                                case 2: ptrPGE->koi_UpdateMouseState(2, true); break;
                                case 3: ptrPGE->koi_UpdateMouseState(1, true); break;
                                case 4: ptrPGE->koi_UpdateMouseWheel(120); break;
                                case 5: ptrPGE->koi_UpdateMouseWheel(-120); break;
                                default: break;
                            }
                        } else if (xev.type == ButtonRelease) {
                            switch (xev.xbutton.button) {
                                case 1: ptrPGE->koi_UpdateMouseState(0, false); break;
                                case 2: ptrPGE->koi_UpdateMouseState(2, false); break;
                                case 3: ptrPGE->koi_UpdateMouseState(1, false); break;
                                default: break;
                            }
                        } else if (xev.type == MotionNotify) {
                            ptrPGE->koi_UpdateMouse(xev.xmotion.x, xev.xmotion.y);
                        } else if (xev.type == FocusIn) {
                            ptrPGE->koi_UpdateKeyFocus(true);
                        } else if (xev.type == FocusOut) {
                            ptrPGE->koi_UpdateKeyFocus(false);
                        } else if (xev.type == ClientMessage) {
                            ptrPGE->koi_Terminate();
                        }
                    }
                    return koi::OK;
                }
            };
        }
    #endif
    // +------------------------------------------------------------------------------+
    // | END PLATFORM: LINUX                                                          |
    // +------------------------------------------------------------------------------+

#endif /* LinuxPlatform_h */
