#include "automaton.h"
#include <random>

struct Automaton::Private
{
    static bool GetNextState(bool left, bool center, bool right, unsigned int rule) 
    {
        unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
        return (rule >> ruleIndex) & 1;
    }

    static void DrawGeneration(Automaton* self, const std::bitset<256>& generation, unsigned int row)
    {
        for (int i = 0; i < 256; ++i) 
        {
            if (generation.test(i)) 
            {
                self->pge->Draw(i, row, olc::WHITE);
            }
        }
    }

    static void GenerateNextGeneration(std::bitset<256>& currentGeneration, std::bitset<256>& nextGeneration, unsigned int numGenerations, unsigned int rule)
    {
        for (int i = 0; i < 256; ++i)
        {
            bool left = currentGeneration[(i + 255) % 256];
            bool center = currentGeneration[i];
            bool right = currentGeneration[(i + 1) % 256];
            bool nextState = GetNextState(left, center, right, rule);

            nextGeneration.set(i, nextState);
        }
    }
};

Automaton::Automaton(olc::PixelGameEngine* engine, unsigned int screenHeight)
{
    pge = engine;
	numGenerations = screenHeight;
    currentGeneration.set(128, true);
    row = 0;
    rule = 30;
    Private::DrawGeneration(this, currentGeneration, row);
}

void Automaton::Run()
{
    if (row < pge->ScreenHeight())
    {
        Private::DrawGeneration(this, currentGeneration, row);
        Private::GenerateNextGeneration(currentGeneration, nextGeneration, numGenerations, rule);
        currentGeneration = nextGeneration;
        row++;
    }
}

void Automaton::SetRule(unsigned int rule)
{
    this->rule = rule;
}

void Automaton::SetSpecificStartingState(unsigned int index)
{
    currentGeneration = { false };
    nextGeneration = { false };
    currentGeneration.set(index, true);
}

void Automaton::SetRandomState()
{
    srand(time(NULL));
    
	for (int i = 0; i < 256; ++i)
	{
		currentGeneration.set(i, rand() % 2);
	}
}

void Automaton::Reset()
{
    pge->Clear(olc::BLACK);
    row = 0;
    Private::DrawGeneration(this, currentGeneration, row);
}

unsigned int Automaton::GetRule()
{
    return rule;
}
