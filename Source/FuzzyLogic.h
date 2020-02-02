#pragma once
#include <fl\Headers.h>

class FuzzyLogic
{
public:
	FuzzyLogic();
	~FuzzyLogic();

	void Init();
	float Process(float position, float velocity);

private: 
	// Fuzzylite Variables 
	fl::Engine* engine; 
	fl::InputVariable* position; 
	fl::InputVariable* velocity; 
	fl::OutputVariable* output; 
	fl::RuleBlock* mamdani; 
};

