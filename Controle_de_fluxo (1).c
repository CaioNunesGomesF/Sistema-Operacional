#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // Incluído para usar wait()
#include <unistd.h>

#define INTERVALO 10    // Intervalo de números para simulação
#define REPETICOES 1000 // Número de vezes que tudo será repetido

// Função que calcula a soma dos números pares em um intervalo
void *calcula_carros(void *arg) {
  int soma = 0;
  for (int i = 0; i <= INTERVALO; i++) {
    if (i % 2 == 0) {
      soma += i;
    }
  }
  printf("Soma dos números pares (Carros no cruzamento): %d\n", soma);
  return NULL;
}

// Função que calcula o fatorial de um número (simulando a capacidade do
// cruzamento)
void *calcula_capacidade(void *arg) {
  int n = 5; // Número representando a capacidade máxima
  long long fatorial = 1;
  for (int i = 1; i <= n; i++) {
    fatorial *= i;
  }
  printf("Fatorial da capacidade (Cruzamento operando dentro da capacidade): "
         "%lld\n",
         fatorial);
  return NULL;
}

int main() {
  for (int i = 0; i < REPETICOES; i++) {
    pid_t pid1, pid2;
    pthread_t thread1_1, thread1_2, thread2_1, thread2_2;

    // Criação do primeiro processo (Cruzamento 1)
    pid1 = fork();
    if (pid1 == 0) { // Processo filho (Cruzamento 1)
      pthread_create(&thread1_1, NULL, calcula_carros,
                     NULL); // Thread 1 (Cruzamento 1)
      pthread_create(&thread1_2, NULL, calcula_capacidade,
                     NULL); // Thread 2 (Cruzamento 1)

      pthread_join(thread1_1, NULL);
      pthread_join(thread1_2, NULL);
      exit(0);
    } else if (pid1 < 0) {
      perror("Erro ao criar o processo 1");
      exit(1);
    }

    // Criação do segundo processo (Cruzamento 2)
    pid2 = fork();
    if (pid2 == 0) { // Processo filho (Cruzamento 2)
      pthread_create(&thread2_1, NULL, calcula_carros,
                     NULL); // Thread 1 (Cruzamento 2)
      pthread_create(&thread2_2, NULL, calcula_capacidade,
                     NULL); // Thread 2 (Cruzamento 2)

      pthread_join(thread2_1, NULL);
      pthread_join(thread2_2, NULL);
      exit(0);
    } else if (pid2 < 0) {
      perror("Erro ao criar o processo 2");
      exit(1);
    }

    // Espera pelos processos filhos
    wait(NULL);
    wait(NULL);
  }

  printf("Sistema de controle de tráfego finalizado após %d repetições.\n",
         REPETICOES);
  return 0;
}