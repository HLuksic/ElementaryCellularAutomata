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
    DrawCurrentGeneration();
    row = 0;
    rule = 30;
    state = 0;
    wrap = false;
}

void Automaton::Run()
{
    GenerateNextGeneration();
    currentGeneration = nextGeneration;
    
    if (int(row) < pge->ScreenHeight() - 1)
        row++;
    else
        // draw screen sprite one pixel higher, new row at the bottom
        pge->DrawSprite(olc::vi2d(0, -1), pge->GetDrawTarget());

    DrawCurrentGeneration();
}

void Automaton::GenerateNextGeneration()
{
    for (unsigned int i = 0; i < width; ++i)
    {
        bool left, right, center;

        if (wrap)
        {
			left = currentGeneration[(i + (width - 1)) % width];
			right = currentGeneration[(i + 1) % width];
			center = currentGeneration[i];
		}
        else
        {
			left = !i ? false : currentGeneration[i - 1];
			right = i == width - 1 ? false : currentGeneration[i + 1];
			center = currentGeneration[i];
		}

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
    for (unsigned int i = 0; i < width; ++i)
        currentGeneration[i] ? pge->Draw(i, row, LIVE_COLOR) : pge->Draw(i, row, DEAD_COLOR);
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
}

void Automaton::SetState(unsigned int state)
{
    this->state = state;
}

void Automaton::ToggleWrap()
{
    wrap = !wrap;
    wrap ? std::cout << "Wrapping enabled\n\n" : std::cout << "Wrapping disabled\n\n";
}

void Automaton::SetSpecificStartingState(unsigned int index)
{
    std::fill(currentGeneration.begin(), currentGeneration.end(), false);
    currentGeneration[index] = true;
}

void Automaton::SetRandomStartingState()
{
    for (auto cell : currentGeneration)
        cell = rand() % 2;
}

void Automaton::Reset()
{
    pge->Clear(DEAD_COLOR);
    row = 0;
    
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
