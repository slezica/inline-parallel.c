#ifndef _INPAR_H_
#define _INPAR_H_

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

/* NOTE this header is GCC-only, as far as I know */

/* Instead of escaping newlines in the macros below, I used the comment
 * trick you'll see so that the output of gcc -E -CC is readable. */

#define proc ({ /*
*/  pid_t _inpar_pid_temp; /*
*/  for (_inpar_pid_temp = fork(); !_inpar_pid_temp; exit(0))

#define endproc _inpar_pid_temp; })
/* Examples:
 * 
 * You can fire an anonimous process:
 *   proc { 
 *       (this code runs in another process)
 *   } endproc;
 * 
 * Or, you can assign the child's pid to a variable:
 *   pid_t pid = proc { 
 *       (this code runs in another process)
 * 
 *   } endproc;
 * 
 * (pid holds the return of fork() for the parent)
 * 
 */
 
#define thread pthread_t _current_background_thread_ = do { /*
*/  pthread_t _inpar_thread_temp; /*
*/  auto void* _inpar_thread_func(void* nothing); /*

*/  pthread_create(&_inpar_thread_temp, NULL, &_inpar_thread_func, NULL);/*
*/  void* _inpar_thread_func(void* nothing)

#define endthread } while (0)

#define wait_for_completion pthread_join(_current_background_thread_)

#endif
