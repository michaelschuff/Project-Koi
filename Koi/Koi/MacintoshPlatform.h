//
//  MacintoshPlatform.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef MacintoshPlatform_h
#define MacintoshPlatform_h

    #include "Global.h"
    #include "Platform.h"
    // MARK: MAC
    // +------------------------------------------------------------------------------+
    // | START PLATFORM: GLUT (used to make it simple for Apple)                      |
    // +------------------------------------------------------------------------------+
    //
    #if defined(__APPLE__)
        namespace koi {
            class Platform_GLUT : public koi::Platform {
            public:
                static std::atomic<bool>* bActiveRef;
                virtual koi::rcode ApplicationStartUp() override {return koi::rcode::OK;}
                virtual koi::rcode ApplicationCleanUp() override { return koi::rcode::OK; }
                virtual koi::rcode ThreadStartUp() override { return koi::rcode::OK; }
                
                virtual koi::rcode ThreadCleanUp() override {
                    renderer->DestroyDevice();
                    return koi::OK;
                }
                
                virtual koi::rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const koi::Vector2i& vViewPos, const koi::Vector2i& vViewSize) override {
                    if (renderer->CreateDevice({}, bFullScreen, bEnableVSYNC) == koi::rcode::OK) {
                        renderer->UpdateViewport(vViewPos, vViewSize);
                        return koi::rcode::OK;
                    } else {
                        return koi::rcode::FAIL;
                    }
                }
                
                static void ExitMainLoop() {
                    if (!ptrPGE->OnUserDestroy()) {
                        *bActiveRef = true;
                        return;
                    }
                    platform->ThreadCleanUp();
                    platform->ApplicationCleanUp();
                    exit(0);
                }
                
                static void ThreadFunct() {
                    if (!*bActiveRef) {
                        ExitMainLoop();
                        return;
                    }
                    glutPostRedisplay();
                }
                
                static void DrawFunct() {
                    ptrPGE->koi_CoreUpdate();
                }
                
                virtual koi::rcode CreateWindowPane(const koi::Vector2i& vWindowPos, koi::Vector2i& vWindowSize, bool bFullScreen) override {
                    renderer->PrepareDevice();
                    
                    
                    if (bFullScreen) {
                        vWindowSize.x = glutGet(GLUT_SCREEN_WIDTH);
                        vWindowSize.y = glutGet(GLUT_SCREEN_HEIGHT);
                        glutFullScreen();
                    }
                    
                    if (vWindowSize.x > glutGet(GLUT_SCREEN_WIDTH) || vWindowSize.y > glutGet(GLUT_SCREEN_HEIGHT)) {
                        perror("ERROR: The specified window dimensions do not fit on your screen\n");
                        return koi::FAIL;
                    }
                    
                    // Create Keyboard Mapping
                    mapKeys[0x00] = Key::NONE;
                    mapKeys['A'] = Key::A; mapKeys['B'] = Key::B; mapKeys['C'] = Key::C; mapKeys['D'] = Key::D; mapKeys['E'] = Key::E;
                    mapKeys['F'] = Key::F; mapKeys['G'] = Key::G; mapKeys['H'] = Key::H; mapKeys['I'] = Key::I; mapKeys['J'] = Key::J;
                    mapKeys['K'] = Key::K; mapKeys['L'] = Key::L; mapKeys['M'] = Key::M; mapKeys['N'] = Key::N; mapKeys['O'] = Key::O;
                    mapKeys['P'] = Key::P; mapKeys['Q'] = Key::Q; mapKeys['R'] = Key::R; mapKeys['S'] = Key::S; mapKeys['T'] = Key::T;
                    mapKeys['U'] = Key::U; mapKeys['V'] = Key::V; mapKeys['W'] = Key::W; mapKeys['X'] = Key::X; mapKeys['Y'] = Key::Y;
                    mapKeys['Z'] = Key::Z;
                    
                    mapKeys[GLUT_KEY_F1] = Key::F1; mapKeys[GLUT_KEY_F2] = Key::F2; mapKeys[GLUT_KEY_F3] = Key::F3; mapKeys[GLUT_KEY_F4] = Key::F4;
                    mapKeys[GLUT_KEY_F5] = Key::F5; mapKeys[GLUT_KEY_F6] = Key::F6; mapKeys[GLUT_KEY_F7] = Key::F7; mapKeys[GLUT_KEY_F8] = Key::F8;
                    mapKeys[GLUT_KEY_F9] = Key::F9; mapKeys[GLUT_KEY_F10] = Key::F10; mapKeys[GLUT_KEY_F11] = Key::F11; mapKeys[GLUT_KEY_F12] = Key::F12;
                    
                    mapKeys[GLUT_KEY_DOWN] = Key::DOWN; mapKeys[GLUT_KEY_LEFT] = Key::LEFT; mapKeys[GLUT_KEY_RIGHT] = Key::RIGHT; mapKeys[GLUT_KEY_UP] = Key::UP;
                    mapKeys[13] = Key::ENTER;
                    
                    mapKeys[127] = Key::BACK; mapKeys[27] = Key::ESCAPE;
                    mapKeys[9] = Key::TAB;  mapKeys[GLUT_KEY_HOME] = Key::HOME;
                    mapKeys[GLUT_KEY_END] = Key::END; mapKeys[GLUT_KEY_PAGE_UP] = Key::PGUP; mapKeys[GLUT_KEY_PAGE_DOWN] = Key::PGDN;    mapKeys[GLUT_KEY_INSERT] = Key::INS;
                    mapKeys[32] = Key::SPACE; mapKeys[46] = Key::PERIOD;
                    
                    mapKeys[48] = Key::K0; mapKeys[49] = Key::K1; mapKeys[50] = Key::K2; mapKeys[51] = Key::K3; mapKeys[52] = Key::K4;
                    mapKeys[53] = Key::K5; mapKeys[54] = Key::K6; mapKeys[55] = Key::K7; mapKeys[56] = Key::K8; mapKeys[57] = Key::K9;
                    
                    glutKeyboardFunc([](unsigned char key, int x, int y) -> void {
                        switch (glutGetModifiers()) {
                            case 0: //This is when there are no modifiers
                                if ('a' <= key && key <= 'z') key -= 32;
                                break;
                            case GLUT_ACTIVE_SHIFT:
                                ptrPGE->koi_UpdateKeyState(Key::SHIFT, true);
                                break;
                            case GLUT_ACTIVE_CTRL:
                                if ('a' <= key && key <= 'z') key -= 32;
                                ptrPGE->koi_UpdateKeyState(Key::CTRL, true);
                                break;
                            case GLUT_ACTIVE_ALT:
                                if ('a' <= key && key <= 'z') key -= 32;
                                break;
                        }
                        
                        if (mapKeys[key])
                            ptrPGE->koi_UpdateKeyState(mapKeys[key], true);
                    });
                    
                    glutKeyboardUpFunc([](unsigned char key, int x, int y) -> void {
                        switch (glutGetModifiers()) {
                            case 0: //This is when there are no modifiers
                                if ('a' <= key && key <= 'z') key -= 32;
                                break;
                            case GLUT_ACTIVE_SHIFT:
                                ptrPGE->koi_UpdateKeyState(Key::SHIFT, false);
                                break;
                            case GLUT_ACTIVE_CTRL:
                                if ('a' <= key && key <= 'z') key -= 32;
                                ptrPGE->koi_UpdateKeyState(Key::CTRL, false);
                                break;
                            case GLUT_ACTIVE_ALT:
                                if ('a' <= key && key <= 'z') key -= 32;
                                //No ALT in PGE
                                break;
                        }
                        
                        if (mapKeys[key])
                            ptrPGE->koi_UpdateKeyState(mapKeys[key], false);
                    });
                    
                    //Special keys
                    glutSpecialFunc([](int key, int x, int y) -> void {
                        if (mapKeys[key])
                            ptrPGE->koi_UpdateKeyState(mapKeys[key], true);
                    });
                    
                    glutSpecialUpFunc([](int key, int x, int y) -> void {
                        if (mapKeys[key])
                            ptrPGE->koi_UpdateKeyState(mapKeys[key], false);
                    });
                    
                    glutMouseFunc([](int button, int state, int x, int y) -> void {
                        switch (button) {
                            case GLUT_LEFT_BUTTON:
                                if (state == GLUT_UP) ptrPGE->koi_UpdateMouseState(0, false);
                                else if (state == GLUT_DOWN) ptrPGE->koi_UpdateMouseState(0, true);
                                break;
                            case GLUT_MIDDLE_BUTTON:
                                if (state == GLUT_UP) ptrPGE->koi_UpdateMouseState(2, false);
                                else if (state == GLUT_DOWN) ptrPGE->koi_UpdateMouseState(2, true);
                                break;
                            case GLUT_RIGHT_BUTTON:
                                if (state == GLUT_UP) ptrPGE->koi_UpdateMouseState(1, false);
                                else if (state == GLUT_DOWN) ptrPGE->koi_UpdateMouseState(1, true);
                                break;
                        }
                    });
                    
                    auto mouseMoveCall = [](int x, int y) -> void {
                        ptrPGE->koi_UpdateMouse(x, y);
                    };
                    
                    glutMotionFunc(mouseMoveCall);
                    glutPassiveMotionFunc(mouseMoveCall);
                    
                    glutEntryFunc([](int state) -> void {
                        if (state == GLUT_ENTERED) ptrPGE->koi_UpdateKeyFocus(true);
                        else if (state == GLUT_LEFT) ptrPGE->koi_UpdateKeyFocus(false);
                    });
                    
                    glutDisplayFunc(DrawFunct);
                    glutIdleFunc(ThreadFunct);
                    
                    return koi::OK;
                }
                
                virtual koi::rcode SetWindowTitle(const std::string& s) override {
                    glutSetWindowTitle(s.c_str());
                    return koi::OK;
                }
                
                virtual koi::rcode StartSystemEventLoop() override {
                    glutMainLoop();
                    return koi::OK;
                }
                
                virtual koi::rcode HandleSystemEvent() override {
                    return koi::OK;
                }
            };
            
            std::atomic<bool>* Platform_GLUT::bActiveRef{ nullptr };
            
            //Custom Start
            koi::rcode KoiEngine::Start() {
                if (platform->ApplicationStartUp() != koi::OK) return koi::FAIL;
                
                // Construct the window
                if (platform->CreateWindowPane({ 30,30 }, vWindowSize, bFullScreen) != koi::OK) return koi::FAIL;
                koi_UpdateWindowSize(vWindowSize.x, vWindowSize.y);
                
                
                if (platform->ThreadStartUp() == koi::FAIL)  return koi::FAIL;
                
                koi_PrepareEngine();
                
                if (!OnUserCreate()) return koi::FAIL;
                
                Platform_GLUT::bActiveRef = &bAtomActive;
                
                glutWMCloseFunc(Platform_GLUT::ExitMainLoop);
                
                bAtomActive = true;
                
                platform->StartSystemEventLoop();
                
                //This code will not even be run but why not
                if (platform->ApplicationCleanUp() != koi::OK) return koi::FAIL;
                
                return koi::OK;
            }
        }
    #endif
    // +------------------------------------------------------------------------------+
    // | END PLATFORM: GLUT                                                           |
    // +------------------------------------------------------------------------------+

#endif /* MacintoshPlatform_h */
