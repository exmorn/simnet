#include "threadpool.h"
int i = 1;
void task1()
{
    while(1)
    {
        printf("i = %d pid: %d\n", i++, simnet::currentThreadId());
        Sleep(2000);
    }
    
}
void task2()
{
    while(1)
    {
        printf("i = %d pid: %d\n", i--, simnet::currentThreadId());
        Sleep(1000);
    }
}
int main()
{
    printf("begin\n");
    simnet::ThreadPool pool("testThreadPool");
    pool.start(10);
    pool.run(task1);
    pool.run(task1);
    Sleep(1000);
    pool.run(task2);
    Sleep(500000);
    return 0;
}