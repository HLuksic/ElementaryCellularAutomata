#include "automaton.h"
#include <random>

namespace States
{
    enum State
    {
	    CENTER = 0,
	    LEFT = 1,
	    RIGHT = 2,
        RANDOM = 3
    };
}

Automaton::Automaton(olc::PixelGameEngine* pge)
{
    this->pge = pge;
    width = pge->ScreenWidth();
    currentGeneration.resize(width);
    nextGeneration.resize(width);
    currentGeneration[width / 2] = true;
    row = 0;
    rule = 30;
    run = false;
    state = 0;
    DrawCurrentGeneration();
}

void Automaton::Run()
{
    if (!run)
        return;

    DrawCurrentGeneration();
    GenerateNextGeneration();
    currentGeneration = nextGeneration;
    row++;

    if (row == pge->ScreenHeight())
        run = false;
}

void Automaton::GenerateNextGeneration()
{
    for (int i = 0; i < width; ++i)
    {
        // wraps around the edges of the simulation
        bool left = currentGeneration[(i + (width - 1)) % width];
        bool right = currentGeneration[(i + 1) % width];
        bool center = currentGeneration[i];
        
        nextGeneration[i] = GetNextState(left, center, right);
    }
}

bool Automaton::GetNextState(bool left, bool center, bool right)
{
    unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
    return (rule >> ruleIndex) & 1;
}

void Automaton::DrawCurrentGeneration()
{
    for (int i = 0; i < width; ++i)
        currentGeneration[i] ? pge->Draw(i, row, olc::DARK_GREY) : pge->Draw(i, row, olc::VERY_DARK_GREY);
}

unsigned int Automaton::GetRule()
{
    return rule;
}

unsigned int Automaton::GetWidth()
{
    return width;
}

void Automaton::SetRule(unsigned int rule)
{
    this->rule = rule;
    std::cout << "Rule set to " << rule << ".\n\n";
}

void Automaton::SetState(unsigned int state)
{
    this->state = state;
}

void Automaton::SetSpecificStartingState(unsigned int index)
{
    std::fill(currentGeneration.begin(), currentGeneration.end(), false);
    currentGeneration[index] = true;
    std::cout << "Cell alive at index " << index << ".\n\n";
}

void Automaton::SetRandomStartingState()
{
    srand(unsigned int(time(NULL)));
    
    for (auto cell : currentGeneration)
        cell = rand() % 2;
    
    std::cout << "State randomized.\n\n";
}

void Automaton::Reset()
{
    Clear();
    run = false;

    switch (state)
    {
    case States::CENTER:
    {
        SetSpecificStartingState(width / 2);
        break;
    }
    case States::LEFT:
    {
        SetSpecificStartingState(0);
        break;
    }
    case States::RIGHT:
    {
        SetSpecificStartingState(width - 1);
        break;
    }
    case States::RANDOM:
    {
        SetRandomStartingState();
        break;
    }
    }

    DrawCurrentGeneration();
}

void Automaton::ClearAndRun()
{
    Clear();
    run = true;
}

void Automaton::Clear()
{
    pge->Clear(olc::VERY_DARK_GREY);
    row = 0;
}