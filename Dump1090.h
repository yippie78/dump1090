//
// This file provides basic Windows implementation of Linus specific functions
// used in the dump1090 project. This allows dump1090 to be compiled and debugged 
// using Microsoft Visual C++ 6.0
//
// ote that not all functions actually provide equivalent functionality to their 
// Linux equivalents. They are simply stubs to allow the project to compile.
//
#ifndef __DUMP1090_H
#define __DUMP1090_H

#include <windows.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

#define M_PI         3.14159265358
#define STDIN_FILENO 0x1
#define ANET_ERR_LEN 256

typedef UCHAR   uint8_t;
typedef USHORT  uint16_t;
typedef UINT32  uint32_t;
typedef UINT64  uint64_t;
typedef INT32   ssize_t;
typedef UINT32  mode_t;
//
// Generic handle type - intended to extend uniqueness beyond that available 
// with a simple pointer. It should scale for either IA-32 or IA-64.
//
typedef struct {
    void * p;                   // Pointer to actual object
    unsigned int x;             // Extra information - reuse count etc 
} ptw32_handle_t;

typedef        ptw32_handle_t         pthread_t;
typedef struct pthread_attr_t_      * pthread_attr_t;
typedef struct pthread_mutex_t_     * pthread_mutex_t;
typedef struct pthread_cond_t_      * pthread_cond_t;
typedef struct pthread_mutexattr_t_ * pthread_mutexattr_t;
typedef struct pthread_condattr_t_  * pthread_condattr_t;

void    usleep(unsigned ulSleep); 
int     gettimeofday(struct timeval *tv, struct timezone *tz);
int     round(double x);
int     open (const char *pathname, int flags);
ssize_t read (int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count); 
int     close(int fd);
#define snprintf _snprintf
uint64_t strtoll(const char *, void *, UINT32);

int anetTcpServer(char *err, int port, char *bindaddr);
int anetNonBlock(char *err, int fd);
int anetTcpAccept(char *err, int serversock, char *ip, int *port);
int anetSetSendBuffer(char *err, int fd, int buffsize);

//
// PThread Functions
//
#define PTW32_CDECL __cdecl
int pthread_create (pthread_t * tid, const pthread_attr_t * attr, void *(PTW32_CDECL *start) (void *), void *arg);

//
// Mutex Functions
//
int pthread_mutex_init   (pthread_mutex_t * mutex, const pthread_mutexattr_t * attr);
int pthread_mutex_lock   (pthread_mutex_t * mutex);
int pthread_mutex_unlock (pthread_mutex_t * mutex);

//
// Condition Variable Functions
//
int pthread_cond_init   (pthread_cond_t * cond,const pthread_condattr_t * attr);
int pthread_cond_wait   (pthread_cond_t * cond, pthread_mutex_t * mutex);
int pthread_cond_signal (pthread_cond_t * cond);

#ifdef __cplusplus
}
#endif

#endif // __DUMP1090_H
