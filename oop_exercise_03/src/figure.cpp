#include <stdexcept>
#include <iostream>
#include <cmath>
#include "figure.hpp"

const double PI = 3.141592653589793;

Figure::Figure(Point center, Point vertex)
{
	if (center == vertex)
		throw std::invalid_argument("center can be eq vertex");

	this->center = center;
	this->vertex = vertex;
}

Point Figure::GetCenter()
{
	return this->center;
}

template <int VERTEX_COUNT>
void _printCords(const Point center, const Point vertex)
{
	const double ANGLE = 2 * PI / VERTEX_COUNT; // угол между двумя соседними вершинами и центром
	std::cout << "Координаты: " << vertex;

	Point vec = vertex - center;
	for (int i = 2; i <= VERTEX_COUNT; ++i)
	{
		vec = vec.rotate(ANGLE);
		std::cout << ' ' << center + vec;
	}
	std::cout << std::endl;
}

template <int VERTEX_COUNT>
double _calcArea(const Point center, const Point vertex)
{
	Point vecRadius = vertex - center; // Вектор-радиус описанной окружности
	double sqRadius = vecRadius * vecRadius;	   // Квадрат радуиса описанной окружности
	return VERTEX_COUNT / 2. * sqRadius * std::sin(2 * PI / VERTEX_COUNT);
}

Rhombus::Rhombus(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Rhombus::PrintCords()
{
	_printCords<4>(center, vertex);
}

double Rhombus::CalcArea()
{
	Point vecDiag = this->center - this->vertex;
	return 2 * (vecDiag * vecDiag);
}


Pentagon::Pentagon(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Pentagon::PrintCords()
{
	_printCords<5>(center, vertex);
}

double Pentagon::CalcArea()
{
	return _calcArea<5>(center, vertex);
}


Hexagon::Hexagon(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Hexagon::PrintCords()
{
	_printCords<6>(center, vertex);
}

double Hexagon::CalcArea()
{
	return _calcArea<6>(center, vertex);
}