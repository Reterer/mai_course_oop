/*
  ������������ ������: 2
  �������: 14
  ������: �8�-206�-19
  �����: ������� ���� ����������
  
  �������:
    C������ ����� TimePoint ��� ������ � ��������� ������� � ������� ����:������:�������. 
    ������������� ���������� ��������: ���������� ������� ����� ����� ��������� �������,
    ����� �������� �������, �������� ������� ������� � ��������� ���������� ������,
    ��������� �� ������� ������� ��������� ���������� ������,
    ���������� �� ��� ������� ���� ������ ������� ������ (������) �������,
    ��������� �������� �������, ������� � ������� � �������, ������� � ������ (� ����������� �� ������) � �������. 
    �������� �������� � ��������� TimePoint,
    � ��� �� ��������� (������, ������ � �����) ���������� ����������� � ���� ���������� ����������.
    ���������� ����������� ���������������� ������� ��� ������ � ����������� ���� TimePoint.
*/
#include <iostream>
#include <string>
#include "time_point.hpp"

using namespace std;

// ������� ������ cin, � ��� �� ���������� ������� ������
void clearLine()
{
    cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ��������� TimePoint � ���������� ������
bool readTimePoint(TimePoint &tp)
{
    if (cin >> tp && isspace(cin.peek()))
        return true;

    cout << "������ �����." << endl;
    clearLine();
    return false;
}

void help()
{
    cout <<
        "���� ����� ������� ������������ � �������: h m s\n"
        "�������� ��������� �������:\n"
        "\texit                              ����� �� ���������\n"
        "\thelp                              ����� ���������� ���������� � ���������\n"
        "\ttoSec     <TimePoint>             ������� � �������\n"
        "\ttoMin     <TimePoint>             ������� � ������\n"
        "\tfromSec   <seconds>               ������� �� ������ � TimePoint\n"
        "\tfromMin   <minuts>                ������� �� ����� � TimePoint\n"
        "\tadd       <TimePoint> <TimePoint> �������� ���� TimePoint\n"
        "\tsub       <TimePoint> <TimePoint> ��������� ���� TimePoint\n"
        "\ttimesMore <TimePoint> <TimePoint> ���������� ��������� ����� TimePoint\n"
        "\taddSec    <TimePoint> <seconds>   �������� ������� � TimePoint\n"
        "\tcmp       <TimePoint> <TimePoint> ��������� ���� TimePoint\n";
}

void toSec()
{
    TimePoint tp;
    if (readTimePoint(tp))
    {
        cout << tp.ToSeconds() << " c��." << endl;
    }
}

void toMin()
{
    TimePoint tp;
    if (readTimePoint(tp))
    {
        cout << tp.ToMinuts() << " ���." << endl;
    }
}

void fromSec()
{
    int sec;
    if (cin >> sec && isspace(cin.peek()))
    {
        if (sec < 0)
            cout << "���-�� ������ �� ����� ���� ������ ����." << endl;
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
        cout << "������ �����." << endl;
    }
}

void fromMin()
{
    int minutes;
    if (cin >> minutes && isspace(cin.peek()))
    {
        if (minutes < 0)
            cout << "���-�� ����� �� ����� ���� ������ ����." << endl;
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
        cout << "������ �����." << endl;
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
            cout << "����� ������� �� ����������." << endl;
        cout << "> ";
    }
}