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
    wstring Arg = L"Parent.exe " + to_wstring(mess_num) + L" " + to_wstring(delay); //аргумент для запуска Parent
}

