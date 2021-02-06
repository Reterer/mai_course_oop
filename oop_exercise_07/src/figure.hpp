#pragma once
#include <fstream>
#include "point.hpp"

class Figure {
public:
	Figure(Point center, Point vertex);
	Point GetCenter();
	virtual void Print() = 0;
	virtual bool Save(std::ofstream& ofs) = 0;

protected:
	Point center;
	Point vertex;
};

class Rhombus : public Figure {
public:
	Rhombus(Point center, Point vertex);
	virtual void Print() override;
	virtual bool Save(std::ofstream& ofs) override;
};

class Pentagon : public Figure {
public:
	Pentagon(Point center, Point vertex);
	virtual void Print() override;
	virtual bool Save(std::ofstream& ofs) override;

};

class Hexagon : public Figure {
public:
	Hexagon(Point center, Point vertex);
	virtual void Print() override;
	virtual bool Save(std::ofstream& ofs) override;
};
