//LINK NO GITHUB: https://github.com/GabrielSS1306/PROJETO-FINAL-APC.git

#include <stdio.h> //biblioteca para incluir dispositivos de entrada e saída 
#include <stdlib.h> //biblioteca para incluir funções utilitárias 
#include <string.h> //biblioteca para manipular strings 
typedef struct { // typedef para nova definição e o struct para ser de várias variáveis 
    int id, quantidade; //int sendo identificador de inteiro 
    char nome[50]; //char sendo um vetor 
    float preco; //float identificador de real 
    char categoria[30]; 
} Produto; //Produto=definiu a struct 

Produto estoque [100]; //array
int total =0;

void adicionarProdutos () { //void para a funcão não retornar nada 
    
    printf("Digite o ID do produto: "); //printf sendo um output
    scanf("%d", & estoque[total].id); //scanf sendo um input

    printf("Digite a quantidade de produtos: ");
    scanf("%d", & estoque[total].quantidade); //armazenamento 

    printf("Digite o preço do produto: ");
    scanf("%f", & estoque[total].preco);

    printf("Digite o nome do produto: ");
    scanf("%[^\n]", & estoque[total].nome);

    printf("Categoria: ");
    scanf(" %[^\n]", & estoque[total].categoria);

    total ++; //aumenta sempre que um novo produto for cadastrado 
}

void listarProdutos() {
    
    for (int i = 0; i < total; i++) { //for sendo um comando de repetição se a condição for verdadeira 
        printf("\nID: %d | Nome: %s | Qtd: %d | Preço: %.2f\n",
        estoque[i].id, //armazenamento
        estoque[i].nome,
        estoque[i].quantidade,
        estoque[i].preco,
        estoque[i].categoria);
    }
}

int buscarProdutosporID (int id) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].id == id) //if sendo uma condição
        return i;
    }
return - 1; //return para devolver o resultado 
}

void alterarQuantidade () {
    int id;
    
    printf("Digite o ID do produto: ");
    scanf("%d", & id);

    int pos = buscarProdutosporID (id);

    if (pos == -1) {
        printf("O produto digitado não encontrado.\n");
        return;
    }

    printf("A nova quantidade de produtos é: ");
    scanf("%d", &estoque[pos].quantidade);
}

void removerProdutos () {
    int id;
    
    printf("Digite o ID do produto: ");
    scanf("%d", & id);

    int pos = buscarProdutosporID (id);

    if (pos == -1) {
        printf("O produto digitado não encontrado.\n");
        return;
    }

    for (int i = pos; i < total - 1; i++) {
        estoque[i] = estoque[i + 1];
    }
    total--; //diminui sempre que um produto for removido
}

void listarProdutosCategoria () {
    char buscada[30];
    int encontrado = 0;

    printf("Digite a categoria de produtos que deseja listar: ");
    scanf("%[^\n]", buscada);

    printf("\n--- Produtos da Categoria: %s ---\n", buscada);

    for (int i = 0; i < total; i++) {
        if (strcmp(estoque[i].categoria, buscada) == 0) { //strcmp comparando duas strings de caracteres
            printf("ID: %d | Nome: %s | Qtd: %d | Preço: %.2f\n",
                estoque[i].id,
                estoque[i].nome,
                estoque[i].quantidade,
                estoque[i].preco);
            encontrado = 1;
        }
    }

    if (!encontrado) { 
        printf("Nenhum produto encontrado nessa categoria.\n");
    }
}

int lerOpcaoMenu() {
    char entrada[10];

    printf("Escolha uma opção: ");
    fgets(entrada, sizeof(entrada), stdin); //fgets para ler texto, sizeof para retornar quantos bytes, stdin para ler dados digitados pelo usuário

    if (entrada[0] == '\n') {
        printf("Opção inválida! Digite um número de 1 a 6.\n");
        return -1;  
    }

    return atoi(entrada); //atoi para converter uma string em um int
}

int main() { //main sendo a função principal
    int opcao;

    do { //do iniciando um laço de repetição dentro de uma condição 
        printf("\n=====================================\n");
        printf("      BEM-VINDO AO NOSSO MERCADO\n");
        printf("=====================================\n");
        printf("          GERENCIADOR DE ESTOQUE\n");
        printf("=====================================\n");
        printf("1 ➜ Adicionar produtos\n");
        printf("2 ➜ Listar produtos\n");
        printf("3 ➜ Alterar quantidade\n");
        printf("4 ➜ Remover produtos\n");
        printf("5 ➜ Listar por categoria\n");
        printf("6 ➜ Sair\n");
        printf("=====================================\n");
        printf("Escolha uma opção: ");
        
        opcao = lerOpcaoMenu();

        if (opcao == -1) {
            continue; //continue para próxima condição
        }
    
        switch(opcao) { //switch sendo estrutrua de seleção
            case 1: adicionarProdutos(); break;
            case 2: listarProdutos(); break;
            case 3: alterarQuantidade(); break; //case colocando a opção a ser selecionada, condição
            case 4: removerProdutos(); break;
            case 5: listarProdutosCategoria(); break; //break para parar caso a opção seja escolhida
            case 6: printf("Obrigado pela preferência! Volte sempre!\n"); break;
            default: //default executado quando nenhuma das opções for usada
                printf("Opção inválida! Digite um número de 1 a 6.\n");
    }
}   while (opcao != 6); //while sendo laço de repetição 


    return 0;
}