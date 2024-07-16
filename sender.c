#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>

#define SHM_NAME "/shm_example"
#define SEM_NAME "/sem_example"
#define SIZE     1024

int main() {
    int shm_fd;
    void *ptr;
    sem_t *sem;

    /* create the shared memory segment */
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory segment */
    ftruncate(shm_fd, SIZE);

    /* map the shared memory segment in the address space of the process */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    /* create the semaphore */
    sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);

    while (1) {
        printf("Enter a message: ");
        fgets(ptr, SIZE, stdin);
        /* signal the semaphore - increment its value by one */
        sem_post(sem);
    }

    return 0;
}
