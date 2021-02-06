/*
  Лабораторная работа: 2
  Вариант: 14
  Группа: М8О-206Б-19
  Автор: Суханов Егор Алексеевич
  
  Задание:
    Cоздать класс TimePoint для работы с моментами времени в формате «час:минута:секунда». 
    Обязательными операциями являются: вычисление разницы между двумя моментами времени,
    сумма моментов времени, сложение момента времени и заданного количества секунд,
    вычитание из момента времени заданного количества секунд,
    вычисление во раз сколько один момент времени больше (меньше) другого,
    сравнение моментов времени, перевод в секунды и обратно, перевод в минуты (с округлением до минуты) и обратно. 
    Операции сложения и вычитания TimePoint,
    а так же сравнения (больше, меньше и равно) необходимо реализовать в виде перегрузки операторов.
    Необходимо реализовать пользовательский литерал для работы с константами типа TimePoint.
*/
#include <iostream>
#include <string>
#include "time_point.hpp"

using namespace std;

// Ощищает статус cin, а так же игнорирует остаток строки
void clearLine()
{
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Считывает TimePoint с обработкой ошибок
bool readTimePoint(TimePoint &tp)
{
    if (cin >> tp && isspace(cin.peek()))
        return true;

    cout << "Ошибка ввода." << endl;
    clearLine();
    return false;
}

void help()
{
    cout <<
        "Ввод метки времени производится в формате: h m s\n"
        "Доступны следующие команды:\n"
        "\texit                              выход из программы\n"
        "\thelp                              вывод справочной информации о программе\n"
        "\ttoSec     <TimePoint>             перевод в секунды\n"
        "\ttoMin     <TimePoint>             перевод в минуты\n"
        "\tfromSec   <seconds>               перевод из секунд в TimePoint\n"
        "\tfromMin   <minuts>                перевод из минут в TimePoint\n"
        "\tadd       <TimePoint> <TimePoint> сложение двух TimePoint\n"
        "\tsub       <TimePoint> <TimePoint> вычитание двух TimePoint\n"
        "\ttimesMore <TimePoint> <TimePoint> нахождение отношения между TimePoint\n"
        "\taddSec    <TimePoint> <seconds>   добавить секунды к TimePoint\n"
        "\tcmp       <TimePoint> <TimePoint> сравнение двух TimePoint\n";
}

void toSec()
{
    TimePoint tp;
    if (readTimePoint(tp))
    {
        cout << tp.ToSeconds() << " cек." << endl;
    }
}

void toMin()
{
    TimePoint tp;
    if (readTimePoint(tp))
    {
        cout << tp.ToMinuts() << " мин." << endl;
    }
}

void fromSec()
{
    int sec;
    if (cin >> sec && isspace(cin.peek()))
    {
        if (sec < 0)
            cout << "Кол-во секунд не может быть меньше нуля." << endl;
        else
        {
            TimePoint tp;
            tp.FromSeconds(sec);
            cout << tp << endl;
        }
    }
    else
    {
        clearLine();
        cout << "Ошибка ввода." << endl;
    }
}

void fromMin()
{
    int minutes;
    if (cin >> minutes && isspace(cin.peek()))
    {
        if (minutes < 0)
            cout << "Кол-во минут не может быть меньше нуля." << endl;
        else
        {
            TimePoint tp;
            tp.FromMinuts(minutes);
            cout << tp << endl;
        }
    }
    else
    {
        clearLine();
        cout << "Ошибка ввода." << endl;
    }
}

void add()
{
    TimePoint a, b;
    if (readTimePoint(a) && readTimePoint(b))
        cout << a + b << endl;
}

void sub()
{
    TimePoint a, b;
    if (readTimePoint(a) && readTimePoint(b))
        cout << a - b << endl;
}

void timesMore()
{
    TimePoint a, b;
    if (readTimePoint(a) && readTimePoint(b))
        cout << a.TimesMore(b) << endl;
}

void addSec()
{
    TimePoint a;
    int sec;
    if (readTimePoint(a))
    {
        if (cin >> sec)
        {
            a.AddSeconds(sec);
            cout << a << endl;
        }
        else
            clearLine();
    }
}

void cmp()
{
    TimePoint a, b;
    if (readTimePoint(a) && readTimePoint(b))
    {
        if (a == b)
            cout << a << " == " << b << endl;
        if (a != b)
            cout << a << " != " << b << endl;
        if (a < b)
            cout << a << " < " << b << endl;
        if (a <= b)
            cout << a << " <= " << b << endl;
        if (a > b)
            cout << a << " > " << b << endl;
        if (a >= b)
            cout << a << " >= " << b << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    string cmd;
    cout << "> ";
    while (cin >> cmd)
    {
        if (cmd == "exit")
            break;
        else if (cmd == "help")
            help();
        else if (cmd == "toSec")
            toSec();
        else if (cmd == "toMin")
            toMin();
        else if (cmd == "fromSec")
            fromSec();
        else if (cmd == "fromMin")
            fromMin();
        else if (cmd == "add")
            add();
        else if (cmd == "sub")
            sub();
        else if (cmd == "timesMore")
            timesMore();
        else if (cmd == "addSec")
            addSec();
        else if (cmd == "cmp")
            cmp();
        else
            cout << "Такой команды не существует." << endl;
        cout << "> ";
    }
}