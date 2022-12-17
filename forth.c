#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LAST_MESSAGE 255

int main() {
  int msqid;
  char_name = "forth.c";
  key_t key;
  int len;
  struct mymsgbuf {
    long mtype;
    char mtext[81]; 
  } mybuf;
  if (key = ftok(name, 0) < 0) {
    printf("Error\n");
    exit(-1);
  }
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Error\n");
    exit(-2);
  }
  for (int i = 0; i <= s; i++) {
    mybuf.mtype = 1;
    strcpy(mybuf.mtext, "I am slave\n");
    len = strlen(mybuf.mtext) + 1;
    if (msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0) < 0) {
      printf("Error\n");
      exit(-3);
    }
  }
  mybuf.mtype = LAST_MESSAGE;
  len = 0;
  if (msgsnd(msqid, (struct msgbuf*)&mybuf, len, 0) < 0) {
    printf("Error\n");
    exit(-4);
  }
  return 0;
}
