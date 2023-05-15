#ifndef _SINGLETON_H_
#define _SINGLETON_H_


/*
** Disabling of creating new instances and accessing and modification data from reference and
*/
typedef struct Singleton Singleton;


const Singleton * 
singleton(void);


const char *
singleton_name(const Singleton * self);


int 
singleton_age(const Singleton * self);


#endif
