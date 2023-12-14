/*
Sistema de Gestão de Biblioteca em C
Por:Rafael Leite Firmino
Guilherme de oliveira Ferreira
Gustavo Silvestre Mingueti
*/



#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>  // Para a função sleep


struct Livro {
    int codigo;
    char titulo[100];
    char autor[100];
    int quantidade;
    int emprestados;
};
struct Cliente {
    int id;
    char nome[100];
};


void limparTela() {// Função para limpar a tela

    printf("\033c");// ANSI escape code para limpar a tela
}
void imprimirMenu() {
    printf("\nSistema da Biblioteca\n");
    printf("1. Cadastrar novo livro\n");
    printf("2. Cadastrar novo cliente\n");
    printf("3. Emprestar livro\n");
    printf("4. Devolver livro\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
}


int buscarLivroPorTitulo(struct Livro acervo[], int quantidadeLivros, const char *titulo) {// Função para buscar um livro pelo título
    for (int i = 0; i < quantidadeLivros; i++) {
        if (strcmp(acervo[i].titulo, titulo) == 0) {
            return i;  // Retorna o índice do livro se encontrado
        }
    }
    return -1;
}


void cadastrarLivro(struct Livro acervo[], int *quantidadeLivros) {// Função para cadastrar um novo livro
    printf("Digite o título do livro: ");
    scanf(" %[^\n]s", acervo[*quantidadeLivros].titulo);
    printf("Digite a quantidade de cópias: ");
    scanf("%d", &acervo[*quantidadeLivros].quantidade);
    acervo[*quantidadeLivros].emprestados = 0;
    acervo[*quantidadeLivros].codigo = *quantidadeLivros + 1;
    (*quantidadeLivros)++;
    sleep(3);
    limparTela();
}


void emprestarLivro(struct Livro acervo[], int quantidadeLivros, struct Cliente clientes[], int *quantidadeClientes) {
    char tituloLivro[100];// Função para emprestar um livro a um cliente
    int clienteId;
    printf("Digite o título do livro a ser emprestado: ");
    scanf(" %[^\n]s", tituloLivro);

    int livroIndex = buscarLivroPorTitulo(acervo, quantidadeLivros, tituloLivro);

    if (livroIndex != -1) {
        printf("Digite o nome do cliente: ");
        scanf("%d", &clienteId);

        if (acervo[livroIndex].quantidade > acervo[livroIndex].emprestados) {
            acervo[livroIndex].emprestados++;


            printf("Livro emprestado com sucesso para o cliente %s\n", clientes[clienteId].nome);
            printf("Quantidade de livros restantes: %d\n", acervo[livroIndex].quantidade - acervo[livroIndex].emprestados);
            // Mostra a quantidade de livros restantes após o empréstimo

            sleep(3);
            limparTela();
        return ;

        }
         else {
            printf("Desculpe, o livro não está disponível no momento.\n");
            // Adiciona a notificação de erro antes de esperar
            sleep(3);
            limparTela();
            return;
        }
    }

}


void devolverLivro(struct Livro acervo[], int quantidadeLivros) {// Função para devolver um livro
    char tituloLivro[100];
    printf("Digite o título do livro a ser devolvido: ");
    scanf(" %[^\n]s", tituloLivro);

    int livroIndex = buscarLivroPorTitulo(acervo, quantidadeLivros, tituloLivro);

    if (livroIndex != -1) {
        if (acervo[livroIndex].emprestados > 0) {
            acervo[livroIndex].emprestados--;
            printf("Livro devolvido com sucesso.\n");
        } else {
            printf("Este livro não está atualmente emprestado.\n");
        }
    } else {
        printf("Livro não encontrado no acervo.\n");
    }
    sleep(3);
    limparTela();
}


int main() {// Alteração na função principal (main)
    setlocale(LC_ALL, "Portuguese");
    struct Livro acervo[100];
    struct Cliente clientes[100];
    int opcao, quantidadeLivros = 0, quantidadeClientes = 0;

    do {
        limparTela();  // Limpa a tela no início de cada iteração do loop
        imprimirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarLivro(acervo, &quantidadeLivros);
                break;
            case 2:
                printf("Digite o nome do novo cliente: ");
                scanf(" %[^\n]s", clientes[quantidadeClientes].nome);
                clientes[quantidadeClientes].id = quantidadeClientes;
                quantidadeClientes++;
                printf("Cliente cadastrado com sucesso.\n");
                sleep(3);
                limparTela();
                break;
            case 3:
                emprestarLivro(acervo, quantidadeLivros, clientes, &quantidadeClientes);
                break;
            case 4:
                devolverLivro(acervo, quantidadeLivros);
                break;
            case 5:
                printf("Saindo do sistema.\n");
                sleep(3);
                limparTela();
                break;
            default:
                printf("Opção inválida.\n");
                // Adiciona a notificação de erro antes de esperar e limpar a tela
                sleep(3);
                limparTela();
        }
    } while (opcao != 5);

    return 0;
}
