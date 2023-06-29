#include "automaton.h"

struct Automaton::Private
{
    static bool GetNextState(bool left, bool center, bool right, unsigned int rule) 
    {
        unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
        return (rule >> ruleIndex) & 1;
    }

    static void DrawGeneration(olc::PixelGameEngine* pge, const std::bitset<256>& generation, unsigned int row)
    {
        for (int i = 0; i < 256; ++i) 
        {
            if (generation.test(i)) 
            {
                pge->Draw(i, row, olc::WHITE);
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

Automaton::Automaton(unsigned int screenHeight)
{
	numGenerations = screenHeight;
    currentGeneration.set(128, true);
    row = 0;
    rule = 73;
}

void Automaton::Run(olc::PixelGameEngine* pge)
{
    Private::DrawGeneration(pge, currentGeneration, row);
    Private::GenerateNextGeneration(currentGeneration, nextGeneration, numGenerations, rule);
    currentGeneration = nextGeneration;
    row++;
}
