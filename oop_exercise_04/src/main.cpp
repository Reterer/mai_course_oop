/*
  ������������ ������: 4
  �������: 21
  ������: �8�-206�-19
  �����: ������� ���� ����������

  �������:
	����������� ������� ������� �������� �������� �������. 
	���������� ������� ������ �������� ��������� ��� ������ �������� ��� ������ ��� ��� ���������. 
	������ ������ ����� ������ ��������� ����. � ������� �� ������ ���� �������, ������ ����.
	������ �������� �������� �������� (���������������), �� ����������� �������� � ��������������. 
	��� �������� ��������� ����� ���������� ������������ ������  std::pair.
	����������� ��������� ������� print � square.
	����������� ���� �����.
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

// ��������� ����� �������� �����
template <class T, size_t index = 0>
double square(T value) {
	if constexpr (index < std::tuple_size<T>::value) {
		return calc_area(std::get<index>(value)) + square<T, index + 1>(value);
	}
	else {
		return 0;
	}
}

// ������� ������ �����
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

// ������������� ���������� ������ ������
template <class T>
void set_figure(T& figure) {
	if (! (std::cin >> figure.center.first >> figure.center.second
		>> figure.vertex.first >> figure.vertex.second)) {
		std::cout << "���������� ������� �������." << std::endl;
		clear();
	}
	if (figure.center.first == figure.vertex.first
		&& figure.center.second == figure.vertex.second) {
		std::cout << "����� � ������� ���������." << std::endl;
		figure.center = {};
		figure.vertex = {};
		clear();
	}
}
// ������������� ���������� i-� ������ � ������� value
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

// ������������ ������� "set" -- ���������� ���������� ����� �� ������
template <class T>
void set(T& value){
	size_t index;
	if (std::cin >> index && index < std::tuple_size<T>::value) {
		set(value, index);
	}
	else {
		std::cout << "������ �������� ������ �������." << std::endl;
		clear();
	}
}

// ������� ������� �� ������������� ���������
void help() {
	std::cout << 
		"help   -- ������� ���� �����\n"
		"exit   -- ����� �� ���������\n"
		"set <id> <center> <vertex> -- ������������� ���������� ��� ������ ��� ������� id\n"
		"print -- ������� ���������� �����\n"
		"square -- ��������� ����� �������\n"
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
			std::cout << "����� �������� �����: " << square(tuple) << std::endl;
		else {
			std::cout << "����� ������� �� ����������." << std::endl;
			clear();
		}
	}

	return 0;
}