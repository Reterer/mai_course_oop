/*
  Лабораторная работа: 7
  Вариант: 21
  Группа: М8О-206Б-19
  Автор: Суханов Егор Алексеевич

  Спроектировать простейший «графический» векторный редактор. 
  Редактор должен уметь создавать, выводить, удалять фигуры, делать отмену дейсвтия.


  Фигуры:
	Ромб, 5-угольник, 6-уогльник
*/
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "figure.hpp"
#include "figure_factory.hpp"

class Command {
public:
	virtual void Execute() = 0;
	virtual void UnExecute() = 0;
};


class CommandAddFigure : public Command {
public:
	CommandAddFigure(std::vector<Figure*>& figures, Figure* figure)
		: figures(figures), figure(figure)
	{};

	virtual void Execute() override;
	virtual void UnExecute() override;

private:
	std::vector<Figure*>& figures;
	Figure* figure;
};

void CommandAddFigure::Execute() {
	figures.push_back(figure);
	std::cout << "Фигура добавлена!\n";
}
void CommandAddFigure::UnExecute() {
	figures.pop_back();
	std::cout << "Добавление фигуры отмененно!\n";
}

class CommandRemoveFigure : public Command {
public:
	CommandRemoveFigure(std::vector<Figure*>& figures, int idx)
		: figures(figures), idx(idx)
	{};

	virtual void Execute() override;
	virtual void UnExecute() override;

private:
	std::vector<Figure*>& figures;
	Figure* figure;
	int idx;
};

void CommandRemoveFigure::Execute() {
	figure = figures[idx];
	figures.erase(figures.begin() + idx);
	std::cout << "Фигура " << idx << " удалена!\n";
}
void CommandRemoveFigure::UnExecute() {
	figures.insert(figures.begin() + idx, figure);
	std::cout << "Удаление фигуры отменнено!\n";
}

void clear() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
bool ansYesNo() {
	std::string ans;
	while (std::cin >> ans) {
		if (ans == "y")
			return true;
		else if (ans == "n")
			return false;
		
		std::cout << "Введите \"y\" (да) или \"n\" (нет)\n";
	}
	std::cout << "Произошла какая-то ошибка!\n";
	clear();
	return false;
}

void help() {
	std::cout <<
		"help - выводит эту справку.\n"
		"exit - выход;\n"
		"save <path> - сохрание сессии;\n"
		"load <path> - загрузка сессии;\n"
		"print - вывести список фигур;\n"
		"add <r|p|h> <center> <vertex> - добавить фигуру (ромб|пяти|шестиугольник)\n"
		"			с коордиинатами центра в <center> и первой вершиной в <vertex>;\n"
		"remove <id> - удалить фигуру с индексом <id>;\n"
		"undo - отменить последнее действие.\n";
}

void print(const std::vector<Figure*>& figures) {
	for (int i = 0; i < figures.size(); ++i) {
		std::cout << "Фигура " << i << " :";
		figures[i]->Print();
	}
}

void save(const std::vector<Figure*>& figures) {
	std::string fileName;
	if (!std::getline(std::cin, fileName)) {
		std::cout << "Ошибка ввода имени файла\n";
		clear();
		return;
	}
	if (std::ofstream ofs = std::ofstream(fileName, std::fstream::out | std::fstream::binary | std::fstream::trunc)) {
		size_t size = figures.size();
		ofs.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (auto f : figures) {
			if (!f->Save(ofs)) {
				std::cout << "Какая-то ошибка при сохранении фигуры\n";
				return;
			}
		}
		ofs.close();
	}
	else {
		std::cout << "Ошибка при открытии файла\n";
		return;
	}
}

void load(std::vector<Figure*>& figures, std::stack<Command*>& execCommands) {
	std::string fileName;
	if (!std::getline(std::cin, fileName)) {
		std::cout << "Ошибка ввода имени файла\n";
		clear();
		return;
	}
	if (std::ifstream ifs = std::ifstream(fileName, std::fstream::in | std::fstream::binary)) {
		std::vector<Figure*> newFigures;
		FigureMaker* loaderFigures = new FigureLoadMaker(ifs);

		size_t figure_count;
		ifs.read(reinterpret_cast<char*>(&figure_count), sizeof(figure_count));
		std::cout << figure_count << " кол-во фигур\n";
		try {
			while (Figure* figure = loaderFigures->Make()) {
				newFigures.push_back(figure);
				figure->Print();
			}
		}
		catch (std::invalid_argument& e) {
			std::cout << "Ошибка: " << e.what() << "\n";
			return;
		}

		if (figure_count == newFigures.size()) {
			figures = std::move(newFigures);
			execCommands = std::stack<Command*>();
		}
		else {
			std::cout << "Файл сохранен в неверном формате.\nВы уверенны, что хотите открыть его (y/n)? ";
			if (ansYesNo()) {
				figures = std::move(newFigures);
				execCommands = std::stack<Command*>();
			}
		}
		ifs.close();
	}
	else {
		std::cout << "Ошибка при открытии файла\n";
		return;
	}
}

Command* add(std::vector<Figure*>& figures, FigureMaker* figureMaker) {
	try {
		if (Figure* figure = figureMaker->Make()) {
			return new CommandAddFigure(figures, figure);
		}
		else {
			std::cout << "Фигура задана в неверном формате\n";
			clear();
		}
	}
	catch (std::invalid_argument& e) {
			std::cout << "Ошибка: " << e.what() << "\n";
			return nullptr;
	}
	return nullptr;
}

Command* remove(std::vector<Figure*>& figures) {
	int idx;
	if (!(std::cin >> idx)) {
		std::cout << "Ошибка ввода\n";
		clear();
		return nullptr;
	}
	if (idx < 0 || idx >= figures.size()) {
		std::cout << "Задан неправильный индекс\n";
		clear();
		return nullptr;
	}

	return new CommandRemoveFigure(figures, idx);
}

void undo(std::stack<Command*>& execCommands) {
	if (!execCommands.empty()) {
		execCommands.top()->UnExecute();
		execCommands.pop();
	}
	else {
		std::cout << "Стек команд уже пустой\n";
	}
}


int main() {
	setlocale(LC_ALL, "russian");

	std::vector<Figure*> figures;
	std::stack<Command*> execCommands;
	FigureMaker* figureMaker = new FigureInputMaker(std::cin);
	bool run = true;

	while (run) {
		Command* figureCommand = nullptr;
		// Обработка пользовательских команд
		{
			std::string cmd;
			std::cout << '>';
			std::cin >> cmd;
			if (cmd == "help") {
				help();
			}
			else if (cmd == "exit") {
				run = false;
			}
			else if (cmd == "save") {
				save(figures);
			}
			else if (cmd == "load") {
				load(figures, execCommands);
			}
			else if (cmd == "print") {
				print(figures);
			}
			else if (cmd == "add") {
				figureCommand = add(figures, figureMaker);
			}
			else if (cmd == "remove") {
				figureCommand = remove(figures);
			}
			else if (cmd == "undo") {
				undo(execCommands);
			}
			else {
				std::cout << "Введена неизвестная команда\n";
				clear();
			}
		}
		


		// Выполнение команды
		if (figureCommand) {
			figureCommand->Execute();
			execCommands.push(figureCommand);
		}
	}

	return 0;
}