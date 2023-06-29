#define OLC_PGE_APPLICATION

#include <random>
#include "olcPixelGameEngine.h"
#include "console.h"
#include "automaton.h"

class Simulator : public olc::PixelGameEngine
{
public:
	Simulator()
	{
		sAppName = "Elementary Cellular Automata";
	}

	bool OnUserCreate() override
	{
		automaton = new Automaton(this, ScreenHeight());
		console = new Console(this, automaton);
		ConsoleCaptureStdOut(true);
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		console->OpenConsole();
		automaton->Run();
		
		return true;
	}

	bool OnConsoleCommand(const std::string& text) override
	{
		console->CheckInput(text);

		return true;
	}
	
private:
	Console* console;
	Automaton* automaton;
};

int main()
{
	Simulator sim;
	if (sim.Construct(256, 200, 4, 4))
		sim.Start();

	return 0;
}