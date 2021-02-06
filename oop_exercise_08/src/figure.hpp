#pragma once
#include <fstream>
#include "point.hpp"

class Figure {
public:
	Figure(Point center, Point vertex);
	Point GetCenter();
	virtual void Print(std::ostream& out) = 0;

protected:
	Point center;
	Point vertex;
};

class Rhombus : public Figure {
public:
	Rhombus(Point center, Point vertex);
	virtual void Print(std::ostream& out) override;
};

class Pentagon : public Figure {
public:
	Pentagon(Point center, Point vertex);
	virtual void Print(std::ostream& out) override;

};

class Hexagon : public Figure {
public:
	Hexagon(Point center, Point vertex);
	virtual void Print(std::ostream& out) override;
};
