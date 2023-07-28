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
		Clear(olc::VERY_DARK_GREY);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		automaton->Run();
		CaptureShortcuts();
		return true;
	}

	bool OnConsoleCommand(const std::string& text) override
	{
		console->ParseInput(text);
		return true;
	}

	bool OnUserDestroy() override
	{
		delete automaton, console;
		return true;
	}

private:
	void CaptureShortcuts()
	{
		if (GetKey(olc::Key::TAB).bPressed)
			ConsoleShow(olc::Key::TAB, true);
		
		if (GetKey(olc::Key::CTRL).bPressed)
			automaton->ClearAndRun();
		
		if (GetKey(olc::Key::C).bPressed && !IsConsoleShowing())
			automaton->Clear();
	}

	Console* console;
	Automaton* automaton;
};

int main()
{
	Simulator sim;
	if (sim.Construct(500, 250, 3, 3 /*300, 150, 5, 5*/))
		sim.Start();

	return 0;
}