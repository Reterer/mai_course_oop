#pragma once
#include <iostream>

struct Point {
	double x;
	double y;

	Point rotate(double radians);

	friend bool operator== (const Point a, const Point b);
	friend bool operator!= (const Point a, const Point b);

	friend Point operator+ (const Point a, const Point b);
	friend Point operator- (const Point a, const Point b);

	friend double operator* (const Point a, const Point b);
	friend Point operator* (const Point a, double b);

	friend std::ostream& operator<< (std::ostream& out, const Point& p);
	friend std::istream& operator>> (std::istream& in, Point& p);
};

