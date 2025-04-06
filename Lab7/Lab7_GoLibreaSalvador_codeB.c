#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int N;
long double X;
long double *sum;

long double factorial(int n) {
    long double fact = 1.0L;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

void *compute_sin(void *offset);

int main(int argc, char *argv[]) {

    N = atoi(argv[1]);
    X = strtold(argv[2], NULL);
    
    sum = (long double *)calloc(N, sizeof(long double));
    pthread_t *threads = malloc(sizeof(pthread_t) * N);

    for (int i = 0; i < N; i++) {
        int *offset = malloc(sizeof(int));
        *offset = i;
        pthread_create(&threads[i], NULL, compute_sin, (void *)offset);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    long double result = 0;
    for (int i = 0; i < N; i++) {
        result += sum[i];
    }
    printf("Computed sin(x): %.16Lf\n", result);
    printf("sinl(x): %.16Lf\n", sinl(X));
}

void *compute_sin(void *idx) {
    int term_index = *(int *)idx;
    long double partial = 0L;
    long double term = 0L;
    while (1) {
        term = powl(-1.0L, term_index) * powl(X, 2 * term_index + 1) /
               factorial(2 * term_index + 1);

        if (fabsl(term) < 1e-16L) {
            break;
        }

        partial += term;
        term_index += N;
    }
    sum[*(int *)idx] = partial;
}