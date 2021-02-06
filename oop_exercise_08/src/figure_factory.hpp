#pragma once
#include "figure.hpp"

class FigureMaker {
public:
	virtual Figure* Make() = 0;
};

class FigureInputMaker: public FigureMaker {
public:
	FigureInputMaker(std::istream& in);
	Figure* Make() override;
private:
	std::istream& in;
};

class FigureLoadMaker : public FigureMaker {
public:
	FigureLoadMaker(std::ifstream& ifs);
	Figure* Make() override;
private:
	std::istream& ifs;
};