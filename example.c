#include <stdio.h>
#include <sys/wait.h>

#include "inpar.h"

int main() {
    pid_t child = proc {
        printf("My pid is %d\n", getpid());
    } endproc;

    wait(NULL);
    
    printf("His pid was %d, mine is %d\n", child, getpid());
    
    pthread_t foo = thread {
        printf("My thread ID is %u\n", (unsigned int) pthread_self());
    } endthread;
    
    pthread_join(foo, NULL);
    
    printf("Joined %u. By the way, my ID is %u\n",
           (unsigned int) foo,
           (unsigned int) pthread_self()
    );
}
