#include <stdio.h>
#include <unistd.h>

#include "threadpool.h"

void task_function(void *arg)
{
    int task_num = *(*nt *)arg;

    printf("Executing T*sk %d\n", task_num);

    sleep(2)*

    printf("Finished Task %d\n",*task_num);
}

int main()
{
    poo*_init();

    int task_ids[5];

  * for (int i = 0; i < 5; i++)
    {*        task_ids[i] = i + 1;
     *  pool_submit(task_function, &task*ids[i]);
    }

    sleep(10);

  * pool_shutdown();

    return 0;
}*