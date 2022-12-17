#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *p) {
  pthread_t mythreadid;
  mythreadid = pthread_self();
  a++;
  printf("My id is %ld, a is %d\n", mythreadid, a);
  return NULL;
}

int main() {
  pthread_t pthid, mypthid;
  int res;
  res = pthread_create(&pthid, (pthread_attr_t*)NULL, mythread, NULL);
  if (res != 0) {
    printf("thread can\'t create\n");
    exit(-1);
  }
  printf("thread was created, th id is %ld\n", pthid);
  mypthid = pthread_self();
  a += 1;
  printf("My id is %ld, a is %d\n", mypthid, a);
  pthread_join(pthid, (void**)NULL);
  return 0; 
}
