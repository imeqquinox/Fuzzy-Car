#include "FuzzyLogic.h"

FuzzyLogic::FuzzyLogic()
{
	engine = nullptr;
	position = nullptr;
	velocity = nullptr;
	output = nullptr; 
}

FuzzyLogic::~FuzzyLogic()
{
}

void FuzzyLogic::Init()
{
	// Engine init 
	engine = new fl::Engine;
	engine->setName("LineFollow");
	engine->setDescription("");

	// Setup of the position of the line variable 
	position = new fl::InputVariable;
	position->setName("position");
	position->setDescription("");
	position->setEnabled(true);
	position->setRange(-320, 320);
	position->setLockValueInRange(true);
	position->addTerm(new fl::Gaussian("left", -300, 150));
	position->addTerm(new fl::Triangle("zero", -192, 0, 192));
	position->addTerm(new fl::Gaussian("right", 300, 150));
	engine->addInputVariable(position);

	// Setup of the velocity variable 
	velocity = new fl::InputVariable;
	velocity->setName("velocity");
	velocity->setDescription("");
	velocity->setEnabled(true);
	velocity->setRange(-1, 1);
	velocity->setLockValueInRange(true);
	velocity->addTerm(new fl::Gaussian("left", -0.75, 0.3));
	velocity->addTerm(new fl::Triangle("zero", -0.6, 0, 0.6));
	velocity->addTerm(new fl::Gaussian("right", 0.75, 0.3));
	engine->addInputVariable(velocity);
	
	// Setup the output (steering) variables 
	output = new fl::OutputVariable;
	output->setName("output");
	output->setDescription("");
	output->setEnabled(true);
	output->setRange(-1, 1);
	output->setLockValueInRange(true);
	output->setAggregation(new fl::Maximum);
	output->setDefuzzifier(new fl::Centroid(100));
	output->setDefaultValue(fl::nan);
	output->setLockPreviousValue(false);
	output->addTerm(new fl::Gaussian("farRight", -1, 0.2123));
	output->addTerm(new fl::Gaussian("slightRight", -0.5, 0.2123));
	output->addTerm(new fl::Gaussian("zero", 0, 0.2123));
	output->addTerm(new fl::Gaussian("slightLeft", 0.5, 0.2123));
	output->addTerm(new fl::Gaussian("farLeft", 1, 0.2123));
	engine->addOutputVariable(output);

	// Setup of mamdani ruleblock 
	mamdani = new fl::RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new fl::Minimum);
	mamdani->setDisjunction(fl::null);
	mamdani->setImplication(new fl::AlgebraicProduct);
	mamdani->setActivation(new fl::General);

	// Rules used for fuzzy logic 
	mamdani->addRule(fl::Rule::parse("if position is left and velocity is left then output is farRight", engine));
	mamdani->addRule(fl::Rule::parse("if position is left and velocity is zero then output is slightRight", engine));
	mamdani->addRule(fl::Rule::parse("if position is left and velocity is right then output is zero", engine));

	mamdani->addRule(fl::Rule::parse("if position is zero and velocity is left then output is slightRight", engine));
	mamdani->addRule(fl::Rule::parse("if position is zero and velocity is zero then output is zero", engine));
	mamdani->addRule(fl::Rule::parse("if position is zero and velocity is right then output is slightLeft", engine));

	mamdani->addRule(fl::Rule::parse("if position is right and velocity is left then output is zero", engine));
	mamdani->addRule(fl::Rule::parse("if position is right and velocity is zero then output is slightLeft", engine));
	mamdani->addRule(fl::Rule::parse("if position is right and velocity is right then output is farLeft", engine));
	engine->addRuleBlock(mamdani);
}

// Fuzzy logic engine process function 
float FuzzyLogic::Process(float inPos, float inVel)
{
	position->setValue(inPos);
	velocity->setValue(inVel);

	engine->process();

	// Return output (steering) value
	return output->getValue();
}