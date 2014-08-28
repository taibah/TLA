#include <assert.h>
#include <pthread.h>
#include <cstdlib>
#include <iostream>
using namespace std;

void *mythread(void *arg) {
    int num;
    num = (intptr_t)arg;
    int i =0;
    for(i=0;i<10000;i++)
       cout << num << endl;
    return NULL;

}

int main(int argc, char *argv[])
{

    pthread_t p[100];
    int i;
    int rc;

    cout << "main: begin\n";

    for(i=0; i<100; i++){
        rc = pthread_create(&p[i], NULL, mythread, (void *)i);
        assert(rc == 0);
    }

    for(i=0; i<100; i++){
        rc = pthread_join(p[i], NULL);
        assert(rc == 0);
    }

    cout << "main: end\n";

    return 0;

}
