#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define process for(; !fork(); exit(0))

#define thread(name) pthread_t name;\
    do {\
    void* __inline_thread_func_ ## name(void* nothing) { do

#define exit_thread(name) while(0); return NULL; }\
    pthread_create(& name, NULL, & __inline_thread_func_ ## name, NULL);\
    } while(0)


int main() {
    int i;

    for (i = 0; i < 5; i++) {

        process {
            /* Five processes print this: */
            printf("My pid is %d\n", getpid());
        }

    }

    /* Only the original prints this: */
    printf("And mine is %d\n", getpid());

    /* Threads are slightly different: you provide a variable
     * name to hold the thread structure: */
    thread(my_thread) {
        printf("My thread ID is: %d\n", (unsigned int) pthread_self());

        /* And you have to end with this: */
    } exit_thread(my_thread);

    pthread_join(my_thread, NULL);

    printf("And my thread ID is: %d\n", (unsigned int) pthread_self());
}
