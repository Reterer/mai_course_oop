#include "point.hpp"

bool operator== (const Point a, const Point b)
{
	return a.x == b.x && a.y == b.y;
}
bool operator!= (const Point a, const Point b)
{
	return a.x != b.x || a.y != b.y;
}

Point operator+ (const Point a, const Point b)
{
	return { a.x + b.x, a.y + b.y };
}

Point operator- (const Point a, const Point b)
{
	return { a.x - b.x, a.y - b.y };
}

double operator*(const Point a, const Point b)
{
	return a.x * b.x + a.y * b.y;
}

Point operator*(const Point a, double b)
{
	return Point{ a.x * b, a.y * b };
}

std::istream& operator>>(std::istream& in, Point& p)
{
	double x, y;
	in >> x >> y;
	p = Point{ x, y };
	return in;
}

std::ostream& operator<< (std::ostream& out, const Point& p)
{
	out << '(' << p.x << ',' << p.y << ')';
	return out;
}

Point Point::rotate(double radians) {
	Point rotated;
	rotated.x = x * std::cos(radians) - y * std::sin(radians);
	rotated.y = x * std::sin(radians) + y * std::cos(radians);
	return rotated;
}
