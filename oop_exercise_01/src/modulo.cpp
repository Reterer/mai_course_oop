#include "modulo.hpp"

Modulo::Modulo()
{
  this->number = 0;
  this->mod = 1;
}
Modulo::Modulo(int number, int mod)
{
  if (mod == 0)
    throw "zero modulo";
  this->number = number % mod;
  this->mod = mod;
}

int Modulo::GetNumber()
{
  return this->number;
}

int Modulo::GetMod()
{
  return this->mod;
}

Modulo Modulo::operator+(const Modulo &rhs) const
{
  validateMod(rhs);
  return {(this->number + rhs.number) % this->mod, mod};
}
Modulo Modulo::operator-(const Modulo &rhs) const
{
  validateMod(rhs);
  return {(this->number - rhs.number) % mod, this->mod};
}
Modulo Modulo::operator*(const Modulo &rhs) const
{
  validateMod(rhs);
  return {(this->number * rhs.number) % this->mod, this->mod};
}
Modulo Modulo::operator/(const Modulo &rhs) const
{
  validateMod(rhs);
  return {this->number / rhs.number, this->mod};
}

bool Modulo::operator>(const Modulo &rhs) const
{
  validateMod(rhs);
  return this->number > rhs.number;
}
bool Modulo::operator>=(const Modulo &rhs) const
{
  validateMod(rhs);
  return this->number >= rhs.number;
}
bool Modulo::operator<(const Modulo &rhs) const
{
  validateMod(rhs);
  return this->number < rhs.number;
}
bool Modulo::operator<=(const Modulo &rhs) const
{
  validateMod(rhs);
  return this->number <= rhs.number;
}
bool Modulo::operator==(const Modulo &rhs) const
{
  return this->mod == rhs.mod && this->number == rhs.number;
}

std::ostream &operator<<(std::ostream &out, const Modulo &modulo)
{
  out << modulo.number << ' ' << modulo.mod;
  return out;
}
std::istream &operator>>(std::istream &in, Modulo &modulo)
{
  in >> modulo.number >> modulo.mod;
  return in;
}