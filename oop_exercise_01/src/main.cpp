/*
  Лабораторная работа 1
  Автор: Суханов Егор Алексеевич
*/

#include <iostream>
#include <limits>
#include <string>
#include "modulo.hpp"

/*
 Сравнивает два экземпляра класса Modulo. 
 Результат сравнения выводит в стандартный поток вывода.
*/
void cmpModulo(const Modulo &lhs, const Modulo &rhs)
{
  try
  {
    if (lhs > rhs)
      std::cout << "lhs is bigger then rhs" << std::endl;
    else if (lhs == rhs)
      std::cout << "lhs is equal rhs" << std::endl;
    else if (lhs < rhs)
      std::cout << "lhs is less than rhs" << std::endl;
  }
  catch (std::string err)
  {
    std::cout << err << std::endl;
  }
}

bool readVariables(Modulo &lhs, Modulo &rhs)
{
  if (std::cin >> lhs >> rhs)
    return true;

  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Переменные введены неправильно" << std::endl;
  return false;
}

int main()
{
  // Обработка ввода команд
  std::string str; // Считанная команда
  while (std::cin >> str)
  {
    if (str == "exit")
      exit(0);
    else if (str == "help")
    {
      std::cout << "Опернды вводить в следующем формате:\n"
                   "\t<число> <модуль>\n"
                   "Доступные команды:\n"
                   "\texit    - выйти из приложения"
                   "\thelp    - вывести справку об командах"
                   "\tadd a b - сложить a и b\n"
                   "\tsub a b - вычесть b из a\n"
                   "\tmul a b - умножить a на b\n"
                   "\tsub a b - разделить a на b\n"
                   "\tcmp a b - сравнить a и b\n";
    }

    try
    {
      Modulo lhs;
      Modulo rhs;
      if (str == "add")
      {
        if (readVariables(lhs, rhs))
          std::cout << lhs + rhs << '\n';
      }
      else if (str == "sub")
      {
        if (readVariables(lhs, rhs))
          std::cout << lhs - rhs << '\n';
      }
      else if (str == "mul")
      {
        if (readVariables(lhs, rhs))
          std::cout << lhs * rhs << '\n';
      }
      else if (str == "div")
      {
        if (readVariables(lhs, rhs))
        {
          if (rhs.GetNumber() == 0)
            std::cout << "Нельзя делить на ноль" << std::endl;
          else
            std::cout << lhs / rhs << '\n';
        }
      }
      else if (str == "cmp")
      {
        if (readVariables(lhs, rhs))
          cmpModulo(lhs, rhs);
      }
      else
      {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Такой команды не существует\n";
      }
    }
    catch (char const *err)
    {
      std::cout << err << std::endl;
    }
  }
}