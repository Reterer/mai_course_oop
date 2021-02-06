/*
  Лабораторная работа: 3
  Вариант: 21
  Группа: М8О-206Б-19
  Автор: Суханов Егор Алексеевич

  Задание:
	Разработать классы для  ромба, 5-угольника и 6-угольника, 
	классы должны наследоваться от базового класса Figure. 
	Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов: 
		Вычисление геометрического центра фигуры;
		Вывод в стандартный поток вывода std::cout координат вершин фигуры; 
		Вычисление площади фигуры.
	Создать программу, которая позволяет:
		Вводить из стандартного ввода std::cin фигуры;
		Сохранять созданные фигуры в динамический массив std::vector<Figure*>;
		Вызывать для всего массива общие функции (1-3 см. выше).
		Т.е. распечатывать для каждой фигуры в массиве геометрический центр, 
		координаты вершин и площадь;
	Необходимо уметь вычислять общую площадь фигур в массиве;
	Удалять из массива фигуру по индексу.

*/
#include <iostream>
#include <vector>
#include <string>
#include "figure.hpp"

void clear()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void help() 
{
	std::cout <<
		"команды:\n"
		"    help        -- выводит этот текст\n"
		"    exit        -- завершает работу программы\n"
		"    print       -- выводит вектор фигур (выполняет их методы)\n"
		"    calc        -- вычисляет сумму площадей\n"
		"    remove <id> -- удаляет элемент с индексом id\n" 
		"    add <type> <center> <vertex> -- добавляет указанную фигуру\n"
		<< std::endl;
}

std::string getNameFigure(Figure* figure)
{
	if (Rhombus* p = dynamic_cast<Rhombus*>(figure))
		return "ромб";
	else if (Pentagon* p = dynamic_cast<Pentagon*>(figure))
		return "пятиугольник";
	else if (Hexagon* p = dynamic_cast<Hexagon*>(figure))
		return "шестиугольник";
	else
		return "неизвестно";
}

void print(const std::vector<Figure*>& figures)
{
	for (int i = 0; i < figures.size(); ++i)
	{
		std::cout << i << "\t - " << getNameFigure(figures[i])<< '\n';
		std::cout << "Координаты центра: " << figures[i]->GetCenter() << '\n';
		figures[i]->PrintCords();
		std::cout << "Площадь: " << figures[i]->CalcArea() << "\n\n";
	}
}

void calc(const std::vector<Figure*>& figures)
{
	double sumOfAreas = 0;
	for (Figure* figure : figures)
	{
		sumOfAreas += figure->CalcArea();
	}
	std::cout << "Общая площадь фигур: " << sumOfAreas << std::endl;
}

void remove(std::vector<Figure*>& figures)
{
	int id;
	if (!(std::cin >> id))
	{
		std::cout << "Ошибка ввода." << std::endl;
		clear();
		return;
	}

	if (id < 0 || id >= figures.size())
	{
		std::cout << "индекс элемента не может быть меньше нуля или больше размера вектора фигур." << std::endl;
		return;
	}
	delete figures[id];
	figures.erase(figures.begin() + id);
}

void add(std::vector<Figure*>& figures)
{
	std::string name;
	if (!(std::cin >> name))
	{
		std::cout << "Ошибка ввода имени." << std::endl;
		clear();
		return;
	}

	Point center, vertex;
	if (!(std::cin >> center >> vertex) || center == vertex)
	{
		std::cout << "Ошибка в вводе координат фигуры." << std::endl;
		clear();
		return;
	}

	Figure* figure;
	if (name == "r")
		figure = new Rhombus(center, vertex);
	else if (name == "p")
		figure = new Pentagon(center, vertex);
	else if (name == "h")
		figure = new Hexagon(center, vertex);
	else
	{
		std::cout << "Ошибка в названии фигуры." << std::endl;
		clear();
		return;
	}
	
	figures.push_back(figure);
}

int main() 
{
	setlocale(LC_ALL, "russian");
	std::vector<Figure*> figures(0);
	
	std::string cmd;
	std::cout << '>';
	while (std::cin >> cmd) 
	{
		if (cmd == "help")
			help();
		else if (cmd == "exit")
			break;
		else if (cmd == "print")
			print(figures);
		else if (cmd == "calc")
			calc(figures);
		else if (cmd == "remove")
			remove(figures);
		else if (cmd == "add")
			add(figures);
		else
		{
			std::cout << "Введена неизвестная команда. Чтобы вывести справку, введите \"help\"" << std::endl;
			clear();
		}

		std::cout << '>';
	}

	return 0;
}