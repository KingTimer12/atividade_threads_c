#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define TAM_VETOR 4000000

int vetor1[TAM_VETOR], vetor2[TAM_VETOR];
int resultado = 0;
pthread_mutex_t mutex;

int produto_vetorial(int *inicio, int *fim)
{
    int soma = 0;
    for (int i = *inicio; i < *fim; i++)
    {
        soma += vetor1[i] * vetor2[i]; // 1 * 1...
    }
    return soma;
}

void iniciar_vetores()
{
    for (int i = 0; i < TAM_VETOR; i++)
    {
        vetor1[i] = 1;
        vetor2[i] = 1;
    }
}

void esperar_threads(pthread_t *threads)
{
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
}

void *soma(void *arg)
{
    int id = *(int *)arg;
    int intervalo = TAM_VETOR / NUM_THREADS;
    int inicio = id * intervalo;
    int fim = inicio + intervalo; // mesma coisa de (id+1) * intervalo; esse cálculo novo foi gerado pelo copilot enquanto eu escrevia xD

    resultado += produto_vetorial(&inicio, &fim);
}

int main()
{
    iniciar_vetores();
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_THREADS];
    int id[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        id[i] = i;
        pthread_create(&threads[i], NULL, soma, &id[i]);
    }
    esperar_threads(threads);
    pthread_mutex_destroy(&mutex);

    printf("Resultado: %d\n", resultado);

    return 0;
}