#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct{
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char dataNasciimento[20];
    char dataCadstro[20];
}Cliente;

typedef struct{
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldoTotal; // Saldo + limite
}Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarConta();
float atualizacaoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta conta_origem, Conta conta_destino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");
    menu();
    return 0;
}

void menu() {
    int opcao = 0;
    printf("==================================================\n");
    printf("======================  ATM  ======================\n");
    printf("================= -> JHON BANK <- ==================\n");
    printf("=====================================================\n");

    printf("Selecione uma opção no Menu: \n");
    printf("1 - Criar Conta\n");
    printf("2 - Efetuar Saque\n");
    printf("3 - Efetuar Depósito\n");
    printf("4 - Efetuar Transferência\n");
    printf("5 - Listar Contas\n");
    printf("6 - Sair\n");

    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            criarConta();
            break;
        case 2:
            efetuarSaque();
            break;
        case 3:
            efetuarDeposito();
            break;
        case 4:
            efetuarTransferencia();
            break;
        case 5:
            listarConta();
            break;
        case 6:
            printf("Até a proxima!\n");
            Sleep(2000);
            exit(0);
        default:
            printf("Opção inválida!\n");
            Sleep(2000);
            menu();
            break;
    }
}


void infoCliente(Cliente cliente){
    printf("Código: %d\nNome: %s\nData de Nascimento: %s\nCadastro: %s", cliente.codigo, strtok(cliente.nome, "\n"), 
    strtok(cliente.dataNasciimento, "\n"), strtok(cliente.dataCadstro, "\n"));
}
void infoConta(Conta conta){
    printf("Número da Conta: %d \nCliente: %s\nData Nascimento: %s \nData Cadastro: %s \nSaldo Total: %.2f\n ", conta.numero, strtok(conta.cliente.nome, "\n"),
    strtok(conta.cliente.dataNasciimento, "\n"), strtok(conta.cliente.dataCadstro, "\n"), conta.saldoTotal);
}
void criarConta(){
    // falta implementar a funcionalidade
}
float atualizacaoTotal(Conta conta){
    // falta implementar a funcionalidade
}
Conta buscarContaPorNumero(int numero){
    // falta implementar a funcionalidade
}
void sacar(Conta conta, float valor){
    // falta implementar a funcionalidade
}
void depositar(Conta conta, float valor){
    // falta implementar a funcionalidade
}
void transferir(Conta conta_origem, Conta conta_destino, float valor){
    // falta implementar a funcionalidade
}
void efetuarSaque(){
    // falta implementar a funcionalidade
}
void efetuarDeposito(){
    // falta implementar a funcionalidade
}
void efetuarTransferencia(){
    // falta implementar a funcionalidade
}
void listarConta(){
    // falta implementar a funcionalidade
}