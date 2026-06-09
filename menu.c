#include <stdio.h>

int main() {
    int opcao;

    while (opcao != 0) {
        printf("\n===== HEAP PRIORITY QUEUE =====\n");
        printf("1. Inserir item manualmente\n");
        printf("2. Remover item de maior prioridade\n");
        printf("3. Ver topo (maior prioridade)\n");
        printf("4. Imprimir heap (primeiros 10)\n");
        printf("5. Carregar CSV\n");
        printf("6. Verificar se está vazia\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}