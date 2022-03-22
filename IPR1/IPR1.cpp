/* Разработать переносимый(portable) класс ThreadPool.Объект этого класса содержит несколько потоков, находящихся в состоянии
ожидания.К объекту можно обратиться с запросом выполнить некоторый метод некоторого объекта в потоке.Для выполнения
процедуры объект класса ThreadPool подключает поток из пула ожидающих потоков
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
