#include "automaton.h"
#include <random>

Automaton::Automaton(olc::PixelGameEngine* engine, unsigned int screenHeight)
{
    pge = engine;
    width = pge->ScreenWidth();
    currentGeneration.resize(width);
    nextGeneration.resize(width);
    currentGeneration.at(width / 2) = true;
    row = 0;
    rule = 30;
    run = false;
    DrawGeneration(currentGeneration, row);
}

void Automaton::DrawGeneration(std::vector<bool>& generation, unsigned int row)
{
    for (int i = 0; i < width; ++i)
    {
        generation.at(i) ? pge->Draw(i, row, olc::DARK_GREEN) : pge->Draw(i, row, olc::VERY_DARK_GREEN);
    }
}

bool Automaton::GetNextState(bool left, bool center, bool right, unsigned int rule)
{
    unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
    return (rule >> ruleIndex) & 1;
}

void Automaton::GenerateNextGeneration(std::vector<bool>& currentGeneration, std::vector<bool>& nextGeneration, unsigned int rule)
{
    for (int i = 0; i < width; ++i)
    {
        // wraps around the edges of the simulation
        bool left = currentGeneration[(i + (width - 1)) % width];
        bool center = currentGeneration[i];
        bool right = currentGeneration[(i + 1) % width];
        bool nextState = GetNextState(left, center, right, rule);

        nextGeneration.at(i) = nextState;
    }
}

void Automaton::Run()
{
    if (run)
    {
        DrawGeneration(currentGeneration, row);
        GenerateNextGeneration(currentGeneration, nextGeneration, rule);
        currentGeneration = nextGeneration;
        row++;
        
        if (row >= unsigned int(pge->ScreenHeight()))
        {
            run = false;
        }
    }
}

unsigned int Automaton::GetRule()
{
    return rule;
}

void Automaton::SetRule(unsigned int rule)
{
    this->rule = rule;
}

void Automaton::SetSpecificStartingState(unsigned int index)
{
    std::fill(currentGeneration.begin(), currentGeneration.end(), 0);
    currentGeneration.at(index) = true;
    Clear();
}

void Automaton::SetRandomStartingState()
{
    srand(unsigned int(time(NULL)));
    
	for (int i = 0; i < width; ++i)
	{
		currentGeneration.at(i) = rand() % 2;
	}

    Clear();
}

void Automaton::Clear()
{
    pge->Clear(olc::BLACK);
    row = 0;
    run = false;
    DrawGeneration(currentGeneration, row);
}

void Automaton::ClearAndRun()
{
    Clear();
    run = true;
}
