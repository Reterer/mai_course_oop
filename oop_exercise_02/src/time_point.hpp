#include <iostream>

class TimePoint
{
public:
	// Создает метку "0:0:0"
	TimePoint();
	// Создает метку "h:m:s"
	TimePoint(int hours, int minuts, int seconds);

	// Конвертирует метку в секунды
	int ToSeconds() const;
	// Устанавливает метку равной seconds
	void FromSeconds(int seconds);
	// Конвертирует метку в минуты
	int ToMinuts() const;
	// Устанавливает метку равной minuts
	void FromMinuts(int minuts);
	// Добавляет секунды к метке. кол-во секунд может быть положительным и отрицательным
	void AddSeconds(int seconds);
	// Возрващает отношение этой временной метки к tp (во сколько раз больше this, чем tp)
	double TimesMore(const TimePoint tp) const;

	// Возвращает кол-во полных часов
	int GetHours() const;
	// Возвращает кол-во минут в текущем часу
	int GetMinuts() const;
	// Возвращает кол-во секунд в текущей минуте
	int GetSeconds() const;

	// Устанавливает кол-во часов
	void SetHours(int hours);
	// Устанавливает кол-во минут в текущем часу
	void SetMinuts(int minuts);
	// Устанавливает кол-во секнуд в текущей минуте
	void SetSeconds(int seconds);

	friend TimePoint operator-(const TimePoint a, const TimePoint b);
	friend TimePoint operator+(const TimePoint a, const TimePoint b);

	bool operator==(TimePoint rhs);
	bool operator!=(TimePoint rhs);
	bool operator>(TimePoint rhs);
	bool operator>=(TimePoint rhs);
	bool operator<(TimePoint rhs);
	bool operator<=(TimePoint rhs);

	friend std::ostream &operator<<(std::ostream &os, const TimePoint tp);
	friend std::istream &operator>>(std::istream &os, TimePoint &tp);

private:
	int hours;
	int minuts;
	int seconds;
};

TimePoint operator"" _tp(const char *str, size_t size);