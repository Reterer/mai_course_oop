/*
  ������������ ������: 3
  �������: 21
  ������: �8�-206�-19
  �����: ������� ���� ����������

  �������:
	����������� ������ ���  �����, 5-��������� � 6-���������, 
	������ ������ ������������� �� �������� ������ Figure. 
	������ �������� �������� ��������. ��� ������ ������ ������������ ����� ����� �������: 
		���������� ��������������� ������ ������;
		����� � ����������� ����� ������ std::cout ��������� ������ ������; 
		���������� ������� ������.
	������� ���������, ������� ���������:
		������� �� ������������ ����� std::cin ������;
		��������� ��������� ������ � ������������ ������ std::vector<Figure*>;
		�������� ��� ����� ������� ����� ������� (1-3 ��. ����).
		�.�. ������������� ��� ������ ������ � ������� �������������� �����, 
		���������� ������ � �������;
	���������� ����� ��������� ����� ������� ����� � �������;
	������� �� ������� ������ �� �������.

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
		"�������:\n"
		"    help        -- ������� ���� �����\n"
		"    exit        -- ��������� ������ ���������\n"
		"    print       -- ������� ������ ����� (��������� �� ������)\n"
		"    calc        -- ��������� ����� ��������\n"
		"    remove <id> -- ������� ������� � �������� id\n" 
		"    add <type> <center> <vertex> -- ��������� ��������� ������\n"
		<< std::endl;
}

std::string getNameFigure(Figure* figure)
{
	if (Rhombus* p = dynamic_cast<Rhombus*>(figure))
		return "����";
	else if (Pentagon* p = dynamic_cast<Pentagon*>(figure))
		return "������������";
	else if (Hexagon* p = dynamic_cast<Hexagon*>(figure))
		return "�������������";
	else
		return "����������";
}

void print(const std::vector<Figure*>& figures)
{
	for (int i = 0; i < figures.size(); ++i)
	{
		std::cout << i << "\t - " << getNameFigure(figures[i])<< '\n';
		std::cout << "���������� ������: " << figures[i]->GetCenter() << '\n';
		figures[i]->PrintCords();
		std::cout << "�������: " << figures[i]->CalcArea() << "\n\n";
	}
}

void calc(const std::vector<Figure*>& figures)
{
	double sumOfAreas = 0;
	for (Figure* figure : figures)
	{
		sumOfAreas += figure->CalcArea();
	}
	std::cout << "����� ������� �����: " << sumOfAreas << std::endl;
}

void remove(std::vector<Figure*>& figures)
{
	int id;
	if (!(std::cin >> id))
	{
		std::cout << "������ �����." << std::endl;
		clear();
		return;
	}

	if (id < 0 || id >= figures.size())
	{
		std::cout << "������ �������� �� ����� ���� ������ ���� ��� ������ ������� ������� �����." << std::endl;
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
		std::cout << "������ ����� �����." << std::endl;
		clear();
		return;
	}

	Point center, vertex;
	if (!(std::cin >> center >> vertex) || center == vertex)
	{
		std::cout << "������ � ����� ��������� ������." << std::endl;
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
		std::cout << "������ � �������� ������." << std::endl;
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
			std::cout << "������� ����������� �������. ����� ������� �������, ������� \"help\"" << std::endl;
			clear();
		}

		std::cout << '>';
	}

	return 0;
}