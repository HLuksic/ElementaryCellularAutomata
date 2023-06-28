#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine.h"
#include <random>

class Simulator : public olc::PixelGameEngine
{
public:
	Simulator()
	{
		sAppName = "Elementary Cellular Automata";
	}

	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int i = 0; i < ScreenWidth(); i++)
		{
			for (int j = 0; j < ScreenHeight(); j++)
			{
				Draw(j, i, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
			}
		}
		
		return true;
	}
};

int main()
{
	Simulator sim;
	if (sim.Construct(256, 256, 4, 4))
		sim.Start();

	return 0;
}