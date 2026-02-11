#include <stdio.h>
#include <string.h>

#define TAMANHO_PRATELEIRA 20

struct Livro {
    int codigo;
    int ano;
    char titulo[50];
    char autor[30];
    char area[30];
    char editora[30];
};

// Função para limpar o buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

// Função para ler texto com segurança
void lerTexto(char texto[], int tamanho) {
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0'; // remove o ENTER
}

void cadastrarLivros(struct Livro prateleira[], int *qtd) {
    int n;

    printf("Quantos livros deseja cadastrar? ");
    scanf("%d", &n);
    limparBuffer();

    if (*qtd + n > TAMANHO_PRATELEIRA) {
        printf("Voce pode cadastrar no maximo %d livros.\n", TAMANHO_PRATELEIRA - *qtd);
        n = TAMANHO_PRATELEIRA - *qtd;
    }

    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do livro %d ===\n", *qtd + 1);

        printf("Codigo: ");
        scanf("%d", &prateleira[*qtd].codigo);
        limparBuffer();

        printf("Titulo: ");
        lerTexto(prateleira[*qtd].titulo, 50);

        printf("Autor: ");
        lerTexto(prateleira[*qtd].autor, 30);

        printf("Area: ");
        lerTexto(prateleira[*qtd].area, 30);

        printf("Ano: ");
        scanf("%d", &prateleira[*qtd].ano);
        limparBuffer();

        printf("Editora: ");
        lerTexto(prateleira[*qtd].editora, 30);

        (*qtd)++;
        printf("Livro cadastrado com sucesso!\n");
    }
}

void imprimirLivros(struct Livro prateleira[], int qtd) {
    if (qtd == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Livros ===\n");

    for (int i = 0; i < qtd; i++) {
        printf("\nLivro %d\n", i + 1);
        printf("Codigo: %d\n", prateleira[i].codigo);
        printf("Titulo: %s\n", prateleira[i].titulo);
        printf("Autor: %s\n", prateleira[i].autor);
        printf("Area: %s\n", prateleira[i].area);
        printf("Ano: %d\n", prateleira[i].ano);
        printf("Editora: %s\n", prateleira[i].editora);
    }
}

void pesquisarLivro(struct Livro prateleira[], int qtd, int codigoBusca) {
    for (int i = 0; i < qtd; i++) {
        if (prateleira[i].codigo == codigoBusca) {
            printf("\n=== Livro Encontrado ===\n");
            printf("Titulo: %s\n", prateleira[i].titulo);
            printf("Autor: %s\n", prateleira[i].autor);
            printf("Ano: %d\n", prateleira[i].ano);
            return;
        }
    }

    printf("Livro com codigo %d nao encontrado.\n", codigoBusca);
}

void ordenarLivros(struct Livro prateleira[], int qtd) {
    struct Livro temp;

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - 1 - i; j++) {
            if (prateleira[j].ano > prateleira[j + 1].ano) {
                temp = prateleira[j];
                prateleira[j] = prateleira[j + 1];
                prateleira[j + 1] = temp;
            }
        }
    }

    printf("Livros ordenados por ano com sucesso!\n");
}

int main() {
    struct Livro prateleira[TAMANHO_PRATELEIRA];
    int qtd = 0;
    int opcao;

    do {
        printf("\n--- Menu Biblioteca ---\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Pesquisar\n");
        printf("4 - Ordenar por ano\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarLivros(prateleira, &qtd);
                break;
            case 2:
                imprimirLivros(prateleira, qtd);
                break;
            case 3: {
                int codigo;
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                limparBuffer();
                pesquisarLivro(prateleira, qtd, codigo);
                break;
            }
            case 4:
                ordenarLivros(prateleira, qtd);
                break;
            case 5:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 5);

    return 0;
}
