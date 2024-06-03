#include<semaphore.h>
#include "philo_bonus.h"
#include <pthread.h>
#include <stdio.h>
#include <libc.h>

int main()
{
	sem_t *sem = sem_open("/semjdg", O_CREAT, 0644, 0);
	if(sem == SEM_FAILED)
		write(2, RED"sem_open faild\n"RESET, 15);
int i = fork();
if (i == 0) {
	for (int h = 0; h < 1000000000; h++)
		;
	sem_post(sem);
	exit(0);
}
	puts("jdgs");
	sem_wait(sem);
	printf("hnaaa\n");
	sem_close(sem);
	sem_unlink("/semjdg");
}
