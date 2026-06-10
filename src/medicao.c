#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"

// Lê todos os registros do CSV, retorna a quantidade lida
int carregar_csv(const char *caminho, Item *registros, int max) {
    FILE *f = fopen(caminho, "r");
    if (!f) {
        printf("Erro ao abrir '%s'.\n", caminho);
        return 0;
    }

    char linha[256];
    // Pula cabeçalho
    fgets(linha, sizeof(linha), f);

    int count = 0;
    while (count < max && fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = 0;

        Item item;
        char *tok = strtok(linha, ",");
        if (!tok) continue;
        strncpy(item.nome, tok, sizeof(item.nome) - 1);

        tok = strtok(NULL, ",");
        if (!tok) continue;
        strncpy(item.matricula, tok, sizeof(item.matricula) - 1);

        tok = strtok(NULL, ",");
        if (!tok) continue;
        item.ranking = atoi(tok);

        tok = strtok(NULL, ",");
        if (!tok) continue;
        strncpy(item.curso, tok, sizeof(item.curso) - 1);

        registros[count++] = item;
    }

    fclose(f);
    return count;
}

// Embaralha o array de registros aleatoriamente (Fisher-Yates)
void embaralhar(Item *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Item tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int main() {
    char caminho_csv[256];
    printf("Caminho do arquivo CSV: ");
    scanf("%255s", caminho_csv);

    // Carrega todos os registros
    Item *todos = malloc(10000 * sizeof(Item));
    if (!todos) { printf("Erro de memoria.\n"); return 1; }

    int total = carregar_csv(caminho_csv, todos, 10000);
    if (total == 0) { free(todos); return 1; }
    printf("Total de registros carregados: %d\n", total);

    // Tamanhos dos subconjuntos
    int tamanhos[] = {500, 1000, 1500, 2000, 2500, 3000, 3500,
                      4000, 4500, 5000, 5500, 6000, 6500,
                      7000, 7500, 8000, 8500, 9000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    // Arquivo de saída com os resultados
    FILE *saida = fopen("resultados.csv", "w");
    if (!saida) { printf("Erro ao criar resultados.csv\n"); free(todos); return 1; }
    fprintf(saida, "n,media_iteracoes\n");

    srand((unsigned int)time(NULL));

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        if (n > total) {
            printf("Base %d: tamanho maior que o dataset, pulando.\n", n);
            continue;
        }

        // Sorteia subconjunto: embaralha tudo e pega os primeiros n
        embaralhar(todos, total);

        // Insere os n primeiros na heap e acumula iterações
        Heap heap;
        inicializar_heap(&heap);

        long long total_iter = 0;
        for (int i = 0; i < n; i++) {
            int iter = heap_inserir(&heap, todos[i]);
            if (iter >= 0)
                total_iter += iter;
        }

        double media = (double)total_iter / n;
        printf("Base %5d -> total iteracoes: %lld | media: %.4f\n", n, total_iter, media);
        fprintf(saida, "%d,%.4f\n", n, media);
    }

    fclose(saida);
    free(todos);

    printf("\nResultados salvos em 'resultados.csv'.\n");
    return 0;
}
