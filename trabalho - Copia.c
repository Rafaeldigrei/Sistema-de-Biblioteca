/*
Sistema de Gest�o de Biblioteca em C
Por:Rafael Leite Firmino
Guilherme de oliveira Ferreira
Gustavo Silvestre Mingueti
*/



#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>  // Para a fun��o sleep


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


void limparTela() {// Fun��o para limpar a tela

    printf("\033c");// ANSI escape code para limpar a tela
}
void imprimirMenu() {
    printf("\nSistema da Biblioteca\n");
    printf("1. Cadastrar novo livro\n");
    printf("2. Cadastrar novo cliente\n");
    printf("3. Emprestar livro\n");
    printf("4. Devolver livro\n");
    printf("5. Sair\n");
    printf("Escolha uma op��o: ");
}


int buscarLivroPorTitulo(struct Livro acervo[], int quantidadeLivros, const char *titulo) {// Fun��o para buscar um livro pelo t�tulo
    for (int i = 0; i < quantidadeLivros; i++) {
        if (strcmp(acervo[i].titulo, titulo) == 0) {
            return i;  // Retorna o �ndice do livro se encontrado
        }
    }
    return -1;
}


void cadastrarLivro(struct Livro acervo[], int *quantidadeLivros) {// Fun��o para cadastrar um novo livro
    printf("Digite o t�tulo do livro: ");
    scanf(" %[^\n]s", acervo[*quantidadeLivros].titulo);
    printf("Digite a quantidade de c�pias: ");
    scanf("%d", &acervo[*quantidadeLivros].quantidade);
    acervo[*quantidadeLivros].emprestados = 0;
    acervo[*quantidadeLivros].codigo = *quantidadeLivros + 1;
    (*quantidadeLivros)++;
    sleep(3);
    limparTela();
}


void emprestarLivro(struct Livro acervo[], int quantidadeLivros, struct Cliente clientes[], int *quantidadeClientes) {
    char tituloLivro[100];// Fun��o para emprestar um livro a um cliente
    int clienteId;
    printf("Digite o t�tulo do livro a ser emprestado: ");
    scanf(" %[^\n]s", tituloLivro);

    int livroIndex = buscarLivroPorTitulo(acervo, quantidadeLivros, tituloLivro);

    if (livroIndex != -1) {
        printf("Digite o nome do cliente: ");
        scanf("%d", &clienteId);

        if (acervo[livroIndex].quantidade > acervo[livroIndex].emprestados) {
            acervo[livroIndex].emprestados++;


            printf("Livro emprestado com sucesso para o cliente %s\n", clientes[clienteId].nome);
            printf("Quantidade de livros restantes: %d\n", acervo[livroIndex].quantidade - acervo[livroIndex].emprestados);
            // Mostra a quantidade de livros restantes ap�s o empr�stimo

            sleep(3);
            limparTela();
        return ;

        }
         else {
            printf("Desculpe, o livro n�o est� dispon�vel no momento.\n");
            // Adiciona a notifica��o de erro antes de esperar
            sleep(3);
            limparTela();
            return;
        }
    }

}


void devolverLivro(struct Livro acervo[], int quantidadeLivros) {// Fun��o para devolver um livro
    char tituloLivro[100];
    printf("Digite o t�tulo do livro a ser devolvido: ");
    scanf(" %[^\n]s", tituloLivro);

    int livroIndex = buscarLivroPorTitulo(acervo, quantidadeLivros, tituloLivro);

    if (livroIndex != -1) {
        if (acervo[livroIndex].emprestados > 0) {
            acervo[livroIndex].emprestados--;
            printf("Livro devolvido com sucesso.\n");
        } else {
            printf("Este livro n�o est� atualmente emprestado.\n");
        }
    } else {
        printf("Livro n�o encontrado no acervo.\n");
    }
    sleep(3);
    limparTela();
}


int main() {// Altera��o na fun��o principal (main)
    setlocale(LC_ALL, "Portuguese");
    struct Livro acervo[100];
    struct Cliente clientes[100];
    int opcao, quantidadeLivros = 0, quantidadeClientes = 0;

    do {
        limparTela();  // Limpa a tela no in�cio de cada itera��o do loop
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
                printf("Op��o inv�lida.\n");
                // Adiciona a notifica��o de erro antes de esperar e limpar a tela
                sleep(3);
                limparTela();
        }
    } while (opcao != 5);

    return 0;
}
