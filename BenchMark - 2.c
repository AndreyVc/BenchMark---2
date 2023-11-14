#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar números aleatórios e salvar em um arquivo
void gerarArquivo(int quantidade) {
    FILE *arquivo = fopen("numeros.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d ", rand() % 100); // Números aleatórios de 0 a 99
    }

    fclose(arquivo);
}

// Função para abrir o arquivo
FILE *abrirArquivo(const char *nome, const char *modo) {
    FILE *arquivo = fopen(nome, modo);

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    return arquivo;
}

// Função para realizar a busca linear
int buscaLinear(int numero, FILE *arquivo) {
    rewind(arquivo);
    int valor;

    while (fscanf(arquivo, "%d", &valor) == 1) {
        if (valor == numero) {
            return 1; // Encontrou o número
        }
    }

    return 0; // Não encontrou o número
}

// Função para realizar a busca sentinela
int buscaSentinela(int numero, FILE *arquivo) {
    rewind(arquivo);
    int ultimo;

    while (fscanf(arquivo, "%d", &ultimo) == 1 && ultimo != numero) {
    }

    return (ultimo == numero) ? 1 : 0; // Encontrou ou não o número
}

// Função para realizar a busca binária
int buscaBinaria(int numero, FILE *arquivo, int quantidade) {
    rewind(arquivo);
    int inicio = 0, fim = quantidade - 1, meio, valor;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        fseek(arquivo, meio * sizeof(int), SEEK_SET);
        fscanf(arquivo, "%d", &valor);

        if (valor == numero) {
            return 1; // Encontrou o número
        } else if (valor < numero) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return 0; // Função para informar que não foi possivel encontrar o número
}

// Função para medir o tempo de execução de uma operação
double medirTempo(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Função para realizar operações de buscas
void executarOperacoesBusca(FILE *arquivo, int quantidade) {
    int numero;

    printf("Digite o número a ser buscado: ");
    scanf("%d", &numero);

    clock_t inicio, fim;

    inicio = clock();
    printf("Busca Linear: %s\n", buscaLinear(numero, arquivo) ? "Encontrado" : "Não encontrado");
    fim = clock();
    printf("Tempo de execução (Busca Linear): %.6f segundos\n", medirTempo(inicio, fim));

    inicio = clock();
    printf("Busca Sentinela: %s\n", buscaSentinela(numero, arquivo) ? "Encontrado" : "Não encontrado");
    fim = clock();
    printf("Tempo de execução (Busca Sentinela): %.6f segundos\n", medirTempo(inicio, fim));

    inicio = clock();
    printf("Busca Binária: %s\n", buscaBinaria(numero, arquivo, quantidade) ? "Encontrado" : "Não encontrado");
    fim = clock();
    printf("Tempo de execução (Busca Binária): %.6f segundos\n", medirTempo(inicio, fim));
}

// Função principal
int main() {
    int opcao, quantidade;
    FILE *arquivo;

    printf("Digite a quantidade de números a serem gerados: ");
    scanf("%d", &quantidade);

    gerarArquivo(quantidade);

    do {
        printf("\n--- MENU ---\n");
        printf("1. Busca de elemento\n");
        printf("2. Classificação de elementos\n");
        printf("3. Comparação entre algoritmos iterativos e recursivos\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                arquivo = abrirArquivo("numeros.txt", "r");
                executarOperacoesBusca(arquivo, quantidade);
                fclose(arquivo);
                break;

            // Adiciona casos para as outras operações (classificação e comparação)

            case 4:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
}
