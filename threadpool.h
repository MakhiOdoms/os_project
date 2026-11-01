#ifndef THREADPOOL_H
#define THREADPOOL_H

void pool_init(void);

int pool_submit(void (*somefunction)(void *), void *p);

void pool_shutdown(void);

#endif
