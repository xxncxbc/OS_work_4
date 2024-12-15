#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;

int main(){
    //инициализируем обьекты синхронизации
    HANDLE EventA = CreateEvent(NULL, FALSE, FALSE, TEXT("EventA"));
    HANDLE EventB = CreateEvent(NULL, FALSE, FALSE, TEXT("EventB"));
    HANDLE EventC = CreateEvent(NULL, FALSE, FALSE, TEXT("EventC"));
    HANDLE EventD = CreateEvent(NULL, FALSE, FALSE, TEXT("EventD"));
    HANDLE EndParent = CreateEvent(NULL, TRUE, FALSE, TEXT("EndParent"));
    HANDLE EndChild = CreateEvent(NULL, TRUE, FALSE, TEXT("EndChild"));
    HANDLE ParentSem = CreateSemaphore(NULL, 1, 1, TEXT("ParentSem"));
    HANDLE ChildMutex = CreateMutex(NULL, FALSE, TEXT("ChildMutex"));

    vector<HANDLE> parents, children;

    int proc_num, mess_num, delay;
    cout << "Enter number of procceses, messages and delay in ms: ";
    cin >> proc_num >> mess_num >> delay;

    wstring PArg = L"Parent.exe " + to_wstring(mess_num) + L" " + to_wstring(delay); //аргумент для запуска Parent
    wstring CArg = L"Child.exe " + to_wstring(mess_num) + L" " + to_wstring(delay); //аргуменет для запуска Children

    for (int i = 0; i < proc_num; ++i) { //запускаем все parent и children
        STARTUPINFO si1 = { sizeof(si1) };
        PROCESS_INFORMATION pi1;
        STARTUPINFO si2 = { sizeof(si2) };
        PROCESS_INFORMATION pi2;
        CreateProcess(NULL, &PArg[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1);
        CreateProcess(NULL, &CArg[0], NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2);
        parents.push_back(pi1.hProcess);
        children.push_back(pi2.hProcess);
        CloseHandle(pi1.hThread);
        CloseHandle(pi2.hThread);
    }



    for (int i = 0; i < proc_num; ++i) { //отслеживаем окончание процессов
        WaitForSingleObject(EndParent, INFINITE);
        WaitForSingleObject(EndChild, INFINITE);
        cout << "Parent #" << i << " is done!" << endl;
        cout << "Child #" << i << " is done!" << endl;
        ResetEvent(EndChild);
        ResetEvent(EndParent);
    }
    
    //закрываем все дескрипторы
    for (HANDLE x : parents) CloseHandle(x);
    for (HANDLE x : children) CloseHandle(x);
    CloseHandle(EventA);
    CloseHandle(EventB);
    CloseHandle(EventC);
    CloseHandle(EventD);
    CloseHandle(EndParent);
    CloseHandle(EndChild);
    CloseHandle(ParentSem);
    CloseHandle(ChildMutex);
}

