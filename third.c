#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int semid;
  char name[] = "third.c"; // для имени файла, через нее будем генерировать ключ
  key_t key;
  struct sembuf mybuf; // sembuf - тип данных; структура для работы над семафором
  if ((key == ftok(name, 0)) < 0) {
    printf("Can\'t create key\n");
    exit(-1);
  }
  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) { // проверяем, создали ли семафор
    printf("Can\'t create semid\n");
    exit(-2);
  }
  mybuf.sem_flg = 0; // флаг
  mybuf.sem_op = 1; //  наша операция; т.к. то A и т.к. 1, то A(S, 1);
  mybuf.sem_num = 0; //  индекс места в массиве с чем мы хотим работать
  if (semop(semid, &mybuf, 1) < 0) { // берет диск., указатель на буфер, кол-во семафоров, с которыми будем работать; ф-я берет структуру и выполняет над ней операцию
    printf("Error\n");
    exit(-3);
  }
  printf("Set condition\n");
  return 0;
}
