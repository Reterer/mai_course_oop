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
	std::cout << "координаты: " << vertex;

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

void Rhombus::Print()
{
	std::cout << "Ромб, ";
	_printCords<4>(center, vertex);
}

bool Rhombus::Save(std::ofstream& ofs)
{
	const char type = 'r';
	bool success = true;

	success &= static_cast<bool>(ofs.write(&type, sizeof(type)));
	success &= static_cast<bool>(ofs.write(reinterpret_cast<char*>(&center), sizeof(center)));
	success &= static_cast<bool>(ofs.write(reinterpret_cast<char*>(&vertex), sizeof(vertex)));
	return success;
}


Pentagon::Pentagon(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Pentagon::Print()
{
	std::cout << "Пятиугольник, ";
	_printCords<5>(center, vertex);
}

bool Pentagon::Save(std::ofstream& ofs)
{
	const char type = 'p';
	bool success = true;

	success &= static_cast<bool>(ofs.write(&type, sizeof(type)));
	success &= static_cast<bool>(ofs.write(reinterpret_cast<char*>(&center), sizeof(center)));
	success &= static_cast<bool>(ofs.write(reinterpret_cast<char*>(&vertex), sizeof(vertex)));
	return success;
}

Hexagon::Hexagon(Point center, Point vertex)
	: Figure(center, vertex)
{}

void Hexagon::Print()
{
	std::cout << "Шестиугольник, ";
	_printCords<6>(center, vertex);
}

bool Hexagon::Save(std::ofstream& ofs)
{
	const char type = 'h';
	bool success = true;

	success &= static_cast<bool>(ofs.write(&type, sizeof(type)));
	success &= static_cast<bool>(ofs.write(reinterpret_cast<char*>(&center), sizeof(center)));
	success &= static_cast<bool>(ofs.write(reinterpret_cast<char*>(&vertex), sizeof(vertex)));
	return success;
}