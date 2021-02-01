#define KOI_PGE_APPLICATION
#include "koiPixelGameEngine.h"

class Example : public koi::PixelGameEngine {
public:
    Example() {
        sAppName = "Example";
    }

public:
    bool OnUserCreate() override {
        // Called once at the start, so create things here
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(koi::BLACK);
        // called once per frame
        for (int x = 0; x < ScreenWidth(); x++) {
            for (int y = 0; y < ScreenHeight(); y++) {
                if (GetMouseX() == x && GetMouseY() == y) {
                    Draw(x, y, koi::WHITE);
                } else {
                    Draw(x, y, koi::Pixel(rand() % 255, rand() % 255, rand()% 255));
                }
            }
        }
        return true;
    }
};


int main(int argc, char const *argv[]) {
	Example demo;
	if (demo.Construct(15, 10, 32, 32))
		demo.Start();

	return 0;
}
