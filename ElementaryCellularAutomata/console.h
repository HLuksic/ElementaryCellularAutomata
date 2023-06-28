#pragma once

#include "olcPixelGameEngine.h"

class Console
{
public:
	void OpenConsole(olc::PixelGameEngine* pge);
	void CheckInput(const std::string& text);

private:
	struct Private;
	const std::string commands[5] = { "help", "reset", "setstate", "setrule", "start"};
};