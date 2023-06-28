#define OLC_PGE_APPLICATION

#include <random>
#include "olcPixelGameEngine.h"
#include "console.h"

class Simulator : public olc::PixelGameEngine
{
public:
	Simulator()
	{
		sAppName = "Elementary Cellular Automata";
	}

	bool OnUserCreate() override
	{
		console = new Console();
		ConsoleCaptureStdOut(true);
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		console->OpenConsole(this);
		
		return true;
	}

	bool OnConsoleCommand(const std::string& text) override
	{
		console->CheckInput(text);

		return true;
	}
	
private:
	Console* console;
};

int main()
{
	Simulator sim;
	if (sim.Construct(256, 200, 4, 4))
		sim.Start();

	return 0;
}