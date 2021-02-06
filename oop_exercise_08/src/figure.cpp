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
void _printCords(std::ostream& out, const Point center, const Point vertex)
{
	const double ANGLE = 2 * PI / VERTEX_COUNT; // угол между двумя соседними вершинами и центром
	out << "координаты: " << vertex;

	Point vec = vertex - center;
	for (int i = 2; i <= VERTEX_COUNT; ++i)
	{
		vec = vec.rotate(ANGLE);
		out << ' ' << center + vec;
	}
	out << std::endl;
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

void Rhombus::Print(std::ostream& out)
{
	out << "Ромб, ";
	_printCords<4>(out, center, vertex);
}

Pentagon::Pentagon(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Pentagon::Print(std::ostream& out)
{
	out << "Пятиугольник, ";
	_printCords<5>(out, center, vertex);
}

Hexagon::Hexagon(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Hexagon::Print(std::ostream& out)
{
	out << "Шестиугольник, ";
	_printCords<6>(out, center, vertex);
}