#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

vector<char> messages;
int count_messages, delay;
bool t = true;

DWORD WINAPI Receive_f_p(LPVOID param) {
    HANDLE EventA = OpenEvent(SYNCHRONIZE, FALSE, TEXT("EventA"));
    HANDLE EventB = OpenEvent(SYNCHRONIZE, FALSE, TEXT("EventB"));
    HANDLE events[] = { EventA, EventB };
    if (!EventA || !EventB) { cerr << "Error"; return 0; }


    while (t) {
        DWORD waitCD = WaitForMultipleObjects(2, events, FALSE, 100);
        if (waitCD == WAIT_OBJECT_0) {
            messages.push_back('A');
        }
        else if (waitCD == WAIT_OBJECT_0 + 1) {
            messages.push_back('B');
        }
    }

    CloseHandle(EventA);
    CloseHandle(EventB);
    CloseHandle(events);

    return 1;
}

int main(int argc, char* argv[]) {
    //подключаем обьекты синхронизации
    HANDLE EventC = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("EventC"));
    HANDLE EventD = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("EventD"));
    HANDLE ChildMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, TEXT("ChildMutex"));
    HANDLE EndChild = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("EndChild"));

    WaitForSingleObject(ChildMutex, INFINITE); //подключаемся к мьютексу
    cout << "I AM CHILD" << '\n';
    HANDLE RecieveThread = CreateThread(NULL, 0, Receive_f_p, NULL, 0, NULL); // начинаем прием 

    //устанавливаем задержку и количество сообщений
    count_messages = atoi(argv[1]);
    delay = atoi(argv[2]);



    //генератор и отправка сообщений
    srand(time(0));
    int random_number;
    for (int i = 0; i < count_messages; ++i) {
        random_number = rand() % 2;
        if (random_number == 0) { SetEvent(EventC); cout << "Sent: C" << '\n'; }
        else { SetEvent(EventD); cout << "Sent: D" << '\n'; }
        Sleep(delay);
    }

    t = false;

    
    
    WaitForSingleObject(RecieveThread, INFINITE); //дожидаемся окончания приема
    CloseHandle(RecieveThread); //закрываем поток приема
    ReleaseMutex(ChildMutex); //отпускаем мьютекс
    
    //Выводим полученное
    cout << "Received: " << '\n';
    for (char k : messages) cout << k << '\n';
    SetEvent(EndChild);
    CloseHandle(ChildMutex);
    CloseHandle(EventD);
    CloseHandle(EventC);
    CloseHandle(EndChild);

    getchar();
    return 0;
}


