#include <stdio.h>
#include <assert.h>
#include <pthread.h>

void *mythread(void *arg) {

    int x = (int)arg;

    printf("%d\n", x);
    return NULL;

}

int main(int argc, char *argv[]) 
{

    pthread_t p[10];
    int i;
    int rc;

    printf("main: begin\n");

    for(i=0; i<10; i++){
        rc = pthread_create(&p[i], NULL, mythread, i); 
        assert(rc == 0);
    }

    for(i=0; i<10; i++){
        rc = pthread_join(p[i], NULL);
        assert(rc == 0);
    }

    printf("main: end\n");

    return 0;

}
