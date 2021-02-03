//
//  Global.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Global_h
#define Global_h

    namespace koi {
        class KoiEngine;
        class Sprite;
        class Renderer;
        class Platform;
        
        // Pixel Game Engine Advanced Configuration
        constexpr uint8_t  nMouseButtons = 5;
        enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };
        
        // MARK: Constants
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
        
        
        // MARK: koi::HWButton
        // +------------------------------------------------------------------------------+
        // | koi::HWButton - Represents the state of a hardware button (mouse/key/joy)    |
        // +------------------------------------------------------------------------------+
        struct HWButton {
            bool bPressed = false;  // Set once during the frame the event occurs
            bool bReleased = false; // Set once during the frame the event occurs
            bool bHeld = false;   // Set true for all frames between pressed and released events
        };
        
        
        static std::unique_ptr<Renderer> renderer;
        static std::unique_ptr<Platform> platform;
        static std::map<size_t, uint8_t> mapKeys;
    }
#endif /* Global_h */
