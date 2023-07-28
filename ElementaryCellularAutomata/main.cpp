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
	if (argc == 4)
		return std::array<int, 3>{ atoi(argv[1]), atoi(argv[2]), atoi(argv[3]) };

	return std::array<int, 3>{ 500, 250, 3 };
}

int main(int argc, char* argv[])
{
	CheckArguments(argc);
	auto args = GetArguments(argc, argv);
	
	Simulator sim;
	if (sim.Construct(args[0], args[1], args[2], args[2]))
		sim.Start();
	else
		std::cout << "Invalid arguments!\n";

	return 0;
}