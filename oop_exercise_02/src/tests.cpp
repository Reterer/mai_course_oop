// Тестирование отдельных функций
#include <iostream>
#include "time_point.hpp"

// Выводит в поток вывода занчение expr и текст msg
void test(bool expr, const char* msg)
{
	std::cout << (expr?"[TRUE]\t":"[FALSE]\t") << msg << std::endl;
}

void tTimePointEq()
{
	TimePoint a, b;
	test(a == b && !(a != b), "TimePoint eq 1");

	a = TimePoint(10, 30, 15);
	b = TimePoint(10, 30, 15);
	test(a == b && !(a != b), "TimePoint eq 2");

	a = TimePoint(10, 30, 0);
	test(!(a == b) && a != b, "TimePoint eq 3");

	a = TimePoint(10, 0, 15);
	test(!(a == b) && a != b, "TimePoint eq 4");

	a = TimePoint(10, 0, 15);
	test(!(a == b) && a != b, "TimePoint eq 5");

}

void tTimePointSub()
{
	test(TimePoint(10, 30, 15) - TimePoint(1, 1, 1) == TimePoint(9, 29, 14), "TimePoint Sub 1");
	test(TimePoint(10, 30, 15) - TimePoint(0, 40, 0) == TimePoint(9, 50, 15), "TimePoint Sub 2");
	test(TimePoint(10, 30, 15) - TimePoint(0, 0, 30) == TimePoint(10, 29, 45), "TimePoint Sub 3");
	test(TimePoint(10, 30, 15) - TimePoint(10, 30, 15) == TimePoint(), "TimePoint Sub 4");
	test(TimePoint(10, 30, 15) - TimePoint(20, 0, 0) == TimePoint(), "TimePoint Sub 5");
}

void tTimePointAdd()
{
	test(TimePoint(10, 30, 15) + TimePoint(1, 1, 1) == TimePoint(11, 31, 16), "TimePoint Add 1");
	test(TimePoint(10, 30, 15) + TimePoint(0, 40, 0) == TimePoint(11, 10, 15), "TimePoint Add 2");
	test(TimePoint(10, 30, 15) + TimePoint(0, 0, 45) == TimePoint(10, 31, 0), "TimePoint Add 3");
	test(TimePoint(10, 30, 15) + TimePoint(10, 30, 15) == TimePoint(21, 0, 30), "TimePoint Add 4");
	test(TimePoint(10, 30, 15) + TimePoint(20, 0, 0) == TimePoint(30, 30, 15), "TimePoint Add 5");
}

void tTimePointAddSeconds()
{
	TimePoint tp(10, 30, 15);

	tp.AddSeconds(15);
	test(tp == TimePoint(10, 30, 30), "TimePoint Add Seconds 1");
	
	tp = TimePoint(10, 30, 30);
	tp.AddSeconds(45);
	test(tp == TimePoint(10, 31, 15), "TimePoint Add Seconds 2");
	
	tp = TimePoint(10, 30, 30);
	tp.AddSeconds(60 * 60);
	test(tp == TimePoint(11, 30, 30), "TimePoint Add Seconds 3");
	
	tp = TimePoint(10, 30, 30);
	tp.AddSeconds(60 * 60 + 45);
	test(tp == TimePoint(11, 31, 15), "TimePoint Add Seconds 4");
}

void tTimePointTimesMore()
{
	test(TimePoint(3, 0, 0).TimesMore(TimePoint(1, 30, 0)) == 2., "TimePoint Times More 1");
	test(TimePoint(3, 20, 20).TimesMore(TimePoint(10, 1, 0)) == 1./3., "TimePoint Times More 2");
}

void tTimePointCmp()
{
	test(TimePoint(3, 15, 2) > TimePoint(2, 0, 0), "TimePoint Cmp 1");
	test(TimePoint(3, 15, 2) >= TimePoint(2, 0, 0) 
		&& TimePoint(3, 15, 2) >= TimePoint(3, 15, 2), "TimePoint Cmp 2");

	test(TimePoint(3, 15, 2) < TimePoint(5, 0, 0), "TimePoint Cmp 3");
	test(TimePoint(3, 15, 2) <= TimePoint(5, 0, 0)
		&& TimePoint(3, 15, 2) <= TimePoint(3, 15, 2), "TimePoint Cmp 4");
}

void tTimePointConverts()
{
	TimePoint tp(3, 15, 2);
	TimePoint a;

	a.FromSeconds(tp.ToSeconds());
	test(a == tp, "TimePoint Converts 1");

	a.FromMinuts(tp.ToMinuts());
	test(a == TimePoint(3, 15, 0), "TimePoint Converts 2");
}

void tTimePointLiteral()
{
	test("12:23:12"_tp == TimePoint(12, 23, 12), "TimePoint Literal 1");
}

int main(void)
{
	tTimePointEq();
	std::cout << std::endl;
	tTimePointSub();
	std::cout << std::endl;
	tTimePointAdd();
	std::cout << std::endl;
	tTimePointAddSeconds();
	std::cout << std::endl;
	tTimePointTimesMore();
	std::cout << std::endl;
	tTimePointCmp();
	std::cout << std::endl;
	tTimePointConverts();
	std::cout << std::endl;
	tTimePointLiteral();
}