#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <spider/core/include/thread.hpp>

class Person2
{
public:
    int test(int a, int b = 9) {
        std::cout<< "Person2 b= " << b << " a= " << a << std::endl;

        return 0;
    }

};

Person2 person2;

spider::core::ThreadBase thread;

class Person
{
public:
    int test(int a, int b = 9) {
        std::cout<< " b= " << b << " a= " << a << std::endl;
        auto t = std::bind(&Person2::test, &person2, 10, 8);
        thread.PostTask(t);

        return 0;
    }

};


int main(int argc, char** argv) {
    int a = 100;
    int b = 20;
    thread.Start();
    // auto t = [=,a, &b] (int text, char* t) {
    //     b = -1;
    // std::cout<< "text text= " << text << " t= " << t << std::endl;
    // std::cout<< "inner b= " << b << " a= " << a << std::endl;
    //     return a +10;
    // };
    // t(1, "f");

    //auto t = std::bind(test, 10, 2);
    Person p;
    auto t = std::bind(&Person::test, p, 10, 8);
    thread.PostTask(t);

    spider::core::Task task(std::bind(&Person::test, p, 10, 8));
    task.Cancel();
    thread.PostTask(task);
    sleep(1);
    std::cout<< " sleep "<< std::endl;
    spider::core::Task task2(std::bind(&Person::test, p, 10, 8));
    thread.PostTask(task2);
    spider::core::Task task3(nullptr);


getchar();


    printf("hello world\n");
    return 0;
}
