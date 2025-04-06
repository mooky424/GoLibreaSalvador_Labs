#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *arr;

void *run(void *idx);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Error: No arguments provided.\n");
        return -1;
    }

    arr = (int *)malloc((argc - 1) * sizeof(int));
    pthread_t *threads = malloc(sizeof(pthread_t) * (argc - 1));

    for (int i = 0; i < argc - 1; i++) {
        arr[i] = atoi(argv[i + 1]);
        int *idx = malloc(sizeof(int));
        *idx = i;
        pthread_create(&threads[i], NULL, run, (void *)idx);
    }

    for (int i = 0; i < argc - 1; i++) {
        pthread_join(threads[i], NULL);
    }

    free(arr);
    free(threads);
}

void *run(void *idx) {
    int x = *((int *)idx);
    int old_val = arr[x];

    if (x % 2 == 0) {
        arr[x] = arr[x] * arr[x] * arr[x];
    } else {
        arr[x] = -arr[x];
    }

    printf("arr[%d](%d) has been replaced with arr[%d](%d)\n", x, old_val, x,
           arr[x]);

    free(idx);
    pthread_exit(NULL);
}