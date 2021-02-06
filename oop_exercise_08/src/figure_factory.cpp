#include <string>
#include "figure_factory.hpp"

FigureInputMaker::FigureInputMaker(std::istream& in) : in{in} {}

Figure* FigureInputMaker::Make() {
	std::string figureType;
	Point center, vertex;
	if(!(in >> figureType >> center >> vertex))
		return nullptr;
	
	
	if(figureType == "r")
		return new Rhombus(center, vertex);
	if(figureType == "p")
		return new Pentagon(center, vertex);
	if(figureType == "h")
		return new Hexagon(center, vertex);

	return nullptr;
}

FigureLoadMaker::FigureLoadMaker(std::ifstream& ifs) : ifs{ ifs } {}
Figure* FigureLoadMaker::Make() {
	std::string figureType;
	Point center, vertex;
	
	{
		char type;
		bool success = true;
		success &= static_cast<bool>(ifs.read(&type, sizeof(type)));
		success &= static_cast<bool>(ifs.read(reinterpret_cast<char*>(&center), sizeof(center)));
		success &= static_cast<bool>(ifs.read(reinterpret_cast<char*>(&vertex), sizeof(vertex)));

		if (!success)
			return nullptr;

		figureType = type;
	}

	if (figureType == "r")
		return new Rhombus(center, vertex);
	if (figureType == "p")
		return new Pentagon(center, vertex);
	if (figureType == "h")
		return new Hexagon(center, vertex);

	return nullptr;
}
