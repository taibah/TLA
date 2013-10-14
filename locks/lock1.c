#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <stdbool.h>

pthread_mutex_t LOCK = PTHREAD_MUTEX_INITIALIZER;
static int critical = 0;
static int req1 = 0, req2 = 0;
static int turn;

void *REQUEST(void *arg) 
{
    int caller = (int *) arg; 
    if(caller == 0 && req1 == 0){
        printf("T1 requested.\n");
        req1 = 1;
        turn = 1 - caller;
    }
    if(caller == 1 && req2 == 0){
        printf("T2 requested\n");
        req2 = 1;
        turn = 1 - caller;
    }
    return NULL;
}
void *ENTER (void *arg) 
{
    int caller = (int *)arg;
    if(caller == 0)
        while(req1 == 1 && (req2 == 0 || turn == 0)){
            printf("T1 in critical section\n");
            critical = 1;
        }
    if(caller == 1)
        while(req2 == 1 && (req1 == 0 || turn == 1)){
            printf("T2 in critical section\n");
            critical = 1;
        }    
    return NULL;
}
void *EXIT (void *arg)
{
    int caller = (int *) arg;
    if(caller == 0 && critical == 1){
        printf("T1 EXISTING\n");
        req1 = 0;
        critical = 0;
    }
    if(caller == 1 && critical == 1){
        printf("T2 EXISTING\n");
        req2 = 0;
        critical = 0;
    }
    return NULL;
}

int main(int argc, char *argv[]) 
{

    pthread_t request[2], enter[2], exit[2];
    int i;
    int rc;

    printf("main: begin\n");

    for(i=0; i<2; i++){
        rc = pthread_create(&request[i], NULL, REQUEST, i); 
        assert(rc == 0);
        rc = pthread_create(&enter[i], NULL, ENTER, i); 
        assert(rc == 0);
        rc = pthread_create(&exit[i], NULL, EXIT, i); 
        assert(rc == 0);
    }

    for(i=0; i<2; i++){
        rc = pthread_join(request[i], NULL);
        assert(rc == 0);
        rc = pthread_join(enter[i], NULL);
        assert(rc == 0);
        rc = pthread_join(exit[i], NULL);
        assert(rc == 0);
    }

    printf("main: end\n");

    return 0;
}
