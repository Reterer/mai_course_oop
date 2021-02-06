/*
  Лабораторная работа: 8
  Вариант: 21
  Группа: М8О-206Б-19
  Автор: Суханов Егор Алексеевич

  Создать приложение, которое будет считывать из стандартного ввода данные фигур, 
  согласно варианту задания, выводить их характеристики на экран и записывать в файл. 

  Сохранять введенные фигуры нужно в буфер. Размер которого задается аргументом при запуске.
  При заполнении буфер, с помощью обработчиков выводит информацию о фигурах и очищается.

  Фигуры:
	Ромб, 5-угольник, 6-уогльник
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
	// Конструктор по умолчанию, максимальный размер равен 0.
	Buffer();
	// Конструктор, maxSize - максимальный размер буфера.
	Buffer(size_t maxSize);

	// Устанавилвает максимальный размер буфера.
	void SetMaxSize(size_t size);
	// Возвращает максимальный размер буфера.
	size_t GetMaxSize();

	// Добавить фигуру figure в буффер.
	void Append(shared_figure_ptr_t figure);

	// Добавляет обработчик func.
	void Attach(handler_t handler);
private:
	// Выполняет всех наблюдателей в отдельном потоке.
	void Notify();

private:
	size_t _maxSize;
	// Список фигур
	buffer_t _buffer;
	// Список обработчиков
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
	// Создаем поток и вызываем каждого обработчика.
	std::thread worker([this](){
		for (auto& handler : this->_handlers)
			handler(this->_buffer);
		});

	worker.join();
	// Обнуляем буфер.
	_buffer.clear();
}

void clear() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void help() {
	std::cout <<
		"Использование: oop_exercise_8 <max buffer size>\n"
		"Доступные команды:\n"
		"	help - выводит эту справку.\n"
		"	exit - выход;\n"
		"	add <r|p|h> <center> <vertex> - добавить фигуру (ромб|пяти|шестиугольник)\n"
		"			с коордиинатами центра в <center> и первой вершиной в <vertex>;\n";
}

void add(std::shared_ptr<FigureMaker> figureMaker, Buffer& buffer) {
	try {
		if (Figure* figure = figureMaker->Make()) {
			buffer.Append(std::shared_ptr<Figure>(figure));
		}
		else {
			std::cout << "Фигура задана в неверном формате\n";
			clear();
		}
	}
	catch (std::invalid_argument& e) {
			std::cout << "Ошибка: " << e.what() << "\n";
	}

}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "russian");
	
	Buffer buffer;
	
	// Обработчик, который выводит фигуры в поток вывода
	buffer.Attach([](const Buffer::buffer_t& buff) {
		for (auto& figure : buff)
			figure->Print(std::cout);
	});
	// Обработчик, который логирует фигуры в файл
	buffer.Attach([](const Buffer::buffer_t& buff) {
		auto timePoint = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream pathS;
		pathS << std::put_time(std::localtime(&timePoint), "%Y-%m-%d %H-%M-%S") << ".log";
		std::ofstream ofs(pathS.str(), std::fstream::out);
		if (!ofs) {
			std::cout << "Не могу открыть файл!\n";
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
			std::cout << "Ошибка ввода аргумента. Это должно быть натуральное число!\n";
			return 1;
		}
	}

	std::shared_ptr<FigureMaker> figureMaker(new FigureInputMaker(std::cin));

	std::string cmd;
	std::cout << '>';
	while (std::cin >> cmd) {
		// Обработка пользовательских команд
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
			std::cout << "Введена неизвестная команда\n";
			clear();
		}
		std::cout << '>';
	}

	return 0;
}