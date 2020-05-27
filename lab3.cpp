#include "lab3.h"
#include <iostream>
#include <Windows.h>

#define threadcount 11
HANDLE m;
HANDLE s[4];
HANDLE threads[threadcount];

HANDLE semstart;
HANDLE semend;

using namespace std;
unsigned int lab3_thread_graph_id() 
{
    return 4;
}

const char* lab3_unsynchronized_threads()
{
    return "bcde";
}

const char* lab3_sequential_threads()
{
    return "efgh";
}

DWORD WINAPI thread_a(LPVOID t)//id=0
{//1
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "a" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_i(LPVOID t)//id=8
{//5
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "i" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_k(LPVOID t)//id=9
{//5
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "k" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_m(LPVOID t)//id=9
{//6
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "m" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_f(LPVOID t)//id=5
{//4
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[1], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "f" << flush;
        ReleaseMutex(m);
        computation();
       ReleaseSemaphore(s[2], 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_b(LPVOID t)//id=1
{//2
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "b" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_c(LPVOID t)//id=2
{//1,2
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "c" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "c" << flush;
        ReleaseMutex(m);
        computation();
    }

    return 0;
}

DWORD WINAPI thread_d(LPVOID t)//id=3
{//1,2,3
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "d" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "d" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "d" << flush;
        ReleaseMutex(m);
        computation();
    }

    return 0;
}

DWORD WINAPI thread_e(LPVOID t)//id=4
{//1,2,3,4
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "e" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "e" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "e" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[0], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "e" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[1], 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_g(LPVOID t)//id=6
{//3,4
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "g" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[2], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "g" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[3], 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_h(LPVOID t)//id=7
{//3,4,5
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "h" << flush;
        ReleaseMutex(m);
        computation();
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[3], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "h" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[0], 1, NULL);
    }

    ReleaseSemaphore(semend, 1, NULL);
    WaitForSingleObject(semstart, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "h" << flush;
        ReleaseMutex(m);
        computation();
    }

    return 0;
}

void control_threads()
{
    //////////такт 1
    //создание потоков cade
    threads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, NULL);
    threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, NULL);
    threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, NULL);
    threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, NULL);

    //ожидание окончания потока а
    WaitForSingleObject(threads[0], INFINITE);

    //ожидание окончания части потоков c d e
    WaitForSingleObject(semend, INFINITE);
    WaitForSingleObject(semend, INFINITE);
    WaitForSingleObject(semend, INFINITE);

    /////////такт 2
    //разрешение потокам c d e работать дальше
    ReleaseSemaphore(semstart, 3, NULL);

    //создание потока b
    threads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, NULL);

    //ожидание окончания потока с
    WaitForSingleObject(threads[2], INFINITE);
    //ожидание окончания потока b
    WaitForSingleObject(threads[1], INFINITE);

    //ожидание окончания части потоков d e
    WaitForSingleObject(semend, INFINITE);
    WaitForSingleObject(semend, INFINITE);

    //////////такт 3
    //разрешение двум потокам (d e) работать дальше
    ReleaseSemaphore(semstart, 2, NULL);

    //создание потоков g h
    threads[6] = CreateThread(NULL, 0, thread_g, NULL, 0, NULL);
    threads[7] = CreateThread(NULL, 0, thread_h, NULL, 0, NULL);

    //ожидание окончания потока d
    WaitForSingleObject(threads[3], INFINITE);


    //ожидание окончания части потоков e g h
    WaitForSingleObject(semend, INFINITE);
    WaitForSingleObject(semend, INFINITE);
    WaitForSingleObject(semend, INFINITE);

    ///////такт 4
    //разрешение трем потокам работать дальше
    ReleaseSemaphore(semstart, 3, NULL);
    //создание потока f
    threads[5] = CreateThread(NULL, 0, thread_f, NULL, 0, NULL);
    //ожидание окончания потока f
    WaitForSingleObject(threads[5], INFINITE);
    //ожидание окончания потока e
    WaitForSingleObject(threads[4], INFINITE);
    //ожидание окончания потока g
    WaitForSingleObject(threads[6], INFINITE);

    //ожидание окончания части h
    WaitForSingleObject(semend, INFINITE);

    ///////такт 5
    //разрешение h продолжить работу
    ReleaseSemaphore(semstart, 1, NULL);
    //создание потоков k i
    threads[8] = CreateThread(NULL, 0, thread_i, NULL, 0, NULL);
    threads[9] = CreateThread(NULL, 0, thread_k, NULL, 0, NULL);
    //ожидание окончания потока i
    WaitForSingleObject(threads[8], INFINITE);
    //ожидание окончания потока k
    WaitForSingleObject(threads[9], INFINITE);    
    //ожидание окончания потока h
    WaitForSingleObject(threads[7], INFINITE);

    ///////такт 6
    //создание потока m
    threads[10] = CreateThread(NULL, 0, thread_m, NULL, 0, NULL);
    //ожидание окончания потока m
    WaitForSingleObject(threads[10], INFINITE);
}


int lab3_init()
{    
    //инициализация мьютекса
    m = CreateMutex(NULL, false, NULL);
    if (m == NULL) {
        cout << "Create mutex error:" << GetLastError();
        return 1;
    }

    //инициализация семафоров
    for (int i = 0; i < 4; i++) {
        s[i] = CreateSemaphore(NULL, i == 0 ? 1 : 0, 1, NULL);
        if (s[i] == NULL) {
            cout << "CreateSemaphore error: " << GetLastError();
            return 1;
        }
    }

    semstart = CreateSemaphore(NULL, 0, 3, NULL);
    semend = CreateSemaphore(NULL, 0, 3, NULL);

    control_threads();
    
    CloseHandle(m);
    for (int i = 0; i < 4; i++)
    {
        CloseHandle(s[i]);
    }
    CloseHandle(semstart);
    CloseHandle(semend);

    return 0;
}
