#include "iostream"

#pragma once

/*
  Класс для работы с числами по модулю.  
  Перегружает арифметические операции +,-,*,/.
  А так же операции сравнения >,>=,<,<=,==.
  Создает ошибку "diff modulo",
  если операнды имеют разные значения mod.
  Создает ошибку "zero modulo",
  если попытаться задать модуль равный нулю.
*/
class Modulo
{
public:
  Modulo();
  Modulo(int number, int mod);

  /* Получить поле Number */
  int GetNumber();
  /* Получить поле Mod */
  int GetMod();

  Modulo operator+(const Modulo &rhs) const;
  Modulo operator-(const Modulo &rhs) const;
  Modulo operator*(const Modulo &rhs) const;
  Modulo operator/(const Modulo &rhs) const;

  bool operator>(const Modulo &rhs) const;
  bool operator>=(const Modulo &rhs) const;
  bool operator<(const Modulo &rhs) const;
  bool operator<=(const Modulo &rhs) const;
  bool operator==(const Modulo &rhs) const;

  friend std::ostream &operator<<(std::ostream &out, const Modulo &modulo);
  friend std::istream &operator>>(std::istream &in, Modulo &modulo);

private:
  // Проверяет поле mod у this и b на тождество. Если они разные, создает ошибку "diff modulo"
  void validateMod(const Modulo &b) const
  {
    if (this->mod != b.mod)
      throw "diff modulo";
    if (this->mod == 0)
      throw "zero modulo";
  }

  int number;
  int mod; // Модуль по которому выполняются операции
};
