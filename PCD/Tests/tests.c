#include <stdio.h>
#include <omp.h>
#include <pthread.h>

void *fun_t (void *arg) {
    printf("Sanfoundry\n");
    pthread_exit(NULL);
}

int main () {
    pthread_t pt;
    void *res_t;

    if (pthread_create(&pt, NULL, fun_t, NULL) != 0)
        perror("pthread_create");
    
    /*if (pthread_join(pt, &res_t) != 0)
        perror("pthread_join");

    printf("Linux\n");*/
    return 0;
}