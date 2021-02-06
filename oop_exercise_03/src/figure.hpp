#pragma once
#include "point.hpp"

class Figure {
public:
	Figure(Point center, Point vertex);
	Point GetCenter();

	virtual void PrintCords() = 0;
	virtual double CalcArea() = 0;

protected:
	Point center;
	Point vertex;
};

class Rhombus : public Figure {
public:
	Rhombus(Point center, Point vertex);
	virtual void PrintCords() override;
	virtual double CalcArea() override;
};

class Pentagon : public Figure {
public:
	Pentagon(Point center, Point vertex);
	virtual void PrintCords() override;
	virtual double CalcArea() override;
};

class Hexagon : public Figure {
public:
	Hexagon(Point center, Point vertex);
	virtual void PrintCords() override;
	virtual double CalcArea() override;
};