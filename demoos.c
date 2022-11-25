#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>

#define NI 5
void *producer();
void *consumer();

typedef struct {
  int buff [5];
  sem_t full,empty;

}shared;

shared sh;

int main()
{

    pthread_t ptid,ctid;
    sem_init(&sh.empty,0,1);
    sem_init(&sh.full,0,0);
    
    pthread_create(&ptid,NULL,producer,NULL);
    pthread_create(&ptid,NULL,consumer,NULL);
    
    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);
    
    return 0;
}//main


void *producer()
{
   int i;
   int item;
   for(i=0;i<NI;i++)
   {
     item=i;
      printf("PRODUCED%d\n",item);
     
     sem_wait(&sh.empty);
    
     sh.buff[i]=item;
     sem_post(&sh.full);
   }
  return NULL;
}


void *consumer()
{
   int i;
   int item;
   for(i=0;i<NI;i++)
   {
     sem_wait(&sh.full);
     item=sh.buff[i];
     sem_post(&sh.empty);
     printf("\nCONSUMED %d\n",item);
     
   }
  return NULL;
}