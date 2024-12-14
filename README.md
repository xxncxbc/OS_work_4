4.12. Написать программы для консольного процесса Boss и консольных процессов Parent, Child.  Для моделирования передачи сообщений ввести специальные события(c автоматическим сбросом), которые обозначают «А» , «B» «C» , «D»   и два события (ручной сброс) конца сеанса для процессов Parent и Child. 
Принимать сообщение можно только  от ОДНОГО АКТИВНОГО процесса Child(использовать мьютекс)  и ОДНОГО АКТИВНОГО процесса Parent(использовать семафор), передача остальных сообщений от других процессов должна временно блокироваться (находиться в режиме ожидания).
Процесс Boss:
Инициализация объектов синхронизации;
запрашивает у пользователя количество процессов Parent и количество процессов Child, которые он должен запустить; 
запрашивает кол-во сообщений отправленных\полученных Parent и Child;
ввести время задержки работы процессов К;
запускает заданное количество процессов Parent, Child;
принимает от каждого процесса Parent, Child сообщения о завершении работы, выводит сообщения и кто его отправил  на консоль в одной строке. 
завершает свою работу.
Процесс Parent: 
синхронизировать работу процессов Parent с помощью семафора
создать новый  поток для принятия сообщений от процесса Сhild
передачу сообщений реализовать с помощью событий
генерирует случайное сообщение состоящее из «А» или «B»   и передает их (по одному через определенный промежуток времени К) процессу Child;
отправляет сообщение Boss о завершении работы и завершает свою работу.
принимает от процесса Child сообщение (отдельный поток);

Процесс Child:
синхронизировать работу процессов Child с помощью мьютекса
передачу сообщений реализовать с помощью событий
создать новый  поток для принятия сообщений от процесса Parent
генерирует случайное сообщение из «C» или «D»   и передает их (по одному через определенный промежуток времени К) процессу Parent;
принимает от процесса Parent сообщение (отдельный поток);
отправляет сообщение Boss о завершении работы и завершает свою работу.
