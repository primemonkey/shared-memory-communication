#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHM_NAME "/shm_example"
#define SEM_NAME "/sem_example"
#define SIZE     1024

int main() {
    int shm_fd;
    void *ptr;
    sem_t *sem;

    /* open the shared memory segment */
    shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);

    /* map the shared memory segment in the address space of the process */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    /* open the semaphore */
    sem = sem_open(SEM_NAME, 0);

    while (1) {
        /* wait for the semaphore */
        sem_wait(sem);
        printf("Received: %s", (char *)ptr);
    }

    return 0;
}
