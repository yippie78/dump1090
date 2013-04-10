//
// This file provides basic Windows implementation of Linus specific functions
// used in the dump1090 project. This allows dump1090 to be compiled and debugged 
// using Microsoft Visual C++ 6.0
//
// ote that not all functions actually provide equivalent functionality to their 
// Linux equivalents. They are simply stubs to allow the project to compile.
//
#include "dump1090.h"

void usleep(unsigned ulSleep)
  {Sleep(ulSleep/1000);} 

int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
  SYSTEMTIME stSystemTime;
  GetLocalTime(&stSystemTime);

  tv->tv_sec  = stSystemTime.wSecond + (60 * (stSystemTime.wMinute + (60 * stSystemTime.wHour)));
  tv->tv_usec = stSystemTime.wMilliseconds * 1000;

  return 0;
  } 

int round(double x)
  {return (int) x;} 

int open (const char *pathname, int flags)
  {
  FILE * hFile = NULL;

  if (flags == O_RDONLY)
    {hFile = fopen(pathname,"rb");}

  if (hFile == 0)
    {return -1;}

  return (int) (hFile);
  } 

ssize_t read (int fd, void *buf, size_t count)
  {
  FILE * hFile;
  if (hFile = (FILE *) fd)
    {return fread(buf, 1, count, hFile);}

  return 0;
  } 

ssize_t write(int fd, const void *buf, size_t count)
  {return 0;} 

int     close(int fd)
  {return 0;} 

uint64_t strtoll(const char *var1, void * var2, UINT32 var3)
  {return 0;}

int anetNonBlock(char *err, int fd)
  {return 0;}  

int anetTcpServer(char *err, int port, char *bindaddr)
  {return -1;}  

int anetSetSendBuffer(char *err, int fd, int buffsize)
  {return 0;}  

int anetTcpAccept(char *err, int serversock, char *ip, int *port)
  {return -1;}  

//
// PThread Functions
//
int pthread_create (pthread_t * tid,
                            const pthread_attr_t * attr,
                            void *(PTW32_CDECL *start) (void *),
                            void *arg)
  {
  tid->p = CreateThread(NULL, 1000, (LPTHREAD_START_ROUTINE) start, NULL, 0, (unsigned long*) &tid->x);

  return (tid->x);
  }

//
// Mutex Functions
//
int pthread_mutex_init (pthread_mutex_t * mutex, const pthread_mutexattr_t * attr)
  {
  *mutex = CreateMutex(NULL, FALSE, NULL);
  return ((int) *mutex);
  }

int pthread_mutex_lock (pthread_mutex_t * mutex)
  {return WaitForSingleObject(*mutex, INFINITE);}

int pthread_mutex_unlock (pthread_mutex_t * mutex)
  {return ReleaseMutex(*mutex);}

//
// Condition Variable Functions
//
int pthread_cond_init (pthread_cond_t * cond, const pthread_condattr_t * attr)
  {
  *cond = CreateEvent(NULL, FALSE, FALSE, NULL);
  return ((int) *cond);
  }

int pthread_cond_wait (pthread_cond_t * cond, pthread_mutex_t * mutex)
  {
  ReleaseMutex(*mutex);
  WaitForSingleObject(*cond, INFINITE);

  //if (ReleaseMutex(*mutex))
  //  {return WaitForSingleObject(*cond, INFINITE);}
    
  return 0;
  }

int pthread_cond_signal (pthread_cond_t * cond)
  {return SetEvent(*cond);}
