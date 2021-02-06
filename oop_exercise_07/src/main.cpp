/*
  ������������ ������: 7
  �������: 21
  ������: �8�-206�-19
  �����: ������� ���� ����������

  �������������� ���������� ������������ ��������� ��������. 
  �������� ������ ����� ���������, ��������, ������� ������, ������ ������ ��������.


  ������:
	����, 5-��������, 6-��������
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
	std::cout << "������ ���������!\n";
}
void CommandAddFigure::UnExecute() {
	figures.pop_back();
	std::cout << "���������� ������ ���������!\n";
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
	std::cout << "������ " << idx << " �������!\n";
}
void CommandRemoveFigure::UnExecute() {
	figures.insert(figures.begin() + idx, figure);
	std::cout << "�������� ������ ���������!\n";
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
		
		std::cout << "������� \"y\" (��) ��� \"n\" (���)\n";
	}
	std::cout << "��������� �����-�� ������!\n";
	clear();
	return false;
}

void help() {
	std::cout <<
		"help - ������� ��� �������.\n"
		"exit - �����;\n"
		"save <path> - �������� ������;\n"
		"load <path> - �������� ������;\n"
		"print - ������� ������ �����;\n"
		"add <r|p|h> <center> <vertex> - �������� ������ (����|����|�������������)\n"
		"			� ������������� ������ � <center> � ������ �������� � <vertex>;\n"
		"remove <id> - ������� ������ � �������� <id>;\n"
		"undo - �������� ��������� ��������.\n";
}

void print(const std::vector<Figure*>& figures) {
	for (int i = 0; i < figures.size(); ++i) {
		std::cout << "������ " << i << " :";
		figures[i]->Print();
	}
}

void save(const std::vector<Figure*>& figures) {
	std::string fileName;
	if (!std::getline(std::cin, fileName)) {
		std::cout << "������ ����� ����� �����\n";
		clear();
		return;
	}
	if (std::ofstream ofs = std::ofstream(fileName, std::fstream::out | std::fstream::binary | std::fstream::trunc)) {
		size_t size = figures.size();
		ofs.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (auto f : figures) {
			if (!f->Save(ofs)) {
				std::cout << "�����-�� ������ ��� ���������� ������\n";
				return;
			}
		}
		ofs.close();
	}
	else {
		std::cout << "������ ��� �������� �����\n";
		return;
	}
}

void load(std::vector<Figure*>& figures, std::stack<Command*>& execCommands) {
	std::string fileName;
	if (!std::getline(std::cin, fileName)) {
		std::cout << "������ ����� ����� �����\n";
		clear();
		return;
	}
	if (std::ifstream ifs = std::ifstream(fileName, std::fstream::in | std::fstream::binary)) {
		std::vector<Figure*> newFigures;
		FigureMaker* loaderFigures = new FigureLoadMaker(ifs);

		size_t figure_count;
		ifs.read(reinterpret_cast<char*>(&figure_count), sizeof(figure_count));
		std::cout << figure_count << " ���-�� �����\n";
		try {
			while (Figure* figure = loaderFigures->Make()) {
				newFigures.push_back(figure);
				figure->Print();
			}
		}
		catch (std::invalid_argument& e) {
			std::cout << "������: " << e.what() << "\n";
			return;
		}

		if (figure_count == newFigures.size()) {
			figures = std::move(newFigures);
			execCommands = std::stack<Command*>();
		}
		else {
			std::cout << "���� �������� � �������� �������.\n�� ��������, ��� ������ ������� ��� (y/n)? ";
			if (ansYesNo()) {
				figures = std::move(newFigures);
				execCommands = std::stack<Command*>();
			}
		}
		ifs.close();
	}
	else {
		std::cout << "������ ��� �������� �����\n";
		return;
	}
}

Command* add(std::vector<Figure*>& figures, FigureMaker* figureMaker) {
	try {
		if (Figure* figure = figureMaker->Make()) {
			return new CommandAddFigure(figures, figure);
		}
		else {
			std::cout << "������ ������ � �������� �������\n";
			clear();
		}
	}
	catch (std::invalid_argument& e) {
			std::cout << "������: " << e.what() << "\n";
			return nullptr;
	}
	return nullptr;
}

Command* remove(std::vector<Figure*>& figures) {
	int idx;
	if (!(std::cin >> idx)) {
		std::cout << "������ �����\n";
		clear();
		return nullptr;
	}
	if (idx < 0 || idx >= figures.size()) {
		std::cout << "����� ������������ ������\n";
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
		std::cout << "���� ������ ��� ������\n";
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
		// ��������� ���������������� ������
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
				std::cout << "������� ����������� �������\n";
				clear();
			}
		}
		


		// ���������� �������
		if (figureCommand) {
			figureCommand->Execute();
			execCommands.push(figureCommand);
		}
	}

	return 0;
}