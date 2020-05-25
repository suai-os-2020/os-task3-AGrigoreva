#include "lab3.h"
#include <iostream>
#include <Windows.h>

#define threadcount 11
HANDLE m;
HANDLE s[4];

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
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "a" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_b(LPVOID t)//id=1
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "b" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_c(LPVOID t)//id=2
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "c" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_d(LPVOID t)//id=3
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "d" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_e(LPVOID t)//id=4
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "e" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_e_s(LPVOID t)//id=4
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[0], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "e" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[1], 1, 0);
    }
    return 0;
}

DWORD WINAPI thread_f_s(LPVOID t)//id=5
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[1], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "f" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[2], 1, 0);
    }
    return 0;
}

DWORD WINAPI thread_g(LPVOID t)//id=6
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "g" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_g_s(LPVOID t)//id=6
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[2], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "g" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[3], 1, 0);
    }
    return 0;
}

DWORD WINAPI thread_h(LPVOID t)//id=7
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "h" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_h_s(LPVOID t)//id=7
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(s[3], INFINITE);
        WaitForSingleObject(m, INFINITE);
        cout << "h" << flush;
        ReleaseMutex(m);
        computation();
        ReleaseSemaphore(s[0], 1, 0);
    }
    return 0;
}

DWORD WINAPI thread_i(LPVOID t)//id=8
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "i" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_k(LPVOID t)//id=9
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "k" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_m(LPVOID t)//id=10
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(m, INFINITE);
        cout << "m" << flush;
        ReleaseMutex(m);
        computation();
    }
    return 0;
}

int lab3_init()
{    
    HANDLE threads[threadcount];
    m = CreateMutex(NULL, false, NULL);
    if (m == NULL) {
        cout << "Create mutex error:" << GetLastError();
        return 1;
    }
    //моменты времени t0 (потоки acde выполняются параллельно)
    threads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, NULL);
    threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, NULL);
    threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, NULL);
    threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, NULL);
    WaitForSingleObject(threads[2], INFINITE);
    WaitForSingleObject(threads[0], INFINITE);
    WaitForSingleObject(threads[3], INFINITE);
    WaitForSingleObject(threads[4], INFINITE);
    CloseHandle(threads[0]);
    CloseHandle(threads[2]);
    CloseHandle(threads[3]);
    CloseHandle(threads[4]);

    //моменты времени t1 (потоки cbde работают параллельно)
    threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, NULL);
    threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, NULL);
    threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, NULL);
    threads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, NULL);
    WaitForSingleObject(threads[2], INFINITE);
    WaitForSingleObject(threads[3], INFINITE);
    WaitForSingleObject(threads[4], INFINITE);
    WaitForSingleObject(threads[1], INFINITE);
    CloseHandle(threads[1]);
    CloseHandle(threads[2]);
    CloseHandle(threads[3]);
    CloseHandle(threads[4]);

    //моменты времени t2 (потоки hgde работают параллельно)
    threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, NULL);
    threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, NULL);
    threads[6] = CreateThread(NULL, 0, thread_g, NULL, 0, NULL);
    threads[7] = CreateThread(NULL, 0, thread_h, NULL, 0, NULL);
    WaitForSingleObject(threads[3], INFINITE);
    WaitForSingleObject(threads[4], INFINITE);
    WaitForSingleObject(threads[6], INFINITE);
    WaitForSingleObject(threads[7], INFINITE);
    CloseHandle(threads[3]);
    CloseHandle(threads[4]);
    CloseHandle(threads[6]);
    CloseHandle(threads[7]);

    //инициализация семафоров
    for (int i = 0; i < 4; i++) {
        s[i] = CreateSemaphore(NULL, i == 0 ? 1 : 0, 1, NULL);
        if (s[i] == NULL) {
            cout << "CreateSemaphore error: " << GetLastError();
            return 1;
        }
    }
    //моменты времени t3 (потоки efgh работают строго в этом порядке)
    threads[4] = CreateThread(NULL, 0, thread_e_s, NULL, 0, NULL);
    threads[5] = CreateThread(NULL, 0, thread_f_s, NULL, 0, NULL);
    threads[6] = CreateThread(NULL, 0, thread_g_s, NULL, 0, NULL);
    threads[7] = CreateThread(NULL, 0, thread_h_s, NULL, 0, NULL);
    WaitForSingleObject(threads[4], INFINITE);
    WaitForSingleObject(threads[5], INFINITE);
    WaitForSingleObject(threads[6], INFINITE);
    WaitForSingleObject(threads[7], INFINITE);
    CloseHandle(threads[4]);
    CloseHandle(threads[5]);
    CloseHandle(threads[6]);
    CloseHandle(threads[7]);
    //моменты времени t4 (потоки hik работают параллельно)
    threads[7] = CreateThread(NULL, 0, thread_h, NULL, 0, NULL);
    threads[8] = CreateThread(NULL, 0, thread_i, NULL, 0, NULL);
    threads[9] = CreateThread(NULL, 0, thread_k, NULL, 0, NULL);
    WaitForSingleObject(threads[7], INFINITE);
    WaitForSingleObject(threads[8], INFINITE);
    WaitForSingleObject(threads[9], INFINITE);
    CloseHandle(threads[7]);
    CloseHandle(threads[8]);
    CloseHandle(threads[9]);

    //мометы времени t5 (работает только поток m)
    threads[10] = CreateThread(NULL, 0, thread_m, NULL, 0, NULL);
    WaitForSingleObject(threads[10], INFINITE);
    CloseHandle(threads[10]);

    CloseHandle(m);
    for (int i = 0; i < 4; i++)
    {
        CloseHandle(s[i]);
    }

    return 0;
}
