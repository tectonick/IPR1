/* ����������� �����������(portable) ����� ThreadPool.������ ����� ������ �������� ��������� �������, ����������� � ���������
��������.� ������� ����� ���������� � �������� ��������� ��������� ����� ���������� ������� � ������.��� ����������
��������� ������ ������ ThreadPool ���������� ����� �� ���� ��������� �������
*/

#include <iostream>
#include "ThreadPool.h"

void Test() {
    std::cout << "Hello World!\n";
}

void Test2() {
    std::cout << "TEST2!\n";
}


int main()
{
    
    ThreadPool * tp = new ThreadPool();
    tp->Run(Test);
    tp->Run(Test2);
    tp->Run(Test);
    tp->Run(Test);
    tp->Run(Test2);
    tp->Run(Test);
    tp->Run(Test2);
    tp->Run(Test);
    tp->Run(Test2);
    tp->Run(Test2);
    delete tp;
}
