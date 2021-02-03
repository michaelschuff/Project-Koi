//
//  Renderer.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Renderer_h
#define Renderer_h
    #include "Global.h"
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
    

#endif /* Renderer_h */
