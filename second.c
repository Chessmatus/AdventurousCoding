// Семафор Дейкстры S - целая неотр. разделяемая чиселка
// инициализируем любым неопределенным значением
// P(S): пока S = 0, блок.; в прот. случае S -= 1
// V(S) : S += 1
// mut_ex = 1
// empty = N ; N - размер буфера
// full = 0
// Pr.                                                            Cons.
// 
// while (1) {                                                    while (1) {
//                                                                  P(full); // проверяем есть ли что читать
//                                                                  P(mut_ex);
//                                                                  get_item();
//  produce_item();                                                 V(mut_ex);
//  P(empty); // проверяем есть ли место записывать                 V(empty)
//  P(mut_ex); // занулили, чтобы не читали одновременно            consume_item();
//  put_item(); // кладем инфу в буфер                            }
//  V(mut_ex);
//  V(full);
// }                                                               

// Операции P и V атомарные, если один процесс их вызвал, другой не может вызвать его

// Модифицируем модель для случая более одного элемента памяти
// A(S, n): S += n
// D(S, n): if S == 0, blocks; otherwise S -= n
// Z(S): waiting until S != 0

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int semid;
  char name[] = "third.c"; // // для имени файла, через нее будем генерировать ключ; имя обяз. существующего из текущей дир.
  key_t key;
  struct sembuf mybuf;  // sembuf - тип данных; структура для работы над семафором
  if((key = ftok(name, 0)) < 0) {
    printf("Can not create key\n");
    exit(-1);
  }
  if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {  // проверяем, создали ли семафор
    printf("Can not create semid\n");
    exit(-2);
  }
  mybuf.sem_flg = 0;
  mybuf.sem_op = -1; //  наша операция; т.к. -, то D и т.к. 1, то D(S, 1);
  mybuf.sem_num = 0; //  индекс места в массиве с чем мы хотим работать
  if(semop(semid, &mybuf, 1) < 0) { // берет диск., указатель на буфер, кол-во семафоров, с которыми будем работать; ф-я берет структуру и выполняет над ней операцию
    printf("Can not create semop\n");
    exit(-3);
  }
  printf("Condition is present\n");
  return 0;
}
