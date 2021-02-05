#define KOI_ENGINE_APPLICATION
#include "ProjectKoi.h"

class Example : public koi::KoiEngine {
public:
    Example() {
        sAppName = "Example";
    }

public:
    bool OnUserCreate() override {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override {
        Clear(koi::Color::BLACK);
        
        for (int x = 0; x < ScreenWidth(); x++) {
            for (int y = 0; y < ScreenHeight(); y++) {
                if (GetMouseX() == x && GetMouseY() == y) {
                    Draw(x, y, koi::Color::WHITE);
                } else {
                    Draw(x, y, koi::Color(rand() % 255, rand() % 255, rand()% 255));
                }
            }
        }
        FillTriangle(10, 10, 40, 40, 50, 10, koi::Color(255, 128, 0));
        DrawLine({10, 10}, {300, 300});
        return true;
    }
};


int main(int argc, char const *argv[]) {
	Example demo;
	if (demo.Construct(600, 400, 1, 1))
		demo.Start();

	return 0;
}
