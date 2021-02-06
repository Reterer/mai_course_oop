#include "time_point.hpp"
#include <iostream>

TimePoint::TimePoint()
		: hours(0), minuts(0), seconds(0)
{
}

TimePoint::TimePoint(int hours, int minuts, int seconds)
		: hours(hours), minuts(minuts), seconds(seconds)
{
	if (this->hours < 0)
		this->hours = 0;
	if (this->minuts < 0 || this->minuts >= 60)
		this->minuts = 0;
	if (this->seconds < 0 || this->seconds >= 60)
		this->seconds = 0;
}

int TimePoint::ToSeconds() const
{
	return seconds + (minuts + hours * 60) * 60;
}

void TimePoint::FromSeconds(int seconds)
{
	if (seconds < 0)
		seconds = 0;
	this->seconds = seconds % 60;
	minuts = seconds / 60;
	hours = minuts / 60;
	minuts %= 60;
}

int TimePoint::ToMinuts() const
{
	return minuts + hours * 60;
}

void TimePoint::FromMinuts(int minuts)
{
	if (minuts < 0)
		minuts = 0;

	this->seconds = 0;
	this->minuts = minuts % 60;
	this->hours = minuts / 60;
}

void TimePoint::AddSeconds(int seconds)
{
	int new_sec = ToSeconds() + seconds;
	if (new_sec < 0)
		new_sec = 0;

	FromSeconds(new_sec);
}

double TimePoint::TimesMore(const TimePoint tp) const
{
	return (double)ToSeconds() / (double)tp.ToSeconds();
}

int TimePoint::GetHours() const
{
	return seconds;
}

int TimePoint::GetMinuts() const
{
	return minuts;
}

int TimePoint::GetSeconds() const
{
	return seconds;
}

void TimePoint::SetHours(int hours)
{
	if (hours < 0)
		return;
	this->hours = hours;
}

void TimePoint::SetMinuts(int minuts)
{
	if (minuts < 0 || minuts >= 60)
		return;
	this->minuts = minuts;
}

void TimePoint::SetSeconds(int seconds)
{
	if (seconds < 0 || seconds >= 60)
		return;
	this->seconds = seconds;
}

bool TimePoint::operator==(TimePoint rhs)
{
	return this->hours == rhs.hours && this->minuts == rhs.minuts && this->seconds == rhs.seconds;
}

bool TimePoint::operator!=(TimePoint rhs)
{
	return this->seconds != rhs.seconds || this->minuts != rhs.minuts || this->hours != rhs.hours;
}

bool TimePoint::operator>(TimePoint rhs)
{
	return ToSeconds() > rhs.ToSeconds();
}

bool TimePoint::operator>=(TimePoint rhs)
{
	return ToSeconds() >= rhs.ToSeconds();
}

bool TimePoint::operator<(TimePoint rhs)
{
	return ToSeconds() < rhs.ToSeconds();
}

bool TimePoint::operator<=(TimePoint rhs)
{
	return ToSeconds() <= rhs.ToSeconds();
}

TimePoint operator-(const TimePoint a, const TimePoint b)
{
	int s = a.seconds - b.seconds;
	int m = a.minuts - b.minuts;
	int h = a.hours - b.hours;

	if (s < 0)
	{
		m--;
		s += 60;
	}
	if (m < 0)
	{
		h--;
		m += 60;
	}
	if (h < 0)
	{
		h = 0;
		m = 0;
		s = 0;
	}
	return TimePoint(h, m, s);
}

TimePoint operator+(const TimePoint a, const TimePoint b)
{
	int s = a.seconds + b.seconds;
	int m = a.minuts + b.minuts;
	int h = a.hours + b.hours;

	if (s >= 60)
	{
		m++;
		s -= 60;
	}
	if (m >= 60)
	{
		h++;
		m -= 60;
	}
	return TimePoint(h, m, s);
}

std::ostream &operator<<(std::ostream &os, const TimePoint tp)
{
	os << tp.hours << ':' << tp.minuts << ':' << tp.seconds;
	return os;
}

std::istream &operator>>(std::istream &os, TimePoint &tp)
{
	int s, m, h;
	os >> h >> m >> s;
	if (h < 0 || m < 0 || s < 0 || m >= 60 || s >= 60)
	{
		os.setstate(std::ios_base::failbit);
		h = 0;
		m = 0;
		s = 0;
	}
	tp = TimePoint(h, m, s);
	return os;
}

// возвращает число из строки
int getInt(const char *str)
{
	int res = 0;
	while (*str != ':' && *str != '\0')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return res;
}

// возвращает индекс следующего разделителя
int getNextSeparate(const char* str)
{
	int sep = 0;
	while (str[sep] != ':')
		sep++;
	return sep;
}

TimePoint operator""_tp(const char *str, size_t size)
{
	int beg = 0; // индекс элемента, находящегося после разделителя
	
	// Часы
	int h = getInt(str);
	beg = getNextSeparate(str) + 1;
	str += beg;

	// Минуты
	int m = getInt(str);
	beg = getNextSeparate(str) + 1;
	str += beg;
	
	// Секунды
	int s = getInt(str);

	return TimePoint(h, m, s);
}
