#include "automaton.h"
#include <random>

bool Automaton::GetNextState(bool left, bool center, bool right, unsigned int rule) 
{
    unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
    return (rule >> ruleIndex) & 1;
}

void Automaton::DrawGeneration(Automaton* self, const std::bitset<SCREEN_WIDTH>& generation, unsigned int row)
{
    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        if (generation.test(i)) 
        {
            self->pge->Draw(i, row, olc::DARK_GREY);
        }
    }
}

void Automaton::GenerateNextGeneration(std::bitset<SCREEN_WIDTH>& currentGeneration, std::bitset<SCREEN_WIDTH>& nextGeneration, unsigned int numGenerations, unsigned int rule)
{
    for (int i = 0; i < SCREEN_WIDTH; ++i)
    {
        bool left = currentGeneration[(i + (SCREEN_WIDTH - 1)) % SCREEN_WIDTH];
        bool center = currentGeneration[i];
        bool right = currentGeneration[(i + 1) % SCREEN_WIDTH];
        bool nextState = GetNextState(left, center, right, rule);

        nextGeneration.set(i, nextState);
    }
}

void Automaton::ShowNewInitialState(Automaton* self)
{
    self->pge->Clear(olc::BLACK);
    DrawGeneration(self, self->currentGeneration, self->row);
}

Automaton::Automaton(olc::PixelGameEngine* engine, unsigned int screenHeight)
{
    pge = engine;
	numGenerations = screenHeight;
    currentGeneration.set(SCREEN_WIDTH / 2, true);
    row = 0;
    rule = 30;
    run = false;
    DrawGeneration(this, currentGeneration, row);
}

void Automaton::Run()
{
    if (run)
    {
        DrawGeneration(this, currentGeneration, row);
        GenerateNextGeneration(currentGeneration, nextGeneration, numGenerations, rule);
        currentGeneration = nextGeneration;
        row++;
        
        if (row >= pge->ScreenHeight())
        {
            run = false;
        }
    }
}

void Automaton::SetRule(unsigned int rule)
{
    this->rule = rule;
}

void Automaton::SetSpecificStartingState(unsigned int index)
{
    currentGeneration = { false };
    currentGeneration.set(index, true);
    ShowNewInitialState(this);
}

void Automaton::SetRandomStartingState()
{
    srand(time(NULL));
    
	for (int i = 0; i < SCREEN_WIDTH; ++i)
	{
		currentGeneration.set(i, rand() % 2);
	}

    ShowNewInitialState(this);
}

void Automaton::Clear()
{
    pge->Clear(olc::BLACK);
    row = 0;
    DrawGeneration(this, currentGeneration, row);
}

void Automaton::ClearAndRun()
{
    run = true;
    Clear();
}

unsigned int Automaton::GetRule()
{
    return rule;
}
