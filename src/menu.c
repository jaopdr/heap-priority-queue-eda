#include <stdio.h>
#include "heap.h"

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

void carregar_csv(Heap *heap, const char *caminho) {
    FILE *file = fopen(caminho, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return;
    }

    char linha[256];
    int iteracoes_totais = 0;

    fgets(linha, sizeof(linha), file);

    while (fgets(linha, sizeof(linha), file)) {
        Item item;
        sscanf(linha, "%99[^,],%19[^,],%d,%49[^\n]", item.nome, item.matricula, &item.ranking, item.curso);
        iteracoes_totais += heap_inserir(heap, item);
    }

    fclose(file);
    printf("CSV carregado com sucesso. Total de iteracoes: %d\n", iteracoes_totais);

}

int main() {
    int opcao;
    char caminho_arquivo[] = "../dados/dataset_v1.csv";
    Heap heap;
    inicializar_heap(&heap);

    opcao = -1;
    while (opcao != 0) {
        printf("\n===== HEAP PRIORITY QUEUE =====\n");
        printf("1. Inserir item manualmente\n");
        printf("2. Remover item de maior prioridade\n");
        printf("3. Ver topo (maior prioridade)\n");
        printf("4. Imprimir heap (primeiros 10)\n");
        printf("5. Carregar CSV\n");
        printf("6. Verificar se esta vazia\n");
        printf("7. Verificar se esta cheia\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (heap_cheia(&heap)) {
                    printf("Heap esta cheia. Nao e possivel inserir mais itens.\n");
                } else {
                    Item item;
                    printf("Digite o nome: ");
                    scanf(" %[^\n]", item.nome);
                    printf("Digite a matricula: ");
                    scanf(" %[^\n]", item.matricula);
                    printf("Digite o ranking: ");
                    scanf("%d", &item.ranking);
                    printf("Digite o curso: ");
                    scanf(" %[^\n]", item.curso);
                    int iteracoes = heap_inserir(&heap, item);
                    printf("Iteracoes realizadas: %d\n", iteracoes);
                }
                pausar();
                break;
            case 2:
                if (heap_vazia(&heap)) {
                    printf("Heap está vazia. Nao ha itens para remover.\n");
                } else {
                    Item *removido = heap_remover(&heap);
                    printf("Item removido: %s %s %d %s\n", removido->nome, removido->matricula, removido->ranking, removido->curso);
                }   
                pausar();
                break;
            case 3:
                Item *topo = heap_topo(&heap);
                if (topo) {
                    printf("Topo: %s %s %d %s\n", topo->nome, topo->matricula, topo->ranking, topo->curso);
                } else {
                    printf("Heap vazio.\n");
                }
                pausar();
                break;
            case 4:
                imprimir_heap(&heap, heap.tamanho);
                pausar();
                break;
            case 5:
                carregar_csv(&heap, caminho_arquivo);
                pausar();
                break;
            case 6:
                if (heap_vazia(&heap)) {
                    printf("Heap esta vazia.\n");
                } else {
                    printf("Heap nao esta vazia.\n");
                }
                pausar();
                break;
            case 7:
                if (heap_cheia(&heap)) {
                    printf("Heap esta cheia.\n");
                } else {
                    printf("Heap nao esta cheia.\n");
                }
                pausar();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}