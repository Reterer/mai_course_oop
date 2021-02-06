/*
  ������������ ������: 8
  �������: 21
  ������: �8�-206�-19
  �����: ������� ���� ����������

  ������� ����������, ������� ����� ��������� �� ������������ ����� ������ �����, 
  �������� �������� �������, �������� �� �������������� �� ����� � ���������� � ����. 

  ��������� ��������� ������ ����� � �����. ������ �������� �������� ���������� ��� �������.
  ��� ���������� �����, � ������� ������������ ������� ���������� � ������� � ���������.

  ������:
	����, 5-��������, 6-��������
*/
#include <list>
#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include <memory>
#include <functional>
#include <thread>

#include <iomanip>
#include <chrono>

#include "figure_factory.hpp"

class Buffer {
public:
	using shared_figure_ptr_t = std::shared_ptr<Figure>;
	using buffer_t = std::list<shared_figure_ptr_t>;
	using handler_t = std::function<void(const buffer_t&)>;
public:
	// ����������� �� ���������, ������������ ������ ����� 0.
	Buffer();
	// �����������, maxSize - ������������ ������ ������.
	Buffer(size_t maxSize);

	// ������������� ������������ ������ ������.
	void SetMaxSize(size_t size);
	// ���������� ������������ ������ ������.
	size_t GetMaxSize();

	// �������� ������ figure � ������.
	void Append(shared_figure_ptr_t figure);

	// ��������� ���������� func.
	void Attach(handler_t handler);
private:
	// ��������� ���� ������������ � ��������� ������.
	void Notify();

private:
	size_t _maxSize;
	// ������ �����
	buffer_t _buffer;
	// ������ ������������
	std::list<handler_t> _handlers;
};

Buffer::Buffer()
	: _maxSize(0), _buffer(), _handlers()
{}
Buffer::Buffer(size_t maxSize)
	: _maxSize(maxSize), _buffer(), _handlers()
{}

void Buffer::SetMaxSize(size_t size) {
	if (_buffer.size() >= size)
		Notify();
	
	_maxSize = size;
}

size_t Buffer::GetMaxSize() {
	return _maxSize;
}

void Buffer::Append(shared_figure_ptr_t figure) {
	if (_buffer.size() == _maxSize)
		Notify();
	_buffer.push_back(figure);
	if (_buffer.size() == _maxSize)
		Notify();
}
void Buffer::Attach(handler_t func) {
	_handlers.push_back(func);
}

void Buffer::Notify() {
	// ������� ����� � �������� ������� �����������.
	std::thread worker([this](){
		for (auto& handler : this->_handlers)
			handler(this->_buffer);
		});

	worker.join();
	// �������� �����.
	_buffer.clear();
}

void clear() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void help() {
	std::cout <<
		"�������������: oop_exercise_8 <max buffer size>\n"
		"��������� �������:\n"
		"	help - ������� ��� �������.\n"
		"	exit - �����;\n"
		"	add <r|p|h> <center> <vertex> - �������� ������ (����|����|�������������)\n"
		"			� ������������� ������ � <center> � ������ �������� � <vertex>;\n";
}

void add(std::shared_ptr<FigureMaker> figureMaker, Buffer& buffer) {
	try {
		if (Figure* figure = figureMaker->Make()) {
			buffer.Append(std::shared_ptr<Figure>(figure));
		}
		else {
			std::cout << "������ ������ � �������� �������\n";
			clear();
		}
	}
	catch (std::invalid_argument& e) {
			std::cout << "������: " << e.what() << "\n";
	}

}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "russian");
	
	Buffer buffer;
	
	// ����������, ������� ������� ������ � ����� ������
	buffer.Attach([](const Buffer::buffer_t& buff) {
		for (auto& figure : buff)
			figure->Print(std::cout);
	});
	// ����������, ������� �������� ������ � ����
	buffer.Attach([](const Buffer::buffer_t& buff) {
		auto timePoint = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream pathS;
		pathS << std::put_time(std::localtime(&timePoint), "%Y-%m-%d %H-%M-%S") << ".log";
		std::ofstream ofs(pathS.str(), std::fstream::out);
		if (!ofs) {
			std::cout << "�� ���� ������� ����!\n";
			return;
		}
		for (auto& figure : buff)	
			figure->Print(ofs);

		ofs.close();
	});

	if (argc != 2) {
		help();
		return 1;
	}

	{
		int64_t max_size;
		std::stringstream st(argv[1]);

		if (st >> max_size && max_size > 0 ) {
			buffer.SetMaxSize(max_size);
		}
		else {
			std::cout << "������ ����� ���������. ��� ������ ���� ����������� �����!\n";
			return 1;
		}
	}

	std::shared_ptr<FigureMaker> figureMaker(new FigureInputMaker(std::cin));

	std::string cmd;
	std::cout << '>';
	while (std::cin >> cmd) {
		// ��������� ���������������� ������
		if (cmd == "help") {
			help();
		}
		else if (cmd == "exit") {
			break;
		}
		else if (cmd == "add") {
			add(figureMaker, buffer);
		}
		else {
			std::cout << "������� ����������� �������\n";
			clear();
		}
		std::cout << '>';
	}

	return 0;
}