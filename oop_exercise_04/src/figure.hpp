#pragma once

template <class T>
struct Rhombus {
	std::pair<T, T> center;
	std::pair<T, T> vertex;
};

template <class T>
struct Pentagon {
	std::pair<T, T> center;
	std::pair<T, T> vertex;
};

template <class T>
struct Hexagon {
	std::pair<T, T> center;
	std::pair<T, T> vertex;
};


// Векторное сложение
template <class T>
std::pair<T, T> operator + (const std::pair<T, T> a, const std::pair<T, T> b) {
	return { a.first + b.first, a.second + b.second };
}
// Векторное вычитание
template <class T>
std::pair<T, T> operator - (const std::pair<T, T> a, const std::pair<T, T> b) {
	return { a.first - b.first, a.second - b.second };
}
// Скалярное умножение векторов
template <class T>
T operator * (const std::pair<T, T> a, const std::pair<T, T> b) {
	return a.first * b.first + a.second * b.second;
}
// Умножение на скаляр
template <class T>
std::pair<T, T> operator * (const T a, const std::pair<T, T> b) {
	return { a * b.first, a * b.second };
}

const double PI = 3.141592653589793;
// Поворот вектора pair на угол angle
template <class T>
std::pair<T, T> rotate(std::pair<T, T> pair, const double angle) {
	std::pair<T, T> rotated;
	rotated.first = (T)(pair.first * std::cos(angle) - pair.second * std::sin(angle));
	rotated.second = (T)(pair.first * std::sin(angle) + pair.second * std::cos(angle));
	return rotated;
}

// Вывод координат точки
template <class T>
void print_pair(std::pair<T, T> p) {
	std::cout << '(' << p.first << " , " << p.second << ')';
}
// Вывод координат фигуры
template <int VERTEX_COUNT, class T>
void print_cords(const T center, const T vertex)
{
	const double ANGLE = 2 * PI / VERTEX_COUNT; // угол между двумя соседними вершинами и центром
	print_pair(vertex);

	T vec = vertex - center;
	for (int i = 2; i <= VERTEX_COUNT; ++i)
	{
		vec = rotate(vec, ANGLE);
		std::cout << ' ';
		print_pair(center + vec);
	}
}
template <class T>
void print_figure(Rhombus<T> value) {
	std::cout << "Координаты ромба: ";
	print_cords<4>(value.center, value.vertex);
	std::cout << std::endl;
}
template <class T>
void print_figure(Pentagon<T> value) {
	std::cout << "Координаты пятиугольника: ";
	print_cords<5>(value.center, value.vertex);
	std::cout << std::endl;
}
template <class T>
void print_figure(Hexagon<T> value) {
	std::cout << "Координаты шестиугольника: ";
	print_cords<6>(value.center, value.vertex);
	std::cout << std::endl;
}

// Вычисление площади фигуры
template <int VERTEX_COUNT, class T>
double calc_area(const T center, const T vertex)
{
	T vecRadius = vertex - center; // Вектор-радиус описанной окружности
	double sqRadius = vecRadius * vecRadius;	   // Квадрат радуиса описанной окружности
	return VERTEX_COUNT / 2. * sqRadius * std::sin(2 * PI / VERTEX_COUNT);
}
template <class T>
double calc_area(Rhombus<T> figure) {
	return calc_area<4>(figure.center, figure.vertex);
}
template <class T>
double calc_area(Pentagon<T> figure) {
	return calc_area<5>(figure.center, figure.vertex);
}
template <class T>
double calc_area(Hexagon<T> figure) {
	return calc_area<6>(figure.center, figure.vertex);
}
