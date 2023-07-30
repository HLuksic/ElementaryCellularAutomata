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
		Clear(DEAD_COLOR);
		automaton = new Automaton(this);
		console = new Console(this, automaton);
		runAutomaton = false;
		ConsoleCaptureStdOut(true);
		srand(unsigned int(time(NULL)));
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (runAutomaton)
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
			runAutomaton = !runAutomaton;
		
		if (GetKey(olc::Key::R).bPressed && !IsConsoleShowing())
			automaton->Reset();
	}

	Console* console;
	Automaton* automaton;
	bool runAutomaton;
};

void CheckArguments(int argc)
{
	if (argc != 4 && argc != 1)
	{
		std::cout << "Provide 0 or 3 arguments!\n";
		exit(0);
	}
}

auto GetArguments(int argc, char* argv[])
{
	std::array<int, 3> args = { 500, 250, 3 };
	if (argc == 4)
		args = { atoi(argv[1]), atoi(argv[2]), atoi(argv[3]) };
	return args;
}

int main(int argc, char* argv[])
{
	CheckArguments(argc);
	auto args = GetArguments(argc, argv);
	Simulator sim;
	
	if (sim.Construct(args[0], args[1], args[2], args[2], false, true))
		sim.Start();
	else
		std::cout << "Invalid argument(s)!\n";

	return 0;
}