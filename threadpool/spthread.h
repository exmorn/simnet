//************************************************
// this code come form SPServer. SPServer is a high concurrency server framework library written on C++
// url: code.google.com/p/spserver
//************************************************
#ifndef __SPTHREAD_H__
#define __SPTHREAD_H__
#include<windows.h>
#ifndef WIN32

/// pthread

#include <pthread.h>
#include <unistd.h>

typedef void * sp_thread_result_t;
typedef pthread_mutex_t sp_thread_mutex_t;
typedef pthread_cond_t  sp_thread_cond_t;
typedef pthread_t       sp_thread_t;
typedef pthread_attr_t  sp_thread_attr_t;

#define sp_thread_mutex_init(m,a)   pthread_mutex_init(m,a)
#define sp_thread_mutex_destroy(m)  pthread_mutex_destroy(m)
#define sp_thread_mutex_lock(m)     pthread_mutex_lock(m)
#define sp_thread_mutex_unlock(m)   pthread_mutex_unlock(m)

#define sp_thread_cond_init(c,a)    pthread_cond_init(c,a)
#define sp_thread_cond_destroy(c)   pthread_cond_destroy(c)
#define sp_thread_cond_wait(c,m)    pthread_cond_wait(c,m)
#define sp_thread_cond_signal(c)    pthread_cond_signal(c)
#define sp_thread_cond_broadcast(c)	pthread_cond_broadcast(c)

#define sp_thread_attr_init(a)        pthread_attr_init(a)
#define sp_thread_attr_setdetachstate pthread_attr_setdetachstate
#define SP_THREAD_CREATE_DETACHED     PTHREAD_CREATE_DETACHED

#define sp_thread_self    pthread_self
#define sp_thread_create  pthread_create

#define sp_thread_exit		pthread_exit
#define sp_thread_join		pthread_join

#define SP_THREAD_CALL
typedef sp_thread_result_t ( * sp_thread_func_t )( void * args );

#define sp_sleep(x) sleep(x)

#else ///////////////////////////////////////////////////////////////////////

// win32 thread
#include <windows.h>
#include <process.h>
typedef unsigned sp_thread_t;
typedef unsigned sp_thread_result_t;
#define SP_THREAD_CALL __stdcall
typedef sp_thread_result_t ( __stdcall * sp_thread_func_t )( void * args );

typedef HANDLE  sp_thread_mutex_t;
typedef HANDLE  sp_thread_cond_t;
typedef DWORD   sp_thread_attr_t;

#define SP_THREAD_CREATE_DETACHED 1
#define sp_sleep(x) Sleep(1000*x)

int sp_thread_mutex_init( sp_thread_mutex_t * mutex, void * attr );

int sp_thread_mutex_destroy( sp_thread_mutex_t * mutex );

int sp_thread_mutex_lock( sp_thread_mutex_t * mutex );

int sp_thread_mutex_unlock( sp_thread_mutex_t * mutex );

int sp_thread_cond_init( sp_thread_cond_t * cond, void * attr );

int sp_thread_cond_destroy( sp_thread_cond_t * cond );

/*
Caller MUST be holding the mutex lock; the
lock is released and the caller is blocked waiting
on 'cond'. When 'cond' is signaled, the mutex
is re-acquired before returning to the caller.
*/
int sp_thread_cond_wait( sp_thread_cond_t * cond, sp_thread_mutex_t * mutex );

int sp_thread_cond_signal( sp_thread_cond_t * cond );

sp_thread_t sp_thread_self();

int sp_thread_attr_init( sp_thread_attr_t * attr );

int sp_thread_attr_setdetachstate( sp_thread_attr_t * attr, int detachstate );

int sp_thread_create( sp_thread_t * thread, sp_thread_attr_t * attr,
		sp_thread_func_t myfunc, void * args );
void sp_thread_exit(DWORD dwExitCode);
int sp_thread_cond_broadcast(sp_thread_cond_t );

#endif

#endif
