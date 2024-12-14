#include <iostream>
#include <windows.h>
#include <vector>
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
    

}

