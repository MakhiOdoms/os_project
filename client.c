#include <stdio.h>
#include <unistd.h>

#include "threadpool.h"

void task_function(void *arg)
{
    int task_num = *(int *)arg;

    printf("Executing Task %d\n", task_num);

    sleep(2);

    printf("Finished Task %d\n", task_num);
}

int main()
{
    pool_init();

    int task_ids[5];

    for (int i = 0; i < 5; i++)
    {
        task_ids[i] = i + 1;
        pool_submit(task_function, &task_ids[i]);
    }

    sleep(10);

    pool_shutdown();

    return 0;
}