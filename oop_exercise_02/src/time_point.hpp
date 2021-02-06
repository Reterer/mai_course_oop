#include <iostream>

class TimePoint
{
public:
	// ������� ����� "0:0:0"
	TimePoint();
	// ������� ����� "h:m:s"
	TimePoint(int hours, int minuts, int seconds);

	// ������������ ����� � �������
	int ToSeconds() const;
	// ������������� ����� ������ seconds
	void FromSeconds(int seconds);
	// ������������ ����� � ������
	int ToMinuts() const;
	// ������������� ����� ������ minuts
	void FromMinuts(int minuts);
	// ��������� ������� � �����. ���-�� ������ ����� ���� ������������� � �������������
	void AddSeconds(int seconds);
	// ���������� ��������� ���� ��������� ����� � tp (�� ������� ��� ������ this, ��� tp)
	double TimesMore(const TimePoint tp) const;

	// ���������� ���-�� ������ �����
	int GetHours() const;
	// ���������� ���-�� ����� � ������� ����
	int GetMinuts() const;
	// ���������� ���-�� ������ � ������� ������
	int GetSeconds() const;

	// ������������� ���-�� �����
	void SetHours(int hours);
	// ������������� ���-�� ����� � ������� ����
	void SetMinuts(int minuts);
	// ������������� ���-�� ������ � ������� ������
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