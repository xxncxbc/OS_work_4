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

DWORD WINAPI Receive_f_ch(LPVOID param) {
    HANDLE EventC = OpenEvent(SYNCHRONIZE, FALSE, TEXT("EventC"));
    HANDLE EventD = OpenEvent(SYNCHRONIZE, FALSE, TEXT("EventD"));
    HANDLE events[] = { EventC, EventD };
    if (!EventC || !EventD) { cerr << "Error"; return 0; }
    
    
    while (t) {
        DWORD waitCD = WaitForMultipleObjects(2, events, FALSE, 100);
        if (waitCD == WAIT_OBJECT_0) {
            messages.push_back('C');
        }
        else if(waitCD == WAIT_OBJECT_0 + 1) {
            messages.push_back('D');
        }
    }

    CloseHandle(EventC);
    CloseHandle(EventD);
    CloseHandle(events);

    return 1;
}

int main(int argc, char * argv[]) {
    //подключаем обьекты синхронизации
    HANDLE EventA = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("EventA"));
    HANDLE EventB = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("EventB"));
    HANDLE ParentSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("ParentSem"));
    HANDLE EndParent = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("EndParent"));

    WaitForSingleObject(ParentSem, INFINITE); //подключаемся к семафору

    cout << "I AM PARENT" << '\n';
    HANDLE RecieveThread = CreateThread(NULL, 0, Receive_f_ch, NULL, 0, NULL); // начинаем прием 

    //устанавливаем задержку и количество сообщений
    count_messages = atoi(argv[1]);
    delay = atoi(argv[2]);

   

    //генератор и отправка сообщений
    srand(time(0));
    int random_number;
    for (int i = 0; i < count_messages; ++i) {
        random_number = rand() % 2;
        if (random_number == 0) { SetEvent(EventA); cout << "Sent: A" << '\n'; }
        else { SetEvent(EventB); cout << "Sent: B" << '\n'; }
        Sleep(delay);
    }

    t = false;

    

    
    WaitForSingleObject(RecieveThread, INFINITE); //дожидаемся окончания приема
    ReleaseSemaphore(ParentSem, 1, NULL); //отпускаем семафор

    //Выводим полученное
    cout << "Received: " << '\n'; 
    for (char k : messages) cout << k << '\n';

    SetEvent(EndParent);

    
    CloseHandle(ParentSem);
    CloseHandle(EventA);
    CloseHandle(EventB);
    CloseHandle(EndParent);
    getchar();
    return 0;
}


