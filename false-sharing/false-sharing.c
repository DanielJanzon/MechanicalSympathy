#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

uint64_t private_value1 __attribute__((aligned(ALIGNMENT)));
uint64_t private_value2 __attribute__((aligned(ALIGNMENT)));

void *update_private_value1(void *arg)
{
  for(uint64_t i=0; i<1000000000LLU; i++) {
    private_value1++;
  }
}

void *update_private_value2(void *arg)
{
  for(uint64_t i=0; i<1000000000LLU; i++) {
    private_value2++;
  }
}

int main()
{
  pthread_t thread1, thread2;

  struct timeval start, stop;
  gettimeofday(&start, NULL);
  pthread_create(&thread1, NULL, update_private_value1, NULL);
  pthread_create(&thread2, NULL, update_private_value2, NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  gettimeofday(&stop, NULL);

  printf("completed in %lld us\n", stop.tv_sec*1000000LLU+stop.tv_usec - (start.tv_sec*1000000LLU+start.tv_usec));

  printf("%llu & %llu\n", (unsigned long long)private_value1, (unsigned long long)private_value2);
}

