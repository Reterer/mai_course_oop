/*
  ������������ ������: 6
  �������: 25
  ������: �8�-206�-19
  �����: ������� ���� ����������

  ����������� ������� ������� �������� �������� �������. 
  ���������� ������� ������ �������� ��������� ��� ������ �������� ��� ������ ��� ��� ���������. 
  ������ ������ ����� ��������� ����. ������ �������� �������� ��������, �.�. ��������������� (����� �������� � ��������������).
  ��� �������� ��������� ����� ���������� ������������ ������  std::pair.

  ����������� ���������, � ������� ������� ����� �������� ��������� ������. ��������� �����
  � ������������ ������� ������� � ������� ������������ ��������� ������. 

  ������:
	�����������
  ��������� ������:
	������������ ������
  ���������:
    ������������ ������
*/
#include <iostream>
#include <algorithm>
#include "vector.hpp"
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
		"    erase <id> -- ������� ������� � �������� id\n"
		"    insert <id> <center> <vertex> -- ��������� ����������� �� ������� � ������� id\n"
		<< std::endl;
}

template<class T, class Alloc>
void print(Vector<T, Alloc>& figures) {
	std::for_each(figures.begin(), figures.end(), [](T& val) { 
		std::cout << val;
	});
}

template<class T, class Alloc>
void erase(Vector<T, Alloc>& vec) {
	int del_element_idx;
	if (!(std::cin >> del_element_idx) || del_element_idx < 0 || del_element_idx >= vec.size()) {
		std::cout << "������� ����������� �����.\n";
		clear();
		return;
	}

	vec.erase(vec.iterator_by_index(del_element_idx));
}

template<class T, class Alloc>
void insert(Vector<T, Alloc>& vec) {
	int new_element_index;
	if (!(std::cin >> new_element_index) || new_element_index < 0 || new_element_index > vec.size()) {
		std::cout << "������� ����������� �����.\n";
		clear();
		return;
	}
	
	T new_el;
	if (!(std::cin >> new_el))
	{
		std::cout << "������� ����������� ����������.\n";
		clear(); 
		return;
	}

	try {
		vec.insert(vec.iterator_by_index(new_element_index), new_el);
	}
	catch (std::bad_alloc&) {
		std::cout << "� ��������� ��������� �� ����� �������� ������ ������\n";
	}
}

#include "allocator.hpp"
int main() {
	setlocale(LC_ALL, "russian");
	Vector<Triangle<int>, Allocator<Triangle<int>, 10>> figures;
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
		else if (cmd == "erase")
			erase(figures);
		else if (cmd == "insert")
			insert(figures);
		else
		{
			std::cout << "������� ����������� �������. ����� ������� �������, ������� \"help\"" << std::endl;
			clear();
		}

		std::cout << '>';
	}
	
	return 0;
}