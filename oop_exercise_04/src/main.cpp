/*
  Лабораторная работа: 4
  Вариант: 21
  Группа: М8О-206Б-19
  Автор: Суханов Егор Алексеевич

  Задание:
	Разработать шаблоны классов согласно варианту задания. 
	Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. 
	Классы должны иметь только публичные поля. В классах не должно быть методов, только поля.
	Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. 
	Для хранения координат фигур необходимо использовать шаблон  std::pair.
	Реализовать шаблонную функцию print и square.
	Реализовать ввод фигур.
*/
#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include "figure.hpp"

void clear()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Вычисляет сумму площадей фигур
template <class T, size_t index = 0>
double square(T value) {
	if constexpr (index < std::tuple_size<T>::value) {
		return calc_area(std::get<index>(value)) + square<T, index + 1>(value);
	}
	else {
		return 0;
	}
}

// Выводит кортеж фигур
template <class T, size_t index = 0>
void print_tuple(T value) {
	if constexpr (index < std::tuple_size<T>::value) {
		print_figure(std::get<index>(value));
		print_tuple<T, index + 1>(value);
	}
	else {
		std::cout << std::endl;
	}
}

// Устанавливает координаты данной фигуры
template <class T>
void set_figure(T& figure) {
	if (! (std::cin >> figure.center.first >> figure.center.second
		>> figure.vertex.first >> figure.vertex.second)) {
		std::cout << "Координаты введены неверно." << std::endl;
		clear();
	}
	if (figure.center.first == figure.vertex.first
		&& figure.center.second == figure.vertex.second) {
		std::cout << "Центр и вершина совпадают." << std::endl;
		figure.center = {};
		figure.vertex = {};
		clear();
	}
}
// Устанавливает координаты i-й фигуры в кортеже value
template <class T, size_t index = 0>
void set(T& value, size_t i) {
	if constexpr (index < std::tuple_size<T>::value) {
		if (i == index) {
			set_figure(std::get<index>(value));
		}
		else {
			set<T, index + 1>(value, i);
		}
	}
	else {
		return;
	}
}

// Обрабатывает команду "set" -- установить координаты какой то фигуры
template <class T>
void set(T& value){
	size_t index;
	if (std::cin >> index && index < std::tuple_size<T>::value) {
		set(value, index);
	}
	else {
		std::cout << "Введен неверный индекс кортежа." << std::endl;
		clear();
	}
}

// Выводит справку об использовании программы
void help() {
	std::cout << 
		"help   -- выводит этот текст\n"
		"exit   -- выход из программы\n"
		"set <id> <center> <vertex> -- устанавливает координаты для фигуры под номером id\n"
		"print -- выводит координаты фигур\n"
		"square -- вычисляет общую площадь\n"
		<< std::endl;
}

int main() {
	setlocale(LC_ALL, "russian");
	std::tuple< Rhombus<double>, Pentagon<double>, Hexagon<double>> tuple;
	
	std::string cmd;
	while (std::cout << '>', std::cin >> cmd) {
		if (cmd == "exit")
			break;
		else if (cmd == "help")
			help();
		else if (cmd == "set")
			set(tuple);
		else if (cmd == "print")
			print_tuple(tuple);
		else if (cmd == "square")
			std::cout << "Сумма площадей фигур: " << square(tuple) << std::endl;
		else {
			std::cout << "Такой команды не существует." << std::endl;
			clear();
		}
	}

	return 0;
}